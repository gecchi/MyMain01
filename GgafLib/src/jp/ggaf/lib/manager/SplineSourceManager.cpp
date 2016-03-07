#include "jp/ggaf/lib/manager/SplineSourceManager.h"

#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/manager/SplineSourceConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineSourceManager::SplineSourceManager(const char* prm_manager_name) :
    GgafResourceManager<SplineSource> (prm_manager_name) {
}

SplineSource* SplineSourceManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    SplineSource* pResource = NEW SplineSource(prm_idstr);
    return pResource;
}

GgafResourceConnection<SplineSource>* SplineSourceManager::processCreateConnection(const char* prm_idstr, SplineSource* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    SplineSourceConnection* pConne = NEW SplineSourceConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}

