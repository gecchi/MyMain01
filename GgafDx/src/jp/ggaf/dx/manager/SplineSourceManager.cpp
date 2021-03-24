#include "jp/ggaf/dx/manager/SplineSourceManager.h"

#include "jp/ggaf/dx/util/spline/SplineSource.h"
#include "jp/ggaf/dx/manager/SplineSourceConnection.h"

using namespace GgafDx;

SplineSourceManager::SplineSourceManager(const char* prm_manager_name) :
    GgafCore::ResourceManager<SplineSource> (prm_manager_name) {
}

SplineSource* SplineSourceManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    SplineSource* pResource = NEW SplineSource(prm_idstr);
    return pResource;
}

GgafCore::ResourceConnection<SplineSource>* SplineSourceManager::processCreateConnection(const char* prm_idstr, SplineSource* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    SplineSourceConnection* pConne = NEW SplineSourceConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}

