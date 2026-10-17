#include "pch.h"
#include "core/game.h"
#include "core/il2cpp_api.h"

namespace Il2Cpp
{
	using DomainGetFn = void* (*)();
	using DomainGetAssembliesFn = void** (*)(void*, size_t*);
	using AssemblyGetImageFn = void* (*)(void*);
	using ImageGetNameFn = const char* (*)(void*);
	using ClassFromNameFn = void* (*)(void*, const char*, const char*);
	using ClassGetFieldFromNameFn = void* (*)(void*, const char*);
	using FieldGetOffsetFn = uintptr_t(*)(void*);
	using FieldStaticGetValueFn = void (*)(void*, void*);

	DomainGetFn domain_get = nullptr;
	DomainGetAssembliesFn domain_get_assemblies = nullptr;
	AssemblyGetImageFn assembly_get_image = nullptr;
	ImageGetNameFn image_get_name = nullptr;
	ClassFromNameFn class_from_name = nullptr;
	ClassGetFieldFromNameFn class_get_field_from_name = nullptr;
	FieldGetOffsetFn field_get_offset = nullptr;
	FieldStaticGetValueFn field_static_get_value = nullptr;

	bool initialized = false;

	template<typename T>
	T Export(HMODULE module, const char* name)
	{
		return reinterpret_cast<T>(GetProcAddress(module, name));
	}

	bool Init()
	{
		if (initialized) return true;

		HMODULE module = GetModuleHandleA("GameAssembly.dll");
		if (!module) return false;

		domain_get = Export<DomainGetFn>(module, "il2cpp_domain_get");
		domain_get_assemblies = Export<DomainGetAssembliesFn>(module, "il2cpp_domain_get_assemblies");
		assembly_get_image = Export<AssemblyGetImageFn>(module, "il2cpp_assembly_get_image");
		image_get_name = Export<ImageGetNameFn>(module, "il2cpp_image_get_name");
		class_from_name = Export<ClassFromNameFn>(module, "il2cpp_class_from_name");
		class_get_field_from_name = Export<ClassGetFieldFromNameFn>(module, "il2cpp_class_get_field_from_name");
		field_get_offset = Export<FieldGetOffsetFn>(module, "il2cpp_field_get_offset");
		field_static_get_value = Export<FieldStaticGetValueFn>(module, "il2cpp_field_static_get_value");

		initialized = domain_get && domain_get_assemblies && assembly_get_image && image_get_name &&
			class_from_name && class_get_field_from_name;

		if (!initialized)
		{
			std::cout << "[ERROR] il2cpp API lookup failed\n";
		}
		return initialized;
	}

	void* GetImage(const char* assemblyName)
	{
		if (!Init() || !assemblyName) return nullptr;

		void* domain = domain_get();
		if (!domain) return nullptr;

		size_t count = 0;
		void** assemblies = domain_get_assemblies(domain, &count);
		if (!assemblies) return nullptr;

		for (size_t i = 0; i < count; ++i)
		{
			void* image = assembly_get_image(assemblies[i]);
			if (!image) continue;
			const char* name = image_get_name(image);
			if (name && std::strcmp(name, assemblyName) == 0) return image;
		}
		return nullptr;
	}

	void* FindClass(const char* namespaze, const char* className)
	{
		if (!Init()) return nullptr;
		void* image = GetImage("Assembly-CSharp");
		if (!image) return nullptr;
		return class_from_name(image, namespaze ? namespaze : "", className);
	}

	void* GetStaticFieldValue(void* klass, const char* fieldName)
	{
		if (!klass || !fieldName || !class_get_field_from_name || !field_static_get_value) return nullptr;

		void* field = class_get_field_from_name(klass, fieldName);
		if (!field) return nullptr;

		void* value = nullptr;
		field_static_get_value(field, &value);
		return value;
	}

	uintptr_t GetFieldOffset(void* klass, const char* fieldName)
	{
		if (!klass || !fieldName || !class_get_field_from_name || !field_get_offset) return 0;

		void* field = class_get_field_from_name(klass, fieldName);
		if (!field) return 0;
		return field_get_offset(field);
	}
}
