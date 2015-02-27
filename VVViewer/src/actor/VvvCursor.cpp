#include "VvvCursor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvCursor::VvvCursor(const char* prm_name) :
        GgafLib::DefaultSpriteActor(prm_name, "Cursor") {
    pAFader_ = NEW GgafDxAlphaFader(this);
    pScaler_ = NEW GgafDxScaler(this);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //���[���h�ϊ��̓r���{�[�h��Rz��]�ɋ���
    effectBlendOne(); //�G�t�F�N�g�e�N�j�b�N�͉��Z�����ɋ���
    setZEnable(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //Z�o�b�t�@�͏������ݖ����ɋ���
    setSpecialDrawDepth(1); //�`�揇�����őO�ʕ`��ɋ����B���b�N�I���G�t�F�N�g���B��Ȃ��悤�ɂ��邽�߁B
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
    useProgress(10);
    _pProg->reset(CUR_SINK);
}

void VvvCursor::initialize() {
    //���W�ݒ�
    _x = _y = _z = 0; //(0,0,0) �͉�ʂ̒��S
    getKuroko()->_angvelo_face[AXIS_Z] = 1000;
    pScaler_->forceRange(2000, 4000);
    pScaler_->beat(30, 2, 0, 28, -1); //�������[�v
    setAlpha(0);
}

void VvvCursor::processBehavior() {
    switch (_pProg->get()) {
        case CUR_SINK: {
            break;
        }
        case CUR_ON_MOVE: {
            setAlpha(0.9);
            _pProg->change(CUR_STAY);
            break;
        }
        case CUR_STAY: {
            if (_pProg->getFrame() > 60) {
                pAFader_->transitionLinerUntil(0.0, 120);
                _pProg->change(CUR_SINK);
            }
            break;
        }
        default: {
            break;
        }
    }

    _pUvFlipper->behave();
    getKuroko()->behave();
    if (getKuroko()->asstA()->isJustFinishSlidingMv()) {
        //���z�ʒu�ɕ␳
        _x = tx_;
        _y = ty_;
        _z = tz_;
    }

    pScaler_->behave();
    pAFader_->behave();
}
void VvvCursor::sinkMe() {
    _pProg->change(CUR_SINK);
}

void VvvCursor::moveTo(coord X, coord Y, coord Z) {
    getKuroko()->asstA()->stopSlidingMv();
    getKuroko()->setMvVelo(0);
    getKuroko()->setMvAcce(0);
    tx_ = X;
    ty_ = Y;
    tz_ = Z;
    getKuroko()->setMvAngTwd(tx_, ty_, tz_);
    getKuroko()->asstA()->slideMvByDt( UTIL::getDistance(_x, _y, _z, tx_, ty_, tz_), 20, 0.3f, 0.7f, 0, true);
    _pProg->change(CUR_ON_MOVE);
}

VvvCursor::~VvvCursor() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE(pScaler_);
}
