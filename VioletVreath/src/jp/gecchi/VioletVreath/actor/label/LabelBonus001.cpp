#include "LabelBonus001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_DISP ,
    PHASE_LEAVE ,
    PHASE_BANPEI,
};

LabelBonus001::LabelBonus001(const char* prm_name) :
        FontBoardActor(prm_name, "Ranking_16Font")
{
    _class_name = "LabelBonus001";
    //useZBufferDrawing(false);      //Z�o�b�t�@�͍l�������ɋ���
    //setZBufferWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ��ɋ���
    setSpecialRenderDepthIndex(1); //�`�揇�����őO�ʕ`��ɋ����B
    //setHitAble(false);
    //defineRotMvWorldMatrix(UTIL::setWorldMatrix_BxyzMv); //XYZ���r���{�[�h
    pOrgActor_ = nullptr;
}

void LabelBonus001::onCreateModel() {
}

void LabelBonus001::initialize() {
}

void LabelBonus001::onDispatched(GgafDx::GeometricActor* prm_pOrgActor) {
    pOrgActor_ = prm_pOrgActor;
    pOrgActor_->getViewPosition(_x, _y);
    getPhase()->reset(PHASE_INIT);
}

void LabelBonus001::processBehavior() {
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }
        case PHASE_DISP: {
            if (pPhase->hasArrivedFrameAt(300)) {
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
}

LabelBonus001::~LabelBonus001() {
}

