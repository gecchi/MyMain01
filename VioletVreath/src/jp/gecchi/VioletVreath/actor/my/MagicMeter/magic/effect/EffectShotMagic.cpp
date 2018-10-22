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

EffectShotMagic::EffectShotMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectShotMagic", nullptr) {
    _class_name = "EffectShotMagic";
    pColorist_ = NEW GgafDxColorist(this);
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
    pColorist_->beat(GgafDxColorist::RED  ,  60, 15, 15, 15, -1);
    pColorist_->beat(GgafDxColorist::GREEN,  70, 15, 15, 15, -1);
    pColorist_->beat(GgafDxColorist::BLUE ,  80, 15, 15, 15, -1);
}

void EffectShotMagic::processBehavior() {
    getUvFlipper()->behave();
    getKuroko()->behave();
    pColorist_->behave();
    getScaler()->behave();
}

void EffectShotMagic::processJudgement() {
}

void EffectShotMagic::onInactive() {
}

EffectShotMagic::~EffectShotMagic() {
    GGAF_DELETE(pColorist_);
}
