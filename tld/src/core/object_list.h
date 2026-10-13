#pragma once

// Mutex-guarded list; written by game threads through the manager hooks,
// read on the render thread.
template<typename T>
class ObjectList
{
	std::vector<T> items;
	mutable std::mutex mtx;
public:
	void add(T item)
	{
		std::lock_guard lock(mtx);
		items.push_back(item);
	}

	void remove(T item)
	{
		std::lock_guard lock(mtx);
		auto it = std::find(items.begin(), items.end(), item);
		if (it != items.end())
		{
			std::swap(*it, items.back());
			items.pop_back();
		}
	}

	template<typename F>
	void for_each(F&& func) const
	{
		std::lock_guard lock(mtx);
		for (auto item : items)
			func(item);
	}

	size_t size() const
	{
		std::lock_guard lock(mtx);
		return items.size();
	}
};
