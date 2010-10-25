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

void TestCamWorker::onPushed() {
    pCAM->setGeometry(pMYSHIP);
    GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;
    pVP->setGeometry(pMYSHIP);
}

void TestCamWorker::processBehavior() {
    GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;
    pVP->setGeometry(pMYSHIP);
    pCAM->_X += 2000;
    pCAM->_Y += 2000;
    pCAM->_Z += 2000;
}

void TestCamWorker::processJudgement() {
}

void TestCamWorker::onInactive() {
}

TestCamWorker::~TestCamWorker() {
}
