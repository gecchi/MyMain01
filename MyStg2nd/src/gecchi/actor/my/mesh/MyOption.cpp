#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOption::MyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent) : DefaultMeshActor(prm_name, "X/ceres") {
    _class_name = "MyOption";
    _pMyOptionParent = prm_pMyOptionParent;
    _distR = 50000;
    _angPosRotX = 0;
    _no = prm_no;
}

void MyOption::initialize() {

    _pGeoMover->setMoveVelocity(2000);
    _pGeoMover->setRzMoveAngleVelocity(2000);
    _pGeoMover->setRyMoveAngle(-ANGLE90);

    _sangvelo = 0;
}

void MyOption::processBehavior() {
    _pGeoMover->behave();
//    _X = _pMyOptionParent->_X;
//    _Y = _pMyOptionParent->_Y;
//    _Z = _pMyOptionParent->_Z;
}

void MyOption::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyOption::processOnHit(GgafActor* prm_pActor_Opponent) {
    farewell();
}

MyOption::~MyOption() {
    //DELETE_IMPOSSIBLE_NULL(_pRing);
}
