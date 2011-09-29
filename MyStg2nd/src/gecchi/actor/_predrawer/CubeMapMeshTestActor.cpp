#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


CubeMapMeshTestActor::CubeMapMeshTestActor(const char* prm_name) :
        CubeMapMeshActor(prm_name, "_chk_CubeMapMeshTestModel", NULL) {
    _class_name = "CubeMapMeshTestActor";
    setHitAble(false);
}

void CubeMapMeshTestActor::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.6, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void CubeMapMeshTestActor::initialize() {
    setHitAble(false);
    setCubeMapTexture("Torus_cubemap.dds", 0.1);
    locate(0,0,0);
    setScaleRate(0.2);
    _pKurokoA->setRzRyMvAng(0,0);
}

void CubeMapMeshTestActor::onActive() {
}


void CubeMapMeshTestActor::processBehavior() {
//    if (GgafDxInput::isPushedDownKey(DIK_T)) {
////        _pKurokoA->execSmoothMvVeloSequence(0, 600*1000, 180, 0.4, 0.6, true);
//        _pKurokoA->execSmoothMvVeloSequenceD(10*1000, 0, 600*1000, 0.4, 0.6);
//        _TRACE_("execSmoothMvVeloSequence!!");
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_Y)) {
////        _pKurokoA->execSmoothMvVeloSequence(0, 600*1000, 180, 0.1, 0.3, true);
//        _pKurokoA->execSmoothMvVeloSequenceD(10*1000, 0, 600*1000, 0.1, 0.3);
//        _TRACE_("execSmoothMvVeloSequence!!");
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_U)) {
////        _pKurokoA->execSmoothMvVeloSequence(0, 600*1000, 180, 0.7, 0.9, true);
//        _pKurokoA->execSmoothMvVeloSequenceD(10*1000, 0, 600*1000, 0.7, 0.9);
//        _TRACE_("execSmoothMvVeloSequence!!");
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_W)) {
//        _X = _X - 2000;
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_R)) {
//        _X = _X + 2000;
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_3)) {
//        _Y = _Y + 2000;
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_E)) {
//        _Y = _Y - 2000;
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_4)) {
//        _X = 0;
//    }
////    _TRACE_(getActivePartFrame() <<":"<<_X<<","<<_Y<<","<<_Z);
//
//
//    _pKurokoA->behave();
}

CubeMapMeshTestActor::~CubeMapMeshTestActor() {
}

