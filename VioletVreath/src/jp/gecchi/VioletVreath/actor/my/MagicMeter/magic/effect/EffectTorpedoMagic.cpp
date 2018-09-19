#include "EffectTorpedoMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectTorpedoMagic::EffectTorpedoMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectTorpedoMagic", nullptr) {
    _class_name = "EffectTorpedoMagic";
    effectBlendOne(); //���Z����Technique
    setZEnableDraw(true);       //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    defineRotMvWorldMatrix_Billboard(); //�ϊ��s����r���{�[�h��
    setHitAble(false);
}

void EffectTorpedoMagic::initialize() {
    setAlpha(0.9);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectTorpedoMagic::onActive() {
}

void EffectTorpedoMagic::processBehavior() {
    getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
}

void EffectTorpedoMagic::processJudgement() {
}

void EffectTorpedoMagic::onInactive() {
}

EffectTorpedoMagic::~EffectTorpedoMagic() {
}
