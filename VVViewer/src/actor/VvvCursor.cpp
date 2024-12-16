#include "VvvCursor.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAssistant.h"

using namespace GgafLib;
using namespace VVViewer;

VvvCursor::VvvCursor(const char* prm_name) :
        GgafLib::DefaultSpriteActor(prm_name, "Cursor") {
    defineRotMvWorldMatrix_Billboard(); //ワールド変換はビルボードでRz回転に強制
    effectBlendOne(); //エフェクトテクニックは加算合成に強制
    useZBufferDrawing(false);      //Zバッファは考慮無しに強制
    setZBufferWriteEnable(false); //自身のZバッファを書き込みしないに強制
    setSpecialRenderDepthIndex(1); //描画順序を最前面描画に強制。ロックオンエフェクトが隠れないようにするため。
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
    _pPhase->reset(CUR_SINK);
}

void VvvCursor::initialize() {
    //座標設定
    _x = _y = _z = 0; //(0,0,0) は画面の中心
    getLocusVehicle()->_angvelo_face[AXIS_Z] = 1000;
    GgafDx::Scaler* const pScaler = getScaler();
    pScaler->setRange(2000, 4000);
    pScaler->beat(30, 2, 0, 28, -1); //無限ループ
    setAlpha(0);
}

void VvvCursor::processBehavior() {
    switch (_pPhase->getCurrent()) {
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
    getLocusVehicle()->behave();
    if (getLocusVehicle()->asstMv()->hasJustFinishedSliding()) {
        //理想位置に補正
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
    getLocusVehicle()->asstMv()->stopSliding();
    getLocusVehicle()->setMvVelo(0);
    getLocusVehicle()->setMvAcce(0);
    tx_ = X;
    ty_ = Y;
    tz_ = Z;
    getLocusVehicle()->setMvAngTwd(tx_, ty_, tz_);
    getLocusVehicle()->asstMv()->slideByDt( UTIL::getDistance(_x, _y, _z, tx_, ty_, tz_), 20, 0.3f, 0.7f, 0, true);
    _pPhase->change(CUR_ON_MOVE);
}

VvvCursor::~VvvCursor() {
}
