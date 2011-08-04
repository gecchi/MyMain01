#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

SplineManager::SplineManager(const char* prm_manager_name) :
    GgafResourceManager<SplineSource> (prm_manager_name) {
}

SplineSource* SplineManager::processCreateResource(char* prm_idstr, void* prm_p) {

    SplineSource* pResource = NEW SplineSource(prm_idstr);

    return pResource;
}

GgafResourceConnection<SplineSource>* SplineManager::processCreateConnection(char* prm_idstr, SplineSource* prm_pResource) {
    TRACE3(" SplineManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    SplineConnection* pConnection = NEW SplineConnection(prm_idstr, prm_pResource);
    TRACE3(" SplineManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}

