```cs
// Namespace: 
public class BaseAi : MonoBehaviour // TypeDefIndex: 8082
{
	// Fields
    public Vector3[] m_Waypoints; // 0x18
    //...
    public string m_DisplayName; // 0x910
    //...
    public float m_CurrentHP; // 0x930
	public float m_MaxHP; // 0x934
    //...
}

// Namespace: 
[RequireComponent] // RVA: 0x19C1D0 Offset: 0x19B5D0 VA: 0x18019C1D0
public class vp_FPSCamera : vp_Component // TypeDefIndex: 7694
{
	// Fields
	private const float ZOOMED_FOV_MULTIPLIER = 0.7;
	private const float MIN_TIME_STEP = 0.02;
	public static bool s_EnabledCustomFixedStep; // 0x0
	protected CharacterController Controller; // 0x40
    //...
    protected Camera m_Camera; // 0x1E0
}
```

# Camera* Camera::get_main():
48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 40 53 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 98 ? ? ? ? 48 85 DB

```asm
il2cpp:00000000016282A0                ; UnityEngine_Camera_o *GameManager__GetMainCamera(const MethodInfo *method)
il2cpp:00000000016282A0                GameManager$$GetMainCamera proc near    ; DATA XREF: .data:0000000004500508↓o
il2cpp:00000000016282A0                                                        ; .pdata:0000000004A65EA4↓o ...
il2cpp:00000000016282A0
il2cpp:00000000016282A0                var_28          = qword ptr -28h
il2cpp:00000000016282A0                var_20          = qword ptr -20h
il2cpp:00000000016282A0                var_18          = qword ptr -18h
il2cpp:00000000016282A0                var_10          = qword ptr -10h
il2cpp:00000000016282A0
il2cpp:00000000016282A0                ; __unwind { // __CxxFrameHandler3
il2cpp:00000000016282A0 48 83 EC 48                    sub     rsp, 48h
il2cpp:00000000016282A4 48 C7 44 24 20                 mov     [rsp+48h+var_28], 0FFFFFFFFFFFFFFFEh
il2cpp:00000000016282A4 FE FF FF FF
il2cpp:00000000016282AD 80 3D 33 43 05                 cmp     cs:byte_467C5E7, 0
il2cpp:00000000016282AD 03 00
il2cpp:00000000016282B4 75 4F                          jnz     short loc_1628305
il2cpp:00000000016282B6 48 8B 05 03 5C                 mov     rax, cs:qword_466DEC0
il2cpp:00000000016282B6 04 03
...
```


# vp_FPSCamera GameManager::GetVpFPSCamera():
48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 80 ? ? ? ? 48 83 C4 ? C3 40 53 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 88 ? ? ? ? 48 8B 05 ? ? ? ? 33 D2 48 89 54 24 ? 48 89 54 24 ? 48 89 54 24 ? 4C 8D 44 24 ? 8B 94 01 ? ? ? ? 8B 8C 01 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 98 ? ? ? ? 48 85 DB
```asm
il2cpp:00000000016285C0                ; vp_FPSCamera_o *GameManager__GetVpFPSCamera(const MethodInfo *method)
il2cpp:00000000016285C0                GameManager$$GetVpFPSCamera proc near   ; DATA XREF: .data:0000000004500530↓o
il2cpp:00000000016285C0                                                        ; .pdata:0000000004A65EE0↓o ...
il2cpp:00000000016285C0
il2cpp:00000000016285C0                var_28          = qword ptr -28h
il2cpp:00000000016285C0                var_20          = qword ptr -20h
il2cpp:00000000016285C0                var_18          = qword ptr -18h
il2cpp:00000000016285C0                var_10          = qword ptr -10h
il2cpp:00000000016285C0
il2cpp:00000000016285C0                ; __unwind { // __CxxFrameHandler3
il2cpp:00000000016285C0 48 83 EC 48                    sub     rsp, 48h
il2cpp:00000000016285C4 48 C7 44 24 20                 mov     [rsp+48h+var_28], 0FFFFFFFFFFFFFFFEh
il2cpp:00000000016285C4 FE FF FF FF
il2cpp:00000000016285CD 80 3D 51 40 05                 cmp     cs:byte_467C625, 0
il2cpp:00000000016285CD 03 00
...
```

# Vector3 Camera::WorldToScreenPoint(Vector3, int eye):
48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 33 C0 41 8B F9 48 89 44 24 ? 49 8B F0 89 44 24 ? 48 8B EA 48 8B 05 ? ? ? ? 48 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 89 05 ? ? ? ? 4C 8D 4C 24 ? 44 8B C7 48 8B D6 48 8B CD FF D0 8B 44 24 ? F2 0F 10 44 24 ? 48 8B 6C 24 ? 48 8B 74 24 ? ? ? ? ? 89 43 ? 48 8B C3 48 8B 5C 24 ? 48 83 C4 ? 5F C3 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 33 C0 41 8B F9 48 89 44 24 ? 49 8B F0 89 44 24 ? 48 8B EA 48 8B 05 ? ? ? ? 48 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 89 05 ? ? ? ? 4C 8D 4C 24 ? 44 8B C7 48 8B D6 48 8B CD FF D0 8B 44 24 ? F2 0F 10 44 24 ? 48 8B 6C 24 ? 48 8B 74 24 ? ? ? ? ? 89 43 ? 48 8B C3 48 8B 5C 24 ? 48 83 C4 ? 5F C3 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 33 C0 41 8B F9 48 89 44 24 ? 49 8B F0 89 44 24 ? 48 8B EA 48 8B 05 ? ? ? ? 48 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 89 05 ? ? ? ? 4C 8D 4C 24 ? 44 8B C7 48 8B D6 48 8B CD FF D0 8B 44 24 ? F2 0F 10 44 24 ? 48 8B 6C 24 ? 48 8B 74 24 ? ? ? ? ? 89 43 ? 48 8B C3 48 8B 5C 24 ? 48 83 C4 ? 5F C3 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24
```asm
il2cpp:0000000001284630                ; UnityEngine_Vector3_o UnityEngine_Camera__WorldToScreenPoint(UnityEngine_Camera_o *this, UnityEngine_Vector3_o position, int32_t eye, const MethodInfo *method)
il2cpp:0000000001284630                UnityEngine_Camera$$WorldToScreenPoint proc near
il2cpp:0000000001284630                                                        ; CODE XREF: SnowPatchManager$$LateUpdate+1776↓p
il2cpp:0000000001284630                                                        ; SnowPatchManager$$LateUpdate+1EAF↓p ...
il2cpp:0000000001284630
il2cpp:0000000001284630                var_18          = qword ptr -18h
il2cpp:0000000001284630                var_10          = dword ptr -10h
il2cpp:0000000001284630                arg_0           = qword ptr  8
il2cpp:0000000001284630                arg_8           = qword ptr  10h
il2cpp:0000000001284630                arg_10          = qword ptr  18h
il2cpp:0000000001284630
il2cpp:0000000001284630 48 89 5C 24 08                 mov     [rsp+arg_0], rbx
il2cpp:0000000001284635 48 89 6C 24 10                 mov     [rsp+arg_8], rbp
il2cpp:000000000128463A 48 89 74 24 18                 mov     [rsp+arg_10], rsi
il2cpp:000000000128463F 57                             push    rdi
il2cpp:0000000001284640 48 83 EC 30                    sub     rsp, 30h
il2cpp:0000000001284644 33 C0                          xor     eax, eax
il2cpp:0000000001284646 41 8B F9                       mov     edi, r9d
il2cpp:0000000001284649 48 89 44 24 20                 mov     [rsp+38h+var_18], rax
il2cpp:000000000128464E 49 8B F0                       mov     rsi, r8
il2cpp:0000000001284651 89 44 24 28                    mov     [rsp+38h+var_10], eax
il2cpp:0000000001284655 48 8B EA                       mov     rbp, rdx
il2cpp:0000000001284658 48 8B 05 E9 16                 mov     rax, cs:qword_4675D48
il2cpp:0000000001284658 3F 03
...
```

# Component* Component::get_gameObject():
40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 89 05 ? ? ? ? 48 8B CB 48 83 C4 ? 5B 48 FF E0 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? ? ? 40 57 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 48 8B D9 33 FF 40 38 3D ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 90 ? ? ? ? 48 8B 05 ? ? ? ? 8B 8C 02 ? ? ? ? 48 89 7C 24 ? 48 89 7C 24 ? 48 89 7C 24 ? 4C 8D 44 24 ? 8B 94 02 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8D 53
```asm
il2cpp:00000000010D6610                ; UnityEngine_GameObject_o *NodeCanvas_Framework_Blackboard__get_propertiesBindTarget(NodeCanvas_Framework_Blackboard_o *this, const MethodInfo *method)
il2cpp:00000000010D6610                NodeCanvas_Framework_Blackboard$$get_propertiesBindTarget proc near
il2cpp:00000000010D6610                                                        ; CODE XREF: EasyRoads3Dv3_OCOCOOQQCD$$OQCDOQOCDC:loc_47E54E↑p
il2cpp:00000000010D6610                                                        ; EasyRoads3Dv3_OCOCOOQQCD$$OQCDOQOCDC+43B↑p ...
il2cpp:00000000010D6610 40 53                          push    rbx
il2cpp:00000000010D6612 48 83 EC 20                    sub     rsp, 20h
il2cpp:00000000010D6616 48 8B 05 F3 F3                 mov     rax, cs:qword_4675A10
il2cpp:00000000010D6616 59 03
il2cpp:00000000010D661D 48 8B D9                       mov     rbx, rcx
il2cpp:00000000010D6620 48 85 C0                       test    rax, rax
il2cpp:00000000010D6623 75 18                          jnz     short loc_10D663D
il2cpp:00000000010D6625 48 8D 0D 64 26                 lea     rcx, aUnityengineCom ; "UnityEngine.Component::get_gameObject()"
il2cpp:00000000010D6625 28 02
il2cpp:00000000010D662C E8 FF 44 FD FE                 call    il2cpp_resolve_icall_0
il2cpp:00000000010D6631 48 85 C0                       test    rax, rax
il2cpp:00000000010D6634 74 12                          jz      short loc_10D6648
il2cpp:00000000010D6636 48 89 05 D3 F3                 mov     cs:qword_4675A10, rax
...
```




# Transform* GameObject::get_transform():
40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 89 05 ? ? ? ? 48 8B CB 48 83 C4 ? 5B 48 FF E0 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? ? ? 48 89 5C 24 ? 57 48 83 EC ? 48 8B 59
```asm
il2cpp:0000000000775370                ; UnityEngine_Transform_o *NodeCanvas_DialogueTrees_DialogueTreeController__NodeCanvas_DialogueTrees_IDialogueActor_get_transform(NodeCanvas_DialogueTrees_DialogueTreeController_o *this, const MethodInfo *method)
il2cpp:0000000000775370                NodeCanvas_DialogueTrees_DialogueTreeController$$NodeCanvas_DialogueTrees_IDialogueActor_get_transform proc near
il2cpp:0000000000775370                                                        ; CODE XREF: EasyRoads3Dv3_OCQCDQCQOQExt$$ODDDQODDQQ+5D4↑p
il2cpp:0000000000775370                                                        ; EasyRoads3Dv3_OCQCDQCQOQExt$$ODDDQODDQQ+672↑p ...
il2cpp:0000000000775370 40 53                          push    rbx
il2cpp:0000000000775372 48 83 EC 20                    sub     rsp, 20h
il2cpp:0000000000775376 48 8B 05 6B 08                 mov     rax, cs:qword_4675BE8
il2cpp:0000000000775376 F0 03
il2cpp:000000000077537D 48 8B D9                       mov     rbx, rcx
il2cpp:0000000000775380 48 85 C0                       test    rax, rax
il2cpp:0000000000775383 75 18                          jnz     short loc_77539D
...
```

# bool GameObject::get_activeInHierarchy():
40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 89 05 ? ? ? ? 48 8B CB 48 83 C4 ? 5B 48 FF E0 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? ? ? 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 0F B6 DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 89 05 ? ? ? ? 0F B6 D3 48 8B CF 48 8B 5C 24 ? 48 83 C4 ? 5F 48 FF E0 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? ? ? ? 40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 89 05 ? ? ? ? 48 8B CB 48 83 C4 ? 5B 48 FF E0 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? ? ? 48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 0F B6 DA 48 8B F9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 89 05 ? ? ? ? 0F B6 D3 48 8B CF 48 8B 5C 24 ? 48 83 C4 ? 5F 48 FF E0 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? ? ? ? 40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 89 05 ? ? ? ? 48 8B CB 48 83 C4 ? 5B 48 FF E0 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? ? ? 40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B D9 48 85 C0 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 89 05 ? ? ? ? 48 8B CB 48 83 C4 ? 5B 48 FF E0 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? ? ? 48 89 5C 24
```asm
il2cpp:0000000001298A90                ; bool UnityEngine_GameObject__get_activeInHierarchy(UnityEngine_GameObject_o *this, const MethodInfo *method)
il2cpp:0000000001298A90                UnityEngine_GameObject$$get_activeInHierarchy proc near
il2cpp:0000000001298A90                                                        ; CODE XREF: UnityEngine_UI_LayoutGroup$$CalculateLayoutInputHorizontal+1D8↑p
il2cpp:0000000001298A90                                                        ; UnityStandardAssets_ImageEffects_CameraMotionBlur$$OnRenderImage+4BB↑p ...
il2cpp:0000000001298A90 40 53                          push    rbx
il2cpp:0000000001298A92 48 83 EC 20                    sub     rsp, 20h
il2cpp:0000000001298A96 48 8B 05 BB D5                 mov     rax, cs:qword_4676058
il2cpp:0000000001298A96 3D 03
il2cpp:0000000001298A9D 48 8B D9                       mov     rbx, rcx
il2cpp:0000000001298AA0 48 85 C0                       test    rax, rax
il2cpp:0000000001298AA3 75 18                          jnz     short loc_1298ABD
il2cpp:0000000001298AA5 48 8D 0D F4 18                 lea     rcx, aUnityengineGam_0 ; "UnityEngine.GameObject::get_activeInHie"...
il2cpp:0000000001298AA5 0C 02
il2cpp:0000000001298AAC E8 7F 20 E1 FE                 call    il2cpp_resolve_icall_0
il2cpp:0000000001298AB1 48 85 C0                       test    rax, rax
il2cpp:0000000001298AB4 74 12                          jz      short loc_1298AC8
il2cpp:0000000001298AB6 48 89 05 9B D5                 mov     cs:qword_4676058, rax
il2cpp:0000000001298AB6 3D 03
```

# string GearItem::get_m_DisplayName():
40 53 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 48 8B D9 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 90 ? ? ? ? 48 8B 05 ? ? ? ? 8B 8C 02 ? ? ? ? 45 33 C0 4C 89 44 24 ? 4C 89 44 24 ? 4C 89 44 24 ? 4C 8D 44 24 ? 8B 94 02 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 80 7B ? ? 75 ? 80 7B ? ? 75
```asm
il2cpp:0000000001CCDE20                ; System_String_o *GearItem__get_m_DisplayName(GearItem_o *this, const MethodInfo *method)
il2cpp:0000000001CCDE20                GearItem$$get_m_DisplayName proc near   ; CODE XREF: PlayerManager$$ExitInspectGearMode+77F↑p
il2cpp:0000000001CCDE20                                                        ; PlayerManager$$GetInteractiveObjectDisplayText+700↑p ...
il2cpp:0000000001CCDE20
il2cpp:0000000001CCDE20                var_28          = qword ptr -28h
il2cpp:0000000001CCDE20                var_20          = qword ptr -20h
il2cpp:0000000001CCDE20                var_18          = qword ptr -18h
il2cpp:0000000001CCDE20                var_10          = qword ptr -10h
il2cpp:0000000001CCDE20
il2cpp:0000000001CCDE20                ; __unwind { // __CxxFrameHandler3
il2cpp:0000000001CCDE20 40 53                          push    rbx
il2cpp:0000000001CCDE22 48 83 EC 40                    sub     rsp, 40h
il2cpp:0000000001CCDE26 48 C7 44 24 20                 mov     [rsp+48h+var_28], 0FFFFFFFFFFFFFFFEh
il2cpp:0000000001CCDE26 FE FF FF FF
il2cpp:0000000001CCDE2F 48 8B D9                       mov     rbx, rcx
il2cpp:0000000001CCDE32 80 3D 59 6B 9B                 cmp     cs:byte_4684992, 0
il2cpp:0000000001CCDE32 02 00
il2cpp:0000000001CCDE39 75 50                          jnz     short loc_1CCDE8B
il2cpp:0000000001CCDE3B 48 8B 05 7E 00                 mov     rax, cs:qword_466DEC0
il2cpp:0000000001CCDE3B 9A 02
il2cpp:0000000001CCDE42 48 63 90 B8 00                 movsxd  rdx, dword ptr [rax+0B8h]
il2cpp:0000000001CCDE42 00 00
il2cpp:0000000001CCDE49 48 8B 05 48 00                 mov     rax, cs:qword_466DE98
il2cpp:0000000001CCDE49 9A 02
il2cpp:0000000001CCDE50 8B 8C 02 B0 07                 mov     ecx, [rdx+rax+407B0h]
il2cpp:0000000001CCDE50 04 00
il2cpp:0000000001CCDE57 45 33 C0                       xor     r8d, r8d
il2cpp:0000000001CCDE5A 4C 89 44 24 28                 mov     [rsp+48h+var_20], r8
il2cpp:0000000001CCDE5F 4C 89 44 24 30                 mov     [rsp+48h+var_18], r8
il2cpp:0000000001CCDE64 4C 89 44 24 38                 mov     [rsp+48h+var_10], r8
il2cpp:0000000001CCDE69 4C 8D 44 24 28                 lea     r8, [rsp+48h+var_20]
il2cpp:0000000001CCDE6E 8B 94 02 B4 07                 mov     edx, [rdx+rax+407B4h]
il2cpp:0000000001CCDE6E 04 00
il2cpp:0000000001CCDE75
il2cpp:0000000001CCDE75                loc_1CCDE75:                            ; DATA XREF: .rdata:stru_40C27F8↓o
il2cpp:0000000001CCDE75                ;   try {
il2cpp:0000000001CCDE75 E8 F6 13 3E FE                 call    sub_AF270
il2cpp:0000000001CCDE7A 90                             nop
il2cpp:0000000001CCDE7B 33 C9                          xor     ecx, ecx        ; Block
il2cpp:0000000001CCDE7B                ;   } // starts at 1CCDE75
il2cpp:0000000001CCDE7D
il2cpp:0000000001CCDE7D                loc_1CCDE7D:                            ; DATA XREF: .rdata:00000000040C2800↓o
il2cpp:0000000001CCDE7D                ;   try {
il2cpp:0000000001CCDE7D FF 15 C5 A2 69                 call    cs:off_4368148
il2cpp:0000000001CCDE7D 02
il2cpp:0000000001CCDE83 90                             nop
il2cpp:0000000001CCDE84 C6 05 07 6B 9B                 mov     cs:byte_4684992, 1
il2cpp:0000000001CCDE84 02 01
il2cpp:0000000001CCDE8B
il2cpp:0000000001CCDE8B                loc_1CCDE8B:                            ; CODE XREF: GearItem$$get_m_DisplayName+19↑j
il2cpp:0000000001CCDE8B 80 7B 1C 00                    cmp     byte ptr [rbx+1Ch], 0
il2cpp:0000000001CCDE8F 75 1E                          jnz     short loc_1CCDEAF
il2cpp:0000000001CCDE91 80 7B 1F 00                    cmp     byte ptr [rbx+1Fh], 0
il2cpp:0000000001CCDE95 75 18                          jnz     short loc_1CCDEAF
il2cpp:0000000001CCDE97 48 8B 8B F8 02                 mov     rcx, [rbx+2F8h] ; this
il2cpp:0000000001CCDE97 00 00
il2cpp:0000000001CCDE9E 48 85 C9                       test    rcx, rcx
il2cpp:0000000001CCDEA1 74 47                          jz      short loc_1CCDEEA
il2cpp:0000000001CCDEA3 33 D2                          xor     edx, edx        ; method
il2cpp:0000000001CCDEA5 48 83 C4 40                    add     rsp, 40h
il2cpp:0000000001CCDEA9 5B                             pop     rbx
il2cpp:0000000001CCDEAA E9 61 F1 D3 FF                 jmp     LocalizedString$$Text
il2cpp:0000000001CCDEAF                ; ---------------------------------------------------------------------------
il2cpp:0000000001CCDEAF
il2cpp:0000000001CCDEAF                loc_1CCDEAF:                            ; CODE XREF: GearItem$$get_m_DisplayName+6F↑j
il2cpp:0000000001CCDEAF                                                        ; GearItem$$get_m_DisplayName+75↑j
il2cpp:0000000001CCDEAF 48 8B 0D 6A A5                 mov     rcx, cs:GameManager_TypeInfo ; GameManager_TypeInfo
il2cpp:0000000001CCDEAF A1 02
il2cpp:0000000001CCDEB6 F6 81 2F 01 00                 test    byte ptr [rcx+12Fh], 2
il2cpp:0000000001CCDEB6 00 02
il2cpp:0000000001CCDEBD 74 0E                          jz      short loc_1CCDECD
il2cpp:0000000001CCDEBF 83 B9 E0 00 00                 cmp     dword ptr [rcx+0E0h], 0
il2cpp:0000000001CCDEBF 00 00
il2cpp:0000000001CCDEC6 75 05                          jnz     short loc_1CCDECD
il2cpp:0000000001CCDEC6                ;   } // starts at 1CCDE7D
il2cpp:0000000001CCDEC8
il2cpp:0000000001CCDEC8                loc_1CCDEC8:                            ; DATA XREF: .rdata:00000000040C2808↓o
il2cpp:0000000001CCDEC8 E8 53 AF 3E FE                 call    il2cpp_runtime_class_init_0
il2cpp:0000000001CCDECD
il2cpp:0000000001CCDECD                loc_1CCDECD:                            ; CODE XREF: GearItem$$get_m_DisplayName+9D↑j
il2cpp:0000000001CCDECD                                                        ; GearItem$$get_m_DisplayName+A6↑j
il2cpp:0000000001CCDECD E8 4E E2 8F FF                 call    sub_15CC120
il2cpp:0000000001CCDED2 48 85 C0                       test    rax, rax
il2cpp:0000000001CCDED5 74 19                          jz      short loc_1CCDEF0
il2cpp:0000000001CCDED7 45 33 C0                       xor     r8d, r8d        ; method
il2cpp:0000000001CCDEDA 48 8B D3                       mov     rdx, rbx        ; gearItem
il2cpp:0000000001CCDEDD 48 8B C8                       mov     rcx, rax        ; this
il2cpp:0000000001CCDEE0 48 83 C4 40                    add     rsp, 40h
il2cpp:0000000001CCDEE4 5B                             pop     rbx
il2cpp:0000000001CCDEE5 E9 56 9C 90 FF                 jmp     ConditionTableManager$$GetDisplayNameWithCondition
il2cpp:0000000001CCDEEA                ; ---------------------------------------------------------------------------
il2cpp:0000000001CCDEEA
il2cpp:0000000001CCDEEA                loc_1CCDEEA:                            ; CODE XREF: GearItem$$get_m_DisplayName+81↑j
il2cpp:0000000001CCDEEA E8 51 9D 42 FE                 call    sub_F7C40
il2cpp:0000000001CCDEEA                ; ---------------------------------------------------------------------------
il2cpp:0000000001CCDEEF CC                             align 10h
il2cpp:0000000001CCDEF0
il2cpp:0000000001CCDEF0                loc_1CCDEF0:                            ; CODE XREF: GearItem$$get_m_DisplayName+B5↑j
il2cpp:0000000001CCDEF0 E8 4B 9D 42 FE                 call    sub_F7C40
il2cpp:0000000001CCDEF0                ; ---------------------------------------------------------------------------
il2cpp:0000000001CCDEF5 CC                             db 0CCh
il2cpp:0000000001CCDEF5                ; } // starts at 1CCDE20
il2cpp:0000000001CCDEF6                algn_1CCDEF6:                           ; DATA XREF: .pdata:0000000004A88254↓o
il2cpp:0000000001CCDEF6 CC CC CC CC CC                 align 20h
il2cpp:0000000001CCDEF6 CC CC CC CC CC GearItem$$get_m_DisplayName endp
il2cpp:0000000001CCDEF6
```


# void BaseAiManager::Add(BaseAi* bai):
4C 8B DC 57 48 83 EC ? 49 C7 43 ? ? ? ? ? 49 89 5B ? 49 89 73 ? 48 8B F9 33 F6 40 38 35 ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 90 ? ? ? ? 48 8B 05 ? ? ? ? 8B 8C 02 ? ? ? ? 49 89 73 ? 49 89 73 ? 49 89 73 ? 4D 8D 43 ? 8B 94 02 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 48 ? 48 85 C9 0F 84 ? ? ? ? 4C 8B 05
```asm
il2cpp:0000000001995470                ; void BaseAiManager__Add(BaseAi_o *bai, const MethodInfo *method)
il2cpp:0000000001995470                BaseAiManager$$Add proc near            ; CODE XREF: BaseAi$$Start+156↑p
il2cpp:0000000001995470                                                        ; DATA XREF: .data:00000000044FE7D0↓o ...
il2cpp:0000000001995470
il2cpp:0000000001995470                var_20          = qword ptr -20h
il2cpp:0000000001995470                var_18          = qword ptr -18h
il2cpp:0000000001995470                var_10          = qword ptr -10h
il2cpp:0000000001995470                arg_0           = qword ptr  8
il2cpp:0000000001995470                arg_8           = qword ptr  10h
il2cpp:0000000001995470
il2cpp:0000000001995470                ; __unwind { // __CxxFrameHandler3
il2cpp:0000000001995470 4C 8B DC                       mov     r11, rsp
il2cpp:0000000001995473 57                             push    rdi
il2cpp:0000000001995474 48 83 EC 40                    sub     rsp, 40h
il2cpp:0000000001995478 49 C7 43 D8 FE                 mov     qword ptr [r11-28h], 0FFFFFFFFFFFFFFFEh
il2cpp:0000000001995478 FF FF FF
il2cpp:0000000001995480 49 89 5B 08                    mov     [r11+8], rbx
il2cpp:0000000001995484 49 89 73 10                    mov     [r11+10h], rsi
il2cpp:0000000001995488 48 8B F9                       mov     rdi, rcx
il2cpp:000000000199548B 33 F6                          xor     esi, esi
il2cpp:000000000199548D 40 38 35 74 86                 cmp     cs:byte_467DB08, sil
il2cpp:000000000199548D CE 02
```

# void BaseAiManager::Remove(BaseAi* bai)
40 57 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 48 8B D9 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 90 ? ? ? ? 48 8B 05 ? ? ? ? 8B 8C 02 ? ? ? ? 45 33 C0 4C 89 44 24 ? 4C 89 44 24 ? 4C 89 44 24 ? 4C 8D 44 24 ? 8B 94 02 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 48 ? 48 85 C9 0F 84 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8B D3 E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 81 ? ? ? ? 4C 8B 88 ? ? ? ? 4D 85 C9 74 ? 4C 8B 05 ? ? ? ? 48 8B D3 49 8B C9 E8 ? ? ? ? 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 81 ? ? ? ? 48 8B 48 ? 48 85 C9 0F 84 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8B D3 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 79 ? 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 33 D2
```asm
il2cpp:0000000001995730                ; void BaseAiManager__Remove(BaseAi_o *bai, const MethodInfo *method)
il2cpp:0000000001995730                BaseAiManager$$Remove proc near         ; CODE XREF: BaseAi$$OnDestroy+240↑j
il2cpp:0000000001995730                                                        ; DATA XREF: .data:00000000044FE7D8↓o ...
il2cpp:0000000001995730
il2cpp:0000000001995730                var_28          = qword ptr -28h
il2cpp:0000000001995730                var_20          = qword ptr -20h
il2cpp:0000000001995730                var_18          = qword ptr -18h
il2cpp:0000000001995730                var_10          = qword ptr -10h
il2cpp:0000000001995730                arg_0           = qword ptr  8
il2cpp:0000000001995730
il2cpp:0000000001995730                ; __unwind { // __CxxFrameHandler3
il2cpp:0000000001995730 40 57                          push    rdi
il2cpp:0000000001995732 48 83 EC 40                    sub     rsp, 40h
il2cpp:0000000001995736 48 C7 44 24 20                 mov     [rsp+48h+var_28], 0FFFFFFFFFFFFFFFEh
il2cpp:0000000001995736 FE FF FF FF
il2cpp:000000000199573F 48 89 5C 24 50                 mov     [rsp+48h+arg_0], rbx
il2cpp:0000000001995744 48 8B D9                       mov     rbx, rcx
il2cpp:0000000001995747 80 3D 1C 84 CE                 cmp     cs:byte_467DB6A, 0
il2cpp:0000000001995747 02 00
```

# void GearManager::Add(GearItem* gi)
4C 8B DC 57 48 83 EC ? 49 C7 43 ? ? ? ? ? 49 89 5B ? 49 89 73 ? 48 8B D9 33 F6 40 38 35 ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 90 ? ? ? ? 48 8B 05 ? ? ? ? 8B 8C 02 ? ? ? ? 49 89 73 ? 49 89 73 ? 49 89 73 ? 4D 8D 43 ? 8B 94 02 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? F6 80 ? ? ? ? ? 74 ? 83 B8 ? ? ? ? ? 75 ? 48 8B C8 E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? ? ? ? 48 85 C9
```asm
il2cpp:0000000001CE5A60                ; void GearManager__Add(GearItem_o *gi, const MethodInfo *method)
il2cpp:0000000001CE5A60                GearManager$$Add proc near              ; CODE XREF: GearItem$$Awake+17C4↑p
il2cpp:0000000001CE5A60                                                        ; DATA XREF: .data:0000000004500C38↓o ...
il2cpp:0000000001CE5A60
il2cpp:0000000001CE5A60                var_20          = qword ptr -20h
il2cpp:0000000001CE5A60                var_18          = qword ptr -18h
il2cpp:0000000001CE5A60                var_10          = qword ptr -10h
il2cpp:0000000001CE5A60                arg_0           = qword ptr  8
il2cpp:0000000001CE5A60                arg_8           = qword ptr  10h
il2cpp:0000000001CE5A60
il2cpp:0000000001CE5A60                ; __unwind { // __CxxFrameHandler3
il2cpp:0000000001CE5A60 4C 8B DC                       mov     r11, rsp
il2cpp:0000000001CE5A63 57                             push    rdi
il2cpp:0000000001CE5A64 48 83 EC 40                    sub     rsp, 40h
il2cpp:0000000001CE5A68 49 C7 43 D8 FE                 mov     qword ptr [r11-28h], 0FFFFFFFFFFFFFFFEh
il2cpp:0000000001CE5A68 FF FF FF
il2cpp:0000000001CE5A70 49 89 5B 08                    mov     [r11+8], rbx
il2cpp:0000000001CE5A74 49 89 73 10                    mov     [r11+10h], rsi
il2cpp:0000000001CE5A78 48 8B D9                       mov     rbx, rcx
il2cpp:0000000001CE5A7B 33 F6                          xor     esi, esi
il2cpp:0000000001CE5A7D 40 38 35 7A EF                 cmp     cs:byte_46849FE, sil
il2cpp:0000000001CE5A7D 99 02
...
```

# void GearManager::Remove(GearItem* gi)
40 53 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 48 8B D9 80 3D ? ? ? ? ? 75 ? 48 8B 05 ? ? ? ? 48 63 90 ? ? ? ? 48 8B 05 ? ? ? ? 8B 8C 02 ? ? ? ? 45 33 C0 4C 89 44 24 ? 4C 89 44 24 ? 4C 89 44 24 ? 4C 8D 44 24 ? 8B 94 02 ? ? ? ? E8 ? ? ? ? 90 33 C9 FF 15 ? ? ? ? 90 C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 74 ? 83 B9 ? ? ? ? ? 75 ? E8 ? ? ? ? 33 D2 48 8B CB E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 81
```asm
il2cpp:0000000001CE6B00                ; void GearManager__Remove(GearItem_o *gi, const MethodInfo *method)
il2cpp:0000000001CE6B00                GearManager$$Remove proc near           ; CODE XREF: GearItem$$OnDestroy+8E↑p
il2cpp:0000000001CE6B00                                                        ; GearManager$$DestroyGearObject+497↑p
il2cpp:0000000001CE6B00                                                        ; DATA XREF: ...
il2cpp:0000000001CE6B00
il2cpp:0000000001CE6B00                var_28          = qword ptr -28h
il2cpp:0000000001CE6B00                var_20          = qword ptr -20h
il2cpp:0000000001CE6B00                var_18          = qword ptr -18h
il2cpp:0000000001CE6B00                var_10          = qword ptr -10h
il2cpp:0000000001CE6B00
il2cpp:0000000001CE6B00                ; __unwind { // __CxxFrameHandler3
il2cpp:0000000001CE6B00 40 53                          push    rbx
il2cpp:0000000001CE6B02 48 83 EC 40                    sub     rsp, 40h
il2cpp:0000000001CE6B06 48 C7 44 24 20                 mov     [rsp+48h+var_28], 0FFFFFFFFFFFFFFFEh
il2cpp:0000000001CE6B06 FE FF FF FF
il2cpp:0000000001CE6B0F 48 8B D9                       mov     rbx, rcx
il2cpp:0000000001CE6B12 80 3D A7 DE 99                 cmp     cs:byte_46849C0, 0
il2cpp:0000000001CE6B12 02 00
...
```