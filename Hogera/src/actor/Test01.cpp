#include "Test01.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "HgrGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Hogera;

enum {
    LOCKON001_PROG_FIRST_LOCK ,
    LOCKON001_PROG_LOCK       ,
    LOCKON001_PROG_RELEASE    ,
    PROG_BANPEI,
};

Test01::Test01(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Lockon001", nullptr) {
    _class_name = "Test01";
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ワールド変換はビルボードでRz回転に強制
    effectBlendOne(); //エフェクトテクニックは加算合成に強制
    setZEnableDraw(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //自身のZバッファを書き込みしないに強制

    setAlpha(0.9);          //α部分があるため、カリングをOFFするため透明オブジェクト扱いにする。

    setHitAble(true);
    useProgress(PROG_BANPEI);
}

void Test01::initialize() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //アニメ範囲を０～１５
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //アニメ順序

    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(2);
//    pChecker->setColliAABox_Cube(0, PX_C(128));
    pChecker->setColliSphere(0, PX_C(64));
    pChecker->setColliAABox(1, PX_C(-128), PX_C(-128), PX_C(-1), PX_C(-64), PX_C(-64), PX_C(1), false, false, true);
}


void Test01::onReset() {
    getProgress()->reset(LOCKON001_PROG_RELEASE);
}

void Test01::onActive() {
    getUvFlipper()->setActivePtnToTop();
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //回転

}

void Test01::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();


    if (GgafDxInput::isPressedKey(DIK_D)) {
        _x += PX_C(2); //右
    }
    if (GgafDxInput::isPressedKey(DIK_A)) {
        _x -= PX_C(2); //左
    }
    if (GgafDxInput::isPressedKey(DIK_W)) {
        _y += PX_C(2); //上
    }
    if (GgafDxInput::isPressedKey(DIK_S)) {
        _y -= PX_C(2); //下
    }

    getUvFlipper()->behave();
    pKuroko->behave();

}

void Test01::processJudgement() {
}

void Test01::onInactive() {
}

void Test01::onHit(const GgafActor* prm_pOtherActor) {
    _TRACE_("Test01::onHit!!!! 相手＝"<<prm_pOtherActor->getName()<<"");
}

Test01::~Test01() {
}

