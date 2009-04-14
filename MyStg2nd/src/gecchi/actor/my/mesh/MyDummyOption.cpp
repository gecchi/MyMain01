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
    _no = prm_no;
    _angveloMove = 0;//����ړ��p���x�i�ǂݏo����p�j

    _angPosition = 0;     //�~���㏉���ʒu�p�x�i���͊p�j�i�㏑�������ݒ�j
    _radius = 200000;     //�������a�����i�㏑�������ݒ�j
    _veloMove = 5000;     //����ړ����x�i�㏑�������ݒ�j
    _angExpanse = 0;      //�I�v�V�����̍L����p�̉�]�p�i�㏑�������ݒ�j
    _angveloExpanse = 1000; //�I�v�V�����̍L����p�̊p��]���x �i�㏑�������ݒ�j

}

void MyDummyOption::initialize() {
    _angveloMove = ((1.0*_veloMove / _radius)*(double)ANGLE180)/PI;
    _pGeoMover->setMoveVelocity(_veloMove);
    _pGeoMover->setRzMoveAngle(_angPosition+ANGLE90);
    _pGeoMover->setRyMoveAngle(-ANGLE90);
    _pGeoMover->setRzMoveAngleVelocity(_angveloMove);//�攼�a�q�����x�u�^�p���x��
    _pGeoMover->setRyMoveAngleVelocity(0);//�攼�a�q�����x�u�^�p���x��
    _Z = GgafDx9Util::COS[_angPosition/ANGLE_RATE]*_radius; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
    _Y = GgafDx9Util::SIN[_angPosition/ANGLE_RATE]*_radius;
    _X = 50000; //TODO:�{����0�i���@�̐^���j�ɂ������B�������V���o�����b�N���N���₷���āA�J�N�����ڂɂ��B�����ł��Ȃ��B
                //��⒆�S���炸�炷���ŁA������x�����̑J�ڂ����炩�ɂ��A
                //�����AXIS_X ����]�𑬂߂ɐݒ肵�A�C�t����Ȃ��悤�ɂ��܂�������Ë��B
    _pGeoMover->setRotAngleVelocity(AXIS_X, 8000);

    _RZ2 = _RZ;
    _RY2 = _RY;
    _X2 = _X;
    _Y2 = _Y;
    _Z2 = _Z;

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;
    _RXorg = _RX;
    _RYorg = _RY;
    _RZorg = _RZ;












    _pMyLaserChipRotation = NEW MyLaserChipRotationActor("ROTLaser");
    getLordActor()->accept(KIND_MY_SHOT_GU, _pMyLaserChipRotation);

}

void MyDummyOption::processBehavior() {
    _X = _Xorg;
    _Y = _Yorg;
    _Z = _Zorg;
    _RX = _RXorg;
    _RY = _RYorg;
    _RZ = _RZorg;

    _pGeoMover->setMoveVelocity(_veloMove);
    _pGeoMover->behave();

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;
    _RXorg = _RX;
    _RYorg = _RY;
    _RZorg = _RZ;


    //�����܂łŁAGgafDx9GeometryMover�̈ړ��@�\���g�p���A
    //�ȉ��̂悤�ȏ�Ԃ܂Ŏ����B
    //(100,0,0) ���猴�_�������C���[�W�A���͌��_
    //��y��  ��z��  �Ex��
    //
    //
    //              YZ���ʂɕ��s�ł��邮�����Ă�B
    //       ����
    //
    //
    //                    ��
    //��        ��        ��
    //��     (0,0,0)      (-50000, 0, _radius)
    //
    //
    //         ����
    //
    //
    //�������܂��F�X��]���K�v�B���Ƃ͕��ʂɌv�Z�i�͋Z�j�ŁA���W��]�A������]���s�Ȃ��B
    //TODO:�����ėp���œK���B


    static float sinRY, cosRY, sinRZ, cosRZ;

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
    _RZ2 = _RZ;
    _RY2 = _RY;
    _X += GameGlobal::_pMyShip->_X;
    _Y += GameGlobal::_pMyShip->_Y;
    _Z += GameGlobal::_pMyShip->_Z;
    _X2 = _X;
    _Y2 = _Y;
    _Z2 = _Z;

    _angExpanse = GgafDx9GeometryMover::simplifyAngle(_angExpanse+_angveloExpanse);










    if (VB::isBeingPressed(VB_SHOT2)) {
        MyLaserChip* pLaser = (MyLaserChip*)_pMyLaserChipRotation->obtain();
        if (pLaser != NULL) {
            pLaser->setRadicalActor(this);
            pLaser->_X = _X2;
            pLaser->_Y = _Y2;
            pLaser->_Z = _Z2;

            pLaser->_pGeoMover->_vX = Q._x;
            pLaser->_pGeoMover->_vY = Q._y;
            pLaser->_pGeoMover->_vZ = Q._z;
            pLaser->_pGeoMover->_angRzMove = _RZ2;
            pLaser->_pGeoMover->_angRyMove = _RY2;

            pLaser->_pGeoMover->_angRot[AXIS_Z] = _RZ2;
            pLaser->_pGeoMover->_angRot[AXIS_Y] = _RY2;

            //pLaser->_frame_on_change_to_active_flg = _lifeframe;
        }
    }




}

void MyDummyOption::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyDummyOption::processOnHit(GgafActor* prm_pActor_Opponent) {
    arigatou_sayounara();
}

MyDummyOption::~MyDummyOption() {
    //DELETE_IMPOSSIBLE_NULL(_pRing);
}


