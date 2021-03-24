#include "Test01.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "HgrGod.h"



using namespace GgafLib;
using namespace Hogera;

enum {
    LOCKON001_PROG_FIRST_LOCK ,
    LOCKON001_PROG_LOCK       ,
    LOCKON001_PROG_RELEASE    ,
    PROG_BANPEI,
};

Test01::Test01(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Lockon001") {
    _class_name = "Test01";
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ワールド変換はビルボードでRz回転に強制
    effectBlendOne(); //エフェクトテクニックは加算合成に強制
    setZEnableDraw(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //自身のZバッファを書き込みしないに強制
    setCullingDraw(false);

    setHitAble(true);
}

void Test01::initialize() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //アニメ範囲を０～１５
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //アニメ順序

    CollisionChecker* pChecker = getCollisionChecker();
//    pChecker->createCollisionArea(1);
//    pChecker->set2DColliRightTriangle_WH(0, PX_C(-10), PX_C(-20), PX_C(50), PX_C(100), POS_R_TRIANGLE_PP);
//    pChecker->setColliSphere(0, PX_C(64));
//    pChecker->setColliAABox(1, PX_C(-128), PX_C(-128), PX_C(-1), PX_C(-64), PX_C(-64), PX_C(1), false, false, true);
//    pChecker->setColli2DRectangle(0, PX_C(-128), PX_C(-128), PX_C(-64), PX_C(-64), true);

    pChecker->createCollisionArea(4);
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
    getProgress()->reset(LOCKON001_PROG_RELEASE);
}

void Test01::onActive() {
    getUvFlipper()->setActivePtnToTop();
    callVecDriver()->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void Test01::processBehavior() {
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    GgafCore::Progress* const pProg = getProgress();

    if (GgafDx::Input::isPressedKey(DIK_D)) {
        _x += PX_C(2); //右
    }
    if (GgafDx::Input::isPressedKey(DIK_A)) {
        _x -= PX_C(2); //左
    }
    if (GgafDx::Input::isPressedKey(DIK_W)) {
        _y += PX_C(2); //上
    }
    if (GgafDx::Input::isPressedKey(DIK_S)) {
        _y -= PX_C(2); //下
    }
    getUvFlipper()->behave();
    pVecDriver->behave();
}

void Test01::processJudgement() {
}

void Test01::onInactive() {
}

void Test01::onHit(const GgafCore::Actor* prm_pOtherActor) {
    _TRACE_("Test01::onHit!!!! 相手＝"<<prm_pOtherActor->getName()<<"");
}

Test01::~Test01() {
}


