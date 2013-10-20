#include "stdafx.h"
#include "MyOptionController.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo002.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"

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
    std::string name = "MyOption("+XTOS(no_)+")";
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

    _pSeTx->set(SE_RESTORE, "WAVE_MY_OPTION_RESTORE_001");
    _pSeTx->set(SE_FREE,    "WAVE_MY_OPTION_FREE_001");
}

void MyOptionController::initialize() {
}

void MyOptionController::onReset() {
    _pKurokoA->setMvVelo(0);
    _pKurokoA->forceRzRyMvAngVeloRange(-1*angVelo_Turn_, angVelo_Turn_);
    _pKurokoA->setRzRyMvAng(0,0);
    _pKurokoA->relateFaceWithMvAng(true);
    _pKurokoA->behave();
}

void MyOptionController::onActive() {
//    reset();
}

void MyOptionController::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    VirtualButton* pVbPlay = VB_PLAY;
    vbsta is_double_push_VB_OPTION = pVbPlay->isDoublePushedDown(VB_OPTION,8,8);
    if (is_double_push_VB_OPTION) {
        //もとに戻す
        _pKurokoA->turnRzRyMvAngTo(D0ANG, D0ANG,
                                   D_ANG(20), 0,
                                   TURN_CLOSE_TO,
                                   false );
        is_free_from_myship_mode_ = false;
        is_handle_move_mode_ = false;
        return_to_default_position_seq_ = true;
        MyOptionController::adjustDefaltAngPosition(60);
        pOption_->return_to_base_radiusPosition_seq_ = true;
        pOption_->return_to_base_angExpanse_seq_= true;
        if (pOption_->isActive()) {
            EffectTurbo002* pTurbo002 = dispatchFromCommon(EffectTurbo002);
            if (pTurbo002) {
                pTurbo002->positionAs(pOption_);
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

    if (pVbPlay->isScrewPushDown(VB_OPTION)) {
        //オプションフリーモード発動
        is_free_from_myship_mode_ = true;
        is_handle_move_mode_ = true;
        _pKurokoB->setZeroVxyzMvVelo();
        _pKurokoB->setZeroVxyzMvAcce();
        if (pOption_->isActive()) {
            EffectTurbo002* pTurbo002 = dispatchFromCommon(EffectTurbo002);
            if (pTurbo002) {
                pTurbo002->positionAs(pOption_);
            }
        }
    }

    if (is_free_from_myship_mode_) {
        if (pVbPlay->isBeingPressed(VB_OPTION)){
            if (is_handle_move_mode_) {
                //オプションの広がり角より、オプション移動速度と、旋回半径増加速度にベクトル分解。
                //そのうちのオプション移動速度のみを設定。
                _pKurokoA->setMvVelo(ANG_COS(pOption_->angExpanse_) * veloOptionsMv_);
                //旋回半径増加速度の処理はMyOptionクラスで行う。
            } else {
                //オプションフリーモードが解除されてる
            }
        } else  {
            is_handle_move_mode_ = false; //VB_OPTION離すと解除
            _pKurokoA->setMvVelo(0);
            //VB_OPTION 押下と無関係で フリーズオプションのよーな感じになる
            GgafDxGeoElem* pGeoMyShipPrev = pMyShip->pRing_MyShipGeoHistory2_->getPrev();
            _X += (pMyShip->_X - pGeoMyShipPrev->X);
            _Y += (pMyShip->_Y - pGeoMyShipPrev->Y);
            _Z += (pMyShip->_Z - pGeoMyShipPrev->Z);
        }
    } else {
        GgafDxGeoElem* pGeoMyShipTrace = pMyShip->pRing_MyShipGeoHistory4OptCtrler_->getPrev(MyOptionController::o2o_*(no_+1));
        coord TX = pMyShip->_X_local + pGeoMyShipTrace->X;
        coord TY = pMyShip->_Y_local + pGeoMyShipTrace->Y;
        coord TZ = pMyShip->_Z_local + pGeoMyShipTrace->Z;
        //(TX,TY,TZ)は自機の絶対座標履歴に同じ。
        //VB_OPTION 押下時は、pRing_MyShipGeoHistory4OptCtrler_ に履歴は追加されず、(_X_local, _Y_local, _Z_local) のみ更新。
        //フリーズオプションの動きとなる。
        //なんでか忘れたら MyShip::processBehavior() をのコメントを見よ

        if (return_to_default_position_seq_) {
            //元の位置へ
            _pKurokoB->setVxyzMvAcce( TX - (_X + _pKurokoB->_veloVxMv*6),
                                      TY - (_Y + _pKurokoB->_veloVyMv*6),
                                      TZ - (_Z + _pKurokoB->_veloVzMv*6)  );
            if (ABS(_X - TX) < 10000 &&
                ABS(_Y - TY) < 10000 &&
                ABS(_Z - TZ) < 10000 &&
                ABS(_pKurokoB->_veloVxMv) < 20000 &&
                ABS(_pKurokoB->_veloVyMv) < 20000 &&
                ABS(_pKurokoB->_veloVzMv) < 20000
            ) {
                //もどった！
                _pKurokoB->setZeroVxyzMvVelo();
                _pKurokoB->setZeroVxyzMvAcce();
                position(TX, TY, TZ);
                return_to_default_position_seq_ = false;
            }

        } else {
            position(TX, TY, TZ); //通常のツインビー分身トレース
        }
    }

//    //ギズモ
//    pDirectionVector_->positionAs(this);
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
    GGAF_DELETE(pRing_OptCtrlGeoHistory_);
}

