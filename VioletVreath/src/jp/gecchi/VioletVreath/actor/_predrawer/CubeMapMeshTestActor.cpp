#include "stdafx.h"
#include "CubeMapMeshTestActor.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CubeMapMeshTestActor::CubeMapMeshTestActor(const char* prm_name) :
        CubeMapMeshActor(prm_name, "_chk_CubeMapMeshTestModel", nullptr) {
    _class_name = "CubeMapMeshTestActor";
    setCubeMap("Ratislavia_cubemap.dds", 0.1);
    setHitAble(false);
}

void CubeMapMeshTestActor::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.6, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void CubeMapMeshTestActor::initialize() {
    setHitAble(false);

    position(0,0,0);
    setScaleR(0.2);
    _pKurokoA->setRzRyMvAng(0,0);
}

void CubeMapMeshTestActor::onActive() {
}


void CubeMapMeshTestActor::processBehavior() {
//    if (GgafDxInput::isPushedDownKey(DIK_T)) {
////        _pKurokoA->slideMvByDT(0, 600*1000, 180, 0.4, 0.6, true);
//        _pKurokoA->slideMvByVD(10*1000, 0, 600*1000, 0.4, 0.6);
//        _TRACE_("slideMv!!");
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_Y)) {
////        _pKurokoA->slideMvByDT(0, 600*1000, 180, 0.1, 0.3, true);
//        _pKurokoA->slideMvByVD(10*1000, 0, 600*1000, 0.1, 0.3);
//        _TRACE_("slideMv!!");
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_U)) {
////        _pKurokoA->slideMvByDT(0, 600*1000, 180, 0.7, 0.9, true);
//        _pKurokoA->slideMvByVD(10*1000, 0, 600*1000, 0.7, 0.9);
//        _TRACE_("slideMv!!");
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
////    _TRACE_(getActiveFrame() <<":"<<_X<<","<<_Y<<","<<_Z);
//
//
//    _pKurokoA->behave();
}

CubeMapMeshTestActor::~CubeMapMeshTestActor() {
}

