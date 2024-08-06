#include "Jiki.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "scene/HgrSpacetime.h"
#include "scene/HgrSpacetime/HgrWorld.h"
#include "HgrCaretaker.h"

using namespace GgafLib;
using namespace Hogera;

enum {
    LOCKON001_PHASE_FIRST_LOCK ,
    LOCKON001_PHASE_LOCK       ,
    LOCKON001_PHASE_RELEASE    ,
    PHASE_BANPEI,
};

Jiki::Jiki(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Lockon001") {
    _class_name = "Jiki";
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv);
    effectBlendOne();
    setZEnableDraw(false);
    setZWriteEnable(false);
    setCullingDraw(false);
    setHitAble(true);
}

void Jiki::initialize() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5);
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
    getLocusVehicle()->setFaceAngVelo(AXIS_Z, 1000);
}

void Jiki::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    VirtualButton* pVb = &(pCARETAKER->getSpacetime()->getWorld()->vb_);
    if (pVb->isPressed(0, VB_BUTTON1)) {
        if (pVb->isPressed(0, VB_UP)) {
            _z += PX_C(2);
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _z -= PX_C(2);
        }
    } else {
        if (pVb->isPressed(0, VB_RIGHT)) {
            _x += PX_C(2);
        }
        if (pVb->isPressed(0, VB_LEFT)) {
            _x -= PX_C(2);
        }
        if (pVb->isPressed(0, VB_UP)) {
            _y += PX_C(2);
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _y -= PX_C(2);
        }
    }
    getUvFlipper()->behave();
    pLocusVehicle->behave();
}

void Jiki::processJudgement() {
}

void Jiki::onInactive() {
}

void Jiki::onHit(const GgafCore::Actor* prm_pOtherActor) {
    _TRACE_("Jiki::onHit!"<<prm_pOtherActor->getName()<<"");
}

Jiki::~Jiki() {
}


