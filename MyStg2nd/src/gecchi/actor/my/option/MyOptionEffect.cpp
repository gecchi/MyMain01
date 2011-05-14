#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyOptionEffect::MyOptionEffect(const char* prm_name, MyOption* prm_pMyOption) : DefaultMeshSetActor(prm_name, "8/option_enagy") {
    changeEffectTechnique("DestBlendOne"); //���Z��������Technique�w��
    _pMyOption = prm_pMyOption;
    setAlpha(0.99);
    setZEnable(true);        //Z�o�b�t�@�͍l�����ĕ`��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
}

void MyOptionEffect::onCreateModel() {
    _pGgafDx9Model->setSpecular(5.0, 1.0);
}

void MyOptionEffect::initialize() {
    _SX=_SY=_SZ=1000;
}

void MyOptionEffect::onReset() {
}

void MyOptionEffect::onActive() {
}

void MyOptionEffect::processBehavior() {
    locateAs(_pMyOption);
}

void MyOptionEffect::processJudgement() {
}

void MyOptionEffect::processPreDraw() {
    setSpecialDrawDepth(_pMyOption->_now_drawdepth-1);
    DefaultMeshSetActor::processPreDraw();
}


void MyOptionEffect::onHit(GgafActor* prm_pOtherActor) {
}

void MyOptionEffect::processFinal() {
}

MyOptionEffect::~MyOptionEffect() {
}

