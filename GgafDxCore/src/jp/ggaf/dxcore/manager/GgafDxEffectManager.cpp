#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectConnection.h"
#include "jp/ggaf/dxcore/effect/GgafDxD3DXAniMeshEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMorphMeshEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteSetEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardSetEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"
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

GgafDxEffect* GgafDxEffectManager::processCreateResource(char* prm_idstr, void* prm_pConnector) {
    //振り分け
    char effect_type = *prm_idstr; //頭一文字
    char* effect_name = prm_idstr + 2; //３文字目以降
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
        case 'B':
            pResourceEffect = NEW GgafDxBoardEffect(effect_name);
            break;
        case 'b':
            pResourceEffect = NEW GgafDxBoardSetEffect(effect_name);
            break;
        case 'P':
            pResourceEffect = NEW GgafDxPointSpriteEffect(effect_name);
            break;
        default:
            throwGgafCriticalException("GgafDxEffectManager::processCreateResource("<<prm_idstr<<") そんなエッフェクト種別は知りません");
            pResourceEffect = nullptr;
            break;
    }
    _DTRACE3_("GgafDxEffectManager::processCreateResource("<<prm_idstr<<")");
    return  pResourceEffect;
}

void GgafDxEffectManager::onDeviceLostAll() {
    _DTRACE3_("GgafDxEffectManager::onDeviceLostAll() start-->");
    GgafResourceConnection<GgafDxEffect>* pCurrent = _pConn_first;
    HRESULT hr;
    while (pCurrent) {
        hr = pCurrent->peek()->_pID3DXEffect->OnLostDevice();
        checkDxException(hr, D3D_OK, "GgafDxEffectManager::onDeviceLostAll エフェクト["<<pCurrent->getIdStr()<<"]の OnLostDevice() に失敗しました。");
        _DTRACE3_("onDeviceLostAll pCurrent="<<pCurrent->getIdStr() << " OnLostDevice() execute");
        pCurrent = pCurrent->getNext();
    }
    _DTRACE3_("GgafDxEffectManager::onDeviceLostAll() end<--");
}

void GgafDxEffectManager::restoreAll() {
    _DTRACE3_("GgafDxEffectManager::restoreAll() start-->");
    GgafResourceConnection<GgafDxEffect>* pCurrent = _pConn_first;
    HRESULT hr;
    while (pCurrent) {
        hr = pCurrent->peek()->_pID3DXEffect->OnResetDevice();
        checkDxException(hr, D3D_OK, "GgafDxEffectManager::restoreAll() エフェクト["<<pCurrent->getIdStr()<<"]の OnResetDevice() に失敗しました。");
        _DTRACE3_("restoreAll pCurrent="<<pCurrent->getIdStr() << " restoreAll() execute");
        pCurrent = pCurrent->getNext();
    }
    _DTRACE3_("GgafDxEffectManager::restoreAll() end<--");
}
void GgafDxEffectManager::setParamPerFrameAll() {
    //通常描画時１フレームに１回、GgafDxUniverse::draw()で描画前に呼ばれる。
    GgafResourceConnection<GgafDxEffect>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->setParamPerFrame();
        pCurrent = pCurrent->getNext();
    }
}
GgafResourceConnection<GgafDxEffect>* GgafDxEffectManager::processCreateConnection(char* prm_idstr,
                                                                                     GgafDxEffect* prm_pResource) {
    _DTRACE3_(" GgafDxEffectManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDxEffectConnection* pConne = NEW GgafDxEffectConnection(prm_idstr, prm_pResource);
    _DTRACE3_(" GgafDxEffectManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConne;
}

