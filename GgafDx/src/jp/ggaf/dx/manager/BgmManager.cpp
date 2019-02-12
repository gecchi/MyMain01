#include "jp/ggaf/dx/manager/BgmManager.h"

#include "jp/ggaf/dx/manager/BgmConnection.h"


using namespace GgafDx;

BgmManager::BgmManager(const char* prm_manager_name) :
    GgafCore::ResourceManager<Bgm> (prm_manager_name) {
    _bgm_master_volume_rate = 1.0;
}

Bgm* BgmManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    Bgm* pResource = nullptr;
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, ",", 1); //最初のカンマで分割
    if (names.size() == 2) {
        pResource = NEW Bgm(names[1].c_str());
    } else {
        pResource = NEW Bgm(names[0].c_str());
    }
    return pResource;
}

void BgmManager::setBgmMasterVolumeRate(double prm_volume_rate) {
    _bgm_master_volume_rate = prm_volume_rate;
    while (_is_connecting_resource) {
        Sleep(1);
    }
    BgmConnection* pConne = (BgmConnection*)_pConn_first;
    while (pConne) {
        Bgm* pBgm = pConne->peek();
        pBgm->setVolume(pBgm->getVolume());
        while (_is_connecting_resource) { //簡易排他
            Sleep(1);
        }
        pConne = (BgmConnection*)(pConne->getNext());
    }
}

float BgmManager::getBgmMasterVolumeRate() {
    return _bgm_master_volume_rate;
}

GgafCore::ResourceConnection<Bgm>* BgmManager::processCreateConnection(const char* prm_idstr, Bgm* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    BgmConnection* pConne = NEW BgmConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}
