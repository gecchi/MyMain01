#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

int EnemyHesperia::max_laser_way_ = RR_EnemyHesperia_ShotWay(1.0);
//RR_EnemyHesperia_ShotWayランク式は 1.0で最大を取るようにしなければならない

EnemyHesperia::EnemyHesperia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Hesperia", STATUS(EnemyHesperia)) {

    cnt_laserchip_ = 0;
    laser_length_ = 40;
    //借り入れレーザーセットのデポジトリ保持用
    papLaserChipDepo_ = NEW LaserChipDepository*[max_laser_way_];
    for (int i = 0; i < max_laser_way_; i++) {
        papLaserChipDepo_[i] = NULL;
    }

    pCon_LaserChipDepoStore_ = connectToDepositoryManager("DpCon_EnemyHesperiaLaserChip001DepoStore", NULL);
    pLaserChipDepoStore_ = (GgafActorDepositoryStore*)(pCon_LaserChipDepoStore_->fetch());

    paLocalPos_Laser_ = NEW GgafDxGeoElem[max_laser_way_];
    paPos_Target_ = NEW GgafDxGeoElem[max_laser_way_];
    coord dX = PX_C(10); //レーザー発射口の間隔
    for (int i = 0; i < max_laser_way_; i++) {
        paLocalPos_Laser_[i].set(PX_C(-40) + (i*dX),  PX_C(10), 0); //レーザー発射元のローカル座標
    }

    _pSeTxer->set(SE_EXPLOSION  , "bomb1"        , GgafRepeatSeq::nextVal("CH_bomb1"));
    _pSeTxer->set(SE_DAMAGED    , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_HATCH_OPEN , "warp"         , GgafRepeatSeq::nextVal("CH_warp"));
    _pSeTxer->set(SE_FIRE       , "yume_Sbend"   , GgafRepeatSeq::nextVal("CH_yume_Sbend"));
    _pSeTxer->set(SE_HATCH_CLOSE, "yume_organ_01", GgafRepeatSeq::nextVal("CH_yume_organ_01"));
    dX_= dZ_ = 0;
    useProgress(PROG_NOTHING);
}

void EnemyHesperia::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.97, 0.5, 12.0);
    _pModel->_pTextureBlinker->setBlink(1.0);
    _pModel->_pTextureBlinker->beat(60*6, 60*2, 60*2, -1);
}

void EnemyHesperia::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(200));
}

void EnemyHesperia::onActive() {
    _pStatus->reset();
    setHitAble(false);
    _pKurokoA->setRzRyMvAng(0, D180ANG);
    _pKurokoA->setMvVelo(1000);
    dX_= dZ_ = 0;
    //出現位置
    static coord appearances_renge_Z = (MyShip::lim_zleft_ - MyShip::lim_zright_) * 3;
    static coord appearances_renge_Y = (MyShip::lim_top_ - MyShip::lim_bottom_) * 3;
    _X = GgafDxUniverse::_X_goneRight - 1000;
    _Y = RND(-(appearances_renge_Y/2) , +(appearances_renge_Y/2));
    _Z = RND(-(appearances_renge_Z/2) , +(appearances_renge_Z/2));

    _pProg->set(PROG_ENTRY);
}

void EnemyHesperia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;
    switch (_pProg->get()) {
        case PROG_ENTRY: {
            if (_pProg->isJustChanged()) {
                UTIL::activateEntryEffectOf(this);
                _pFader->setAlpha(0);
                _pFader->intoTargetAlphaLinerUntil(0.98, 20);
            }
            if (_pFader->isWorking()) {
                _pFader->behave();
            } else {
                setHitAble(true);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE: {
            if (_pProg->isJustChanged()) {

            }
            if (_pProg->getFrameInProgress() == 100) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_HATCH_OPEN: {
            if (_pProg->isJustChanged()) {
                _pSeTxer->play3D(SE_HATCH_OPEN);
                _pMorpher->intoTargetLinerUntil(1, 1.0, 120);
            }
            if (_pProg->getFrameInProgress() == 120) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            if (_pProg->isJustChanged()) {
                //レーザーセット（レーザーチップのデポジトリで、１本分のレーザー）のデポジトリから、
                //レーザーセットの借入を試みる
                int laser_way = RR_EnemyHesperia_ShotWay(_RANK_); //今回発射レーザー本数
                coord laser_density = RR_EnemyHesperia_Density(_RANK_); //今回レーザーとレーザーの隙間
                bool can_fire = false; //少なくとも一本は発射できるかどうか

                for (int i = 0; i < max_laser_way_; i++) {
                    if (laser_way > i) {
                        LaserChipDepository* pLaserChipDepo = (LaserChipDepository*)(pLaserChipDepoStore_->dispatch());
                        if (pLaserChipDepo) {
                            //レーザーセット（レーザーチップのデポジトリ）が借り入れ出来た。
                            papLaserChipDepo_[i] = pLaserChipDepo;
                            papLaserChipDepo_[i]->config(laser_length_, 1);
                            can_fire = true;
                        } else {
                            //レーザーセット（レーザーチップのデポジトリ）が借り入れ出来なかった。
                            papLaserChipDepo_[i] = NULL;
                        }
                    } else {
                        papLaserChipDepo_[i] = NULL;
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
                    coord total_laser_effect = laser_density*(laser_way-1)+1; //すだれレーザーのすだれ距離（範囲）

                    dX_ = ABS(_X - pMyShip->_X);
                    dZ_ = ABS(_Z - pMyShip->_Z);
                    if (dX_ < dZ_)  {
                        //(a)(d) の場合、X方向距離よりZ方向距離が遠い
                        for (int i = 0, tX = -total_laser_effect/2; i < laser_way; i++, tX+=laser_density) {
                            paPos_Target_[i].set(tX, 0, 0);
                        }
                    } else {
                        if (pMyShip->_X < _X) { //自機より前
                            //(b)(c)の場合、Z方向距離よりX方向距離が遠い
                            if (pMyShip->_Z < _Z) {
                                //(b)自機が手前、ヘスペリアが奥
                                for (int i = 0, tZ = total_laser_effect/2; i < laser_way; i++, tZ-=laser_density) {
                                    paPos_Target_[i].set(0, 0, tZ);
                                }
                            } else {
                                //(c)自機が奥、ヘスペリアが手前
                                for (int i = 0, tZ = -total_laser_effect/2; i < laser_way; i++, tZ+=laser_density) {
                                    paPos_Target_[i].set(0, 0, tZ);
                                }
                            }
                        } else { //自機より後ろ (e)(f)
                            if (pMyShip->_Z < _Z) {
                                //(e)自機が手前、ヘスペリアが奥
                                for (int i = 0, tZ = -total_laser_effect/2; i < laser_way; i++, tZ+=laser_density) {
                                    paPos_Target_[i].set(0, 0, tZ);
                                }
                            } else {
                                //(f)自機が奥、ヘスペリアが手前
                                for (int i = 0, tZ = total_laser_effect/2; i < laser_way; i++, tZ-=laser_density) {
                                    paPos_Target_[i].set(0, 0, tZ);
                                }
                            }
                        }
                    }

                    _pSeTxer->play3D(SE_FIRE); //発射音
                    effectFlush(2); //フラッシュ
                    cnt_laserchip_ = 0;
                }
            }

            //laser_length_以内の間、レーザーチップをdispatch()を試み続ける
            if (cnt_laserchip_ < laser_length_) {
                cnt_laserchip_++;
                EnemyHesperiaLaserChip001* pLaserChip;
                GgafDxGeoElem* p;
                coord turn_dY = getTurnDY(this, pMyShip, (dX_ > dZ_ ? dX_ : dZ_) );
                //↑turn_dY の 引数は EnemyHesperiaLaserChip001::turn_dY_と同期を取る事
                for (int i = 0; i < max_laser_way_; i++) {
                    if (papLaserChipDepo_[i]) {
                        pLaserChip = (EnemyHesperiaLaserChip001*)papLaserChipDepo_[i]->dispatch();
                        if (pLaserChip) {
                            p = &(paLocalPos_Laser_[i]);
                            //発射元座標に設定
                            pLaserChip->locate(_X+p->_X, _Y+p->_Y, _Z+p->_Z);
                            //最初の目標地点(折り返す地点)を設定
                            //シンバルロック付近を避けるためすこしズラス
                            if (dX_ < dZ_)  {
                                //X方向距離よりZ方向距離が遠い
                                if (pMyShip->_Z < _Z) {
                                    //自機が手前、ヘスペリアが奥
                                    pLaserChip->tX1_ = _X + paPos_Target_[i]._X;
                                    pLaserChip->tY1_ = _Y + paPos_Target_[i]._Y + turn_dY;
                                    pLaserChip->tZ1_ = _Z + paPos_Target_[i]._Z + PX_C(200);
                                } else {
                                    //自機が奥、ヘスペリアが手前
                                    pLaserChip->tX1_ = _X + paPos_Target_[i]._X;
                                    pLaserChip->tY1_ = _Y + paPos_Target_[i]._Y + turn_dY;
                                    pLaserChip->tZ1_ = _Z + paPos_Target_[i]._Z - PX_C(200);
                                }
                            } else {
                                //シンバルロック付近を避けるためX-200
                                pLaserChip->tX1_ = _X + paPos_Target_[i]._X - PX_C(200);
                                pLaserChip->tY1_ = _Y + paPos_Target_[i]._Y + turn_dY;
                                pLaserChip->tZ1_ = _Z + paPos_Target_[i]._Z;
                            }

                            pLaserChip->turn_dY_ = turn_dY;
                            //最終目標地点を設定
                            pLaserChip->tX2_ = pMyShip->_X + paPos_Target_[i]._X;
                            pLaserChip->tY2_ = pMyShip->_Y + paPos_Target_[i]._Y;
                            pLaserChip->tZ2_ = pMyShip->_Z + paPos_Target_[i]._Z;
                            //速さと加速度
                            pLaserChip->_pKurokoA->setMvVelo(10000); //初期速度
                            pLaserChip->_pKurokoA->setMvAcce(200+(max_laser_way_-i)*150); //少しバラけるように
                        }
                    }
                }
            } else {
                //レーザーを打ち切った
                _pProg->changeNext();
            }
            break;
        }

        case PROG_HATCH_CLOSE: {
            if (_pProg->isJustChanged()) {
                _pSeTxer->play3D(SE_HATCH_CLOSE);
                _pMorpher->intoTargetLinerUntil(1, 0.0, 120);
            }
            if (_pProg->getFrameInProgress() == 120) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_NOTHING: {
            if (_pProg->getFrameInProgress() == 600) {
                _pProg->change(PROG_MOVE);
            }
            break;
        }
    }
    _pSeTxer->behave();
    _pKurokoA->behave();
    _pMorpher->behave();
}

void EnemyHesperia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyHesperia::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
        _pSeTxer->play3D(SE_DAMAGED);
    }
}

void EnemyHesperia::onInactive() {
    //レーザーデポジトリは遅れてから戻す
    for (int i = 0; i < max_laser_way_; i++) {
        if (papLaserChipDepo_[i]) {
            papLaserChipDepo_[i]->sayonara(60*10);
        }
    }
    sayonara();
}

coord EnemyHesperia::getTurnDY(GgafDxCore::GgafDxGeometricActor* pThis,
                               GgafDxCore::GgafDxGeometricActor* pMyShip,
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
    //DY = DT・tan(5°) - (敵_Y - 自機_Y)
    static double tan33 = tan(5.0*(PI/180.0)); //５度上から打ち下ろす
    coord dY = pThis->_Y - pMyShip->_Y;
    coord TurnDY = DT*tan33 - dY;
    if (TurnDY < 0) {
        return PX_C(200);
    } else {
        return TurnDY;
    }
}

EnemyHesperia::~EnemyHesperia() {
    pCon_LaserChipDepoStore_->close();
    DELETEARR_IMPOSSIBLE_NULL(paLocalPos_Laser_);
    DELETEARR_IMPOSSIBLE_NULL(paPos_Target_);
    DELETEARR_IMPOSSIBLE_NULL(papLaserChipDepo_);
}
