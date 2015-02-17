#include "DefaultPointSpriteTestActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DefaultPointSpriteTestActor::DefaultPointSpriteTestActor(const char* prm_name) :
        DefaultPointSpriteActor(prm_name, "_chk_DefaultPointSpriteTestModel", nullptr) {
    _class_name = "DefaultPointSpriteTestActor";
    effectBlendOne(); //加算合成
    setHitAble(false);
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL-1);
}

int DefaultPointSpriteTestActor::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool DefaultPointSpriteTestActor::isOutOfUniverse() const {
    //ゲーム座標範囲外判定無し
    return false;
}
void DefaultPointSpriteTestActor::initialize() {

}

void DefaultPointSpriteTestActor::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void DefaultPointSpriteTestActor::processBehavior() {
    getUvFlipper()->behave();
}

void DefaultPointSpriteTestActor::processSettlementBehavior() {
    //画面外判定無しに伴ない処理簡略化
    //GgafDxGeometricActor::processSettlementBehavior() と同期を取る事！
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
}

void DefaultPointSpriteTestActor::processJudgement() {
}

//void DefaultPointSpriteTestActor::processPreDraw() {
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


DefaultPointSpriteTestActor::~DefaultPointSpriteTestActor() {
}
