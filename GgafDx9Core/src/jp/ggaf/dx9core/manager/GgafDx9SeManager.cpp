#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SeManager::GgafDx9SeManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Se> (prm_manager_name) {
}

GgafDx9Se* GgafDx9SeManager::processCreateResource(char* prm_idstr) {
    GgafDx9Se* pResource = NEW GgafDx9Se(prm_idstr);
    return pResource;
}

GgafResourceConnection<GgafDx9Se>* GgafDx9SeManager::processCreateConnection(char* prm_idstr, GgafDx9Se* prm_pResource) {
    TRACE3(" GgafDx9SeManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDx9SeConnection* pConnection = NEW GgafDx9SeConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDx9SeManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
