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

    MyOption* pMyOption01 = NEW MyOption("MY_OPTION01", 0, this);
    pMyOption01->_radiusPosition = 60000;
    pMyOption01->_veloMv = 2000;
    pMyOption01->_angExpanse = 0;
    pMyOption01->_angveloExpanse = 0;
    pMyOption01->_angPosition = 0;
    pMyOption01->setMaterialColor(1.0, 1.0, 1.0);
    addSubLast(pMyOption01);

    MyOption* pMyOption02 = NEW MyOption("MY_OPTION02", 1, this);
    pMyOption02->_radiusPosition = 60000;
    pMyOption02->_veloMv = 2000;
    pMyOption02->_angExpanse = 0;
    pMyOption02->_angveloExpanse = 0;
    pMyOption02->_angPosition = ANGLE90;
    pMyOption02->setMaterialColor(0.0, 1.0, 1.0);
    addSubLast(pMyOption02);

    MyOption* pMyOption03 = NEW MyOption("MY_OPTION03", 2, this);
    pMyOption03->_radiusPosition = 60000;
    pMyOption03->_veloMv = 2000;
    pMyOption03->_angExpanse = 0;
    pMyOption03->_angveloExpanse = 0;
    pMyOption03->_angPosition = ANGLE180;
    pMyOption03->setMaterialColor(1.0, 0, 1.0);
    addSubLast(pMyOption03);

    MyOption* pMyOption04 = NEW MyOption("MY_OPTION04", 4, this);
    pMyOption04->_radiusPosition = 60000;
    pMyOption04->_veloMv = 2000;
    pMyOption04->_angExpanse = 0;
    pMyOption04->_angveloExpanse = 0;
    pMyOption04->_angPosition = ANGLE270;
    pMyOption04->setMaterialColor(0, 1.0, 0);
    addSubLast(pMyOption04);

    MyOption* pMyOption05 = NEW MyOption("MY_OPTION05", 5, this);
    pMyOption05->_radiusPosition = 120000;
    pMyOption05->_angPosition = 0;
    pMyOption05->_angExpanse = 0;
    pMyOption05->_angveloExpanse = 0;
    pMyOption05->_veloMv = -3000;
    pMyOption05->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 0, 1.0, 1.0);
    addSubLast(pMyOption05);

    MyOption* pMyOption06 = NEW MyOption("MY_OPTION06", 6, this);
    pMyOption06->_radiusPosition = 120000;
    pMyOption06->_angPosition = ANGLE90;
    pMyOption06->_angExpanse = 0;
    pMyOption06->_angveloExpanse = 0;
    pMyOption06->_veloMv = -3000;
    pMyOption06->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 1.0, 0, 1.0);
    addSubLast(pMyOption06);

    MyOption* pMyOption07 = NEW MyOption("MY_OPTION07", 7, this);
    pMyOption07->_radiusPosition = 120000;
    pMyOption07->_angPosition = ANGLE180;
    pMyOption07->_angExpanse = 0;
    pMyOption07->_angveloExpanse = 0;
    pMyOption07->_veloMv = -3000;
    pMyOption07->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0, 0, 1.0);
    addSubLast(pMyOption07);

    MyOption* pMyOption08 = NEW MyOption("MY_OPTION08", 8, this);
    pMyOption08->_radiusPosition = 120000;
    pMyOption08->_angPosition = ANGLE270;
    pMyOption08->_angExpanse = 0;
    pMyOption08->_angveloExpanse = 0;
    pMyOption08->_veloMv = -3000;
    pMyOption08->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
    pMyOption08->setAlpha(0.3);
    addSubLast(pMyOption08);

//    MyOption* pMyOption09 = NEW MyOption("MY_OPTION09", 9, this);
//    pMyOption09->_radiusPosition = 180000;
//    pMyOption09->_angPosition = 0;
//    pMyOption09->_angExpanse = 0;
//    pMyOption09->_angveloExpanse = 0;
//    pMyOption09->_veloMv = 4000;
//    addSubLast(pMyOption09);
//
//    MyOption* pMyOption10 = NEW MyOption("MY_OPTION10",10, this);
//    pMyOption10->_radiusPosition = 180000;
//    pMyOption10->_angPosition = ANGLE90;
//    pMyOption10->_angExpanse = 0;
//    pMyOption10->_angveloExpanse = 0;
//    pMyOption10->_veloMv = 4000;
//    addSubLast(pMyOption10);
//
//    MyOption* pMyOption11 = NEW MyOption("MY_OPTION11",11, this);
//    pMyOption11->_radiusPosition = 180000;
//    pMyOption11->_angPosition = ANGLE180;
//    pMyOption11->_angExpanse = 0;
//    pMyOption11->_angveloExpanse = 0;
//    pMyOption11->_veloMv = 4000;
//    addSubLast(pMyOption11);
//
//    MyOption* pMyOption12 = NEW MyOption("MY_OPTION12",12, this);
//    pMyOption12->_radiusPosition = 180000;
//    pMyOption12->_angPosition = ANGLE270;
//    pMyOption12->_angExpanse = 0;
//    pMyOption12->_angveloExpanse = 0;
//    pMyOption12->_veloMv = 4000;
//    addSubLast(pMyOption12);

    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }
    _is_rotate = false;
}

void MyOptionParent::initialize() {
    _pMover->setMvVelo(0);
    _pMover->forceRyMvAngVeloRange(-1*_angVelo_Turn, _angVelo_Turn);
    _pMover->forceRzMvAngVeloRange(-1*_angVelo_Turn, _angVelo_Turn);
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

    if (_is_rotate) {
        _pMover->execTagettingMvAngSequence(
                        GameGlobal::_pMyShip->_pMover->_angRzMv,
                        GameGlobal::_pMyShip->_pMover->_angRyMv,
                        3000, 0,
                        TURN_CLOSE_TO
                 );
    } else {
        _pMover->execTagettingMvAngSequence(
                        0,
                        0,
                        300, 0,
                        TURN_CLOSE_TO
                 );
    }

    if (pMYSHIP->_way != WAY_NONE && VB::isBeingPressed(VB_OPTION)) {
        _pMover->behave();
    } else {
        _pMover->behave();
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
