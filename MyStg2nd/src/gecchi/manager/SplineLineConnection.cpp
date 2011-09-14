#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

SplineLineConnection::SplineLineConnection(char* prm_idstr, GgafDx9LibStg::SplineLine* prm_pResource) :
    GgafResourceConnection<GgafDx9LibStg::SplineLine> (prm_idstr, prm_pResource) {
}

void SplineLineConnection::processReleaseResource(GgafDx9LibStg::SplineLine* prm_pResource) {
    _TRACE_("SplineLineConnection::processReleaseResource‚Å _num_basepoint="<<prm_pResource->_num_basepoint<<"‚Ì‚ðŠJ•ú(‚±‚±‚Å‚Ô‚Á‰ó‚ê‚½‚çclose()˜R‚ê‚Ì‰Â”\«‚ ‚è)");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}
