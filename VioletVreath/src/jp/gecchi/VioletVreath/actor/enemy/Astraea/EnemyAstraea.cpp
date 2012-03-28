#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    ASTRAEA_PROG_MOVE = 1,
    ASTRAEA_PROG_TURN    ,
    ASTRAEA_PROG_FIRE    ,
};

EnemyAstraea::EnemyAstraea(const char* prm_name) :
        DefaultMeshActor(prm_name, "Astraea", STATUS(EnemyAstraea)) {

    //レーザー
    laser_way_ = 3;
    _X = 0;
    _Y = 0;
    _Z = 0;
    laser_length_ = 30;
    laser_interval_ = 300;
    ang_veloTurn_ = 100;
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
    angle* paAngWay = NEW angle[laser_way_];
    GgafDxUtil::getWayAngle2D(0, laser_way_, angClearance_, paAngWay);
    angle Rz,Ry;
    float vx, vy, vz;
    for (int i = 0; i < laser_way_; i++) {
        Rz = GgafDxUtil::simplifyAng(paAngWay[i]);
        papaPosLaser_[i] = NEW PosLaser[laser_way_];
        for (int j = 0; j < laser_way_; j++) {
            Ry = GgafDxUtil::simplifyAng(paAngWay[j]);
            GgafDxUtil::getNormalizeVectorZY(Rz, Ry, vx, vy, vz);
            papaPosLaser_[i][j].X = vx * P2C(100);
            papaPosLaser_[i][j].Y = vy * P2C(100);
            papaPosLaser_[i][j].Z = vz * P2C(100);
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);

    pEffect_Appearance_ = NULL;

    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "yume_Sbend", GgafRepeatSeq::nextVal("CH_yume_Sbend"));
    _pSeTransmitter->set(1, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));
    useProgress(ASTRAEA_PROG_FIRE);
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
    _pColliChecker->setColliSphere(0, P2C(200));
    _pKurokoA->setRzRyMvAng(0, D180ANG);
    _pKurokoA->setMvVelo(P2C(5));
}

void EnemyAstraea::onActive() {
    //ステータスリセット
    _pStatus->reset();
    if (pEffect_Appearance_) {
        pEffect_Appearance_->activate();
    }
    _pProg->set(ASTRAEA_PROG_MOVE);
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight - 10000;
}

void EnemyAstraea::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case ASTRAEA_PROG_MOVE: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->setFaceAngVelo(AXIS_X, 0);
                _pKurokoA->setFaceAngVelo(AXIS_Z, ang_veloTurn_*0.3);
                _pKurokoA->setFaceAngVelo(AXIS_Y, ang_veloTurn_*0.5);
                _pKurokoA->setMvVelo(5000);
                //_pKurokoA->setMvVelo(0);
            }
            if (getActivePartFrame() % laser_interval_ == 0) {
                _pProg->change(ASTRAEA_PROG_TURN);
            }
            break;
        }

        case ASTRAEA_PROG_TURN: {
            if (_pProg->isJustChanged()) {
                //ターン開始
                _pKurokoA->execTurnFaceAngSequence(P_MYSHIP, ang_veloTurn_*20, 0,
                                                   TURN_COUNTERCLOCKWISE, false);
                cnt_laserchip_ = 0;
            }
            if (_pKurokoA->isTurningFaceAng()) {
                //ターン中
            } else {
                //自機にがいた方向に振り向きが完了時
                _pKurokoA->setFaceAngVelo(AXIS_X, ang_veloTurn_*40);
                _pKurokoA->setFaceAngVelo(AXIS_Z, 0);
                _pKurokoA->setFaceAngVelo(AXIS_Y, 0);
                _pKurokoA->setMvVelo(0);
                _pProg->change(ASTRAEA_PROG_FIRE);
            }
            break;
        }

        case ASTRAEA_PROG_FIRE: {
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
                    _pSeTransmitter->play3D(0); //発射音
                    changeEffectTechniqueInterim("Flush", 5); //フラッシュ
                }
            }
            if (cnt_laserchip_ < laser_length_) {
                cnt_laserchip_++;
                LaserChip* pLaserChip;
                PosLaser* p;
                D3DXMATRIX matWorldRot;
                GgafDxUtil::setWorldMatrix_RxRzRy(this, matWorldRot);
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
                                GgafDxUtil::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                                pLaserChip->locate(_X+vX, _Y+vY, _Z+vZ);
                                pLaserChip->_pKurokoA->setRzRyMvAng(Rz, Ry);
                                pLaserChip->_pKurokoA->_angFace[AXIS_Z] = Rz;
                                pLaserChip->_pKurokoA->_angFace[AXIS_Y] = Ry;
                            }
                        }
                    }
                }
            } else {
                _pProg->change(ASTRAEA_PROG_MOVE);
            }
            break;
        }
    }
    _pSeTransmitter->behave();
    _pKurokoA->behave();
}

void EnemyAstraea::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAstraea::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    changeEffectTechniqueInterim("Flush", 2); //フラッシュ
    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        EffectExplosion001* pExplo001 = getFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locatedBy(this);
        }
        _pSeTransmitter->play3D(1);
        sayonara();
        //消滅エフェクト
    } else {

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
    for (int i = 0; i < laser_way_; i++) {
        DELETEARR_IMPOSSIBLE_NULL(papaPosLaser_[i]);
        DELETEARR_IMPOSSIBLE_NULL(papapLaserChipDepo_[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(papaPosLaser_);
    DELETEARR_IMPOSSIBLE_NULL(papapLaserChipDepo_);
}
