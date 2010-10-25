#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

CameraWorker::CameraWorker(const char* prm_name) : GgafMainActor(prm_name) {
    _class_name = "CameraWorker";
    _pos_camera = 0;
}
CameraWorker::~CameraWorker() {
}
