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
    DWORD dwFlags = D3DXSHADER_DEBUG; //|D3DXSHADER_SKIPOPTIMIZATION;//|D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT|D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT|D3DXSHADER_SKIPOPTIMIZATION;
#else
    DWORD dwFlags = D3DXSHADER_SKIPVALIDATION;
#endif
    string effect_file_name;
    if ( GgafDx9God::_ps_v >= D3DPS_VERSION(3, 0)) {
        effect_file_name = CFG_PROPERTY(DIR_EFFECT) + "3_0_" + string(prm_effect_name) + ".fxo";
    } else if ( GgafDx9God::_ps_v >= D3DPS_VERSION(2, 0)) {
        effect_file_name = CFG_PROPERTY(DIR_EFFECT) + "2_0_" + string(prm_effect_name) + ".fxo";
    } else {
        effect_file_name = CFG_PROPERTY(DIR_EFFECT) + string(prm_effect_name) + ".fx";
    }
    HRESULT hr;
    if ( GgafDx9God::_ps_v >= D3DPS_VERSION(3, 0)) {
        hr = D3DXCreateEffectFromFile(
                 GgafDx9God::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice
                 effect_file_name.c_str(),  // [in] LPCTSTR pSrcFile
                 GgafDx9God::_aD3DXMacro_Defines, // [in] CONST D3DXMACRO* pDefines
                 0,                         // [in] LPD3DXINCLUDE pInclude
                 dwFlags,                   // [in] DWORD Flags
                 0,                         // [in] LPD3DXEFFECTPOOL pPool
                 &_pID3DXEffect,         // [out] LPD3DXEFFECT* ppEffect
                 &pError                    // [out] LPD3DXBUFFER *ppCompilationxErrors
            );

    } else {
        hr = D3DXCreateEffectFromFile(
                 GgafDx9God::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice
                 effect_file_name.c_str(),  // [in] LPCTSTR pSrcFile
                 0,                         // [in] CONST D3DXMACRO* pDefines
                 0,                         // [in] LPD3DXINCLUDE pInclude
                 dwFlags,                   // [in] DWORD Flags
                 0,                         // [in] LPD3DXEFFECTPOOL pPool
                 &_pID3DXEffect,         // [out] LPD3DXEFFECT* ppEffect
                 &pError                    // [out] LPD3DXBUFFER *ppCompilationxErrors
            );

    }

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

