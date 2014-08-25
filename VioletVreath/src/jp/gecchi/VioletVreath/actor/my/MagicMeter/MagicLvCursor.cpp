#include "MagicLvCursor.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor::MagicLvCursor(const char* prm_name, const char* prm_model, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        DefaultBoardActor(prm_name, prm_model) {
    _class_name = "MagicLvCursor";
    pAFader_ = NEW GgafDxAlphaFader(this);
    pScaler_ = NEW GgafDxScaler(this);
    pMagicMeter_ = prm_pMagicMeter;
    pMagic_ = prm_pMagic;
    magic_index_ = pMagicMeter_->lstMagic_.indexOf(pMagic_);
    if (magic_index_ < 0) {
        throwGgafCriticalException("MagicLvCursor::MagicLvCursor prm_pMagic("<<prm_pMagic->getName()<<")��"<<
                                   "MagicMeter�ɓo�^����Ă��܂���B");
    }
    point_lv_ = 0;
    tmp_y_ = _y;
    tmp_alpha_ = _alpha;
    tx_ = 0;
    ty_ = 0;
    setZWriteEnable(false);
}

void MagicLvCursor::initialize() {
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    //MagicMeter�̍��W����܂��Ă���s������
    _x = tx_ = pMagicMeter_->_x + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    _y = ty_ = pMagicMeter_->_y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
    pScaler_->forceRange(1000, 3000);
}

void MagicLvCursor::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->behave();
    if (pKuroko->asstA()->isJustFinishSlidingMv()) {
        //���z�ʒu�ɕ␳
        _x = tx_;
        _y = ty_;
    }
    getUvFlipper()->behave();
    pAFader_->behave();
    pScaler_->behave();
}
void MagicLvCursor::processPreDraw() {
    //�J�[�\���֘A��
    //�������߂ɔ����Ȃ�i������j�悤�ɂ���
    //��{��pAFader_�A�`�掞�̂݃��[�������̔��������l��
    float rr = pMagicMeter_->r_roll_[magic_index_];
    float alpha_r = rr * 2 - 1.0f;
    if (alpha_r < 0.0f) {
        alpha_r = 0.0f;
    }
    tmp_alpha_ = getAlpha();//�ޔ�
    setAlpha(alpha_r*tmp_alpha_*pMagicMeter_->getAlpha());
    //�����ŁA���[����Y���W��␳
    tmp_y_ = _y; //�ޔ�
    _y += (1.0 * pMagicMeter_->height_ * (point_lv_+1) * (1.0 - rr));
    DefaultBoardActor::processPreDraw();

    //Y���W���[���Ǐ]������ς�����AMagicLvCursor003::processPreDraw() �����l�̕ύX���I
}

void MagicLvCursor::processAfterDraw() {
    DefaultBoardActor::processAfterDraw();
    _y = tmp_y_; //���A
    setAlpha(tmp_alpha_); //���A
    //Y���W���[���Ǐ]������ς�����AMagicLvCursor003::processAfterDraw() �����l�̕ύX���I
}

void MagicLvCursor::moveTo(int prm_lv) {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->asstA()->stopSlidingMv();
    pKuroko->stopMv();
    point_lv_ = prm_lv;
    _x = tx_ = pMagicMeter_->_x + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    _y = ty_ = pMagicMeter_->_y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
}

void MagicLvCursor::moveSmoothTo(int prm_lv, frame prm_target_frames, float prm_p1, float prm_p2) {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->stopMv();
    //Y���W�̃��[���i�X���C�h�\���j�̕��l��������Y���W��LV�J�[�\���ړ��v�Z���s���Ă���B
    //processPreDraw()�Ń��[������␳����B
    point_lv_ = prm_lv;
    tx_ = pMagicMeter_->_x + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    ty_ = pMagicMeter_->_y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
    pKuroko->setMvAngTwd(tx_, ty_);
    pKuroko->asstA()->slideMvByDt(UTIL::getDistance(_x, _y, tx_, ty_), (int)prm_target_frames,
                                  prm_p1, prm_p2, 0, true); //���[�����l�������ɂƂ肠�����ړ�
}

void MagicLvCursor::blink() {
    pAFader_->beat(6, 3, 0, 3, 7.5); //�s�J�s�J�A+0.5�͍Ō�͕\���I����
    pScaler_->beat(12, 6, 0, 6, 3);
}

MagicLvCursor::~MagicLvCursor() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE(pScaler_);
}
