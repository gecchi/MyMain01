#include "stdafx.h"
#include "FormationAdelheid.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Palisana/EnemyPalisana.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Adelheid/EnemyAdelheid.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


FormationAdelheid::FormationAdelheid(const char* prm_name)
   : DepositoryFormation(prm_name) {
    _class_name = "FormationAdelheid";

    pPalisana_start = NEW EnemyPalisana("Palisana_START");
    pPalisana_start->inactivateImmed();
    addSubGroup(pPalisana_start);

    pPalisana_goal = NEW EnemyPalisana("Palisana_GOAL");
    pPalisana_goal->inactivateImmed();
    addSubGroup(pPalisana_goal);

    //�O���v�Z�p�̃_�~�[
    pDummy_ = NEW EnemyAdelheid("DammyEnemyAdelheid");
    pDummy_->pKurokoLeader_ = nullptr;
    pDummy_->inactivateImmed();
    addSubGroup(pDummy_);

    //�ґ������f�|�W�g���Z�b�g
    pConn_AdelheidDepo_ = connect_DepositoryManager("EnemyAdelheid4Formation");
    setFormationMember(pConn_AdelheidDepo_->peek());
    //�ґ������̃V���b�g�f�|�W�g��
    pConn_ShotDepo_ = connect_DepositoryManager("EnemyAdelheidShot");

    updateRankParameter();
    useProgress(PROG_LEAVE);
}

void FormationAdelheid::updateRankParameter() {
    RV_NumFormation_     = RF_FormationAdelheid_Num(G_RANK);    //�ґ���
    RV_MvVelo_           = RF_FormationAdelheid_MvVelo(G_RANK); //���x
    RV_IntervalFrames_   = 64 / C_PX(RV_MvVelo_);
}

void FormationAdelheid::initialize() {

}

void FormationAdelheid::onActive() {
    updateRankParameter();
    _pProg->reset(PROG_INIT);
}

void FormationAdelheid::processBehavior() {
    //pPalisana_start ���j�󂳂�Ă��邩�`�F�b�N
    if (pPalisana_start) {
        if (pPalisana_start->onChangeToInactive()) {
            pPalisana_start = nullptr;
        }
    }
    //pPalisana_goal ���j�󂳂�Ă��邩�`�F�b�N
    if (pPalisana_goal) {
        if (pPalisana_goal->onChangeToInactive()) {
            pPalisana_goal = nullptr;
        }
    }

    switch (_pProg->get()) {
         case PROG_INIT: {
             updateRankParameter();
             //�_�~�[(pDummy_)���g���ă����o�[�̃X�v���C���ړ��̊J�n�ʒu�ƕ����A�I���ʒu�ƕ�����\�ߋ��߂�
             pDummy_->config(getSplManuf()->createKurokoLeader(pDummy_->_pKurokoA), nullptr);
             pDummy_->_pKurokoA->setMvVelo(RV_MvVelo_);
             onCallUpAdelheid(pDummy_); //�����o�[(Adelheid)�̃t�H�[���[�V�����J�n���W�ƕ����𓾂�
             pDummy_->pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //���W�v�Z�̂��߃X�^�[�g���I�v�V�����w�肪�K�v
             coord next_X, next_Y, next_Z;             //�J�n+1 �̕⊮�_���W
             coord end_X, end_Y, end_Z;                //�ŏI�̕⊮�_���W
             coord end_prev_X, end_prev_Y, end_prev_Z; //�ŏI-1 �̕⊮�_���W
             pDummy_->pKurokoLeader_->getPointCoord(1, next_X, next_Y, next_Z);//[0] or [1] ���C������
             int spl_point_num = pDummy_->pKurokoLeader_->getPointNum(); //�⊮�_�̐�
             pDummy_->pKurokoLeader_->getPointCoord(spl_point_num-1, end_X, end_Y, end_Z);
             pDummy_->pKurokoLeader_->getPointCoord(spl_point_num-2, end_prev_X, end_prev_Y, end_prev_Z);
             //�o���J�n�ʒu�p���T�i��z��
             pPalisana_start->positionAs(pDummy_);
             pPalisana_start->_pKurokoA->setFaceAngTwd(next_X, next_Y, next_Z); //�����Z�b�g
             pPalisana_start->acitve_open(); //�n�b�`�I�[�v��
             //�I���ʒu�Ƀp���T�i��z��
             pPalisana_goal->position(end_X, end_Y, end_Z);
             pPalisana_goal->_pKurokoA->setFaceAngTwd(end_prev_X, end_prev_Y, end_prev_Z);
             pPalisana_goal->acitve_open((frame)(pDummy_->pKurokoLeader_->getTotalDistance() / RV_MvVelo_)); //�n�b�`�I�[�v���\��

             pDummy_->sayonara(); //���肪�Ƃ��_�~�[
             _pProg->changeNext();
             break;
         }
         //�n�b�`�o�����I�[�v��
         case PROG_ENTRY: {
             //�J�n�n�b�`�����݂��Ă��邩�ǂ���
             if (pPalisana_start) {
                 if (pPalisana_start->isOpenDone()) {
                     //�n�b�`�I�[�v�������܂ő҂�
                     _pProg->changeNext(); //����
                 }
             } else {
                 //�J�n�n�b�`���I�[�v���O�ɂ��ꂽ
                 callUpMember(0); //�������W�ł��؂�
                 _pProg->changeNothing(); //�{�t�H�[���[�V�������̏I���I
             }
             //�n�b�`�I�[�v�������҂�
             break;
         }
         //�n�b�`����ґ������o�[�o��
         case PROG_FROMATION_MOVE1: {
             if (pPalisana_start) {
                 //�J�n�n�b�`���I�[�v�������ݒ��̏ꍇ
                 if (canCallUp()) {
                     //���W��������
                     if (_pProg->getFrameInProgress() % RV_IntervalFrames_ == 0) {
                         //�@�� RV_NumFormation_ �@�܂ŏ��W
                         EnemyAdelheid* pAdelheid = (EnemyAdelheid*)callUpMember(RV_NumFormation_);
                         if (pAdelheid) {
                             pAdelheid->config(getSplManuf()->createKurokoLeader(pAdelheid->_pKurokoA),
                                               pConn_ShotDepo_->peek() );
                             pAdelheid->_pKurokoA->forceMvVeloRange(RV_MvVelo_*2);
                             pAdelheid->_pKurokoA->setMvVelo(RV_MvVelo_);

                             pAdelheid->_pKurokoA->setMvAcce(0);
                             onCallUpAdelheid(pAdelheid); //���ʃt�H�[���[�V�����N���X�ʎ����̏���
                         } else {
                             //���W�����܂�
                         }
                     }
                 } else {
                     //���W���E��
                     pPalisana_start->close_sayonara();
                     _pProg->changeNext(); //�o���I���I
                 }
             } else {
                 //�J�n�n�b�`������(�����Ȃ���)�ꍇ
                 callUpMember(0); //�������W�ł��؂�i�{�t�H�[���V�����I�u�W�F�N�g���������������Ƃ��ĕK�v�j
                 _pProg->changeNext(); //�o���I���I
             }
             break;
         }

         //�S�����o�[����
         case PROG_FROMATION_MOVE2: {
             if (_pProg->isJustChanged()) {
                 _listFollower.executeFunc(FormationAdelheid::order1, this, nullptr);
             }
             if (_pProg->getFrameInProgress() == 120) {
                 _pProg->changeNext();
             }

             break;
         }

         //�����o�[���&����
         case PROG_FROMATION_MOVE3: {
             if (_pProg->isJustChanged()) {
                 _listFollower.executeFunc(FormationAdelheid::order2, this, nullptr);
             }
             if (_pProg->getFrameInProgress() == 360) {
                 _pProg->changeNext(); //��؏I���I
             }
             break;
         }

         //�����o�[�Ďn��
         case PROG_FROMATION_MOVE4: {
             if (_pProg->isJustChanged()) {
                 _listFollower.executeFunc(FormationAdelheid::order3, this, nullptr);
             }
             if (_pProg->getFrameInProgress() == 120) {
                 _pProg->changeNext(); //�Ďn������
             }
             break;
         }

         //�ҋ@
         case PROG_FROMATION_MOVE5: {
             if (_pProg->isJustChanged()) {
             }
             //onSayonaraAll() �R�[���o�b�N�҂�
             break;
         }

//----------------------------------------------
         //�ґ������o�[�S�@�񊈓���(onSayonaraAll()��)
         case PROG_LEAVE: {
             if (_pProg->isJustChanged()) {
                  if (pPalisana_goal) {
                      pPalisana_goal->close_sayonara();
                  }
             }
             break;
         }

         default:
             break;
     }
}

void FormationAdelheid::order1(GgafCore::GgafActor* prm_pAdelheid, void* prm1, void* prm2) {
    //�e�����o�[����
    EnemyAdelheid* pMember = (EnemyAdelheid*)prm_pAdelheid;
    FormationAdelheid* pFormation = (FormationAdelheid*)prm1;
    pMember->_pKurokoA->setMvAcceByT(120, -(pFormation->RV_MvVelo_/8));
}

void FormationAdelheid::order2(GgafCore::GgafActor* prm_pAdelheid, void* prm1, void* prm2) {
    //�e�����o�[���&����
    EnemyAdelheid* pMember = (EnemyAdelheid*)prm_pAdelheid;
    FormationAdelheid* pFormation = (FormationAdelheid*)prm1;
    pMember->_pKurokoA->setMvAcce(0);
    pMember->open_shot(); //�V���b�g���ˁI
}

void FormationAdelheid::order3(GgafCore::GgafActor* prm_pAdelheid, void* prm1, void* prm2) {
    //�e�����o�[�Ďn��
    EnemyAdelheid* pMember = (EnemyAdelheid*)prm_pAdelheid;
    FormationAdelheid* pFormation = (FormationAdelheid*)prm1;
    pMember->_pKurokoA->setMvAcceByT(120, pFormation->RV_MvVelo_);
}

void FormationAdelheid::onSayonaraAll() {
    //���̃R�[���o�b�N���Ăяo���ꂽ���_�ŁA�]���� FORMATION_END_DELAY �t���[���̂͂�
    _TRACE_("FormationAdelheid::onSayonaraAll() �ł�");
    _pProg->change(PROG_LEAVE);
    //�����҂�
}

void FormationAdelheid::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationAdelheid::~FormationAdelheid() {
    pConn_ShotDepo_->close();
    pConn_AdelheidDepo_->close();
}

