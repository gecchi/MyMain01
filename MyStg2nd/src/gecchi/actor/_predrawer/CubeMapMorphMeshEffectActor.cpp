#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CubeMapMorphMeshEffectActor::CubeMapMorphMeshEffectActor(const char* prm_name) : CubeMapMorphMeshActor(prm_name, "1/ThaliaCM") {
    _class_name = "CubeMapMorphMeshEffectActor";
    setHitAble(false);
}
void CubeMapMorphMeshEffectActor::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
    _pGgafDx9Model->_blink_threshold = 0.9;
    _pGgafDx9Model->setSpecular(5.0, 1.0);
}

void CubeMapMorphMeshEffectActor::initialize() {
    setHitAble(false);
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
}

void CubeMapMorphMeshEffectActor::onActive() {
    _pMorpher->beat(1, 130, 60, 10, -1);
}


void CubeMapMorphMeshEffectActor::processBehavior() {
    _pKuroko->behave();
    _pMorpher->behave();
}

CubeMapMorphMeshEffectActor::~CubeMapMorphMeshEffectActor() {
}

