#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;
int MyOptionController::max_option_num_ = 9;
int MyOptionController::o2o_ = 15;
int MyOptionController::now_option_num_ = 0;
//MyOptionController::MyOptionController(const char* prm_name, int prm_no) :
//        DefaultMeshSetActor(prm_name, "8/momomo") {

MyOptionController::MyOptionController(const char* prm_name, int prm_no) :
  GgafDxGeometricActor(prm_name, nullptr, nullptr) {
    no_ = prm_no;
    is_handle_move_mode_ = false;
    is_free_from_myship_mode_ = false;
    return_to_default_position_seq_ = false;
    angVelo_Turn_ = 3000;
    veloOptionsMv_ = 20000;
    renge_ = 80000;
    _pKurokoB->forceVxyzMvVeloRange(-renge_, renge_);
    _pKurokoB->forceVxyzMvAcceRange(-renge_ / 30, renge_ / 30);
    std::string name = "MyOption("+ITOS(no_)+")";
    pOption_ = NEW MyOption(name.c_str(), no_, this);
    addSubGroup(pOption_);
    pOption_->inactivateImmed();

//    //ギズモ
//    pGizmo_ = NEW MyOptionControllerGizmo("MyPGizmo");
//    addSubGroup(pGizmo_);
//    //方向ベクトル
//    pDirectionVector_ = NEW MyOptionControllerDirectionVector("MyPDirectionVector");
//    addSubGroup(pDirectionVector_);

    //トレース用履歴
    pRing_OptCtrlGeoHistory_ = NEW GgafLinkedListRing<GgafDxGeoElem>();
    for (int i = 0; i < max_option_num_*o2o_; i++) {
        pRing_OptCtrlGeoHistory_->addLast(NEW GgafDxGeoElem(this));
    }
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
//    reset();
}

void MyOptionController::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    VirtualButton* pVbPlay = VB_PLAY;

    if (pVbPlay->isDoublePushedDown(VB_OPTION,8,8)) {
        //もとに戻す
        _pKurokoA->execTurnRzRyMvAngSequence(
                        0, 0,
                        20000, 0,
                        TURN_CLOSE_TO,
                        false
                   );
        is_free_from_myship_mode_ = false;
        is_handle_move_mode_ = false;
        return_to_default_position_seq_ = true;
        MyOptionController::adjustDefaltAngPosition(60);
        pOption_->return_to_base_radiusPosition_seq_ = true;
        pOption_->return_to_base_angExpanse_seq_= true;
        if (pOption_->isActive()) {
            EffectTurbo002* pTurbo002 = employFromCommon(EffectTurbo002);
            if (pTurbo002) {
                pTurbo002->locateWith(pOption_);
            }
        }
    } else if (pVbPlay->isBeingPressed(VB_OPTION) && !pVbPlay->isBeingPressed(VB_TURBO)) {
        //オプション向き操作
        if (pVbPlay->isBeingPressed(VB_UP)) {
            _pKurokoA->addRzMvAng(angVelo_Turn_);
        }
        if (pVbPlay->isBeingPressed(VB_DOWN)) {
            _pKurokoA->addRzMvAng(-angVelo_Turn_);
        }
        if (pVbPlay->isBeingPressed(VB_RIGHT)) {
            _pKurokoA->addRyMvAng(angVelo_Turn_);
        }
        if (pVbPlay->isBeingPressed(VB_LEFT)) {
            _pKurokoA->addRyMvAng(-angVelo_Turn_);
        }
    }

    if (pVbPlay->isRoundPushDown(VB_OPTION)) {
        is_free_from_myship_mode_ = true;
        is_handle_move_mode_ = true;
        _pKurokoB->setZeroVxyzMvVelo();
        _pKurokoB->setZeroVxyzMvAcce();
        if (pOption_->isActive()) {
            EffectTurbo002* pTurbo002 = employFromCommon(EffectTurbo002);
            if (pTurbo002) {
                pTurbo002->locateWith(pOption_);
            }
        }
    }

    if (is_free_from_myship_mode_) {
        if (pVbPlay->isBeingPressed(VB_OPTION) && is_handle_move_mode_) {
            //オプションの広がり角より、オプション移動速度と、旋回半径増加速度にベクトル分解。
            //そのうちのオプション移動速度のみを設定。
            _pKurokoA->setMvVelo(ANG_COS(pOption_->angExpanse_) * veloOptionsMv_);
            //旋回半径増加速度の処理はMyOptionクラスで行う。
        } else {
            is_handle_move_mode_ = false;
            _pKurokoA->setMvVelo(0);
        }
    } else {
        GgafDxGeoElem* pGeoMyShipTrace = pMyShip->pRing_MyShipGeoHistory4OptCtrler_->getPrev(MyOptionController::o2o_*(no_+1));
        coord TX = pMyShip->_X_local + pGeoMyShipTrace->_X;
        coord TY = pMyShip->_Y_local + pGeoMyShipTrace->_Y;
        coord TZ = pMyShip->_Z_local + pGeoMyShipTrace->_Z;
        if (return_to_default_position_seq_) {
            //元の位置へ
            int dx = TX - (_X + _pKurokoB->_veloVxMv*6);
            int dy = TY - (_Y + _pKurokoB->_veloVyMv*6);
            int dz = TZ - (_Z + _pKurokoB->_veloVzMv*6);
            _pKurokoB->setVxMvAcce(dx);
            _pKurokoB->setVyMvAcce(dy);
            _pKurokoB->setVzMvAcce(dz);
            if (ABS(_X - TX) < 10000 &&
                ABS(_Y - TY) < 10000 &&
                ABS(_Z - TZ) < 10000 &&
                ABS(_pKurokoB->_veloVxMv) < 20000 &&
                ABS(_pKurokoB->_veloVyMv) < 20000 &&
                ABS(_pKurokoB->_veloVzMv) < 20000    ) {

                _TRACE_("もどった！");
                _pKurokoB->setZeroVxyzMvVelo();
                _pKurokoB->setZeroVxyzMvAcce();
                locate(TX, TY, TZ);
                return_to_default_position_seq_ = false;
            }

        } else {
            locate(TX, TY, TZ);
        }
    }



//    //ギズモ
//    pDirectionVector_->locateWith(this);
//    pDirectionVector_->_pKurokoA->setRzRyMvAng(_pKurokoA->_angRzMv, _pKurokoA->_angRyMv);

    _pKurokoA->behave();
    _pKurokoB->behave();

    pRing_OptCtrlGeoHistory_->next()->set(this);
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

