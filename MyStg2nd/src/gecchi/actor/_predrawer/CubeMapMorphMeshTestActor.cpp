#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CubeMapMorphMeshTestActor::CubeMapMorphMeshTestActor(const char* prm_name) : CubeMapMorphMeshActor(prm_name, "4/_chk_CubeMapMorphMeshEffectTest") {
    _class_name = "CubeMapMorphMeshTestActor";
    setHitAble(false);
}
void CubeMapMorphMeshTestActor::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.6, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void CubeMapMorphMeshTestActor::initialize() {
    setHitAble(false);
    setCubeMapTexture("Torus_cubemap.dds", 0.1);
    _pMorpher->setWeight(0, 1.0);
    setScaleRate(0.1);
}

void CubeMapMorphMeshTestActor::onActive() {
    _pMorpher->beat(1, 240, 60, 30, -1);
    _pMorpher->beat(2, 240, 90, 30, -1);
    _pMorpher->beat(3, 240, 120, 30, -1);
    _pMorpher->beat(4, 240, 150, 30, -1);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 500);
}


void CubeMapMorphMeshTestActor::processBehavior() {


    /////////////モーフテスト(DefaultMorphMeshActor継承要)////////////////
//    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
//        _pMorpher->beat(1, 30, 3, 22);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
//        _pMorpher->stopImmediately(1);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
//        _pMorpher->intoTargetAcceStep(2, 1.0f, 0, 0.002f);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
//        _pMorpher->intoTargetAcceStep(2, 0, 0, -0.004f);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
//        _pMorpher->beat(3, 20, 13, 2);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
//        _pMorpher->stopImmediately(3);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
//        _pMorpher->beat(4, 60, 3, 20);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
//        _pMorpher->stopImmediately(4);
//    }
//    _pMorpher->behave();

//    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
//        _pMorpher->intoTargetLinerUntil(1, 1.0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 1.0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 1.0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 1.0, 30);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    }
//    _pMorpher->behave();
    /////////////モーフテスト////////////////
    _pKurokoA->behave();
    _pMorpher->behave();
}

CubeMapMorphMeshTestActor::~CubeMapMorphMeshTestActor() {
}

