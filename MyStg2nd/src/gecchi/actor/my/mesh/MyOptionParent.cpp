#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


//MyOptionParent::MyOptionParent(const char* prm_name) :
//    DefaultMeshActor(prm_name, "vic2") {

MyOptionParent::MyOptionParent(const char* prm_name) :
  GgafDx9GeometricActor(prm_name,
                            NULL) {

    _angVelo_Turn = 8000;

    MyDummyOption* pMyDummyOption01 = NEW MyDummyOption("MY_OPTION01", 0, this);
    pMyDummyOption01->_radiusPosition = 60000;
    pMyDummyOption01->_veloMv = 2000;
    pMyDummyOption01->_angExpanse = 0;
    pMyDummyOption01->_angveloExpanse = 0;
    pMyDummyOption01->_angPosition = 0;
    pMyDummyOption01->setMaterialColor(1.0, 1.0, 1.0);
    addSubLast(pMyDummyOption01);

    MyDummyOption* pMyDummyOption02 = NEW MyDummyOption("MY_OPTION02", 1, this);
    pMyDummyOption02->_radiusPosition = 60000;
    pMyDummyOption02->_veloMv = 2000;
    pMyDummyOption02->_angExpanse = 0;
    pMyDummyOption02->_angveloExpanse = 0;
    pMyDummyOption02->_angPosition = ANGLE90;
    pMyDummyOption02->setMaterialColor(0.0, 1.0, 1.0);
    addSubLast(pMyDummyOption02);

    MyDummyOption* pMyDummyOption03 = NEW MyDummyOption("MY_OPTION03", 2, this);
    pMyDummyOption03->_radiusPosition = 60000;
    pMyDummyOption03->_veloMv = 2000;
    pMyDummyOption03->_angExpanse = 0;
    pMyDummyOption03->_angveloExpanse = 0;
    pMyDummyOption03->_angPosition = ANGLE180;
    pMyDummyOption03->setMaterialColor(1.0, 0, 1.0);
    addSubLast(pMyDummyOption03);

    MyDummyOption* pMyDummyOption04 = NEW MyDummyOption("MY_OPTION04", 4, this);
    pMyDummyOption04->_radiusPosition = 60000;
    pMyDummyOption04->_veloMv = 2000;
    pMyDummyOption04->_angExpanse = 0;
    pMyDummyOption04->_angveloExpanse = 0;
    pMyDummyOption04->_angPosition = ANGLE270;
    pMyDummyOption04->setMaterialColor(0, 1.0, 0);
    addSubLast(pMyDummyOption04);

    MyDummyOption* pMyDummyOption05 = NEW MyDummyOption("MY_OPTION05", 5, this);
    pMyDummyOption05->_radiusPosition = 120000;
    pMyDummyOption05->_angPosition = 0;
    pMyDummyOption05->_angExpanse = 0;
    pMyDummyOption05->_angveloExpanse = 0;
    pMyDummyOption05->_veloMv = -3000;
    pMyDummyOption05->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 0, 1.0, 1.0);
    addSubLast(pMyDummyOption05);

    MyDummyOption* pMyDummyOption06 = NEW MyDummyOption("MY_OPTION06", 6, this);
    pMyDummyOption06->_radiusPosition = 120000;
    pMyDummyOption06->_angPosition = ANGLE90;
    pMyDummyOption06->_angExpanse = 0;
    pMyDummyOption06->_angveloExpanse = 0;
    pMyDummyOption06->_veloMv = -3000;
    pMyDummyOption06->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 1.0, 0, 1.0);
    addSubLast(pMyDummyOption06);

    MyDummyOption* pMyDummyOption07 = NEW MyDummyOption("MY_OPTION07", 7, this);
    pMyDummyOption07->_radiusPosition = 120000;
    pMyDummyOption07->_angPosition = ANGLE180;
    pMyDummyOption07->_angExpanse = 0;
    pMyDummyOption07->_angveloExpanse = 0;
    pMyDummyOption07->_veloMv = -3000;
    pMyDummyOption07->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0, 0, 1.0);
    addSubLast(pMyDummyOption07);

    MyDummyOption* pMyDummyOption08 = NEW MyDummyOption("MY_OPTION08", 8, this);
    pMyDummyOption08->_radiusPosition = 120000;
    pMyDummyOption08->_angPosition = ANGLE270;
    pMyDummyOption08->_angExpanse = 0;
    pMyDummyOption08->_angveloExpanse = 0;
    pMyDummyOption08->_veloMv = -3000;
    pMyDummyOption08->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
    pMyDummyOption08->setAlpha(0.3);
    addSubLast(pMyDummyOption08);

//    MyDummyOption* pMyDummyOption09 = NEW MyDummyOption("MY_OPTION09", 9, this);
//    pMyDummyOption09->_radiusPosition = 180000;
//    pMyDummyOption09->_angPosition = 0;
//    pMyDummyOption09->_angExpanse = 0;
//    pMyDummyOption09->_angveloExpanse = 0;
//    pMyDummyOption09->_veloMv = 4000;
//    addSubLast(pMyDummyOption09);
//
//    MyDummyOption* pMyDummyOption10 = NEW MyDummyOption("MY_OPTION10",10, this);
//    pMyDummyOption10->_radiusPosition = 180000;
//    pMyDummyOption10->_angPosition = ANGLE90;
//    pMyDummyOption10->_angExpanse = 0;
//    pMyDummyOption10->_angveloExpanse = 0;
//    pMyDummyOption10->_veloMv = 4000;
//    addSubLast(pMyDummyOption10);
//
//    MyDummyOption* pMyDummyOption11 = NEW MyDummyOption("MY_OPTION11",11, this);
//    pMyDummyOption11->_radiusPosition = 180000;
//    pMyDummyOption11->_angPosition = ANGLE180;
//    pMyDummyOption11->_angExpanse = 0;
//    pMyDummyOption11->_angveloExpanse = 0;
//    pMyDummyOption11->_veloMv = 4000;
//    addSubLast(pMyDummyOption11);
//
//    MyDummyOption* pMyDummyOption12 = NEW MyDummyOption("MY_OPTION12",12, this);
//    pMyDummyOption12->_radiusPosition = 180000;
//    pMyDummyOption12->_angPosition = ANGLE270;
//    pMyDummyOption12->_angExpanse = 0;
//    pMyDummyOption12->_angveloExpanse = 0;
//    pMyDummyOption12->_veloMv = 4000;
//    addSubLast(pMyDummyOption12);

    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }
    _is_rotate = false;
}

void MyOptionParent::initialize() {
    _pMover->setMvVelo(0);
    _pMover->setRyMvAngVeloRenge(-1*_angVelo_Turn, _angVelo_Turn);
    _pMover->setRzMvAngVeloRenge(-1*_angVelo_Turn, _angVelo_Turn);
    _pMover->setRzRyMvAng(0,0);
    _way_myship_prev = GameGlobal::_pMyShip->_way;
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->behave();
}

void MyOptionParent::processBehavior() {
//    _X = GameGlobal::_pMyShip->_X;
//    _Y = GameGlobal::_pMyShip->_Y;
//    _Z = GameGlobal::_pMyShip->_Z;

    //方向が変わった

    if (VB::isBeingPressed(VB_OPTION)) {
        _is_rotate = true;
    } else {
        _is_rotate = false;
    }

//    if (_is_rotate) {
//        _pMover->execTagettingMvAngSequence(
//                        GameGlobal::_pMyShip->_pMover->_angRzMv,
//                        GameGlobal::_pMyShip->_pMover->_angRyMv,
//                        3000, 0,
//                        TURN_CLOSE_TO
//                 );
//    } else {
//        _pMover->execTagettingMvAngSequence(
//                        0,
//                        0,
//                        200, 0,
//                        TURN_CLOSE_TO
//                 );
//    }

    if (pMYSHIP->_way != WAY_NONE && VB::isBeingPressed(VB_OPTION)) {
        _pMover->behave();
    } else {


    }
//
//
//    if (VB::isBeingPressed(VB_OPTION)) {
//        if (_way_myship_prev != GameGlobal::_pMyShip->_way) {
//
//
//
////            switch(GameGlobal::_pMyShip->_way) {
////
////
////
////                case WAY_UP:
////                    if (pWORLD->_pos_camera == CAM_POS_RIGHT || pWORLD->_pos_camera == CAM_POS_LEFT) {
////                        _pMover->execTagettingMvAngSequence(ANGLE90, 0,
////                                                                   _angVelo_Turn, TURN_CLOSE_TO);
////                    } else {
////                        _pMover->execTagettingMvAngSequence(ANGLE90, ANGLE90,
////                                                                   _angVelo_Turn, TURN_CLOSE_TO);
////                    }
////                    break;
////                case WAY_UP_FRONT:
////                    _pMover->execTagettingMvAngSequence(ANGLE45, 0,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////                case WAY_UP_BEHIND:
////                    _pMover->execTagettingMvAngSequence(ANGLE135, 0,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////                case WAY_DOWN:
////                    if (pWORLD->_pos_camera == CAM_POS_RIGHT || pWORLD->_pos_camera == CAM_POS_LEFT) {
////                        _pMover->execTagettingMvAngSequence(ANGLE270, 0,
////                                                                   _angVelo_Turn, TURN_CLOSE_TO);
////                    } else {
////                        _pMover->execTagettingMvAngSequence(ANGLE270, ANGLE90,
////                                                                   _angVelo_Turn, TURN_CLOSE_TO);
////                    }
////                    break;
////                case WAY_DOWN_FRONT:
////                    _pMover->execTagettingMvAngSequence(ANGLE315, 0,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////                case WAY_DOWN_BEHIND:
////                    _pMover->execTagettingMvAngSequence(ANGLE225, 0,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////                case WAY_FRONT:
////                    _pMover->execTagettingMvAngSequence(0, 0,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////                case WAY_BEHIND:
////                    _pMover->execTagettingMvAngSequence(ANGLE180, 0,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    //            _pMover->setStopTarget_RzMvAng(0);
////                    //            _pMover->setStopTarget_RyMvAng(ANGLE180);
////
////                    break;
////                case WAY_ZLEFT:
////                    _pMover->execTagettingMvAngSequence(ANGLE180, ANGLE90,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////
////                case WAY_ZLEFT_UP:
////                    _pMover->execTagettingMvAngSequence(ANGLE135, ANGLE90,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////                case WAY_ZLEFT_DOWN:
////                    _pMover->execTagettingMvAngSequence(ANGLE225, ANGLE90,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////
////                case WAY_ZLEFT_FRONT:
////                    _pMover->execTagettingMvAngSequence(ANGLE180, ANGLE135,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////                case WAY_ZLEFT_BEHIND:
////                    _pMover->execTagettingMvAngSequence(ANGLE180, ANGLE45,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////
////
////                case WAY_ZRIGHT:
////                    _pMover->execTagettingMvAngSequence(0, ANGLE90
////                                                               , _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////                case WAY_ZRIGHT_UP:
////                    _pMover->execTagettingMvAngSequence(ANGLE45, ANGLE90,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////                case WAY_ZRIGHT_DOWN:
////                    _pMover->execTagettingMvAngSequence(ANGLE315, ANGLE90,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////
////                case WAY_ZRIGHT_FRONT:
////                    _pMover->execTagettingMvAngSequence(0, ANGLE45,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////                case WAY_ZRIGHT_BEHIND:
////                    _pMover->execTagettingMvAngSequence(0, ANGLE135,
////                                                               _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////                default:
////                    //_pMover->execTagettingMvAngSequence(0, 0, _angVelo_Turn, TURN_CLOSE_TO);
////                    break;
////            }
//
//            _way_myship_prev = GameGlobal::_pMyShip->_way;
//        }
//
//
//        //座標に反映
//        if (GameGlobal::_pMyShip->_stc != VB_NEUTRAL_STC) {
//            _angVelo_Turn = 3500 + GameGlobal::_pMyShip->_pMover->_veloMv;
//            //動かそうとしていた！
//            _pMover->behave();
//        }
//    }
    _pRing_GeoHistory->next()->set(this);
}


//void MyOptionParent::setTerget(angle prm_angRz_Target, angle prm_angRy_Target) {
//    if (_pMover->getRzMvAngDistance(prm_angRz_Target, TURN_CLOSE_TO) > 0) {
//        _pMover->setRzMvAngVelo(_angVelo_Turn);
//    } else {
//        _pMover->setRzMvAngVelo(-1 * _angVelo_Turn);
//    }
//    if (_pMover->getRyMvAngDistance(prm_angRy_Target, TURN_CLOSE_TO) > 0) {
//        _pMover->setRyMvAngVelo(_angVelo_Turn);
//    } else {
//        _pMover->setRyMvAngVelo(-1 * _angVelo_Turn);
//    }
//    _pMover->setStopTarget_RzMvAng(prm_angRz_Target);
//    _pMover->setStopTarget_RyMvAng(prm_angRy_Target);
//}

MyOptionParent::~MyOptionParent() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}
