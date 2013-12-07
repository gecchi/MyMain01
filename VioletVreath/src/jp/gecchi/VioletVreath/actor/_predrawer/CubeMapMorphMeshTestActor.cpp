#include "stdafx.h"
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
    _pModel->_pTexBlinker->setBlinkableRange(0.6, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void CubeMapMorphMeshTestActor::initialize() {
    setHitAble(false);
//    _pMorpher->setWeight(0, 1.0);
//    setScaleR(0.1);
}

void CubeMapMorphMeshTestActor::onActive() {
//    _pMorpher->beat(1, 240, 60, 30, -1);
//    _pMorpher->beat(2, 240, 90, 30, -1);
//    _pMorpher->beat(3, 240, 120, 30, -1);
//    _pMorpher->beat(4, 240, 150, 30, -1);
//    _pKuroko->setFaceAngVelo(AXIS_Y, 500);
}


void CubeMapMorphMeshTestActor::processBehavior() {


    /////////////モーフテスト(DefaultMorphMeshActor継承要)////////////////
//    if (GgafDxInput::isBeingPressedKey(DIK_1)) {
//        _pMorpher->beat(1, 30, 3, 22);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_7)) {
//        _pMorpher->stopImmed(1);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_2)) {
//        _pMorpher->morphAcceStep(2, 1.0f, 0, 0.002f);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_8)) {
//        _pMorpher->morphAcceStep(2, 0, 0, -0.004f);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_3)) {
//        _pMorpher->beat(3, 20, 13, 2);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_9)) {
//        _pMorpher->stopImmed(3);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_4)) {
//        _pMorpher->beat(4, 60, 3, 20);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_0)) {
//        _pMorpher->stopImmed(4);
//    }
//    _pMorpher->behave();

//    if (GgafDxInput::isBeingPressedKey(DIK_1)) {
//        _pMorpher->morphLinerUntil(1, 1.0, 30);
//        _pMorpher->morphLinerUntil(2, 0, 30);
//        _pMorpher->morphLinerUntil(3, 0, 30);
//        _pMorpher->morphLinerUntil(4, 0, 30);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_7)) {
//        _pMorpher->morphLinerUntil(1, 0, 30);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_2)) {
//        _pMorpher->morphLinerUntil(1, 0, 30);
//        _pMorpher->morphLinerUntil(2, 1.0, 30);
//        _pMorpher->morphLinerUntil(3, 0, 30);
//        _pMorpher->morphLinerUntil(4, 0, 30);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_8)) {
//        _pMorpher->morphLinerUntil(2, 0, 30);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_3)) {
//        _pMorpher->morphLinerUntil(1, 0, 30);
//        _pMorpher->morphLinerUntil(2, 0, 30);
//        _pMorpher->morphLinerUntil(3, 1.0, 30);
//        _pMorpher->morphLinerUntil(4, 0, 30);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_9)) {
//        _pMorpher->morphLinerUntil(3, 0, 30);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_4)) {
//        _pMorpher->morphLinerUntil(1, 0, 30);
//        _pMorpher->morphLinerUntil(2, 0, 30);
//        _pMorpher->morphLinerUntil(3, 0, 30);
//        _pMorpher->morphLinerUntil(4, 1.0, 30);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_0)) {
//        _pMorpher->morphLinerUntil(4, 0, 30);
//    }
//    _pMorpher->behave();
//    /////////////モーフテスト////////////////
//    _pKuroko->behave();
//    _pMorpher->behave();
}

CubeMapMorphMeshTestActor::~CubeMapMorphMeshTestActor() {
}

