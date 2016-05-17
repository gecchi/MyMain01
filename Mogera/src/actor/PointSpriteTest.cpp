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
    //effectBlendOne(); //‰ÁŽZ‡¬
    setHitAble(false);
}

int PointSpriteTest::isOutOfView() {
    //‰æ–ÊŠO”»’è–³‚µ
    return 0;
}

bool PointSpriteTest::isOutOfSpacetime() const {
    //ƒQ[ƒ€À•W”ÍˆÍŠO”»’è–³‚µ
    return false;
}
void PointSpriteTest::initialize() {
    getKuroko()->setRollPitchYawFaceAngVelo(30, 50, 70);
    pScaler_->setRange(R_SC(0.1), R_SC(1.0));
    pScaler_->beat(220,100,10,100,-1);
}

void PointSpriteTest::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void PointSpriteTest::processBehavior() {
    getUvFlipper()->behave();
    getKuroko()->behave();
    pScaler_->behave();
}

void PointSpriteTest::processJudgement() {
}

PointSpriteTest::~PointSpriteTest() {
}
