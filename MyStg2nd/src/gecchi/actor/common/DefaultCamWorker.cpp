#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DefaultCamWorker::DefaultCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "DefaultCamWorker";
}

void DefaultCamWorker::processBehavior() {
}

DefaultCamWorker::~DefaultCamWorker() {
}
