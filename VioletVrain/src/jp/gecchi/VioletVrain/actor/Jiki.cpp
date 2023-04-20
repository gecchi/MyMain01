#include "Jiki.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/gecchi/VioletVrain/scene/VvSpacetime.h"
#include "jp/gecchi/VioletVrain/scene/VvSpacetime/World.h"
#include "jp/gecchi/VioletVrain/VvCaretaker.h"



using namespace GgafLib;
using namespace VioletVrain;

enum {
    LOCKON001_PHASE_FIRST_LOCK ,
    LOCKON001_PHASE_LOCK       ,
    LOCKON001_PHASE_RELEASE    ,
    PHASE_BANPEI,
};

Jiki::Jiki(const char* prm_name) :
        VvMyActor<DefaultSpriteActor>(prm_name, "Lockon001", (void*)Jiki::resetJikiStatus) {
    _class_name = "Jiki";
//    defineRotMvWorldMatrix_Billboard(); //ワールド変換はビルボードでRz回転に強制
    effectBlendOne(); //エフェクトテクニックは加算合成に強制
    setZEnableDraw(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //自身のZバッファを書き込みしないに強制
    setCullingDraw(false);
    setHitAble(true);
}

void Jiki::initialize() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //アニメ範囲を０～１５
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //アニメ順序
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
//    pChecker->addCollisionArea(1);
////    pChecker->set2DColliSquare(0, PX_C(128));
////    pChecker->set2DColliCircle(0, PX_C(32));
//    pChecker->set2DColliRightTriangle_WH(0, PX_C(60), PX_C(70), PX_C(250), PX_C(150), POS_R_TRIANGLE_NN);

    pChecker->addCollisionArea(4);
    coord ox = PX_C(30);
    coord oy = PX_C(40);
    coord w = PX_C(50);
    coord h = PX_C(70);
    pChecker->set2DColliRightTriangle_WH(0, ox - (w*2), oy - (h*2), w, h, POS_R_TRIANGLE_PP);
    pChecker->set2DColliRightTriangle_WH(1, ox - (w*2), oy + (h*2), w, h, POS_R_TRIANGLE_PN);
    pChecker->set2DColliRightTriangle_WH(2, ox + (w*2), oy - (h*2), w, h, POS_R_TRIANGLE_NP);
    pChecker->set2DColliRightTriangle_WH(3, ox + (w*2), oy + (h*2), w, h, POS_R_TRIANGLE_NN);
}

void Jiki::onReset() {
    getPhase()->reset(LOCKON001_PHASE_RELEASE);
}

void Jiki::onActive() {
    getUvFlipper()->setActivePtnToTop();
    getLocoVehicle()->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void Jiki::processBehavior() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    VirtualButton* pVb = &(pCARETAKER->getSpacetime()->getWorld()->vb_);
    if (pVb->isPressed(0, VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (pVb->isPressed(0, VB_UP)) {
            _z += PX_C(2); //奥
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _z -= PX_C(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (pVb->isPressed(0, VB_RIGHT)) {
            _x += PX_C(2); //右
        }
        if (pVb->isPressed(0, VB_LEFT)) {
            _x -= PX_C(2); //左
        }
        if (pVb->isPressed(0, VB_UP)) {
            _y += PX_C(2); //上
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _y -= PX_C(2); //下
        }
    }
    getUvFlipper()->behave();
    pLocoVehicle->behave();
}

void Jiki::processJudgement() {
}

void Jiki::onInactive() {
}

Jiki::~Jiki() {
}


