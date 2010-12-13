#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

SplineProgramConnection::SplineProgramConnection(char* prm_idstr, GgafDx9Core::GgafDx9SplineProgram* prm_pResource) :
    GgafResourceConnection<GgafDx9Core::GgafDx9SplineProgram> (prm_idstr, prm_pResource) {
}

void SplineProgramConnection::processReleaseResource(GgafDx9Core::GgafDx9SplineProgram* prm_pResource) {
    _TRACE_("SplineProgramConnection::processReleaseResourceで開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

