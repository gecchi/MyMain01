#include "VvvCursor.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"



using namespace GgafLib;
using namespace VVViewer;

VvvCursor::VvvCursor(const char* prm_name) :
        GgafLib::DefaultSpriteActor(prm_name, "Cursor") {
    defineRotMvWorldMatrix_Billboard(); //���[���h�ϊ��̓r���{�[�h��Rz��]�ɋ���
    effectBlendOne(); //�G�t�F�N�g�e�N�j�b�N�͉��Z�����ɋ���
    setZEnableDraw(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ��ɋ���
    setSpecialRenderDepthIndex(1); //�`�揇�����őO�ʕ`��ɋ����B���b�N�I���G�t�F�N�g���B��Ȃ��悤�ɂ��邽�߁B
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
    _pPhase->reset(CUR_SINK);
}

void VvvCursor::initialize() {
    //���W�ݒ�
    _x = _y = _z = 0; //(0,0,0) �͉�ʂ̒��S
    getVecVehicle()->_angvelo_face[AXIS_Z] = 1000;
    GgafDx::Scaler* const pScaler = getScaler();
    pScaler->setRange(2000, 4000);
    pScaler->beat(30, 2, 0, 28, -1); //�������[�v
    setAlpha(0);
}

void VvvCursor::processBehavior() {
    switch (_pPhase->get()) {
        case CUR_SINK: {
            break;
        }
        case CUR_ON_MOVE: {
            setCullingDraw(false);
            _pPhase->change(CUR_STAY);
            break;
        }
        case CUR_STAY: {
            if (_pPhase->getFrame() > 60) {
                getAlphaFader()->transitionLinearUntil(0.0, 120);
                _pPhase->change(CUR_SINK);
            }
            break;
        }
        default: {
            break;
        }
    }

    _pUvFlipper->behave();
    getVecVehicle()->behave();
    if (getVecVehicle()->asstMv()->hasJustFinishedSliding()) {
        //���z�ʒu�ɕ␳
        _x = tx_;
        _y = ty_;
        _z = tz_;
    }

    getScaler()->behave();
    getAlphaFader()->behave();
}
void VvvCursor::sinkMe() {
    _pPhase->change(CUR_SINK);
}

void VvvCursor::moveTo(coord X, coord Y, coord Z) {
    getVecVehicle()->asstMv()->stopSliding();
    getVecVehicle()->setMvVelo(0);
    getVecVehicle()->setMvAcce(0);
    tx_ = X;
    ty_ = Y;
    tz_ = Z;
    getVecVehicle()->setMvAngTwd(tx_, ty_, tz_);
    getVecVehicle()->asstMv()->slideByDt( UTIL::getDistance(_x, _y, _z, tx_, ty_, tz_), 20, 0.3f, 0.7f, 0, true);
    _pPhase->change(CUR_ON_MOVE);
}

VvvCursor::~VvvCursor() {
}
