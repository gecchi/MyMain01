#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Spline3DConnection::Spline3DConnection(char* prm_idstr, GgafDx9LibStg::Spline3D* prm_pResource) :
    GgafResourceConnection<GgafDx9LibStg::Spline3D> (prm_idstr, prm_pResource) {
}

void Spline3DConnection::processReleaseResource(GgafDx9LibStg::Spline3D* prm_pResource) {
    _TRACE_("Spline3DConnection::processReleaseResource‚Å _num_basepoint="<<prm_pResource->_num_basepoint<<"‚Ì‚ðŠJ•ú(‚±‚±‚Å‚Ô‚Á‰ó‚ê‚½‚çclose()˜R‚ê‚Ì‰Â”\«‚ ‚è)");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}
