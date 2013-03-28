#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBgmManager::GgafDxBgmManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxBgm> (prm_manager_name) {
}

GgafDxBgm* GgafDxBgmManager::processCreateResource(char* prm_idstr, void* prm_p) {
    GgafDxBgm* pResourceBgm = NEW GgafDxBgm(prm_idstr);
    return pResourceBgm;
}

void GgafDxBgmManager::updateVolume() {
    while(_is_connecting_resource) {
        Sleep(1);
    }
    GgafDxBgmConnection* pConnection = (GgafDxBgmConnection*)_pConnection_first;
    while (pConnection) {
        pConnection->peek()->setVolume(GGAF_MAX_VOLUME);
        while(_is_connecting_resource) { //簡易排他
            Sleep(1);
        }
        pConnection = (GgafDxBgmConnection*)(pConnection->getNext());
    }
}

GgafResourceConnection<GgafDxBgm>* GgafDxBgmManager::processCreateConnection(char* prm_idstr, GgafDxBgm* prm_pResource) {
    TRACE3(" GgafDxBgmManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDxBgmConnection* pConnection = NEW GgafDxBgmConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDxBgmManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
