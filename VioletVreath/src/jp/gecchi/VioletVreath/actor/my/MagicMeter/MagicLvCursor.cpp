#include "stdafx.h"
#include "MagicLvCursor.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor::MagicLvCursor(const char* prm_name, const char* prm_model, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        DefaultBoardActor(prm_name, prm_model) {
    _class_name = "MagicLvCursor";
    pMagicMeter_ = prm_pMagicMeter;
    pMagic_ = prm_pMagic;
    magic_index_ = pMagicMeter_->lstMagic_.indexOf(pMagic_);
    if (magic_index_ < 0) {
        throwGgafCriticalException("MagicLvCursor::MagicLvCursor prm_pMagic("<<prm_pMagic->getName()<<")��"<<
                                   "MagicMeter�ɓo�^����Ă��܂���B");
    }
    point_lv_ = 0;
    tmp_Y_ = _Y;
    tmp_alpha_ = _alpha;
    tX_ = 0;
    tY_ = 0;
    setZWriteEnable(false);
}

void MagicLvCursor::initialize() {
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    //MagicMeter�̍��W����܂��Ă���s������
    _X = tX_ = pMagicMeter_->_X + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    _Y = tY_ = pMagicMeter_->_Y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    _pScaler->forceRange(1000, 3000);
}

void MagicLvCursor::processBehavior() {

    if (_pKurokoA->isJustFinishSlidingMv()) {
        //���z�ʒu�ɕ␳
        _X = tX_;
        _Y = tY_;
    }
    _pKurokoA->behave();
    _pUvFlipper->behave();
    _pAFader->behave();
    _pScaler->behave();
}
void MagicLvCursor::processPreDraw() {
    //�J�[�\���֘A��
    //�������߂ɔ����Ȃ�i������j�悤�ɂ���
    //��{��_pAFader�A�`�掞�̂݃��[�������̔��������l��
    float rr = pMagicMeter_->paFloat_rr_[magic_index_];
    float alpha_r = rr * 2 - 1.0f;
    if (alpha_r < 0.0f) {
        alpha_r = 0.0f;
    }
    tmp_alpha_ = getAlpha();//�ޔ�
    setAlpha(alpha_r*tmp_alpha_*pMagicMeter_->getAlpha());
    //�����ŁA���[����Y���W��␳
    tmp_Y_ = _Y; //�ޔ�
    _Y += (1.0 * pMagicMeter_->height_ * (point_lv_+1) * (1.0 - rr));
    DefaultBoardActor::processPreDraw();

    //Y���W���[���Ǐ]������ς�����AMagicLvCursor003::processPreDraw() �����l�̕ύX���I
}

void MagicLvCursor::processAfterDraw() {
    DefaultBoardActor::processAfterDraw();
    _Y = tmp_Y_; //���A
    setAlpha(tmp_alpha_); //���A

    //Y���W���[���Ǐ]������ς�����AMagicLvCursor003::processAfterDraw() �����l�̕ύX���I
}

void MagicLvCursor::moveTo(int prm_lv) {
    _pKurokoA->_slide_mv_flg = false;
    _pKurokoA->setMvVelo(0);
    _pKurokoA->setMvAcce(0);
    point_lv_ = prm_lv;
    _X = tX_ = pMagicMeter_->_X + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    _Y = tY_ = pMagicMeter_->_Y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
}

void MagicLvCursor::moveSmoothTo(int prm_lv, frame prm_target_frames, float prm_p1, float prm_p2) {
    _pKurokoA->setMvVelo(0);
    _pKurokoA->setMvAcce(0);
    //Y���W�̃��[���i�X���C�h�\���j�̕��l��������Y���W��LV�J�[�\���ړ��v�Z���s���Ă���B
    //processPreDraw()�Ń��[������␳����B
    point_lv_ = prm_lv;
    tX_ = pMagicMeter_->_X + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    tY_ = pMagicMeter_->_Y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
    _pKurokoA->setMvAngTwd(tX_, tY_);
    _pKurokoA->slideMvByDT(0, UTIL::getDistance(_X, _Y, tX_, tY_),
                                        (int)prm_target_frames, prm_p1, prm_p2); //���[�����l�������ɂƂ肠�����ړ�
}

void MagicLvCursor::blink() {
    _pAFader->beat(6, 3, 0, 0, 7.5); //�s�J�s�J�A+0.5�͍Ō�͕\���I����
    _pScaler->beat(12, 6, 0, 3);
}

MagicLvCursor::~MagicLvCursor() {
}
