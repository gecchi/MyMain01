#pragma once
//������胊���N�G���[����I
//�ǂ����@���Ȃ����̂��E�E�E
#ifdef  __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER

#else
    //for GCC
    uintptr_t __security_cookie;
    void __declspec(naked) __fastcall __security_check_cookie(DWORD_PTR cookie) {}
#endif
#ifdef  __cplusplus
};
#endif


