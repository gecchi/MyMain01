#include "Planet001Atmosphere.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Planet001Atmosphere::Planet001Atmosphere(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planet001Atmosphere", nullptr) {
    _class_name = "Planet001Atmosphere";
    setHitAble(false);
    setZEnable(true);        //Zバッファは考慮
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setSpecialDrawDepth(RENDER_DEPTH_LEVEL_SP_BACK1-2);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //XYZ軸ビルボード
    drawAnyFar(true); //遠くても表示
}
void Planet001Atmosphere::onCreateModel() {
}

void Planet001Atmosphere::initialize() {
    setAlpha(0.9);
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);
}

void Planet001Atmosphere::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->behave();
}

Planet001Atmosphere::~Planet001Atmosphere() {
}

