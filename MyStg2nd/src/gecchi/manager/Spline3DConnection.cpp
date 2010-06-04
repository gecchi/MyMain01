#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Spline3DConnection::Spline3DConnection(char* prm_idstr, GgafDx9Core::GgafDx9Spline3D* prm_pResource) :
    GgafResourceConnection<GgafDx9Core::GgafDx9Spline3D> (prm_idstr, prm_pResource) {
}

void Spline3DConnection::processReleaseResource(GgafDx9Core::GgafDx9Spline3D* prm_pResource) {
    _TRACE_("Spline3DConnection::processReleaseResource‚ÅŠJ•ú");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

