#include "EffectSpeedMagic.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectSpeedMagic::EffectSpeedMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectSpeedMagic") {
    _class_name = "EffectSpeedMagic";
    effectBlendOne(); //���Z����Technique
    setZEnableDraw(true);       //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    defineRotMvWorldMatrix_Billboard(); //�ϊ��s����r���{�[�h��
    setHitAble(false);
}

void EffectSpeedMagic::initialize() {
    setCullingDraw(false);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectSpeedMagic::onActive() {
}

void EffectSpeedMagic::processBehavior() {
    getUvFlipper()->behave();
    callVecDriver()->behave();
    getScaler()->behave();
}

void EffectSpeedMagic::processJudgement() {
}

void EffectSpeedMagic::onInactive() {
}

EffectSpeedMagic::~EffectSpeedMagic() {
}
