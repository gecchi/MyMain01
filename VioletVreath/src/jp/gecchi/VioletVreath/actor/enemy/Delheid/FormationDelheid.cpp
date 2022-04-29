#include "FormationDelheid.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Alisana/EnemyAlisana.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/EnemyDelheid.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT  ,
    PHASE_ENTRY ,
    PHASE_FROMATION_MOVE1,
    PHASE_FROMATION_MOVE2,
    PHASE_FROMATION_MOVE3,
    PHASE_FROMATION_MOVE4,
    PHASE_FROMATION_MOVE5,
    PHASE_LEAVE ,
    PHASE_BANPEI,
};

FormationDelheid::FormationDelheid(const char* prm_name)
   : DepositoryFormation(prm_name) {
    _class_name = "FormationDelheid";

    RV_Num_           = 0;
    RV_MvVelo_        = 0;
    RV_LaunchInterval = 0;

    pAlisana_start = NEW EnemyAlisana("Alisana_START");
    pAlisana_start->inactivate(); //��������͔񊈓��Ȃ̂ŁA����� onInactive() �͔������܂���B
    appendGroupChild(pAlisana_start);

    pAlisana_goal = NEW EnemyAlisana("Alisana_GOAL");
    pAlisana_goal->inactivate();
    appendGroupChild(pAlisana_goal);

    //�O���v�Z�p�̃_�~�[
    pDummy_ = NEW EnemyDelheid("DammyEnemyDelheid");
    pDummy_->pVehicleLeader_ = nullptr;
    pDummy_->inactivate();
    appendGroupChild(pDummy_);

    //�ґ������f�|�W�g���Z�b�g
    pConn_pDelheidDepo_ = connectToDepositoryManager("EnemyDelheid4Formation");
    setFormationMember(pConn_pDelheidDepo_->peek());
    //�ґ������̃V���b�g�f�|�W�g��
    pConn_pShotDepo_ = connectToDepositoryManager("EnemyDelheidShot");
}

void FormationDelheid::initialize() {

}

void FormationDelheid::onActive() {
    RV_Num_           = RF_FormationDelheid_Num(G_RANK);    //�ґ���
    RV_MvVelo_        = RF_FormationDelheid_MvVelo(G_RANK); //���x
    RV_LaunchInterval = 64 / C_PX(RV_MvVelo_);
    getPhase()->reset(PHASE_INIT);
}

void FormationDelheid::processBehavior() {
    //pAlisana_start ���j�󂳂�Ă��邩�`�F�b�N
    if (pAlisana_start) {
        if (pAlisana_start->hasJustChangedToInactive()) {
            pAlisana_start = nullptr;
        }
    }
    //pAlisana_goal ���j�󂳂�Ă��邩�`�F�b�N
    if (pAlisana_goal) {
        if (pAlisana_goal->hasJustChangedToInactive()) {
            pAlisana_goal = nullptr;
        }
    }
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->get()) {
         case PHASE_INIT: {
             //�_�~�[(pDummy_)���g���ă����o�[�̃J�[�u�ړ��̊J�n�ʒu�ƕ����A�I���ʒu�ƕ�����\�ߋ��߂�
             pDummy_->config(getSplManuf(), nullptr);
             pDummy_->getVecVehicle()->setMvVelo(RV_MvVelo_);
             pDummy_->setPositionAt(&geoLocate_);
             pDummy_->setFaceAngAs(&geoLocate_);
             pDummy_->getVecVehicle()->setRzRyMvAng(geoLocate_.rz, geoLocate_.ry);
             onCalledUpDelheid(pDummy_);
             pDummy_->pVehicleLeader_->start(RELATIVE_COORD_DIRECTION); //���W�v�Z�̂��߃X�^�[�g���I�v�V�����w�肪�K�v
             coord next_x, next_y, next_z;             //�J�n+1 �̕⊮�_���W
             coord end_x, end_y, end_z;                //�ŏI�̕⊮�_���W
             coord end_prev_x, end_prev_y, end_prev_z; //�ŏI-1 �̕⊮�_���W
             pDummy_->pVehicleLeader_->getPointCoord(1, next_x, next_y, next_z);//[0] or [1] ���C������
             int ldr_point_num = pDummy_->pVehicleLeader_->getPointNum(); //�⊮�_�̐�
             pDummy_->pVehicleLeader_->getPointCoord(ldr_point_num-1, end_x, end_y, end_z);
             pDummy_->pVehicleLeader_->getPointCoord(ldr_point_num-2, end_prev_x, end_prev_y, end_prev_z);
             //�o���J�n�ʒu�A���T�i��z��
             pAlisana_start->setPositionAt(pDummy_);
             pAlisana_start->setFaceAngTwd(next_x, next_y, next_z); //�����Z�b�g
             pAlisana_start->acitve_open(); //�n�b�`�I�[�v��
             //�I���ʒu�ɃA���T�i��z��
             pAlisana_goal->setPosition(end_x, end_y, end_z);
             pAlisana_goal->setFaceAngTwd(end_prev_x, end_prev_y, end_prev_z);
             pAlisana_goal->acitve_open((frame)(pDummy_->pVehicleLeader_->getTotalDistance() / RV_MvVelo_)); //�n�b�`�I�[�v���\��

             pDummy_->sayonara(); //���肪�Ƃ��_�~�[
             pPhase->changeNext();
             break;
         }
         //�n�b�`�o�����I�[�v��
         case PHASE_ENTRY: {
             //�J�n�n�b�`�����݂��Ă��邩�ǂ���
             if (pAlisana_start) {
                 if (pAlisana_start->isOpenDone()) {
                     //�n�b�`�I�[�v�������܂ő҂�
                     pPhase->changeNext(); //����
                 }
             } else {
                 //�J�n�n�b�`���I�[�v���O�ɂ��ꂽ
                 calledUpMember(0); //�������W�ł��؂�
                 pPhase->changeNothing(); //�{�t�H�[���[�V�������̏I���I
             }
             //�n�b�`�I�[�v�������҂�
             break;
         }
         //�n�b�`����ґ������o�[�o��
         case PHASE_FROMATION_MOVE1: {
             if (pAlisana_start) {
                 //�J�n�n�b�`���I�[�v�������ݒ��̏ꍇ
                 if (canCalledUp()) {
                     //���W��������
                     if (pPhase->getFrame() % RV_LaunchInterval == 0) {
                         //�@�� RV_Num_ �@�܂ŏ��W
                         EnemyDelheid* pDelheid = (EnemyDelheid*)calledUpMember(RV_Num_);
                         if (pDelheid) {
                             pDelheid->config(getSplManuf(),
                                              pConn_pShotDepo_->peek() );
                             pDelheid->getVecVehicle()->forceMvVeloRange(RV_MvVelo_*2);
                             pDelheid->getVecVehicle()->setMvVelo(RV_MvVelo_);

                             pDelheid->getVecVehicle()->setMvAcce(0);
                             pDelheid->setPositionAt(&geoLocate_);
                             pDelheid->setFaceAngAs(&geoLocate_);
                             pDelheid->getVecVehicle()->setRzRyMvAng(geoLocate_.rz, geoLocate_.ry);
                             pDelheid->pVehicleLeader_->setStartAngle(geoLocate_.rx, geoLocate_.ry, geoLocate_.rz);
//                             pDelheid->pVehicleLeader_->setLoopAngleByMvAng();
                             onCalledUpDelheid(pDelheid); //���ʃt�H�[���[�V�����N���X�ʎ����̏���
                         } else {
                             //���W�����܂�
                         }
                     }
                 } else {
                     //���W���E��
                     pAlisana_start->close_sayonara();
                     pPhase->changeNext(); //�o���I���I
                 }
             } else {
                 //�J�n�n�b�`������(�����Ȃ���)�ꍇ
                 calledUpMember(0); //�������W�ł��؂�i�{�t�H�[���V�����I�u�W�F�N�g���������������Ƃ��ĕK�v�j
                 pPhase->changeNext(); //�o���I���I
             }
             break;
         }

         //�S�����o�[����
         case PHASE_FROMATION_MOVE2: {
             if (pPhase->hasJustChanged()) {
                 _listFollower.executeFunc(FormationDelheid::order1, this, nullptr, nullptr);
             }
             if (pPhase->hasArrivedFrameAt(120)) {
                 pPhase->changeNext();
             }

             break;
         }

         //�����o�[���&����
         case PHASE_FROMATION_MOVE3: {
             if (pPhase->hasJustChanged()) {
                 _listFollower.executeFunc(FormationDelheid::order2, this, nullptr, nullptr);
             }
             if (pPhase->hasArrivedFrameAt(360)) {
                 pPhase->changeNext(); //��؏I���I
             }
             break;
         }

         //�����o�[�Ďn��
         case PHASE_FROMATION_MOVE4: {
             if (pPhase->hasJustChanged()) {
                 _listFollower.executeFunc(FormationDelheid::order3, this, nullptr, nullptr);
             }
             if (pPhase->hasArrivedFrameAt(120)) {
                 pPhase->changeNext(); //�Ďn������
             }
             break;
         }

         //�ҋ@
         case PHASE_FROMATION_MOVE5: {
             if (pPhase->hasJustChanged()) {
             }
             //onSayonaraAll() �R�[���o�b�N�҂�
             break;
         }

//----------------------------------------------
         //�ґ������o�[�S�@�񊈓���(onSayonaraAll()��)
         case PHASE_LEAVE: {
             if (pPhase->hasJustChanged()) {
                  if (pAlisana_goal) {
                      pAlisana_goal->close_sayonara();
                  }
             }
             break;
         }

         default: {
             break;
         }
     }
}

void FormationDelheid::order1(GgafCore::Actor* prm_pDelheid, void* prm1, void* prm2, void* prm3) {
    //�e�����o�[����
    EnemyDelheid* pMember = (EnemyDelheid*)prm_pDelheid;
    FormationDelheid* pFormation = (FormationDelheid*)prm1;
    pMember->getVecVehicle()->setMvAcceByT(120, -(pFormation->RV_MvVelo_/8));
}

void FormationDelheid::order2(GgafCore::Actor* prm_pDelheid, void* prm1, void* prm2, void* prm3) {
    //�e�����o�[���&����
    EnemyDelheid* pMember = (EnemyDelheid*)prm_pDelheid;
    FormationDelheid* pFormation = (FormationDelheid*)prm1;
    pMember->getVecVehicle()->setMvAcce(0);
    pMember->open_shot(); //�V���b�g���ˁI
}

void FormationDelheid::order3(GgafCore::Actor* prm_pDelheid, void* prm1, void* prm2, void* prm3) {
    //�e�����o�[�Ďn��
    EnemyDelheid* pMember = (EnemyDelheid*)prm_pDelheid;
    FormationDelheid* pFormation = (FormationDelheid*)prm1;
    pMember->getVecVehicle()->setMvAcceByT(120, pFormation->RV_MvVelo_);
}

void FormationDelheid::onSayonaraAll() {
    //���̃R�[���o�b�N���Ăяo���ꂽ���_�ŁA�]���� FORMATION_END_DELAY �t���[���̂͂�
    _TRACE_(FUNC_NAME<<" �ł�");
    getPhase()->change(PHASE_LEAVE);
    //�����҂�
}

void FormationDelheid::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationDelheid::~FormationDelheid() {
    pConn_pShotDepo_->close();
    pConn_pDelheidDepo_->close();
}

