#include "stdafx.h"
#include "VvvCursor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvCursor::VvvCursor(const char* prm_name) :
        GgafLib::DefaultSpriteActor(prm_name, "Cursor") {
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //���[���h�ϊ��̓r���{�[�h��Rz��]�ɋ���
    effectBlendOne(); //�G�t�F�N�g�e�N�j�b�N�͉��Z�����ɋ���
    setZEnable(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //Z�o�b�t�@�͏������ݖ����ɋ���
    setSpecialDrawDepth(1); //�`�揇�����őO�ʕ`��ɋ����B���b�N�I���G�t�F�N�g���B��Ȃ��悤�ɂ��邽�߁B
    tX_ = _X;
    tY_ = _Y;
    tZ_ = _Z;
    useProgress(10);
    _pProg->reset(CUR_SINK);
}

void VvvCursor::initialize() {
    //���W�ݒ�
    _X = _Y = _Z = 0; //(0,0,0) �͉�ʂ̒��S
    _pKurokoA->_angveloFace[AXIS_Z] = 1000;
    _pScaler->forceRange(2000, 4000);
    _pScaler->beat(30, 2, 2, -1); //�������[�v
    _pAFader->setAlpha(0);
}

void VvvCursor::processBehavior() {
    switch (_pProg->get()) {
        case CUR_SINK: {
            break;
        }
        case CUR_ON_MOVE: {
            _pAFader->setAlpha(0.9);
            _pProg->change(CUR_STAY);
            break;
        }
        case CUR_STAY: {
            if (_pProg->getFrameInProgress() > 60) {
                _pAFader->fadeLinerUntil(0.0, 120);
                _pProg->change(CUR_SINK);
            }
            break;
        }
        default: {
            break;
        }
    }
    if (_pKurokoA->isJustFinishSlidingMv()) {
        //���z�ʒu�ɕ␳
        _X = tX_;
        _Y = tY_;
        _Z = tZ_;
    }
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
    _pAFader->behave();
}
void VvvCursor::sink() {
    _pProg->change(CUR_SINK);
}

void VvvCursor::moveTo(coord X, coord Y, coord Z) {
    _pKurokoA->_slide_mv_flg = false;
    _pKurokoA->setMvVelo(0);
    _pKurokoA->setMvAcce(0);
    tX_ = X;
    tY_ = Y;
    tZ_ = Z;
    _pKurokoA->setMvAngTwd(tX_, tY_, tZ_);
    _pKurokoA->slideMvByDT(0, UTIL::getDistance(_X, _Y, _Z, tX_, tY_, tZ_),
                                        20, 0.3f, 0.7f);
    _pProg->change(CUR_ON_MOVE);
}

VvvCursor::~VvvCursor() {
}
