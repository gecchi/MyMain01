#include "jp/ggaf/dx/manager/CurveSourceManager.h"

#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/manager/CurveSourceConnection.h"

using namespace GgafDx;

CurveSourceManager::CurveSourceManager(const char* prm_manager_name) :
    GgafCore::ResourceManager<CurveSource> (prm_manager_name) {
}

CurveSource* CurveSourceManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    CurveSource* pResource = NEW CurveSource(prm_idstr);
    return pResource;
}

GgafCore::ResourceConnection<CurveSource>* CurveSourceManager::processCreateConnection(const char* prm_idstr, CurveSource* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    CurveSourceConnection* pConne = NEW CurveSourceConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}

