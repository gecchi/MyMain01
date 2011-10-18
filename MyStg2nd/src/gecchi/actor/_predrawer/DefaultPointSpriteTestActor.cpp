#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;
DefaultPointSpriteTestActor::DefaultPointSpriteTestActor(const char* prm_name) :
        DefaultPointSpriteActor(prm_name, "_chk_DefaultPointSpriteTestModel", NULL) {
    _class_name = "DefaultPointSpriteTestActor";
    changeEffectTechnique("DestBlendOne"); //加算合成
    setHitAble(false);
    _CAM_ZF = abs(P_CAM->_zf * PX_UNIT * LEN_UNIT);
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL-1);
    _TRACE_("DefaultPointSpriteTestActor::DefaultPointSpriteTestActor _CAM_ZF="<<_CAM_ZF);
}

int DefaultPointSpriteTestActor::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool DefaultPointSpriteTestActor::isOutOfUniverse() {
    //ゲーム座標範囲外判定無し
    return false;
}
void DefaultPointSpriteTestActor::initialize() {

}

void DefaultPointSpriteTestActor::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void DefaultPointSpriteTestActor::processBehavior() {
    if (_X < -_CAM_ZF) {
        _X += (_CAM_ZF*2);
    } else {
        _X -= 10000;
    }

    _pUvFlipper->behave();
}

void DefaultPointSpriteTestActor::processSettlementBehavior() {
    //画面外判定無しに伴ない処理簡略化
    //GgafDxGeometricActor::processSettlementBehavior() と同期を取る事！
    _fX = Co2Dx(_X);
    _fY = Co2Dx(_Y);
    _fZ = Co2Dx(_Z);
}

void DefaultPointSpriteTestActor::processJudgement() {
}

//void DefaultPointSpriteTestActor::processPreDraw() {
//    //画面外判定無しに伴ない処理簡略化
//    //GgafDxDrawableActor::processPreDraw() と同期を取る事！
//    GgafDxUniverse::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL-1,this); //最深部-1、最深部はWorldBound
//
////    //一時テクニック期間チェック
////    if (_is_temp_technique) {
////        if (_frame_of_behaving_temp_technique_end <= _frame_of_behaving) {
////            //一時テクニック期間満了。元に戻す
////            _hash_technique = _hash_temp_technique;
////            strcpy(_technique, _temp_technique);
////            _is_temp_technique = false;
////            //これはダメ。配列領域がどこかにいくため。_temp_technique = "";
////            _hash_temp_technique = 0;
////        }
////    }
//}


DefaultPointSpriteTestActor::~DefaultPointSpriteTestActor() {
}
