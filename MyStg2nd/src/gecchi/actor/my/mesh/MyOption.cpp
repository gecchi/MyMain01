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
    _angveloMove = 0;//旋廻移動角速度（読み出し専用）

    _angPosition = 0;     //円周上初期位置角度（周囲角）（上書き初期設定可）
    _radiusPosition = 150000;     //旋廻半径距離（上書き初期設定可）
    _veloMv = 5000;     //旋廻移動速度（上書き初期設定可）
    _angExpanse = 0;      //オプションの広がり角の回転角（上書き初期設定可）
    _angveloExpanse = 0; //オプションの広がり角の角回転速度 （上書き初期設定可）
    _angacceExpanse = 0;
    _pSeCon_Laser = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->connect("laser001");

    _pLaserChipDispatcher = NEW LaserChipDispatcher("ROTLaser");
    _pLaserChipDispatcher->_pSeConnection = _pSeCon_Laser;
    MyCurveLaserChip001* pChip;
    for (int i = 0; i < 90; i++) { //レーザーストック
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
    _pMover->setRzMvAngVelo(_angveloMove);//∵半径Ｒ＝速度Ｖ／角速度ω
    _pMover->setRyMvAngVelo(0);//∵半径Ｒ＝速度Ｖ／角速度ω
    _Z = GgafDx9Util::COS[_angPosition/ANGLE_RATE]*_radiusPosition; //X軸中心回転なのでXYではなくてZY
    _Y = GgafDx9Util::SIN[_angPosition/ANGLE_RATE]*_radiusPosition;
    _X = 0;
//_X = 50000; //TODO:＜メモ＞オプションをX軸付近を回転していると、 _angExpanse の値によってはシンバルロック付近で、
//                //急激な回転が目につく（目につきだすと止まらない）。解決を断念。オプションの回転を考え直す。
//                //解決するためには根本的に回転部分のライブラリ(GgafDx9GeometryMover)を作り直す必要アリ。時間があれば考えよう。後回し。
//                //TODO:2009/04/08
//                //本当は0（自機の真横）にしたい。が、やや自機の真横からずらす事で、シンバルロックによるワープのような回転する確率をやや緩和する。
//                //X軸回転角角速度を速めに設定し、くるくる速く回して気付かれないようにごまかす。↑と↓向き付近で急激な回転を起こす事は免れない。
    _pMover->setFaceAngVelo(AXIS_X, 8000);

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;
//    _RXorg = _RX;
//    _RYorg = _RY;
//    _RZorg = _RZ;

    GameGlobal::_pSceneCommon->getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pLaserChipDispatcher->extract());

}

void MyOption::processBehavior() {
//    /////////////モーフテスト(DefaultMorphMeshActor継承要)////////////////
//    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
//        _pMorpher->loopTriangleWave(1, 30, 3, 22);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
//        _pMorpher->stopImmediately(1);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
//        _pMorpher->intoTargetAcceStep(2, 1.0f, 0, 0.002f);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
//        _pMorpher->intoTargetAcceStep(2, 0, 0, -0.004f);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
//        _pMorpher->loopTriangleWave(3, 20, 13, 2);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
//        _pMorpher->stopImmediately(3);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
//        _pMorpher->loopTriangleWave(4, 60, 3, 20);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
//        _pMorpher->stopImmediately(4);
//    }
//    _pMorpher->behave();
//    /////////////モーフテスト////////////////

    if (VB::isDoublePushedDown(VB_OPTION, 6, 6)) {
        _TRACE_("isDoublePushedDown");
        _is_flapping = true;
        _iflappingSeq = 0;
        _angveloExpanse = 100;
        _angacceExpanse = 100;
        _range_angveloExpanse = 3000;
    } else if (_is_flapping && VB::isPushedDown(VB_OPTION)) {
        _is_flapping = false;
    }
    if (_is_flapping) {
        if (_iflappingSeq == 0) {
            if (ANGLE225 < _angExpanse && _angExpanse <= ANGLE270) {
                _iflappingSeq = 1;
                _angveloExpanse = -_angveloExpanse;
                _angacceExpanse = -_angacceExpanse;
            }
        } else if (_iflappingSeq == 1) {
            if (ANGLE270 <_angExpanse && _angExpanse < ANGLE315) {
                _iflappingSeq = 0;
                _angveloExpanse = -_angveloExpanse;
                _angacceExpanse = -_angacceExpanse;
            }
        }
        _angveloExpanse += _angacceExpanse;
        if (_angveloExpanse >= _range_angveloExpanse) {
            _angveloExpanse = _range_angveloExpanse;
        } else if (_angveloExpanse <= -_range_angveloExpanse) {
            _angveloExpanse = -_range_angveloExpanse;
        }
        _angExpanse = GgafDx9GeometryMover::simplifyAng(_angExpanse+_angveloExpanse);

    }

    _X = _Xorg;
    _Y = _Yorg;
    _Z = _Zorg;
//    _RX = _RXorg;
//    _RY = _RYorg;
//    _RZ = _RZorg;

    _pMover->setMvVelo(_veloMv);
    _pMover->behave();

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;
//    _RXorg = _RX;
//    _RYorg = _RY;
//    _RZorg = _RZ;

    //＜メモ＞
    //ここまでで、GgafDx9GeometryMoverのメソッドのみで、
    //以下のような状態までもっていく。
    //(100,0,0) から原点を見たイメージ、自は原点
    //↑y軸  →z軸  ・x軸
    //
    //
    //              YZ平面に平行でぐるぐる回ってる。
    //        ←○
    //
    //
    //                    ↑
    //○        自        ○
    //↓     (0,0,0)      (-50000, 0, _radiusPosition)
    //
    //
    //          ○→
    //          (-50000, -1*_radiusPosition, 0)
    //
    //しかしまだ色々と回転したいため。あとは普通に計算（力技）で、座標回転、向き回転を行なう。
    //ダミーのアクターを連結しようとしたがいろいろ難しい、Quaternion を使わざるを得ない（のではないか；）。
    //TODO:最適化すべし、処理が重たい。いつか汎用化

    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;

    //sinRX = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angFace[AXIS_X] / ANGLE_RATE];
    //cosRX = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angFace[AXIS_X] / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angFace[AXIS_Z] / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angFace[AXIS_Z] / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angFace[AXIS_Y] / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angFace[AXIS_Y] / ANGLE_RATE];
    //自機を中心にWORLD変換のような旋廻

//_TRACE_("MyOption -----");
//_TRACE_("MyOption ParentFaceRzRy = "<<(_pMyOptionParent->_pMover->_angFace[AXIS_Z])<<" > "<<(_pMyOptionParent->_pMover->_angFace[AXIS_Y]));

    //if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
        //Y軸回転 ＞ Z軸回転
        _X = cosRY*cosRZ*_Xorg + cosRY*-sinRZ*_Yorg + sinRY*_Zorg;
        _Y = sinRZ*_Xorg + cosRZ*_Yorg;
        _Z = -sinRY*cosRZ*_Xorg + -sinRY*-sinRZ*_Yorg + cosRY*_Zorg;
    //} else {
    //	//Z軸回転 ＞ Y軸回転
    //	_X = cosRZ*cosRY*_Xorg + -sinRZ*_Yorg + cosRZ*sinRY*_Zorg;
    //	_Y = sinRZ*cosRY*_Xorg + cosRZ*_Yorg + sinRZ*sinRY*_Zorg;
    //	_Z = -sinRY*_Xorg + cosRY*_Zorg;
    //}



    //懐中電灯の照射角が広がるような回転（Quaternionで実現）
    static float vX_axis,vY_axis,vZ_axis; //回転させたい軸ベクトル
//_TRACE_("_pMover->_angFace[AXIS_Z],_pMover->_angFace[AXIS_Y]="<<(_pMover->_angFace[AXIS_Z])<<","<<(_pMover->_angFace[AXIS_Y]));
//    angle zz = _pMyOptionParent->_pMover->_angFace[AXIS_Z] + _pMover->_angRzMv;
//    angle yy = _pMyOptionParent->_pMover->_angFace[AXIS_Y] + _pMover->_angRyMv;
//    GgafDx9Util::getNormalizeVectorZY(GgafDx9GeometryMover::simplifyAng(zz),
//                                      GgafDx9GeometryMover::simplifyAng(yy),
//                                      vX_axis,
//                                      vY_axis,
//                                      vZ_axis);


    //if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
        vX_axis = cosRY*cosRZ*_pMover->_vX + cosRY*-sinRZ*_pMover->_vY + sinRY*_pMover->_vZ;
        vY_axis = sinRZ*_pMover->_vX + cosRZ*_pMover->_vY;
        vZ_axis = -sinRY*cosRZ*_pMover->_vX + -sinRY*-sinRZ*_pMover->_vY + cosRY*_pMover->_vZ;
    //} else {
    //	vX_axis = cosRZ*cosRY*_pMover->_vX + -sinRZ*_pMover->_vY + cosRZ*sinRY*_pMover->_vZ;
    //	vY_axis = sinRZ*cosRY*_pMover->_vX +  cosRZ*_pMover->_vY + sinRZ*sinRY*_pMover->_vZ;
    //	vZ_axis = -sinRY*_pMover->_vX + cosRY*_pMover->_vZ;
    //}
    static float sinHalf, cosHalf;
    sinHalf = GgafDx9Util::SIN[_angExpanse/ANGLE_RATE/2]; //_angExpanse=回転させたい角度
    cosHalf = GgafDx9Util::COS[_angExpanse/ANGLE_RATE/2];

    //計算
    _Q.set( cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    _Q.mul(0,
           _pMyOptionParent->_pMover->_vX,
           _pMyOptionParent->_pMover->_vY,
           _pMyOptionParent->_pMover->_vZ); //R*P 回転軸が現在の進行方向ベクトルとなる
    _Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //_Q._x, _Q._y, _Q._z が回転後の座標となる
    //Z軸回転、Y軸回転角度を計算

//_TRACE_("MyOption Q vX,vY,vZ="<<_Q._x<<","<<_Q._y<<","<<_Q._z);

    GgafDx9Util::getRzRyAng(
        (float)_Q._x,
        (float)_Q._y,
        (float)_Q._z,
        _RZ,
        _RY
     );

//_TRACE_("MyOption Q RzRy="<<_RZ<<" > "<<_RY);


    _RZ = GgafDx9GeometryMover::simplifyAng(_RZ);
    _RY = GgafDx9GeometryMover::simplifyAng(_RY);
    //GgafDx9Util::anotherRzRy(_RZ,_RY);

//_TRACE_("MyOption SAIGO RzRy="<<_RZ<<" > "<<_RY);
    _X += GameGlobal::_pMyShip->_X;
    _Y += GameGlobal::_pMyShip->_Y;
    _Z += GameGlobal::_pMyShip->_Z;

    //TODO
    //最適化
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
        if (_pLockOnTarget->isOffscreen() || _pLockOnTarget->isActive() == false) {
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



