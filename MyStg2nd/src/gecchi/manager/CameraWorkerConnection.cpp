#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

CameraWorkerConnection::CameraWorkerConnection(char* prm_idstr, CameraWorker* prm_pResource) :
    GgafResourceConnection<CameraWorker> (prm_idstr, prm_pResource) {
}

void CameraWorkerConnection::processReleaseResource(CameraWorker* prm_pResource) {
    prm_pResource->end();
}

