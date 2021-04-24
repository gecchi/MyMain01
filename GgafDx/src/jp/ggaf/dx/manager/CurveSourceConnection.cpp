#include "jp/ggaf/dx/manager/CurveSourceConnection.h"

using namespace GgafDx;

CurveSourceConnection::CurveSourceConnection(const char* prm_idstr, CurveSource* prm_pResource) :
    GgafCore::ResourceConnection<CurveSource> (prm_idstr, prm_pResource) {
}

void CurveSourceConnection::processReleaseResource(CurveSource* prm_pResource) {
    _TRACE_("CurveSourceConnection::processReleaseResource��"<<prm_pResource->_coord_data_file<<"�J��(�����łԂ���ꂽ��close()�R��̉\������)");
    GGAF_DELETE(prm_pResource);
}

