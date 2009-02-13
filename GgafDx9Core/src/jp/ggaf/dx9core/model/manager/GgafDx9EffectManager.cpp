#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9EffectManager::GgafDx9EffectManager(const char* prm_manager_name) :
    GgafResourceManager<ID3DXEffect> (prm_manager_name) {
}

ID3DXEffect* GgafDx9EffectManager::processCreateResource(char* prm_idstr) {
    string effect_file_name = GGAFDX9_PROPERTY(DIR_EFFECT) + string(prm_idstr) + ".fx";
    _TRACE_("effect_file_name="<<effect_file_name);
    ID3DXEffect* pID3DXEffect_New;
    ID3DXBuffer* pError;
#ifdef OREDEBUG
    DWORD dwFlags = D3DXSHADER_DEBUG;
#else
    DWORD dwFlags = D3DXSHADER_SKIPVALIDATION;
#endif
    HRESULT hr = D3DXCreateEffectFromFile(
                     GgafDx9God::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice
                     effect_file_name.c_str(),  // [in] LPCTSTR pSrcFile
                     0,                         // [in] CONST D3DXMACRO* pDefines
                     0,                         // [in] LPD3DXINCLUDE pInclude
                     dwFlags,                   // [in] DWORD Flags
                     0,                         // [in] LPD3DXEFFECTPOOL pPool
                     &pID3DXEffect_New,         // [out] LPD3DXEFFECT* ppEffect
                     &pError                    // [out] LPD3DXBUFFER *ppCompilationxErrors
                );
    if (hr != D3D_OK) {
        if ( pError ) {
            throwGgafDx9CriticalException("GgafDx9EffectManager::processCreateResource ["<<prm_idstr<<"]\n"<<(const char*)(pError->GetBufferPointer()), hr);
        } else {
            throwGgafDx9CriticalException("GgafDx9EffectManager::processCreateResource ["<<prm_idstr<<"]\n何かのエラー", hr);
        }
    }
    _TRACE_(" GgafDx9EffectManager::processCreateResource "<<prm_idstr<<" のエフェクトを生成しました。");
    pID3DXEffect_New->SetMatrix( "g_viewMat", &GgafDx9God::_vMatrixView );
    pID3DXEffect_New->SetMatrix( "g_projMat", &GgafDx9God::_vMatrixProjrction );
    return pID3DXEffect_New;
}

GgafResourceConnection<ID3DXEffect>* GgafDx9EffectManager::processCreateConnection(char* prm_idstr,
                                                                       ID3DXEffect* prm_pResource) {
    _TRACE_(" GgafDx9EffectManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDx9EffectConnection* p = NEW GgafDx9EffectConnection(prm_idstr, prm_pResource);
    _TRACE_(" GgafDx9EffectManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return p;
}

