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
    _angExpanse = 0;


}

void MyDummyOption::initialize() {
    _fAlpha = 0.9;

    int v = 4000;
    _angvelo = ((1.0*v / _distR)*(double)ANGLE180)/PI;
    _pGeoMover->setMoveVelocity(v);
    _pGeoMover->setRzMoveAngle(_angPosRotX+ANGLE90);
    _pGeoMover->setRyMoveAngle(-ANGLE90);
    _pGeoMover->setRzMoveAngleVelocity(_angvelo);//�攼�a�q�����x�u�^�p���x��
    _pGeoMover->setRyMoveAngleVelocity(0);//�攼�a�q�����x�u�^�p���x��
    _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_Flg = true;
    _pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_Flg = true; //RY�͎g���Ă͑ʖځB�ϊ��s��RxRyRz������
    _Z = GgafDx9Util::COS[_angPosRotX/ANGLE_RATE]*_distR; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
    _Y = GgafDx9Util::SIN[_angPosRotX/ANGLE_RATE]*_distR;

    _pGeoMover->setRotAngleVelocity(AXIS_X, 8000);
    //���C�u�����̈ړ��@�\���g�p���āA�ȉ��̂悤�ȏ�Ԃ܂ł���������
    //���Ƃ͗͋Z�ŉ�]������B
    //
    //       ����
    //
    //
    //                    ��
    //��        ��        ��
    //��         (0,0,0)
    //
    //
    //         ����
    //
    //(100,0,0) ���猴�_�������C���[�W�A���͌��_
    //��y��  ��z��  �Ex��


    _angExpanse = ANGLE90;

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;

    _RXorg = _RX;
    _RYorg = _RY;
    _RZorg = _RZ;

    _angRot_ParentPrev[AXIS_X] = _pMyOptionParent->_pGeoMover->_angRot[AXIS_X];
    _angRot_ParentPrev[AXIS_Y] = _pMyOptionParent->_pGeoMover->_angRot[AXIS_Y];
    _angRot_ParentPrev[AXIS_Z] = _pMyOptionParent->_pGeoMover->_angRot[AXIS_Z];


}

void MyDummyOption::processBehavior() {
     _X = _Xorg;
     _Y = _Yorg;
     _Z = _Zorg;
     _RX = _RXorg;
     _RY = _RYorg;
     _RZ = _RZorg;

    _pGeoMover->behave();

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;
    _RXorg = _RX;
    _RYorg = _RY;
    _RZorg = _RZ;



    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static angle diffRot[3];

    sinRZ = GgafDx9Util::SIN[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Z] / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Z] / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y] / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y] / ANGLE_RATE];
    _Xwk = _X;
    _Ywk = _Y;
    _Zwk = _Z;
    _X = cosRZ*cosRY*_Xwk + -sinRZ*_Ywk + cosRZ*sinRY*_Zwk;
    _Y = sinRZ*cosRY*_Xwk + cosRZ*_Ywk + sinRZ*sinRY*_Zwk;
    _Z = -sinRY*_Xwk + cosRY*_Zwk;

    //Quaternion�Ŏ���]
    static float vX_axis,vY_axis,vZ_axis; //��]�����������x�N�g��
    vX_axis = cosRZ*cosRY*_pGeoMover->_vX + -sinRZ*_pGeoMover->_vY + cosRZ*sinRY*_pGeoMover->_vZ;
    vY_axis = sinRZ*cosRY*_pGeoMover->_vX +  cosRZ*_pGeoMover->_vY + sinRZ*sinRY*_pGeoMover->_vZ;
    vZ_axis = -sinRY*_pGeoMover->_vX + cosRY*_pGeoMover->_vZ;

    static float sinHalf, cosHalf;
    sinHalf = GgafDx9Util::SIN[_angExpanse/ANGLE_RATE/2]; //_angExpanse=��]���������p�x
    cosHalf = GgafDx9Util::COS[_angExpanse/ANGLE_RATE/2];
    static double vx, vy, vz; //��]�������������x�N�g���i���̓_���W�j�B���ˏ�ɂȂ��Ă܂��B
    static double k;   //���K���{��
    vx = ((double)_X) / LEN_UNIT;
    vy = ((double)_Y) / LEN_UNIT;
    vz = ((double)_Z) / LEN_UNIT;
    k = 1 / GgafDx9Util::sqrt_fast(vx*vx + vy*vy + vz*vz);

    //�v�Z
    GgafDx9Quaternion Q( cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    Q.mul(0, k*vx, k*vy, k*vz); //R*P
    Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //Q._x, Q._y, Q._z ����]��̍��W�ƂȂ�
    //Z����]�AY����]�p�x���v�Z
    GgafDx9Util::getRotAngleZY(
        Q._x,
        Q._y,
        Q._z,
        _RZ,
        _RY
     );

    _RZ = GgafDx9GeometryMover::simplifyAngle(_RZ);
    _RY = GgafDx9GeometryMover::simplifyAngle(_RY);

    _angExpanse = GgafDx9GeometryMover::simplifyAngle(_angExpanse+500);


    _X += GameGlobal::_pMyShip->_X;
    _Y += GameGlobal::_pMyShip->_Y;
    _Z += GameGlobal::_pMyShip->_Z;
    _TX = _X;
    _TY = _Y;
    _TZ = _Z;
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


