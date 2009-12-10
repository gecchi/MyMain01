#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SeManager::GgafDx9SeManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Se> (prm_manager_name) {
}

GgafDx9Se* GgafDx9SeManager::processCreateResource(char* prm_idstr) {
    // prm_idstr = "1/laser" の場合、モデルマネージャーのキーには"1/laser"で登録し
    // 読み込むwaveファイルは"laser.wav"とする。
    // これは、同一waveを複数チャンネルで鳴らしたい場合等、最初の数値を変化されば、資源が複数
    // 確保されると事を意味する。

    GgafDx9Se* pResource = NULL;
    char idstr[129];
    strcpy(idstr, prm_idstr);
    char* pT = strtok(idstr, "/" );
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        pResource = NEW GgafDx9Se(prm_idstr);
    } else {
        pResource = NEW GgafDx9Se(pT);
    }

    return pResource;
}

GgafResourceConnection<GgafDx9Se>* GgafDx9SeManager::processCreateConnection(char* prm_idstr, GgafDx9Se* prm_pResource) {
    TRACE3(" GgafDx9SeManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDx9SeConnection* pConnection = NEW GgafDx9SeConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDx9SeManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
