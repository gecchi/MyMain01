#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SeManager::GgafDx9SeManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Se> (prm_manager_name) {
}

GgafDx9Se* GgafDx9SeManager::processCreateResource(char* prm_idstr) {
    GgafDx9Se* pSe_New = NEW GgafDx9Se(prm_idstr, 1);
    return pSe_New;
}

GgafResourceLead<GgafDx9Se>* GgafDx9SeManager::processCreateLead(char* prm_idstr, GgafDx9Se* prm_pResource) {
    _TRACE_(" GgafDx9SeManager::processCreateLead "<<prm_idstr<<" を生成開始。");
    GgafDx9SeLead* p = NEW GgafDx9SeLead(prm_idstr, prm_pResource);
    _TRACE_(" GgafDx9SeManager::processCreateLead "<<prm_idstr<<" を生成終了。");
    return p;
}
