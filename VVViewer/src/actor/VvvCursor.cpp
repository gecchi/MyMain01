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
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ワールド変換はビルボードでRz回転に強制
    effectBlendOne(); //エフェクトテクニックは加算合成に強制
    setZEnable(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //Zバッファは書き込み無しに強制
    setSpecialDrawDepth(1); //描画順序を最前面描画に強制。ロックオンエフェクトが隠れないようにするため。
    tX_ = _X;
    tY_ = _Y;
    tZ_ = _Z;
    useProgress(10);
    _pProg->reset(CUR_SINK);
}

void VvvCursor::initialize() {
    //座標設定
    _X = _Y = _Z = 0; //(0,0,0) は画面の中心
    _pKurokoA->_angveloFace[AXIS_Z] = 1000;
    _pScaler->forceRange(2000, 4000);
    _pScaler->beat(30, 2, 2, -1); //無限ループ
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
        //理想位置に補正
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
