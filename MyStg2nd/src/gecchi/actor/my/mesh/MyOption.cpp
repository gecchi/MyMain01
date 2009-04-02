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
    _pGeoMover->setMoveVelocity(GgafDx9Util::RAD[_pMyDummyOption->_pMyOptionParent->_angVelocity_Turn/ANGLE_RATE] *200000);//ãóó£
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
    _X += GgafDx9Util::COS[_pMyDummyOption->_angPosRotX/ANGLE_RATE]*_pMyDummyOption->_distR; //Xé≤íÜêSâÒì]Ç»ÇÃÇ≈XYÇ≈ÇÕÇ»Ç≠ÇƒZY
    _Y += GgafDx9Util::SIN[_pMyDummyOption->_angPosRotX/ANGLE_RATE]*_pMyDummyOption->_distR;
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
    _vX_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vX;
    _vY_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vY;
    _vZ_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vZ;

//
//
//    _TRACE_("_angPosRotX="<<_angPosRotX<<" _distR="<<_distR<<" èâä˙ZY="<<_Z<<","<<_Y);
//    _TRACE_("GgafDx9Util::COS[_angPosRotX/ANGLE_RATE]*_distR="<<GgafDx9Util::COS[_angPosRotX/ANGLE_RATE]*_distR);
//    _TRACE_("GgafDx9Util::SIN[_angPosRotX/ANGLE_RATE]*_distR="<<GgafDx9Util::SIN[_angPosRotX/ANGLE_RATE]*_distR);


}

void MyOption::processBehavior() {
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


    _pGeoMover->setRzMoveAngle(_pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRzMove);
    _pGeoMover->setRyMoveAngle(_pMyDummyOption->_pMyOptionParent->_pGeoMover->_angRyMove);
    if (GameGlobal::_pMyShip->_stc != 0) {
        //ìÆÇ©ÇªÇ§Ç∆ÇµÇƒÇ¢ÇΩÅI
        if ((_vX_ParentPrev != _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vX) ||
            (_vY_ParentPrev != _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vY) ||
            (_vZ_ParentPrev != _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vZ)) {

            _pGeoMover->behave();

        }
    }

    _vX_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vX;
    _vY_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vY;
    _vZ_ParentPrev = _pMyDummyOption->_pMyOptionParent->_pGeoMover->_vZ;

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


//    _pGeoMover->behave();

    //êeÇÃà⁄ìÆç¿ïWç∑ï™Çâ¡Ç¶ÇƒêeÇ…ÉgÉåÅ[ÉX
//    _X += (_pMyDummyOption->_X - _X_ParentPrev);
//    _Y += (_pMyDummyOption->_Y - _Y_ParentPrev);
//    _Z += (_pMyDummyOption->_Z - _Z_ParentPrev);


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
