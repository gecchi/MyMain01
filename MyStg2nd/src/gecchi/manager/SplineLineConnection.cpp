#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

SplineLineConnection::SplineLineConnection(char* prm_idstr, GgafLib::SplineLine* prm_pResource) :
    GgafResourceConnection<GgafLib::SplineLine> (prm_idstr, prm_pResource) {
}

void SplineLineConnection::processReleaseResource(GgafLib::SplineLine* prm_pResource) {
    _TRACE_("SplineLineConnection::processReleaseResource�� _num_basepoint="<<prm_pResource->_num_basepoint<<"�̂��J��(�����łԂ���ꂽ��close()�R��̉\������)");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}
