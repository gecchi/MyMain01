#include "stdafx.h"
#include "MagicLvCursor003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor003::MagicLvCursor003(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        MagicLvCursor(prm_name, "MagicLvCursor003", prm_pMagicMeter, prm_pMagic) {
    _class_name = "MagicLvCursor003";
    pMagicMeter_ = prm_pMagicMeter;
    pMagic_ = prm_pMagic;
    magic_index_ = pMagicMeter_->lstMagic_.indexOf(pMagic_);
    if (magic_index_ < 0) {
        throwGgafCriticalException("MagicLvCursor003::MagicLvCursor003 prm_pMagic("<<prm_pMagic->getName()<<")��"<<
                                   "MagicMeter�ɓo�^����Ă��܂���B");
    }
}

void MagicLvCursor003::initialize() {
    MagicLvCursor::initialize();
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0,3);
    pUvFlipper->setActivePtn(3);
    pUvFlipper->exec(NOT_ANIMATED);
    pScaler_->forceRange(1000, 10000);
}

void MagicLvCursor003::processPreDraw() {
    //MagicLvCursor::processPreDraw(); �y�сAMagicLvCursor::processAfterDraw()
    //�ł́AY���W���[���̒Ǐ]�ƁA���[���I�[�v���E�N���[�Y�ɔ����������������s�Ȃ��Ă���B
    //�������A�{�J�[�\���i"CASTING"�Ȃǂ̕����j���[�������Ă������Ȃ��悤�ɂ��邽�߁A
    //�I�[�o�[���C�h���A��������������邱�Ƃɂ���B
    //Y���W���[���Ǐ]�͍s���̂ŁA���̕����̂ݎ������s�����Ƃɂ���B
    //MagicLvCursor::processPreDraw(); �y�сAMagicLvCursor::processAfterDraw() �̏�����ύX������A
    //�������ύX����B
    tmp_y_ = _y; //�ޔ�
    _y += (1.0 * pMagicMeter_->height_ * (point_lv_+1) * (1.0 - pMagicMeter_->r_roll_[magic_index_]));
    DefaultBoardActor::processPreDraw();
}

void MagicLvCursor003::processAfterDraw() {
    DefaultBoardActor::processAfterDraw();
    _y = tmp_y_; //���A
}

void MagicLvCursor003::markOff() {
    getUvFlipper()->stopFlip();
    pAFader_->reset();
    setAlpha(0);
}

void MagicLvCursor003::markOnLevelUpCast(int prm_lv) {
    setAlpha(0);
    pAFader_->transitionLinerUntil(1.0, 20);
    moveTo(prm_lv);
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0,3);
    pUvFlipper->setActivePtn(0);
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    setScale(10000);
    pScaler_->transitionLinerUntil(1000, 20);
    setRzFaceAng(D180ANG);
    getKuroko()->turnRzFaceAngTo(0, D180ANG/20, 0, TURN_COUNTERCLOCKWISE);
}

void MagicLvCursor003::markOnLevelDownCast(int prm_lv) {
    setAlpha(1.0);
    pAFader_->transitionLinerUntil(0, 20);
    moveTo(prm_lv);
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(8, 11);
    pUvFlipper->setActivePtn(8);
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    setScale(1000);
    pScaler_->transitionLinerUntil(10000, 20);
}

void MagicLvCursor003::markOnInvoke(int prm_lv) {
    moveTo(prm_lv);
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(4, 7);
    pUvFlipper->setActivePtn(4);
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
}

void MagicLvCursor003::markOnEffect(int prm_lv) {
    setAlpha(1.0);
    pAFader_->transitionLinerUntil(0, 20);
    moveTo(prm_lv);
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(8, 11);
    pUvFlipper->setActivePtn(8);
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    setScale(1000);
    pScaler_->transitionLinerUntil(10000, 20);
}

MagicLvCursor003::~MagicLvCursor003() {
}
