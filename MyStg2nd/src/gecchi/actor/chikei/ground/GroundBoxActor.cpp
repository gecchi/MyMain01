#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GroundBoxActor::GroundBoxActor(const char* prm_name) :
    WallActor(prm_name, "16/g_box001") {
    _class_name = "GroundBoxActor";
    MyStgUtil::resetGroundBoxActorStatus(_pStatus);
    setHitAble(true);
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(true);  //Z�o�b�t�@�͏������ݗL��
}


void GroundBoxActor::initialize() {
    _SX=_SY=_SZ = 2000;
    setBoundingSphereRadiusRate(2.0);
}



GroundBoxActor::~GroundBoxActor() {
}
