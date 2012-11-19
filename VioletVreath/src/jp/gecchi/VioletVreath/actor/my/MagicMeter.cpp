#include "stdafx.h"
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
    _Z = 5;

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
    ringMagics_.addLast(pTractorMagic_);
    ringMagics_.addLast(pSpeedMagic_  );
    ringMagics_.addLast(pLockonMagic_ );
    ringMagics_.addLast(pTorpedoMagic_);
    ringMagics_.addLast(pLaserMagic_  );
    ringMagics_.addLast(pOptionMagic_ );
    ringMagics_.addLast(pVreathMagic_ );
    ringMagics_.addLast(pSmileMagic_  );

    for (int i = 0; i < ringMagics_.length(); i++) {
        addSubGroup(ringMagics_.getNext(i));
    }

    pMagicCursor_ = NEW MagicMeterCursor001("MagicCursor", this); //���[�^��J�[�\��
    pMagicCursor_->_Z = _Z - 3; //�ł���O�ɕ\��������
    addSubGroup(pMagicCursor_);

    papLvTargetCursor_ = NEW MagicLvCursor001*[ringMagics_.length()];
    papLvHilightCursor_ = NEW MagicLvCursor002*[ringMagics_.length()];
    papLvCastingMarkCursor_ = NEW MagicLvCursor003*[ringMagics_.length()];
    paFloat_rr_ = NEW float[ringMagics_.length()];
    paFloat_velo_rr_ = NEW float[ringMagics_.length()];
    Magic* pMagic;
    for (int i = 0; i < ringMagics_.length(); i++) {
        pMagic = ringMagics_.getFromFirst(i);

        papLvTargetCursor_[i] = NEW MagicLvCursor001("LvTargetCursor", this, pMagic); //���[�^���J�[�\��
        papLvTargetCursor_[i]->_Z = _Z - 3;
        addSubGroup(papLvTargetCursor_[i]);

        papLvHilightCursor_[i] = NEW MagicLvCursor002("LvHilightCursor", this, pMagic); //�����x�������J�[�\��
        papLvHilightCursor_[i]->_Z = _Z - 1;
        addSubGroup(papLvHilightCursor_[i]);

        papLvCastingMarkCursor_[i] = NEW MagicLvCursor003("LvCastMarkCursor_", this, pMagic); //�r�����x�������J�[�\��
        papLvCastingMarkCursor_[i]->_Z = _Z - 2;
        papLvCastingMarkCursor_[i]->markOff();
        addSubGroup(papLvCastingMarkCursor_[i]);

        paFloat_rr_[i] = 0.0f;
        paFloat_velo_rr_[i] = 0.0f;
    }

    pMagicMeterStatus_ = NEW MagicMeterStatus("MagicMeterStatus", this);
    pMagicMeterStatus_->locateWith(this);
    addSubGroup(pMagicMeterStatus_);

    //�G�l���M�[�o�[�ݒu
    pEnergyBar_ = NEW EnergyBar("EnergyBar", pMP_MyShip_);
    pEnergyBar_->locate(PX_C(100), PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 60.0f), _Z);
    addSubGroup(pEnergyBar_);
    //�G�l���M�[�o�[�̃R�X�g�\���o�[
    pCostDispBar_ = NEW CostDispBar("CostDispBar", pEnergyBar_, &cost_disp_mp_);
    pCostDispBar_->locate(pEnergyBar_->_X, pEnergyBar_->_Y, _Z-1);
    addSubGroup(pCostDispBar_);

    //Vreath�o�[�ݒu
    pVreathBar_ = NEW VreathBar("VreathBar", pVreath_MyShip_);
    pVreathBar_->locate(PX_C(100), PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 20.0f), _Z);
    addSubGroup(pVreathBar_);
    //Vreath�o�[�R�X�g�\���o�[
    pCostDispBar2_ = NEW CostDispBar("CostDispBar2", pVreathBar_, &cost_disp_vreath);
    pCostDispBar2_->locate(pVreathBar_->_X, pVreathBar_->_Y, _Z-1);
    addSubGroup(pCostDispBar2_);
    //Vreath�o�[�_���[�W�\���o�[
    pDamageDispBar_ = NEW DamageDispBar("DamageDispBar", pVreathBar_, &damage_disp_vreath);
    pDamageDispBar_->locate(pVreathBar_->_X, pVreathBar_->_Y, _Z-1);
    addSubGroup(pDamageDispBar_);


    _pSeTxer->set(SE_CURSOR_MOVE_METER             , "WAVE_MM_CURSOR_MOVE_METER");  //�僁�[�^�[�J�[�\���ړ���
    _pSeTxer->set(SE_CURSOR_MOVE_LEVEL             , "WAVE_MM_CURSOR_MOVE_LEVEL");  //�㉺���x���ړ���
    _pSeTxer->set(SE_CURSOR_MOVE_LEVEL_CANCEL      , "WAVE_MM_CURSOR_MOVE_LEVEL_CANCEL");  //�㉺���x���ړ��L�����Z���i�j
    _pSeTxer->set(SE_CURSOR_BAD_MOVE               , "WAVE_MM_CURSOR_BAD_MOVE");  //�_���ȃJ�[�\���ړ��i��Ƃ��邳���̂Ō��ݖ��g�p�j
    _pSeTxer->set(SE_EXECUTE_LEVELUP_MAGIC         , "WAVE_MM_EXECUTE_LEVELUP_MAGIC");  //���x���A�b�v���s��
    _pSeTxer->set(SE_EXECUTE_LEVELDOWN_MAGIC       , "WAVE_MM_EXECUTE_LEVELDOWN_MAGIC");  //���x���_�E�����s��
    _pSeTxer->set(SE_EXECUTE_CANCEL_LEVELUP_MAGIC  , "WAVE_MM_EXECUTE_CANCEL_LEVELUP_MAGIC");  //�i�r���L�����Z�����āj���x���A�b�v���s��
    _pSeTxer->set(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC, "WAVE_MM_EXECUTE_CANCEL_LEVELDOWN_MAGIC");  //�i�r���L�����Z�����āj���x���_�E�����s��
    _pSeTxer->set(SE_CANT_INVOKE_MAGIC             , "WAVE_MM_CANT_INVOKE_MAGIC");  //�r���������AMP������Ȃ����ߔ����ł��Ȃ��ꍇ
    _pSeTxer->set(SE_BAD_OPERATION                 , "WAVE_MM_BAD_OPERATION");  //����~�X�B�o���Ȃ����́A�u�u�[

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
    Magic* pOrgMagic = ringMagics_.getCurrent();
    int len_magics = ringMagics_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->save(sts);
        pOrgMagic = ringMagics_.next();
    }
}

void MagicMeter::load(std::stringstream& sts) {
    int mp;
    sts >> mp;
    pMP_MyShip_->set(mp);

    Magic* pOrgMagic = ringMagics_.getCurrent();
    int len_magics = ringMagics_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->load(sts);
        pOrgMagic = ringMagics_.next();
    }
}

void MagicMeter::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //�A�j������
    Magic* pMagic;
    for (int i = 0; i < ringMagics_.length(); i++) {
        pMagic = ringMagics_.getFromFirst(i);
        papLvTargetCursor_[i]->moveTo(pMagic->level_);
        papLvHilightCursor_[i]->moveTo(pMagic->level_);
        papLvCastingMarkCursor_[i]->moveTo(0);
    }
}
void MagicMeter::onReset() {
    Magic* pMagic;
    for (int i = 0; i < ringMagics_.length(); i++) {
        pMagic = ringMagics_.getFromFirst(i);
        pMagic->resetTree(); //���Magic�����Z�b�g������B
        papLvTargetCursor_[i]->moveTo(pMagic->level_);
        papLvHilightCursor_[i]->moveTo(pMagic->level_);
        papLvCastingMarkCursor_[i]->moveTo(0);
    }
}
void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    if (VB_PLAY->isBeingPressed(VB_POWERUP)) {
        alpha_velo_ = 0.05f;
        Magic* pActiveMagic = ringMagics_.getCurrent();     //�A�N�e�B�u�Ȗ��@
        int active_idx = ringMagics_.getCurrentIndex();     //�A�N�e�B�u�Ȗ��@�̃C���f�b�N�X
        progress active_prg = pActiveMagic->_pProg->get();  //�A�N�e�B�u�Ȗ��@�̐i��
        if (VB_PLAY->isPushedDown(VB_POWERUP)) {
            rollOpen(active_idx);
        }

        if (VB_PLAY->isAutoRepeat(VB_RIGHT)) {    //�u���v������
            //���x���\��
            if (papLvTargetCursor_[active_idx]->point_lv_ != pActiveMagic->level_) {
                _pSeTxer->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_); //���s����Ȃ������ׁA���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
            }
            rollClose(active_idx); //���݃��[���N���[�Y

            ringMagics_.next(); //���[�^�[���P�i�߂�
            pActiveMagic= ringMagics_.getCurrent();     //�X�V
            active_idx = ringMagics_.getCurrentIndex(); //�X�V
            active_prg = pActiveMagic->_pProg->get();   //�X�V

            rollOpen(active_idx);  //�i�߂�������[���I�[�v��
            pMagicCursor_->moveTo(active_idx); //���[�^�[�J�[�\�����P�i�߂�
            _pSeTxer->play(SE_CURSOR_MOVE_METER);

        } else if (VB_PLAY->isAutoRepeat(VB_LEFT)) { //�u���v������
            //���x���\��
            if (papLvTargetCursor_[active_idx]->point_lv_ != pActiveMagic->level_) {
                _pSeTxer->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_); //���s����Ȃ������ׁA���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
            }
            rollClose(active_idx); //���݃��[���N���[�Y

            ringMagics_.prev(); //���[�^�[���P�߂�
            pActiveMagic= ringMagics_.getCurrent();     //�X�V
            active_idx = ringMagics_.getCurrentIndex(); //�X�V
            active_prg = pActiveMagic->_pProg->get();   //�X�V

            rollOpen(active_idx); //�߂���������[���I�[�v��
            pMagicCursor_->moveTo(active_idx); //���[�^�[�J�[�\�����P�߂�
            _pSeTxer->play(SE_CURSOR_MOVE_METER);

        } else if (VB_PLAY->isAutoRepeat(VB_UP) ) {  // �u���v������
            if (pActiveMagic->max_level_ > papLvTargetCursor_[active_idx]->point_lv_) {
                _pSeTxer->play(SE_CURSOR_MOVE_LEVEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(papLvTargetCursor_[active_idx]->point_lv_ + 1);
            }

        } else if (VB_PLAY->isAutoRepeat(VB_DOWN)) {  //�u���v������
            if (0 < papLvTargetCursor_[active_idx]->point_lv_) {
                _pSeTxer->play(SE_CURSOR_MOVE_LEVEL);
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
        if (VB_PLAY->isPushedDown(VB_SHOT1)) {
            int r = pActiveMagic->cast(papLvTargetCursor_[active_idx]->point_lv_);

            switch (r) {
                case MAGIC_CAST_NG_INVOKING_NOW: {
                    _pSeTxer->play(SE_BAD_OPERATION);
                    break;
                }
                case MAGIC_CAST_NG_MP_IS_SHORT: {
                    _pSeTxer->play(SE_BAD_OPERATION);
                    break;
                }
                case MAGIC_CAST_NOTHING: {
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    break;
                }
                case MAGIC_CAST_CANCEL: {
                    _pSeTxer->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTargetCursor_[active_idx]->beginBlinking(); //�s�J�s�J�I
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    break;
                }
                case MAGIC_CAST_OK_LEVELUP: {
                    _pSeTxer->play(SE_EXECUTE_LEVELUP_MAGIC);
                    papLvTargetCursor_[active_idx]->beginBlinking(); //�s�J�s�J�I
                    //LEVELUP ���͊���pActiveMagic->new_level_ ���A�b�v�\�背�x��
                    papLvCastingMarkCursor_[active_idx]->markOnLevelUpCast(pActiveMagic->new_level_);
                    break;
                }
                case MAGIC_CAST_OK_LEVELDOWN: {
                    _pSeTxer->play(SE_EXECUTE_LEVELDOWN_MAGIC);
                    papLvTargetCursor_[active_idx]->beginBlinking(); //�s�J�s�J�I
                    //LEVELDOWN ���͊��� effect(new_lv) ���s�ς݂̂��߁A�����x�� pActiveMagic->level_ �ƂȂ�
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->beginBlinking();
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
                    _pSeTxer->play(SE_EXECUTE_CANCEL_LEVELUP_MAGIC);
                    papLvTargetCursor_[active_idx]->beginBlinking(); //�s�J�s�J�I
                    //LEVELUP ���͊���pActiveMagic->new_level_ ���A�b�v�\�背�x��
                    papLvCastingMarkCursor_[active_idx]->markOnLevelUpCast(pActiveMagic->new_level_);
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN: {
                    _pSeTxer->play(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC);
                    papLvTargetCursor_[active_idx]->beginBlinking(); //�s�J�s�J�I
                    //LEVELDOWN ���͊��� effect(new_lv) ���s�ς݂̂��߁A�����x�� pActiveMagic->level_ �ƂȂ�
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->beginBlinking();
                    break;
                }
            }
        }
    } else  {
        alpha_velo_ = -0.02f;
        if (VB_PLAY->isReleasedUp(VB_POWERUP)) {
            rollClose(ringMagics_.getCurrentIndex());
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
    GgafProgress* pMagicProg = NULL;
    Magic* pMagic = NULL;
    for (int m = 0; m < ringMagics_.length(); m++) {
        pMagic = ringMagics_.getFromFirst(m);
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
        if (pMagicProg->hasJustChangedTo(Magic::STATE_INVOKE_BEGIN)) {
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
        if (pMagicProg->hasJustChangedFrom(Magic::STATE_INVOKING)) {
            papLvTargetCursor_[m]->dispEnable();
            papLvHilightCursor_[m]->dispEnable();
            papLvHilightCursor_[m]->beginBlinking();
        }

        //���ʊJ�n��
        if (pMagicProg->hasJustChangedTo(Magic::STATE_EFFECT_BEGIN)) {
            if (pMagic->last_level_ < pMagic->level_) {
                //���x���A�b�vEFFECT_BEGEIN�������Ȃ��
                papLvCastingMarkCursor_[m]->markOff(); //�}�[�N�I�t�I
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
            papLvHilightCursor_[m]->beginBlinking();
        }

        //��r���i�r���������A�r���������AMP������Ȃ������j
        if (pMagicProg->get() == Magic::STATE_NOTHING && pMagicProg->hasJustChangedFrom(Magic::STATE_CASTING)) {
            papLvCastingMarkCursor_[m]->markOff(); //�}�[�N�I�t�I
            _pSeTxer->play(SE_CANT_INVOKE_MAGIC);
        }

        //���������@�I����
        if (pMagic->time_of_effect_base_ == 0 &&
            pMagicProg->get() == Magic::STATE_NOTHING &&
            pMagicProg->hasJustChangedFrom(Magic::STATE_INVOKING)) {
            //����
            //STATE_INVOKING
            //��
            //effect(new_level_)(chenge(STATE_EFFECT_BEGIN))
            //��
            //chenge(STATE_NOTHING) �Ə㏑�������̂�
            // pMagicProg->hasJustChangedFrom(Magic::STATE_INVOKING) �̔���ƂȂ�
            //���̃^�C�~���O��
            papLvCastingMarkCursor_[m]->markOff(); //�}�[�N�I�t�I
            papLvHilightCursor_[m]->moveSmoothTo(pMagic->level_);
        }
    }


    //debug -------------->
    if (GgafDxInput::isPushedDownKey(DIK_K)) {
        _TRACE_("MagicMeter saveStatus(0)!!!!");
        saveStatus(0);
    }
    if (GgafDxInput::isPushedDownKey(DIK_L)) {
        _TRACE_("MagicMeter loadStatus(0)!!!!");
        loadStatus(0);
    }
    //<-----------------debug
}

void MagicMeter::processJudgement() {
}

void MagicMeter::onInactive() {
}

void MagicMeter::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    //�p���[���[�^�[
    //[====]���P�̑傫�� [====][====][====]
    GgafLinkedListRing<Magic>::Elem* pElem = ringMagics_.getElemFirst();
    Magic* pMagic;
    int len_magics = ringMagics_.length();
    int n = 0;
    float u,v;
    float x = float(C_PX(_X));
    float y = float(C_PX(_Y));
    float z = float(C_PX(_Z));
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//��������̂ŃA�N�e�B�u�ł���͂�
        n = 0;

        //�}�W�b�N���[�^�[�w�i
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[n], x +width_px_*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[n], y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[n], getAlpha());
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) �Ɏ��s���܂����B");
        _pUvFlipper->getUV(0, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
        n++;

        //�}�W�b�N���[�^�[��̌��݂̃}�W�b�N���x���\��
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[n], x + width_px_*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[n], y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[n], getAlpha());
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) �Ɏ��s���܂����B");
        _pUvFlipper->getUV(pMagic->lvinfo_[pMagic->level_].pno_, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) �Ɏ��s���܂����B");
        n++;

        if (paFloat_rr_[i] > 0.1) {
            //�e�}�W�b�N�v�f
            for (int j = 0; j < pMagic->max_level_+1; j++) {
                //���@��
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[n], x + width_px_*i);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[n], y - (height_px_*(j+1)*paFloat_rr_[i]));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[n], z);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[n], getAlpha()*paFloat_rr_[i]); //�A�N�e�B�u�Ȃ�Z����
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) �Ɏ��s���܂����B");

                if (pMagic->chkCastAble(j) <= MAGIC_CAST_NG_MP_IS_SHORT) {
                    //MAGIC_CAST_NG_MP_IS_SHORT �� MAGIC_CAST_NG_INVOKING_NOW
                    //�r���s�\��
                    _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_ + 1, u, v); //�E�ׂ̃e�N�X�`���p�^�[���� DISABLE �ȃp�^�[���O��
                } else {
                    //�r���\�\��
                    _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
                }
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[n], u);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[n], v);
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
    DELETEARR_IMPOSSIBLE_NULL(papLvTargetCursor_);
    DELETEARR_IMPOSSIBLE_NULL(papLvHilightCursor_);
    DELETEARR_IMPOSSIBLE_NULL(papLvCastingMarkCursor_);
    DELETEARR_IMPOSSIBLE_NULL(paFloat_rr_);
    DELETEARR_IMPOSSIBLE_NULL(paFloat_velo_rr_);
}
