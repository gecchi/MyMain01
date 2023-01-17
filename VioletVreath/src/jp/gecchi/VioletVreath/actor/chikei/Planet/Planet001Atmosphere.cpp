#include "Planet001Atmosphere.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi.h"



using namespace GgafLib;
using namespace VioletVreath;

Planet001Atmosphere::Planet001Atmosphere(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planet001Atmosphere") {
    _class_name = "Planet001Atmosphere";
    setHitAble(false);
    setZEnableDraw(true);        //Zバッファは考慮
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
    defineRotMvWorldMatrix_Billboard(); //XYZ軸ビルボード
    drawAnyFar(true); //遠くても表示
}
void Planet001Atmosphere::onCreateModel() {
}

void Planet001Atmosphere::initialize() {
    setCullingDraw(false);
    getVecVehicle()->setFaceAngVelo(AXIS_Z, 1000);
}

void Planet001Atmosphere::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->behave();
}

Planet001Atmosphere::~Planet001Atmosphere() {
}

