#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CubeMapMeshTestActor::CubeMapMeshTestActor(const char* prm_name) : CubeMapMeshActor(prm_name, "Thalia_0") {
    //_chk_CubeMapMeshEffectTest
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
    locate(0,0,0);
    setScaleRate(0.5);
    _pMvNavigator->setRzRyMvAng(0,0);
}

void CubeMapMeshTestActor::onActive() {
}


void CubeMapMeshTestActor::processBehavior() {
    if (GgafDx9Input::isPushedDownKey(DIK_T)) {
        _pMvNavigator->execSmoothMvVeloSequenceEx(0, 400*1000, 180);
        _TRACE_("execSmoothMvVeloSequenceEx!!");
    }
    if (GgafDx9Input::isPushedDownKey(DIK_Y)) {
        _pMvNavigator->execSmoothMvVeloSequence1(5000, 0, 400*1000);
        _TRACE_("execSmoothMvVeloSequenceEx!!");
    }
    if (GgafDx9Input::isPushedDownKey(DIK_U)) {
        _pMvNavigator->execSmoothMvVeloSequence2(5000, 0, 180);
        _TRACE_("execSmoothMvVeloSequenceEx!!");
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_E)) {
        _X = _X - 2000;
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_R)) {
        _X = _X + 2000;
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
        _Y = _Y + 2000;
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_D)) {
        _Y = _Y - 2000;
    }
    _TRACE_(getActivePartFrame() <<":"<<_X<<","<<_Y<<","<<_Z);


    _pMvNavigator->behave();
}

CubeMapMeshTestActor::~CubeMapMeshTestActor() {
}

