#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;
//現在未使用
HoshiBoshi002::HoshiBoshi002(const char* prm_name) :
        DefaultPointSpriteActor(prm_name, "hoshitest", NULL) {
    _class_name = "HoshiBoshi002";
    changeEffectTechnique("DestBlendOne"); //加算合成
    setHitAble(false);
    CAM_ZF_ = GgafUtil::abs(DX_C(P_CAM->_zf));
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_HOSHIBOSHI);
    _TRACE_("HoshiBoshi002::HoshiBoshi002 CAM_ZF_="<<CAM_ZF_);
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
    if (_X < -CAM_ZF_) {
        _X += (CAM_ZF_*2);
    } else {
        _X -= 10000;
    }

    _pUvFlipper->behave();
}

void HoshiBoshi002::processSettlementBehavior() {
    //画面外判定無しに伴ない処理簡略化
    //GgafDxGeometricActor::processSettlementBehavior() と同期を取る事！
    _fX = C_DX(_X);
    _fY = C_DX(_Y);
    _fZ = C_DX(_Z);
}

void HoshiBoshi002::processJudgement() {
}

//void HoshiBoshi002::processPreDraw() {
//    //画面外判定無しに伴ない処理簡略化
//    //GgafDxDrawableActor::processPreDraw() と同期を取る事！
//    GgafDxUniverse::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL-1,this); //最深部-1、最深部はWorldBound
//
////    //一時テクニック期間チェック
////    if (is_temp_technique_) {
////        if (frame_of_behaving_temp_technique_end_ <= frame_of_behaving_) {
////            //一時テクニック期間満了。元に戻す
////            hash_technique_ = hash_temp_technique_;
////            strcpy(technique_, temp_technique_);
////            is_temp_technique_ = false;
////            //これはダメ。配列領域がどこかにいくため。temp_technique_ = "";
////            hash_temp_technique_ = 0;
////        }
////    }
//}


HoshiBoshi002::~HoshiBoshi002() {
}
