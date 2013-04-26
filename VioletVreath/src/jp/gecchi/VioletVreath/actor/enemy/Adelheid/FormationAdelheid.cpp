#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


FormationAdelheid::FormationAdelheid(const char* prm_name)
   : DepositoryFormation(prm_name) {
    _class_name = "FormationAdelheid";

    pPalisana1_ = NEW EnemyPalisana("Palisana1");
    pPalisana1_->inactivateImmed();
    addSubGroup(pPalisana1_);

    pPalisana2_ = NEW EnemyPalisana("Palisana2");
    pPalisana2_->inactivateImmed();
    addSubGroup(pPalisana2_);
    _TRACE_("����҂�1");
    dump();

    //�ґ������f�|�W�g���Z�b�g
    pConnection_AdelheidDepo_ = connectToDepositoryManager("EnemyAdelheid4Formation");
    setFormationMemberDepo(pConnection_AdelheidDepo_->peek());



    pConnection_ShotDepo_ = connectToDepositoryManager("EnemyAdelheidShot");

    updateRankParameter();

    pFirstAdelheid_ = nullptr;

    useProgress(PROG_LEAVE);
}

void FormationAdelheid::updateRankParameter() {
    rr_num_formation_     = 2; //RR_FormationAdelheid_Num(_RANK_);            //�ґ���
    rr_interval_frames_   = 30;
    rr_mv_velo_           = RR_FormationAdelheid_MvVelo(_RANK_);         //���x
}

void FormationAdelheid::initialize() {

}

void FormationAdelheid::onActive() {
    updateRankParameter();
    _pProg->reset(PROG_INIT);
}

void FormationAdelheid::processBehavior() {

    pConnection_AdelheidDepo_->peek()->dump();


    switch (_pProg->get()) {
         case PROG_INIT: {
             _TRACE_("FormationAdelheid::processBehavior() PROG_INIT ���[");

             //�ŏ��̈�@
             pFirstAdelheid_ = (EnemyAdelheid*)callUpMember(rr_num_formation_);
             if (!pFirstAdelheid_) {
                 //�P�@�ڂ��Ăяo���Ȃ�������ґ����̂��̂𖳂�
                 _pProg->changeNothing();
                 sayonara();
                 break;
             }
             pFirstAdelheid_->inactivateImmed(); //�v�Z�p�ɌĂяo�����̂ŁA�����͂�����Ƒ҂��āB
             pFirstAdelheid_->config(getFormationSplManuf()->createKurokoLeader(pFirstAdelheid_->_pKurokoA),
                                     pConnection_ShotDepo_->peek());
             pFirstAdelheid_->_pKurokoA->setMvVelo(rr_mv_velo_);
             onCallUpAdelheid(pFirstAdelheid_); //���ʃt�H�[���[�V�����N���X�ʎ����̏���
                                                //�J�n���W�ƕ�������܂�
             //�o���J�n�ʒu��pPalisana1_�z��
             pPalisana1_->locateAs(pFirstAdelheid_);
             coord next_X, next_Y, next_Z;
             pFirstAdelheid_->pKurokoLeader_->getPointCoord(1, next_X, next_Y, next_Z);
             pPalisana1_->_pKurokoA->setFaceAngTwd(next_X, next_Y, next_Z); //�����Z�b�g
             pPalisana1_->acitve_open(); //�L�����n�b�`�I�[�v��
             //�o���I���ʒu�ƁA���p�����߁A�o���I���ʒu��pPalisana2_�z��
             coord end_X, end_Y, end_Z;
             coord end_prev_X, end_prev_Y, end_prev_Z;
             int spl_point_num = pFirstAdelheid_->pKurokoLeader_->getPointNum();
             pFirstAdelheid_->pKurokoLeader_->getPointCoord(spl_point_num-1,
                                                            end_X, end_Y, end_Z); //�ŏI�⊮�_���W
             pFirstAdelheid_->pKurokoLeader_->getPointCoord(spl_point_num-2,
                                                            end_prev_X, end_prev_Y, end_prev_Z);  //�ŏI-1 �⊮�_���W
             pPalisana2_->locate(end_X, end_Y, end_Z);
             pPalisana2_->_pKurokoA->setFaceAngTwd(end_prev_X, end_prev_Y, end_prev_Z);
             pPalisana2_->acitve_open();//�L�����n�b�`�I�[�v��
             _pProg->changeNext();
             _TRACE_("FormationAdelheid::processBehavior() PROG_INIT OK ���[");
             break;
         }
         case PROG_ENTRY: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_ENTRY ���[");
             }
             if (pPalisana1_->isOpenDone()) {
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

             if (_pProg->getFrameInProgress() == rr_interval_frames_) {
                 //�ŏ��̂P�@��
                 pFirstAdelheid_->activate();
             } else if (canCallUp() && (_pProg->getFrameInProgress() % rr_interval_frames_ == 0)) {
                 //�Q�@�ڈȍ~
                 EnemyAdelheid* pAdelheid = (EnemyAdelheid*)callUpMember(rr_num_formation_);
                 if (pAdelheid) {
                     SplineKurokoLeader* pKurokoLeader =
                             getFormationSplManuf()->createKurokoLeader(pAdelheid->_pKurokoA);
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
                 pPalisana1_->close_sayonara();
                 pPalisana2_->close_sayonara();
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
void FormationAdelheid::processOnSayonara() {
    //�]���� FORMATION_END_DELAY �t���[��
    //����ȓ��ɕ���A�j���[�V�������I��点�܂��傤
    _TRACE_("FormationAdelheid::processOnSayonara() ���[");
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

