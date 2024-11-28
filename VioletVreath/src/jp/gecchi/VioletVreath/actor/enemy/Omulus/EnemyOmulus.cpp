#include "EnemyOmulus.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

enum {
    PHASE_INIT       ,
    PHASE_HATCH_CLOSE,
    PHASE_HATCH_OPEN ,
    PHASE_BANPEI,
};

EnemyOmulus::EnemyOmulus(const char* prm_name) :
        VvEnemyActor<DefaultMassMorphMeshActor>(prm_name, "Omulus", StatusReset(EnemyOmulus)) {
    _class_name = "EnemyOmulus";
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 20*60;
    frame_of_morph_interval_ = 120;

    pDepo_Fired_ = nullptr;
    pConn_depo_ = connectToDepositoryManager("Talante");
}

void EnemyOmulus::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
    pModel->setSpecular(5.0, 1.0);
}

void EnemyOmulus::initialize() {
    setHitAble(true);
    getLocusVehicle()->linkFaceAngByMvAng(true);
    getMorpher()->setRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 200000);
    setScale(1000);
    getScaler()->setRange(1000, 1200);
    getScaler()->beat(30, 5, 0, 20, -1);
    pDepo_Fired_ = pConn_depo_->peek();
}

void EnemyOmulus::onActive() {
    getStatus()->reset();
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
//    frame_of_moment_nextopen_ = frame_of_close_interval_;
    getPhase()->reset(PHASE_HATCH_CLOSE);
}

void EnemyOmulus::processBehavior() {
    //���[�J���Ōv�Z���s��
    changeGeoLocal();

    //�{�[���ɂ�����A�N�^�[�̃���
    //_x, _y, _z, _rx, _ry, _rz �ɂ��ĂQ�̍��W�n�Z�b�g��؂�ւ����K�v�Ȏd�l�ł��B
    //���ꂼ�ꃍ�[�J�����W�A�ŏI�i��΁j���W�ƌĂԂ��Ƃɂ��܂��B
    //�E�ŏI�i��΁j���W �E�E�E ���ʂ̃��[���h���W�n�̎��ł��B
    //�E���[�J�����W     �E�E�E �e�A�N�^�[�̊�_(0,0,0)����̑��ΓI�ȍ��W�n���Ӗ����܂��B
    //                          ���W�v�Z�͂�����ōs���ĉ������B
    //�����j��
    //  �@���W�v�Z�͎�Ƀ��[�J�����W�n�̌v�Z�ł���BGgafDx::LocusVehicle �Ń��[�J�����W�n�̑�����s�����ƂƂ���B
    //    �������A�����ؓo�^��A�����蔻���A�^�[�Q�b�g���W�ȂǁA���̃I�u�W�F�N�g���烏�[���h���W���Q�Ƃ��铙�A
    //    ��{��Ԃ͍ŏI�i��΁j���W�n�B
    //    processBehavior()�J�n���� �ŏI�i��΁j���W�n(changeGeoFinal())�̏�ԂƂȂ��Ă���B
    //  �AprocessBehavior()���ŕK�v�ɉ����� changeGeoLocal() �Ń����o�[ _x, _y, _z, _rx, _ry, _rz �����[�J�����W�n��
    //    �؂�ւ��邱�Ƃ��\�B�ړ����̍��W�v�Z���s���B
    //  �B�A�� processBehavior() �𔲂���ۂɂ͕K���ŏI���W(changeGeoFinal())�̏�Ԃɖ߂��Ă������B
    //  �C�ŏI�i��΁j���W�ƁA���[�J�����W�݂͌��ɓƗ����A���͂��Ȃ����A
    //    �\�����̃��[���h�ϊ��s��쐬���A�s��ςō�������A�ŏI�I�ȕ\���ʒu�����肷��B

    //��changeGeoLocal(); ���s����
    //���[�J�����W�n�ɐؑւ��܂��B
    //�E_x, _y, _z     �E�E�E �́A���[�J�����W���Ӗ�����悤�ɂȂ�܂��B
    //                        changeGeoLocal(); �����s����Ǝ����I��_x, _y, _z ��
    //                        ���[�J�����W�l�ɐ؂�ւ��܂��B
    //�E_rx, _ry, _rz  �E�E�E �́A���[�J�����W�ł̎���]�l���Ӗ�����悤�ɂȂ�܂��B
    //                        changeGeoLocal(); �����s����Ǝ����I��_rx, _ry, _rz��
    //                        ���[�J�����W����]�l�ɐ؂�ւ��܂��B

    //��changeGeoFinal(); ���s����
    //�ŏI�i��΁j���W�n�ɐ؂�ւ��܂��B
    //�E_x, _y, _z    �E�E�E ���t���[�� GgafDx::GeometricActor::processSettlementBehavior() �Ōv�Z���ꎩ���X�V����Ă܂��B
    //                       processBehavior() �� changeGeoFinal() ���s���ƁA�P�t���[���O��_x, _y, _z�ɐ؂�ւ�鎖�ɂȂ�܂��B
    //                       _x, _y, _z �͎Q�Ɛ�p�B�l�������Ă��Ӗ����L��܂���
    //�E_rx, _ry, _rz �E�E�E ���t���[�� GgafDx::GeometricActor::processSettlementBehavior() �����������܂���I
    //                       changeGeoFinal(); �����s���Ă��A_rx, _ry, _rz �͈ȑO�̍ŏI�i��΁j���W�n�̒l��
    //                       ������ςȂ��ŕω����܂���B
    //                       ���̃I�u�W�F�N�g����A�{�[���ɂ�����A�N�^�[���Q�Ƃ���Ƃ��A_rx, _ry, _rz�͑S���M�p�ł��܂���B

    //�����Ӂ�
    //�EGgafDx::LocusVehicle(getLocusVehicle())�� behave() �ȊO���\�b�h�́A��Ƀ��[�J�����W�̑���Ƃ���B
    //  behave()�ȊO���\�b�h�͎��ۂɍ��W�v�Z���Ă���킯�ł͂Ȃ��̂ŁA
    //  changeGeoFinal()���AchangeGeoLocal()���Ɋ֌W�Ȃ��A�Ăяo���\�B
    //�EGgafDx::LocusVehicle(getLocusVehicle())�� behave() ���\�b�h�͍��W���P�t���[����̏�Ԃɂ���v�Z���s���B
    //  ���������āA���̂悤�� ���[�J�����W��(changeGeoLocal()��)�ŌĂяo�����Ƃ���B
    //    changeGeoLocal();
    //    pLocusVehicle->behave();
    //    changeGeoFinal();
    //TODO:���݊��������ƂȂ����B
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_HATCH_CLOSE);
            break;
        }
        case PHASE_HATCH_CLOSE: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MORPHTARGET_HATCH_OPEN,
                                                0.0f, frame_of_morph_interval_);
                pLocusVehicle->setRollFaceAngVelo(-3000);
            }

            //����
            if (pPhase->getFrame() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                pPhase->change(PHASE_HATCH_OPEN);
            }
            break;
        }
        case PHASE_HATCH_OPEN: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MORPHTARGET_HATCH_OPEN,
                                           1.0f, frame_of_morph_interval_);
                pLocusVehicle->setRollFaceAngVelo(0);
            }
            //processJudgement()�ŃV���b�g����
            if (pPhase->getFrame() >= frame_of_open_interval_+ frame_of_morph_interval_) {
                pPhase->change(PHASE_HATCH_CLOSE);
            }
            break;
        }
        default :
            break;
    }

    getScaler()->behave();
    getMorpher()->behave();

    pLocusVehicle->behave();
    changeGeoFinal();
}

void EnemyOmulus::processChangeGeoFinal() {
    //��΍��W���X�V����Ă���`
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_HATCH_OPEN: {
            //�I�[�v�����G�o������
            if (getMorphWeight(MORPHTARGET_HATCH_OPEN) > 0.5) { //���[�V�����������ȏ�܂œ��B�����Ȃ�
                if (pPhase->getFrame() % (frame)(RF_EnemyOmulus_ShotInterval(G_RANK)) == 0) { //�o���Ԋu
                    if (pDepo_Fired_) {
                        GgafDx::FigureActor* pActor = (GgafDx::FigureActor*)pDepo_Fired_->dispatch();
                        if (pActor) {
                            pActor->getLocusVehicle()->setRzRyMvAng(_rz, _ry); //��΍��W�n�ł̌���
                            pActor->setPosition(_x, _y, _z);
                            pActor->reset();
                        }
                    }
                }
            }
            break;
        }
        default :
            break;
    }
}

void EnemyOmulus::processJudgement() {
    if (getBaseActor() && getBaseActor()->isActiveInTheTree()) {
//        (*(_pActor_base->_pFunc_calc_rot_mv_world_matrix))(_pActor_base, _matWorld);
    } else {
        //�y�䂪�Ȃ���Ύ���������
        sayonara();
    }


//    if (isOutOfSpacetime()) {
//        sayonara();
//    }
}

void EnemyOmulus::onInactive() {
    sayonara();
}

EnemyOmulus::~EnemyOmulus() {
    pConn_depo_->close();
}
