#include "BoardTest.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "actor/BoardTest.h"

#include "jp/ggaf/core/util/GgafValueEnveloper.hpp"
using namespace GgafCore;
using namespace GgafDxCore;
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
    GgafDxUvFlipper* pFrameUvFlipper = getFrameUvFlipper();
    static int ptn[8] = {0, 8, 16, 24, 32, 40, 48, 56 };
    pFrameUvFlipper->customizePtnOrder(ptn, 8);
    pFrameUvFlipper->exec(FLIP_CUSTOMIZED_LOOP, 30);
    GgafDxScaler* const pScaler = getScaler();
    pScaler->setRange(R_SC(0.1), R_SC(1.5));
    pScaler->beat(300, 100, 100, 100, -1);
//    setWidth(PX_C(32*4));
//    setHeight(PX_C(32*5));
}

void BoardTest::onActive() {
}

void BoardTest::processBehavior() {
    addRzFaceAng(1000);
    if (GgafDxInput::isPressedKey(DIK_D)) {
        _x += PX_C(2); //‰E
    }
    if (GgafDxInput::isPressedKey(DIK_A)) {
        _x -= PX_C(2); //¶
    }
    if (GgafDxInput::isPressedKey(DIK_S)) {
        _y += PX_C(2); //ã
    }
    if (GgafDxInput::isPressedKey(DIK_W)) {
        _y -= PX_C(2); //‰º
    }

    if (GgafDxInput::isPressedKey(DIK_1)) {
        addWidth(PX_C(2));
    }
    if (GgafDxInput::isPressedKey(DIK_2)) {
        addWidth(-PX_C(2));
    }
    if (GgafDxInput::isPressedKey(DIK_3)) {
        addHeight(PX_C(2));
    }
    if (GgafDxInput::isPressedKey(DIK_4)) {
        addHeight(-PX_C(2));
    }

    if (GgafDxInput::isPressedKey(DIK_Z)) {
        setAlign(ALIGN_LEFT);
    }
    if (GgafDxInput::isPressedKey(DIK_X)) {
        setAlign(ALIGN_CENTER);
    }
    if (GgafDxInput::isPressedKey(DIK_C)) {
        setAlign(ALIGN_RIGHT);
    }

    if (GgafDxInput::isPressedKey(DIK_V)) {
        setValign(VALIGN_TOP);
    }
    if (GgafDxInput::isPressedKey(DIK_B)) {
        setValign(VALIGN_MIDDLE);
    }
    if (GgafDxInput::isPressedKey(DIK_N)) {
        setValign(VALIGN_BOTTOM);
    }
    getFrameUvFlipper()->behave();
    getUvFlipper()->behave();
//    getScaler()->behave();
}

void BoardTest::processJudgement() {
}

void BoardTest::onHit(const GgafActor* prm_pOtherActor) {
}

void BoardTest::onInactive() {
}

BoardTest::~BoardTest() {
}

