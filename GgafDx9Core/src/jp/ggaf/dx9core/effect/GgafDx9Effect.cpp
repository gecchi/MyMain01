#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9Effect::GgafDx9Effect(char* prm_effect_name) : GgafObject() {
    TRACE4("GgafDx9Effect::GgafDx9Effect(" << prm_effect_name << ")");
    _effect_name = NEW char[51];
    strcpy(_effect_name, prm_effect_name);

    ID3DXBuffer* pError = NULL;
#ifdef _DEBUG
    DWORD dwFlags = D3DXSHADER_DEBUG|D3DXFX_NOT_CLONEABLE;
#else
    DWORD dwFlags = D3DXSHADER_SKIPVALIDATION|D3DXFX_NOT_CLONEABLE;
#endif

//#ifdef _DEBUG
//    DWORD dwFlags = D3DXSHADER_PARTIALPRECISION|D3DXSHADER_DEBUG|D3DXSHADER_PREFER_FLOW_CONTROL|D3DXFX_NOT_CLONEABLE;
//#else
//    DWORD dwFlags = D3DXSHADER_SKIPVALIDATION|D3DXSHADER_PARTIALPRECISION|D3DXSHADER_PREFER_FLOW_CONTROL|D3DXFX_NOT_CLONEABLE;
//#endif

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
    _TRACE_(" GgafDx9Effect::GgafDx9Effect "<<prm_effect_name<<" のエフェクトを生成しました。ADD:"<<this);
    _h_alpha_master = _pID3DXEffect->GetParameterByName( NULL, "g_alpha_master" ); //マスターα
    _begin = false;
}

GgafDx9Effect::~GgafDx9Effect() {
    TRACE4("GgafDx9Effect::~GgafDx9Effect("<<_effect_name<<") Adr:"<<this);
    _pID3DXEffect->EndPass();
    _pID3DXEffect->End();
    DELETEARR_IMPOSSIBLE_NULL(_effect_name);
    RELEASE_IMPOSSIBLE_NULL(_pID3DXEffect);  //
}

