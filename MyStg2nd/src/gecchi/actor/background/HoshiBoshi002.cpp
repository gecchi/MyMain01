#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;
//現在未使用
HoshiBoshi002::HoshiBoshi002(const char* prm_name) :
DefaultPointSpriteActor(prm_name, "hoshitest") {
    _class_name = "HoshiBoshi002";
    changeEffectTechnique("DestBlendOne"); //加算合成
    setHitAble(false);
    _CAM_ZF = abs(P_CAM->_zf * PX_UNIT * LEN_UNIT);
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL-1);
    _TRACE_("HoshiBoshi002::HoshiBoshi002 _CAM_ZF="<<_CAM_ZF);
}

int HoshiBoshi002::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool HoshiBoshi002::isOutOfUniverse() {
    //ゲーム座標範囲外判定無し
    return false;
}
void HoshiBoshi002::initialize() {

}

void HoshiBoshi002::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void HoshiBoshi002::processBehavior() {
    if (_X < -_CAM_ZF) {
        _X += (_CAM_ZF*2);
    } else {
        _X -= 10000;
    }

    _pUvFlipper->behave();
}

void HoshiBoshi002::processSettlementBehavior() {
    //画面外判定無しに伴ない処理簡略化
    //GgafDx9GeometricActor::processSettlementBehavior() と同期を取る事！
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
}

void HoshiBoshi002::processJudgement() {
}

//void HoshiBoshi002::processPreDraw() {
//    //画面外判定無しに伴ない処理簡略化
//    //GgafDx9DrawableActor::processPreDraw() と同期を取る事！
//    GgafDx9Universe::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL-1,this); //最深部-1、最深部はWorldBound
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


HoshiBoshi002::~HoshiBoshi002() {
}
