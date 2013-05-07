#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


FormationAdelheid::FormationAdelheid(const char* prm_name)
   : DepositoryFormation(prm_name) {
    _class_name = "FormationAdelheid";

    pPalisana_start = NEW EnemyPalisana("Palisana1");
    pPalisana_start->inactivateImmed();
    addSubGroup(pPalisana_start);

    pPalisana_goal = NEW EnemyPalisana("Palisana2");
    pPalisana_goal->inactivateImmed();
    addSubGroup(pPalisana_goal);

    //�O���v�Z�p�̃_�~�[
    pDummy_ = NEW EnemyAdelheid("DammyEnemyAdelheid");;
    pDummy_->inactivateImmed();
    addSubGroup(pDummy_);

    //�ґ������f�|�W�g���Z�b�g
    pConnection_AdelheidDepo_ = connectToDepositoryManager("EnemyAdelheid4Formation");
    setFormationMemberDepo(pConnection_AdelheidDepo_->peek());

    pConnection_ShotDepo_ = connectToDepositoryManager("EnemyAdelheidShot");

    updateRankParameter();


    useProgress(PROG_LEAVE);
}

void FormationAdelheid::updateRankParameter() {
    rr_num_formation_     = 1; //RR_FormationAdelheid_Num(_RANK_);            //�ґ���
    rr_interval_frames_   = 12;
    rr_mv_velo_           = PX_C(8); //RR_FormationAdelheid_MvVelo(_RANK_);         //���x
}

void FormationAdelheid::initialize() {

}

void FormationAdelheid::onActive() {
    updateRankParameter();
    _pProg->reset(PROG_INIT);
}

void FormationAdelheid::processBehavior() {

    switch (_pProg->get()) {
         case PROG_INIT: {
             _TRACE_("FormationAdelheid::processBehavior() PROG_INIT ���[");

             //�ŏ��̈�@
             pDummy_->config(getSplManuf()->createKurokoLeader(pDummy_->_pKurokoA),
                                     pConnection_ShotDepo_->peek());
             pDummy_->_pKurokoA->setMvVelo(rr_mv_velo_);
             onCallUpAdelheid(pDummy_); //���ʃt�H�[���[�V�����N���X�ʎ����̏���
                                        //�J�n���W�ƕ�������܂�
             pDummy_->pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //���W�v�Z�̂��߃X�^�[�g���I�v�V�����w��
                                                                                     //�I�v�V������EnemyAdelheid�ƍ��킹�邱��
             //�o���J�n�ʒu��pPalisana_start�z��
             pPalisana_start->locateAs(pDummy_);
             coord next_X, next_Y, next_Z;
             pDummy_->pKurokoLeader_->getPointCoord(1, next_X, next_Y, next_Z);//[0] or [1] ���C������
             pPalisana_start->_pKurokoA->setFaceAngTwd(next_X, next_Y, next_Z); //�����Z�b�g
             pPalisana_start->acitve_open(); //�L�����n�b�`�I�[�v��
             //�o���I���ʒu�ƁA���p�����߁A�o���I���ʒu��pPalisana_goal�z��
             coord end_X, end_Y, end_Z;
             coord end_prev_X, end_prev_Y, end_prev_Z;
             int spl_point_num = pDummy_->pKurokoLeader_->getPointNum();
             pDummy_->pKurokoLeader_->getPointCoord(spl_point_num-1,
                                                    end_X, end_Y, end_Z); //�ŏI�⊮�_���W
             pDummy_->pKurokoLeader_->getPointCoord(spl_point_num-2,
                                                    end_prev_X, end_prev_Y, end_prev_Z);  //�ŏI-1 �⊮�_���W
             pPalisana_goal->locate(end_X, end_Y, end_Z);
             pPalisana_goal->_pKurokoA->setFaceAngTwd(end_prev_X, end_prev_Y, end_prev_Z);
             pPalisana_goal->acitve_open(
                               (frame)(pDummy_->pKurokoLeader_->getTotalDistance() / rr_mv_velo_)
                             ); //�x��ăn�b�`�I�[�v��

             pDummy_->sayonara(); //���肪�Ƃ��_�~�[
             _pProg->changeNext();
             _TRACE_("FormationAdelheid::processBehavior() PROG_INIT OK ���[");
             break;
         }

         case PROG_ENTRY: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_ENTRY ���[");
             }
             if (pPalisana_start->isOpenDone()) {
                 //�n�b�`�I�[�v������
                 _pProg->changeNext();
             }
             //�n�b�`�I�[�v����
             break;
         }

         case PROG_FROMATION_MOVE1: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_FROMATION_MOVE1 ���[");
             }
             if (canCallUp() && (_pProg->getFrameInProgress() % rr_interval_frames_ == 0)) {
                 //�Q�@�ڈȍ~
                 EnemyAdelheid* pAdelheid = (EnemyAdelheid*)callUpMember(rr_num_formation_);
                 if (pAdelheid) {
                     SplineKurokoLeader* pKurokoLeader =
                             getSplManuf()->createKurokoLeader(pAdelheid->_pKurokoA);
                     pAdelheid->config(pKurokoLeader, pConnection_ShotDepo_->peek());
                     pAdelheid->_pKurokoA->setMvVelo(rr_mv_velo_);
                     onCallUpAdelheid(pAdelheid); //���ʃt�H�[���[�V�����N���X�ʎ����̏���
                 } else {
                     _pProg->changeNext(); //�K�萔�o���I��
                 }
             }
             break;
         }

         case PROG_FROMATION_MOVE2: {
            if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_FROMATION_MOVE2 ���[");
             }
             //�R�[���o�b�N processOnSayonar() ���N����܂ő҂B
             break;
         }

         case PROG_LEAVE: {
             if (_pProg->isJustChanged()) {
                  _TRACE_("FormationAdelheid::processBehavior() PROG_LEAVE ���[");
                 pPalisana_start->close_sayonara();
                 pPalisana_goal->close_sayonara();
             }
             if (_pProg->getFrameInProgress() == 15) {
                 setHitAble(false);
             }
             break;
         }
         default:
             break;
     }
}

void FormationAdelheid::onSayonaraAll() {
    //�]���� FORMATION_END_DELAY �t���[��
    //����ȓ��ɕ���A�j���[�V�������I��点�܂��傤
    _TRACE_("FormationAdelheid::onSayonaraAll() ���[");
    _pProg->change(PROG_LEAVE);
}

void FormationAdelheid::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //�ґ��S�Ŏ��G�t�F�N�g�o���i���{�[�i�X�X�R�A���Z���s����j
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //�ґ��S�ŃA�C�e���o��
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationAdelheid::~FormationAdelheid() {
    pConnection_ShotDepo_->close();
    pConnection_AdelheidDepo_->close();
}

