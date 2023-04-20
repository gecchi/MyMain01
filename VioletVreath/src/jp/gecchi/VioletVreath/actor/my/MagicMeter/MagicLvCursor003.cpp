#include "MagicLvCursor003.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"



using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor003::MagicLvCursor003(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        MagicLvCursor(prm_name, "MagicLvCursor003", prm_pMagicMeter, prm_pMagic) {
    _class_name = "MagicLvCursor003";
    pMagicMeter_ = prm_pMagicMeter;
    pMagic_ = prm_pMagic;
    magic_index_ = pMagicMeter_->lstMagic_.indexOf(pMagic_);
    if (magic_index_ < 0) {
        throwCriticalException("prm_pMagic("<<prm_pMagic->getName()<<")��"<<
                                   "MagicMeter�ɓo�^����Ă��܂���B");
    }
}

void MagicLvCursor003::initialize() {
    MagicLvCursor::initialize();
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);
    pUvFlipper->exec(NOT_ANIMATED);
    getScaler()->setRange(1000, 10000);
}

void MagicLvCursor003::processPreDraw() {
    //MagicLvCursor::processPreDraw(); �y�сAMagicLvCursor::processAfterDraw()
    //�ł́AY���W���[���̒Ǐ]�ƁA���[���I�[�v���E�N���[�Y�ɔ����������������s�Ȃ��Ă���B
    //�������A�{�J�[�\���i"CASTING"�Ȃǂ̕����j���[�������Ă������Ȃ��悤�ɂ��邽�߁A
    //�I�[�o�[���C�h���A��������������邱�Ƃɂ���B
    //Y���W���[���Ǐ]�͍s���̂ŁA���̕����̂ݎ������s�����Ƃɂ���B
    //MagicLvCursor::processPreDraw(); �y�сAMagicLvCursor::processAfterDraw() �̏�����ύX������A
    //TODO:�������ύX����B
    tmp_y_ = _y; //�ޔ�
    _y += (1.0 * pMagicMeter_->height_ * (point_lv_+1) * (1.0 - pMagicMeter_->r_roll_[magic_index_]));
    DefaultBoardActor::processPreDraw();
}

void MagicLvCursor003::processAfterDraw() {
    DefaultBoardActor::processAfterDraw();
    _y = tmp_y_; //���A
}

void MagicLvCursor003::markOff() {
    getUvFlipper()->stop();
    getAlphaFader()->reset();
    setAlpha(0);
}

void MagicLvCursor003::markOnLevelUpCast(int prm_lv) {
    setAlpha(0);
    getAlphaFader()->transitionLinearUntil(1.0, 20);
    moveTo(prm_lv);
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0,3);
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    setScale(10000);
    getScaler()->transitionLinearUntil(1000, 20);
    setRzFaceAng(D180ANG);
    getLocoVehicle()->turnRzFaceAngTo(0, D180ANG/20, 0, TURN_COUNTERCLOCKWISE);
}

void MagicLvCursor003::markOnLevelDownCast(int prm_lv) {
    setAlpha(1.0);
    getAlphaFader()->transitionLinearUntil(0, 20);
    moveTo(prm_lv);
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(8, 11);
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    setScale(1000);
    getScaler()->transitionLinearUntil(10000, 20);
}

void MagicLvCursor003::markOnInvoke(int prm_lv) {
    moveTo(prm_lv);
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(4, 7);
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
}

void MagicLvCursor003::markOnEffect(int prm_lv) {
    setAlpha(1.0);
    getAlphaFader()->transitionLinearUntil(0, 20);
    moveTo(prm_lv);
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(8, 11);
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    setScale(1000);
    getScaler()->transitionLinearUntil(10000, 20);
}

MagicLvCursor003::~MagicLvCursor003() {
}
