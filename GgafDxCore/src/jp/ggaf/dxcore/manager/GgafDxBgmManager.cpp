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

GgafResourceConnection<GgafDxBgm>* GgafDxBgmManager::processCreateConnection(char* prm_idstr, GgafDxBgm* prm_pResource) {
    TRACE3(" GgafDxBgmManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDxBgmConnection* pConnection = NEW GgafDxBgmConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDxBgmManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
