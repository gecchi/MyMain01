#include "EffectVreathMagic001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectVreathMagic001::EffectVreathMagic001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectSpeedMagic") {
    _class_name = "EffectVreathMagic001";
    effectBlendOne(); //���Z����Technique
    setZEnableDraw(true);       //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    defineRotMvWorldMatrix_Billboard(); //�ϊ��s����r���{�[�h��
    setHitAble(false);
}

void EffectVreathMagic001::initialize() {
    setCullingDraw(false);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectVreathMagic001::onActive() {
}

void EffectVreathMagic001::processBehavior() {
    getUvFlipper()->behave();
    callVecDriver()->behave();
    getScaler()->behave();
}

void EffectVreathMagic001::processJudgement() {
}

void EffectVreathMagic001::onInactive() {
}

EffectVreathMagic001::~EffectVreathMagic001() {
}
