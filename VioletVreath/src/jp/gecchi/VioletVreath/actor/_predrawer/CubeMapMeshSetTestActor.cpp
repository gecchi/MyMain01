#include "stdafx.h"
#include "CubeMapMeshSetTestActor.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CubeMapMeshSetTestActor::CubeMapMeshSetTestActor(const char* prm_name) :
        CubeMapMeshSetActor(prm_name, "_chk_CubeMapMeshSetTestModel", nullptr) {
    _class_name = "CubeMapMeshSetTestActor";
    setCubeMap("Sylvia_cubemap.dds", 0.2);
    setHitAble(false);
}

void CubeMapMeshSetTestActor::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.6, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void CubeMapMeshSetTestActor::initialize() {
    setHitAble(false);
    setScaleR(2);
}

void CubeMapMeshSetTestActor::onActive() {
    _pKurokoA->setFaceAngVelo(AXIS_Y, 200);
}

void CubeMapMeshSetTestActor::processBehavior() {
    _pKurokoA->behave();
}

CubeMapMeshSetTestActor::~CubeMapMeshSetTestActor() {
}

