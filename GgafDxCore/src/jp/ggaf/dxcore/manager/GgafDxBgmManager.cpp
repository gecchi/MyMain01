#include "jp/ggaf/dxcore/manager/GgafDxBgmManager.h"

#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBgmManager::GgafDxBgmManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxBgm> (prm_manager_name) {
    _bgm_master_volume_rate = 1.0;
}

GgafDxBgm* GgafDxBgmManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    GgafDxBgm* pResource = nullptr;
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, "/", 1); //最初のスラッシュで分割
    if (names.size() == 2) {
        pResource = NEW GgafDxBgm(names[1].c_str());
    } else {
        pResource = NEW GgafDxBgm(names[0].c_str());
    }
    return pResource;
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
        while (_is_connecting_resource) { //簡易排他
            Sleep(1);
        }
        pConne = (GgafDxBgmConnection*)(pConne->getNext());
    }
}

float GgafDxBgmManager::getBgmMasterVolumeRate() {
    return _bgm_master_volume_rate;
}

GgafResourceConnection<GgafDxBgm>* GgafDxBgmManager::processCreateConnection(const char* prm_idstr, GgafDxBgm* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    GgafDxBgmConnection* pConne = NEW GgafDxBgmConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}
