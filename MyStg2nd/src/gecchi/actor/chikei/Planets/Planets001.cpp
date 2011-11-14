#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


Planets001::Planets001(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planets001", NULL) {
    _class_name = "Planets001";
    setHitAble(false);
    setZEnable(true);        //Z�o�b�t�@�͍l��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
}
void Planets001::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void Planets001::initialize() {
    setAlpha(0.99);
    _X = GgafDxUniverse::_X_goneRight - 1000;
    _RX = D45ANG;
    _SX = _SY = _SZ = 500 * 1000;
    _pKurokoA->setFaceAngVelo(AXIS_Y, 1000);
}
void Planets001::processBehavior() {
    //����I�u�W�F�N�g�e�X�g
    if (GgafDxInput::isBeingPressedKey(DIK_O)) {
        _X += 300*1000;
    }
    if (GgafDxInput::isBeingPressedKey(DIK_Y)) {
        _X -= 300*1000;
    }
    if (GgafDxInput::isBeingPressedKey(DIK_U)) {
        _pScaler->addScale(5000);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_I)) {
        _pScaler->addScale(-5000);
    }
    _pScaler->behave();
    _pKurokoA->behave();
}

bool Planets001::isOutOfUniverse() {
    return false;
}

Planets001::~Planets001() {
}

