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
    _angveloMove = 0;//旋廻移動角速度（読み出し専用）

    _angPosition = 0;     //円周上初期位置角度（周囲角）（上書き初期設定可）
    _radiusPosition = 150000;     //旋廻半径距離（上書き初期設定可）
    _veloMove = 5000;     //旋廻移動速度（上書き初期設定可）
    _angExpanse = 290000;      //オプションの広がり角の回転角（上書き初期設定可）
    _angveloExpanse = 0; //オプションの広がり角の角回転速度 （上書き初期設定可）
    _pSeCon_Laser = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->connect("laser001");

    _pLaserChipDispatcher = NEW LaserChipDispatcher("ROTLaser");
    _pLaserChipDispatcher->_pSeConnection = _pSeCon_Laser;
    MyLaserChip001* pChip;
    for (int i = 0; i < 50; i++) { //レーザーストック
        Sleep(2); //工場に気を使う。
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
    addSubLast(_pLaserChipDispatcher); //仮サブ

}

void MyDummyOption::initialize() {
    _angveloMove = ((1.0*_veloMove / _radiusPosition)*(double)ANGLE180)/PI;
    _pMover->setMoveVelocity(_veloMove);
    _pMover->setRzMoveAngle(_angPosition+ANGLE90);
    _pMover->setRyMoveAngle(-ANGLE90);
    _pMover->setRzMoveAngleVelocity(_angveloMove);//∵半径Ｒ＝速度Ｖ／角速度ω
    _pMover->setRyMoveAngleVelocity(0);//∵半径Ｒ＝速度Ｖ／角速度ω
    _Z = GgafDx9Util::COS[_angPosition/ANGLE_RATE]*_radiusPosition; //X軸中心回転なのでXYではなくてZY
    _Y = GgafDx9Util::SIN[_angPosition/ANGLE_RATE]*_radiusPosition;
    _X = 0;
//_X = 50000; //TODO:＜メモ＞オプションをX軸回転していると、 _angExpanse の値によってはシンバルロックが起きて、
//                //カクつきが目につく（目につきだすと止まらない）。解決を断念。オプションの回転を考え直す。
//                //解決するためには根本的に回転部分のライブラリ(GgafDx9GeometryMover)を作り直す必要アリ。時間があれば考えよ。後回し。
//                //TODO:2009/04/08
//                //本当は0（自機の真横）にしたい。が、やや自機の真横からずらす事で、シンバルロックによるワープのような回転する確率をやや緩和する。
//                //X軸回転角角速度を速めに設定し、くるくる速く回して気付かれないようにごまかす。↑と↓向き付近で急激な回転を起こす事は免れない。
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
    /////////////モーフテスト(DefaultMorphMeshActor継承要)////////////////
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
    /////////////モーフテスト////////////////

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

    //＜メモ＞
    //ここまでで、GgafDx9GeometryMoverのメソッドのみで、
    //以下のような状態までもっていく。
    //(100,0,0) から原点を見たイメージ、自は原点
    //↑y軸  →z軸  ・x軸
    //
    //
    //              YZ平面に平行でぐるぐる回ってる。
    //       ←○
    //
    //
    //                    ↑
    //○        自        ○
    //↓     (0,0,0)      (-50000, 0, _radiusPosition)
    //
    //
    //         ○→
    //          (-50000, -1*_radiusPosition, 0)
    //
    //しかしまだ色々と回転したいため。あとは普通に計算（力技）で、座標回転、向き回転を行なう。
    //ダミーのアクターを連結しようとしたがいろいろ難しい、Quaternion を使わざるを得ない（のではないか；）。
    //TODO:最適化すべし、処理が重たい。いつか汎用化

    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;

    sinRX = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angRot[AXIS_X] / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angRot[AXIS_X] / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angRot[AXIS_Z] / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angRot[AXIS_Z] / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angRot[AXIS_Y] / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angRot[AXIS_Y] / ANGLE_RATE];
    //自機を中心にVIEW変換のような旋廻
    //_TRACE_(_pMyOptionParent->_pMover->_angRot[AXIS_Z]<<" "<<_pMyOptionParent->_pMover->_angRot[AXIS_Y]);

    //Y軸回転 ＞ Z軸回転
    _X = cosRY*cosRZ*_Xorg + cosRY*-sinRZ*_Yorg + sinRY*_Zorg;
    _Y = sinRZ*_Xorg + cosRZ*_Yorg;
    _Z = -sinRY*cosRZ*_Xorg + -sinRY*-sinRZ*_Yorg + cosRY*_Zorg;

//    Z軸回転 ＞ Y軸回転
//    _X = cosRZ*cosRY*_Xorg + -sinRZ*_Yorg + cosRZ*sinRY*_Zorg;
//    _Y = sinRZ*cosRY*_Xorg + cosRZ*_Yorg + sinRZ*sinRY*_Zorg;
//    _Z = -sinRY*_Xorg + cosRY*_Zorg;

    //懐中電灯の照射角が広がるような回転（Quaternionで実現）
    static float vX_axis,vY_axis,vZ_axis; //回転させたい軸ベクトル
    vX_axis = cosRY*cosRZ*_pMover->_vX + cosRY*-sinRZ*_pMover->_vY + sinRY*_pMover->_vZ;
    vY_axis = sinRZ*_pMover->_vX + cosRZ*_pMover->_vY;
    vZ_axis = -sinRY*cosRZ*_pMover->_vX + -sinRY*-sinRZ*_pMover->_vY + cosRY*_pMover->_vZ;

//    vX_axis = cosRZ*cosRY*_pMover->_vX + -sinRZ*_pMover->_vY + cosRZ*sinRY*_pMover->_vZ;
//    vY_axis = sinRZ*cosRY*_pMover->_vX +  cosRZ*_pMover->_vY + sinRZ*sinRY*_pMover->_vZ;
//    vZ_axis = -sinRY*_pMover->_vX + cosRY*_pMover->_vZ;

    static float sinHalf, cosHalf;
    sinHalf = GgafDx9Util::SIN[_angExpanse/ANGLE_RATE/2]; //_angExpanse=回転させたい角度
    cosHalf = GgafDx9Util::COS[_angExpanse/ANGLE_RATE/2];
    static float vx, vy, vz; //回転させたい方向ベクトル（元の点座標）。放射状（但し平面状とは限らない）になってます。
    static float k;   //正規化倍数
    vx = ((float)_X) / LEN_UNIT;
    vy = ((float)_Y) / LEN_UNIT;
    vz = ((float)_Z) / LEN_UNIT;
    k = 1.0 / GgafDx9Util::sqrt_fast(vx*vx + vy*vy + vz*vz);

    //計算
    _Q.set( cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    _Q.mul(0, k*vx, k*vy, k*vz); //R*P 回転軸が現在の進行方向ベクトルとなる
    _Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //_Q._x, _Q._y, _Q._z が回転後の座標となる
    //Z軸回転、Y軸回転角度を計算
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
    //最適化


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



