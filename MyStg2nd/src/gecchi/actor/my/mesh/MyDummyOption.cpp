#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyDummyOption::MyDummyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent) : DefaultMeshActor(prm_name, "X/ceres") {
_TRACE_("MyDummyOption::MyDummyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyDummyOption";
    _pMyOptionParent = prm_pMyOptionParent;
    _distR = 100000;
    _angPosRotX = 0;
    _no = prm_no;

    MyOption* pMyOption = NEW MyOption("MY_OPTION01", prm_no, this);
    addSubLast(pMyOption);
}

void MyDummyOption::initialize() {
    int v = 4000;
    _angvelo = ((1.0*v / _distR)*(double)ANGLE180)/PI;
    _pGeoMover->setMoveVelocity(v);
    _pGeoMover->setRzMoveAngle(_angPosRotX+ANGLE90);
    _pGeoMover->setRyMoveAngle(0);
    _pGeoMover->setRzMoveAngleVelocity(_angvelo);//�攼�a�q�����x�u�^�p���x��
    _pGeoMover->setRyMoveAngleVelocity(0);//�攼�a�q�����x�u�^�p���x��
    _pGeoMover->setRyMoveAngle(-ANGLE90);//Rz�~�^�����Ă��郂�m��X�����S��]�ɕϊ�
    _Z += GgafDx9Util::COS[_angPosRotX/ANGLE_RATE]*_distR; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
    _Y += GgafDx9Util::SIN[_angPosRotX/ANGLE_RATE]*_distR;

    _sangvelo = 0;

    _X_ParentPrev = _pMyOptionParent->_X;
    _Y_ParentPrev = _pMyOptionParent->_Y;
    _Z_ParentPrev = _pMyOptionParent->_Z;

}

void MyDummyOption::processBehavior() {

    _pGeoMover->setRotAngle(AXIS_X, _pMyOptionParent->_pGeoMover->_angRot[AXIS_X]);
    _pGeoMover->setRotAngle(AXIS_Y, _pMyOptionParent->_pGeoMover->_angRot[AXIS_Y]);
    _pGeoMover->setRotAngle(AXIS_Z, _pMyOptionParent->_pGeoMover->_angRot[AXIS_Z]);

    _pGeoMover->behave();

    //�e�̈ړ����W�����������Đe�Ƀg���[�X
    _X += (_pMyOptionParent->_X - _X_ParentPrev);
    _Y += (_pMyOptionParent->_Y - _Y_ParentPrev);
    _Z += (_pMyOptionParent->_Z - _Z_ParentPrev);


    //���t���[���̂��߂ɐe�̏���ۑ�
    _X_ParentPrev = _pMyOptionParent->_X;
    _Y_ParentPrev = _pMyOptionParent->_Y;
    _Z_ParentPrev = _pMyOptionParent->_Z;

}

void MyDummyOption::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyDummyOption::processOnHit(GgafActor* prm_pActor_Opponent) {
    farewell();
}

MyDummyOption::~MyDummyOption() {
    //DELETE_IMPOSSIBLE_NULL(_pRing);
}
