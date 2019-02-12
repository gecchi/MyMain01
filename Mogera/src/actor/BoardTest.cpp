#include "BoardTest.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/util/Input.h"
#include "actor/BoardTest.h"

#include "jp/ggaf/core/util/ValueEnveloper.hpp"


using namespace GgafLib;
using namespace Mogera;


BoardTest::BoardTest(const char* prm_name) :
        DefaultFramedBoardActor(prm_name, "BoardTest") {
    _class_name = "BoardTest";
}

void BoardTest::onCreateModel() {
}

void BoardTest::initialize() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 40);
    GgafDx::UvFlipper* pFrameUvFlipper = getFrameUvFlipper();
    static int ptn[8] = {0, 8, 16, 24, 32, 40, 48, 56 };
    pFrameUvFlipper->customizePtnOrder(ptn, 8);
    pFrameUvFlipper->exec(FLIP_CUSTOMIZED_LOOP, 30);
    GgafDx::Scaler* const pScaler = getScaler();
    pScaler->setRange(R_SC(0.1), R_SC(1.5));
    pScaler->beat(300, 100, 100, 100, -1);
//    setWidth(PX_C(32*4));
//    setHeight(PX_C(32*5));
}

void BoardTest::onActive() {
}

void BoardTest::processBehavior() {
    addRzFaceAng(1000);
    if (GgafDx::Input::isPressedKey(DIK_D)) {
        _x += PX_C(2); //‰E
    }
    if (GgafDx::Input::isPressedKey(DIK_A)) {
        _x -= PX_C(2); //¶
    }
    if (GgafDx::Input::isPressedKey(DIK_S)) {
        _y += PX_C(2); //ã
    }
    if (GgafDx::Input::isPressedKey(DIK_W)) {
        _y -= PX_C(2); //‰º
    }

    if (GgafDx::Input::isPressedKey(DIK_1)) {
        addWidth(PX_C(2));
    }
    if (GgafDx::Input::isPressedKey(DIK_2)) {
        addWidth(-PX_C(2));
    }
    if (GgafDx::Input::isPressedKey(DIK_3)) {
        addHeight(PX_C(2));
    }
    if (GgafDx::Input::isPressedKey(DIK_4)) {
        addHeight(-PX_C(2));
    }

    if (GgafDx::Input::isPressedKey(DIK_Z)) {
        setAlign(ALIGN_LEFT);
    }
    if (GgafDx::Input::isPressedKey(DIK_X)) {
        setAlign(ALIGN_CENTER);
    }
    if (GgafDx::Input::isPressedKey(DIK_C)) {
        setAlign(ALIGN_RIGHT);
    }

    if (GgafDx::Input::isPressedKey(DIK_V)) {
        setValign(VALIGN_TOP);
    }
    if (GgafDx::Input::isPressedKey(DIK_B)) {
        setValign(VALIGN_MIDDLE);
    }
    if (GgafDx::Input::isPressedKey(DIK_N)) {
        setValign(VALIGN_BOTTOM);
    }
    getFrameUvFlipper()->behave();
    getUvFlipper()->behave();
//    getScaler()->behave();
}

void BoardTest::processJudgement() {
}

void BoardTest::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

void BoardTest::onInactive() {
}

BoardTest::~BoardTest() {
}

