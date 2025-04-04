#include "Test01.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "HgrCaretaker.h"



using namespace GgafLib;
using namespace Hogera;

enum {
    LOCKON001_PHASE_FIRST_LOCK ,
    LOCKON001_PHASE_LOCK       ,
    LOCKON001_PHASE_RELEASE    ,
    PHASE_BANPEI,
};

Test01::Test01(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Lockon001") {
    _class_name = "Test01";
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv);
    effectBlendOne();
    useZBufferDrawing(false);
    setZBufferWriteEnable(false);
    setCullingDraw(false);

    setHitAble(true);
}

void Test01::initialize() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5);

    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
//    pChecker->addCollisionArea(1);
//    pChecker->set2DColliRightTriangle_WH(0, PX_C(-10), PX_C(-20), PX_C(50), PX_C(100), POS_R_TRIANGLE_PP);
//    pChecker->setColliSphere(0, PX_C(64));
//    pChecker->setColliAABox(1, PX_C(-128), PX_C(-128), PX_C(-1), PX_C(-64), PX_C(-64), PX_C(1), false, false, true);
//    pChecker->setColli2DRectangle(0, PX_C(-128), PX_C(-128), PX_C(-64), PX_C(-64), true);

    pChecker->addCollisionArea(4);
    coord ox = PX_C(10);
    coord oy = PX_C(20);
    coord w = PX_C(70);
    coord h = PX_C(50);
    pChecker->set2DColliRightTriangle_WH(0, ox - (w*2), oy - (h*2), w, h, POS_R_TRIANGLE_PP);
    pChecker->set2DColliRightTriangle_WH(1, ox - (w*2), oy + (h*2), w, h, POS_R_TRIANGLE_PN);
    pChecker->set2DColliRightTriangle_WH(2, ox + (w*2), oy - (h*2), w, h, POS_R_TRIANGLE_NP);
    pChecker->set2DColliRightTriangle_WH(3, ox + (w*2), oy + (h*2), w, h, POS_R_TRIANGLE_NN);

}

void Test01::onReset() {
    getPhase()->reset(LOCKON001_PHASE_RELEASE);
}

void Test01::onActive() {
    getUvFlipper()->setActivePtnToTop();
    getLocusVehicle()->setFaceAngVelo(AXIS_Z, 1000);
}

void Test01::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();

    if (GgafDx::Input::isPressedKey(DIK_D)) {
        _x += PX_C(2);
    }
    if (GgafDx::Input::isPressedKey(DIK_A)) {
        _x -= PX_C(2);
    }
    if (GgafDx::Input::isPressedKey(DIK_W)) {
        _y += PX_C(2);
    }
    if (GgafDx::Input::isPressedKey(DIK_S)) {
        _y -= PX_C(2);
    }
    getUvFlipper()->behave();
    pLocusVehicle->behave();
}

void Test01::processJudgement() {
}

void Test01::onInactive() {
}

void Test01::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    _TRACE_("Test01::onHit!"<<prm_pOppHitChecker->_pActor->getName()<<"");
}

Test01::~Test01() {
}


