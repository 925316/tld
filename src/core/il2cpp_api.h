#pragma once

// Thin wrappers over the IL2CPP runtime API exported by GameAssembly.dll.
// They allow looking up classes and reading static fields by name, which is
// useful when there is no game instance to read a static from.
namespace Il2Cpp
{
	// Resolves the exported il2cpp_* entry points. Safe to call repeatedly.
	bool Init();

	// Returns the Il2CppImage* of the named assembly (e.g. "Assembly-CSharp").
	void* GetImage(const char* assemblyName);

	// Returns the Il2CppClass* for a type, or nullptr.
	void* FindClass(const char* namespaze, const char* className);

	// Reads a static field by name. For reference-type fields the returned
	// value is the object pointer; returns nullptr when unavailable.
	void* GetStaticFieldValue(void* klass, const char* fieldName);

	// Offset of an instance field within its object, or 0 when not found.
	uintptr_t GetFieldOffset(void* klass, const char* fieldName);
}
