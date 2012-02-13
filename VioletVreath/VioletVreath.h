#pragma once

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER

#else
    //無理やりリンクエラー回避 for GCC
    //VC では不要。良い方法がないものか・・・
    uintptr_t __security_cookie;
    void __declspec(naked) __fastcall __security_check_cookie(DWORD_PTR cookie) {}
#endif

#ifdef  __cplusplus
};
#endif



