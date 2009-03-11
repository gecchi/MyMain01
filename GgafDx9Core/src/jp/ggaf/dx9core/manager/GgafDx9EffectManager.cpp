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
    GgafDx9Effect* p;
    switch (effect_type) {
        case 'X':
            p = NEW GgafDx9MeshEffect(effect_name);
            break;
        case 'S':
            p = NEW GgafDx9SpriteEffect(effect_name);
            break;
        case 'B':
            p = NEW GgafDx9BoardEffect(effect_name);
            break;
       default:
            TRACE("GgafDx9EffectManager::processCreateResource("<<prm_idstr<<") そんな種別はありません");
            throwGgafCriticalException("GgafDx9EffectManager::processCreateResource("<<prm_idstr<<") そんなエッフェクト種別は知りません");
            p = NULL;
            break;
    }
    _TRACE_("GgafDx9EffectManager::processCreateResource("<<prm_idstr<<")");
    return  p;
}

void GgafDx9EffectManager::onDeviceLostAll() {
    _TRACE_("GgafDx9EffectManager::onDeviceLostAll() start-->");
    GgafResourceConnection<GgafDx9Effect>* pCurrent = _pTop;
    HRESULT hr;
    while (pCurrent != NULL) {
        hr = pCurrent->view()->_pID3DXEffect->OnLostDevice();
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9EffectManager::onDeviceLostAll エフェクト["<<pCurrent->_idstr<<"]の OnLostDevice() に失敗しました。");
        _TRACE_("onDeviceLostAll pCurrent="<<pCurrent->_idstr << " OnLostDevice() execute");
        pCurrent = pCurrent->_pNext;
    }
    _TRACE_("GgafDx9EffectManager::onDeviceLostAll() end<--");
}

void GgafDx9EffectManager::restoreAll() {
    _TRACE_("GgafDx9EffectManager::restoreAll() start-->");
    GgafResourceConnection<GgafDx9Effect>* pCurrent = _pTop;
    HRESULT hr;
    while (pCurrent != NULL) {
        hr = pCurrent->view()->_pID3DXEffect->OnResetDevice();
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9EffectManager::restoreAll() エフェクト["<<pCurrent->_idstr<<"]の OnResetDevice() に失敗しました。");
        _TRACE_("restoreAll pCurrent="<<pCurrent->_idstr << " restoreAll() execute");
        pCurrent = pCurrent->_pNext;
    }
    _TRACE_("GgafDx9EffectManager::restoreAll() end<--");
}


GgafResourceConnection<GgafDx9Effect>* GgafDx9EffectManager::processCreateConnection(char* prm_idstr,
                                                                                     GgafDx9Effect* prm_pResource) {
    _TRACE_(" GgafDx9EffectManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDx9EffectConnection* p = NEW GgafDx9EffectConnection(prm_idstr, prm_pResource);
    _TRACE_(" GgafDx9EffectManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return p;
}

