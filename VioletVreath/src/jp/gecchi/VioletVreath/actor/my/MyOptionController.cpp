#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;
int MyOptionController::max_option_num_ = 8;
int MyOptionController::o2o_ = 15;
//MyOptionController::MyOptionController(const char* prm_name) :
//    DefaultMeshActor(prm_name, "Gizmo") {

MyOptionController::MyOptionController(const char* prm_name) :
  GgafDxGeometricActor(prm_name, NULL, NULL) {
    is_handle_move_mode_ = false;
    is_free_from_myship_mode_ = false;
    return_to_default_position_seq_ = false;
    angVelo_Turn_ = 3000;
    veloOptionsMv_ = 20000;

    now_option_num_ = 0;

    renge_ = 80000;

    _pKurokoB->forceVxMvVeloRange(-renge_, renge_);
    _pKurokoB->forceVyMvVeloRange(-renge_, renge_);
    _pKurokoB->forceVzMvVeloRange(-renge_, renge_);

    _pKurokoB->forceVxMvAcceRange(-renge_ / 30, renge_ / 30);
    _pKurokoB->forceVyMvAcceRange(-renge_ / 30, renge_ / 30);
    _pKurokoB->forceVzMvAcceRange(-renge_ / 30, renge_ / 30);

    papMyOption_ = NEW MyOption*[max_option_num_];
    for (int i = 0; i < max_option_num_; i++) {
        papMyOption_[i] = NULL;
    }

    papMyOption_[0] = NEW MyOption("MY_OPTION01", 0, this);
    papMyOption_[0]->config(60000, D0ANG, 0, 1000);
    papMyOption_[0]->setMaterialColor(1.0, 1.0, 1.0);
    papMyOption_[0]->setAlpha(0.7);
    addSubGroup(papMyOption_[0]);

    papMyOption_[1] = NEW MyOption("MY_OPTION02", 1, this);
    papMyOption_[1]->config(60000, D90ANG, 0, 1000);
    papMyOption_[1]->setMaterialColor(0.8, 1.0, 1.0);
    papMyOption_[1]->setAlpha(0.7);
    addSubGroup(papMyOption_[1]);

    papMyOption_[2] = NEW MyOption("MY_OPTION03", 2, this);
    papMyOption_[2]->config(60000, D180ANG, 0, 1000);
    papMyOption_[2]->setMaterialColor(1.0, 0.8, 0.8);
    papMyOption_[2]->setAlpha(0.7);
    addSubGroup(papMyOption_[2]);

    papMyOption_[3] = NEW MyOption("MY_OPTION04", 3, this);
    papMyOption_[3]->config(60000, D270ANG, 0, 1000);
    papMyOption_[3]->setMaterialColor(0.8, 1.0, 0.8);
    papMyOption_[3]->setAlpha(0.7);
    addSubGroup(papMyOption_[3]);

    papMyOption_[4] = NEW MyOption("MY_OPTION05", 4, this);
    papMyOption_[4]->config(120000, D0ANG, 0, -1500);
    papMyOption_[4]->setMaterialColor(0.8, 0.8, 1.0);
    papMyOption_[4]->setAlpha(0.7);
    addSubGroup(papMyOption_[4]);

    papMyOption_[5] = NEW MyOption("MY_OPTION06", 5, this);
    papMyOption_[5]->config(120000, D90ANG, 0, -1500);
    papMyOption_[5]->setMaterialColor(0.8, 1.0, 0.8);
    papMyOption_[5]->setAlpha(0.7);
    addSubGroup(papMyOption_[5]);

    papMyOption_[6] = NEW MyOption("MY_OPTION07", 6, this);
    papMyOption_[6]->config(120000, D180ANG, 0, -1500);
    papMyOption_[6]->setMaterialColor(1.0, 0.8, 0);
    papMyOption_[6]->setAlpha(0.7);
    addSubGroup(papMyOption_[6]);

    papMyOption_[7] = NEW MyOption("MY_OPTION08", 7, this);
    papMyOption_[7]->config(120000, D270ANG, 0, -1500);
    papMyOption_[7]->setMaterialColor(1.0, 1.0, 1.0);
    papMyOption_[7]->setAlpha(0.7);
    addSubGroup(papMyOption_[7]);

    for (int i = 0; i < max_option_num_; i++) {
        papMyOption_[i]->inactivateImmed();
    }


    for (int i = 0; i < now_option_num_; i++) {
        papMyOption_[i]->activate();
    }

    //ギズモ
    pGizmo_ = NEW MyOptionControllerGizmo("MyPGizmo");
    addSubGroup(pGizmo_);
    //方向ベクトル
    pDirectionVector_ = NEW MyOptionControllerDirectionVector("MyPDirectionVector");
    addSubGroup(pDirectionVector_);

    //トレース用履歴
    pRing_OpConGeoHistory_ = NEW GgafLinkedListRing<GgafDxGeoElem>();
    for (DWORD i = 0; i < max_option_num_*o2o_; i++) {
        pRing_OpConGeoHistory_->addLast(NEW GgafDxGeoElem(this));
    }
    X_on_free_ = _X;
    Y_on_free_ = _Y;
    Z_on_free_ = _Z;

}


void MyOptionController::initialize() {
}


void MyOptionController::onReset() {
    _pKurokoA->setMvVelo(0);
    _pKurokoA->forceRyMvAngVeloRange(-1*angVelo_Turn_, angVelo_Turn_);
    _pKurokoA->forceRzMvAngVeloRange(-1*angVelo_Turn_, angVelo_Turn_);
    _pKurokoA->setRzRyMvAng(0,0);
    way_myship_prev_ = P_MYSHIP->way_;
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->behave();
}

void MyOptionController::onActive() {
    reset();
}

void MyOptionController::processBehavior() {
//    if (GgafDxInput::isBeingPressedKey(DIK_I)) {
//        dump();
//    }


    if (VB_PLAY->isDoublePushedDown(VB_OPTION,8,8)) {
        //もとに戻す
        _pKurokoA->execTurnMvAngSequence(
                        0,
                        0,
                        20000, 0,
                        TURN_CLOSE_TO,
                        false
                 );
        is_free_from_myship_mode_ = false;
        is_handle_move_mode_ = false;
        return_to_default_position_seq_ = true;
        adjustDefaltAngPosition(60);
        for (int i = 0; i < now_option_num_; i++) {
            //オプションの半径位置を元に戻す指示
            papMyOption_[i]->return_to_base_radiusPosition_seq_ = true;
            papMyOption_[i]->return_to_base_angExpanse_seq_= true;
        }
        //トレース履歴を書き換える
        GgafLinkedListRing<GgafDxGeoElem>::Elem* pElem = pRing_OpConGeoHistory_->getElemFirst();
        GgafDxGeoElem* p;
        while (true) {
            p = pElem->_pValue;
            p->_X += (_X-X_on_free_);
            p->_Y += (_Y-Y_on_free_);
            p->_Z += (_Z-Z_on_free_);

            if (pElem->_is_last_flg) {
                break;
            } else {
                pElem = pElem -> _pNext;
            }
        }
        X_on_free_ = _X;
        Y_on_free_ = _Y;
        Z_on_free_ = _Z;


    } else if (VB_PLAY->isBeingPressed(VB_OPTION) && !VB_PLAY->isBeingPressed(VB_TURBO)) {
        //オプション向き操作
        if (VB_PLAY->isBeingPressed(VB_UP)) {
            _pKurokoA->addRzMvAng(angVelo_Turn_);
        }
        if (VB_PLAY->isBeingPressed(VB_DOWN)) {
            _pKurokoA->addRzMvAng(-angVelo_Turn_);
        }
        if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
            _pKurokoA->addRyMvAng(angVelo_Turn_);
        }
        if (VB_PLAY->isBeingPressed(VB_LEFT)) {
            _pKurokoA->addRyMvAng(-angVelo_Turn_);
        }

    }

    if (VB_PLAY->isRoundPushDown(VB_OPTION)) {
    //if (VB_PLAY->isPushedDown(VB_OPTION) && GgafDxInput::isBeingPressedKey(DIK_S)) {

        if (papMyOption_[0]) {
            X_on_free_ = _X;
            Y_on_free_ = _Y;
            Z_on_free_ = _Z;
            is_free_from_myship_mode_ = true;
            is_handle_move_mode_ = true;
            _pKurokoB->setVxMvAcce(0);
            _pKurokoB->setVyMvAcce(0);
            _pKurokoB->setVzMvAcce(0);
            _pKurokoB->setVxMvVelo(0);
            _pKurokoB->setVyMvVelo(0);
            _pKurokoB->setVzMvVelo(0);
        }
    }


    if (is_free_from_myship_mode_) {
        if (VB_PLAY->isBeingPressed(VB_OPTION) && is_handle_move_mode_) {
            //オプションの広がり角より、オプション移動速度と、旋回半径増加速度にベクトル分解。
            //そのうちのオプション移動速度のみを設定。
            _pKurokoA->setMvVelo(GgafDxUtil::COS[papMyOption_[0]->angExpanse_/ SANG_RATE] * veloOptionsMv_);
            //旋回半径増加速度の処理はMyOptionクラスで行う。
        } else {
            is_handle_move_mode_ = false;
            _pKurokoA->setMvVelo(0);
        }
    } else {
        //GgafDxGeoElem* pGeoMyShip = P_MYSHIP->pRing_OpConGeoHistory_->getPrev(4); //自機にすこしおくれて追従



        MyShip* pGeoMyShip = P_MYSHIP;
        if (return_to_default_position_seq_) {
            //元の位置へ
            int dx = pGeoMyShip->_X - (_X + _pKurokoB->_veloVxMv*6);
            int dy = pGeoMyShip->_Y - (_Y + _pKurokoB->_veloVyMv*6);
            int dz = pGeoMyShip->_Z - (_Z + _pKurokoB->_veloVzMv*6);
            _pKurokoB->setVxMvAcce(dx);
            _pKurokoB->setVyMvAcce(dy);
            _pKurokoB->setVzMvAcce(dz);
            if (abs(_X - pGeoMyShip->_X) < 10000 &&
                abs(_Y - pGeoMyShip->_Y) < 10000 &&
                abs(_Z - pGeoMyShip->_Z) < 10000 &&
                abs(_pKurokoB->_veloVxMv) < 20000 &&
                abs(_pKurokoB->_veloVyMv) < 20000 &&
                abs(_pKurokoB->_veloVzMv) < 20000    ) {

                _TRACE_("もどった！");
                _pKurokoB->setVxMvVelo(0);
                _pKurokoB->setVyMvVelo(0);
                _pKurokoB->setVzMvVelo(0);
                _pKurokoB->setVxMvAcce(0);
                _pKurokoB->setVyMvAcce(0);
                _pKurokoB->setVzMvAcce(0);
                locateAs(pGeoMyShip);
                return_to_default_position_seq_ = false;
            }

        } else {
            locateAs(pGeoMyShip);
        }
    }


    if (VB_PLAY->isPushedDown(VB_OPTION)) {
        papMyOption_[0]->_pModel->_pTextureBlinker->forceBlinkRange(0.01, 0.1, 3.0);
        papMyOption_[0]->_pModel->_pTextureBlinker->beat(30,10,2,-1);
    } else if (VB_PLAY->isReleasedUp(VB_OPTION)) {
        papMyOption_[0]->_pModel->_pTextureBlinker->stopImmed();
        papMyOption_[0]->_pModel->_pTextureBlinker->setBlink(1.0f);
    }


    //ギズモ
    pDirectionVector_->locateAs(this);
    pDirectionVector_->_pKurokoA->setRzRyMvAng(_pKurokoA->_angRzMv, _pKurokoA->_angRyMv);

    _pKurokoA->behave();
    _pKurokoB->behave();


    if (is_free_from_myship_mode_) {

    } else {
        pRing_OpConGeoHistory_->next()->set(this);
    }
}

void MyOptionController::setNumOption(int prm_num) {
    now_option_num_ = prm_num;
    for (int i = 0; i < max_option_num_; i++) {
        if (i >= now_option_num_) {
            papMyOption_[i]->inactivate();
        }
        if (i < now_option_num_) {
            papMyOption_[i]->activate();
        }
    }
}

void MyOptionController::adjustDefaltAngPosition(frame prm_spent_frame) {
    if (now_option_num_ <= 4) {
        for (int i = 0; i < now_option_num_; i++) {
            papMyOption_[i]->adjustAngPosition((D360ANG/now_option_num_)*i,prm_spent_frame);
        }
    } else if (now_option_num_ > 4) {
        for (int i = 0; i < 4; i++) {
            papMyOption_[i]->adjustAngPosition((D360ANG/4)*i, prm_spent_frame);
        }
        for (int i = 4; i < now_option_num_; i++) {
            papMyOption_[i]->adjustAngPosition((D360ANG/(now_option_num_-4))*(i-4), prm_spent_frame);
        }
    }
}
MyOptionController::~MyOptionController() {
    DELETEARR_IMPOSSIBLE_NULL(papMyOption_);
    DELETE_IMPOSSIBLE_NULL(pRing_OpConGeoHistory_);
}

