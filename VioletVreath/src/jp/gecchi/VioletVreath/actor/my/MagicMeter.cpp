#include "stdafx.h"
#include "MagicMeter.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardSetEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardSetModel.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/CostDispBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/DamageDispBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/EnergyBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/OptionMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/SmileMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/SpeedMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TorpedoMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/VreathMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor002.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor003.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicMeterCursor001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicMeterStatus.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/VreathBar.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dxcore/sound/GgafDxSe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicMeter::MagicMeter(const char* prm_name, GgafLib::AmountGraph* prm_pMP_MyShip, GgafLib::AmountGraph* prm_pVreath_MyShip)
      : DefaultBoardSetActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeter";
    width_px_ = _pBoardSetModel->_fSize_BoardSetModelWidthPx;
    height_px_ = _pBoardSetModel->_fSize_BoardSetModelHeightPx;
    width_ = PX_C(width_px_);
    height_ = PX_C(height_px_);

    pMP_MyShip_ = prm_pMP_MyShip;
    cost_disp_mp_.config(pMP_MyShip_->_max_val_px, pMP_MyShip_->_max_val);
    cost_disp_mp_.set(0);
    pVreath_MyShip_ = prm_pVreath_MyShip;
    cost_disp_vreath.config(pVreath_MyShip_->_max_val_px, pVreath_MyShip_->_max_val);
    cost_disp_vreath.set(0);
    damage_disp_vreath.config(pVreath_MyShip_->_max_val_px, pVreath_MyShip_->_max_val);
    damage_disp_vreath.set(0);

    pTractorMagic_ = NEW TractorMagic("TRACTOR", pMP_MyShip_);
    pSpeedMagic_   = NEW SpeedMagic("SPEED", pMP_MyShip_);
    pLockonMagic_  = NEW LockonMagic("LOCKON", pMP_MyShip_);
    pTorpedoMagic_ = NEW TorpedoMagic("TORPEDO", pMP_MyShip_);
    pLaserMagic_   = NEW LaserMagic("LASER", pMP_MyShip_);
    pOptionMagic_  = NEW OptionMagic("OPTION", pMP_MyShip_);
    pVreathMagic_  = NEW VreathMagic("VREATH", pMP_MyShip_);
    pSmileMagic_   = NEW SmileMagic("SMILE", pMP_MyShip_); //�������@
    lstMagic_.addLast(pTractorMagic_);
    lstMagic_.addLast(pSpeedMagic_  );
    lstMagic_.addLast(pLockonMagic_ );
    lstMagic_.addLast(pTorpedoMagic_);
    lstMagic_.addLast(pLaserMagic_  );
    lstMagic_.addLast(pOptionMagic_ );
    lstMagic_.addLast(pVreathMagic_ );
    lstMagic_.addLast(pSmileMagic_  );

    int magic_num = lstMagic_.length();

    for (int i = 0; i < magic_num; i++) {
        addSubGroup(lstMagic_.getNext(i));
    }

    papLvTargetCursor_      = NEW MagicLvCursor001*[magic_num];
    papLvHilightCursor_     = NEW MagicLvCursor002*[magic_num];
    papLvCastingMarkCursor_ = NEW MagicLvCursor003*[magic_num];
    paFloat_rr_      = NEW float[magic_num];
    paFloat_velo_rr_ = NEW float[magic_num];
    Magic* pMagic;
    MagicList::Elem* pMagicElem = lstMagic_.getElemFirst();
    for (int i = 0; i < magic_num; i++) {
        pMagic = pMagicElem->getValue();
        papLvHilightCursor_[i] = NEW MagicLvCursor002("LvHilightCursor", this, pMagic); //�����x�������J�[�\��
        papLvCastingMarkCursor_[i] = NEW MagicLvCursor003("LvCastMarkCursor_", this, pMagic); //�r�����x�������J�[�\��
        papLvCastingMarkCursor_[i]->markOff();
        papLvTargetCursor_[i] = NEW MagicLvCursor001("LvTargetCursor", this, pMagic); //���[�^�⏕�J�[�\��
        pMagicElem = pMagicElem->_pNext;
    }
    for (int i = 0; i < magic_num; i++) {
        paFloat_rr_[i] = 0.0f;
        paFloat_velo_rr_[i] = 0.0f;
    }

    //�\���v���I���e�B���l�����āAaddSubGroup���s�����I
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvHilightCursor_[i]); //�����x�������J�[�\��
    }
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvCastingMarkCursor_[i]); //�r�����x�������J�[�\��
    }
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvTargetCursor_[i]); //���[�^�⏕�J�[�\��
    }


    //�G�l���M�[�o�[�ݒu
    pEnergyBar_ = NEW EnergyBar("EnergyBar", pMP_MyShip_);
    addSubGroup(pEnergyBar_);
    //Vreath�o�[�ݒu
    pVreathBar_ = NEW VreathBar("VreathBar", pVreath_MyShip_);
    addSubGroup(pVreathBar_);

    //�G�l���M�[�o�[�̃R�X�g�\���o�[
    pCostDispBar_ = NEW CostDispBar("CostDispBar", pEnergyBar_, &cost_disp_mp_);
    addSubGroup(pCostDispBar_);
    //Vreath�o�[�R�X�g�\���o�[
    pCostDispBar2_ = NEW CostDispBar("CostDispBar2", pVreathBar_, &cost_disp_vreath);
    addSubGroup(pCostDispBar2_);
    //Vreath�o�[�_���[�W�\���o�[
    pDamageDispBar_ = NEW DamageDispBar("DamageDispBar", pVreathBar_, &damage_disp_vreath);
    addSubGroup(pDamageDispBar_);


    //�c���@���ʎ������ԕ\��
    pMagicMeterStatus_ = NEW MagicMeterStatus("MagicMeterStatus", this);
    addSubGroup(pMagicMeterStatus_);

    //���[�^��J�[�\��
    pMagicCursor_ = NEW MagicMeterCursor001("MagicCursor", this);
    addSubGroup(pMagicCursor_);


    _pSeTx->set(SE_CURSOR_MOVE_METER             , "WAVE_MM_CURSOR_MOVE_METER");  //�僁�[�^�[�J�[�\���ړ���
    _pSeTx->set(SE_CURSOR_MOVE_LEVEL             , "WAVE_MM_CURSOR_MOVE_LEVEL");  //�㉺���x���ړ���
    _pSeTx->set(SE_CURSOR_MOVE_LEVEL_CANCEL      , "WAVE_MM_CURSOR_MOVE_LEVEL_CANCEL");  //�㉺���x���ړ��L�����Z���i�j
    _pSeTx->set(SE_CURSOR_BAD_MOVE               , "WAVE_MM_CURSOR_BAD_MOVE");  //�_���ȃJ�[�\���ړ��i��Ƃ��邳���̂Ō��ݖ��g�p�j
    _pSeTx->set(SE_EXECUTE_LEVELUP_MAGIC         , "WAVE_MM_EXECUTE_LEVELUP_MAGIC");  //���x���A�b�v���s��
    _pSeTx->set(SE_EXECUTE_LEVELDOWN_MAGIC       , "WAVE_MM_EXECUTE_LEVELDOWN_MAGIC");  //���x���_�E�����s��
    _pSeTx->set(SE_EXECUTE_CANCEL_LEVELUP_MAGIC  , "WAVE_MM_EXECUTE_CANCEL_LEVELUP_MAGIC");  //�i�r���L�����Z�����āj���x���A�b�v���s��
    _pSeTx->set(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC, "WAVE_MM_EXECUTE_CANCEL_LEVELDOWN_MAGIC");  //�i�r���L�����Z�����āj���x���_�E�����s��
    _pSeTx->set(SE_CANT_INVOKE_MAGIC             , "WAVE_MM_CANT_INVOKE_MAGIC");  //�r���������AMP������Ȃ����ߔ����ł��Ȃ��ꍇ
    _pSeTx->set(SE_BAD_OPERATION                 , "WAVE_MM_BAD_OPERATION");  //����~�X�B�o���Ȃ����́A�u�u�[
    pSeTx4Cast_ = NEW GgafDxSeTransmitterForActor(this);
    for (int i = 0; i < magic_num; i++) {
        pSeTx4Cast_->set(i, "WAVE_MM_CASTING", i); //�`�����l�������w��
    }
    alpha_velo_ = -0.01f;
}


void MagicMeter::loadStatus(int prm_saveno) {
    st_[prm_saveno].seekg(std::stringstream::beg); //���o��
    load(st_[prm_saveno]);
}

void MagicMeter::saveStatus(int prm_saveno) {
    save(st_[prm_saveno]);
}

void MagicMeter::save(std::stringstream& sts) {
    sts << pMP_MyShip_->get() << " ";
    Magic* pOrgMagic = lstMagic_.getCurrent();
    int len_magics = lstMagic_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->save(sts);
        pOrgMagic = lstMagic_.next();
    }
}

void MagicMeter::load(std::stringstream& sts) {
    int mp;
    sts >> mp;
    pMP_MyShip_->set(mp);

    Magic* pOrgMagic = lstMagic_.getCurrent();
    int len_magics = lstMagic_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->load(sts);
        pOrgMagic = lstMagic_.next();
    }
}

void MagicMeter::initialize() {
    pEnergyBar_->position(_X, _Y + height_ + PX_C(16));
    pCostDispBar_->position(pEnergyBar_->_X, pEnergyBar_->_Y);
    pVreathBar_->position(_X, _Y + height_ + PX_C(16) + PX_C(16) );
    pCostDispBar2_->position(pVreathBar_->_X, pVreathBar_->_Y);
    pDamageDispBar_->position(pVreathBar_->_X, pVreathBar_->_Y);
    pMagicMeterStatus_->positionAs(this);

    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //�A�j������
    Magic* pMagic;
    for (int i = 0; i < lstMagic_.length(); i++) {
        pMagic = lstMagic_.getFromFirst(i);
        papLvTargetCursor_[i]->moveTo(pMagic->level_);
        papLvHilightCursor_[i]->moveTo(pMagic->level_);
        papLvCastingMarkCursor_[i]->moveTo(0);
    }
}
void MagicMeter::onReset() {
    Magic* pMagic;
    for (int i = 0; i < lstMagic_.length(); i++) {
        pMagic = lstMagic_.getFromFirst(i);
        pMagic->resetTree(); //���Magic�����Z�b�g������B
        papLvTargetCursor_[i]->moveTo(pMagic->level_);
        papLvHilightCursor_[i]->moveTo(pMagic->level_);
        papLvCastingMarkCursor_[i]->moveTo(0);

        paFloat_rr_[i] = 0.0f;
        paFloat_velo_rr_[i] = 0.0f;

        pSeTx4Cast_->get(i)->stop();
    }
    //�僁�[�^�[�J�[�\��
    lstMagic_.current(0);
    int active_idx = lstMagic_.getCurrentIndex();
    pMagicCursor_->moveTo(active_idx);
}
void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    VirtualButton* pVbPlay = VB_PLAY;

    if (pVbPlay->isBeingPressed(VB_POWERUP)) {
        alpha_velo_ = 0.05f;
        Magic* pActiveMagic = lstMagic_.getCurrent();     //�A�N�e�B�u�Ȗ��@
        int active_idx = lstMagic_.getCurrentIndex();     //�A�N�e�B�u�Ȗ��@�̃C���f�b�N�X
        progress active_prg = pActiveMagic->_pProg->get();  //�A�N�e�B�u�Ȗ��@�̐i��
        if (pVbPlay->isPushedDown(VB_POWERUP)) {
            rollOpen(active_idx);
        }

        if (pVbPlay->isAutoRepeat(VB_RIGHT)) {    //�u���v������
            //���x���\��
            if (papLvTargetCursor_[active_idx]->point_lv_ != papLvCastingMarkCursor_[active_idx]->point_lv_) {
                _pSeTx->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(papLvCastingMarkCursor_[active_idx]->point_lv_); //���s����Ȃ������ׁA���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
            }
            rollClose(active_idx); //���݃��[���N���[�Y

            lstMagic_.next(); //���[�^�[���P�i�߂�
            pActiveMagic= lstMagic_.getCurrent();     //�X�V
            active_idx = lstMagic_.getCurrentIndex(); //�X�V
            active_prg = pActiveMagic->_pProg->get();   //�X�V

            rollOpen(active_idx);  //�i�߂�������[���I�[�v��
            pMagicCursor_->moveTo(active_idx); //���[�^�[�J�[�\�����P�i�߂�
            _pSeTx->play(SE_CURSOR_MOVE_METER);

        } else if (pVbPlay->isAutoRepeat(VB_LEFT)) { //�u���v������
            //���x���\��
            if (papLvTargetCursor_[active_idx]->point_lv_ != papLvCastingMarkCursor_[active_idx]->point_lv_) {
                _pSeTx->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(papLvCastingMarkCursor_[active_idx]->point_lv_); //���s����Ȃ������ׁA���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
            }
            rollClose(active_idx); //���݃��[���N���[�Y

            lstMagic_.prev(); //���[�^�[���P�߂�
            pActiveMagic= lstMagic_.getCurrent();     //�X�V
            active_idx = lstMagic_.getCurrentIndex(); //�X�V
            active_prg = pActiveMagic->_pProg->get();   //�X�V

            rollOpen(active_idx); //�߂���������[���I�[�v��
            pMagicCursor_->moveTo(active_idx); //���[�^�[�J�[�\�����P�߂�
            _pSeTx->play(SE_CURSOR_MOVE_METER);

        } else if (pVbPlay->isAutoRepeat(VB_UP) ) {  // �u���v������
            if (pActiveMagic->max_level_ > papLvTargetCursor_[active_idx]->point_lv_) {
                _pSeTx->play(SE_CURSOR_MOVE_LEVEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(papLvTargetCursor_[active_idx]->point_lv_ + 1);
            }

        } else if (pVbPlay->isAutoRepeat(VB_DOWN)) {  //�u���v������
            if (0 < papLvTargetCursor_[active_idx]->point_lv_) {
                _pSeTx->play(SE_CURSOR_MOVE_LEVEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(papLvTargetCursor_[active_idx]->point_lv_ - 1);
            }
        } else {

        }
        //�R�X�g�o�[
        if (paFloat_rr_[active_idx] > 0.01f) {
            if (papLvTargetCursor_[active_idx]->point_lv_ == pActiveMagic->level_) {
                //�J�[�\������茻�݂Ɠ������x�����w���Ă���ꍇ
                cost_disp_mp_.set(0);
            } else if (papLvTargetCursor_[active_idx]->point_lv_ > pActiveMagic->level_) {
                //�J�[�\�������݂�荂�����x�����w���Ă���ꍇ
                cost_disp_mp_.set(
                  pActiveMagic->interest_cost_[papLvTargetCursor_[active_idx]->point_lv_ - pActiveMagic->level_]
                );
            } else {
                //�J�[�\�������݂��Ⴂ���x�����w���Ă���ꍇ
                cost_disp_mp_.set(
                    -1*pActiveMagic->calcReduceMp(pActiveMagic->level_,  papLvTargetCursor_[active_idx]->point_lv_)
                );
            }
        } else {
            cost_disp_mp_.set(0);
        }

        //Vreath�o�[
        if (active_idx == 6) {
            VreathMagic* pVM = (VreathMagic*)pActiveMagic;
            if (paFloat_rr_[active_idx] > 0.01f) {
                if (papLvTargetCursor_[active_idx]->point_lv_ == pVM->level_) {
                    //�J�[�\������茻�݂Ɠ������x�����w���Ă���ꍇ
                    cost_disp_vreath.set(0);
                } else if (papLvTargetCursor_[active_idx]->point_lv_ > pVM->level_) {
                    //�J�[�\�������݂�荂�����x�����w���Ă���ꍇ
                    cost_disp_vreath.set(
                            (int)(-1 * pVM->calcTotalVreath(pActiveMagic->level_,  papLvTargetCursor_[active_idx]->point_lv_))
                    );
                } else {
                    //�J�[�\�������݂��Ⴂ���x�����w���Ă���ꍇ
                    cost_disp_vreath.set(0);
                }
            } else {
                cost_disp_vreath.set(0);
            }
        } else {
            cost_disp_vreath.set(0);
        }

        //�u����v��
        if (pVbPlay->isPushedDown(VB_SHOT1) || pVbPlay->isPushedDown(VB_SHOT2) || pVbPlay->isPushedDown(VB_TURBO)) {
            int r = pActiveMagic->cast(papLvTargetCursor_[active_idx]->point_lv_);

            switch (r) {
                case MAGIC_CAST_NG_INVOKING_NOW: {
                    _pSeTx->play(SE_BAD_OPERATION);
                    break;
                }
                case MAGIC_CAST_NG_MP_IS_SHORT: {
                    _pSeTx->play(SE_BAD_OPERATION);
                    break;
                }
                case MAGIC_CAST_NOTHING: {
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    break;
                }
                case MAGIC_CAST_CANCEL: {
                    _pSeTx->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTargetCursor_[active_idx]->blink(); //�s�J�s�J�I
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    break;
                }
                case MAGIC_CAST_OK_LEVELUP: {
                    pSeTx4Cast_->get(active_idx)->setLooping(true);
                    pSeTx4Cast_->play(active_idx);

                    _pSeTx->play(SE_EXECUTE_LEVELUP_MAGIC);
                    papLvTargetCursor_[active_idx]->blink(); //�s�J�s�J�I
                    //LEVELUP ���͊���pActiveMagic->new_level_ ���A�b�v�\�背�x��
                    papLvCastingMarkCursor_[active_idx]->markOnLevelUpCast(pActiveMagic->new_level_);
                    break;
                }
                case MAGIC_CAST_OK_LEVELDOWN: {
                    _pSeTx->play(SE_EXECUTE_LEVELDOWN_MAGIC);
                    papLvTargetCursor_[active_idx]->blink(); //�s�J�s�J�I
                    //LEVELDOWN ���͊��� effect(new_lv) ���s�ς݂̂��߁A�����x�� pActiveMagic->level_ �ƂȂ�
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->blink();
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
                    pSeTx4Cast_->get(active_idx)->setLooping(true);
                    pSeTx4Cast_->play(active_idx);

                    _pSeTx->play(SE_EXECUTE_CANCEL_LEVELUP_MAGIC);
                    papLvTargetCursor_[active_idx]->blink(); //�s�J�s�J�I
                    //LEVELUP ���͊���pActiveMagic->new_level_ ���A�b�v�\�背�x��
                    papLvCastingMarkCursor_[active_idx]->markOnLevelUpCast(pActiveMagic->new_level_);
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN: {
                    _pSeTx->play(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC);
                    papLvTargetCursor_[active_idx]->blink(); //�s�J�s�J�I
                    //LEVELDOWN ���͊��� effect(new_lv) ���s�ς݂̂��߁A�����x�� pActiveMagic->level_ �ƂȂ�
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->blink();
                    break;
                }
            }
        }
    } else  {
        alpha_velo_ = -0.02f;
        if (pVbPlay->isReleasedUp(VB_POWERUP)) {
            rollClose(lstMagic_.getCurrentIndex());
        }
        cost_disp_mp_.set(0);
        cost_disp_vreath.set(0);
    }

    addAlpha(alpha_velo_);
    if (getAlpha() < 0.2f) {
        setAlpha(0.2f);
    } else if (getAlpha() > 1.0f) {
        setAlpha(1.0f);
    }
    //���t���[���̊e���@�\���ɂ��Ă̏���
    GgafProgress* pMagicProg = nullptr;
    Magic* pMagic = nullptr;
    for (int m = 0; m < lstMagic_.length(); m++) {
        pMagic = lstMagic_.getFromFirst(m);
        pMagicProg = pMagic->_pProg;

        paFloat_rr_[m] += paFloat_velo_rr_[m];
        if (paFloat_rr_[m] < 0.0f) {
            paFloat_rr_[m] = 0.0f;
            paFloat_velo_rr_[m] = 0.0f;
        }
        if (paFloat_rr_[m] > 1.0f) {
            paFloat_rr_[m] = 1.0f;
            paFloat_velo_rr_[m] = 0.0f;
        }

        //���x���A�b�vINVOKING��
        if (pMagicProg->isJustChangedTo(Magic::STATE_INVOKE_BEGIN)) {
            papLvTargetCursor_[m]->dispDisable();
            papLvHilightCursor_[m]->dispDisable();
            if (papLvTargetCursor_[m]->point_lv_ == pMagic->level_) {
                //�����x�����w���Ă���ꍇ
                //�V�������x���ɂ������蓮�����Ă�����B
                papLvTargetCursor_[m]->moveSmoothTo(pMagic->new_level_);
            }
            papLvHilightCursor_[m]->moveSmoothTo(pMagic->new_level_, (frame)(pMagic->interest_time_of_invoking_[pMagic->new_level_-pMagic->level_]));
            papLvCastingMarkCursor_[m]->markOnInvoke(pMagic->new_level_);
        }
        //���x���A�b�vINVOKING������
        if (pMagicProg->isJustChangedFrom(Magic::STATE_INVOKING)) {
            papLvTargetCursor_[m]->dispEnable();
            papLvHilightCursor_[m]->dispEnable();
            papLvHilightCursor_[m]->blink();
        }

        if (pMagicProg->isJustChangedTo(Magic::STATE_EFFECT_BEGIN)) {
            if (pMagic->last_level_ < pMagic->level_) {
                //���x���A�b�vEFFECT_BEGEIN�������Ȃ��
//                papLvCastingMarkCursor_[m]->markOff(); //�}�[�N�I�t�I
                papLvCastingMarkCursor_[m]->markOnEffect(pMagic->level_);
            } else {
                //���x���_�E��EFFECT_BEGEIN�������Ȃ��
                //markOnLevelDownCast() ��������ł���B
                //�uCASTING�v�P���[�v�̃A�j���[�V����������ׁA�������Ȃ��B
            }
        }

        //�������x���_�E����
        if (pMagic->prev_frame_level_ != pMagic->level_ && pMagic->prev_frame_level_ > pMagic->level_) {
            if (papLvTargetCursor_[m]->point_lv_ == pMagic->prev_frame_level_) {
                papLvTargetCursor_[m]->moveSmoothTo(pMagic->level_);
            }
            papLvHilightCursor_[m]->moveSmoothTo(pMagic->level_);
            papLvHilightCursor_[m]->blink();
        }

        //��r���i�r���������A�r���������AMP������Ȃ������j
        if (pMagicProg->get() == Magic::STATE_NOTHING && pMagicProg->isJustChangedFrom(Magic::STATE_CASTING)) {
            papLvCastingMarkCursor_[m]->markOff(); //�}�[�N�I�t�I
            _pSeTx->play(SE_CANT_INVOKE_MAGIC);
        }

        //���������@�I����
        if (pMagic->time_of_effect_base_ == 0 &&
            pMagicProg->get() == Magic::STATE_NOTHING &&
            pMagicProg->isJustChangedFrom(Magic::STATE_INVOKING)) {
            //����
            //STATE_INVOKING
            //��
            //effect(new_level_)(chenge(STATE_EFFECT_BEGIN))
            //��
            //chenge(STATE_NOTHING) �Ə㏑�������̂�
            // pMagicProg->isJustChangedFrom(Magic::STATE_INVOKING) �̔���ƂȂ�
            //���̃^�C�~���O��
//            papLvCastingMarkCursor_[m]->markOff(); //�}�[�N�I�t�I
            papLvCastingMarkCursor_[m]->markOnEffect(pMagic->level_);
            papLvHilightCursor_[m]->moveSmoothTo(pMagic->level_);
        }

        //�r������SE
        GgafDxSe* pSe = pSeTx4Cast_->get(m);
        if (pMagicProg->get() == Magic::STATE_CASTING) {
            float f = ((float)(pMagicProg->getFrameInProgress())) / ((float)(pMagic->time_of_next_state_));
            pSe->setFrequencyRate(1.0f + (f*3.0f));
        } else if (pMagicProg->isJustChangedFrom(Magic::STATE_CASTING)) {
            pSe->stop();
        }
    }

//    //debug -------------->
//    if (GgafDxInput::isPushedDownKey(DIK_K)) {
//        _TRACE_("MagicMeter saveStatus(0)!!!!");
//        saveStatus(0);
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_L)) {
//        _TRACE_("MagicMeter loadStatus(0)!!!!");
//        loadStatus(0);
//    }
//    //<-----------------debug
}

void MagicMeter::processJudgement() {
}

void MagicMeter::onInactive() {
}

void MagicMeter::processDraw() {
    GgafDxBoardSetEffect* pBoardSetEffect = _pBoardSetEffect;
    ID3DXEffect* pID3DXEffect = pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    //�p���[���[�^�[
    //[====]���P�̑傫�� [====][====][====]
    MagicList::Elem* pElem = lstMagic_.getElemFirst();
    Magic* pMagic;
    int len_magics = lstMagic_.length();
    int n = 0;
    float u,v;
    float x = float(C_PX(_X));
    float y = float(C_PX(_Y));
    float z = float(C_PX(_Z));
    float alpha = getAlpha();
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//��������̂ŃA�N�e�B�u�ł���͂�
        n = 0;
        float wx = width_px_*i;
        //�}�W�b�N���[�^�[�w�i
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_X[n], x + wx);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_Y[n], y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_Z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[n], alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) �Ɏ��s���܂����B");
        _pUvFlipper->getUV(0, u, v);
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
        n++;

        //�}�W�b�N���[�^�[��̌��݂̃}�W�b�N���x���\��
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_X[n], x + wx);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_Y[n], y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_Z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[n], alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) �Ɏ��s���܂����B");
        _pUvFlipper->getUV(pMagic->lvinfo_[pMagic->level_].pno_, u, v);
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
        n++;

        float rr = paFloat_rr_[i];
        if (rr > 0.1f) {
            //�e�}�W�b�N�v�f
            int lv_slecter_num = pMagic->max_level_+1;
            for (int j = 0; j < lv_slecter_num; j++) {
                //���@��
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_X[n], x + wx);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_Y[n], y - (height_px_*(j+1)*rr));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_Z[n], z);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[n], alpha*rr); //�A�N�e�B�u�Ȃ�Z����
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) �Ɏ��s���܂����B");

                if (pMagic->chkCastAble(j) <= MAGIC_CAST_NG_MP_IS_SHORT) {
                    //MAGIC_CAST_NG_MP_IS_SHORT �� MAGIC_CAST_NG_INVOKING_NOW
                    //�r���s�\��
                    _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_ + 1, u, v); //�E�ׂ̃e�N�X�`���p�^�[���� DISABLE �ȃp�^�[���O��
                } else {
                    //�r���\�\��
                    _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
                }
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[n], u);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[n], v);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
                n++;
            }
        }
        _pBoardSetModel->draw(this, n);
        pElem = pElem->_pNext;
    }
}

void MagicMeter::rollOpen(int prm_meter_index) {
    paFloat_velo_rr_[prm_meter_index] = 0.1f;
}

void MagicMeter::rollClose(int prm_meter_index) {
    paFloat_velo_rr_[prm_meter_index] = -0.02f;
}

MagicMeter::~MagicMeter() {
    GGAF_DELETEARR(papLvTargetCursor_);
    GGAF_DELETEARR(papLvHilightCursor_);
    GGAF_DELETEARR(papLvCastingMarkCursor_);
    GGAF_DELETEARR(paFloat_rr_);
    GGAF_DELETEARR(paFloat_velo_rr_);
    GGAF_DELETE(pSeTx4Cast_);
}
