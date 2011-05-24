#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CubeMapMorphMeshEffectActor::CubeMapMorphMeshEffectActor(const char* prm_name) : CubeMapMorphMeshActor(prm_name, "4/_chk_CubeMapMorphMeshEffectTest") {
    _class_name = "CubeMapMorphMeshEffectActor";
    setHitAble(false);
}
void CubeMapMorphMeshEffectActor::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
    _pGgafDx9Model->_blink_threshold = 0.6;
    _pGgafDx9Model->setSpecular(5.0, 1.0);
}

void CubeMapMorphMeshEffectActor::initialize() {
    setHitAble(false);
    setCubeMapTexture("Torus_cubemap.dds", 0.1);
    _pMorpher->setWeight(0, 1.0);
    setScaleRate(0.2);
}

void CubeMapMorphMeshEffectActor::onActive() {
    _pMorpher->beat(1, 240, 60, 30, -1);
    _pMorpher->beat(2, 240, 90, 30, -1);
    _pMorpher->beat(3, 240, 120, 30, -1);
    _pMorpher->beat(4, 240, 150, 30, -1);
    _pKuroko->setFaceAngVelo(AXIS_Y, 500);
}


void CubeMapMorphMeshEffectActor::processBehavior() {
    _pKuroko->behave();
    _pMorpher->behave();
}

CubeMapMorphMeshEffectActor::~CubeMapMorphMeshEffectActor() {
}

