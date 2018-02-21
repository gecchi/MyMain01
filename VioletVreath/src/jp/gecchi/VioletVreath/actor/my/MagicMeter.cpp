#include "MagicMeter.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassBoardEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMassBoardModel.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/CostDispBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/DamageDispBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MpBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/ShotMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
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
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/BunshinMagic.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_CURSOR_MOVE_METER       ,
    SE_CURSOR_MOVE_LEVEL       ,
    SE_CURSOR_MOVE_LEVEL_CANCEL,
    SE_CURSOR_BAD_MOVE         ,
    SE_EXECUTE_LEVELUP_MAGIC   ,
    SE_EXECUTE_LEVELDOWN_MAGIC ,
    SE_EXECUTE_CANCEL_LEVELUP_MAGIC   ,
    SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC ,
    SE_NG_MP_IS_SHORT       ,
    SE_EFFECT_MAGIC    ,
    SE_NOTICE_LEVELDOWN_MAGIC,
    SE_BAD_OPERATION   ,
};

MagicMeter::MagicMeter(const char* prm_name, int* prm_pMP_MyShip, int* prm_pVreath_MyShip)
      : DefaultMassBoardActor(prm_name, "128/MagicMeter"),
width_px_(_pMassBoardModel->_model_width_px),
height_px_(_pMassBoardModel->_model_height_px),
width_(PX_C(width_px_)),
height_(PX_C(height_px_)) {

    _class_name = "MagicMeter";
    pTractorMagic_ = NEW TractorMagic("TRACTOR", prm_pMP_MyShip); //�ێ��R�X�g�L��
    pSpeedMagic_   = NEW SpeedMagic("SPEED", prm_pMP_MyShip);
    pLockonMagic_  = NEW LockonMagic("LOCKON", prm_pMP_MyShip);
    pTorpedoMagic_ = NEW TorpedoMagic("TORPEDO", prm_pMP_MyShip);
    pShotMagic_    = NEW ShotMagic("SHOT", prm_pMP_MyShip);
    pLaserMagic_   = NEW LaserMagic("LASER", prm_pMP_MyShip);
    pBunshinMagic_ = NEW BunshinMagic("BUNSHIN", prm_pMP_MyShip);
    pVreathMagic_  = NEW VreathMagic("VREATH", prm_pMP_MyShip);
    pSmileMagic_   = NEW SmileMagic("SMILE", prm_pMP_MyShip); //�������@
    lstMagic_.addLast(pTractorMagic_);
    lstMagic_.addLast(pSpeedMagic_  );
    lstMagic_.addLast(pLockonMagic_ );
    lstMagic_.addLast(pTorpedoMagic_);
    lstMagic_.addLast(pShotMagic_   );
    lstMagic_.addLast(pLaserMagic_  );
    lstMagic_.addLast(pBunshinMagic_);
    lstMagic_.addLast(pVreathMagic_ );
    lstMagic_.addLast(pSmileMagic_  );
    lstMagic_.createIndex();

    int magic_num = lstMagic_.length();
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(lstMagic_.getNext(i));
    }

    papLvTgtMvCur_   = NEW MagicLvCursor001*[magic_num];
    papLvNowCur_     = NEW MagicLvCursor002*[magic_num];
    papLvCastingCur_ = NEW MagicLvCursor003*[magic_num];
    r_roll_      = NEW float[magic_num];
    r_roll_velo_ = NEW float[magic_num];
    Magic* pMagic;
    MagicList::Elem* pMagicElem = lstMagic_.getElemFirst();
    for (int i = 0; i < magic_num; i++) {
        pMagic = pMagicElem->getValue();
        papLvNowCur_[i] = NEW MagicLvCursor002("LvHilightCursor", this, pMagic); //�����x�������J�[�\��
        papLvCastingCur_[i] = NEW MagicLvCursor003("LvCastMarkCursor", this, pMagic); //�r�����x�������J�[�\��
        papLvCastingCur_[i]->markOff();
        papLvTgtMvCur_[i] = NEW MagicLvCursor001("LvTargetCursor", this, pMagic); //���[�^�⏕�J�[�\��
        pMagicElem = pMagicElem->_pNext;
    }
    for (int i = 0; i < magic_num; i++) {
        r_roll_[i] = 0.0f;
        r_roll_velo_[i] = 0.0f;
    }

    //�\���v���I���e�B���l�����āAaddSubGroup���s�����I
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvNowCur_[i]); //�����x�������J�[�\��
    }
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvCastingCur_[i]); //�r�����x�������J�[�\��
    }
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvTgtMvCur_[i]); //���[�^�⏕�J�[�\��
    }

    pixcoord mp_px = 800;
    int vreath_val = *prm_pVreath_MyShip; //�ŏ������^�������炱����g�p
    pixcoord vreath_px = mp_px;
    //MP�o�[�ݒu
    pMpBar_ = NEW MpBar("MpBar");
    pMpBar_->linkVariable(prm_pMP_MyShip);
    pMpBar_->graduate(0, MY_SHIP_MAX_MP, mp_px); //���ݒl�ŉ�ʕ\����600px�Ƃ���B
    addSubGroup(pMpBar_);
    //Vreath�o�[�ݒu
    pVreathBar_ = NEW VreathBar("VreathBar");
    pVreathBar_->linkVariable(prm_pVreath_MyShip);
    pVreathBar_->graduate(0, vreath_val, vreath_px); //���ݒl�ŉ�ʕ\����600px�Ƃ���B
    addSubGroup(pVreathBar_);

    //�G�l���M�[�o�[�̃R�X�g�\���o�[
    pMpCostDispBar_ = NEW CostDispBar("CostDispBar", pMpBar_);
    pMpCostDispBar_->graduate(-MY_SHIP_MAX_MP, +MY_SHIP_MAX_MP, mp_px*2);
    addSubGroup(pMpCostDispBar_);
    //Vreath�o�[�A�R�X�g�\���o�[
    pVreathCostDispBar_ = NEW CostDispBar("CostDispBar2", pVreathBar_);
    pVreathCostDispBar_->graduate(-vreath_val, +vreath_val, vreath_px*2);
    addSubGroup(pVreathCostDispBar_);
    //Vreath�o�[�A�_���[�W�\���o�[
    pDamageDispBar_ = NEW DamageDispBar("DamageDispBar", pVreathBar_);
    pDamageDispBar_->graduate(-vreath_val, +vreath_val, vreath_px*2);
    addSubGroup(pDamageDispBar_);

    //�c���@���ʎ������ԕ\��
    pMagicMeterStatus_ = NEW MagicMeterStatus("MagicMeterStatus", this);
    addSubGroup(pMagicMeterStatus_);

    //���[�^��J�[�\��
    pMainCur_ = NEW MagicMeterCursor001("MagicCursor", this);
    addSubGroup(pMainCur_);

    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_CURSOR_MOVE_METER             , "WAVE_MM_CURSOR_MOVE_METER");  //�僁�[�^�[�J�[�\���ړ���
    pSeTx->set(SE_CURSOR_MOVE_LEVEL             , "WAVE_MM_CURSOR_MOVE_LEVEL");  //�㉺���x���ړ���
    pSeTx->set(SE_CURSOR_MOVE_LEVEL_CANCEL      , "WAVE_MM_CURSOR_MOVE_LEVEL_CANCEL");  //�㉺���x���ړ��L�����Z���i�j
    pSeTx->set(SE_CURSOR_BAD_MOVE               , "WAVE_MM_CURSOR_BAD_MOVE");  //�_���ȃJ�[�\���ړ��i��Ƃ��邳���̂Ō��ݖ��g�p�j
    pSeTx->set(SE_EXECUTE_LEVELUP_MAGIC         , "WAVE_MM_EXECUTE_LEVELUP_MAGIC");  //���x���A�b�v���s��
    pSeTx->set(SE_EXECUTE_LEVELDOWN_MAGIC       , "WAVE_MM_EXECUTE_LEVELDOWN_MAGIC");  //���x���_�E�����s��
    pSeTx->set(SE_EXECUTE_CANCEL_LEVELUP_MAGIC  , "WAVE_MM_EXECUTE_CANCEL_LEVELUP_MAGIC");  //�i�r���L�����Z�����āj���x���A�b�v���s��
    pSeTx->set(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC, "WAVE_MM_EXECUTE_CANCEL_LEVELDOWN_MAGIC");  //�i�r���L�����Z�����āj���x���_�E�����s��
    pSeTx->set(SE_NG_MP_IS_SHORT                , "WAVE_MM_NG_MP_IS_SHORT");  //MP������Ȃ����ߔ������邢�͌��ʊJ�n�ł��Ȃ��ꍇ
    pSeTx->set(SE_EFFECT_MAGIC                  , "WAVE_MM_EFFECT_MAGIC");  //�������������A���ʔ�����
    pSeTx->set(SE_NOTICE_LEVELDOWN_MAGIC        , "WAVE_MM_NOTICE_LEVELDOWN_MAGIC");  //���x���_�E�������\��
    pSeTx->set(SE_BAD_OPERATION                 , "WAVE_MM_BAD_OPERATION");  //����~�X�B�o���Ȃ����́A�u�u�[

    pSeTx4Cast_ = NEW GgafDxSeTransmitterForActor(this);
    pSeTx4Invoke_ = NEW GgafDxSeTransmitterForActor(this);
    for (int i = 0; i < magic_num; i++) {
        pSeTx4Cast_->set(i, "WAVE_MM_CASTING", i); //�r����SE�B�`�����l�������w��
        pSeTx4Invoke_->set(i, "WAVE_MM_INVOKING", i); //������SE�B�`�����l�������w��
    }
    fraeme_of_notice_remaind_ = 60*5;//�c��͂��x�������̎c�莞��
    alpha_velo_ = -0.01f;

    //�C���X�^���X�f�[�^������
    max_draw_num_ = 0;
    int len_magics = lstMagic_.length();
    MagicList::Elem* pElem = lstMagic_.getElemFirst();
    for (int i = 0; i < len_magics; i++) {
        max_draw_num_++; //�}�W�b�N���[�^�[�w�i
        max_draw_num_++; //�}�W�b�N���[�^�[��̌��݂̃}�W�b�N���x���\��
        pMagic = pElem->getValue();//��������̂ŃA�N�e�B�u�ł���͂�
        int lv_slecter_num = pMagic->max_level_+1;
        for (int j = 0; j < lv_slecter_num; j++) {
            max_draw_num_++;  //�e�}�W�b�N�v�f
        }
        pElem = pElem->_pNext;
    }
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    paInstancedata_MM_ = NEW VERTEX_instancedata[max_draw_num_];
    paInstancedata_MM_[0].px_x = C_PX(_x);
    paInstancedata_MM_[0].px_y = C_PX(_y);
    paInstancedata_MM_[0].depth_z = C_PX(_z);
    paInstancedata_MM_[0].local_px_x = 0.0f;
    paInstancedata_MM_[0].local_px_y = 0.0f;
    paInstancedata_MM_[0].r_sx = SC_R(_sx);
    paInstancedata_MM_[0].r_sy = SC_R(_sy);
    paInstancedata_MM_[0].rad_rz = ANG_RAD(_rz);
    paInstancedata_MM_[0].offset_u = 0;
    paInstancedata_MM_[0].offset_v = 0;
    memcpy(&(paInstancedata_MM_[0].r), &(_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);
    for (int i = 1; i < max_draw_num_; i++) {
        paInstancedata_MM_[i] = paInstancedata_MM_[0]; //�R�s�[���ď�����
    }
}

void MagicMeter::loadStatus(int prm_saveno) {
    st_[prm_saveno].seekg(std::stringstream::beg); //���o��
    loadProperties(st_[prm_saveno]);
}

void MagicMeter::saveStatus(int prm_saveno) {
    save(st_[prm_saveno]);
}

void MagicMeter::save(std::stringstream& sts) {
    sts << pMpBar_->getVal() << " ";
    Magic* pOrgMagic = lstMagic_.getCurrent();
    int len_magics = lstMagic_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->save(sts);
        pOrgMagic = lstMagic_.next();
    }
}

void MagicMeter::loadProperties(std::stringstream& sts) {
    int mp;
    sts >> mp;
    pMpBar_->setVal(mp);

    Magic* pOrgMagic = lstMagic_.getCurrent();
    int len_magics = lstMagic_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->loadProperties(sts);
        pOrgMagic = lstMagic_.next();
    }
}

void MagicMeter::initialize() {
    pMpBar_->setPosition(_x, _y + height_ + PX_C(16));
    pVreathBar_->setPosition(_x, _y + height_ + PX_C(16) + PX_C(16) );
    pMagicMeterStatus_->setPositionAt(this);

    getUvFlipper()->exec(FLIP_ORDER_LOOP, 10); //�A�j������
    Magic* pMagic;
    for (int i = 0; i < lstMagic_.length(); i++) {
        pMagic = lstMagic_.getFromFirst(i);
        papLvTgtMvCur_[i]->moveTo(pMagic->level_);
        papLvNowCur_[i]->moveTo(pMagic->level_);
        papLvCastingCur_[i]->moveTo(0);
        papLvCastingCur_[i]->markOff();
    }
}
void MagicMeter::onReset() {
    Magic* pMagic;
    for (int i = 0; i < lstMagic_.length(); i++) {
        pMagic = lstMagic_.getFromFirst(i);
        pMagic->resetTree(); //���Magic�����Z�b�g������B
        papLvTgtMvCur_[i]->moveTo(pMagic->level_);
        papLvNowCur_[i]->moveTo(pMagic->level_);
        papLvCastingCur_[i]->moveTo(0);
        papLvCastingCur_[i]->markOff();

        r_roll_[i] = 0.0f;
        r_roll_velo_[i] = 0.0f;

        pSeTx4Cast_->stop(i);
        pSeTx4Invoke_->stop(i);
    }
    pMpCostDispBar_->setVal(0);
    pVreathCostDispBar_->setVal(0);
    pDamageDispBar_->setVal(0);
}

void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    ////////////////////////�e���@�ɂ��Ă̏���//////////////////////////
    GgafProgress* pMagicProg;
    Magic* pMagic = nullptr;
    int pMagic_level, pMagic_new_level;
    MagicLvCursor001* pLvTgtMvCur;
    MagicLvCursor002* pLvNowCur;
    MagicLvCursor003* pLvCastingCur;

    for (int m = 0; m < lstMagic_.length(); m++) {
        pMagic = lstMagic_.getFromFirst(m);    //���@�I�u�W�F�N�g
        pMagicProg = pMagic->_pProg;           //���@�̐i����
        pMagic_level = pMagic->level_;         //���@�̌����x��
        pMagic_new_level = pMagic->new_level_; //���@�̐V���x���i�r�����E�������̏ꍇ�j
        pLvTgtMvCur = papLvTgtMvCur_[m];       //����J�[�\���I�u�W�F�N�g(�����ړ�)
        pLvNowCur = papLvNowCur_[m];           //�����x�������\���p�J�[�\���I�u�W�F�N�g
        pLvCastingCur = papLvCastingCur_[m];   //�r�������x�������\���p�J�[�\���I�u�W�F�N�g�iCASTING�Ȃǂ̕����j

        //���[���A�b�v
        r_roll_[m] += r_roll_velo_[m];
        if (r_roll_[m] < 0.0f) {
            r_roll_[m] = 0.0f;
            r_roll_velo_[m] = 0.0f;
        }
        if (r_roll_[m] > 1.0f) {
            r_roll_[m] = 1.0f;
            r_roll_velo_[m] = 0.0f;
        }

        //�r���J�n
        if (pMagicProg->hasJustChangedTo(Magic::STATE_CASTING)) {
            switch (pMagic->last_cast_) {
                case MAGIC_CAST_OK_LEVELUP: {
                    getSeTransmitter()->play(SE_EXECUTE_LEVELUP_MAGIC);
                    pSeTx4Cast_->play(m, true);
                    pLvTgtMvCur->blink(); //�s�J�s�J�I
                    pLvCastingCur->markOnLevelUpCast(pMagic_new_level);
                    break;
                }
                case MAGIC_CAST_LEVELDOWN: {
                    getSeTransmitter()->play(SE_EXECUTE_LEVELDOWN_MAGIC);
                    pLvTgtMvCur->blink(); //�s�J�s�J�I
                    pLvNowCur->moveSmoothTo(pMagic_new_level);
                    pLvNowCur->blink();
                    if (pMagic_new_level > 0) {
                        //���x��0�ȊO�ւ̃��x���_�E���Ȃ�� EFFECT �G�t�F�N�g
                        pLvCastingCur->markOnLevelDownCast(pMagic_new_level);
                    }
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
                    if ( pLvCastingCur->point_lv_ ==  pLvTgtMvCur->point_lv_) {
                        //���݉r�����̃��x���ōēx����
                        //�Ȃɂ����Ȃ�
                    } else {
                        getSeTransmitter()->play(SE_EXECUTE_CANCEL_LEVELUP_MAGIC);
                        pSeTx4Cast_->play(m);
                        pLvTgtMvCur->blink(); //�s�J�s�J�I
                        pLvCastingCur->markOnLevelUpCast(pMagic_new_level);
                    }
                    break;
                }
                case MAGIC_CAST_CANCEL_AND_LEVELDOWN: {
                    getSeTransmitter()->play(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC);
                    pLvTgtMvCur->blink(); //�s�J�s�J�I
                    pLvNowCur->moveSmoothTo(pMagic_new_level);
                    pLvNowCur->blink();
                    if (pMagic_new_level > 0) {
                        //���x��0�ȊO�ւ̃��x���_�E���Ȃ�� EFFECT �G�t�F�N�g
                        pLvCastingCur->markOnLevelDownCast(pMagic_new_level);
                    } else {
                        //���x��0�ȊO�ւ̃��x���_�E���Ȃ�΁A�����܂��B
                        pLvCastingCur->markOff();
                    }
                    break;
                }
                default: {
                    throwGgafCriticalException("["<<pMagic->getName()<<"] ���������B����͂����Ȃ��BpMagic->last_cast_="<<(pMagic->last_cast_));
                    break;
                }
            }
        }
        //�r����
        if (pMagicProg->get() == Magic::STATE_CASTING) {
            if (pMagic->new_level_ > pMagic_level) {
                //���x���A�b�v�Ȃ特���A�b�v
                float r = ((float)(pMagicProg->getFrame())) / ((float)(pMagic->time_of_next_state_));
                pSeTx4Cast_->getSe(m)->setFrequencyRate(1.0f + (r*3.0f));
            }
        }
        //�r�����ł͂Ȃ��Ȃ���
        if (pMagicProg->hasJustChangedFrom(Magic::STATE_CASTING)) {
            pSeTx4Cast_->stop(m); //����
        }

        //�����J�n��
        if (pMagicProg->hasJustChangedTo(Magic::STATE_INVOKING)) {
            switch (pMagic->last_invoke_) {
                case MAGIC_INVOKE_OK_LEVELUP: {
                    pSeTx4Invoke_->play(m, true);
                    pLvTgtMvCur->dispDisable(); //����s�\��
                    pLvNowCur->dispDisable();
                    if (pLvTgtMvCur->point_lv_ == pMagic_level) {
                        //�J�[�\���������x�����w���Ă���ꍇ�Ɍ���
                        //�V�������x���ɂ������蓮�����Ă�����B
                        pLvTgtMvCur->moveSmoothTo(pMagic_new_level);
                    }
                    frame invoking_frames = (frame)(pMagic->level_up_invoking_frames_[pMagic_level][pMagic_new_level]);
                    pLvNowCur->moveSmoothTo(pMagic_new_level, invoking_frames); //INVOKING�ɍ��킹�ē���
                    pLvCastingCur->markOnInvoke(pMagic_new_level);
                    break;
                }
                case MAGIC_INVOKE_OK_LEVELDOWN: {
                    //���x���_�E���́A�r���J�n���Ɍ��݃��x�������\���̃J�[�\���ړ������ɂ����Ȃ��Ă���B
                    //�̂ŁA�����ł͉������Ȃ��B
                    break;
                }
                default: {
                    throwGgafCriticalException("["<<pMagic->getName()<<"] ���������B����͂����Ȃ��BpMagic->last_invoke_="<<(pMagic->last_invoke_));
                    break;
                }
            }
        }
        //������
        if (pMagicProg->get() == Magic::STATE_INVOKING) {
            if (pMagic->new_level_ > pMagic_level) {
                //���x���A�b�v��
                float r = ((float)(pMagicProg->getFrame())) / ((float)(pMagic->time_of_next_state_));
                pSeTx4Invoke_->getSe(m)->setFrequencyRate(1.0f + (r*3.0f));//�������グ��
            }
        }
        //�����ł͂Ȃ��Ȃ���
        if (pMagicProg->hasJustChangedFrom(Magic::STATE_INVOKING)) {
            pSeTx4Invoke_->stop(m); //����
            pLvTgtMvCur->dispEnable(); //����s�\��������
            pLvNowCur->dispEnable();
        }
        //���ʊJ�n��
        if (pMagicProg->hasJustChangedTo(Magic::STATE_EFFECT_START)) {
            switch (pMagic->last_effect_) {
                case MAGIC_EFFECT_OK_LEVELUP: {
                    if (pMagic->effecting_frames_base_ == 0) {
                        //���������@�̏ꍇ
                        getSeTransmitter()->play(SE_EFFECT_MAGIC);
                        pLvCastingCur->markOnEffect(pMagic_level);
                    } else {
                        //�ʏ햂�@�̏ꍇ
                        getSeTransmitter()->play(SE_EFFECT_MAGIC);
                        pLvCastingCur->markOnEffect(pMagic_level);
                    }
                    break;
                }
                case MAGIC_EFFECT_OK_LEVELDOWN: {
                    if (pMagic->effecting_frames_base_ == 0) {
                        //���U���@�̏I���̃��x���_�E���ꍇ
                        _TRACE_(FUNC_NAME<<" ["<<pMagic->getName()<<"] ���U���@�̃��x���_�E���̃��x���_�E��");
                        pLvNowCur->moveSmoothTo(pMagic_level);
                    } else {
                        //���ʂ̃��x���_�E��
                        getSeTransmitter()->play(SE_EXECUTE_LEVELDOWN_MAGIC);
                        if (pLvTgtMvCur->point_lv_ == pMagic->last_level_) {
                            //�������Ԗ����A���邢��MP�͊����A
                            //�J�[�\�������x���_�E���O�̌��s���x�����w���Ă���΁A
                            //��������A�J�[�\�����ꏏ�Ɉړ�
                            pLvTgtMvCur->moveSmoothTo(pMagic_level);
                        }
                        pLvNowCur->moveSmoothTo(pMagic_level);
                        pLvNowCur->blink();
                        if (pMagic_level > 0) {
                            pLvCastingCur->markOnEffect(pMagic_level);
                        }
                    }
                    break;
                }
                default: {
                    throwGgafCriticalException("["<<pMagic->getName()<<"] ���������B����͂����Ȃ��BpMagic->last_effect_="<<(pMagic->last_effect_));
                    break;
                }
            }
        }

        //STATE_NOTHING�ֈڍs����
        if (pMagicProg->hasJustChangedTo(Magic::STATE_NOTHING)) {
            if (pMagicProg->hasJustChangedFrom(Magic::STATE_CASTING)) { //�r����STATE_NOTHING
                //��r���i�r�����L�����Z������ or �r���������r����������MP������Ȃ������j
                _TRACE_(FUNC_NAME<<" ["<<pMagic->getName()<<"] �r����STATE_NOTHING ��r�����B");
                pLvCastingCur->markOff(); //�}�[�N�I�t�I
                pLvNowCur->moveSmoothTo(pMagic_level);
                pLvTgtMvCur->moveSmoothTo(pMagic_level); //���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
                if (pMagic->last_invoke_ == MAGIC_INVOKE_NG_MP_IS_SHORT) {
                    _TRACE_(FUNC_NAME<<" ["<<pMagic->getName()<<"] ��r�����̌����� MAGIC_INVOKE_NG_MP_IS_SHORT ���������� ");
                    getSeTransmitter()->play(SE_NG_MP_IS_SHORT);
                } else {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                }
            }
            if (pMagicProg->hasJustChangedFrom(Magic::STATE_INVOKING)) {  //������STATE_NOTHING
                //�󔭓��i�����������A�����������AMP������Ȃ������̂ŁA���ʊJ�n�o���Ȃ������j
                _TRACE_(FUNC_NAME<<" ["<<pMagic->getName()<<"] ������STATE_NOTHING �󔭓��� ");
                pLvCastingCur->markOff(); //�}�[�N�I�t�I
                pLvNowCur->moveSmoothTo(pMagic_level);
                pLvTgtMvCur->moveSmoothTo(pMagic_level); //���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
                if (pMagic->last_effect_ == MAGIC_EFFECT_NG_MP_IS_SHORT) {
                    _TRACE_(FUNC_NAME<<" ["<<pMagic->getName()<<"] �󔭓����̌����� MAGIC_EFFECT_NG_MP_IS_SHORT ���������� ");
                    getSeTransmitter()->play(SE_NG_MP_IS_SHORT);
                } else {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                }
            }
        }

        //�����������x���_�E���x��
        if (pMagic->lvinfo_[pMagic_level].remained_frame_of_effecting == fraeme_of_notice_remaind_) {
            getSeTransmitter()->play(SE_NOTICE_LEVELDOWN_MAGIC);
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

    ////////////////////////���@���[�^�[�ɂ��Ă̏���//////////////////////////
    VirtualButton* pVbPlay = VB_PLAY;
    MyShip* pMyShip = pMYSHIP;
    if (pMyShip->canControl() && pVbPlay->isPressed(VB_POWERUP)) {
        alpha_velo_ = 0.05f;
        Magic* pActiveMagic = lstMagic_.getCurrent();     //�A�N�e�B�u�Ȗ��@
        int active_idx = lstMagic_.getCurrentIndex();     //�A�N�e�B�u�Ȗ��@�̃C���f�b�N�X
        progress active_prg = pActiveMagic->getProgress()->get();  //�A�N�e�B�u�Ȗ��@�̐i��
        if (pMyShip->canControl() && pVbPlay->isPushedDown(VB_POWERUP)) {
            rollOpen(active_idx);
        }

        if (pVbPlay->isAutoRepeat(VB_RIGHT)) {    //�u���v������
            //���x���\��
            if (active_prg == Magic::STATE_CASTING) {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvCastingCur_[active_idx]->point_lv_) {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvCastingCur_[active_idx]->point_lv_); //���x���J�[�\�����r���惌�x���ɖ߂�
                }
            } else {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvNowCur_[active_idx]->point_lv_) {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvNowCur_[active_idx]->point_lv_); //���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
                }
            }
            rollClose(active_idx); //���݃��[���N���[�Y

            lstMagic_.next(); //���[�^�[���P�i�߂�
            pActiveMagic= lstMagic_.getCurrent();     //�X�V
            active_idx = lstMagic_.getCurrentIndex(); //�X�V
            active_prg = pActiveMagic->getProgress()->get(); //�X�V

            rollOpen(active_idx);  //�i�߂�������[���I�[�v��
            pMainCur_->moveTo(active_idx); //���[�^�[�J�[�\�����P�i�߂�
            getSeTransmitter()->play(SE_CURSOR_MOVE_METER);

        } else if (pVbPlay->isAutoRepeat(VB_LEFT)) { //�u���v������
            //���x���\��
            if (active_prg == Magic::STATE_CASTING) {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvCastingCur_[active_idx]->point_lv_) {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvCastingCur_[active_idx]->point_lv_); //���x���J�[�\�����r���惌�x���ɖ߂�
                }
            } else {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvNowCur_[active_idx]->point_lv_) {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvNowCur_[active_idx]->point_lv_); //���x���J�[�\�����A�N�e�B�u���x���ɖ߂�
                }
            }
            rollClose(active_idx); //���݃��[���N���[�Y

            lstMagic_.prev(); //���[�^�[���P�߂�
            pActiveMagic= lstMagic_.getCurrent();     //�X�V
            active_idx = lstMagic_.getCurrentIndex(); //�X�V
            active_prg = pActiveMagic->getProgress()->get(); //�X�V

            rollOpen(active_idx); //�߂���������[���I�[�v��
            pMainCur_->moveTo(active_idx); //���[�^�[�J�[�\�����P�߂�
            getSeTransmitter()->play(SE_CURSOR_MOVE_METER);

        } else if (pVbPlay->isAutoRepeat(VB_UP) ) {  // �u���v������
            if (pActiveMagic->max_level_ > papLvTgtMvCur_[active_idx]->point_lv_) {
                getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL);
                papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvTgtMvCur_[active_idx]->point_lv_ + 1);
            }

        } else if (pVbPlay->isAutoRepeat(VB_DOWN)) {  //�u���v������
            if (0 < papLvTgtMvCur_[active_idx]->point_lv_) {
                getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL);
                papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvTgtMvCur_[active_idx]->point_lv_ - 1);
            }
        } else {

        }
        //MP�R�X�g�o�[
        if (r_roll_[active_idx] > 0.01f) {
            if (papLvTgtMvCur_[active_idx]->point_lv_ == pActiveMagic->level_) {
                //�J�[�\������茻�݂Ɠ������x�����w���Ă���ꍇ
                pMpCostDispBar_->setVal(0);
            } else if (papLvTgtMvCur_[active_idx]->point_lv_ > pActiveMagic->level_) {
                //�J�[�\�������݂�荂�����x�����w���Ă���ꍇ
                //MP�R�X�g�𕉂̐Ԃ̕\��
                pMpCostDispBar_->setVal(
                  -1*pActiveMagic->level_up_cost_[pActiveMagic->level_][papLvTgtMvCur_[active_idx]->point_lv_]
                );
            } else {
                //�J�[�\�������݂��Ⴂ���x�����w���Ă���ꍇ
                //���̐̕\��
                if (pActiveMagic->keep_cost_base_ <= 0) {
                    //�ێ��R�X�g�����̏ꍇ�̂�MP�Ҍ��o�[�\��
                    pMpCostDispBar_->setVal(
                      pActiveMagic->calcReduceMp(pActiveMagic->level_,  papLvTgtMvCur_[active_idx]->point_lv_)
                    );
                } else {
                    //�ێ��R�X�g�L��̏ꍇ�AMP�Ҍ��͖���
                }
            }
        } else {
            pMpCostDispBar_->setVal(0);
        }

        //Vreath�o�[���A�N�e�B�u�������ꍇ�AVreath�����\��
        if (pActiveMagic == pVreathMagic_) {
            VreathMagic* pVM = (VreathMagic*)pActiveMagic;
            if (r_roll_[active_idx] > 0.01f) {
                if (papLvTgtMvCur_[active_idx]->point_lv_ == pVM->level_) {
                    //�J�[�\������茻�݂Ɠ������x�����w���Ă���ꍇ
                    pVreathCostDispBar_->setVal(0);
                } else if (papLvTgtMvCur_[active_idx]->point_lv_ > pVM->level_) {
                    //�J�[�\�������݂�荂�����x�����w���Ă���ꍇ
                    //���̐̕\��
                    pVreathCostDispBar_->setVal(
                            (int)(pVM->calcTotalVreath(pActiveMagic->level_,  papLvTgtMvCur_[active_idx]->point_lv_))
                    );
                } else {
                    //�J�[�\�������݂��Ⴂ���x�����w���Ă���ꍇ
                    pVreathCostDispBar_->setVal(0);
                }
            } else {
                pVreathCostDispBar_->setVal(0);
            }
        } else {
            pVreathCostDispBar_->setVal(0);
        }

        //�u����v��
        if (pVbPlay->isPushedDown(VB_SHOT1) || pVbPlay->isPushedDown(VB_SHOT2) || pVbPlay->isPushedDown(VB_TURBO)) {
            int r = pActiveMagic->cast(papLvTgtMvCur_[active_idx]->point_lv_);
            switch (r) {
                case MAGIC_CAST_NG_INVOKING_NOW: {
                    getSeTransmitter()->play(SE_BAD_OPERATION);
                    break;
                }
                case MAGIC_CAST_NG_MP_IS_SHORT: {
                    getSeTransmitter()->play(SE_NG_MP_IS_SHORT);
                    break;
                }
            }
        }
    } else  {
        alpha_velo_ = -0.02f;
        if (!pMyShip->canControl() || pVbPlay->isReleasedUp(VB_POWERUP)) {
            rollClose(lstMagic_.getCurrentIndex());
        }
        pMpCostDispBar_->setVal(0);
        pVreathCostDispBar_->setVal(0);
    }

    addAlpha(alpha_velo_);
    if (getAlpha() < 0.3f) {
        setAlpha(0.3f); //��A�N�e�B�u���̂�������\��
    } else if (getAlpha() > 1.0f) {
        setAlpha(1.0f); //�A�N�e�B�u���̃n�b�L���\��
    }
}

void MagicMeter::onInactive() {
}

void MagicMeter::processDraw() {
    GgafDxMassBoardEffect* const pMassBoardEffect = _pMassBoardEffect;
    ID3DXEffect* pID3DXEffect = pMassBoardEffect->_pID3DXEffect;
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();

    HRESULT hr;
    //�p���[���[�^�[
    //[====]���P�̑傫�� [====][====][====]
    MagicList::Elem* pElem = lstMagic_.getElemFirst();
    Magic* pMagic;
    int pMagic_level;
    int len_magics = lstMagic_.length();
    int n = 0;
    float u,v;
    float x = float(C_PX(_x));
    float y = float(C_PX(_y));
    float z = float(C_PX(_z));
    float alpha = getAlpha();
    VERTEX_instancedata* p = paInstancedata_MM_;

    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->getValue();//��������̂ŃA�N�e�B�u�ł���͂�
        pMagic_level = pMagic->level_;
        float wx = width_px_*i;

        //�}�W�b�N���[�^�[�w�i
        p->px_x = x + wx;
        p->px_y = y;
        p->depth_z = z;

        if (pMagic_level > 0 && pMagic->lvinfo_[pMagic_level].remained_frame_of_effecting <= fraeme_of_notice_remaind_) {
            p->r = 2.0;   p->g = 0.5;   p->b = 0.5;
//            pUvFlipper->getUV(1, u, v); //�p�^�[��1�͐Ԕw�i�A�c�莞�Ԃ���΂���������
        } else {
            p->r = 1.0;   p->g = 1.0;   p->b = 1.0;
//            pUvFlipper->getUV(0, u, v); //�p�^�[��0�͒ʏ�w�i
        }
        p->a = alpha;
        pUvFlipper->getUV(0, u, v);
        p->offset_u = u;
        p->offset_v = v;
        ++p; n++;

        //�}�W�b�N���[�^�[��̌��݂̃}�W�b�N���x���\��
        p->px_x = x + wx;
        p->px_y = y;
        p->depth_z = z;
        p->r = 1.0;   p->g = 1.0;   p->b = 1.0;
        p->a = alpha*3; //�����\��
        pUvFlipper->getUV(pMagic->lvinfo_[pMagic_level].pno_, u, v);
        p->offset_u = u;
        p->offset_v = v;
        ++p; n++;

        float rr = r_roll_[i];
        if (rr > 0.1f) {
            //�e�}�W�b�N�v�f
            int lv_slecter_num = pMagic->max_level_+1;
            for (int j = 0; j < lv_slecter_num; j++) {

                //���@��
                p->px_x = x + wx;
                p->px_y = y - (height_px_*(j+1)*rr);
                p->depth_z = z;
                p->a = alpha*rr; //�A�N�e�B�u�ȗ�͕\��
                if (pMagic->chkCastAble(j) <= MAGIC_CAST_NG_MP_IS_SHORT) {
                    //�r���s�\�� (MAGIC_CAST_NG_MP_IS_SHORT �� MAGIC_CAST_NG_INVOKING_NOW)
//                    pUvFlipper->getUV(pMagic->lvinfo_[j].pno_ + 1, u, v); //�E�ׂ̃e�N�X�`���p�^�[���� DISABLE �ȃp�^�[���O��
                    p->r = 0.3;  p->g = 0.3;  p->b = 0.3;
                } else {
                    //�r���\�\��
//                    pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
                    p->r = 1.0;  p->g = 1.0;  p->b = 1.0;
                }
                pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
                p->offset_u = u;
                p->offset_v = v;
                p++; n++;
            }
        }
        pElem = pElem->_pNext;
    }
    _pMassBoardModel->GgafDxMassBoardModel::draw(this, n, paInstancedata_MM_);
}

void MagicMeter::rollOpen(int prm_meter_index) {
    r_roll_velo_[prm_meter_index] = 0.1f;
}

void MagicMeter::rollClose(int prm_meter_index) {
    r_roll_velo_[prm_meter_index] = -0.1f;
}

MagicMeter::~MagicMeter() {
    GGAF_DELETEARR(papLvTgtMvCur_);
    GGAF_DELETEARR(papLvNowCur_);
    GGAF_DELETEARR(papLvCastingCur_);
    GGAF_DELETEARR(r_roll_);
    GGAF_DELETEARR(r_roll_velo_);
    GGAF_DELETE(pSeTx4Cast_);
    GGAF_DELETE(pSeTx4Invoke_);

    GGAF_DELETEARR(paInstancedata_MM_);
}
