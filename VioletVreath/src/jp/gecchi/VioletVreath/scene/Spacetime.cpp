#include "Spacetime.h"

#include "jp/gecchi/VioletVreath/actor/camera/VVCameraWorkerChanger.h"
#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

Spacetime::Spacetime(const char* prm_name, Camera* prm_pCamera) : DefaultSpacetime(prm_name, prm_pCamera) {
    _class_name = "Spacetime";
    pWorld_ = nullptr;
    _TRACE_(FUNC_NAME<<"");
    pCameraWorkerChanger_ = NEW VVCameraWorkerChanger("CameraWorkerChanger", prm_pCamera);
    bringSceneMediator()->appendGroupChild(pCameraWorkerChanger_);
    //y‚ß‚àz
    //‚±‚±‚ÅActor‚âScene‚ÌNEW‚ğ‚µ‚Ä‚Í‚È‚ç‚È‚¢B
    //‚Ü‚¸‚Í‚±‚Ì¢‚ğì‚é‚±‚Æ‚ğ—Dæ‚µ‚È‚¢‚ÆA‚¢‚ë‚¢‚ë‚Æ•s“s‡‚ª‚ ‚éB
}

void Spacetime::initialize() {
    pWorld_ = desireScene(VioletVreath::World);
    appendChild(pWorld_);
    _TRACE_(FUNC_NAME<<"");
}

void Spacetime::processBehavior() {
    DefaultSpacetime::processBehavior();
}

void Spacetime::processJudgement() {
    DefaultSpacetime::processJudgement();
}

Spacetime::~Spacetime() {
}
