#include "SpriteLabelBonus001.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_MOVE01 ,
    PHASE_MOVE02 ,
    PHASE_LEAVE ,
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
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_BxyzMv); //XYZ���r���{�[�h
}

void SpriteLabelBonus001::onCreateModel() {
}

void SpriteLabelBonus001::initialize() {

}

void SpriteLabelBonus001::onDispatched(GgafDx::GeometricActor* prm_pOrgActor) {
    setPositionAt(prm_pOrgActor);
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->takeoverFrom(prm_pOrgActor->getLocoVehicle());
    pLocoVehicle->setMvAcce(300);
    setAlpha(0.7);
    getPhase()->reset(PHASE_INIT);
}

void SpriteLabelBonus001::processBehavior() {
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }
        case PHASE_MOVE01: {
            //���΂炭���i
            if (pPhase->hasArrivedFrameAt(60)) {
                //�J�����Ɍ������ĕ����]��1
                pLocoVehicle->turnMvAngTwd(pCam,
                                      D_ANG(3), 0, TURN_CLOSE_TO, true);
            }
            if (pPhase->hasArrivedFrameAt(60+30)) {
                //�J�����Ɍ������ĕ����]��2
                pLocoVehicle->turnMvAngTwd(pCam,
                                      D_ANG(1), 0, TURN_CLOSE_TO, true);
            }

            if (ABS(pCam->_x - _x) < PX_C(200) || pPhase->getFrame() >= 60+30+120) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_MOVE02: {
            if (pPhase->hasJustChanged()) {
            }
            addAlpha(-0.01);
            if (getAlpha() <= 0.0) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_LEAVE: {
            if (pPhase->hasJustChanged()) {
                sayonara();
                pPhase->changeNothing();
            }
            break;
        }
        default :
            break;
    }

    pLocoVehicle->behave();
}

SpriteLabelBonus001::~SpriteLabelBonus001() {
}

