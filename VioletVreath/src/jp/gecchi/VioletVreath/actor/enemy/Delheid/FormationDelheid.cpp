#include "stdafx.h"
#include "FormationDelheid.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Alisana/EnemyAlisana.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/EnemyDelheid.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


FormationDelheid::FormationDelheid(const char* prm_name)
   : DepositoryFormation(prm_name) {
    _class_name = "FormationDelheid";

    pAlisana_start = NEW EnemyAlisana("Alisana_START");
    pAlisana_start->inactivateImmed();
    addSubGroup(pAlisana_start);

    pAlisana_goal = NEW EnemyAlisana("Alisana_GOAL");
    pAlisana_goal->inactivateImmed();
    addSubGroup(pAlisana_goal);

    //�O���v�Z�p�̃_�~�[
    pDummy_ = NEW EnemyDelheid("DammyEnemyDelheid");
    pDummy_->pKurokoLeader_ = nullptr;
    pDummy_->inactivateImmed();
    addSubGroup(pDummy_);

    //�ґ������f�|�W�g���Z�b�g
    pConn_DelheidDepo_ = connect_DepositoryManager("EnemyDelheid4Formation");
    setFormationMember(pConn_DelheidDepo_->peek());
    //�ґ������̃V���b�g�f�|�W�g��
    pConn_ShotDepo_ = connect_DepositoryManager("EnemyDelheidShot");

    updateRankParameter();
    useProgress(_BANPEI_-1);
}

void FormationDelheid::updateRankParameter() {
    RV_NumFormation_     = RF_FormationDelheid_Num(G_RANK);    //�ґ���
    RV_MvVelo_           = RF_FormationDelheid_MvVelo(G_RANK); //���x
    RV_IntervalFrames_   = 64 / C_PX(RV_MvVelo_);
}

void FormationDelheid::initialize() {

}

void FormationDelheid::onActive() {
    updateRankParameter();
    _pProg->reset(PROG_INIT);
}

void FormationDelheid::processBehavior() {
    //pAlisana_start ���j�󂳂�Ă��邩�`�F�b�N
    if (pAlisana_start) {
        if (pAlisana_start->onChangeToInactive()) {
            pAlisana_start = nullptr;
        }
    }
    //pAlisana_goal ���j�󂳂�Ă��邩�`�F�b�N
    if (pAlisana_goal) {
        if (pAlisana_goal->onChangeToInactive()) {
            pAlisana_goal = nullptr;
        }
    }

    switch (_pProg->get()) {
         case PROG_INIT: {
             updateRankParameter();
             //�_�~�[(pDummy_)���g���ă����o�[�̃X�v���C���ړ��̊J�n�ʒu�ƕ����A�I���ʒu�ƕ�����\�ߋ��߂�
             pDummy_->config(getSplManuf()->createKurokoLeader(pDummy_->_pKurokoA), nullptr);
             pDummy_->_pKurokoA->setMvVelo(RV_MvVelo_);
             onCallUpDelheid(pDummy_); //�����o�[(Delheid)�̃t�H�[���[�V�����J�n���W�ƕ����𓾂�
             pDummy_->pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //���W�v�Z�̂��߃X�^�[�g���I�v�V�����w�肪�K�v
             coord next_x, next_y, next_z;             //�J�n+1 �̕⊮�_���W
             coord end_x, end_y, end_z;                //�ŏI�̕⊮�_���W
             coord end_prev_x, end_prev_y, end_prev_z; //�ŏI-1 �̕⊮�_���W
             pDummy_->pKurokoLeader_->getPointCoord(1, next_x, next_y, next_z);//[0] or [1] ���C������
             int spl_point_num = pDummy_->pKurokoLeader_->getPointNum(); //�⊮�_�̐�
             pDummy_->pKurokoLeader_->getPointCoord(spl_point_num-1, end_x, end_y, end_z);
             pDummy_->pKurokoLeader_->getPointCoord(spl_point_num-2, end_prev_x, end_prev_y, end_prev_z);
             //�o���J�n�ʒu�A���T�i��z��
             pAlisana_start->positionAs(pDummy_);
             pAlisana_start->_pKurokoA->setFaceAngTwd(next_x, next_y, next_z); //�����Z�b�g
             pAlisana_start->acitve_open(); //�n�b�`�I�[�v��
             //�I���ʒu�ɃA���T�i��z��
             pAlisana_goal->position(end_x, end_y, end_z);
             pAlisana_goal->_pKurokoA->setFaceAngTwd(end_prev_x, end_prev_y, end_prev_z);
             pAlisana_goal->acitve_open((frame)(pDummy_->pKurokoLeader_->getTotalDistance() / RV_MvVelo_)); //�n�b�`�I�[�v���\��

             pDummy_->sayonara(); //���肪�Ƃ��_�~�[
             _pProg->changeNext();
             break;
         }
         //�n�b�`�o�����I�[�v��
         case PROG_ENTRY: {
             //�J�n�n�b�`�����݂��Ă��邩�ǂ���
             if (pAlisana_start) {
                 if (pAlisana_start->isOpenDone()) {
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
             if (pAlisana_start) {
                 //�J�n�n�b�`���I�[�v�������ݒ��̏ꍇ
                 if (canCallUp()) {
                     //���W��������
                     if (_pProg->getFrameInProgress() % RV_IntervalFrames_ == 0) {
                         //�@�� RV_NumFormation_ �@�܂ŏ��W
                         EnemyDelheid* pDelheid = (EnemyDelheid*)callUpMember(RV_NumFormation_);
                         if (pDelheid) {
                             pDelheid->config(getSplManuf()->createKurokoLeader(pDelheid->_pKurokoA),
                                               pConn_ShotDepo_->peek() );
                             pDelheid->_pKurokoA->forceMvVeloRange(RV_MvVelo_*2);
                             pDelheid->_pKurokoA->setMvVelo(RV_MvVelo_);

                             pDelheid->_pKurokoA->setMvAcce(0);
                             onCallUpDelheid(pDelheid); //���ʃt�H�[���[�V�����N���X�ʎ����̏���
                         } else {
                             //���W�����܂�
                         }
                     }
                 } else {
                     //���W���E��
                     pAlisana_start->close_sayonara();
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
                 _listFollower.executeFunc(FormationDelheid::order1, this, nullptr);
             }
             if (_pProg->getFrameInProgress() == 120) {
                 _pProg->changeNext();
             }

             break;
         }

         //�����o�[���&����
         case PROG_FROMATION_MOVE3: {
             if (_pProg->isJustChanged()) {
                 _listFollower.executeFunc(FormationDelheid::order2, this, nullptr);
             }
             if (_pProg->getFrameInProgress() == 360) {
                 _pProg->changeNext(); //��؏I���I
             }
             break;
         }

         //�����o�[�Ďn��
         case PROG_FROMATION_MOVE4: {
             if (_pProg->isJustChanged()) {
                 _listFollower.executeFunc(FormationDelheid::order3, this, nullptr);
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
                  if (pAlisana_goal) {
                      pAlisana_goal->close_sayonara();
                  }
             }
             break;
         }

         default:
             break;
     }
}

void FormationDelheid::order1(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2) {
    //�e�����o�[����
    EnemyDelheid* pMember = (EnemyDelheid*)prm_pDelheid;
    FormationDelheid* pFormation = (FormationDelheid*)prm1;
    pMember->_pKurokoA->setMvAcceByT(120, -(pFormation->RV_MvVelo_/8));
}

void FormationDelheid::order2(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2) {
    //�e�����o�[���&����
    EnemyDelheid* pMember = (EnemyDelheid*)prm_pDelheid;
    FormationDelheid* pFormation = (FormationDelheid*)prm1;
    pMember->_pKurokoA->setMvAcce(0);
    pMember->open_shot(); //�V���b�g���ˁI
}

void FormationDelheid::order3(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2) {
    //�e�����o�[�Ďn��
    EnemyDelheid* pMember = (EnemyDelheid*)prm_pDelheid;
    FormationDelheid* pFormation = (FormationDelheid*)prm1;
    pMember->_pKurokoA->setMvAcceByT(120, pFormation->RV_MvVelo_);
}

void FormationDelheid::onSayonaraAll() {
    //���̃R�[���o�b�N���Ăяo���ꂽ���_�ŁA�]���� FORMATION_END_DELAY �t���[���̂͂�
    _TRACE_("FormationDelheid::onSayonaraAll() �ł�");
    _pProg->change(PROG_LEAVE);
    //�����҂�
}

void FormationDelheid::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationDelheid::~FormationDelheid() {
    pConn_ShotDepo_->close();
    pConn_DelheidDepo_->close();
}

