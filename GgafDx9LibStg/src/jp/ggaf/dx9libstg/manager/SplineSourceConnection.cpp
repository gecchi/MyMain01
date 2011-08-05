#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

SplineSourceConnection::SplineSourceConnection(char* prm_idstr, SplineSource* prm_pResource) :
    GgafResourceConnection<SplineSource> (prm_idstr, prm_pResource) {
}

void SplineSourceConnection::processReleaseResource(SplineSource* prm_pResource) {
    _TRACE_("SplineSourceConnection::processReleaseResource�ŊJ��(�����łԂ���ꂽ��close()�R��̉\������)");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

