#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectConnection.h"
#include "jp/ggaf/dxcore/effect/GgafDxD3DXAniMeshEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMeshEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMorphMeshEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMorphMeshEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteSetEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassSpriteEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardSetEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassBoardEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassPointSpriteEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteSetEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxEnclosedBoardEffect.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMeshEffect.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMeshSetEffect.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMorphMeshEffect.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxWorldBoundEffect.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxEffect* GgafDxEffectManager::_pEffect_active = nullptr;

GgafDxEffectManager::GgafDxEffectManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxEffect> (prm_manager_name) {
}

GgafDxEffect* GgafDxEffectManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, "/", 1);
    if (names.size() != 2) {
        throwGgafCriticalException("引数は、次の形式で与えてください。『エフェクトタイプ1文字  + \"/\" + fxファイル名(拡張子 .fx を除いたもの)』\n"<<
                "実際の引数は、prm_idstr="<<prm_idstr);
    }
    char effect_type = (names[0])[0];
    const char* effect_name = names[1].c_str();
    GgafDxEffect* pResourceEffect;
    switch (effect_type) {
        case 'D':
        case 'd':
        case 'X':
            pResourceEffect = NEW GgafDxMeshEffect(effect_name);
            break;
        case 'x':
            pResourceEffect = NEW GgafDxMeshSetEffect(effect_name);
            break;
        case 't':
            pResourceEffect = NEW GgafDxMassMeshEffect(effect_name);
            break;
        case 'G':
            pResourceEffect = NEW GgafDxCubeMapMeshEffect(effect_name);
            break;
        case 'g':
            pResourceEffect = NEW GgafDxCubeMapMeshSetEffect(effect_name);
            break;
        case 'A':
            pResourceEffect = NEW GgafDxD3DXAniMeshEffect(effect_name);
            break;
        case 'M':
            pResourceEffect = NEW GgafDxMorphMeshEffect(effect_name);
            break;
        case 'm':
            pResourceEffect = NEW GgafDxMassMorphMeshEffect(effect_name);
            break;
        case 'H':
            pResourceEffect = NEW GgafDxCubeMapMorphMeshEffect(effect_name);
            break;
        case 'W':
            pResourceEffect = NEW GgafDxWorldBoundEffect(effect_name);
            break;
        case 'S':
            pResourceEffect = NEW GgafDxSpriteEffect(effect_name);
            break;
        case 's':
            pResourceEffect = NEW GgafDxSpriteSetEffect(effect_name);
            break;
        case 'z':
            pResourceEffect = NEW GgafDxMassSpriteEffect(effect_name);
            break;
        case 'B':
            pResourceEffect = NEW GgafDxBoardEffect(effect_name);
            break;
        case 'b':
            pResourceEffect = NEW GgafDxBoardSetEffect(effect_name);
            break;
        case 'w':
            pResourceEffect = NEW GgafDxMassBoardEffect(effect_name);
            break;
        case 'P':
            pResourceEffect = NEW GgafDxPointSpriteEffect(effect_name);
            break;
        case 'p':
            pResourceEffect = NEW GgafDxMassPointSpriteEffect(effect_name);
            break;
        case 'o':
            pResourceEffect = NEW GgafDxPointSpriteSetEffect(effect_name);
            break;
        case 'E':
            pResourceEffect = NEW GgafDxEnclosedBoardEffect(effect_name);
            break;
        default:
            throwGgafCriticalException("prm_idstr="<<prm_idstr<<" の '"<<effect_type<<"' ・・・そんなエッフェクト種別は知りません");
            pResourceEffect = nullptr;
            break;
    }
    _TRACE3_("prm_idstr="<<prm_idstr);
    return  pResourceEffect;
}

void GgafDxEffectManager::onDeviceLostAll() {
    _TRACE3_("start-->");
    GgafResourceConnection<GgafDxEffect>* pCurrent = _pConn_first;
    HRESULT hr;
    while (pCurrent) {
        hr = pCurrent->peek()->_pID3DXEffect->OnLostDevice();
        checkDxException(hr, D3D_OK, "OnLostDevice() に失敗しました。");
        _TRACE3_("onDeviceLostAll pCurrent="<<pCurrent->getIdStr() << " OnLostDevice() execute");
        pCurrent = pCurrent->getNext();
    }
    _TRACE3_("end<--");
}

void GgafDxEffectManager::restoreAll() {
    _TRACE3_("start-->");
    GgafResourceConnection<GgafDxEffect>* pCurrent = _pConn_first;
    HRESULT hr;
    while (pCurrent) {
        hr = pCurrent->peek()->_pID3DXEffect->OnResetDevice();
        checkDxException(hr, D3D_OK, "OnResetDevice() に失敗しました。");
        _TRACE3_("restoreAll pCurrent="<<pCurrent->getIdStr() << " restoreAll() execute");
        pCurrent = pCurrent->getNext();
    }
    _TRACE3_("end<--");
}
void GgafDxEffectManager::setParamPerFrameAll() {
    //通常描画時１フレームに１回、GgafDxSpacetime::draw()で描画前に呼ばれる。
    GgafResourceConnection<GgafDxEffect>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->setParamPerFrame();
        pCurrent = pCurrent->getNext();
    }
}
GgafResourceConnection<GgafDxEffect>* GgafDxEffectManager::processCreateConnection(const char* prm_idstr,
                                                                                     GgafDxEffect* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    GgafDxEffectConnection* pConne = NEW GgafDxEffectConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}

