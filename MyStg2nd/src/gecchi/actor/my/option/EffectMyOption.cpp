#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EffectMyOption::EffectMyOption(const char* prm_name, MyOption* prm_pMyOption) : DefaultMeshSetActor(prm_name, "8/option_enagy") {
    changeEffectTechnique("DestBlendOne"); //���Z��������Technique�w��
    _pMyOption = prm_pMyOption;
    setAlpha(0.99);
    setZEnable(true);        //Z�o�b�t�@�͍l�����ĕ`��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    setHitAble(false);
//    setScaleRate(0.1);
    useProgress(10);
}

void EffectMyOption::onCreateModel() {
    _pGgafDx9Model->setSpecular(5.0, 1.0);
}

void EffectMyOption::initialize() {
    _pKuroko->setFaceAngVelo(AXIS_X, 5*1000);
//    _pKuroko->setFaceAngVelo(AXIS_Y, 3*1000);
//    _pKuroko->setFaceAngVelo(AXIS_Z, 7*1000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 1500);

}

void EffectMyOption::onReset() {
    _pPrg->set(1);
}

void EffectMyOption::onActive() {

}

void EffectMyOption::processBehavior() {
    if (_pPrg->get() == 1) {
        _pScaler->beat(30,8,2,-1);
        _pPrg->change(2);
    }
    locateAs(_pMyOption);
    _pKuroko->behave();
    _pScaler->behave();
}

void EffectMyOption::processJudgement() {
}

void EffectMyOption::processPreDraw() {
    setSpecialDrawDepth(_pMyOption->_now_drawdepth-1);//�e�I�v�V��������ɕ`�悷�邽��
    DefaultMeshSetActor::processPreDraw();
}


void EffectMyOption::onHit(GgafActor* prm_pOtherActor) {
}

void EffectMyOption::processFinal() {
}

EffectMyOption::~EffectMyOption() {
}

