#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BgmManager::GgafDx9BgmManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Bgm> (prm_manager_name) {
}

GgafDx9Bgm* GgafDx9BgmManager::processCreateResource(char* prm_idstr) {
    GgafDx9Bgm* pResourceBgm = NEW GgafDx9Bgm(prm_idstr);
    return pResourceBgm;
}

GgafResourceConnection<GgafDx9Bgm>* GgafDx9BgmManager::processCreateConnection(char* prm_idstr, GgafDx9Bgm* prm_pResource) {
    TRACE3(" GgafDx9BgmManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    GgafDx9BgmConnection* pConnection = NEW GgafDx9BgmConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDx9BgmManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConnection;
}
