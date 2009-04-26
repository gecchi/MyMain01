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
    _angveloMove = 0;//旋廻移動角速度（読み出し専用）

    _angPosition = 0;     //円周上初期位置角度（周囲角）（上書き初期設定可）
    _radius = 150000;     //旋廻半径距離（上書き初期設定可）
    _veloMove = 5000;     //旋廻移動速度（上書き初期設定可）
    _angExpanse = 295000;      //オプションの広がり角の回転角（上書き初期設定可）
    _angveloExpanse = 00; //オプションの広がり角の角回転速度 （上書き初期設定可）

}

void MyDummyOption::initialize() {
    _angveloMove = ((1.0*_veloMove / _radius)*(double)ANGLE180)/PI;
    _pGeoMover->setMoveVelocity(_veloMove);
    _pGeoMover->setRzMoveAngle(_angPosition+ANGLE90);
    _pGeoMover->setRyMoveAngle(-ANGLE90);
    _pGeoMover->setRzMoveAngleVelocity(_angveloMove);//∵半径Ｒ＝速度Ｖ／角速度ω
    _pGeoMover->setRyMoveAngleVelocity(0);//∵半径Ｒ＝速度Ｖ／角速度ω
    _Z = GgafDx9Util::COS[_angPosition/ANGLE_RATE]*_radius; //X軸中心回転なのでXYではなくてZY
    _Y = GgafDx9Util::SIN[_angPosition/ANGLE_RATE]*_radius;
    _X = 50000; //TODO:本当は0（自機の真横）にしたい。しかしシンバルロックが起きやすくて、カクつきが目につく。解決できない。
                //やや中心からずらす事で、ある程度向きの遷移を滑らかにし、
                //さらにAXIS_X 軸回転を速めに設定し、気付かれないようにごまかす･･･妥協。
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

    _pLaserChipRotation = NEW LaserChipRotationActor("ROTLaser");

    MyLaserChip001* pChip;
    for (int i = 0; i < 32; i++) { //レーザーストック
        Sleep(2); //工場に気を使う。
        stringstream name;
        name <<  "MYS_LaserChip" << i;
        string name2 = name.str();
        pChip = NEW MyLaserChip001(name2.c_str());
        pChip->inactivateImmediately();
        _pLaserChipRotation->addLaserChip(pChip);
    }
    Sleep(1);


    GameGlobal::_pSceneCommon->getLordActor()->accept(KIND_MY_SHOT_GU, _pLaserChipRotation);

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


    //ここまでで、GgafDx9GeometryMoverの移動機能を使用し、
    //以下のような状態まで実現。
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
    //↓     (0,0,0)      (-50000, 0, _radius)
    //
    //
    //         ○→
    //          (-50000, -1*_radius, 0)
    //
    //しかしまだ色々回転が必要。あとは普通に計算（力技）で、座標回転、向き回転を行なう。
    //TODO:いつか汎用化最適化。


    static float sinRY, cosRY, sinRZ, cosRZ;

    sinRZ = GgafDx9Util::SIN[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Z] / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Z] / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y] / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y] / ANGLE_RATE];
    _X = cosRZ*cosRY*_Xorg + -sinRZ*_Yorg + cosRZ*sinRY*_Zorg;
    _Y = sinRZ*cosRY*_Xorg + cosRZ*_Yorg + sinRZ*sinRY*_Zorg;
    _Z = -sinRY*_Xorg + cosRY*_Zorg;

    //Quaternionで軸回転
    static float vX_axis,vY_axis,vZ_axis; //回転させたい軸ベクトル
    vX_axis = cosRZ*cosRY*_pGeoMover->_vX + -sinRZ*_pGeoMover->_vY + cosRZ*sinRY*_pGeoMover->_vZ;
    vY_axis = sinRZ*cosRY*_pGeoMover->_vX +  cosRZ*_pGeoMover->_vY + sinRZ*sinRY*_pGeoMover->_vZ;
    vZ_axis = -sinRY*_pGeoMover->_vX + cosRY*_pGeoMover->_vZ;

    static float sinHalf, cosHalf;
    sinHalf = GgafDx9Util::SIN[_angExpanse/ANGLE_RATE/2]; //_angExpanse=回転させたい角度
    cosHalf = GgafDx9Util::COS[_angExpanse/ANGLE_RATE/2];
    static double vx, vy, vz; //回転させたい方向ベクトル（元の点座標）。放射状になってます。
    static double k;   //正規化倍数
    vx = ((double)_X) / LEN_UNIT;
    vy = ((double)_Y) / LEN_UNIT;
    vz = ((double)_Z) / LEN_UNIT;
    k = 1 / GgafDx9Util::sqrt_fast(vx*vx + vy*vy + vz*vz);

    //計算
    GgafDx9Quaternion Q( cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    Q.mul(0, k*vx, k*vy, k*vz); //R*P
    Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //Q._x, Q._y, Q._z が回転後の座標となる
    //Z軸回転、Y軸回転角度を計算
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
        MyLaserChip001* pLaser = (MyLaserChip001*)_pLaserChipRotation->obtain();
        if (pLaser != NULL) {
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


