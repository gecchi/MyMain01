#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvCursor::VvvCursor(const char* prm_name) :
        GgafLib::DefaultSpriteSetActor(prm_name, "Cursor") { //Guruguru.x が参照される。
    defineRotMvWorldMatrix(GgafDxUtil::setWorldMatrix_RzBxyzMv); //ワールド変換はビルボードでRz回転に強制
    changeEffectTechnique("DestBlendOne"); //エフェクトテクニックは加算合成に強制
    setZEnable(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //Zバッファは書き込み無しに強制
    setSpecialDrawDepth(1); //描画順序を最前面描画に強制。ロックオンエフェクトが隠れないようにするため。

    useProgress(10);
    _pProg->set(CUR_SINK);
}

void VvvCursor::initialize() {
    //座標設定
    _X = _Y = _Z = 0; //(0,0,0) は画面の中心
    _pKurokoA->_angveloFace[AXIS_Z] = 1000;
    _pScaler->forceScaleRange(2000, 4000);
    _pScaler->beat(30, 2, 2, -1); //無限ループ
    setAlpha(0);
}

void VvvCursor::processBehavior() {
    switch (_pProg->get()) {
        case CUR_SINK: {
            setAlpha(0);
            break;
        }
        case CUR_ON_MOVE: {
            setAlpha(0.9);
            _pProg->change(CUR_STAY);
            break;
        }
        case CUR_STAY: {
            if (_pProg->getFrameInProgress() > 3*60) {
                _pProg->change(CUR_SINK);
            }
            break;
        }
        default: {
            break;
        }
    }
    if (_pKurokoA->isJustFinishSmoothMvSequence()) {
        //理想位置に補正
        _X = tX_;
        _Y = tY_;
        _Z = tZ_;
    }
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}
void VvvCursor::sink() {
    _pProg->change(CUR_SINK);
}

void VvvCursor::moveTo(coord X, coord Y, coord Z) {
    _pKurokoA->_smooth_mv_velo_seq_flg = false;
    _pKurokoA->setMvVelo(0);
    _pKurokoA->setMvAcce(0);
    tX_ = X;
    tY_ = Y;
    tZ_ = Z;
    _pKurokoA->setMvAng(tX_, tY_, tZ_);
    _pKurokoA->execSmoothMvSequence(0, GgafDxUtil::getDistance(_X, _Y, _Z, tX_, tY_, tZ_),
                                    20, 0.3f, 0.7f);
    _pProg->change(CUR_ON_MOVE);
}

VvvCursor::~VvvCursor() {
}
