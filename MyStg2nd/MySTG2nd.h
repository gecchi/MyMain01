#pragma once

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER

#else
    //������胊���N�G���[��� for GCC
    //VC �ł͕s�v�B�ǂ����@���Ȃ����̂��E�E�E
    uintptr_t __security_cookie;
    void __declspec(naked) __fastcall __security_check_cookie(DWORD_PTR cookie) {}
#endif

#ifdef  __cplusplus
};
#endif



