#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CubeMapMeshSetEffectActor::CubeMapMeshSetEffectActor(const char* prm_name) : CubeMapMeshSetActor(prm_name, "_chk_CubeMapMeshSetEffectTest") {
    _class_name = "CubeMapMeshSetEffectActor";
    setHitAble(false);
}

void CubeMapMeshSetEffectActor::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.6, 0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
    _pGgafDx9Model->setSpecular(5.0, 1.0);
}

void CubeMapMeshSetEffectActor::initialize() {
    setHitAble(false);
    setCubeMapTexture("Torus_cubemap.dds", 0.2);
    setScaleRate(2);
}

void CubeMapMeshSetEffectActor::onActive() {
    _pMvNavigator->setFaceAngVelo(AXIS_Y, 200);
}


void CubeMapMeshSetEffectActor::processBehavior() {
    _pMvNavigator->behave();
}

CubeMapMeshSetEffectActor::~CubeMapMeshSetEffectActor() {
}

