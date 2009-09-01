#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyDummyOption::MyDummyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent) : DefaultMorphMeshActor(prm_name, "4/Ceres") {
//MyDummyOption::MyDummyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent) : DefaultMeshSetActor(prm_name, "ceres") {

_TRACE_("MyDummyOption::MyDummyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyDummyOption";
    _pMyOptionParent = prm_pMyOptionParent;
    _no = prm_no;
    _angveloMove = 0;//����ړ��p���x�i�ǂݏo����p�j

    _angPosition = 0;     //�~���㏉���ʒu�p�x�i���͊p�j�i�㏑�������ݒ�j
    _radiusPosition = 150000;     //�������a�����i�㏑�������ݒ�j
    _veloMove = 5000;     //����ړ����x�i�㏑�������ݒ�j
    _angExpanse = 290000;      //�I�v�V�����̍L����p�̉�]�p�i�㏑�������ݒ�j
    _angveloExpanse = 0; //�I�v�V�����̍L����p�̊p��]���x �i�㏑�������ݒ�j
    _pSeCon_Laser = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->connect("laser001");

    _pLaserChipDispatcher = NEW LaserChipDispatcher("ROTLaser");
    _pLaserChipDispatcher->_pSeConnection = _pSeCon_Laser;
    MyLaserChip001* pChip;
    for (int i = 0; i < 50; i++) { //���[�U�[�X�g�b�N
        Sleep(2); //�H��ɋC���g���B
        stringstream name;
        name <<  getName() << "'s MYS_LaserChip" << i;
        string name2 = name.str();
        pChip = NEW MyLaserChip001(name2.c_str());
//        pChip->setSource(this);
//        pChip->_pSource_vX = &_Q._x;
//        pChip->_pSource_vY = &_Q._y;
//        pChip->_pSource_vZ = &_Q._z;
        pChip->inactivateImmediately();
        _pLaserChipDispatcher->addLaserChip(pChip);
    }
    addSubLast(_pLaserChipDispatcher); //���T�u

}

void MyDummyOption::initialize() {
    _angveloMove = ((1.0*_veloMove / _radiusPosition)*(double)ANGLE180)/PI;
    _pMover->setMoveVelocity(_veloMove);
    _pMover->setRzMoveAngle(_angPosition+ANGLE90);
    _pMover->setRyMoveAngle(-ANGLE90);
    _pMover->setRzMoveAngleVelocity(_angveloMove);//�攼�a�q�����x�u�^�p���x��
    _pMover->setRyMoveAngleVelocity(0);//�攼�a�q�����x�u�^�p���x��
    _Z = GgafDx9Util::COS[_angPosition/ANGLE_RATE]*_radiusPosition; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
    _Y = GgafDx9Util::SIN[_angPosition/ANGLE_RATE]*_radiusPosition;
    _X = 0;
//_X = 50000; //TODO:���������I�v�V������X����]���Ă���ƁA _angExpanse �̒l�ɂ���Ă̓V���o�����b�N���N���āA
//                //�J�N�����ڂɂ��i�ڂɂ������Ǝ~�܂�Ȃ��j�B������f�O�B�I�v�V�����̉�]���l�������B
//                //�������邽�߂ɂ͍��{�I�ɉ�]�����̃��C�u����(GgafDx9GeometryMover)����蒼���K�v�A���B���Ԃ�����΍l����B��񂵁B
//                //TODO:2009/04/08
//                //�{����0�i���@�̐^���j�ɂ������B���A��⎩�@�̐^�����炸�炷���ŁA�V���o�����b�N�ɂ�郏�[�v�̂悤�ȉ�]����m�������ɘa����B
//                //X����]�p�p���x�𑬂߂ɐݒ肵�A���邭�鑬���񂵂ċC�t����Ȃ��悤�ɂ��܂����B���Ɓ������t�߂ŋ}���ȉ�]���N�������͖Ƃ�Ȃ��B
    _pMover->setRotAngleVelocity(AXIS_X, 8000);

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

    GameGlobal::_pSceneCommon->getLordActor()->accept(KIND_MY_SHOT_GU, _pLaserChipDispatcher->extract());

}

void MyDummyOption::processBehavior() {
    /////////////���[�t�e�X�g(DefaultMorphMeshActor�p���v)////////////////
    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
        _pMorpher->loopTriangleWave(1, 30, 3, 22);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
        _pMorpher->stopImmediately(1);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
        _pMorpher->intoTargetAccelerationStep(2, 1.0, 0, 0.002);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
        _pMorpher->intoTargetAccelerationStep(2, 0, 0, -0.004);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
        _pMorpher->loopTriangleWave(3, 20, 13, 2);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
        _pMorpher->stopImmediately(3);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
        _pMorpher->loopTriangleWave(4, 60, 3, 20);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
        _pMorpher->stopImmediately(4);
    }

    _pMorpher->behave();
    /////////////���[�t�e�X�g////////////////

    if (!VB::isBeingPressed(VB_SHOT2) && VB::isBeingPressed(VB_OPTION)) {
        _angveloExpanse = 1000;
    } else {
        _angveloExpanse = 0;
    }


    _X = _Xorg;
    _Y = _Yorg;
    _Z = _Zorg;
    _RX = _RXorg;
    _RY = _RYorg;
    _RZ = _RZorg;

    _pMover->setMoveVelocity(_veloMove);
    _pMover->behave();

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;
    _RXorg = _RX;
    _RYorg = _RY;
    _RZorg = _RZ;

    //��������
    //�����܂łŁAGgafDx9GeometryMover�̃��\�b�h�݂̂ŁA
    //�ȉ��̂悤�ȏ�Ԃ܂ł����Ă����B
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
    //��     (0,0,0)      (-50000, 0, _radiusPosition)
    //
    //
    //         ����
    //          (-50000, -1*_radiusPosition, 0)
    //
    //�������܂��F�X�Ɖ�]���������߁B���Ƃ͕��ʂɌv�Z�i�͋Z�j�ŁA���W��]�A������]���s�Ȃ��B
    //�_�~�[�̃A�N�^�[��A�����悤�Ƃ��������낢�����AQuaternion ���g�킴��𓾂Ȃ��i�̂ł͂Ȃ����G�j�B
    //TODO:�œK�����ׂ��A�������d�����B�����ėp��

    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;

    sinRX = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angRot[AXIS_X] / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angRot[AXIS_X] / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angRot[AXIS_Z] / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angRot[AXIS_Z] / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angRot[AXIS_Y] / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angRot[AXIS_Y] / ANGLE_RATE];
    //���@�𒆐S��VIEW�ϊ��̂悤�Ȑ���
    //_TRACE_(_pMyOptionParent->_pMover->_angRot[AXIS_Z]<<" "<<_pMyOptionParent->_pMover->_angRot[AXIS_Y]);

    //Y����] �� Z����]
    _X = cosRY*cosRZ*_Xorg + cosRY*-sinRZ*_Yorg + sinRY*_Zorg;
    _Y = sinRZ*_Xorg + cosRZ*_Yorg;
    _Z = -sinRY*cosRZ*_Xorg + -sinRY*-sinRZ*_Yorg + cosRY*_Zorg;

//    Z����] �� Y����]
//    _X = cosRZ*cosRY*_Xorg + -sinRZ*_Yorg + cosRZ*sinRY*_Zorg;
//    _Y = sinRZ*cosRY*_Xorg + cosRZ*_Yorg + sinRZ*sinRY*_Zorg;
//    _Z = -sinRY*_Xorg + cosRY*_Zorg;

    //�����d���̏Ǝˊp���L����悤�ȉ�]�iQuaternion�Ŏ����j
    static float vX_axis,vY_axis,vZ_axis; //��]�����������x�N�g��
    vX_axis = cosRY*cosRZ*_pMover->_vX + cosRY*-sinRZ*_pMover->_vY + sinRY*_pMover->_vZ;
    vY_axis = sinRZ*_pMover->_vX + cosRZ*_pMover->_vY;
    vZ_axis = -sinRY*cosRZ*_pMover->_vX + -sinRY*-sinRZ*_pMover->_vY + cosRY*_pMover->_vZ;

//    vX_axis = cosRZ*cosRY*_pMover->_vX + -sinRZ*_pMover->_vY + cosRZ*sinRY*_pMover->_vZ;
//    vY_axis = sinRZ*cosRY*_pMover->_vX +  cosRZ*_pMover->_vY + sinRZ*sinRY*_pMover->_vZ;
//    vZ_axis = -sinRY*_pMover->_vX + cosRY*_pMover->_vZ;

    static float sinHalf, cosHalf;
    sinHalf = GgafDx9Util::SIN[_angExpanse/ANGLE_RATE/2]; //_angExpanse=��]���������p�x
    cosHalf = GgafDx9Util::COS[_angExpanse/ANGLE_RATE/2];
    static float vx, vy, vz; //��]�������������x�N�g���i���̓_���W�j�B���ˏ�i�A�����ʏ�Ƃ͌���Ȃ��j�ɂȂ��Ă܂��B
    static float k;   //���K���{��
    vx = ((float)_X) / LEN_UNIT;
    vy = ((float)_Y) / LEN_UNIT;
    vz = ((float)_Z) / LEN_UNIT;
    k = 1.0 / GgafDx9Util::sqrt_fast(vx*vx + vy*vy + vz*vz);

    //�v�Z
    _Q.set( cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    _Q.mul(0, k*vx, k*vy, k*vz); //R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
    _Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //_Q._x, _Q._y, _Q._z ����]��̍��W�ƂȂ�
    //Z����]�AY����]�p�x���v�Z
    GgafDx9Util::getRotAngleZY(
        _Q._x,
        _Q._y,
        _Q._z,
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

    //TODO
    //�œK��


    _angExpanse = GgafDx9GeometryMover::simplifyAngle(_angExpanse+_angveloExpanse);

    if (VB::isBeingPressed(VB_SHOT2)) {
        MyLaserChip001* pLaserChip = (MyLaserChip001*)_pLaserChipDispatcher->employ();
        if (pLaserChip != NULL) {
            pLaserChip->_pMover->_vX = _Q._x;
            pLaserChip->_pMover->_vY = _Q._y;
            pLaserChip->_pMover->_vZ = _Q._z;
            pLaserChip->_pMover->_angRzMove = _RZ2;
            pLaserChip->_pMover->_angRyMove = _RY2;
            static angle angWk;
            if ((0 <= _RZ2 && _RZ2 < ANGLE90) ||
                (ANGLE270 <= _RZ2 && _RZ2 < ANGLE360) ) {
                angWk = 0;
            } else {
                angWk = ANGLE180;
            }
            pLaserChip->_pMover->_angRot[AXIS_X] = angWk;
            pLaserChip->_pMover->_angRot[AXIS_Z] = _RZ2;
            pLaserChip->_pMover->_angRot[AXIS_Y] = _RY2;
            pLaserChip->_pMover->behave();
            pLaserChip->_X = _X2;
            pLaserChip->_Y = _Y2;
            pLaserChip->_Z = _Z2;

        }
    }

}

void MyDummyOption::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyDummyOption::processOnHit(GgafActor* prm_pActor_Opponent) {
    adios();
}


MyDummyOption::~MyDummyOption() {
    _pSeCon_Laser->close();
    //DELETE_IMPOSSIBLE_NULL(_pRing);
}



