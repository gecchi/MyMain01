#include "Jiki.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "scene/HgrSpacetime.h"
#include "scene/HgrSpacetime/HgrWorld.h"
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

Jiki::Jiki(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Lockon001", nullptr) {
    _class_name = "Jiki";
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ワールド変換はビルボードでRz回転に強制
    effectBlendOne(); //エフェクトテクニックは加算合成に強制
    setZEnableDraw(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //自身のZバッファを書き込みしないに強制

    setAlpha(0.9);          //α部分があるため、カリングをOFFするため透明オブジェクト扱いにする。
    setHitAble(true);
    useProgress(PROG_BANPEI);
}

void Jiki::initialize() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //アニメ範囲を０～１５
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //アニメ順序
    CollisionChecker* pChecker = getCollisionChecker();
//    pChecker->createCollisionArea(1);
////    pChecker->set2DColliSquare(0, PX_C(128));
////    pChecker->set2DColliCircle(0, PX_C(32));
//    pChecker->set2DColliRightTriangle_WH(0, PX_C(60), PX_C(70), PX_C(250), PX_C(150), POS_R_TRIANGLE_NN);

    pChecker->createCollisionArea(4);
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
    getProgress()->reset(LOCKON001_PROG_RELEASE);
}

void Jiki::onActive() {
    getUvFlipper()->setActivePtnToTop();
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void Jiki::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    VirtualButton* pVb = &(P_GOD->getSpacetime()->getWorld()->vb_);
    if (pVb->isPressed(VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (pVb->isPressed(VB_UP)) {
            _z += PX_C(2); //奥
        }
        if (pVb->isPressed(VB_DOWN)) {
            _z -= PX_C(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (pVb->isPressed(VB_RIGHT)) {
            _x += PX_C(2); //右
        }
        if (pVb->isPressed(VB_LEFT)) {
            _x -= PX_C(2); //左
        }
        if (pVb->isPressed(VB_UP)) {
            _y += PX_C(2); //上
        }
        if (pVb->isPressed(VB_DOWN)) {
            _y -= PX_C(2); //下
        }
    }
    getUvFlipper()->behave();
    pKuroko->behave();
}

void Jiki::processJudgement() {
}

void Jiki::onInactive() {
}

void Jiki::onHit(const GgafActor* prm_pOtherActor) {
    _TRACE_("Jiki::onHit!!!! 相手＝"<<prm_pOtherActor->getName()<<"");
}

Jiki::~Jiki() {
}


