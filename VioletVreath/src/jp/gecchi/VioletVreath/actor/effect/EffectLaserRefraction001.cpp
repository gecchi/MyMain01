#include "EffectLaserRefraction001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLaserRefraction001::EffectLaserRefraction001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001", nullptr) {
    _class_name = "EffectLaserRefraction001";
    effectBlendOne(); //���Z��������Technique�w��
    setZEnableDraw(true);        //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
}

void EffectLaserRefraction001::initialize() {
    setHitAble(false);
}

void EffectLaserRefraction001::onActive() {
    //getUvFlipper()->setActivePtnToTop();
    //getUvFlipper()->exec(FLIP_ORDER_LOOP, 1); //�p���p���A�j������
    setAlpha(0.5);
    setScale(R_SC(6));
    getKuroko()->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
}

void EffectLaserRefraction001::processBehavior() {
    addScale(100);

    //getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
}

void EffectLaserRefraction001::processJudgement() {
}

void EffectLaserRefraction001::onInactive() {
}

EffectLaserRefraction001::~EffectLaserRefraction001() {
}
