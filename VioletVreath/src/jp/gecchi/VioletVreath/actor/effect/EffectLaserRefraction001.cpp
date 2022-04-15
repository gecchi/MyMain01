#include "EffectLaserRefraction001.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectLaserRefraction001::EffectLaserRefraction001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001") {
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
    getVecVehicle()->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
}

void EffectLaserRefraction001::processBehavior() {
    addScale(100);

    //getUvFlipper()->behave();
    getVecVehicle()->behave();
    getScaler()->behave();
}

void EffectLaserRefraction001::processJudgement() {
}

void EffectLaserRefraction001::onInactive() {
}

EffectLaserRefraction001::~EffectLaserRefraction001() {
}
