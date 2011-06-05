#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CubeMapMeshTestActor::CubeMapMeshTestActor(const char* prm_name) : CubeMapMeshActor(prm_name, "_chk_CubeMapMeshEffectTest") {
    _class_name = "CubeMapMeshTestActor";
    setHitAble(false);
}

void CubeMapMeshTestActor::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.6, 0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
    _pGgafDx9Model->setSpecular(5.0, 1.0);
}

void CubeMapMeshTestActor::initialize() {
    setHitAble(false);
    setCubeMapTexture("Torus_cubemap.dds", 0.1);
    setScaleRate(3);
}

void CubeMapMeshTestActor::onActive() {
    _X = 100*1000; _Y = 100*1000;
    _pMvNavigator->setFaceAngVelo(AXIS_Y, 500);
}


void CubeMapMeshTestActor::processBehavior() {
    _pMvNavigator->behave();
}

CubeMapMeshTestActor::~CubeMapMeshTestActor() {
}

