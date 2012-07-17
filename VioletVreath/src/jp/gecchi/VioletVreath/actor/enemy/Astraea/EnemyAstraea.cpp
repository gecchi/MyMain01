#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyAstraea::EnemyAstraea(const char* prm_name) :
        DefaultMeshActor(prm_name, "Astraea", STATUS(EnemyAstraea)) {

    //レーザー
    laser_way_ = 3;
    _X = 0;
    _Y = 0;
    _Z = 0;
    laser_length_ = 30;
    laser_interval_ = 300;
    angveloTurn_ = 100;
    angClearance_ = 30000;//開き具合
    papapLaserChipDepo_ = NEW LaserChipDepository**[laser_way_];
    for (int i = 0; i < laser_way_; i++) {
        papapLaserChipDepo_[i] = NEW LaserChipDepository*[laser_way_];
        for (int j = 0; j < laser_way_; j++) {
            papapLaserChipDepo_[i][j] = NULL;
        }
    }

    pCon_RefractionEffectDepository_ = connectToDepositoryManager("DpCon_EffRefraction001", NULL);
    pCon_LaserChipDepoStore_ = connectToDepositoryManager(
            "DpCon_EnemyAstraeaLaserChip004DepoStore",
         //"DpCon_EnemyAstraeaLaserChip003DepoStore",
         //"DpCon_EnemyAstraeaLaserChip001DepoStore",
         //"DpCon_EnemyAstraeaLaserChip002DepoStore",
         pCon_RefractionEffectDepository_->fetch()
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
            UTIL::getNormalizeVectorZY(Rz, Ry, vx, vy, vz);
            papaPosLaser_[i][j].X = vx * PX_C(100);
            papaPosLaser_[i][j].Y = vy * PX_C(100);
            papaPosLaser_[i][j].Z = vz * PX_C(100);
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAng_way);

    pEffect_Appearance_ = NULL;

    _pSeTx->set(SE_EXPLOSION, "bomb1"     , GgafRepeatSeq::nextVal("CH_bomb1"));
    _pSeTx->set(SE_FIRE     , "yume_Sbend", GgafRepeatSeq::nextVal("CH_yume_Sbend"));

    useProgress(PROG_FIRE);
    pCon_ShotDepo_  = connectToDepositoryManager("DpCon_Shot004", NULL);
    pCon_ShotDepo2_ = connectToDepositoryManager("DpCon_Shot004Yellow", NULL);
    pCon_ShotDepo3_ = connectToDepositoryManager("DpCon_Shot004Blue", NULL);
}

void EnemyAstraea::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.97, 0.5, 12.0);
    _pModel->_pTextureBlinker->setBlink(1.0);
    _pModel->_pTextureBlinker->beat(60*6, 60*2, 60*2, -1);
}

void EnemyAstraea::initialize() {
    setHitAble(true);
    setAlpha(0.99);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(200));
    _pKurokoA->setRzRyMvAng(0, D180ANG);
    _pKurokoA->setMvVelo(PX_C(5));
}

void EnemyAstraea::onActive() {
    //ステータスリセット
    _pStatus->reset();
    if (pEffect_Appearance_) {
        pEffect_Appearance_->activate();
    }
    _pProg->set(PROG_MOVE);
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight - 10000;
}

void EnemyAstraea::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case PROG_MOVE: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->setFaceAngVelo(AXIS_X, 0);
                _pKurokoA->setFaceAngVelo(AXIS_Z, angveloTurn_*0.3);
                _pKurokoA->setFaceAngVelo(AXIS_Y, angveloTurn_*0.5);
                _pKurokoA->setMvVelo(5000);
                //_pKurokoA->setMvVelo(0);
            }
            if (getActivePartFrame() % laser_interval_ == 0) {
                _pProg->change(PROG_TURN);
            }
            break;
        }

        case PROG_TURN: {
            if (_pProg->isJustChanged()) {
                //ターン開始
                _pKurokoA->execTurnFaceAngSequence(P_MYSHIP, angveloTurn_*20, 0,
                                                   TURN_COUNTERCLOCKWISE, false);
                cnt_laserchip_ = 0;
            }
            if (_pKurokoA->isRunnigTurnFaceAngSequence()) {
                //ターン中
            } else {
                //自機にがいた方向に振り向きが完了時
                _pKurokoA->setFaceAngVelo(AXIS_X, angveloTurn_*40);
                _pKurokoA->setFaceAngVelo(AXIS_Z, 0);
                _pKurokoA->setFaceAngVelo(AXIS_Y, 0);
                _pKurokoA->setMvVelo(0);
                _pProg->change(PROG_FIRE);
            }
            break;
        }

        case PROG_FIRE: {
            if (_pProg->isJustChanged()) {
                //レーザーセット、借入
                GgafActorDepositoryStore* pLaserChipDepoStore =
                        (GgafActorDepositoryStore*)(pCon_LaserChipDepoStore_->fetch());
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
                    _pSeTx->play3D(SE_FIRE); //発射音
                    effectFlush(5); //フラッシュ
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
                                //ローカルでのショットの方向ベクトルを(Xorg_,Yorg_,Zorg_)、
                                //ワールド変換行列の回転部分（matWorldRot)の成分を mat_xx、
                                //最終的な方向ベクトルを(vX, vY, vZ) とすると
                                //
                                //                       | mat_11 mat_12 mat_13 |
                                // | Xorg_ Yorg_ Zorg_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                                //                       | mat_31 mat_32 mat_33 |
                                //よって
                                // vX = Xorg_*mat_11 + Yorg_*mat_21 + Zorg_*mat_31
                                // vY = Xorg_*mat_12 + Yorg_*mat_22 + Zorg_*mat_32
                                // vZ = Xorg_*mat_13 + Yorg_*mat_23 + Zorg_*mat_33
                                p = &(papaPosLaser_[i][j]);
                                vX = p->X*matWorldRot._11 + p->Y*matWorldRot._21 + p->Z*matWorldRot._31;
                                vY = p->X*matWorldRot._12 + p->Y*matWorldRot._22 + p->Z*matWorldRot._32;
                                vZ = p->X*matWorldRot._13 + p->Y*matWorldRot._23 + p->Z*matWorldRot._33;
                                UTIL::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                                pLaserChip->locate(_X+vX, _Y+vY, _Z+vZ);
                                pLaserChip->_pKurokoA->setRzRyMvAng(Rz, Ry);
                                pLaserChip->_pKurokoA->_angFace[AXIS_Z] = Rz;
                                pLaserChip->_pKurokoA->_angFace[AXIS_Y] = Ry;
                            }
                        }
                    }
                }
            } else {
                _pProg->change(PROG_MOVE);
            }
            break;
        }
    }
    _pSeTx->behave();
    _pKurokoA->behave();
}

void EnemyAstraea::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAstraea::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    static UINT32 spritedoller[24] = {
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


    static UINT32 red_dot[11] = {
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
    static UINT32 yellow_dot[11] = {
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
    static UINT32 blue_dot[11] = {
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



    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発エフェクト
        GgafDxDrawableActor* pExplo = UTIL::activateExplosionEffectOf(this);
        if (pExplo) {
            pExplo->locateWith(this);
            pExplo->_pKurokoA->followMvFrom(_pKurokoA);
        }
        _pSeTx->play3D(SE_EXPLOSION);
//          UTIL::shotWay002(this, pDepo_Shot_,
//                              PX_C(20),
//                              5, 5, D_ANG(6), D_ANG(6),
//                              3000, 200,
//                              3, 5, 0.9);


        UTIL::shotWay002(this,
                         pCon_ShotDepo_->fetch(), red_dot,
                         pCon_ShotDepo2_->fetch(), yellow_dot,
                         pCon_ShotDepo3_->fetch(), blue_dot,
                         PX_C(20),
                         11, 11,
                         D_ANG(1), D_ANG(1),
                         5000, 100,
                         2, 1, 0.9);
        sayonara();
        //消滅エフェクト
    } else {
        effectFlush(2); //フラッシュ
    }

}


void EnemyAstraea::onInactive() {
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


EnemyAstraea::~EnemyAstraea() {
    pCon_RefractionEffectDepository_->close();
    pCon_LaserChipDepoStore_->close();
    pCon_ShotDepo_->close();
    pCon_ShotDepo2_->close();
    pCon_ShotDepo3_->close();
    for (int i = 0; i < laser_way_; i++) {
        DELETEARR_IMPOSSIBLE_NULL(papaPosLaser_[i]);
        DELETEARR_IMPOSSIBLE_NULL(papapLaserChipDepo_[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(papaPosLaser_);
    DELETEARR_IMPOSSIBLE_NULL(papapLaserChipDepo_);
}
