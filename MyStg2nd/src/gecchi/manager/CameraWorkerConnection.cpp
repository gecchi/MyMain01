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
    _TRACE_("CameraWorkerConnection::processReleaseResource��"<<prm_pResource->getName()<<"�J���Ƃ�����end() (�����łԂ���ꂽ��close()�R��̉\������)");
    //DELETE_IMPOSSIBLE_NULL(prm_pResource);
    prm_pResource->end(5);
}

