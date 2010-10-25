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
    //CameraWorkerは全てUniverseに所属しているため、解放不要
    //DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

