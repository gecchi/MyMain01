#include "jp/ggaf/lib/manager/SplineSourceConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineSourceConnection::SplineSourceConnection(const char* prm_idstr, SplineSource* prm_pResource) :
    GgafResourceConnection<SplineSource> (prm_idstr, prm_pResource) {
}

void SplineSourceConnection::processReleaseResource(SplineSource* prm_pResource) {
    _TRACE_("SplineSourceConnection::processReleaseResource��"<<prm_pResource->_coord_data_file<<"�J��(�����łԂ���ꂽ��close()�R��̉\������)");
    GGAF_DELETE(prm_pResource);
}

