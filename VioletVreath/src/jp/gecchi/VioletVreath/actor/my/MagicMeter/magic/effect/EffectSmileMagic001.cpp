#include "EffectSmileMagic001.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectSmileMagic001::EffectSmileMagic001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectSpeedMagic") {
    _class_name = "EffectSmileMagic001";
    effectBlendOne(); //���Z����Technique
    setZEnableDraw(true);       //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    defineRotMvWorldMatrix_Billboard(); //�ϊ��s����r���{�[�h��
    setHitAble(false);
}

void EffectSmileMagic001::initialize() {
    setCullingDraw(false);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectSmileMagic001::onActive() {
}

void EffectSmileMagic001::processBehavior() {
    getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
}

void EffectSmileMagic001::processJudgement() {
}

void EffectSmileMagic001::onInactive() {
}

EffectSmileMagic001::~EffectSmileMagic001() {
}
