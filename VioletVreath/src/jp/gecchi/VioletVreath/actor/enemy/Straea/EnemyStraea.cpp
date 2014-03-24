#include "stdafx.h"
#include "EnemyStraea.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyStraea::EnemyStraea(const char* prm_name) :
        DefaultMeshActor(prm_name, "Straea", STATUS(EnemyStraea)) {
    pAFader_ = NEW GgafDxAlphaFader(this);
    //レーザー
    laser_way_ = 3;
    cnt_laserchip_ = 0;
    _x = 0;
    _y = 0;
    _z = 0;
    laser_length_ = 30;
    laser_interval_ = 300;
    angveloTurn_ = 5000;
    angClearance_ = 30000;//開き具合
    papapLaserChipDepo_ = NEW LaserChipDepository**[laser_way_];
    for (int i = 0; i < laser_way_; i++) {
        papapLaserChipDepo_[i] = NEW LaserChipDepository*[laser_way_];
        for (int j = 0; j < laser_way_; j++) {
            papapLaserChipDepo_[i][j] = nullptr;
        }
    }

    pConn_RefractionEffectDepository_ = connect_DepositoryManager("EffRefraction001");
    pConn_LaserChipDepoStore_ = connect_DepositoryManager(
            "EnemyStraeaLaserChip004DepoStore"//,
         //"EnemyStraeaLaserChip003DepoStore",
         //"EnemyStraeaLaserChip001DepoStore",
         //"EnemyStraeaLaserChip002DepoStore",
         //pConn_RefractionEffectDepository_->peek()
        );

    papaPosLaser_ = NEW PosLaser*[laser_way_];
    angle* paAng_way = NEW angle[laser_way_];
    UTIL::getWayAngle2D(0, laser_way_, angClearance_, paAng_way);
    angle Rz,Ry;
    float vx, vy, vz;
    for (int i = 0; i < laser_way_; i++) {
        Rz = UTIL::simplifyAng(paAng_way[i]);
        papaPosLaser_[i] = NEW PosLaser[laser_way_];
        for (int j = 0; j < laser_way_; j++) {
            Ry = UTIL::simplifyAng(paAng_way[j]);
            UTIL::convRzRyToVector(Rz, Ry, vx, vy, vz);
            papaPosLaser_[i][j].x = vx * PX_C(100);
            papaPosLaser_[i][j].y = vy * PX_C(100);
            papaPosLaser_[i][j].z = vz * PX_C(100);
        }
    }
    GGAF_DELETEARR(paAng_way);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_BANPEI);
    pConn_ShotDepo2_ = connect_DepositoryManager("Shot004Yellow");
    pConn_ShotDepo3_ = connect_DepositoryManager("Shot004Blue");
}

void EnemyStraea::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(1.0, 0.97);
    pModel->_pTexBlinker->forceRange(0.5, 12.0);
    pModel->_pTexBlinker->beat(60*6, 60*2, 0, 60*2, -1);
}

void EnemyStraea::initialize() {
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliSphere(0, PX_C(200));
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setRzRyMvAng(0, D180ANG);
    pKuroko->setMvVelo(PX_C(5));
}

void EnemyStraea::onActive() {
    getStatus()->reset();
    setHitAble(false);
    _x = GgafDxCore::GgafDxUniverse::_x_gone_right - 1000;
    getProgress()->reset(PROG_ENTRY);
}

void EnemyStraea::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_ENTRY: {
            if (pProg->isJustChanged()) {
                UTIL::activateEntryEffectOf(this);
                setAlpha(0);
                pAFader_->transitionLinerUntil(0.98, 20);
                pKuroko->setFaceAngVelo(AXIS_X, 4000);
            }
            if (!pAFader_->isTransitioning()) {
                setHitAble(true);
                pProg->changeNext();
            }
            pAFader_->behave();
            break;
        }
        case PROG_MOVE: {
            if (pProg->isJustChanged()) {
                angle v = angveloTurn_ / 50;
                pKuroko->setFaceAngVelo(RND(-v, v), RND(-v, v), RND(-v, v));
                pKuroko->setMvVelo(2000);
                //_pKuroko->setMvVelo(0);
            }
            if (getActiveFrame() % laser_interval_ == 0) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_TURN: {
            if (pProg->isJustChanged()) {
                //ターン開始
                pKuroko->turnFaceAngTwd(P_MYSHIP,
                                          angveloTurn_, 0, TURN_ANTICLOSE_TO, false);
                cnt_laserchip_ = 0;
            }
            if (pKuroko->isTurningFaceAng()) {
                //ターン中
            } else {
                //自機にがいた方向に振り向きが完了時
                pKuroko->setFaceAngVelo(angveloTurn_*2, 0, 0);
                pKuroko->setMvVelo(0);
                pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            if (pProg->isJustChanged()) {
                //レーザーセット、借入
                GgafActorDepositoryStore* pLaserChipDepoStore =
                        (GgafActorDepositoryStore*)(pConn_LaserChipDepoStore_->peek());
                bool can_fire = false;
                for (int i = 0; i < laser_way_; i++) {
                    for (int j = 0; j < laser_way_; j++) {
                        papapLaserChipDepo_[i][j] = (LaserChipDepository*)(pLaserChipDepoStore->dispatch());
                        if (papapLaserChipDepo_[i][j]) {
                            papapLaserChipDepo_[i][j]->config(laser_length_, 1);
                            can_fire = true;
                        }
                    }
                }
                if (can_fire) {
                    getSeTx()->play3D(SE_FIRE); //発射音
                    effectFlush(2); //フラッシュ
                }
            }
            if (cnt_laserchip_ < laser_length_) {
                cnt_laserchip_++;
                LaserChip* pLaserChip;
                PosLaser* p;
                D3DXMATRIX matWorldRot;
                UTIL::setWorldMatrix_RxRzRy(this, matWorldRot);
                angle Rz, Ry;
                int vX, vY, vZ;
                for (int i = 0; i < laser_way_; i++) {
                    for (int j = 0; j < laser_way_; j++) {
                        if (papapLaserChipDepo_[i][j]) {
                            pLaserChip = papapLaserChipDepo_[i][j]->dispatch();
                            if (pLaserChip) {
                                //レーザーの向きを計算
                                //ローカルでのショットの方向ベクトルを(x_org_,y_org_,z_org_)、
                                //ワールド変換行列の回転部分（matWorldRot)の成分を mat_xx、
                                //最終的な方向ベクトルを(vX, vY, vZ) とすると
                                //
                                //                       | mat_11 mat_12 mat_13 |
                                // | x_org_ y_org_ z_org_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                                //                       | mat_31 mat_32 mat_33 |
                                //よって
                                // vX = x_org_*mat_11 + y_org_*mat_21 + z_org_*mat_31
                                // vY = x_org_*mat_12 + y_org_*mat_22 + z_org_*mat_32
                                // vZ = x_org_*mat_13 + y_org_*mat_23 + z_org_*mat_33
                                p = &(papaPosLaser_[i][j]);
                                vX = p->x*matWorldRot._11 + p->y*matWorldRot._21 + p->z*matWorldRot._31;
                                vY = p->x*matWorldRot._12 + p->y*matWorldRot._22 + p->z*matWorldRot._32;
                                vZ = p->x*matWorldRot._13 + p->y*matWorldRot._23 + p->z*matWorldRot._33;
                                UTIL::convVectorToRzRy(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                                pLaserChip->position(_x+vX, _y+vY, _z+vZ);
                                pLaserChip->getKuroko()->setRzRyMvAng(Rz, Ry);
                                pLaserChip->_rz = Rz;
                                pLaserChip->_ry = Ry;
                            }
                        }
                    }
                }
            } else {
                pProg->change(PROG_MOVE);
            }
            break;
        }
    }
    getSeTx()->behave();
    pKuroko->behave();
}

void EnemyStraea::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyStraea::onHit(GgafActor* prm_pOtherActor) {
    static uint32_t spritedoller[24] = {
                                     6144      ,       //  000000000001100000000000
                                     14336     ,       //  000000000011100000000000
                                     13312     ,       //  000000000011010000000000
                                     25088     ,       //  000000000110001000000000
                                     49408     ,       //  000000001100000100000000
                                     98432     ,       //  000000011000000010000000
                                     196704    ,       //  000000110000000001100000
                                     393528    ,       //  000001100000000100111000
                                     917407    ,       //  000011011111111110011111
                                     3145734   ,       //  001100000000000000000110
                                     12582912  ,       //  110000000000000000000000
                                     1098776   ,       //  000100001100010000011000
                                     2091004   ,       //  000111111110011111111100
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     2082552   ,       //  000111111100011011111000
                                     1623600   ,       //  000110001100011000110000
                                     1536      ,       //  000000000000011000000000
                                     1536              //  000000000000011000000000
    };


    static uint32_t red_dot[11] = {
            32  ,       //  00000100000
            112 ,       //  00001110000
            248 ,       //  00011111000
            428 ,       //  00110101100
            32  ,       //  00000100000
            0   ,       //  00000000000
            0   ,       //  00000000000
            0   ,       //  00000000000
            0   ,       //  00000000000
            0   ,       //  00000000000
            0           //  00000000000
    };
    static uint32_t yellow_dot[11] = {
            0   ,       //  00000000000
            0   ,       //  00000000000
            0   ,       //  00000000000
            594 ,       //  01001010010
            990 ,       //  01111011110
            508 ,       //  00111111100
            168 ,       //  00010101000
            32  ,       //  00000100000
            32  ,       //  00000100000
            32  ,       //  00000100000
            32          //  00000100000
        };
    static uint32_t blue_dot[11] = {
            0   ,       //  00000000000
            1025,       //  10000000001
            1025,       //  10000000001
            1025,       //  10000000001
            1025,       //  10000000001
            1539,       //  11000000011
            774 ,       //  01100000110
            396 ,       //  00110001100
            136 ,       //  00010001000
            0   ,       //  00000000000
            0           //  00000000000
        };


    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        getSeTx()->play3D(SE_EXPLOSION);
        //打ち返し
        UTIL::shotWay003(this,
                         getCommonDepository(Shot004) , red_dot,
                         pConn_ShotDepo2_->peek(), yellow_dot,
                         pConn_ShotDepo3_->peek(), blue_dot,
                         PX_C(20),
                         11, 11,
                         D_ANG(1), D_ANG(1),
                         5000, 100,
                         2, 1, 0.9);
    } else {
        //非破壊時
    }
}


void EnemyStraea::onInactive() {
    //レーザーデポジトリは遅れてから戻す
    for (int i = 0; i < laser_way_; i++) {
        for (int j = 0; j < laser_way_; j++) {
            if (papapLaserChipDepo_[i][j]) {
                papapLaserChipDepo_[i][j]->sayonara(60*10);
            }
        }
    }
    sayonara();
}


EnemyStraea::~EnemyStraea() {
    GGAF_DELETE(pAFader_);
    pConn_RefractionEffectDepository_->close();
    pConn_LaserChipDepoStore_->close();
    pConn_ShotDepo2_->close();
    pConn_ShotDepo3_->close();
    for (int i = 0; i < laser_way_; i++) {
        GGAF_DELETEARR(papaPosLaser_[i]);
        GGAF_DELETEARR(papapLaserChipDepo_[i]);
    }
    GGAF_DELETEARR(papaPosLaser_);
    GGAF_DELETEARR(papapLaserChipDepo_);
}
