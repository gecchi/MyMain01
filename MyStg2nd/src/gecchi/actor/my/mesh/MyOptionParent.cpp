#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyOptionParent::MyOptionParent(const char* prm_name) :
    DefaultMeshActor(prm_name, "myvic") {

//MyOptionParent::MyOptionParent(const char* prm_name) :
//  GgafDx9GeometricActor(prm_name,
//                            NULL) {

    _angVelo_Turn = 3000;
    _angMyOptionExpanse = 0;
    _angveloMyOptionExpanseNomal = 3000;
    _angveloMyOptionExpanseSlow = 1000;

    _paMyOption[0] = NEW MyOption("MY_OPTION01", 0, this);
    _paMyOption[0]->_radiusPosition = 60000;
    _paMyOption[0]->_veloMv = 1000;
    _paMyOption[0]->_angExpanse = 0;
    _paMyOption[0]->_angveloExpanse = 0;
    _paMyOption[0]->_angPosition = 0;
    _paMyOption[0]->setMaterialColor(1.0, 1.0, 1.0);
    addSubLast(_paMyOption[0]);

    _paMyOption[1] = NEW MyOption("MY_OPTION02", 1, this);
    _paMyOption[1]->_radiusPosition = 60000;
    _paMyOption[1]->_veloMv = 1000;
    _paMyOption[1]->_angExpanse = 0;
    _paMyOption[1]->_angveloExpanse = 0;
    _paMyOption[1]->_angPosition = ANGLE90;
    _paMyOption[1]->setMaterialColor(0.0, 1.0, 1.0);
    addSubLast(_paMyOption[1]);

    _paMyOption[2] = NEW MyOption("MY_OPTION03", 2, this);
    _paMyOption[2]->_radiusPosition = 60000;
    _paMyOption[2]->_veloMv = 1000;
    _paMyOption[2]->_angExpanse = 0;
    _paMyOption[2]->_angveloExpanse = 0;
    _paMyOption[2]->_angPosition = ANGLE180;
    _paMyOption[2]->setMaterialColor(1.0, 0, 1.0);
    addSubLast(_paMyOption[2]);

    _paMyOption[3] = NEW MyOption("MY_OPTION04", 4, this);
    _paMyOption[3]->_radiusPosition = 60000;
    _paMyOption[3]->_veloMv = 1000;
    _paMyOption[3]->_angExpanse = 0;
    _paMyOption[3]->_angveloExpanse = 0;
    _paMyOption[3]->_angPosition = ANGLE270;
    _paMyOption[3]->setMaterialColor(0, 1.0, 0);
    addSubLast(_paMyOption[3]);

    _paMyOption[4] = NEW MyOption("MY_OPTION05", 5, this);
    _paMyOption[4]->_radiusPosition = 120000;
    _paMyOption[4]->_angPosition = 0;
    _paMyOption[4]->_angExpanse = 0;
    _paMyOption[4]->_angveloExpanse = 0;
    _paMyOption[4]->_veloMv = -1000;
    _paMyOption[4]->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 0, 1.0, 1.0);
    addSubLast(_paMyOption[4]);

    _paMyOption[5] = NEW MyOption("MY_OPTION06", 6, this);
    _paMyOption[5]->_radiusPosition = 120000;
    _paMyOption[5]->_angPosition = ANGLE90;
    _paMyOption[5]->_angExpanse = 0;
    _paMyOption[5]->_angveloExpanse = 0;
    _paMyOption[5]->_veloMv = -1000;
    _paMyOption[5]->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 1.0, 0, 1.0);
    addSubLast(_paMyOption[5]);

    _paMyOption[6] = NEW MyOption("MY_OPTION07", 7, this);
    _paMyOption[6]->_radiusPosition = 120000;
    _paMyOption[6]->_angPosition = ANGLE180;
    _paMyOption[6]->_angExpanse = 0;
    _paMyOption[6]->_angveloExpanse = 0;
    _paMyOption[6]->_veloMv = -1000;
    _paMyOption[6]->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0, 0, 1.0);
    addSubLast(_paMyOption[6]);

    _paMyOption[7] = NEW MyOption("MY_OPTION08", 8, this);
    _paMyOption[7]->_radiusPosition = 120000;
    _paMyOption[7]->_angPosition = ANGLE270;
    _paMyOption[7]->_angExpanse = 0;
    _paMyOption[7]->_angveloExpanse = 0;
    _paMyOption[7]->_veloMv = -1000;
    _paMyOption[7]->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
    _paMyOption[7]->setAlpha(0.3);
    addSubLast(_paMyOption[7]);

//    MyOption* _paMyOption[8] = NEW MyOption("MY_OPTION09", 9, this);
//    _paMyOption[8]->_radiusPosition = 180000;
//    _paMyOption[8]->_angPosition = 0;
//    _paMyOption[8]->_angExpanse = 0;
//    _paMyOption[8]->_angveloExpanse = 0;
//    _paMyOption[8]->_veloMv = 4000;
//    addSubLast(_paMyOption[8]);
//
//    MyOption* _paMyOption[9] = NEW MyOption("MY_OPTION10",10, this);
//    _paMyOption[9]->_radiusPosition = 180000;
//    _paMyOption[9]->_angPosition = ANGLE90;
//    _paMyOption[9]->_angExpanse = 0;
//    _paMyOption[9]->_angveloExpanse = 0;
//    _paMyOption[9]->_veloMv = 4000;
//    addSubLast(_paMyOption[9]);
//
//    MyOption* _paMyOption[10] = NEW MyOption("MY_OPTION11",11, this);
//    _paMyOption[10]->_radiusPosition = 180000;
//    _paMyOption[10]->_angPosition = ANGLE180;
//    _paMyOption[10]->_angExpanse = 0;
//    _paMyOption[10]->_angveloExpanse = 0;
//    _paMyOption[10]->_veloMv = 4000;
//    addSubLast(_paMyOption[10]);
//
//    MyOption* _paMyOption[11] = NEW MyOption("MY_OPTION12",12, this);
//    _paMyOption[11]->_radiusPosition = 180000;
//    _paMyOption[11]->_angPosition = ANGLE270;
//    _paMyOption[11]->_angExpanse = 0;
//    _paMyOption[11]->_angveloExpanse = 0;
//    _paMyOption[11]->_veloMv = 4000;
//    addSubLast(_paMyOption[11]);

    for (int i = 0; i < 8; i++) {
        _paMyOption[i]->activate();
    }


    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }
    _is_rotate = false;

    int d = 1000;
    int CAM_POS_BEHIND = 0;
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
    //方向が変わった


    if (VB::isBeingPressed(VB_OPTION) && VB::isBeingPressed(VB_TURBO)) {
        //オプション広がり
        if (pWORLD->_pos_camera == CAM_POS_RIGHT) {
            if (VB::isBeingPressed(VB_RIGHT)) {
                _angMyOptionExpanse += _angveloMyOptionExpanseNomal;
            }
            if (VB::isBeingPressed(VB_LEFT)) {
                _angMyOptionExpanse -= _angveloMyOptionExpanseNomal;
            }
            if (VB::isBeingPressed(VB_UP)) {
                _angMyOptionExpanse += _angveloMyOptionExpanseSlow;
            }
            if (VB::isBeingPressed(VB_DOWN)) {
                _angMyOptionExpanse -= _angveloMyOptionExpanseSlow;
            }
        } else if (pWORLD->_pos_camera == CAM_POS_LEFT) {
            if (VB::isBeingPressed(VB_RIGHT)) {
                _angMyOptionExpanse -= _angveloMyOptionExpanseNomal;
            }
            if (VB::isBeingPressed(VB_LEFT)) {
                _angMyOptionExpanse += _angveloMyOptionExpanseNomal;
            }
            if (VB::isBeingPressed(VB_UP)) {
                _angMyOptionExpanse += _angveloMyOptionExpanseSlow;
            }
            if (VB::isBeingPressed(VB_DOWN)) {
                _angMyOptionExpanse -= _angveloMyOptionExpanseSlow;
            }
        } else if (pWORLD->_pos_camera == CAM_POS_TOP) {
            if (VB::isBeingPressed(VB_RIGHT)) {
                _angMyOptionExpanse += _angveloMyOptionExpanseSlow;
            }
            if (VB::isBeingPressed(VB_LEFT)) {
                _angMyOptionExpanse -= _angveloMyOptionExpanseSlow;
            }
            if (VB::isBeingPressed(VB_UP)) {
                _angMyOptionExpanse += _angveloMyOptionExpanseNomal;
            }
            if (VB::isBeingPressed(VB_DOWN)) {
                _angMyOptionExpanse -= _angveloMyOptionExpanseNomal;
            }
        } else if (pWORLD->_pos_camera == CAM_POS_BOTTOM) {
            if (VB::isBeingPressed(VB_RIGHT)) {
                _angMyOptionExpanse -= _angveloMyOptionExpanseSlow;
            }
            if (VB::isBeingPressed(VB_LEFT)) {
                _angMyOptionExpanse += _angveloMyOptionExpanseSlow;
            }
            if (VB::isBeingPressed(VB_UP)) {
                _angMyOptionExpanse -= _angveloMyOptionExpanseNomal;
            }
            if (VB::isBeingPressed(VB_DOWN)) {
                _angMyOptionExpanse += _angveloMyOptionExpanseNomal;
            }
        } else if (pWORLD->_pos_camera > CAM_POS_TO_BEHIND) {
            if (VB::isBeingPressed(VB_RIGHT)) {
                _angMyOptionExpanse += _angveloMyOptionExpanseSlow;
            }
            if (VB::isBeingPressed(VB_LEFT)) {
                _angMyOptionExpanse -= _angveloMyOptionExpanseSlow;
            }
            if (VB::isBeingPressed(VB_UP)) {
                _angMyOptionExpanse += _angveloMyOptionExpanseNomal;
            }
            if (VB::isBeingPressed(VB_DOWN)) {
                _angMyOptionExpanse -= _angveloMyOptionExpanseNomal;
            }
        }
        _angMyOptionExpanse = GgafDx9GeometryMover::simplifyAng(_angMyOptionExpanse);
        for (int i = 0; i < 8; i++) {
            _paMyOption[i]->_angExpanse = _angMyOptionExpanse;
        }
    } else {

        //オプション向き操作
        if (VB::isDoublePushedDown(VB_OPTION,8,8)) {
            //もとに戻す
            _pMover->execTagettingMvAngSequence(
                            0,
                            0,
                            5000, 0,
                            TURN_CLOSE_TO,
                            false
                     );
            _is_rotate = true;
        } else if (VB::isBeingPressed(VB_OPTION)) {

            if (VB::isBeingPressed(VB_UP)) {
                _pMover->addRzMvAng(_angVelo_Turn);
            }
            if (VB::isBeingPressed(VB_DOWN)) {
                _pMover->addRzMvAng(-_angVelo_Turn);
            }
            if (VB::isBeingPressed(VB_RIGHT)) {
                _pMover->addRyMvAng(_angVelo_Turn);
            }
            if (VB::isBeingPressed(VB_LEFT)) {
                _pMover->addRyMvAng(-_angVelo_Turn);
            }

        }
    }
    //_X = _X + 1000;
    setGeometry(pMYSHIP);
    _pMover->behave();
    _pRing_GeoHistory->next()->set(this);
}



MyOptionParent::~MyOptionParent() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}



bool MyOptionParent::isRoundPush(vbsta prm_VB, DWORD prm_frame_delay) {
    if (VB::isPushedDown(prm_VB)) {

        VB::VBMap* pVBMap;
        pVBMap = VB::_pVBMap_Active;
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        for (DWORD i = 0; i < prm_frame_delay; i++) {
            pVBMap = pVBMap->_prev;
            if (pVBMap->_state & VB_UP) {
                up = true;
                continue;
            }
            if (pVBMap->_state & VB_RIGHT) {
                right = true;
                continue;
            }
            if (pVBMap->_state & VB_DOWN) {
                down = true;
                continue;
            }
            if (pVBMap->_state & VB_LEFT) {
                up = left;
                continue;
            }
        }
        if (up && down && left && right) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }







}
