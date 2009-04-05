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

    _Z = GgafDx9Util::COS[_angPosRotX/ANGLE_RATE]*_distR; //X軸中心回転なのでXYではなくてZY
    _Y = GgafDx9Util::SIN[_angPosRotX/ANGLE_RATE]*_distR;

    //_pGeoMover->addRotAngle(AXIS_Z, -ANGLE90);

    //あとで使おう
//    _pGeoMover->setRotAngleAcceleration(AXIS_Z, 4000);



    //_pGeoMover->setRotAngleAcceleration(AXIS_Y, 4000);//2回目のX軸回転




//    //ともかくここでちゃんとX軸回転（Rx）をするしかない。
//    //getNormalizeVectorXY とか作るしかないか！
//    _pGeoMover->setRzMoveAngle(GgafDx9Util::COS[_angPosRotX/ANGLE_RATE]*ANGLE90);
//    _pGeoMover->setRyMoveAngle(GgafDx9Util::SIN[_angPosRotX/ANGLE_RATE]*ANGLE90);
////    _pGeoMover->setRzMoveAngleVelocity(GgafDx9Util::COS[_angPosRotX/ANGLE_RATE]*_angvelo);//∵半径Ｒ＝速度Ｖ／角速度ω
////    _pGeoMover->setRyMoveAngleVelocity(GgafDx9Util::SIN[_angPosRotX/ANGLE_RATE]*_angvelo);//∵半径Ｒ＝速度Ｖ／角速度ω
//    //_pGeoMover->setRyMoveAngle(-ANGLE90);//Rz円運動しているモノをX軸中心回転に変換
//    _Z += GgafDx9Util::COS[_angPosRotX/ANGLE_RATE]*_distR; //X軸中心回転なのでXYではなくてZY
//    _Y += GgafDx9Util::SIN[_angPosRotX/ANGLE_RATE]*_distR;
//
//    _sangvelo = 0;
//    _Xorg = _X;
//    _Yorg = _Y;
//    _Zorg = _Z;
//
//
//    _X_ParentPrev = _pMyOptionParent->_X;
//    _Y_ParentPrev = _pMyOptionParent->_Y;
//    _Z_ParentPrev = _pMyOptionParent->_Z;

}

void MyDummyOption::processBehavior() {
    //_angExpanse = GgafDx9GeometryMover::simplifyAngle(_angExpanse + 2000);
    _pGeoMover->addRotAngle(AXIS_Y, 2000);
    _pGeoMover->behave();
//    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
//    sinRY = GgafDx9Util::SIN[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y] / ANGLE_RATE];
//    cosRY = GgafDx9Util::COS[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y] / ANGLE_RATE];
//    sinRZ = GgafDx9Util::SIN[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Z] / ANGLE_RATE];
//    cosRZ = GgafDx9Util::COS[_pMyOptionParent->_pGeoMover->_angRot[AXIS_Z] / ANGLE_RATE];
//    _Xorg = _X;
//    _Yorg = _Y;
//    _Zorg = _Z;
//
//    _X = cosRZ*cosRY*_Xorg + -sinRZ*_Yorg + cosRZ*sinRY*_Zorg;
//    _Y = sinRZ*cosRY*_Xorg + cosRZ*_Yorg + sinRZ*sinRY*_Zorg;
//    _Z = -sinRY*_Xorg + cosRY*_Zorg;

}
////あとで使おう
////    _pGeoMover->_angveloRot[AXIS_Z] = _pGeoMover->simplifyAngle(_pGeoMover->_angveloRot[AXIS_Z]);
// //  _pGeoMover->addRotAngle(AXIS_Z, -ANGLE90);
//
//
//
//  // _pGeoMover->_angveloRot[AXIS_Y] = _pGeoMover->simplifyAngle(_pGeoMover->_angveloRot[AXIS_Y]);
//
////    setRotAngle(AXIS_X, _pGeoMover->_angRxMove);
////    setRotAngle(AXIS_Y, _pGeoMover->_angRyMove);
////    setRotAngle(AXIS_Z, _pGeoMover->_angRzMove);
////    _pGeoMover->setRotAngle(AXIS_X,_pGeoMover->_angRxMove);
//
//
//    //_pGeoMover->addRotAngle(AXIS_X, 10000);
//    //_pGeoMover->addRotAngle(AXIS_Y, 1000);
////    _pGeoMover->addRotAngle(AXIS_Z, -ANGLE90);
//
//
//
////    _angExpanse = GgafDx9GeometryMover::simplifyAngle(_angExpanse + 2000);
//
//
//
//
////
////    _pGeoMover->setAutoTargetRzMoveAngle(prm_angRz_Target);
////    _pGeoMover->setAutoTargetRyMoveAngle(prm_angRy_Target);
////
////    _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_Flg = true;
////    _pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_Flg = true;
//
//
//    //_pGeoMover->addRotAngle(AXIS_X, 5000);
//    //_pGeoMover->addRotAngle(AXIS_Y, 5000);
////    _pGeoMover->addRotAngle(AXIS_Y, ANGLE90);
////    _pGeoMover->setRotAngle(AXIS_X, _pMyOptionParent->_pGeoMover->_angRot[AXIS_X]);
////    _pGeoMover->setRotAngle(AXIS_Y, _pMyOptionParent->_pGeoMover->_angRot[AXIS_Y]);
////    _pGeoMover->setRotAngle(AXIS_Z, _pMyOptionParent->_pGeoMover->_angRot[AXIS_Z]);
////
//
//
////    _pGeoMover->_vX = _pMyOptionParent->_pGeoMover->_vX;
////    _pGeoMover->_vY = _pMyOptionParent->_pGeoMover->_vY;
////    _pGeoMover->_vZ = _pMyOptionParent->_pGeoMover->_vZ;
//
//
////    if (GameGlobal::_pMyShip->_stc != 0) {
////        angle Rz, Ry;
////        GgafDx9Util::getRotAngleZY(
////                _pMyOptionParent->_pGeoMover->_vX,
////                _pMyOptionParent->_pGeoMover->_vY,
////                _pMyOptionParent->_pGeoMover->_vZ,
////                Rz,
////                Ry
////                );
////        //_pGeoMover->setRzRyMoveAngle(Rz+_angPosRotX+ANGLE90, Ry-ANGLE90);
////        _pGeoMover->setRzMoveAngleVelocity(GgafDx9Util::COS[Rz/ANGLE_RATE]*_angvelo);
////        _pGeoMover->setRyMoveAngleVelocity(GgafDx9Util::SIN[Ry/ANGLE_RATE]*_angvelo);
////    }
//
//
////    _angRot_ParentPrev[AXIS_X] = _pGeoMover->_angRot[AXIS_X];
////    _angRot_ParentPrev[AXIS_Y] = _pGeoMover->_angRot[AXIS_Y];
////    _angRot_ParentPrev[AXIS_Z] = _pGeoMover->_angRot[AXIS_Z];
//
//
////    GgafDx9Util::getRotAngleZY(
////            _pGeoMover->_vX,
////            _pGeoMover->_vY,
////            _pGeoMover->_vZ,
////            Rz,
////            Ry
////            );
////    _pGeoMover->setRzMoveAngleVelocity(GgafDx9Util::COS[Rz/ANGLE_RATE]*_angvelo);//∵半径Ｒ＝速度Ｖ／角速度ω
////    _pGeoMover->setRyMoveAngleVelocity(GgafDx9Util::SIN[Ry/ANGLE_RATE]*_angvelo);//∵半径Ｒ＝速度Ｖ／角速度ω
//
//    //親の移動座標差分を加えて親にトレース
////    _X += (_pMyOptionParent->_X - _X_ParentPrev);
////    _Y += (_pMyOptionParent->_Y - _Y_ParentPrev);
////    _Z += (_pMyOptionParent->_Z - _Z_ParentPrev);
//
//
//
//
//
//
//
//
//    // | cosRZ*cosRY, sinRZ,  cosRZ* -sinRY | |_X|   | cosRZ*cosRY*_X + sinRZ*_Y + cosRZ* -sinRY*_Z |
//    // |-sinRZ*cosRY, cosRZ, -sinRZ* -sinRY | |_Y| = |-sinRZ*cosRY*_X + cosRZ*_Y - sinRZ* -sinRY*_Z |
//    // |       sinRY,     0,         cosRY | |_Z|   | sinRY*_X + cosRY*_Z                         |
//
////        angle Rz, Ry;
////        GgafDx9Util::getRotAngleZY(
////                _pMyOptionParent->_pGeoMover->_vX,
////                _pMyOptionParent->_pGeoMover->_vY,
////                _pMyOptionParent->_pGeoMover->_vZ,
////                Rz,
////                Ry
////                );
////
//
////
////
////
////
//
//
//
//
//
//    //次フレームのために親の情報を保存
//    _X_ParentPrev = _pMyOptionParent->_X;
//    _Y_ParentPrev = _pMyOptionParent->_Y;
//    _Z_ParentPrev = _pMyOptionParent->_Z;
//
//}

void MyDummyOption::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyDummyOption::processOnHit(GgafActor* prm_pActor_Opponent) {
    farewell();
}




void MyDummyOption::processDrawMain() {

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    static D3DXMATRIX matWorld; //WORLD変換行列
//    angle Rz2, Ry2;
//    GgafDx9Util::getRotAngleZY(
//            _pMyOptionParent->_pGeoMover->_vX,
//            _pMyOptionParent->_pGeoMover->_vY,
//            _pMyOptionParent->_pGeoMover->_vZ,
//            Rz2,
//            Ry2
//            );


    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);
//    getWorldTransformRxRyRzMvRyRzRy(
//               this,
//               //_pGeoMover->simplifyAngle(_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y] + ANGLE90),//←ANGLE270でなぜだめなのか
//               0,
//               _pMyOptionParent->_pGeoMover->_angRot[AXIS_Z],
//               _pMyOptionParent->_pGeoMover->_angRot[AXIS_Y],
//               //_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y], //TODOTODOTODO:薄っぺら苦なる、たぶん移動後の回転はだめなのか？！
////               _pMyOptionParent->_pGeoMover->_angRot[AXIS_Z],
////               _pMyOptionParent->_pGeoMover->_angRot[AXIS_Y],
//
//               matWorld);

    HRESULT hr;
    hr = pID3DXEffect->SetTechnique(_technique);
    potentialDx9Exception(hr, S_OK, "GgafDx9MeshActor::processDrawMain() SetTechnique("<<_technique<<") に失敗しました。");

    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &matWorld );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");
    UINT numPass;
    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE | D3DXFX_DONOTSAVESHADERSTATE );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() Begin() に失敗しました。");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = pID3DXEffect->BeginPass(pass);
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() BeginPass("<<pass<<") に失敗しました。");
        _pMeshModel->draw(this);
        hr = pID3DXEffect->EndPass();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() EndPass() に失敗しました。");
    }
    hr = pID3DXEffect->End();
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() End() に失敗しました。");

}





MyDummyOption::~MyDummyOption() {
    //DELETE_IMPOSSIBLE_NULL(_pRing);
}

void MyDummyOption::getWorldTransformRxRyRzMvRyRzRy(GgafDx9UntransformedActor* prm_pActor, angle prm_RY2, angle prm_RZ2, angle prm_RY3,  D3DXMATRIX& out_matWorld) {
    //WORLD変換
    //単位行列 × X軸回転 × Y軸回転 × Z軸回転 × 拡大縮小 × 平行移動 × Y軸回転 × Z軸回転× Y軸回転　の変換行列を作成

    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float sinRY2, cosRY2, sinRZ2, cosRZ2, sinRY3, cosRY3;
    static float fRateScale = 1.0 * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;
    static float dx, dy, dz;
    sinRX = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    sinRY2 = GgafDx9Util::SIN[prm_RY2 / ANGLE_RATE];
    cosRY2 = GgafDx9Util::COS[prm_RY2 / ANGLE_RATE];
    sinRZ2 = GgafDx9Util::SIN[prm_RZ2 / ANGLE_RATE];
    cosRZ2 = GgafDx9Util::COS[prm_RZ2 / ANGLE_RATE];
    sinRY3 = GgafDx9Util::SIN[prm_RY3 / ANGLE_RATE];
    cosRY3 = GgafDx9Util::COS[prm_RY3 / ANGLE_RATE];

    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;
    dx = (float)(1.0 * prm_pActor->_X / LEN_UNIT / PX_UNIT);
    dy = (float)(1.0 * prm_pActor->_Y / LEN_UNIT / PX_UNIT);
    dz = (float)(1.0 * prm_pActor->_Z / LEN_UNIT / PX_UNIT);


    out_matWorld._11 = sx*cosRY3;
    out_matWorld._12 = 0;
    out_matWorld._13 = sx*-sinRY3;
    out_matWorld._14 = 0;

    out_matWorld._21 = 0;
    out_matWorld._22 = sy;
    out_matWorld._23 = 0;
    out_matWorld._24 = 0;

    out_matWorld._31 = sz*sinRY2;
    out_matWorld._32 = 0;
    out_matWorld._33 = sz*cosRY3;
    out_matWorld._34 = 0;

    out_matWorld._41 = dx*cosRY3 + dz*sinRY2;
    out_matWorld._42 = dy;
    out_matWorld._43 = dx*-sinRY3 + dz*cosRY3;
    out_matWorld._44 = 1;
}


void MyDummyOption::getWorldTransformRxRyRzScMvRzRy(GgafDx9UntransformedActor* prm_pActor, angle prm_RZ2, angle prm_RY2, D3DXMATRIX& out_matWorld) {
    //WORLD変換
    //単位行列 × X軸回転 × Y軸回転 × Z軸回転 × 拡大縮小 × 平行移動 × Z軸回転× Y軸回転　の変換行列を作成
    //    |                           cosRY*cosRZ*sx,                        cosRY*sinRZ*sy  ,      -sinRY*sz,  0 |
    //    | ((sinRX*sinRY*cosRZ +  cosRX* -sinRZ)*sx), ((sinRX*sinRY*sinRZ +  cosRX*cosRZ)*sy), sinRX*cosRY*sz,  0 |
    //    | ((cosRX*sinRY*cosRZ + -sinRX* -sinRZ)*sx), ((cosRX*sinRY*sinRZ + -sinRX*cosRZ)*sy), cosRX*cosRY*sz,  0 |
    //    |                                       dx,                                      dy,             dz,  1 |

    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float sinRZ2, cosRZ2, sinRY2, cosRY2;
    static float fRateScale = 1.0 * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;
    static float dx, dy, dz;
    sinRX = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    sinRZ2 = GgafDx9Util::SIN[prm_RZ2 / ANGLE_RATE];
    cosRZ2 = GgafDx9Util::COS[prm_RZ2 / ANGLE_RATE];
    sinRY2 = GgafDx9Util::SIN[prm_RY2 / ANGLE_RATE];
    cosRY2 = GgafDx9Util::COS[prm_RY2 / ANGLE_RATE];

    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;
    dx = (float)(1.0 * prm_pActor->_X / LEN_UNIT / PX_UNIT);
    dy = (float)(1.0 * prm_pActor->_Y / LEN_UNIT / PX_UNIT);
    dz = (float)(1.0 * prm_pActor->_Z / LEN_UNIT / PX_UNIT);


    out_matWorld._11 = (cosRY*cosRZ*sx*cosRZ2 + cosRY*sinRZ*sy* -sinRZ2)*cosRY2 + -sinRY*sz*sinRY2;
    out_matWorld._12 = (cosRY*cosRZ*sx*sinRZ2 + cosRY*sinRZ*sy*cosRZ2);
    out_matWorld._13 = (cosRY*cosRZ*sx*cosRZ2 + cosRY*sinRZ*sy* -sinRZ2)* -sinRY2 + -sinRY*sz*cosRY2;
    out_matWorld._14 = 0;

    out_matWorld._21 = ((((sinRX*sinRY*cosRZ + cosRX* -sinRZ)*sx))*cosRZ2 + (((sinRX*sinRY*sinRZ + cosRX*cosRZ)*sy))* -sinRZ2)*cosRY2 + sinRX*cosRY*sz*sinRY2;
    out_matWorld._22 = ((((sinRX*sinRY*cosRZ + cosRX* -sinRZ)*sx))*sinRZ2 + (((sinRX*sinRY*sinRZ + cosRX*cosRZ)*sy))*cosRZ2);
    out_matWorld._23 = ((((sinRX*sinRY*cosRZ + cosRX* -sinRZ)*sx))*cosRZ2 + (((sinRX*sinRY*sinRZ + cosRX*cosRZ)*sy))* -sinRZ2)* -sinRY2 + sinRX*cosRY*sz*cosRY2;
    out_matWorld._24 = 0;

    out_matWorld._31 = ((((cosRX*sinRY*cosRZ + -sinRX* -sinRZ)*sx))*cosRZ2 + (((cosRX*sinRY*sinRZ + -sinRX*cosRZ)*sy))* -sinRZ2)*cosRY2 + cosRX*cosRY*sz*sinRY2;
    out_matWorld._32 = ((((cosRX*sinRY*cosRZ + -sinRX* -sinRZ)*sx))*sinRZ2 + (((cosRX*sinRY*sinRZ + -sinRX*cosRZ)*sy))*cosRZ2);
    out_matWorld._33 = ((((cosRX*sinRY*cosRZ + -sinRX* -sinRZ)*sx))*cosRZ2 + (((cosRX*sinRY*sinRZ + -sinRX*cosRZ)*sy))* -sinRZ2)* -sinRY2 + cosRX*cosRY*sz*cosRY2;
    out_matWorld._34 = 0;

    out_matWorld._41 = (dx*cosRZ2 + dy* -sinRZ2)*cosRY2 + dz*sinRY2,
    out_matWorld._42 = (dx*sinRZ2 + dy*cosRZ2),
    out_matWorld._43 = (dx*cosRZ2 + dy* -sinRZ2)* -sinRY2 + dz*cosRY2,
    out_matWorld._44 = 1;
}


void MyDummyOption::getWorldTransformRxRyRzRyScMv(GgafDx9UntransformedActor* prm_pActor, angle prm_RYt, D3DXMATRIX& out_matWorld) {
    //WORLD変換

    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float sinRYt, cosRYt;
    static float fRateScale = 1.0 * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;
    static float dx, dy, dz;
    sinRX = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];

    sinRYt = GgafDx9Util::SIN[prm_RYt / ANGLE_RATE];
    cosRYt = GgafDx9Util::COS[prm_RYt / ANGLE_RATE];

    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;
    dx = (float)(1.0 * prm_pActor->_X / LEN_UNIT / PX_UNIT);
    dy = (float)(1.0 * prm_pActor->_Y / LEN_UNIT / PX_UNIT);
    dz = (float)(1.0 * prm_pActor->_Z / LEN_UNIT / PX_UNIT);

    out_matWorld._11 = ((cosRYt*cosRZ*cosRY + -sinRYt*sinRY)*sx);
    out_matWorld._12 = cosRYt*sinRZ*sy;
    out_matWorld._13 = ((cosRYt*cosRZ*-sinRY + -sinRYt*cosRY)*sz);
    out_matWorld._14 = 0;

    out_matWorld._21 = (((sinRX*sinRYt*cosRZ + cosRX*-sinRZ)*cosRY + sinRX*cosRYt*sinRY)*sx);
    out_matWorld._22 = (((sinRX*sinRYt*sinRZ + cosRX*cosRZ))*sy);
    out_matWorld._23 = (((sinRX*sinRYt*cosRZ + cosRX*-sinRZ)*-sinRY + sinRX*cosRYt*cosRY)*sz);
    out_matWorld._24 = 0;

    out_matWorld._31 = (((cosRX*sinRYt*cosRZ + -sinRX*-sinRZ)*cosRY + cosRX*cosRYt*sinRY)*sx);
    out_matWorld._32 = (((cosRX*sinRYt*sinRZ + -sinRX*cosRZ))*sy);
    out_matWorld._33 = (((cosRX*sinRYt*cosRZ + -sinRX*-sinRZ)*-sinRY + cosRX*cosRYt*cosRY)*sz);
    out_matWorld._34 = 0;

    out_matWorld._41 = dx;
    out_matWorld._42 = dy;
    out_matWorld._43 = dz;
    out_matWorld._44 = 1;
}


