#include "stdafx.h"
#include "EffectCondensation001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectCondensation001::EffectCondensation001(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "8/Lockon001", nullptr) {
    _class_name = "EffectCondensation001";
    inactivateImmed();
    effectBlendOne(); //���Z����
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectCondensation001::initialize() {
    _pUvFlipper->setFlipPtnRange(0, 3);   //�A�j���͈͂��O�`�P�T
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //�A�j������

}

void EffectCondensation001::onActive() {
    _pUvFlipper->setActivePtnToTop();
    setAlpha(0.01);
    _pScaler->forceRange(30000, 1000); //�X�P�[�����O�E�͈�
    _pScaler->setScale(30000);
    _pScaler->scaleLinerUntil(1000, 30);//�X�P�[�����O�E60F��₵��1000�ɏk��
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);        //��]
}

void EffectCondensation001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (_pScaler->_method[0] == NOSCALE) {
        //�k��������ABeat
        _pScaler->forceRange(1000, 2000);
        _pScaler->beat(30, 2, 2, -1); //�������[�v
    }
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectCondensation001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectCondensation001::onInactive() {
}

EffectCondensation001::~EffectCondensation001() {
}
