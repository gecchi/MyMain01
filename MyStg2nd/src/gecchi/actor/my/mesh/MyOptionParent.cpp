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

    _angVelocity_Turn = 3000;

    MyDummyOption* pMyDummyOption01 = NEW MyDummyOption("MY_OPTION01", 0, this);
    pMyDummyOption01->_radiusPosition = 120000;
    pMyDummyOption01->_veloMove = 6000;
    pMyDummyOption01->_angExpanse = 0;
    pMyDummyOption01->_angveloExpanse = 0;
    pMyDummyOption01->_angPosition = 0;
    pMyDummyOption01->setMaterialColor(1.0, 1.0, 1.0);
    addSubLast(pMyDummyOption01);

    MyDummyOption* pMyDummyOption02 = NEW MyDummyOption("MY_OPTION02", 1, this);
    pMyDummyOption02->_radiusPosition = 120000;
    pMyDummyOption02->_veloMove = 6000;
    pMyDummyOption02->_angExpanse = 0;
    pMyDummyOption02->_angveloExpanse = 0;
    pMyDummyOption02->_angPosition = ANGLE90;
    pMyDummyOption02->setMaterialColor(0.0, 1.0, 1.0);
    addSubLast(pMyDummyOption02);

    MyDummyOption* pMyDummyOption03 = NEW MyDummyOption("MY_OPTION03", 2, this);
    pMyDummyOption03->_radiusPosition = 120000;
    pMyDummyOption03->_veloMove = 6000;
    pMyDummyOption03->_angExpanse = 0;
    pMyDummyOption03->_angveloExpanse = 0;
    pMyDummyOption03->_angPosition = ANGLE180;
    pMyDummyOption03->setMaterialColor(1.0, 0, 1.0);
    addSubLast(pMyDummyOption03);

    MyDummyOption* pMyDummyOption04 = NEW MyDummyOption("MY_OPTION04", 4, this);
    pMyDummyOption04->_radiusPosition = 120000;
    pMyDummyOption04->_veloMove = 6000;
    pMyDummyOption04->_angExpanse = 0;
    pMyDummyOption04->_angveloExpanse = 0;
    pMyDummyOption04->_angPosition = ANGLE270;
    pMyDummyOption04->setMaterialColor(0, 1.0, 0);
    addSubLast(pMyDummyOption04);

//    MyDummyOption* pMyDummyOption05 = NEW MyDummyOption("MY_OPTION05", 5, this);
//    pMyDummyOption05->_radiusPosition = 200000;
//    pMyDummyOption05->_angPosition = 0;
//    pMyDummyOption05->_angExpanse = 0;
//    pMyDummyOption05->_angveloExpanse = 0;
//    pMyDummyOption05->_veloMove = -7000;
//    pMyDummyOption05->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 0, 1.0, 1.0);
//    addSubLast(pMyDummyOption05);
//
//    MyDummyOption* pMyDummyOption06 = NEW MyDummyOption("MY_OPTION06", 6, this);
//    pMyDummyOption06->_radiusPosition = 200000;
//    pMyDummyOption06->_angPosition = ANGLE90;
//    pMyDummyOption06->_angExpanse = 0;
//    pMyDummyOption06->_angveloExpanse = 0;
//    pMyDummyOption06->_veloMove = -7000;
//    pMyDummyOption06->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 1.0, 0, 1.0);
//    addSubLast(pMyDummyOption06);
//
//    MyDummyOption* pMyDummyOption07 = NEW MyDummyOption("MY_OPTION07", 7, this);
//    pMyDummyOption07->_radiusPosition = 200000;
//    pMyDummyOption07->_angPosition = ANGLE180;
//    pMyDummyOption07->_angExpanse = 0;
//    pMyDummyOption07->_angveloExpanse = 0;
//    pMyDummyOption07->_veloMove = -7000;
//    pMyDummyOption07->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0, 0, 1.0);
//    addSubLast(pMyDummyOption07);
//
//    MyDummyOption* pMyDummyOption08 = NEW MyDummyOption("MY_OPTION08", 8, this);
//    pMyDummyOption08->_radiusPosition = 200000;
//    pMyDummyOption08->_angPosition = ANGLE270;
//    pMyDummyOption08->_angExpanse = 0;
//    pMyDummyOption08->_angveloExpanse = 0;
//    pMyDummyOption08->_veloMove = -7000;
//    pMyDummyOption08->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
//    pMyDummyOption08->setAlpha(0.3);
//    addSubLast(pMyDummyOption08);

//    MyDummyOption* pMyDummyOption09 = NEW MyDummyOption("MY_OPTION09", 9, this);
//    pMyDummyOption09->_radiusPosition = 280000;
//    pMyDummyOption09->_angPosition = 0;
//    pMyDummyOption09->_angExpanse = 0;
//    pMyDummyOption09->_angveloExpanse = 0;
//    pMyDummyOption09->_veloMove = 8000;
//    addSubLast(pMyDummyOption09);
//
//    MyDummyOption* pMyDummyOption10 = NEW MyDummyOption("MY_OPTION10",10, this);
//    pMyDummyOption10->_radiusPosition = 280000;
//    pMyDummyOption10->_angPosition = ANGLE90;
//    pMyDummyOption10->_angExpanse = 0;
//    pMyDummyOption10->_angveloExpanse = 0;
//    pMyDummyOption10->_veloMove = 8000;
//    addSubLast(pMyDummyOption10);
//
//    MyDummyOption* pMyDummyOption11 = NEW MyDummyOption("MY_OPTION11",11, this);
//    pMyDummyOption11->_radiusPosition = 280000;
//    pMyDummyOption11->_angPosition = ANGLE180;
//    pMyDummyOption11->_angExpanse = 0;
//    pMyDummyOption11->_angveloExpanse = 0;
//    pMyDummyOption11->_veloMove = 8000;
//    addSubLast(pMyDummyOption11);
//
//    MyDummyOption* pMyDummyOption12 = NEW MyDummyOption("MY_OPTION12",12, this);
//    pMyDummyOption12->_radiusPosition = 280000;
//    pMyDummyOption12->_angPosition = ANGLE270;
//    pMyDummyOption12->_angExpanse = 0;
//    pMyDummyOption12->_angveloExpanse = 0;
//    pMyDummyOption12->_veloMove = 8000;
//    addSubLast(pMyDummyOption12);

    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }
}

void MyOptionParent::initialize() {
    _pMover->setMoveVelocity(0);
    _pMover->setRyMoveAngleVeloRenge(-1*_angVelocity_Turn, _angVelocity_Turn);
    _pMover->setRzMoveAngleVeloRenge(-1*_angVelocity_Turn, _angVelocity_Turn);
    _pMover->setRzRyMoveAngle(0,0);
    _way_myship_prev = GameGlobal::_pMyShip->_way;
    _pMover->behave();
}

void MyOptionParent::processBehavior() {
//    _X = GameGlobal::_pMyShip->_X;
//    _Y = GameGlobal::_pMyShip->_Y;
//    _Z = GameGlobal::_pMyShip->_Z;

    if (VB::isBeingPressed(VB_OPTION)) {
        if (_way_myship_prev != GameGlobal::_pMyShip->_way) {

            //方向が変わった
            _pMover->relateRzRyFaceAngleToMoveAngle(true);
            _pMover->executeTagettingMoveAngleSequence(
                            GameGlobal::_pMyShip->_pMover->_angTargetRzMove,
                            GameGlobal::_pMyShip->_pMover->_angTargetRyMove,
                            _angVelocity_Turn,
                            TURN_CLOSE_TO
                     );

//            switch(GameGlobal::_pMyShip->_way) {
//
//
//
//                case WAY_UP:
//                    if (pWORLD->_pos_camera == CAM_POS_RIGHT || pWORLD->_pos_camera == CAM_POS_LEFT) {
//                        _pMover->executeTagettingMoveAngleSequence(ANGLE90, 0,
//                                                                   _angVelocity_Turn, TURN_CLOSE_TO);
//                    } else {
//                        _pMover->executeTagettingMoveAngleSequence(ANGLE90, ANGLE90,
//                                                                   _angVelocity_Turn, TURN_CLOSE_TO);
//                    }
//                    break;
//                case WAY_UP_FRONT:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE45, 0,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//                case WAY_UP_BEHIND:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE135, 0,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//                case WAY_DOWN:
//                    if (pWORLD->_pos_camera == CAM_POS_RIGHT || pWORLD->_pos_camera == CAM_POS_LEFT) {
//                        _pMover->executeTagettingMoveAngleSequence(ANGLE270, 0,
//                                                                   _angVelocity_Turn, TURN_CLOSE_TO);
//                    } else {
//                        _pMover->executeTagettingMoveAngleSequence(ANGLE270, ANGLE90,
//                                                                   _angVelocity_Turn, TURN_CLOSE_TO);
//                    }
//                    break;
//                case WAY_DOWN_FRONT:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE315, 0,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//                case WAY_DOWN_BEHIND:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE225, 0,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//                case WAY_FRONT:
//                    _pMover->executeTagettingMoveAngleSequence(0, 0,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//                case WAY_BEHIND:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE180, 0,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    //            _pMover->setStopTarget_RzMoveAngle(0);
//                    //            _pMover->setStopTarget_RyMoveAngle(ANGLE180);
//
//                    break;
//                case WAY_ZLEFT:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE180, ANGLE90,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//
//                case WAY_ZLEFT_UP:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE135, ANGLE90,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//                case WAY_ZLEFT_DOWN:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE225, ANGLE90,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//
//                case WAY_ZLEFT_FRONT:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE180, ANGLE135,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//                case WAY_ZLEFT_BEHIND:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE180, ANGLE45,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//
//
//                case WAY_ZRIGHT:
//                    _pMover->executeTagettingMoveAngleSequence(0, ANGLE90
//                                                               , _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//                case WAY_ZRIGHT_UP:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE45, ANGLE90,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//                case WAY_ZRIGHT_DOWN:
//                    _pMover->executeTagettingMoveAngleSequence(ANGLE315, ANGLE90,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//
//                case WAY_ZRIGHT_FRONT:
//                    _pMover->executeTagettingMoveAngleSequence(0, ANGLE45,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//                case WAY_ZRIGHT_BEHIND:
//                    _pMover->executeTagettingMoveAngleSequence(0, ANGLE135,
//                                                               _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//                default:
//                    //_pMover->executeTagettingMoveAngleSequence(0, 0, _angVelocity_Turn, TURN_CLOSE_TO);
//                    break;
//            }

            _way_myship_prev = GameGlobal::_pMyShip->_way;
        }


        //座標に反映
        if (GameGlobal::_pMyShip->_stc != VB_NEUTRAL_STC) {
            _angVelocity_Turn = 3500 + GameGlobal::_pMyShip->_pMover->_veloMove;
            //動かそうとしていた！
            _pMover->behave();
        }
    }
    _pRing_GeoHistory->next()->set(this);
}


//void MyOptionParent::setTerget(angle prm_angRz_Target, angle prm_angRy_Target) {
//    if (_pMover->getRzMoveAngleDistance(prm_angRz_Target, TURN_CLOSE_TO) > 0) {
//        _pMover->setRzMoveAngleVelocity(_angVelocity_Turn);
//    } else {
//        _pMover->setRzMoveAngleVelocity(-1 * _angVelocity_Turn);
//    }
//    if (_pMover->getRyMoveAngleDistance(prm_angRy_Target, TURN_CLOSE_TO) > 0) {
//        _pMover->setRyMoveAngleVelocity(_angVelocity_Turn);
//    } else {
//        _pMover->setRyMoveAngleVelocity(-1 * _angVelocity_Turn);
//    }
//    _pMover->setStopTarget_RzMoveAngle(prm_angRz_Target);
//    _pMover->setStopTarget_RyMoveAngle(prm_angRy_Target);
//}

MyOptionParent::~MyOptionParent() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}
