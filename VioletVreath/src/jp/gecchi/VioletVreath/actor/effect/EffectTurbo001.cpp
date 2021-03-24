#include "EffectTurbo001.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectTurbo001::EffectTurbo001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Turbo001") {
    _class_name = "EffectTurbo001";
    inactivate();
    effectBlendOne(); //���Z����
    defineRotMvWorldMatrix_Billboard(); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectTurbo001::initialize() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1); //�A�j������
    setCullingDraw(false);
}

void EffectTurbo001::onActive() {
    getUvFlipper()->setActivePtnToTop();
    callVecDriver()->setFaceAngVelo(AXIS_Z, 3000);        //��]
}

void EffectTurbo001::processBehavior() {
    getUvFlipper()->behave();
    callVecDriver()->behave();
    getScaler()->behave();
    if (VB_PLAY->isPressed(VB_TURBO)) { //�^�[�{

    } else {
        inactivate();
    }
}

void EffectTurbo001::processJudgement() {

}

void EffectTurbo001::onInactive() {
}

EffectTurbo001::~EffectTurbo001() {
}
