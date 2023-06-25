#include "VvvMousePointer.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/actor/camera/Camera.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "scene/VvvSpacetime/VvvWorld.h"
#include "VvvCaretaker.h"

using namespace GgafLib;
using namespace VVViewer;

VvvMousePointer::VvvMousePointer(const char* prm_name) :
        MousePointerActor(prm_name, "VvvMousePointer") {
    _class_name = "VvvMousePointer";
    pI_ = nullptr;

    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    ViewCollisionChecker* pChecker = getViewCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSquare(0, PX_C(16));
    setHitAble(true);
}

void VvvMousePointer::onCreateModel() {
}

void VvvMousePointer::initialize() {
    pI_ = desireActor(GgafLib::DefaultMeshActor, "Guruguru", "Guruguru");
    WorldCollisionChecker* pChecker = pI_->getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(100));
    pI_->setScaleR(3.0);
    pI_->setHitAble(true);
    appendGroupChild(KIND_ACTOR, pI_);
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
        pI_->setPositionByViewCoord(_x, _y, d);
    } else {
        pI_->setPositionByViewCoord(_x, _y, DX_C(-(pCam->_cameraZ_org)));
    }
}

void VvvMousePointer::processJudgement() {
//    _TRACE_("dtop,dbottom="<<DX_PX(pI_->_dest_from_vppln_top)<<","<<DX_PX(pI_->_dest_from_vppln_bottom));
//    _TRACE_("dleft,dright="<<DX_PX(pI_->_dest_from_vppln_left)<<","<<DX_PX(pI_->_dest_from_vppln_right));
}

void VvvMousePointer::onHit(const GgafCore::Actor* prm_pOtherActor) {
    MousePointerActor::onHit(prm_pOtherActor);
}

void VvvMousePointer::onInactive() {
}

VvvMousePointer::~VvvMousePointer() {
}

