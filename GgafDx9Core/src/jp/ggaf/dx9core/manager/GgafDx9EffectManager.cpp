#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9EffectManager::GgafDx9EffectManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Effect> (prm_manager_name) {
}

GgafDx9Effect* GgafDx9EffectManager::processCreateResource(char* prm_idstr) {
    //振り分け
    char effect_type = *prm_idstr; //頭一文字
    char* effect_name = prm_idstr + 2; //３文字目以降
    GgafDx9Effect* pResourceEffect;
    switch (effect_type) {
        case 'X':
            pResourceEffect = NEW GgafDx9MeshEffect(effect_name);
            break;
        case '2':
            pResourceEffect = NEW GgafDx9MorphTwoMeshEffect(effect_name);
            break;

        case 'S':
            pResourceEffect = NEW GgafDx9SpriteEffect(effect_name);
            break;
        case 'B':
            pResourceEffect = NEW GgafDx9BoardEffect(effect_name);
            break;
       default:
            TRACE("GgafDx9EffectManager::processCreateResource("<<prm_idstr<<") そんな種別はありません");
            throwGgafCriticalException("GgafDx9EffectManager::processCreateResource("<<prm_idstr<<") そんなエッフェクト種別は知りません");
            pResourceEffect = NULL;
            break;
    }
    TRACE3("GgafDx9EffectManager::processCreateResource("<<prm_idstr<<")");
    return  pResourceEffect;
}

void GgafDx9EffectManager::onDeviceLostAll() {
    TRACE3("GgafDx9EffectManager::onDeviceLostAll() start-->");
    GgafResourceConnection<GgafDx9Effect>* pCurrent = _pFirstConnection;
    HRESULT hr;
    while (pCurrent != NULL) {
        hr = pCurrent->view()->_pID3DXEffect->OnLostDevice();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9EffectManager::onDeviceLostAll エフェクト["<<pCurrent->getIdStr()<<"]の OnLostDevice() に失敗しました。");
        TRACE3("onDeviceLostAll pCurrent="<<pCurrent->getIdStr() << " OnLostDevice() execute");
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDx9EffectManager::onDeviceLostAll() end<--");
}

void GgafDx9EffectManager::restoreAll() {
    TRACE3("GgafDx9EffectManager::restoreAll() start-->");
    GgafResourceConnection<GgafDx9Effect>* pCurrent = _pFirstConnection;
    HRESULT hr;
    while (pCurrent != NULL) {
        hr = pCurrent->view()->_pID3DXEffect->OnResetDevice();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9EffectManager::restoreAll() エフェクト["<<pCurrent->getIdStr()<<"]の OnResetDevice() に失敗しました。");
        TRACE3("restoreAll pCurrent="<<pCurrent->getIdStr() << " restoreAll() execute");
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDx9EffectManager::restoreAll() end<--");
}


GgafResourceConnection<GgafDx9Effect>* GgafDx9EffectManager::processCreateConnection(char* prm_idstr,
                                                                                     GgafDx9Effect* prm_pResource) {
    TRACE3(" GgafDx9EffectManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDx9EffectConnection* pConnection = NEW GgafDx9EffectConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDx9EffectManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}

