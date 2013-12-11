#include "stdafx.h"
#include "VvvCursor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvCursor::VvvCursor(const char* prm_name) :
        GgafLib::DefaultSpriteActor(prm_name, "Cursor") {
    pAFader_ = NEW GgafDxAlphaFader(this);
    pScaler_ = NEW GgafDxScaler(this);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ワールド変換はビルボードでRz回転に強制
    effectBlendOne(); //エフェクトテクニックは加算合成に強制
    setZEnable(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //Zバッファは書き込み無しに強制
    setSpecialDrawDepth(1); //描画順序を最前面描画に強制。ロックオンエフェクトが隠れないようにするため。
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
    useProgress(10);
    _pProg->reset(CUR_SINK);
}

void VvvCursor::initialize() {
    //座標設定
    _x = _y = _z = 0; //(0,0,0) は画面の中心
    _pKuroko->_angveloFace[AXIS_Z] = 1000;
    pScaler_->forceRange(2000, 4000);
    pScaler_->beat(30, 2, 2, -1); //無限ループ
    pAFader_->setAlpha(0);
}

void VvvCursor::processBehavior() {
    switch (_pProg->get()) {
        case CUR_SINK: {
            break;
        }
        case CUR_ON_MOVE: {
            pAFader_->setAlpha(0.9);
            _pProg->change(CUR_STAY);
            break;
        }
        case CUR_STAY: {
            if (_pProg->getFrameInProgress() > 60) {
                pAFader_->fadeLinerUntil(0.0, 120);
                _pProg->change(CUR_SINK);
            }
            break;
        }
        default: {
            break;
        }
    }

    _pUvFlipper->behave();
    _pKuroko->behave();
    if (_pKuroko->helperA()->isJustFinishSlidingMv()) {
        //理想位置に補正
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
    _pKuroko->helperA()->stopSlidingMv();
    _pKuroko->setMvVelo(0);
    _pKuroko->setMvAcce(0);
    tx_ = X;
    ty_ = Y;
    tz_ = Z;
    _pKuroko->setMvAngTwd(tx_, ty_, tz_);
    _pKuroko->helperA()->slideMvByDt( UTIL::getDistance(_x, _y, _z, tx_, ty_, tz_), 20, 0.3f, 0.7f, 0);
    _pProg->change(CUR_ON_MOVE);
}

VvvCursor::~VvvCursor() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE(pScaler_);
}
