#include "jp/ggaf/dx/manager/SeManager.h"

#include <cstring>
#include "jp/ggaf/dx/manager/SeConnection.h"


using namespace GgafDx;

SeManager::SeManager(const char* prm_manager_name) :
    GgafCore::ResourceManager<Se> (prm_manager_name) {
    _se_master_volume_rate = 1.0;
}

Se* SeManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    // prm_idstr = "1,laser" の場合、モデルマネージャーのキーには"1,laser"で登録されることになる。
    // しかし、読み込むwaveファイルは"laser.wav"とする。
    // これは、同一waveを複数チャンネルで鳴らしたい場合等、最初の数値を変化されば、資源が複数
    // 確保されると事を意味する。

    Se* pResource = nullptr;
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, ",", 1); //最初のスラッシュで分割
    if (names.size() == 2) {
        pResource = NEW Se(names[1].c_str());
    } else {
        pResource = NEW Se(names[0].c_str());
    }
    return pResource;
}

void SeManager::setSeMasterVolumeRate(double prm_volume_rate) {
    _se_master_volume_rate = prm_volume_rate;
    while (_is_connecting_resource) {
        Sleep(1);
    }
    SeConnection* pConne = (SeConnection*)_pConn_first;
    while (pConne) {

        Se* pSe = pConne->peek();
        pSe->setVolume(pSe->getVolume());

        while (_is_connecting_resource) { //簡易排他
            Sleep(1);
        }
        pConne = (SeConnection*)(pConne->getNext());
    }
}

double SeManager::getSeMasterVolumeRate() {
    return _se_master_volume_rate;
}

GgafCore::ResourceConnection<Se>* SeManager::processCreateConnection(const char* prm_idstr, Se* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    SeConnection* pConne = NEW SeConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}
