#include "EffectShotMagic.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/Colorist.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    RED = 0,
    GREEN = 1,
    BLUE = 2,
};

EffectShotMagic::EffectShotMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectShotMagic") {
    _class_name = "EffectShotMagic";
    effectBlendOne(); //���Z����Technique
    useZBufferDrawing(true);       //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZBufferWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    defineRotMvWorldMatrix_Billboard(); //�ϊ��s����r���{�[�h��
    setHitAble(false);
}

void EffectShotMagic::initialize() {
    setMaterialColor(0.1, 1.0, 0.1);
    setCullingDraw(false);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectShotMagic::onActive() {
    GgafDx::Colorist* pColorist = getColorist();
    pColorist->beat(RED  ,  60, 15, 15, 15, -1);
    pColorist->beat(GREEN,  70, 15, 15, 15, -1);
    pColorist->beat(BLUE ,  80, 15, 15, 15, -1);
}

void EffectShotMagic::processBehavior() {
    getUvFlipper()->behave();
    getLocusVehicle()->behave();
    getScaler()->behave();
}

void EffectShotMagic::processJudgement() {
}

void EffectShotMagic::onInactive() {
}

EffectShotMagic::~EffectShotMagic() {
}
