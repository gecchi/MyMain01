#include "FormationDelheid.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Alisana/EnemyAlisana.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/EnemyDelheid.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_ENTRY ,
    PROG_FROMATION_MOVE1,
    PROG_FROMATION_MOVE2,
    PROG_FROMATION_MOVE3,
    PROG_FROMATION_MOVE4,
    PROG_FROMATION_MOVE5,
    PROG_LEAVE ,
    PROG_BANPEI,
};

FormationDelheid::FormationDelheid(const char* prm_name)
   : DepositoryFormation(prm_name) {
    _class_name = "FormationDelheid";

    pAlisana_start = NEW EnemyAlisana("Alisana_START");
    pAlisana_start->inactivate(); //��������͔񊈓��Ȃ̂ŁA����� onInactive() �͔������܂���B
    appendGroupChild(pAlisana_start);

    pAlisana_goal = NEW EnemyAlisana("Alisana_GOAL");
    pAlisana_goal->inactivate();
    appendGroupChild(pAlisana_goal);

    //�O���v�Z�p�̃_�~�[
    pDummy_ = NEW EnemyDelheid("DammyEnemyDelheid");
    pDummy_->pDriverLeader_ = nullptr;
    pDummy_->inactivate();
    appendGroupChild(pDummy_);

    //�ґ������f�|�W�g���Z�b�g
    pConn_pDelheidDepo_ = connectToDepositoryManager("EnemyDelheid4Formation");
    setFormationMember(pConn_pDelheidDepo_->peek());
    //�ґ������̃V���b�g�f�|�W�g��
    pConn_pShotDepo_ = connectToDepositoryManager("EnemyDelheidShot");

    updateRankParameter();
}

void FormationDelheid::updateRankParameter() {
    RV_Num_           = RF_FormationDelheid_Num(G_RANK);    //�ґ���
    RV_MvVelo_        = RF_FormationDelheid_MvVelo(G_RANK); //���x
    RV_LaunchInterval = 64 / C_PX(RV_MvVelo_);
}

void FormationDelheid::initialize() {

}

void FormationDelheid::onActive() {
    updateRankParameter();
    getProgress()->reset(PROG_INIT);
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
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
         case PROG_INIT: {
             updateRankParameter();
             //�_�~�[(pDummy_)���g���ă����o�[�̃X�v���C���ړ��̊J�n�ʒu�ƕ����A�I���ʒu�ƕ�����\�ߋ��߂�
             pDummy_->config(getSplManuf()->createVecDriverLeader(pDummy_->getVecDriver()), nullptr);
             pDummy_->getVecDriver()->setMvVelo(RV_MvVelo_);
             pDummy_->setPositionAt(&geoLocate_);
             pDummy_->setFaceAngAs(&geoLocate_);
             pDummy_->getVecDriver()->setRzRyMvAng(geoLocate_.rz, geoLocate_.ry);
             onCallUpDelheid(pDummy_);
             pDummy_->pDriverLeader_->start(RELATIVE_COORD_DIRECTION); //���W�v�Z�̂��߃X�^�[�g���I�v�V�����w�肪�K�v
             coord next_x, next_y, next_z;             //�J�n+1 �̕⊮�_���W
             coord end_x, end_y, end_z;                //�ŏI�̕⊮�_���W
             coord end_prev_x, end_prev_y, end_prev_z; //�ŏI-1 �̕⊮�_���W
             pDummy_->pDriverLeader_->getPointCoord(1, next_x, next_y, next_z);//[0] or [1] ���C������
             int ldr_point_num = pDummy_->pDriverLeader_->getPointNum(); //�⊮�_�̐�
             pDummy_->pDriverLeader_->getPointCoord(ldr_point_num-1, end_x, end_y, end_z);
             pDummy_->pDriverLeader_->getPointCoord(ldr_point_num-2, end_prev_x, end_prev_y, end_prev_z);
             //�o���J�n�ʒu�A���T�i��z��
             pAlisana_start->setPositionAt(pDummy_);
             pAlisana_start->setFaceAngTwd(next_x, next_y, next_z); //�����Z�b�g
             pAlisana_start->acitve_open(); //�n�b�`�I�[�v��
             //�I���ʒu�ɃA���T�i��z��
             pAlisana_goal->setPosition(end_x, end_y, end_z);
             pAlisana_goal->setFaceAngTwd(end_prev_x, end_prev_y, end_prev_z);
             pAlisana_goal->acitve_open((frame)(pDummy_->pDriverLeader_->getTotalDistance() / RV_MvVelo_)); //�n�b�`�I�[�v���\��

             pDummy_->sayonara(); //���肪�Ƃ��_�~�[
             pProg->changeNext();
             break;
         }
         //�n�b�`�o�����I�[�v��
         case PROG_ENTRY: {
             //�J�n�n�b�`�����݂��Ă��邩�ǂ���
             if (pAlisana_start) {
                 if (pAlisana_start->isOpenDone()) {
                     //�n�b�`�I�[�v�������܂ő҂�
                     pProg->changeNext(); //����
                 }
             } else {
                 //�J�n�n�b�`���I�[�v���O�ɂ��ꂽ
                 callUpMember(0); //�������W�ł��؂�
                 pProg->changeNothing(); //�{�t�H�[���[�V�������̏I���I
             }
             //�n�b�`�I�[�v�������҂�
             break;
         }
         //�n�b�`����ґ������o�[�o��
         case PROG_FROMATION_MOVE1: {
             if (pAlisana_start) {
                 //�J�n�n�b�`���I�[�v�������ݒ��̏ꍇ
                 if (canCallUp()) {
                     //���W��������
                     if (pProg->getFrame() % RV_LaunchInterval == 0) {
                         //�@�� RV_Num_ �@�܂ŏ��W
                         EnemyDelheid* pDelheid = (EnemyDelheid*)callUpMember(RV_Num_);
                         if (pDelheid) {
                             pDelheid->config(getSplManuf()->createVecDriverLeader(pDelheid->getVecDriver()),
                                              pConn_pShotDepo_->peek() );
                             pDelheid->getVecDriver()->forceMvVeloRange(RV_MvVelo_*2);
                             pDelheid->getVecDriver()->setMvVelo(RV_MvVelo_);

                             pDelheid->getVecDriver()->setMvAcce(0);
                             pDelheid->setPositionAt(&geoLocate_);
                             pDelheid->setFaceAngAs(&geoLocate_);
                             pDelheid->getVecDriver()->setRzRyMvAng(geoLocate_.rz, geoLocate_.ry);
                             pDelheid->pDriverLeader_->setStartAngle(geoLocate_.rx, geoLocate_.ry, geoLocate_.rz);
//                             pDelheid->pDriverLeader_->setLoopAngleByMvAng();
                             onCallUpDelheid(pDelheid); //���ʃt�H�[���[�V�����N���X�ʎ����̏���
                         } else {
                             //���W�����܂�
                         }
                     }
                 } else {
                     //���W���E��
                     pAlisana_start->close_sayonara();
                     pProg->changeNext(); //�o���I���I
                 }
             } else {
                 //�J�n�n�b�`������(�����Ȃ���)�ꍇ
                 callUpMember(0); //�������W�ł��؂�i�{�t�H�[���V�����I�u�W�F�N�g���������������Ƃ��ĕK�v�j
                 pProg->changeNext(); //�o���I���I
             }
             break;
         }

         //�S�����o�[����
         case PROG_FROMATION_MOVE2: {
             if (pProg->hasJustChanged()) {
                 _listFollower.executeFunc(FormationDelheid::order1, this, nullptr, nullptr);
             }
             if (pProg->hasArrivedAt(120)) {
                 pProg->changeNext();
             }

             break;
         }

         //�����o�[���&����
         case PROG_FROMATION_MOVE3: {
             if (pProg->hasJustChanged()) {
                 _listFollower.executeFunc(FormationDelheid::order2, this, nullptr, nullptr);
             }
             if (pProg->hasArrivedAt(360)) {
                 pProg->changeNext(); //��؏I���I
             }
             break;
         }

         //�����o�[�Ďn��
         case PROG_FROMATION_MOVE4: {
             if (pProg->hasJustChanged()) {
                 _listFollower.executeFunc(FormationDelheid::order3, this, nullptr, nullptr);
             }
             if (pProg->hasArrivedAt(120)) {
                 pProg->changeNext(); //�Ďn������
             }
             break;
         }

         //�ҋ@
         case PROG_FROMATION_MOVE5: {
             if (pProg->hasJustChanged()) {
             }
             //onSayonaraAll() �R�[���o�b�N�҂�
             break;
         }

//----------------------------------------------
         //�ґ������o�[�S�@�񊈓���(onSayonaraAll()��)
         case PROG_LEAVE: {
             if (pProg->hasJustChanged()) {
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
    pMember->getVecDriver()->setMvAcceByT(120, -(pFormation->RV_MvVelo_/8));
}

void FormationDelheid::order2(GgafCore::Actor* prm_pDelheid, void* prm1, void* prm2, void* prm3) {
    //�e�����o�[���&����
    EnemyDelheid* pMember = (EnemyDelheid*)prm_pDelheid;
    FormationDelheid* pFormation = (FormationDelheid*)prm1;
    pMember->getVecDriver()->setMvAcce(0);
    pMember->open_shot(); //�V���b�g���ˁI
}

void FormationDelheid::order3(GgafCore::Actor* prm_pDelheid, void* prm1, void* prm2, void* prm3) {
    //�e�����o�[�Ďn��
    EnemyDelheid* pMember = (EnemyDelheid*)prm_pDelheid;
    FormationDelheid* pFormation = (FormationDelheid*)prm1;
    pMember->getVecDriver()->setMvAcceByT(120, pFormation->RV_MvVelo_);
}

void FormationDelheid::onSayonaraAll() {
    //���̃R�[���o�b�N���Ăяo���ꂽ���_�ŁA�]���� FORMATION_END_DELAY �t���[���̂͂�
    _TRACE_(FUNC_NAME<<" �ł�");
    getProgress()->change(PROG_LEAVE);
    //�����҂�
}

void FormationDelheid::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationDelheid::~FormationDelheid() {
    pConn_pShotDepo_->close();
    pConn_pDelheidDepo_->close();
}

