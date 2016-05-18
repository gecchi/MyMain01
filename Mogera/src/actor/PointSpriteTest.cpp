#include "PointSpriteTest.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

PointSpriteTest::PointSpriteTest(const char* prm_name) :
        DefaultMassPointSpriteActor(prm_name, "3/PTEST", nullptr) {
    _class_name = "PointSpriteTest";
    pScaler_ = NEW GgafDxScaler(this);
    //effectBlendOne(); //加算合成
    setAlpha(0.8);
    setHitAble(false);
}

int PointSpriteTest::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool PointSpriteTest::isOutOfSpacetime() const {
    //ゲーム座標範囲外判定無し
    return false;
}
void PointSpriteTest::initialize() {
    getKuroko()->setRollPitchYawFaceAngVelo(30, 50, 70);
    setScale(0);
    pScaler_->transitionAcceUntilVelo(-R_SC(0.01) , R_SC(0.1), -R_SC(0.001));
}

void PointSpriteTest::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void PointSpriteTest::processBehavior() {
//    if (!pScaler_->isTransitioning()) {
//        sayonara();
//    }
    getUvFlipper()->behave();
    getKuroko()->behave();
    pScaler_->behave();
}

void PointSpriteTest::processJudgement() {
}

PointSpriteTest::~PointSpriteTest() {
}
