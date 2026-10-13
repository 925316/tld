#pragma once

// Boyer-Moore-Horspool
uintptr_t scan_pattern(const std::string& module_name, const std::string& sig)
{
	HMODULE hMod = GetModuleHandleA(module_name.c_str());
	if (!hMod)
		return 0;

	MODULEINFO modInfo;
	if (!GetModuleInformation(GetCurrentProcess(), hMod, &modInfo, sizeof(modInfo)))
		return 0;

	const uint8_t* module_base = static_cast<const uint8_t*>(modInfo.lpBaseOfDll);
	size_t module_size = modInfo.SizeOfImage;

	std::vector<uint8_t> pattern;
	std::vector<uint8_t> mask;
	pattern.reserve(sig.size() / 2);
	mask.reserve(sig.size() / 2);

	const char* s = sig.c_str();
	size_t len = sig.size();

	auto hex_digit = [](char c) -> int
		{
			if (c >= '0' && c <= '9') return c - '0';
			if (c >= 'a' && c <= 'f') return c - 'a' + 10;
			if (c >= 'A' && c <= 'F') return c - 'A' + 10;
			return -1;
		};

	for (size_t i = 0; i < len; ++i)
	{
		if (s[i] == ' ')
			continue;

		if (s[i] == '?')
		{
			pattern.push_back(0x00);
			mask.push_back(0x00);
			if (i + 1 < len && s[i + 1] == '?') ++i;
		}
		else
		{
			int high = hex_digit(s[i]);
			int low = (i + 1 < len) ? hex_digit(s[i + 1]) : -1;

			if (high == -1 || low == -1)
				return 0;

			uint8_t byte = static_cast<uint8_t>((high << 4) | low);
			pattern.push_back(byte);
			mask.push_back(0xFF);
			++i;
		}
	}

	size_t pat_len = pattern.size();
	if (pat_len == 0)
		return 0;
	if (module_size < pat_len)
		return 0;

	size_t pivot_index = pat_len - 1;
	while (pivot_index > 0 && mask[pivot_index] == 0x00)
		--pivot_index;

	bool is_all_wild = (mask[pivot_index] == 0x00);
	if (is_all_wild)
		return 0;

	struct Block { size_t offset; size_t length; const uint8_t* data; };
	std::vector<Block> blocks;
	blocks.reserve(16);

	size_t block_start = 0;
	while (block_start < pat_len)
	{
		while (block_start < pat_len && mask[block_start] == 0x00)
			++block_start;
		if (block_start >= pat_len)
			break;

		size_t block_end = block_start;
		while (block_end < pat_len && mask[block_end] != 0x00)
			++block_end;

		blocks.push_back({ block_start,
						   block_end - block_start,
						   &pattern[block_start] });
		block_start = block_end;
	}

	size_t skip_table[256];
	size_t default_skip = pivot_index + 1;
	for (size_t i = 0; i < 256; ++i)
		skip_table[i] = default_skip;

	for (size_t i = 0; i < pivot_index; ++i)
	{
		if (mask[i] == 0xFF)
			skip_table[pattern[i]] = pivot_index - i;
	}

	const uint8_t* scan_ptr = module_base;
	const uint8_t* end_ptr = module_base + module_size - pat_len;

	while (scan_ptr <= end_ptr)
	{
		if (scan_ptr[pivot_index] == pattern[pivot_index])
		{
			bool match = true;

			for (const auto& blk : blocks)
			{
				if (memcmp(scan_ptr + blk.offset, blk.data, blk.length) != 0)
				{
					match = false;
					break;
				}
			}

			if (match)
				return reinterpret_cast<uintptr_t>(scan_ptr);
		}

		scan_ptr += skip_table[scan_ptr[pivot_index]];
	}

	return 0;
}