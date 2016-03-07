#include "EffectLockonMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLockonMagic::EffectLockonMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectLockonMagic", nullptr) {
    _class_name = "EffectLockonMagic";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne(); //���Z����Technique
    setZEnableDraw(true);       //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //�ϊ��s����r���{�[�h��
    setHitAble(false);
}

void EffectLockonMagic::initialize() {
    setAlpha(0.9);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectLockonMagic::onActive() {
}

void EffectLockonMagic::processBehavior() {
    getUvFlipper()->behave();
    getKuroko()->behave();
    pScaler_->behave();
}

void EffectLockonMagic::processJudgement() {
}

void EffectLockonMagic::onInactive() {
}

EffectLockonMagic::~EffectLockonMagic() {
    GGAF_DELETE(pScaler_);
}
