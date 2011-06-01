#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;
int MyOptionController::_max_option_num = 8;

//MyOptionController::MyOptionController(const char* prm_name) :
//    DefaultMeshActor(prm_name, "Gizmo") {

MyOptionController::MyOptionController(const char* prm_name) :
  GgafDx9GeometricActor(prm_name,
                            NULL) {
    _is_handle_move_mode = false;
    _is_free_from_myship_mode = false;
    _return_to_default_position_seq = false;
    _angVelo_Turn = 3000;
    _veloOptionsMv = 20000;

    _now_option_num = 0;

    _renge = 80000;
    
    //_pMvTransporter->forceVxMvVeloRange(-_renge, _renge);
    //_pMvTransporter->forceVyMvVeloRange(-_renge, _renge);
    //_pMvTransporter->forceVzMvVeloRange(-_renge, _renge);

    //_pMvTransporter->forceVxMvAcceRange(-_renge / 30, _renge / 30);
    //_pMvTransporter->forceVyMvAcceRange(-_renge / 30, _renge / 30);
    //_pMvTransporter->forceVzMvAcceRange(-_renge / 30, _renge / 30);

    _papMyOption = NEW MyOption*[_max_option_num];
    for (int i = 0; i < _max_option_num; i++) {
        _papMyOption[i] = NULL;
    }

    _papMyOption[0] = NEW MyOption("MY_OPTION01", 0, this);
    _papMyOption[0]->config(60000, ANGLE0, 0, 1000);
    _papMyOption[0]->setMaterialColor(1.0, 1.0, 1.0);
    _papMyOption[0]->setAlpha(0.7);
    addSubGroup(_papMyOption[0]);

    _papMyOption[1] = NEW MyOption("MY_OPTION02", 1, this);
    _papMyOption[1]->config(60000, ANGLE90, 0, 1000);
    _papMyOption[1]->setMaterialColor(0.8, 1.0, 1.0);
    _papMyOption[1]->setAlpha(0.7);
    addSubGroup(_papMyOption[1]);

    _papMyOption[2] = NEW MyOption("MY_OPTION03", 2, this);
    _papMyOption[2]->config(60000, ANGLE180, 0, 1000);
    _papMyOption[2]->setMaterialColor(1.0, 0.8, 0.8);
    _papMyOption[2]->setAlpha(0.7);
    addSubGroup(_papMyOption[2]);

    _papMyOption[3] = NEW MyOption("MY_OPTION04", 3, this);
    _papMyOption[3]->config(60000, ANGLE270, 0, 1000);
    _papMyOption[3]->setMaterialColor(0.8, 1.0, 0.8);
    _papMyOption[3]->setAlpha(0.7);
    addSubGroup(_papMyOption[3]);

    _papMyOption[4] = NEW MyOption("MY_OPTION05", 4, this);
    _papMyOption[4]->config(120000, ANGLE0, 0, -1500);
    _papMyOption[4]->setMaterialColor(0.8, 0.8, 1.0);
    _papMyOption[4]->setAlpha(0.7);
    addSubGroup(_papMyOption[4]);

    _papMyOption[5] = NEW MyOption("MY_OPTION06", 5, this);
    _papMyOption[5]->config(120000, ANGLE90, 0, -1500);
    _papMyOption[5]->setMaterialColor(0.8, 1.0, 0.8);
    _papMyOption[5]->setAlpha(0.7);
    addSubGroup(_papMyOption[5]);

    _papMyOption[6] = NEW MyOption("MY_OPTION07", 6, this);
    _papMyOption[6]->config(120000, ANGLE180, 0, -1500);
    _papMyOption[6]->setMaterialColor(1.0, 0.8, 0);
    _papMyOption[6]->setAlpha(0.7);
    addSubGroup(_papMyOption[6]);

    _papMyOption[7] = NEW MyOption("MY_OPTION08", 7, this);
    _papMyOption[7]->config(120000, ANGLE270, 0, -1500);
    _papMyOption[7]->setMaterialColor(1.0, 1.0, 1.0);
    _papMyOption[7]->setAlpha(0.7);
    addSubGroup(_papMyOption[7]);

    for (int i = 0; i < _max_option_num; i++) {
        _papMyOption[i]->inactivateImmediately();
    }


    for (int i = 0; i < _now_option_num; i++) {
        _papMyOption[i]->activate();
    }

    //ギズモ
    _pGizmo = NEW MyOptionControllerGizmo("MyPGizmo");
    addSubGroup(_pGizmo);
    //方向ベクトル
    _pDirectionVector = NEW MyOptionControllerDirectionVector("MyPDirectionVector");
    addSubGroup(_pDirectionVector);

    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GgafDx9GeoElem>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GgafDx9GeoElem(this));
    }

}


void MyOptionController::initialize() {
}


void MyOptionController::onReset() {
    _pMvNavigator->setMvVelo(0);
    _pMvNavigator->forceRyMvAngVeloRange(-1*_angVelo_Turn, _angVelo_Turn);
    _pMvNavigator->forceRzMvAngVeloRange(-1*_angVelo_Turn, _angVelo_Turn);
    _pMvNavigator->setRzRyMvAng(0,0);
    _way_myship_prev = P_MYSHIP->_way;
    _pMvNavigator->relateRzRyFaceAngToMvAng(true);
    _pMvNavigator->behave();
}

void MyOptionController::onActive() {
    reset();
}

void MyOptionController::processBehavior() {
//    if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
//        dump();
//    }


    if (VB_PLAY->isDoublePushedDown(VB_OPTION,8,8)) {
        //もとに戻す
        _pMvNavigator->orderTagettingMvAngSequence(
                        0,
                        0,
                        20000, 0,
                        TURN_CLOSE_TO,
                        false
                 );
        _is_free_from_myship_mode = false;
        _is_handle_move_mode = false;
        _return_to_default_position_seq = true;
        adjustDefaltAngPosition(60);
        for (int i = 0; i < _now_option_num; i++) {
            //オプションの半径位置を元に戻す指示
            _papMyOption[i]->_return_to_base_radiusPosition_seq = true;
            _papMyOption[i]->_return_to_base_angExpanse_seq= true;
        }


    } else if (VB_PLAY->isBeingPressed(VB_OPTION) && !VB_PLAY->isBeingPressed(VB_TURBO)) {
        //オプション向き操作
        if (VB_PLAY->isBeingPressed(VB_UP)) {
            _pMvNavigator->addRzMvAng(_angVelo_Turn);
        }
        if (VB_PLAY->isBeingPressed(VB_DOWN)) {
            _pMvNavigator->addRzMvAng(-_angVelo_Turn);
        }
        if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
            _pMvNavigator->addRyMvAng(_angVelo_Turn);
        }
        if (VB_PLAY->isBeingPressed(VB_LEFT)) {
            _pMvNavigator->addRyMvAng(-_angVelo_Turn);
        }

    }

    if (VB_PLAY->isPushedDown(VB_OPTION)) {
        if (VB_PLAY->isRoundPushDown(VB_OPTION)) {
        //if (VB_PLAY->isPushedDown(VB_OPTION) && GgafDx9Input::isBeingPressedKey(DIK_S)) {
            if (_papMyOption[0]) {
                _is_free_from_myship_mode = true;
                _is_handle_move_mode = true;
                _pMvTransporter->setVxMvAcce(0);
                _pMvTransporter->setVyMvAcce(0);
                _pMvTransporter->setVzMvAcce(0);
                _pMvTransporter->setVxMvVelo(0);
                _pMvTransporter->setVyMvVelo(0);
                _pMvTransporter->setVzMvVelo(0);

            }
        }
    }

    if (_is_free_from_myship_mode) {
        if (VB_PLAY->isBeingPressed(VB_OPTION) && _is_handle_move_mode) {
            //オプションの広がり角より、オプション移動速度と、旋回半径増加速度にベクトル分解。
            //そのうちのオプション移動速度のみを設定。
            _pMvNavigator->setMvVelo(GgafDx9Util::COS[_papMyOption[0]->_angExpanse/ ANGLE_RATE] * _veloOptionsMv);
            //旋回半径増加速度の処理はMyOptionクラスで行う。
        } else {
            _is_handle_move_mode = false;
            _pMvNavigator->setMvVelo(0);
        }
    } else {
        GgafDx9GeoElem* pGeoMyShip = P_MYSHIP->_pRing_GeoHistory->getPrev(4); //自機にすこしおくれて追従
        if (_return_to_default_position_seq) {
            //元の位置へ
            int dx = pGeoMyShip->_X - (_X + _pMvTransporter->_veloVxMv*6);
            int dy = pGeoMyShip->_Y - (_Y + _pMvTransporter->_veloVyMv*6);
            int dz = pGeoMyShip->_Z - (_Z + _pMvTransporter->_veloVzMv*6);
            _pMvTransporter->setVxMvAcce(dx);
            _pMvTransporter->setVyMvAcce(dy);
            _pMvTransporter->setVzMvAcce(dz);
            if (abs(_X - pGeoMyShip->_X) < 10000 &&
                abs(_Y - pGeoMyShip->_Y) < 10000 &&
                abs(_Z - pGeoMyShip->_Z) < 10000 &&
                abs(_pMvTransporter->_veloVxMv) < 20000 &&
                abs(_pMvTransporter->_veloVyMv) < 20000 &&
                abs(_pMvTransporter->_veloVzMv) < 20000    ) {

                _TRACE_("もどった！");
                _pMvTransporter->setVxMvVelo(0);
                _pMvTransporter->setVyMvVelo(0);
                _pMvTransporter->setVzMvVelo(0);
                _pMvTransporter->setVxMvAcce(0);
                _pMvTransporter->setVyMvAcce(0);
                _pMvTransporter->setVzMvAcce(0);
                locateAs(pGeoMyShip);
                _return_to_default_position_seq = false;
            }

        } else {
            locateAs(pGeoMyShip);
        }
    }


    //ギズモ
    _pDirectionVector->locateAs(this);
    _pDirectionVector->_pMvNavigator->setRzRyMvAng(_pMvNavigator->_angRzMv, _pMvNavigator->_angRyMv);

    _pMvNavigator->behave();
    _pMvTransporter->behave();
    _pRing_GeoHistory->next()->set(this);
}

void MyOptionController::setNumOption(int prm_num) {
    _now_option_num = prm_num;
    for (int i = 0; i < _max_option_num; i++) {
        if (i >= _now_option_num) {
            _papMyOption[i]->inactivate();
        }
        if (i < _now_option_num) {
            _papMyOption[i]->activate();
        }
    }
}

void MyOptionController::adjustDefaltAngPosition(frame prm_spent_frame) {
    if (_now_option_num <= 4) {
        for (int i = 0; i < _now_option_num; i++) {
            _papMyOption[i]->adjustAngPosition((ANGLE360/_now_option_num)*i,prm_spent_frame);
        }
    } else if (_now_option_num > 4) {
        for (int i = 0; i < 4; i++) {
            _papMyOption[i]->adjustAngPosition((ANGLE360/4)*i, prm_spent_frame);
        }
        for (int i = 4; i < _now_option_num; i++) {
            _papMyOption[i]->adjustAngPosition((ANGLE360/(_now_option_num-4))*(i-4), prm_spent_frame);
        }
    }
}
MyOptionController::~MyOptionController() {
    DELETEARR_IMPOSSIBLE_NULL(_papMyOption);
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}

