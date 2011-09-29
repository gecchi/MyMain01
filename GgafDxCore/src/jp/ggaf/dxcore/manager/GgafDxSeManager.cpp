#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSeManager::GgafDxSeManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxSe> (prm_manager_name) {
}

GgafDxSe* GgafDxSeManager::processCreateResource(char* prm_idstr, void* prm_p) {
    // prm_idstr = "1/laser" の場合、モデルマネージャーのキーには"1/laser"で登録し
    // 読み込むwaveファイルは"laser.wav"とする。
    // これは、同一waveを複数チャンネルで鳴らしたい場合等、最初の数値を変化されば、資源が複数
    // 確保されると事を意味する。

    GgafDxSe* pResource = NULL;
    char idstr[129];
    strcpy(idstr, prm_idstr);
    char* pT = strtok(idstr, "/" );
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        pResource = NEW GgafDxSe(prm_idstr);
    } else {
        pResource = NEW GgafDxSe(pT);
    }

    return pResource;
}

GgafResourceConnection<GgafDxSe>* GgafDxSeManager::processCreateConnection(char* prm_idstr, GgafDxSe* prm_pResource) {
    TRACE3(" GgafDxSeManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDxSeConnection* pConnection = NEW GgafDxSeConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDxSeManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
