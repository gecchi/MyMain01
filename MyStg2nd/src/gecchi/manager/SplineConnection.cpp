#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

SplineConnection::SplineConnection(char* prm_idstr, SplineSource* prm_pResource) :
    GgafResourceConnection<SplineSource> (prm_idstr, prm_pResource) {
}

void SplineConnection::processReleaseResource(SplineSource* prm_pResource) {
    _TRACE_("SplineConnection::processReleaseResource�ŊJ��(�����łԂ���ꂽ��close()�R��̉\������)");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

