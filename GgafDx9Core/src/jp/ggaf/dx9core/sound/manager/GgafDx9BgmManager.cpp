#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BgmManager::GgafDx9BgmManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Bgm> (prm_manager_name) {
}

GgafDx9Bgm* GgafDx9BgmManager::processCreateResource(char* prm_idstr) {
    GgafDx9Bgm* pBgm_New = NEW GgafDx9Bgm(prm_idstr);
    return pBgm_New;
}

GgafResourceLead<GgafDx9Bgm>* GgafDx9BgmManager::processCreateLead(char* prm_idstr, GgafDx9Bgm* prm_pResource) {
    _TRACE_(" GgafDx9BgmManager::processCreateLead "<<prm_idstr<<" を生成開始。");
    GgafDx9BgmLead* p = NEW GgafDx9BgmLead(prm_idstr, prm_pResource);
    _TRACE_(" GgafDx9BgmManager::processCreateLead "<<prm_idstr<<" を生成終了。");
    return p;
}
