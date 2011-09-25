#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CubeMapMeshSetTestActor::CubeMapMeshSetTestActor(const char* prm_name) :
        CubeMapMeshSetActor(prm_name, "_chk_CubeMapMeshSetTestModel", NULL) {
    _class_name = "CubeMapMeshSetTestActor";
    setHitAble(false);
}

void CubeMapMeshSetTestActor::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.6, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void CubeMapMeshSetTestActor::initialize() {
    setHitAble(false);
    setCubeMapTexture("Torus_cubemap.dds", 0.2);
    setScaleRate(2);
}

void CubeMapMeshSetTestActor::onActive() {
    _pKurokoA->setFaceAngVelo(AXIS_Y, 200);
}


void CubeMapMeshSetTestActor::processBehavior() {
    _pKurokoA->behave();
}

CubeMapMeshSetTestActor::~CubeMapMeshSetTestActor() {
}

