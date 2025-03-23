#include "VvvMousePointer.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/actor/camera/Camera.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"
#include "scene/VvvSpacetime/VvvWorld.h"
#include "VvvCaretaker.h"

using namespace GgafLib;
using namespace VVViewer;

VvvMousePointer::VvvMousePointer(const char* prm_name) :
        MousePointerActor(prm_name, "VvvMousePointer") {
    _class_name = "VvvMousePointer";
    pWorldMousePointer_ = nullptr;
    setAlpha(0.7f);
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    ViewCollisionChecker* pChecker = getViewCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSquare(0, PX_C(16));
    setHitAble(true);
}

void VvvMousePointer::onCreateModel() {
}

void VvvMousePointer::initialize() {
    pWorldMousePointer_ = desireActor(GgafLib::DefaultSpriteActor, "VvvMousePointer", "VvvMousePointer");
    WorldCollisionChecker* pChecker = pWorldMousePointer_->getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(100));
    pWorldMousePointer_->setAlpha(0.7f);
    pWorldMousePointer_->setCullingDraw(false);
    pWorldMousePointer_->setHitAble(true);
    pWorldMousePointer_->setCheckerKind(KIND_ACTOR);
    appendChild(pWorldMousePointer_);
}

void VvvMousePointer::onActive() {
}

void VvvMousePointer::processBehavior() {
    VvvWorld* pWorld  = pCARETAKER->getSpacetime()->pWorld_;
    VvvCamera* pCam = pCARETAKER->getSpacetime()->getCamera();
    VvvWorld::ActorInfo* pActorInfo = pWorld->listActorInfo_.getCurrent();
    if (pActorInfo) {
        GgafDx::FigureActor* pT = pActorInfo->pActor_;
        double d = UTIL::getDistance(pCam, pT);
        pWorldMousePointer_->setPositionByViewCoord(_x, _y, d);
    } else {
        pWorldMousePointer_->setPositionByViewCoord(_x, _y, DX_C(-(pCam->_cameraZ_org)));
    }
}

void VvvMousePointer::processJudgement() {
//    _TRACE_("dtop,dbottom="<<DX_PX(pWorldMousePointer_->_dest_from_vppln_top)<<","<<DX_PX(pWorldMousePointer_->_dest_from_vppln_bottom));
//    _TRACE_("dleft,dright="<<DX_PX(pWorldMousePointer_->_dest_from_vppln_left)<<","<<DX_PX(pWorldMousePointer_->_dest_from_vppln_right));
}

void VvvMousePointer::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    MousePointerActor::onHit(prm_pThisHitChecker, prm_pOppHitChecker);
}

void VvvMousePointer::onInactive() {
}

VvvMousePointer::~VvvMousePointer() {
}

