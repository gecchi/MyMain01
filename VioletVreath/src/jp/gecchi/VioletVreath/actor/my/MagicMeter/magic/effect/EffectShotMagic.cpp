#include "EffectShotMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxColorist.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    RED = 0,
    GREEN = 1,
    BLUE = 2,
};

EffectShotMagic::EffectShotMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectShotMagic", nullptr) {
    _class_name = "EffectShotMagic";
    effectBlendOne(); //���Z����Technique
    setZEnableDraw(true);       //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    defineRotMvWorldMatrix_Billboard(); //�ϊ��s����r���{�[�h��
    setHitAble(false);
}

void EffectShotMagic::initialize() {
    setMaterialColor(0.1, 1.0, 0.1);
    setCullingDraw(false);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectShotMagic::onActive() {
    GgafDxColorist* pColorist = getColorist();
    pColorist->beat(RED  ,  60, 15, 15, 15, -1);
    pColorist->beat(GREEN,  70, 15, 15, 15, -1);
    pColorist->beat(BLUE ,  80, 15, 15, 15, -1);
}

void EffectShotMagic::processBehavior() {
    getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
}

void EffectShotMagic::processJudgement() {
}

void EffectShotMagic::onInactive() {
}

EffectShotMagic::~EffectShotMagic() {
}
