#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Planet001Atmosphere::Planet001Atmosphere(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planet001Atmosphere", NULL) {
    _class_name = "Planet001Atmosphere";
    setHitAble(false);
    setZEnable(true);        //Z�o�b�t�@�͍l��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_WORLDBOUND-2);
    defineRotMvWorldMatrix(GgafDxUtil::setWorldMatrix_RzBxyzMv); //XYZ���r���{�[�h
    viewAlsoForcesFar(true); //�����Ă��\��
}
void Planet001Atmosphere::onCreateModel() {
}

void Planet001Atmosphere::initialize() {
    setAlpha(0.9);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 100);
}

void Planet001Atmosphere::processBehavior() {
    _pScaler->behave();
    _pKurokoA->behave();
}

Planet001Atmosphere::~Planet001Atmosphere() {
}
