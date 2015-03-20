#include "jp/ggaf/dxcore/manager/GgafDxBgmManager.h"

#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBgmManager::GgafDxBgmManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxBgm> (prm_manager_name) {
}

GgafDxBgm* GgafDxBgmManager::processCreateResource(char* prm_idstr, void* prm_pConnector) {
    GgafDxBgm* pResourceBgm = NEW GgafDxBgm(prm_idstr);
    return pResourceBgm;
}

void GgafDxBgmManager::updateVolume() {
    while (_is_connecting_resource) {
        Sleep(1);
    }
    GgafDxBgmConnection* pConne = (GgafDxBgmConnection*)_pConn_first;
    while (pConne) {
        pConne->peek()->setVolume(GGAF_MAX_VOLUME);
        while (_is_connecting_resource) { //簡易排他
            Sleep(1);
        }
        pConne = (GgafDxBgmConnection*)(pConne->getNext());
    }
}

GgafResourceConnection<GgafDxBgm>* GgafDxBgmManager::processCreateConnection(char* prm_idstr, GgafDxBgm* prm_pResource) {
    _TRACE3_(" GgafDxBgmManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDxBgmConnection* pConne = NEW GgafDxBgmConnection(prm_idstr, prm_pResource);
    _TRACE3_(" GgafDxBgmManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConne;
}
