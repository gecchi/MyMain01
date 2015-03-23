#include "jp/ggaf/dxcore/manager/GgafDxSeManager.h"

#include <cstring>
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSeManager::GgafDxSeManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxSe> (prm_manager_name) {
}

GgafDxSe* GgafDxSeManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    // prm_idstr = "1/laser" の場合、モデルマネージャーのキーには"1/laser"で登録されることになる。
    // しかし、読み込むwaveファイルは"laser.wav"とする。
    // これは、同一waveを複数チャンネルで鳴らしたい場合等、最初の数値を変化されば、資源が複数
    // 確保されると事を意味する。

    GgafDxSe* pResource = nullptr;
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, "/", 1); //最初のスラッシュで分割
    if (names.size() == 2) {
        pResource = NEW GgafDxSe(names[1].c_str());
    } else {
        pResource = NEW GgafDxSe(names[0].c_str());
    }
    return pResource;
}

void GgafDxSeManager::updateVolume() {
    while (_is_connecting_resource) {
        Sleep(1);
    }
    GgafDxSeConnection* pConne = (GgafDxSeConnection*)_pConn_first;
    while (pConne) {
        pConne->peek()->setVolume(GGAF_MAX_VOLUME);
        while (_is_connecting_resource) { //簡易排他
            Sleep(1);
        }
        pConne = (GgafDxSeConnection*)(pConne->getNext());
    }
}

GgafResourceConnection<GgafDxSe>* GgafDxSeManager::processCreateConnection(const char* prm_idstr, GgafDxSe* prm_pResource) {
    _TRACE3_(" GgafDxSeManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDxSeConnection* pConne = NEW GgafDxSeConnection(prm_idstr, prm_pResource);
    _TRACE3_(" GgafDxSeManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConne;
}
