#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOption::MyOption(const char* prm_name, int prm_no, MyDummyOption* prm_pMyDummyOption) : DefaultMeshActor(prm_name, "X/ebi2") {
_TRACE_("MyOption::MyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyOption";
    _pMyDummyOption = prm_pMyDummyOption;
    _no = prm_no;
}

void MyOption::initialize() {

    int v = 4000;
    _angvelo = ((1.0*v / _pMyDummyOption->_distR)*(double)ANGLE180)/PI;
    _pGeoMover->setMoveVelocity(v);
    _pGeoMover->setRzMoveAngle(_pMyDummyOption->_angPosRotX+ANGLE90);
    _pGeoMover->setRyMoveAngle(-ANGLE90);
    _pGeoMover->setRzMoveAngleVelocity(_angvelo);//ÅÊîºåaÇqÅÅë¨ìxÇuÅ^äpë¨ìxÉ÷
    _pGeoMover->setRyMoveAngleVelocity(0);//ÅÊîºåaÇqÅÅë¨ìxÇuÅ^äpë¨ìxÉ÷
    _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_Flg = true;
    _pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_Flg = true; //RYÇÕégÇ¡ÇƒÇÕë ñ⁄ÅBïœä∑çsóÒÇ™RxRyRzÇæÇ©ÇÁ
    _Z = GgafDx9Util::COS[_pMyDummyOption->_angPosRotX/ANGLE_RATE]*_pMyDummyOption->_distR; //Xé≤íÜêSâÒì]Ç»ÇÃÇ≈XYÇ≈ÇÕÇ»Ç≠ÇƒZY
    _Y = GgafDx9Util::SIN[_pMyDummyOption->_angPosRotX/ANGLE_RATE]*_pMyDummyOption->_distR;

//    _pGeoMover->setMoveVelocity(GgafDx9Util::RAD[_pMyDummyOption->_pMyOptionParent->_angVelocity_Turn/ANGLE_RATE] *200000);//ãóó£
//    _pGeoMover->setMoveVelocity(4000);//ãóó£

    //    _pGeoMover->setMoveVelocity(v);
//    _pGeoMover->setRzMoveAngleVelocity(v/_distR);
//    _angvelo = ((1.0*v / _distR)*(double)ANGLE180)/PI;
//    _pGeoMover->setMoveVelocity(v);
//    _pGeoMover->setRzMoveAngle(_angPosRotX+ANGLE90);
//    _pGeoMover->setRyMoveAngle(0);
//    _pGeoMover->setRzMoveAngleVelocity(_angvelo);//ÅÊîºåaÇqÅÅë¨ìxÇuÅ^äpë¨ìxÉ÷
//    _pGeoMover->setRyMoveAngleVelocity(0);//ÅÊîºåaÇqÅÅë¨ìxÇuÅ^äpë¨ìxÉ÷
//
//
//
////    _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_Flg = true;
//    _pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_Flg = true;
//    _pGeoMover->setRyMoveAngle(-ANGLE90);//Rzâ~â^ìÆÇµÇƒÇ¢ÇÈÉÇÉmÇXé≤íÜêSâÒì]Ç…ïœä∑

//    _Z += GgafDx9Util::COS[_pMyDummyOption->_angPosRotX/ANGLE_RATE]*_pMyDummyOption->_distR; //Xé≤íÜêSâÒì]Ç»ÇÃÇ≈XYÇ≈ÇÕÇ»Ç≠ÇƒZY
//    _Y += GgafDx9Util::SIN[_pMyDummyOption->_angPosRotX/ANGLE_RATE]*_pMyDummyOption->_distR;
//    _angExpanse = 0;
//

    //
//    _sangvelo = 0;
//
//
//
//    _angRzMove_ParentPrev = _pMyDummyOption->_pGeoMover->_angRzMove;
//    _angRyMove_ParentPrev = _pMyDummyOption->_pGeoMover->_angRzMove;
//    _angveloRzMove_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angveloRzMove;
//    _angveloRyMove_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angveloRyMove;
//    _X_ParentPrev = _pMyDummyOption->_X;
//    _Y_ParentPrev = _pMyDummyOption->_Y;
//    _Z_ParentPrev = _pMyDummyOption->_Z;
//


//    _vX_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vX;
//    _vY_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vY;
//    _vZ_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vZ;

//
//
//    _TRACE_("_angPosRotX="<<_angPosRotX<<" _distR="<<_distR<<" èâä˙ZY="<<_Z<<","<<_Y);
//    _TRACE_("GgafDx9Util::COS[_angPosRotX/ANGLE_RATE]*_distR="<<GgafDx9Util::COS[_angPosRotX/ANGLE_RATE]*_distR);
//    _TRACE_("GgafDx9Util::SIN[_angPosRotX/ANGLE_RATE]*_distR="<<GgafDx9Util::SIN[_angPosRotX/ANGLE_RATE]*_distR);

//    _Xorg = _X;
//    _Yorg = _Y;
//    _Zorg = _Z;
//
//	//_pGeoMover->addRotAngle(AXIS_Z, -ANGLE90);
//
//    _angRot_ParentPrev[AXIS_X] = _pMyDummyOption->_pGeoMover->_angRot[AXIS_X];
//    _angRot_ParentPrev[AXIS_Y] = _pMyDummyOption->_pGeoMover->_angRot[AXIS_Y];
//    _angRot_ParentPrev[AXIS_Z] = _pMyDummyOption->_pGeoMover->_angRot[AXIS_Z];
}

void MyOption::processBehavior() {
    _pGeoMover->addRotAngle(AXIS_Z, -ANGLE90);
    //_pGeoMover->addRotAngle(AXIS_Z, 0);
    //_pGeoMover->addRotAngle(AXIS_Y, 2000);

//    angle Rz, Ry;
//    GgafDx9Util::getRotAngleZY(
//            _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vX,
//            _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vY,
//            _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vZ,
//            Rz,
//            Ry
//            );
    //    _X = cosRZ*cosRY*_Xorg + sinRZ*_Yorg + cosRZ*-sinRY*_Zorg;
    //    _Y = -sinRZ*cosRY*_Xorg + cosRZ*_Yorg + -sinRZ*-sinRY*_Zorg;
    //    _Z = sinRY*_Xorg + cosRY*_Zorg;




    //_angExpanse = GgafDx9GeometryMover::simplifyAngle(_angExpanse + 2000);

    //
//    _pGeoMover->setRotAngle(AXIS_X, _pMyDummyOption->_pGeoMover->_angRot[AXIS_X]);
//    _pGeoMover->setRotAngle(AXIS_Y, _pMyDummyOption->_pGeoMover->_angRot[AXIS_Y]);
//    _pGeoMover->setRotAngle(AXIS_Z, _pMyDummyOption->_pGeoMover->_angRot[AXIS_Z]);

    //    angle angRzMovediff_Dummy = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRzMove - _angRzMove_ParentPrev;
    //    angle angRyMovediff_Parent = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRyMove - _angRyMove_ParentPrev;
//    bool flg = false;
//    if (_angveloRzMove_ParentPrev != _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angveloRzMove) {
//        _pGeoMover->addRzMoveAngle(_angveloRzMove_ParentPrev - _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRzMove);
//        flg = true;
//    }
//    if (_angveloRyMove_ParentPrev != _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angveloRyMove) {
//        _pGeoMover->addRyMoveAngle(_angveloRyMove_ParentPrev - _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRyMove - ANGLE90);
//        flg = true;
//    }


//    _pGeoMover->setRzMoveAngle(_pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRzMove);
//    _pGeoMover->setRyMoveAngle(_pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRyMove);
//    if (GameGlobal::_pMyShip->_stc != 0) {
//        //ìÆÇ©ÇªÇ§Ç∆ÇµÇƒÇ¢ÇΩÅI
//        if ((_vX_ParentPrev != _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vX) ||
//            (_vY_ParentPrev != _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vY) ||
//            (_vZ_ParentPrev != _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vZ)) {
//
//            _pGeoMover->behave();
//
//        }
//    }

//    _vX_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vX;
//    _vY_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vY;
//    _vZ_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vZ;

//    _angveloRzMove_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angveloRzMove;
//    _angveloRyMove_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angveloRyMove;


    //êeÇÃà⁄ìÆï˚äpç∑ï™Çâ¡Ç¶ÇƒêeÇ∆ìØï˚äpÇ…âÒì]à⁄ìÆ
//    angle angRzMovediff_Dummy = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRzMove - _angRzMove_ParentPrev;
//    angle angRyMovediff_Parent = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRyMove - _angRyMove_ParentPrev;
//    if (angRzMovediff_Parent != 0 || angRyMovediff_Parent != 0) {
//        //âÒì]à⁄ìÆ
//        int out_X, out_Y;
//        GgafDx9Util::rotXY(int _X, int prm_Y,
//                           angle prm_ang,
//                           int& out_X, int& out_Y) {
//    }
        //        //êeÇÃà⁄ìÆï˚äpç∑ï™Çâ¡Ç¶ÇƒêeÇ∆ìØï˚äpÇ…âÒì]à⁄ìÆ
//        _pGeoMover->setRzMoveAngle(_pMyDummyOption->_pGeoMover->_angRzMove);
//        _pGeoMover->setRyMoveAngle(_pMyDummyOption->_pGeoMover->_angRyMove - ANGLE90);
//
//    }
////        _TRACE_("Rz,Ry êeÅF"<<_pMyDummyOption->_pGeoMover->_angRzMove<<","<<_pMyDummyOption->_pGeoMover->_angRyMove);
////        _TRACE_("Rz,Ry êeëOÅF"<<_angRzMove_ParentPrev<<","<<_angRyMove_ParentPrev);
////        _TRACE_("Rz,Ry éÑÅF"<<_pGeoMover->_angRzMove<<","<<_pGeoMover->_angRyMove);
////        _TRACE_("Rz,Ry ç∑ÅF"<<angRzMovediff_Parent<<","<<angRyMovediff_Parent);
////                _pGeoMover->setRzRyMoveAngle(_pMyDummyOption->_pGeoMover->_angRzMove,
////                                             _pMyDummyOption->_pGeoMover->_angRyMove);
//
//
//        _pGeoMover->setRzMoveAngle(_pGeoMover->_angRzMove + angRzMovediff_Parent);
//        _pGeoMover->setRyMoveAngle(_pGeoMover->_angRyMove + angRyMovediff_Parent);
//
//
////        double dX,dY,dZ;
////        GgafDx9Util::getNormalizeVectorZY(angRzMovediff_Parent,
////                                          angRyMovediff_Parent,
////                                          dX,
////                                          dY,
////                                          dZ);
//        _X += (_pGeoMover->_vX - _pMyDummyOption->_pGeoMover->_vX)  * _pGeoMover->_veloMove;
//        _Y += (_pGeoMover->_vY - _pMyDummyOption->_pGeoMover->_vY)  * _pGeoMover->_veloMove;
//        _Z += (_pGeoMover->_vZ - _pMyDummyOption->_pGeoMover->_vZ)  * _pGeoMover->_veloMove;
////        angvelo angveloRzMoveDiff_Parent = _pMyDummyOption->_pGeoMover->_angveloRzMove - _angveloRzMove_ParentPrev;
////        angvelo angveloRyMoveDiff_Parent = _pMyDummyOption->_pGeoMover->_angveloRyMove - _angveloRyMove_ParentPrev;
//
////        _pGeoMover->setRzMoveAngleVelocity(GgafDx9Util::COS[_pGeoMover->_angRyMove/ANGLE_RATE] * _angvelo);//ÅÊîºåaÇqÅÅë¨ìxÇuÅ^äpë¨ìxÉ÷
////        _pGeoMover->setRyMoveAngleVelocity(GgafDx9Util::SIN[_pGeoMover->_angRzMove/ANGLE_RATE] * _angvelo);//ÅÊîºåaÇqÅÅë¨ìxÇuÅ^äpë¨ìxÉ÷
//
//
////        _pGeoMover->setRzRyMoveAngle(_pGeoMover->_angRzMove+angRzMovediff_Parent,
////                                     _pGeoMover->_angRyMove+angRyMovediff_Parent);
//    }

    //_pGeoMover->addRotAngle(AXIS_X, _pMyDummyOption->_pGeoMover->_angRot[AXIS_X] - _angRot_ParentPrev[AXIS_X]);
    //_pGeoMover->addRotAngle(AXIS_Y, _pMyDummyOption->_pGeoMover->_angRot[AXIS_Y] - _angRot_ParentPrev[AXIS_Y]);
    //_pGeoMover->addRotAngle(AXIS_Z, _pMyDummyOption->_pGeoMover->_angRot[AXIS_Z] - _angRot_ParentPrev[AXIS_Z]);

    _pGeoMover->behave();
//
//    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
//    sinRY = GgafDx9Util::SIN[_pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y] / ANGLE_RATE];
//    cosRY = GgafDx9Util::COS[_pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y] / ANGLE_RATE];
//    sinRZ = GgafDx9Util::SIN[_pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRot[AXIS_Z] / ANGLE_RATE];
//    cosRZ = GgafDx9Util::COS[_pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRot[AXIS_Z] / ANGLE_RATE];
//    _Xorg = _pMyDummyOption->_X;
//    _Yorg = _pMyDummyOption->_Y;
//    _Zorg = _pMyDummyOption->_Z;
//
//    _X = cosRZ*cosRY*_Xorg + -sinRZ*_Yorg + cosRZ*sinRY*_Zorg;
//    _Y = sinRZ*cosRY*_Xorg + cosRZ*_Yorg + sinRZ*sinRY*_Zorg;
//    _Z = -sinRY*_Xorg + cosRY*_Zorg;
//
//



//    _angRot_ParentPrev[AXIS_X] = _pMyDummyOption->_pGeoMover->_angRot[AXIS_X];
//    _angRot_ParentPrev[AXIS_Y] = _pMyDummyOption->_pGeoMover->_angRot[AXIS_Y];
//    _angRot_ParentPrev[AXIS_Z] = _pMyDummyOption->_pGeoMover->_angRot[AXIS_Z];

    //êeÇÃà⁄ìÆç¿ïWç∑ï™Çâ¡Ç¶ÇƒêeÇ…ÉgÉåÅ[ÉX
//    _X += (_pMyDummyOption->_X - _X_ParentPrev);
//    _Y += (_pMyDummyOption->_Y - _Y_ParentPrev);
//    _Z += (_pMyDummyOption->_Z - _Z_ParentPrev);
//
//    _X_ParentPrev = _pMyDummyOption->_X;
//    _Y_ParentPrev = _pMyDummyOption->_Y;
//    _Z_ParentPrev = _pMyDummyOption->_Z;

    //éüÉtÉåÅ[ÉÄÇÃÇΩÇﬂÇ…êeÇÃèÓïÒÇï€ë∂
//    _angRzMove_ParentPrev = _pMyDummyOption->_pGeoMover->_angRzMove;
//    _angRyMove_ParentPrev = _pMyDummyOption->_pGeoMover->_angRyMove;
//    _angveloRzMove_ParentPrev = _pMyDummyOption->_pGeoMover->_angveloRzMove;
//    _angveloRyMove_ParentPrev = _pMyDummyOption->_pGeoMover->_angveloRyMove;
////    _X_ParentPrev = _pMyDummyOption->_X;
//    _Y_ParentPrev = _pMyDummyOption->_Y;
//    _Z_ParentPrev = _pMyDummyOption->_Z;

}

void MyOption::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyOption::processOnHit(GgafActor* prm_pActor_Opponent) {
    farewell();
}



MyOption::~MyOption() {
    //DELETE_IMPOSSIBLE_NULL(_pRing);
}


void MyOption::processDrawMain() {

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    static D3DXMATRIX matWorld; //WORLDïœä∑çsóÒ
//    angle Rz2, Ry2;
//    GgafDx9Util::getRotAngleZY(
//            _pMyOptionParent->_pGeoMover->_vX,
//            _pMyOptionParent->_pGeoMover->_vY,
//            _pMyOptionParent->_pGeoMover->_vZ,
//            Rz2,
//            Ry2
//            );

    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);
    //MyOption::getWorldTransformRxRyRzRyScMv(this, _angExpanse, matWorld);
//    getWorldTransformRxRyRzMvRyRzRy(
//               this,
//               //_pGeoMover->simplifyAngle(_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y] + ANGLE90),//Å©ANGLE270Ç≈Ç»Ç∫ÇæÇﬂÇ»ÇÃÇ©
//               0,
//               _pMyOptionParent->_pGeoMover->_angRot[AXIS_Z],
//               _pMyOptionParent->_pGeoMover->_angRot[AXIS_Y],
//               //_pMyOptionParent->_pGeoMover->_angRot[AXIS_Y], //TODOTODOTODO:îñÇ¡ÇÿÇÁãÍÇ»ÇÈÅAÇΩÇ‘ÇÒà⁄ìÆå„ÇÃâÒì]ÇÕÇæÇﬂÇ»ÇÃÇ©ÅHÅI
////               _pMyOptionParent->_pGeoMover->_angRot[AXIS_Z],
////               _pMyOptionParent->_pGeoMover->_angRot[AXIS_Y],
//
//               matWorld);

    HRESULT hr;
    hr = pID3DXEffect->SetTechnique(_technique);
    potentialDx9Exception(hr, S_OK, "GgafDx9MeshActor::processDrawMain() SetTechnique("<<_technique<<") Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &matWorld );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() SetMatrix(g_matWorld) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    UINT numPass;
    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE | D3DXFX_DONOTSAVESHADERSTATE );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() Begin() Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = pID3DXEffect->BeginPass(pass);
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() BeginPass("<<pass<<") Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        _pMeshModel->draw(this);
        hr = pID3DXEffect->EndPass();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() EndPass() Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    }
    hr = pID3DXEffect->End();
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() End() Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

}


void MyOption::getWorldTransformRxRyRzRyScMv(GgafDx9UntransformedActor* prm_pActor, angle prm_RYt, D3DXMATRIX& out_matWorld) {
    //WORLDïœä∑

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
