#include "SplineLineConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SplineLineConnection::SplineLineConnection(char* prm_idstr, GgafLib::SplineLine* prm_pResource) :
    GgafResourceConnection<GgafLib::SplineLine> (prm_idstr, prm_pResource) {
}

void SplineLineConnection::processReleaseResource(GgafLib::SplineLine* prm_pResource) {
    _TRACE_("SplineLineConnection::processReleaseResourceで num_basepoint_="<<prm_pResource->_num_basepoint<<"のを開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    GGAF_DELETE(prm_pResource);
}
