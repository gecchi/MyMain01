#include "jp/ggaf/dx/effect/Effect.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/Caretaker.h"
#include <Shlwapi.h>


using namespace GgafDx;

//D3DXMACRO Effect::_aD3DXMacro_Defines[3] =
//{
//    { "VS_VERSION", "vs_3_0" },
//    { "PS_VERSION", "ps_3_0" },
//    { nullptr, nullptr }
//};

Effect::Effect(const char* prm_effect_name) : GgafCore::Object() {
    _TRACE4_("Effect::Effect(" << prm_effect_name << ")");
    _obj_class = Obj_GgafDx_Effect;
    int len = strlen(prm_effect_name);
    _effect_name = NEW char[len+1];
    strcpy(_effect_name, prm_effect_name);

    std::string effect_file_name;
    if (CONFIG::REALTIME_EFFECT_COMPILE) {
        //fx ファイルからコンパイル
        effect_file_name = Effect::getEffectFileName(std::string(prm_effect_name) + ".fx");
    } else {
        //コンパイル済み fxo ファイルを読み込み
        effect_file_name = Effect::getEffectFileName("3_0_" + std::string(prm_effect_name) + ".fxo");
//        if ( Caretaker::_ps_v >= D3DPS_VERSION(3, 0)) {
//            effect_file_name = Effect::getEffectFileName("3_0_" + std::string(prm_effect_name) + ".fxo");
//        } else {
//            effect_file_name = Effect::getEffectFileName("2_0_" + std::string(prm_effect_name) + ".fxo");
//        }
    }

    ID3DXBuffer* pError = nullptr;
    HRESULT hr;
#ifdef MY_DEBUG
    DWORD dwFlags = D3DXSHADER_DEBUG; //|D3DXSHADER_SKIPOPTIMIZATION;//|D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT|D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT|D3DXSHADER_SKIPOPTIMIZATION;
    _begin = false;
#else
    DWORD dwFlags = D3DXSHADER_SKIPVALIDATION;
#endif

    hr = D3DXCreateEffectFromFile(
             pCARETAKER->_pID3DDevice9,  // [in] LPDIRECT3DDEVICE9 pDevice
             effect_file_name.c_str(),  // [in] LPCTSTR pSrcFile
             0,                         // [in] CONST D3DXMACRO* pDefines
             0,                         // [in] LPD3DXINCLUDE pInclude
             dwFlags,                   // [in] DWORD Flags
             0,                         // [in] LPD3DXEFFECTPOOL pPool
             &_pID3DXEffect,            // [out] LPD3DXEFFECT* ppEffect
             &pError                    // [out] LPD3DXBUFFER *ppCompilationxErrors
        );


//    if ( Caretaker::_ps_v >= D3DPS_VERSION(3, 0)) {
//        //ピクセルシェーダーが 3.0 以上の場合
//        hr = D3DXCreateEffectFromFile(
//                 pCARETAKER->_pID3DDevice9,  // [in] LPDIRECT3DDEVICE9 pDevice
//                 effect_file_name.c_str(),  // [in] LPCTSTR pSrcFile
//                 Effect::_aD3DXMacro_Defines, // [in] CONST D3DXMACRO* pDefines
//                 0,                         // [in] LPD3DXINCLUDE pInclude
//                 dwFlags,                   // [in] DWORD Flags
//                 0,                         // [in] LPD3DXEFFECTPOOL pPool
//                 &_pID3DXEffect,            // [out] LPD3DXEFFECT* ppEffect
//                 &pError                    // [out] LPD3DXBUFFER *ppCompilationxErrors
//            );
//    } else {
//        //ピクセルシェーダーが 3.0 未満の場合(2.0と想定する)
//        hr = D3DXCreateEffectFromFile(
//                 pCARETAKER->_pID3DDevice9,  // [in] LPDIRECT3DDEVICE9 pDevice
//                 effect_file_name.c_str(),  // [in] LPCTSTR pSrcFile
//                 0,                         // [in] CONST D3DXMACRO* pDefines
//                 0,                         // [in] LPD3DXINCLUDE pInclude
//                 dwFlags,                   // [in] DWORD Flags
//                 0,                         // [in] LPD3DXEFFECTPOOL pPool
//                 &_pID3DXEffect,            // [out] LPD3DXEFFECT* ppEffect
//                 &pError                    // [out] LPD3DXBUFFER *ppCompilationxErrors
//            );
//    }
    if (hr != D3D_OK && pError == nullptr) {
        throwCriticalException(effect_file_name<<" が存在しないのではないだろうか・・・");
    }
    checkDxException(hr, D3D_OK, "["<<effect_file_name<<"]\n"<<(const char*)(pError->GetBufferPointer()));
    _TRACE_(" Effect::Effect "<<prm_effect_name<<" のエフェクトを生成しました。ADD:"<<this);


    _h_alpha_master = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha_master" );
    _pID3DXEffect->SetFloat(_h_alpha_master, 1.0); //マスターαデフォルトは1.0
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
}

std::string Effect::getEffectFileName(std::string prm_file) {
    std::string effect_file = CONFIG::DIR_EFFECT[2] + "/" + prm_file;
    UTIL::strReplace(effect_file, "//", "/");
    if (PathFileExists(effect_file.c_str()) ) {
        return effect_file;
    } else {
        effect_file = CONFIG::DIR_EFFECT[1] + "/" + prm_file;
        UTIL::strReplace(effect_file, "//", "/");
        if (PathFileExists(effect_file.c_str()) ) {
            return effect_file; //ユーザースキンに存在すればそれを優先
        } else {
            effect_file = CONFIG::DIR_EFFECT[0] + "/" + prm_file;
            UTIL::strReplace(effect_file, "//", "/");
            if (PathFileExists(effect_file.c_str()) ) {
                return effect_file;
            } else {
                throwCriticalException("エフェクトファイルが見つかりません。effect_file="<<effect_file);
            }
        }
    }
}
void Effect::setAlphaMaster(float prm_scene_alpha) {
    _pID3DXEffect->SetFloat(_h_alpha_master, prm_scene_alpha);
}

Effect::~Effect() {
    _TRACE4_("Effect::~Effect("<<_effect_name<<") Adr:"<<this);
    _pID3DXEffect->EndPass();
    _pID3DXEffect->End();
    GGAF_DELETEARR(_effect_name);
    GGAF_RELEASE(_pID3DXEffect);
}

