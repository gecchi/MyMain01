#include "EnemyEsperia.h"

#include "jp/ggaf/core/actor/ex/ActorDepositoryStore.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Esperia/EnemyEsperiaLaserChip001.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT,
    PHASE_ENTRY,
    PHASE_MOVE,
    PHASE_HATCH_OPEN,
    PHASE_FIRE,
    PHASE_HATCH_CLOSE,
    PHASE_NOTHING,
    PHASE_BANPEI,
};
enum {
    SE_EXPLOSION,
    SE_DAMAGED,
    SE_HATCH_OPEN,
    SE_FIRE,
    SE_HATCH_CLOSE,
};

int EnemyEsperia::max_laser_way_ = RF_EnemyEsperia_ShotWay(1.0);
//RF_EnemyEsperia_ShotWayランク式は 1.0で最大を取るようにしなければならない

EnemyEsperia::EnemyEsperia(const char* prm_name) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "Esperia", StatusReset(EnemyEsperia)) {
    cnt_laserchip_ = 0;
    laser_length_ = 40;
    now_laser_way_ = 0;
    //借り入れレーザーセットのデポジトリ保持用
    papLaserChipDepo_ = NEW LaserChipDepository*[max_laser_way_];
    for (int i = 0; i < max_laser_way_; i++) {
        papLaserChipDepo_[i] = nullptr;
    }

    pConn_pDepoStore_laser_set = connectToDepositoryManager("EnemyEsperiaLaserChip001DepoStore");
    pDepoStore_laser_set = (GgafCore::ActorDepositoryStore*)(pConn_pDepoStore_laser_set->peek());

    paLocalPos_laser_ = NEW GgafDx::GeoElem[max_laser_way_];
    paPos_target_ = NEW GgafDx::GeoElem[max_laser_way_];
    coord dX = PX_C(10); //レーザー発射口の間隔
    for (int i = 0; i < max_laser_way_; i++) {
        paLocalPos_laser_[i].set(PX_C(-40) + (i*dX),  PX_C(10), 0); //レーザー発射元のローカル座標
    }

    GgafDx::SeTransmitterForActor* pSetx = getSeTransmitter();
    pSetx->set(SE_EXPLOSION  , "SE_EXPLOSION_MIDDLE_001");
    pSetx->set(SE_DAMAGED    , "SE_ENEMY_DAMAGED_001");
    pSetx->set(SE_HATCH_OPEN , "SE_HATCH_OPEN_001");
    pSetx->set(SE_FIRE       , "SE_ENEMY_FIRE_LASER_001");
    pSetx->set(SE_HATCH_CLOSE, "SE_HATCH_CLOSE_001");
    dX_= dZ_ = 0;
}

void EnemyEsperia::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(1.0, 0.97);
    pModel->getTexBlinker()->setRange(0.5, 12.0);
    pModel->getTexBlinker()->beat(60*6, 60*2, 0, 60*2, -1);
}

void EnemyEsperia::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(200));
}

void EnemyEsperia::onActive() {
    getStatus()->reset();
    setHitAble(false);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setRzRyMvAng(0, D180ANG);
    pVecVehicle->setMvVelo(1000);

    dX_= dZ_ = 0;
    //出現位置
    const coord appearances_renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 3;
    const coord appearances_renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 3;
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
    _x = pSpacetime->_x_bound_right - 1000;
    _y = RND(-(appearances_renge_y/2) , +(appearances_renge_y/2));
    _z = RND(-(appearances_renge_z/2) , +(appearances_renge_z/2));


   // setPositionAroundAt(pMYSHIP, PX_C(400));


    getPhase()->reset(PHASE_INIT);
}

void EnemyEsperia::processBehavior() {
    MyShip* pMyShip = pMYSHIP;
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
            pPhase->changeNext();
            break;
        }
        case PHASE_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pPhase->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pPhase->hasArrivedFrameAt(frame_of_summons_begin)) {
                getAlphaFader()->transitionLinearUntil(0.999, frame_of_entering);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                setHitAble(true);
                pPhase->changeNext();
            }
            getAlphaFader()->behave();
            break;
        }
        case PHASE_MOVE: {
            if (pPhase->hasJustChanged()) {

            }
            if (pPhase->hasArrivedFrameAt(100)) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_HATCH_OPEN: {
            if (pPhase->hasJustChanged()) {
                getSeTransmitter()->play3D(SE_HATCH_OPEN);
                getMorpher()->transitionLinearUntil(1, 1.0, 120);
            }
            if (pPhase->hasArrivedFrameAt(120)) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_FIRE: {
            if (pPhase->hasJustChanged()) {
                //レーザーセット（レーザーチップのデポジトリで、１本分のレーザー）のデポジトリから、
                //レーザーセットの借入を試みる
                now_laser_way_ = RF_EnemyEsperia_ShotWay(G_RANK); //今回発射レーザー本数
                coord laser_density = RF_EnemyEsperia_Density(G_RANK); //今回レーザーとレーザーの隙間
                bool can_fire = false; //少なくとも一本は発射できるかどうか

                for (int i = 0; i < max_laser_way_; i++) {
                    if (now_laser_way_ > i) {
                        LaserChipDepository* pLaserChipDepo = (LaserChipDepository*)(pDepoStore_laser_set->dispatch());
                        if (pLaserChipDepo) {
                            //レーザーセット（レーザーチップのデポジトリ）が借り入れ出来た。
                            papLaserChipDepo_[i] = pLaserChipDepo;
                            papLaserChipDepo_[i]->config(laser_length_, 1);
                            can_fire = true;
                        } else {
                            //レーザーセット（レーザーチップのデポジトリ）が借り入れ出来なかった。
                            papLaserChipDepo_[i] = nullptr;
                        }
                    } else {
                        papLaserChipDepo_[i] = nullptr;
                    }
                }

                if (can_fire) { //発射するでー
                    //すだれターゲット座標設定
                    //                    ^
                    //                    | X
                    //                    |
                    //              (b)   |   (c)
                    //                    |
                    //                    |
                    //                    |
                    //       (a)          |              (d)
                    //  Z                 |
                    //  <---------------自 機------------------
                    //                    |
                    //                    |
                    //                    |
                    //                    |
                    //                    |
                    //                    |
                    //               (e)  |    (f)
                    //                    |
                    //                    |
                    //
                    //  (a)(d) の場合、X方向距離よりZ方向距離が遠いので
                    //         Xの小さい方から
                    //                    ^
                    //                    | X
                    //                    |
                    //                    |
                    //  ーーーーーーーーーーーーーーーーーーー→ [3]
                    //                    |
                    //                    |
                    //  ーーーーーーーーーーーーーーーーーーー→ [2]
                    //  Z                 |
                    //  <---------------自 機------------------
                    //                    |
                    //  ーーーーーーーーーーーーーーーーーーー→ [1]
                    //                    |
                    //                    |
                    //  ーーーーーーーーーーーーーーーーーーー→ [0]
                    //                    |
                    //                    |
                    //                    |
                    //とする。
                    //
                    //
                    //  (b)(c) の場合、Z方向距離よりX方向距離が遠いので
                    //  Z     ｜     ｜       ｜     ｜
                    //  <-----｜-----｜-自 機-｜-----｜------
                    //        ｜     ｜       ｜     ｜
                    //        ｜     ｜       ｜     ｜
                    //        ↓     ↓       ↓     ↓
                    //       [0]     [1]      [2]    [3]  ・・・ (b)
                    //       [3]     [2]      [1]    [0]  ・・・ (c)
                    //  とする
                    coord total_laser_effect = laser_density*(now_laser_way_-1)+1; //すだれレーザーのすだれ距離（範囲）

                    dX_ = ABS(_x - pMyShip->_x);
                    dZ_ = ABS(_z - pMyShip->_z);
                    if (dX_ < dZ_)  {
                        //(a)(d) の場合、X方向距離よりZ方向距離が遠い
                        for (int i = 0, tX = -total_laser_effect/2; i < now_laser_way_; i++, tX+=laser_density) {
                            paPos_target_[i].set(tX, 0, 0);
                        }
                    } else {
                        if (pMyShip->_x < _x) { //自機より前
                            //(b)(c)の場合、Z方向距離よりX方向距離が遠い
                            if (pMyShip->_z < _z) {
                                //(b)自機が手前、エスペリアが奥
                                for (int i = 0, tZ = total_laser_effect/2; i < now_laser_way_; i++, tZ-=laser_density) {
                                    paPos_target_[i].set(0, 0, tZ);
                                }
                            } else {
                                //(c)自機が奥、エスペリアが手前
                                for (int i = 0, tZ = -total_laser_effect/2; i < now_laser_way_; i++, tZ+=laser_density) {
                                    paPos_target_[i].set(0, 0, tZ);
                                }
                            }
                        } else { //自機より後ろ (e)(f)
                            if (pMyShip->_z < _z) {
                                //(e)自機が手前、エスペリアが奥
                                for (int i = 0, tZ = -total_laser_effect/2; i < now_laser_way_; i++, tZ+=laser_density) {
                                    paPos_target_[i].set(0, 0, tZ);
                                }
                            } else {
                                //(f)自機が奥、エスペリアが手前
                                for (int i = 0, tZ = total_laser_effect/2; i < now_laser_way_; i++, tZ-=laser_density) {
                                    paPos_target_[i].set(0, 0, tZ);
                                }
                            }
                        }
                    }

                    getSeTransmitter()->play3D(SE_FIRE); //発射音
                    effectFlush(2); //フラッシュ
                    cnt_laserchip_ = 0;
                }
            }

            //laser_length_以内の間、レーザーチップをdispatch()を試み続ける
            if (cnt_laserchip_ < laser_length_) {
                cnt_laserchip_++;
                EnemyEsperiaLaserChip001* pLaserChip;
                GgafDx::GeoElem* p;
                coord turn_dy = getTurnDY(this, pMyShip, (dX_ > dZ_ ? dX_ : dZ_) );
                //↑turn_dy の 引数は EnemyEsperiaLaserChip001::turn_dy_と同期を取る事
                for (int i = 0; i < max_laser_way_; i++) {
                    if (papLaserChipDepo_[i]) {
                        pLaserChip = (EnemyEsperiaLaserChip001*)papLaserChipDepo_[i]->dispatch();
                        if (pLaserChip) {
                            p = &(paLocalPos_laser_[i]);
                            //発射元座標に設定
                            pLaserChip->setPosition(_x+p->x, _y+p->y, _z+p->z);
                            //最初の目標地点(折り返す地点)を設定
                            //シンバルロック付近を避けるためすこしズラス
                            if (dX_ < dZ_)  {
                                //X方向距離よりZ方向距離が遠い
                                if (pMyShip->_z < _z) {
                                    //自機が手前、エスペリアが奥
                                    pLaserChip->tx1_ = _x + paPos_target_[i].x;
                                    pLaserChip->ty1_ = _y + paPos_target_[i].y + turn_dy;
                                    pLaserChip->tz1_ = _z + paPos_target_[i].z + PX_C(100);
                                } else {
                                    //自機が奥、エスペリアが手前
                                    pLaserChip->tx1_ = _x + paPos_target_[i].x;
                                    pLaserChip->ty1_ = _y + paPos_target_[i].y + turn_dy;
                                    pLaserChip->tz1_ = _z + paPos_target_[i].z - PX_C(100);
                                }
                            } else {
                                //シンバルロック付近を避けるためX-100
                                pLaserChip->tx1_ = _x + paPos_target_[i].x - PX_C(100);
                                pLaserChip->ty1_ = _y + paPos_target_[i].y + turn_dy;
                                pLaserChip->tz1_ = _z + paPos_target_[i].z;
                            }

                            pLaserChip->turn_dy_ = turn_dy;
                            //最終目標地点を設定
                            pLaserChip->tx2_ = pMyShip->_x + paPos_target_[i].x;
                            pLaserChip->ty2_ = pMyShip->_y + paPos_target_[i].y;
                            pLaserChip->tz2_ = pMyShip->_z + paPos_target_[i].z;
                            //速さと加速度
                            pLaserChip->getVecVehicle()->setMvVelo(10000); //初期速度
                            pLaserChip->getVecVehicle()->setMvAcce(150+(max_laser_way_-i)*20); //少しバラけるように
                        }
                    }
                }
            } else {
                //レーザーを打ち切った
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_HATCH_CLOSE: {
            if (pPhase->hasJustChanged()) {
                getSeTransmitter()->play3D(SE_HATCH_CLOSE);
                getMorpher()->transitionLinearUntil(1, 0.0, 120);
            }
            if (pPhase->hasArrivedFrameAt(120)) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_NOTHING: {
            if (pPhase->hasArrivedFrameAt(600)) {
                pPhase->change(PHASE_MOVE);
            }
            break;
        }
    }
    pVecVehicle->behave();
    getMorpher()->behave();
}

void EnemyEsperia::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEsperia::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyEsperia::onInactive() {
    //レーザーデポジトリは遅れてから戻す
    for (int i = 0; i < max_laser_way_; i++) {
        if (papLaserChipDepo_[i]) {
            papLaserChipDepo_[i]->sayonara(60*10);
        }
    }
    sayonara();
}

coord EnemyEsperia::getTurnDY(GgafDx::GeometricActor* pThis,
                              GgafDx::GeometricActor* pMyShip,
                              coord DT) {
    //                        ^ Y
    //                        |
    //                        |…………
    //                      ／|     ^
    //                    ／  |     |
    //                  ／    |     | TurnDY（返す値）
    //                ／      |     |
    //              ／        |     v
    //            ／         敵…………
    //          ／θ=5°      |
    //    ---自機-------------+--------->
    //      ／:               |
    //    ／  :               |
    //  ／    :<------------->|
    //        :     DT(引数)  |
    //
    //DY = DT・tan(5°) - (敵_y - 自機_y)
    static const double TAN5 = tan(5*(PI/180.0)); //５度上から打ち下ろす
    coord dY = pThis->_y - pMyShip->_y;
    coord TurnDY = DT*TAN5 - dY;
    if (TurnDY < PX_C(100)) {
        return PX_C(100);
    } else {
        return TurnDY;
    }
}

EnemyEsperia::~EnemyEsperia() {
    pConn_pDepoStore_laser_set->close();
    GGAF_DELETEARR(paLocalPos_laser_);
    GGAF_DELETEARR(paPos_target_);
    GGAF_DELETEARR(papLaserChipDepo_);
}
