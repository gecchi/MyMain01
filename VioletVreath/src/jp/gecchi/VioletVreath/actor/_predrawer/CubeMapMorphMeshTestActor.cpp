#include "CubeMapMorphMeshTestActor.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CubeMapMorphMeshTestActor::CubeMapMorphMeshTestActor(const char* prm_name) :
        CubeMapMorphMeshActor(prm_name, "0/_chk_CubeMapMorphMeshTestModel", nullptr) {
    _class_name = "CubeMapMorphMeshTestActor";
    setCubeMap("Ratislavia_cubemap.dds", 0.1);
    setHitAble(false);
}
void CubeMapMorphMeshTestActor::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
    pModel->setBlinkPower(0.1, 0.6);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void CubeMapMorphMeshTestActor::initialize() {
    setHitAble(false);
//    setScaleR(0.1);
}

void CubeMapMorphMeshTestActor::onActive() {
//    getMorpher()->beat(1, 240, 60, 30, -1);
//    getMorpher()->beat(2, 240, 90, 30, -1);
//    getMorpher()->beat(3, 240, 120, 30, -1);
//    getMorpher()->beat(4, 240, 150, 30, -1);
//    pKuroko->setFaceAngVelo(AXIS_Y, 500);
}


void CubeMapMorphMeshTestActor::processBehavior() {


    /////////////モーフテスト(DefaultMorphMeshActor継承要)////////////////
//    if (GgafDxInput::isPressedKey(DIK_1)) {
//        getMorpher()->beat(1, 30, 3, 22);
//    } else if (GgafDxInput::isPressedKey(DIK_7)) {
//        getMorpher()->stop(1);
//    }
//    if (GgafDxInput::isPressedKey(DIK_2)) {
//        getMorpher()->transitionAcceUntil(2, 1.0f, 0, 0.002f);
//    } else if (GgafDxInput::isPressedKey(DIK_8)) {
//        getMorpher()->transitionAcceUntil(2, 0, 0, -0.004f);
//    }
//    if (GgafDxInput::isPressedKey(DIK_3)) {
//        getMorpher()->beat(3, 20, 13, 2);
//    } else if (GgafDxInput::isPressedKey(DIK_9)) {
//        getMorpher()->stop(3);
//    }
//    if (GgafDxInput::isPressedKey(DIK_4)) {
//        getMorpher()->beat(4, 60, 3, 20);
//    } else if (GgafDxInput::isPressedKey(DIK_0)) {
//        getMorpher()->stop(4);
//    }
//    getMorpher()->behave();

//    if (GgafDxInput::isPressedKey(DIK_1)) {
//        getMorpher()->transitionLinearUntil(1, 1.0, 30);
//        getMorpher()->transitionLinearUntil(2, 0, 30);
//        getMorpher()->transitionLinearUntil(3, 0, 30);
//        getMorpher()->transitionLinearUntil(4, 0, 30);
//    } else if (GgafDxInput::isPressedKey(DIK_7)) {
//        getMorpher()->transitionLinearUntil(1, 0, 30);
//    }
//    if (GgafDxInput::isPressedKey(DIK_2)) {
//        getMorpher()->transitionLinearUntil(1, 0, 30);
//        getMorpher()->transitionLinearUntil(2, 1.0, 30);
//        getMorpher()->transitionLinearUntil(3, 0, 30);
//        getMorpher()->transitionLinearUntil(4, 0, 30);
//    } else if (GgafDxInput::isPressedKey(DIK_8)) {
//        getMorpher()->transitionLinearUntil(2, 0, 30);
//    }
//    if (GgafDxInput::isPressedKey(DIK_3)) {
//        getMorpher()->transitionLinearUntil(1, 0, 30);
//        getMorpher()->transitionLinearUntil(2, 0, 30);
//        getMorpher()->transitionLinearUntil(3, 1.0, 30);
//        getMorpher()->transitionLinearUntil(4, 0, 30);
//    } else if (GgafDxInput::isPressedKey(DIK_9)) {
//        getMorpher()->transitionLinearUntil(3, 0, 30);
//    }
//    if (GgafDxInput::isPressedKey(DIK_4)) {
//        getMorpher()->transitionLinearUntil(1, 0, 30);
//        getMorpher()->transitionLinearUntil(2, 0, 30);
//        getMorpher()->transitionLinearUntil(3, 0, 30);
//        getMorpher()->transitionLinearUntil(4, 1.0, 30);
//    } else if (GgafDxInput::isPressedKey(DIK_0)) {
//        getMorpher()->transitionLinearUntil(4, 0, 30);
//    }
//    getMorpher()->behave();
//    /////////////モーフテスト////////////////
//    pKuroko->behave();
//    getMorpher()->behave();
}

CubeMapMorphMeshTestActor::~CubeMapMorphMeshTestActor() {
}

