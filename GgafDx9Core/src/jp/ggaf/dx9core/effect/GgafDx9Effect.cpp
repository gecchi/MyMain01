#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9Effect::GgafDx9Effect(char* prm_effect_name) : GgafObject() {
    TRACE("GgafDx9Effect::GgafDx9Effect(" << prm_effect_name << ")");
    _effect_name = NEW char[51];
    strcpy(_effect_name, prm_effect_name);

    ID3DXBuffer* pError;
#ifdef MY_DEBUG
    DWORD dwFlags = D3DXSHADER_DEBUG;
#else
    DWORD dwFlags = D3DXSHADER_SKIPVALIDATION;
#endif
    string effect_file_name = GGAFDX9_PROPERTY(DIR_EFFECT) + string(prm_effect_name) + ".fx";
    HRESULT hr = D3DXCreateEffectFromFile(
                     GgafDx9God::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice
                     effect_file_name.c_str(),  // [in] LPCTSTR pSrcFile
                     0,                         // [in] CONST D3DXMACRO* pDefines
                     0,                         // [in] LPD3DXINCLUDE pInclude
                     dwFlags,                   // [in] DWORD Flags
                     0,                         // [in] LPD3DXEFFECTPOOL pPool
                     &_pID3DXEffect,         // [out] LPD3DXEFFECT* ppEffect
                     &pError                    // [out] LPD3DXBUFFER *ppCompilationxErrors
                );
    if (hr != D3D_OK && pError == NULL) {
        throwGgafCriticalException("GgafDx9Effect::GgafDx9Effect "<<effect_file_name<<" が存在しないのではないだろうか・・・");
    }
    checkDxException(hr, D3D_OK, "GgafDx9Effect::GgafDx9Effect ["<<effect_file_name<<"]\n"<<(const char*)(pError->GetBufferPointer()));
    TRACE3(" GgafDx9Effect::GgafDx9Effect "<<prm_effect_name<<" のエフェクトを生成しました。");

    _h_alpha_master = _pID3DXEffect->GetParameterByName( NULL, "g_alpha_master" ); //マスターα
}

GgafDx9Effect::~GgafDx9Effect() {
    TRACE3("GgafDx9Effect::~GgafDx9Effect() " << _effect_name << " start-->");
    DELETEARR_IMPOSSIBLE_NULL(_effect_name);
    RELEASE_IMPOSSIBLE_NULL(_pID3DXEffect);
}

