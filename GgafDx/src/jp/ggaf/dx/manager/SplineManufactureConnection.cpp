#include "jp/ggaf/dx/manager/SplineManufactureConnection.h"

using namespace GgafDx;

SplineManufactureConnection::SplineManufactureConnection(const char* prm_idstr, SplineManufacture* prm_pResource) :
    GgafCore::ResourceConnection<SplineManufacture> (prm_idstr, prm_pResource) {
}

void SplineManufactureConnection::processReleaseResource(SplineManufacture* prm_pResource) {
    _TRACE_("SplineManufactureConnection::processReleaseResource��"<<prm_pResource->_spl_file<<"�̊J��(�����łԂ���ꂽ��close()�R��̉\������)");
    GGAF_DELETE(prm_pResource);
}

