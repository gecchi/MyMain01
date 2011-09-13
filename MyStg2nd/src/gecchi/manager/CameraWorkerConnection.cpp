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
    _TRACE_("CameraWorkerConnection::processReleaseResource‚Å"<<prm_pResource->getName()<<"ŠJ•ú‚Æ‚¢‚¤‚©end() (‚±‚±‚Å‚Ô‚Á‰ó‚ê‚½‚çclose()˜R‚ê‚Ì‰Â”\«‚ ‚è)");
    //DELETE_IMPOSSIBLE_NULL(prm_pResource);
    prm_pResource->end(5);
}

