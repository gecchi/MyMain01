#include "CubeMapMeshTestActor.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CubeMapMeshTestActor::CubeMapMeshTestActor(const char* prm_name) :
        CubeMapMeshActor(prm_name, "_chk_CubeMapMeshTestModel", nullptr) {
    _class_name = "CubeMapMeshTestActor";
    setCubeMap("Ratislavia_cubemap.dds", 0.1);
    setHitAble(false);
}

void CubeMapMeshTestActor::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.6);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
    pModel->setSpecular(5.0, 1.0);
}

void CubeMapMeshTestActor::initialize() {
    setHitAble(false);

    position(0,0,0);
    setScaleR(0.2);
}

void CubeMapMeshTestActor::onActive() {
}


void CubeMapMeshTestActor::processBehavior() {
}

CubeMapMeshTestActor::~CubeMapMeshTestActor() {
}

