#include "SpriteLabelBonus001.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT ,
    PHASE_FADE ,
    PHASE_BANPEI,
};

SpriteLabelBonus001::SpriteLabelBonus001(const char* prm_name) :
        FontSpriteActor(prm_name, "Ranking_16Font")
{
    _class_name = "SpriteLabelBonus001";
    setZEnableDraw(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ��ɋ���
    setSpecialRenderDepthIndex(1); //�`�揇�����őO�ʕ`��ɋ����B
    setHitAble(false);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_AlignAppScBxyzMv); //��������̑傫���𑵂���r���{�[�h
}

void SpriteLabelBonus001::onCreateModel() {
}

void SpriteLabelBonus001::initialize() {
}

void SpriteLabelBonus001::onDispatched(GgafDx::GeometricActor* prm_pOrgActor) {
    setPositionAt(prm_pOrgActor);
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->setMvVelo(0);
    pLocoVehicle->setMvAcce(0);
    pLocoVehicle->takeoverFrom(prm_pOrgActor->getLocoVehicle());
    setAlpha(0.9);
    getPhase()->reset(PHASE_INIT);
}

void SpriteLabelBonus001::processBehavior() {
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pLocoVehicle->setMvAcceByT(60,0);
            if(pPhase->getFrame() >= 60) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_FADE: {
            addAlpha(-0.01);
            if (getAlpha() <= 0.0) {
                sayonara();
                pPhase->changeNext();
            }
            break;
        }
        default:
            break;
    }
    pLocoVehicle->behave();
}

SpriteLabelBonus001::~SpriteLabelBonus001() {
}

