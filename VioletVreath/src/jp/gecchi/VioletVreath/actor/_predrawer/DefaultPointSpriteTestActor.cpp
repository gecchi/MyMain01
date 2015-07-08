#include "DefaultPointSpriteTestActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DefaultPointSpriteTestActor::DefaultPointSpriteTestActor(const char* prm_name) :
        DefaultPointSpriteActor(prm_name, "_chk_DefaultPointSpriteTestModel", nullptr) {
    _class_name = "DefaultPointSpriteTestActor";
    effectBlendOne(); //加算合成
    setHitAble(false);
    setSpecialDrawDepth(RENDER_DEPTH_LEVEL_BACK);
}

int DefaultPointSpriteTestActor::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool DefaultPointSpriteTestActor::isOutOfSpacetime() const {
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

DefaultPointSpriteTestActor::~DefaultPointSpriteTestActor() {
}
