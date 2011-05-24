#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CubeMapMeshEffectActor::CubeMapMeshEffectActor(const char* prm_name) : CubeMapMeshActor(prm_name, "_chk_CubeMapMeshEffectTest") {
    _class_name = "CubeMapMeshEffectActor";
    setHitAble(false);
}

void CubeMapMeshEffectActor::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
    _pGgafDx9Model->_blink_threshold = 0.6;
    _pGgafDx9Model->setSpecular(5.0, 1.0);
}

void CubeMapMeshEffectActor::initialize() {
    setHitAble(false);
    setCubeMapTexture("Torus_cubemap.dds", 0.1);
    setScaleRate(3);
}

void CubeMapMeshEffectActor::onActive() {
    _X = 100*1000; _Y = 100*1000;
    _pKuroko->setFaceAngVelo(AXIS_Y, 500);
}


void CubeMapMeshEffectActor::processBehavior() {
    _pKuroko->behave();
}

CubeMapMeshEffectActor::~CubeMapMeshEffectActor() {
}

