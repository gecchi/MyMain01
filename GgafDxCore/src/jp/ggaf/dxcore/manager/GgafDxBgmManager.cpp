#include "jp/ggaf/dxcore/manager/GgafDxBgmManager.h"

#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBgmManager::GgafDxBgmManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxBgm> (prm_manager_name) {
    _bgm_master_volume_rate = 1.0;
}

GgafDxBgm* GgafDxBgmManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    GgafDxBgm* pResourceBgm = NEW GgafDxBgm(prm_idstr);
    return pResourceBgm;
}

void GgafDxBgmManager::setBgmMasterVolumeRate(double prm_volume_rate) {
    _bgm_master_volume_rate = prm_volume_rate;
    while (_is_connecting_resource) {
        Sleep(1);
    }
    GgafDxBgmConnection* pConne = (GgafDxBgmConnection*)_pConn_first;
    while (pConne) {
        GgafDxBgm* pBgm = pConne->peek();
        pBgm->setVolume(pBgm->getVolume());
        while (_is_connecting_resource) { //�ȈՔr��
            Sleep(1);
        }
        pConne = (GgafDxBgmConnection*)(pConne->getNext());
    }
}

float GgafDxBgmManager::getBgmMasterVolumeRate() {
    return _bgm_master_volume_rate;
}

GgafResourceConnection<GgafDxBgm>* GgafDxBgmManager::processCreateConnection(const char* prm_idstr, GgafDxBgm* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��J�n�B");
    GgafDxBgmConnection* pConne = NEW GgafDxBgmConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��I���B");
    return pConne;
}
