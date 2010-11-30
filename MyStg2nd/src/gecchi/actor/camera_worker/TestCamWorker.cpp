#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TestCamWorker::TestCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "TestCamWorker";
}

void TestCamWorker::onActive() {

}

void TestCamWorker::onSwitchedCameraWork() {
    P_CAM->setCoordinateBy(P_MYSHIP);
    GgafDx9CameraViewPoint* pVP = P_CAM->_pViewPoint;
    pVP->setCoordinateBy(P_MYSHIP);
}

void TestCamWorker::processBehavior() {
    GgafDx9CameraViewPoint* pVP = P_CAM->_pViewPoint;
    pVP->setCoordinateBy(P_MYSHIP);
    P_CAM->_X += 2000;
    P_CAM->_Y += 2000;
    P_CAM->_Z += 2000;
}

void TestCamWorker::processJudgement() {
}

void TestCamWorker::onInactive() {
}

TestCamWorker::~TestCamWorker() {
}
