#include "jp/ggaf/dx/manager/CurveSourceConnection.h"

using namespace GgafDx;

CurveSourceConnection::CurveSourceConnection(const char* prm_idstr, CurveSource* prm_pResource) :
    GgafCore::ResourceConnection<CurveSource> (prm_idstr, prm_pResource) {
}

void CurveSourceConnection::processReleaseResource(CurveSource* prm_pResource) {
    _TRACE_("CurveSourceConnection::processReleaseResourceで"<<prm_pResource->_coord_spl_file<<"開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    GGAF_DELETE(prm_pResource);
}

