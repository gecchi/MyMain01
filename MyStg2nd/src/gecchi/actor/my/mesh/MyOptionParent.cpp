#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyOptionParent::MyOptionParent(const char* prm_name) :
    DefaultMeshActor(prm_name, "Gizmo") {

//MyOptionParent::MyOptionParent(const char* prm_name) :
//  GgafDx9GeometricActor(prm_name,
//                            NULL) {
    _is_handle_move_mode = false;
    _is_free_from_myship_mode = false;
    _angVelo_Turn = 3000;
    _veloOptionsMv = 5000;
    for (int i = 0; i < 8; i++) {
        _paMyOption[i] = NULL;
    }

    _paMyOption[0] = NEW MyOption("MY_OPTION01", 0, this);
    _paMyOption[0]->setProperty(60000, ANGLE0, 0, 1000);
    _paMyOption[0]->setMaterialColor(1.0, 1.0, 1.0);
    addSubLast(_paMyOption[0]);

    _paMyOption[1] = NEW MyOption("MY_OPTION02", 1, this);
    _paMyOption[1]->setProperty(60000, ANGLE90, 0, 1000);
    _paMyOption[1]->setMaterialColor(0.0, 1.0, 1.0);
    addSubLast(_paMyOption[1]);

    _paMyOption[2] = NEW MyOption("MY_OPTION03", 2, this);
    _paMyOption[2]->setProperty(60000, ANGLE180, 0, 1000);
    _paMyOption[2]->setMaterialColor(1.0, 0, 1.0);
    addSubLast(_paMyOption[2]);

    _paMyOption[3] = NEW MyOption("MY_OPTION04", 4, this);
    _paMyOption[3]->setProperty(60000, ANGLE270, 0, 1000);
    _paMyOption[3]->setMaterialColor(0, 1.0, 0);
    addSubLast(_paMyOption[3]);

    _paMyOption[4] = NEW MyOption("MY_OPTION05", 5, this);
    _paMyOption[4]->setProperty(120000, ANGLE0, 0, -1000);
    _paMyOption[4]->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 0, 1.0, 1.0);
    addSubLast(_paMyOption[4]);

    _paMyOption[5] = NEW MyOption("MY_OPTION06", 6, this);
    _paMyOption[5]->setProperty(120000, ANGLE90, 0, -1000);
    _paMyOption[5]->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(0, 1.0, 0, 1.0);
    addSubLast(_paMyOption[5]);

    _paMyOption[6] = NEW MyOption("MY_OPTION07", 7, this);
    _paMyOption[6]->setProperty(120000, ANGLE180, 0, -1000);
    _paMyOption[6]->_paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0, 0, 1.0);
    addSubLast(_paMyOption[6]);

    _paMyOption[7] = NEW MyOption("MY_OPTION08", 8, this);
    _paMyOption[7]->setProperty(120000, ANGLE270, 0, -1000);
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
//    _paMyOption[9]->_veloMv = 4000;
//    addSubLast(_paMyOption[9]);
//
//    MyOption* _paMyOption[10] = NEW MyOption("MY_OPTION11",11, this);
//    _paMyOption[10]->_radiusPosition = 180000;
//    _paMyOption[10]->_angPosition = ANGLE180;
//    _paMyOption[10]->_angExpanse = 0;
//    _paMyOption[10]->_veloMv = 4000;
//    addSubLast(_paMyOption[10]);
//
//    MyOption* _paMyOption[11] = NEW MyOption("MY_OPTION12",12, this);
//    _paMyOption[11]->_radiusPosition = 180000;
//    _paMyOption[11]->_angPosition = ANGLE270;
//    _paMyOption[11]->_angExpanse = 0;
//    _paMyOption[11]->_veloMv = 4000;
//    addSubLast(_paMyOption[11]);

    for (int i = 0; i < 8; i++) {
        _paMyOption[i]->activate();
    }


    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(pMYSHIP));
    }

}

void MyOptionParent::initialize() {

    _pMover->setMvVelo(0);
    _pMover->forceRyMvAngVeloRange(-1*_angVelo_Turn, _angVelo_Turn);
    _pMover->forceRzMvAngVeloRange(-1*_angVelo_Turn, _angVelo_Turn);
    _pMover->setRzRyMvAng(0,0);
    _way_myship_prev = pMYSHIP->_way;
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->behave();
}

void MyOptionParent::processBehavior() {

    if (VB::isDoublePushedDown(VB_OPTION,8,8)) {
        //もとに戻す
        _pMover->execTagettingMvAngSequence(
                        0,
                        0,
                        5000, 0,
                        TURN_CLOSE_TO,
                        false
                 );
        _is_free_from_myship_mode = false;
        _is_handle_move_mode = false;

    } else if (VB::isBeingPressed(VB_OPTION) && !VB::isBeingPressed(VB_TURBO)) {
        //オプション向き操作
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

    //if (VB::isRoundPush(VB_OPTION)) {
    if (VB::isPushedDown(VB_OPTION) && GgafDx9Input::isBeingPressedKey(DIK_S)) {
        if (_paMyOption[0]) {
            _is_free_from_myship_mode = true;
            _is_handle_move_mode = true;
        }
    }

    if (_is_free_from_myship_mode) {
        if (VB::isBeingPressed(VB_OPTION) && _is_handle_move_mode) {
            //オプションの広がり角より、オプション移動速度と、旋回半径増加速度にベクトル分解。
            //そのうちのオプション移動速度のみを設定。
            _pMover->setMvVelo(GgafDx9Util::COS[_paMyOption[0]->_angExpanse/ ANGLE_RATE] * _veloOptionsMv);
            //旋回半径増加速度の処理はMyOptionクラスで行う。
        } else {
            _is_handle_move_mode = false;
            _pMover->setMvVelo(0);
        }
    } else {
        setGeometry(pMYSHIP);
    }
    _pMover->behave();
    _pRing_GeoHistory->next()->set(this);
}



MyOptionParent::~MyOptionParent() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}

