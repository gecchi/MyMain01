#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

//MyOption::MyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent) : DefaultMorphMeshActor(prm_name, "4/Ceres") {
MyOption::MyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent) : DefaultMeshSetActor(prm_name, "myvic") {

_TRACE_("MyOption::MyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyOption";
    _pMyOptionParent = prm_pMyOptionParent;
    _no = prm_no;
    _angveloMove = 0;//����ړ��p���x�i�ǂݏo����p�j

    _angPosition = 0;     //�~���㏉���ʒu�p�x�i���͊p�j�i�㏑�������ݒ�j
    _radiusPosition = 150000;     //�������a�����i�㏑�������ݒ�j
    _veloMv = 5000;     //����ړ����x�i�㏑�������ݒ�j
    _angExpanse = 0;      //�I�v�V�����̍L����p�̉�]�p�i�㏑�������ݒ�j
    _angveloExpanse = 0; //�I�v�V�����̍L����p�̊p��]���x �i�㏑�������ݒ�j
    _angacceExpanse = 0;
    _pSeCon_Laser = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->connect("laser001");

    _pLaserChipDispatcher = NEW LaserChipDispatcher("ROTLaser");
    _pLaserChipDispatcher->_pSeConnection = _pSeCon_Laser;
    MyCurveLaserChip001* pChip;
    for (int i = 0; i < 90; i++) { //���[�U�[�X�g�b�N
        stringstream name;
        name <<  getName() << "'s MYS_LaserChip" << i;
        string name2 = name.str();
        pChip = NEW MyCurveLaserChip001(name2.c_str());
//        pChip->setSource(this);
//        pChip->_pSource_vX = &_Q._x;
//        pChip->_pSource_vY = &_Q._y;
//        pChip->_pSource_vZ = &_Q._z;
        pChip->inactivateImmediately();
        _pLaserChipDispatcher->addSubLast(pChip);
    }
    addSubLast(_pLaserChipDispatcher);

    _pEffectLockOn = NEW EffectLockOn001("EffectLockOn001");
    addSubGroup(_pEffectLockOn);
    _pEffectLockOn_Release = NEW EffectLockOn001_Release("EffectLockOn001_R", _pEffectLockOn);
    addSubGroup(_pEffectLockOn_Release);

    _is_flapping = false;
    _pLockOnTarget = NULL;
}

void MyOption::initialize() {
    _angveloMove = ((1.0f*_veloMv / _radiusPosition)*(float)ANGLE180)/PI;
    _pMover->setMvVelo(_veloMv);
    _pMover->setRzMvAng(_angPosition+ANGLE90);
    _pMover->setRyMvAng(-ANGLE90);
    _pMover->setRzMvAngVelo(_angveloMove);//�攼�a�q�����x�u�^�p���x��
    _pMover->setRyMvAngVelo(0);//�攼�a�q�����x�u�^�p���x��
    _Z = GgafDx9Util::COS[_angPosition/ANGLE_RATE]*_radiusPosition; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
    _Y = GgafDx9Util::SIN[_angPosition/ANGLE_RATE]*_radiusPosition;
    _X = 0;
//_X = 50000; //TODO:���������I�v�V������X���t�߂���]���Ă���ƁA _angExpanse �̒l�ɂ���Ă̓V���o�����b�N�t�߂ŁA
//                //�}���ȉ�]���ڂɂ��i�ڂɂ������Ǝ~�܂�Ȃ��j�B������f�O�B�I�v�V�����̉�]���l�������B
//                //�������邽�߂ɂ͍��{�I�ɉ�]�����̃��C�u����(GgafDx9GeometryMover)����蒼���K�v�A���B���Ԃ�����΍l���悤�B��񂵁B
//                //TODO:2009/04/08
//                //�{����0�i���@�̐^���j�ɂ������B���A��⎩�@�̐^�����炸�炷���ŁA�V���o�����b�N�ɂ�郏�[�v�̂悤�ȉ�]����m�������ɘa����B
//                //X����]�p�p���x�𑬂߂ɐݒ肵�A���邭�鑬���񂵂ċC�t����Ȃ��悤�ɂ��܂����B���Ɓ������t�߂ŋ}���ȉ�]���N�������͖Ƃ�Ȃ��B
    _pMover->setFaceAngVelo(AXIS_X, 8000);

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;
//    _RXorg = _RX;
//    _RYorg = _RY;
//    _RZorg = _RZ;

    GameGlobal::_pSceneCommon->getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pLaserChipDispatcher->extract());

}


void MyOption::addRadiusPosition(int prm_len) {
    _radiusPosition += prm_len;
    angle angZY_ROTANG_X = MyStgUtil::getAngle2D(-_Z, _Y); //�����̈ʒu
    //rz����P�ʕ����x�N�g��
    float vx,vy,vz;
    vx = 0;
    vy = GgafDx9Util::SIN[GgafDx9GeometryMover::simplifyAng(angZY_ROTANG_X)/ANGLE_RATE];
    vz = -GgafDx9Util::COS[GgafDx9GeometryMover::simplifyAng(angZY_ROTANG_X)/ANGLE_RATE];
    _Z = _radiusPosition * vz;
    _Y = _radiusPosition * vy;

    _pMover->setRzMvAng(angZY_ROTANG_X + ANGLE90);
//    _pMover->setRyMvAng(-ANGLE90);
//    _angveloMove = ((1.0f*_veloMv / _radiusPosition)*(float)ANGLE180)/PI;
}

void MyOption::processBehavior() {

    _X = _Xorg;
    _Y = _Yorg;
    _Z = _Zorg;

    //_radiusPosition += 100;
    addRadiusPosition(0);


    _pMover->setMvVelo(_veloMv);
    _pMover->behave();


    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;

    //��������
    //�����܂łŁAGgafDx9GeometryMover�̃��\�b�h�݂̂ŁA
    //�ȉ��̂悤�ȏ�Ԃ܂ł����Ă����B
    //(100,0,0) ���猴�_�������C���[�W�A���͌��_
    //��y��  ��z��  �Ex��
    //
    //
    //              YZ���ʂɕ��s�ł��邮�����Ă�B
    //        ����
    //
    //
    //                    ��
    //��        ��        ��
    //��     (0,0,0)      (-50000, 0, _radiusPosition)
    //
    //
    //          ����
    //          (-50000, -1*_radiusPosition, 0)
    //
    //�������܂��F�X�Ɖ�]���������߁B���Ƃ͕��ʂɌv�Z�i�͋Z�j�ŁA���W��]�A������]���s�Ȃ��B
    //�_�~�[�̃A�N�^�[��A�����悤�Ƃ��������낢�����AQuaternion ���g�킴��𓾂Ȃ��i�̂ł͂Ȃ����G�j�B
    //TODO:�œK�����ׂ��A�������d�����B�����ėp��

//    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
//
//    //sinRX = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angFace[AXIS_X] / ANGLE_RATE];
//    //cosRX = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angFace[AXIS_X] / ANGLE_RATE];
//    sinRZ = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angFace[AXIS_Z] / ANGLE_RATE];
//    cosRZ = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angFace[AXIS_Z] / ANGLE_RATE];
//    sinRY = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angFace[AXIS_Y] / ANGLE_RATE];
//    cosRY = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angFace[AXIS_Y] / ANGLE_RATE];
//    //���@�𒆐S��WORLD�ϊ��̂悤�Ȑ���
//
////_TRACE_("MyOption -----");
////_TRACE_("MyOption ParentFaceRzRy = "<<(_pMyOptionParent->_pMover->_angFace[AXIS_Z])<<" > "<<(_pMyOptionParent->_pMover->_angFace[AXIS_Y]));
//
//    //if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
//        //Y����] �� Z����]
//        _X = cosRY*cosRZ*_Xorg + cosRY*-sinRZ*_Yorg + sinRY*_Zorg;
//        _Y = sinRZ*_Xorg + cosRZ*_Yorg;
//        _Z = -sinRY*cosRZ*_Xorg + -sinRY*-sinRZ*_Yorg + cosRY*_Zorg;
//    //} else {
//    //	//Z����] �� Y����]
//    //	_X = cosRZ*cosRY*_Xorg + -sinRZ*_Yorg + cosRZ*sinRY*_Zorg;
//    //	_Y = sinRZ*cosRY*_Xorg + cosRZ*_Yorg + sinRZ*sinRY*_Zorg;
//    //	_Z = -sinRY*_Xorg + cosRY*_Zorg;
//    //}
//
//
//
//    //�����d���̏Ǝˊp���L����悤�ȉ�]�iQuaternion�Ŏ����j
//    static float vX_axis,vY_axis,vZ_axis; //��]�����������x�N�g��
////_TRACE_("_pMover->_angFace[AXIS_Z],_pMover->_angFace[AXIS_Y]="<<(_pMover->_angFace[AXIS_Z])<<","<<(_pMover->_angFace[AXIS_Y]));
////    angle zz = _pMyOptionParent->_pMover->_angFace[AXIS_Z] + _pMover->_angRzMv;
////    angle yy = _pMyOptionParent->_pMover->_angFace[AXIS_Y] + _pMover->_angRyMv;
////    GgafDx9Util::getNormalizeVectorZY(GgafDx9GeometryMover::simplifyAng(zz),
////                                      GgafDx9GeometryMover::simplifyAng(yy),
////                                      vX_axis,
////                                      vY_axis,
////                                      vZ_axis);
//
//
//    //if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
//        vX_axis = cosRY*cosRZ*_pMover->_vX + cosRY*-sinRZ*_pMover->_vY + sinRY*_pMover->_vZ;
//        vY_axis = sinRZ*_pMover->_vX + cosRZ*_pMover->_vY;
//        vZ_axis = -sinRY*cosRZ*_pMover->_vX + -sinRY*-sinRZ*_pMover->_vY + cosRY*_pMover->_vZ;
//    //} else {
//    //	vX_axis = cosRZ*cosRY*_pMover->_vX + -sinRZ*_pMover->_vY + cosRZ*sinRY*_pMover->_vZ;
//    //	vY_axis = sinRZ*cosRY*_pMover->_vX +  cosRZ*_pMover->_vY + sinRZ*sinRY*_pMover->_vZ;
//    //	vZ_axis = -sinRY*_pMover->_vX + cosRY*_pMover->_vZ;
//    //}
//    static float sinHalf, cosHalf;
//    sinHalf = GgafDx9Util::SIN[_angExpanse/ANGLE_RATE/2]; //_angExpanse=��]���������p�x
//    cosHalf = GgafDx9Util::COS[_angExpanse/ANGLE_RATE/2];
//
//    //�v�Z
//    _Q.set( cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
//    _Q.mul(0,
//           _pMyOptionParent->_pMover->_vX,
//           _pMyOptionParent->_pMover->_vY,
//           _pMyOptionParent->_pMover->_vZ); //R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
//    _Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
//    //_Q._x, _Q._y, _Q._z ����]��̍��W�ƂȂ�
//    //Z����]�AY����]�p�x���v�Z
//
////_TRACE_("MyOption Q vX,vY,vZ="<<_Q._x<<","<<_Q._y<<","<<_Q._z);
//
//    GgafDx9Util::getRzRyAng(
//        (float)_Q._x,
//        (float)_Q._y,
//        (float)_Q._z,
//        _RZ,
//        _RY
//     );
//
////_TRACE_("MyOption Q RzRy="<<_RZ<<" > "<<_RY);
//
//
//    _RZ = GgafDx9GeometryMover::simplifyAng(_RZ);
//    _RY = GgafDx9GeometryMover::simplifyAng(_RY);
//    //GgafDx9Util::anotherRzRy(_RZ,_RY);
//
////_TRACE_("MyOption SAIGO RzRy="<<_RZ<<" > "<<_RY);
//    _X += _pMyOptionParent->_X;
//    _Y += _pMyOptionParent->_Y;
//    _Z += _pMyOptionParent->_Z;

    //TODO
    //�œK��
    _pMover->setVxMvVelo(0);
    _pMover->setVyMvVelo(0);
    _pMover->setVzMvVelo(0);



    if (VB::isBeingPressed(VB_SHOT2)) {
        MyCurveLaserChip001* pLaserChip = (MyCurveLaserChip001*)_pLaserChipDispatcher->employ();
        if (pLaserChip != NULL) {
            pLaserChip->_pMover->_vX = _Q._x;
            pLaserChip->_pMover->_vY = _Q._y;
            pLaserChip->_pMover->_vZ = _Q._z;
            pLaserChip->_pMover->_angRzMv = _RZ;
            pLaserChip->_pMover->_angRyMv = _RY;
//            pLaserChip->_pMover->_angFace[AXIS_X] = angWk;
            pLaserChip->_pMover->_angFace[AXIS_Z] = _RZ;
            pLaserChip->_pMover->_angFace[AXIS_Y] = _RY;
            pLaserChip->_pMover->setVxMvVelo(_Q._x*150000);
            pLaserChip->_pMover->setVyMvVelo(_Q._y*150000);
            pLaserChip->_pMover->setVzMvVelo(_Q._z*150000);
            pLaserChip->_pMover->setVxMvAcce(0);
            pLaserChip->_pMover->setVyMvAcce(0);
            pLaserChip->_pMover->setVzMvAcce(0);
            pLaserChip->_pMover->behave();
            pLaserChip->_X = _X;
            pLaserChip->_Y = _Y;
            pLaserChip->_Z = _Z;
            pLaserChip->_pOrg = this;
            pLaserChip->activate();
        }
    } else {
        _pLockOnTarget = NULL;
    }



    if (_pLockOnTarget) {
        //if (_pLockOnTarget->isOffscreen() || _pLockOnTarget->isActive() == false) { //��A�N�e�B�u�݂̂Ǝ���O�̓��b�N�I������
        if (_pLockOnTarget->isActive() == false) {  //��A�N�e�B�u�̂݉����i����O�ł����b�N�I���ێ��j
            _pLockOnTarget = NULL;
        } else {
            _pEffectLockOn->setGeometry(_pLockOnTarget);
            _pEffectLockOn->activate();
        }

    } else {
        if (_pEffectLockOn->isActive()) {
            _pEffectLockOn_Release->setGeometry(_pEffectLockOn);
            _pEffectLockOn_Release->activate();
        }
       _pEffectLockOn->inactivate();
    }

}

void MyOption::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyOption::onHit(GgafActor* prm_pOtherActor) {
    sayonara();
}


MyOption::~MyOption() {
    _pSeCon_Laser->close();
    //DELETE_IMPOSSIBLE_NULL(_pRing);
}



