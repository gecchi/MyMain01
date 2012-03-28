#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;
int MyOptionController::max_option_num_ = 8;
int MyOptionController::o2o_ = 15;
int MyOptionController::now_option_num_ = 0;
//MyOptionController::MyOptionController(const char* prm_name) :
//    DefaultMeshActor(prm_name, "Gizmo") {

MyOptionController::MyOptionController(const char* prm_name, int prm_no) :
  GgafDxGeometricActor(prm_name, NULL, NULL) {
    no_ = prm_no;
    is_handle_move_mode_ = false;
    is_free_from_myship_mode_ = false;
    return_to_default_position_seq_ = false;
    angVelo_Turn_ = 3000;
    veloOptionsMv_ = 20000;

    renge_ = 80000;

    _pKurokoB->forceVxMvVeloRange(-renge_, renge_);
    _pKurokoB->forceVyMvVeloRange(-renge_, renge_);
    _pKurokoB->forceVzMvVeloRange(-renge_, renge_);

    _pKurokoB->forceVxMvAcceRange(-renge_ / 30, renge_ / 30);
    _pKurokoB->forceVyMvAcceRange(-renge_ / 30, renge_ / 30);
    _pKurokoB->forceVzMvAcceRange(-renge_ / 30, renge_ / 30);

//    papOption_ = NEW MyOption*[max_option_num_];
//    for (int i = 0; i < max_option_num_; i++) {
//        papOption_[i] = NULL;
//    }

    pOption_ = NEW MyOption("MY_OPTION01", no_, this);
    addSubGroup(pOption_);


//    for (int i = 0; i < max_option_num_; i++) {
//        papOption_[i]->inactivateImmed();
//    }
    pOption_->inactivateImmed();

//    for (int i = 0; i < MyOptionController::now_option_num_; i++) {
//        papOption_[i]->activate();
//    }
//    pOption_->activate();

//    //ギズモ
//    pGizmo_ = NEW MyOptionControllerGizmo("MyPGizmo");
//    addSubGroup(pGizmo_);
//    //方向ベクトル
//    pDirectionVector_ = NEW MyOptionControllerDirectionVector("MyPDirectionVector");
//    addSubGroup(pDirectionVector_);

    //トレース用履歴
    pRing_OptCtrlGeoHistory_ = NEW GgafLinkedListRing<GgafDxGeoElem>();
    for (DWORD i = 0; i < max_option_num_*o2o_; i++) {
        pRing_OptCtrlGeoHistory_->addLast(NEW GgafDxGeoElem(this));
    }
//    X_on_free_ = _X;
//    Y_on_free_ = _Y;
//    Z_on_free_ = _Z;

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
        MyOptionController::adjustDefaltAngPosition(60);
//        for (int i = 0; i < MyOptionController::now_option_num_; i++) {
//            //オプションの半径位置を元に戻す指示
//            papOption_[i]->return_to_base_radiusPosition_seq_ = true;
//            papOption_[i]->return_to_base_angExpanse_seq_= true;
//        }
        pOption_->return_to_base_radiusPosition_seq_ = true;
        pOption_->return_to_base_angExpanse_seq_= true;

//        //トレース履歴を書き換える
//        GgafLinkedListRing<GgafDxGeoElem>::Elem* pElem = pRing_OptCtrlGeoHistory_->getElemFirst();
//        GgafDxGeoElem* p;
//        while (true) {
//            p = pElem->_pValue;
//            p->_X += (_X-X_on_free_);
//            p->_Y += (_Y-Y_on_free_);
//            p->_Z += (_Z-Z_on_free_);
//
//            if (pElem->_is_last_flg) {
//                break;
//            } else {
//                pElem = pElem -> _pNext;
//            }
//        }
//        X_on_free_ = _X;
//        Y_on_free_ = _Y;
//        Z_on_free_ = _Z;


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

        //if (papOption_[0]) {
        if (pOption_) {
//            X_on_free_ = _X;
//            Y_on_free_ = _Y;
//            Z_on_free_ = _Z;
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
//            _pKurokoA->setMvVelo(GgafDxUtil::COS[papOption_[0]->angExpanse_/ SANG_RATE] * veloOptionsMv_);
            _pKurokoA->setMvVelo(GgafDxUtil::COS[pOption_->angExpanse_/ SANG_RATE] * veloOptionsMv_);
            //旋回半径増加速度の処理はMyOptionクラスで行う。
        } else {
            is_handle_move_mode_ = false;
            _pKurokoA->setMvVelo(0);
        }
    } else {
        //GgafDxGeoElem* pGeoMyShipTrace = P_MYSHIP->pRing_OptCtrlGeoHistory_->getPrev(4); //自機にすこしおくれて追従



        GgafDxGeoElem* pGeoMyShipTrace = P_MYSHIP->pRing_MyShipGeoHistory_->getPrev(MyOptionController::o2o_*(no_+1));
        if (return_to_default_position_seq_) {
            //元の位置へ
            int dx = pGeoMyShipTrace->_X - (_X + _pKurokoB->_veloVxMv*6);
            int dy = pGeoMyShipTrace->_Y - (_Y + _pKurokoB->_veloVyMv*6);
            int dz = pGeoMyShipTrace->_Z - (_Z + _pKurokoB->_veloVzMv*6);
            _pKurokoB->setVxMvAcce(dx);
            _pKurokoB->setVyMvAcce(dy);
            _pKurokoB->setVzMvAcce(dz);
            if (abs(_X - pGeoMyShipTrace->_X) < 10000 &&
                abs(_Y - pGeoMyShipTrace->_Y) < 10000 &&
                abs(_Z - pGeoMyShipTrace->_Z) < 10000 &&
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
                locatedBy(pGeoMyShipTrace);
                return_to_default_position_seq_ = false;
            }

        } else {
            locatedBy(pGeoMyShipTrace);



        }
    }


//    if (VB_PLAY->isPushedDown(VB_OPTION)) {
//        papOption_[0]->_pModel->_pTextureBlinker->forceBlinkRange(0.01, 0.1, 3.0);
//        papOption_[0]->_pModel->_pTextureBlinker->beat(30,10,2,-1);
//    } else if (VB_PLAY->isReleasedUp(VB_OPTION)) {
//        papOption_[0]->_pModel->_pTextureBlinker->stopImmed();
//        papOption_[0]->_pModel->_pTextureBlinker->setBlink(1.0f);
//    }


//    //ギズモ
//    pDirectionVector_->locatedBy(this);
//    pDirectionVector_->_pKurokoA->setRzRyMvAng(_pKurokoA->_angRzMv, _pKurokoA->_angRyMv);

    _pKurokoA->behave();
    _pKurokoB->behave();

    pRing_OptCtrlGeoHistory_->next()->set(this);
//    if (is_free_from_myship_mode_) {
//
//    } else {
//        pRing_OptCtrlGeoHistory_->next()->set(this);
//    }
}


void MyOptionController::setNumOption(int prm_num) {
    MyShipScene* pMyShipScene = P_MYSHIP_SCENE;
    MyOptionController::now_option_num_ = prm_num;
    for (int i = 0; i < MyOptionController::max_option_num_; i++) {
        if (i >= MyOptionController::now_option_num_) {
            pMyShipScene->papOptionCtrler_[i]->pOption_->inactivate();
        }
        if (i < MyOptionController::now_option_num_) {
            pMyShipScene->papOptionCtrler_[i]->pOption_->activate();
        }
    }
}

void MyOptionController::adjustDefaltAngPosition(frame prm_spent_frame) {
    MyShipScene* pMyShipScene = P_MYSHIP_SCENE;
    if (MyOptionController::now_option_num_ <= 4) {
        for (int i = 0; i < MyOptionController::now_option_num_; i++) {
            pMyShipScene->papOptionCtrler_[i]->pOption_->adjustAngPosition((D360ANG/MyOptionController::now_option_num_)*i,prm_spent_frame);
        }
    } else if (MyOptionController::now_option_num_ > 4) {
        for (int i = 0; i < 4; i++) {
            pMyShipScene->papOptionCtrler_[i]->pOption_->adjustAngPosition((D360ANG/4)*i, prm_spent_frame);
        }
        for (int i = 4; i < MyOptionController::now_option_num_; i++) {
            pMyShipScene->papOptionCtrler_[i]->pOption_->adjustAngPosition((D360ANG/(MyOptionController::now_option_num_-4))*(i-4), prm_spent_frame);
        }
    }
}
MyOptionController::~MyOptionController() {
//    DELETEARR_IMPOSSIBLE_NULL(papOption_);
    DELETE_IMPOSSIBLE_NULL(pRing_OptCtrlGeoHistory_);
}

