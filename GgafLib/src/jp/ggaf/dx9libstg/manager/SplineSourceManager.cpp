#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

SplineSourceManager::SplineSourceManager(const char* prm_manager_name) :
    GgafResourceManager<SplineSource> (prm_manager_name) {
}

SplineSource* SplineSourceManager::processCreateResource(char* prm_idstr, void* prm_p) {

    SplineSource* pResource = NEW SplineSource(prm_idstr);

    return pResource;
}

GgafResourceConnection<SplineSource>* SplineSourceManager::processCreateConnection(char* prm_idstr, SplineSource* prm_pResource) {
    TRACE3(" SplineSourceManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    SplineSourceConnection* pConnection = NEW SplineSourceConnection(prm_idstr, prm_pResource);
    TRACE3(" SplineSourceManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConnection;
}

