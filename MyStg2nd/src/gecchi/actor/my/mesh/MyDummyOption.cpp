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

    int v = 1000;
    _angvelo = ((1.0*v / _distR)*(double)ANGLE180)/PI;
    _pGeoMover->setMoveVelocity(v);
    _pGeoMover->setRzMoveAngle(_angPosRotX+ANGLE90);
    _pGeoMover->setRyMoveAngle(-ANGLE90);
    _pGeoMover->setRzMoveAngleVelocity(_angvelo);//∵半径Ｒ＝速度Ｖ／角速度ω
    _pGeoMover->setRyMoveAngleVelocity(0);//∵半径Ｒ＝速度Ｖ／角速度ω
    //_pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_Flg = true;
    //_pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_Flg = true; //RYは使っては駄目。変換行列がRxRyRzだから

    _Z = GgafDx9Util::COS[_angPosRotX/ANGLE_RATE]*_distR; //X軸中心回転なのでXYではなくてZY
    _Y = GgafDx9Util::SIN[_angPosRotX/ANGLE_RATE]*_distR;

    _X = 20000; //TODO:本当は0（時機の真横）にしたい。しかしシンバルロックが起き、見た目ひどい。解決できない。
                //やや中心からずらす事で、ある程度向きの遷移を滑らかにし、
                //さらにAXIS_X 軸回転を速めに設定し、気付かれないようにごまかす･･･妥協。

    _pGeoMover->setRotAngleVelocity(AXIS_X, 5000);


    _angExpanse = 0;

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


    //ここまでで、GgafDx9GeometryMoverの移動機能を使用し、
    //以下のような状態まで実現。
    //
    //              YZ平面に平行でぐるぐる回ってる。
    //       ←○
    //
    //
    //                    ↑
    //○        自        ○
    //↓     (0,0,0)      (-20000, 0, _distR)
    //
    //
    //         ○→
    //
    //(100,0,0) から原点を見たイメージ、自は原点
    //↑y軸  →z軸  ・x軸
    //
    //しかしまだ色々回転が必要。あとは普通に計算（力技）で、座標回転、向き回転を行なう。
    //TODO:いつか汎用化最適化。


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

    //Quaternionで軸回転
    static float vX_axis,vY_axis,vZ_axis; //回転させたい軸ベクトル
    vX_axis = cosRZ*cosRY*_pGeoMover->_vX + -sinRZ*_pGeoMover->_vY + cosRZ*sinRY*_pGeoMover->_vZ;
    vY_axis = sinRZ*cosRY*_pGeoMover->_vX +  cosRZ*_pGeoMover->_vY + sinRZ*sinRY*_pGeoMover->_vZ;
    vZ_axis = -sinRY*_pGeoMover->_vX + cosRY*_pGeoMover->_vZ;
//        GgafDx9Util::getRotAngleZY(
//                vX_axis,
//                vY_axis,
//                vZ_axis,
//                _RZ,
//                _RY
//             );
//
//     _RZ = GgafDx9GeometryMover::simplifyAngle(_RZ);
//     _RY = GgafDx9GeometryMover::simplifyAngle(_RY);
//	 _TRACE_("_RZ,_RY="<<_RZ<<","<<_RY);


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
    //_TRACE_("_RZ,_RY="<<_RZ<<","<<_RY);
    _RZ = GgafDx9GeometryMover::simplifyAngle(_RZ);
    _RY = GgafDx9GeometryMover::simplifyAngle(_RY);

    _angExpanse = GgafDx9GeometryMover::simplifyAngle(_angExpanse+50);


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


