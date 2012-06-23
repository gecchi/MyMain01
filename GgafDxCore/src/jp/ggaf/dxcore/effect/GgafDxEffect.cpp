#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
D3DXMACRO GgafDxEffect::_aD3DXMacro_Defines[3] =
{
    { "VS_VERSION", "vs_3_0" },
    { "PS_VERSION", "ps_3_0" },
    { NULL, NULL }
};

GgafDxEffect::GgafDxEffect(char* prm_effect_name) : GgafObject() {
    TRACE4("GgafDxEffect::GgafDxEffect(" << prm_effect_name << ")");
    _effect_name = NEW char[51];
    strcpy(_effect_name, prm_effect_name);

    std::string effect_file_name;
    if (GGAF_PROPERTY(REALTIME_EFFECT_COMPILE)) {
        //fx ファイルからコンパイル
        effect_file_name = getEffectFileName(std::string(prm_effect_name) + ".fx");
    } else {
        //コンパイル済み fxo ファイルを読み込み
        if ( GgafDxGod::_ps_v >= D3DPS_VERSION(3, 0)) {
            effect_file_name = getEffectFileName("3_0_" + std::string(prm_effect_name) + ".fxo");
        } else {
            effect_file_name = getEffectFileName("2_0_" + std::string(prm_effect_name) + ".fxo");
        }
    }

    ID3DXBuffer* pError = NULL;
    HRESULT hr;
#ifdef MY_DEBUG
    DWORD dwFlags = D3DXSHADER_DEBUG; //|D3DXSHADER_SKIPOPTIMIZATION;//|D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT|D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT|D3DXSHADER_SKIPOPTIMIZATION;
    _begin = false;
#else
    DWORD dwFlags = D3DXSHADER_SKIPVALIDATION;
#endif
    if ( GgafDxGod::_ps_v >= D3DPS_VERSION(3, 0)) {
        //ピクセルシェーダーが 3.0 以上の場合
        hr = D3DXCreateEffectFromFile(
                 GgafDxGod::_pID3DDevice9,  // [in] LPDIRECT3DDEVICE9 pDevice
                 effect_file_name.c_str(),  // [in] LPCTSTR pSrcFile
                 _aD3DXMacro_Defines,       // [in] CONST D3DXMACRO* pDefines
                 0,                         // [in] LPD3DXINCLUDE pInclude
                 dwFlags,                   // [in] DWORD Flags
                 0,                         // [in] LPD3DXEFFECTPOOL pPool
                 &_pID3DXEffect,            // [out] LPD3DXEFFECT* ppEffect
                 &pError                    // [out] LPD3DXBUFFER *ppCompilationxErrors
            );
    } else {
        //ピクセルシェーダーが 3.0 未満の場合(2.0と想定する)
        hr = D3DXCreateEffectFromFile(
                 GgafDxGod::_pID3DDevice9,  // [in] LPDIRECT3DDEVICE9 pDevice
                 effect_file_name.c_str(),  // [in] LPCTSTR pSrcFile
                 0,                         // [in] CONST D3DXMACRO* pDefines
                 0,                         // [in] LPD3DXINCLUDE pInclude
                 dwFlags,                   // [in] DWORD Flags
                 0,                         // [in] LPD3DXEFFECTPOOL pPool
                 &_pID3DXEffect,            // [out] LPD3DXEFFECT* ppEffect
                 &pError                    // [out] LPD3DXBUFFER *ppCompilationxErrors
            );
    }
    if (hr != D3D_OK && pError == NULL) {
        throwGgafCriticalException("GgafDxEffect::GgafDxEffect "<<effect_file_name<<" が存在しないのではないだろうか・・・");
    }
    checkDxException(hr, D3D_OK, "GgafDxEffect::GgafDxEffect ["<<effect_file_name<<"]\n"<<(const char*)(pError->GetBufferPointer()));
    _TRACE_(" GgafDxEffect::GgafDxEffect "<<prm_effect_name<<" のエフェクトを生成しました。ADD:"<<this);
    _h_alpha_master = _pID3DXEffect->GetParameterByName( NULL, "g_alpha_master" ); //マスターα
}

std::string GgafDxEffect::getEffectFileName(std::string prm_file) {
    std::string effect_file = GGAF_PROPERTY(DIR_EFFECT[0]) + "/" + prm_file;
    UTIL::strReplace(effect_file, "//", "/");
    if (PathFileExists(effect_file.c_str()) ) {
        return effect_file;
    } else {
        effect_file = GGAF_PROPERTY(DIR_EFFECT[2]) + "/" + prm_file;
        UTIL::strReplace(effect_file, "//", "/");
        if (PathFileExists(effect_file.c_str()) ) {
            return effect_file; //ユーザースキンに存在すればそれを優先
        } else {
            effect_file = GGAF_PROPERTY(DIR_EFFECT[1]) + "/" + prm_file;
            UTIL::strReplace(effect_file, "//", "/");
            if (PathFileExists(effect_file.c_str()) ) {
                return effect_file;
            } else {
                throwGgafCriticalException("GgafDxEffect::getEffectFileName エフェクトファイルが見つかりません。effect_file="<<effect_file);
            }
        }
    }
}

GgafDxEffect::~GgafDxEffect() {
    TRACE4("GgafDxEffect::~GgafDxEffect("<<_effect_name<<") Adr:"<<this);
    _pID3DXEffect->EndPass();
    _pID3DXEffect->End();
    DELETEARR_IMPOSSIBLE_NULL(_effect_name);
    RELEASE_IMPOSSIBLE_NULL(_pID3DXEffect);
}

