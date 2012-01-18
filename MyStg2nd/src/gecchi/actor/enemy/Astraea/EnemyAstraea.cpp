#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    ASTRAEA_PROG_MOVE = 1,
    ASTRAEA_PROG_TURN    ,
    ASTRAEA_PROG_FIRE    ,
};

EnemyAstraea::EnemyAstraea(const char* prm_name) :
        DefaultMeshActor(prm_name, "Astraea", STATUS(EnemyAstraea)) {

    //レーザー
    _laser_way = 3;
    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 30;
    _laser_interval = 300;
    _ang_veloTurn = 100;
    _angClearance = 30000;//開き具合
    _papapLaserChipDepo = NEW LaserChipDepository**[_laser_way];
    for (int i = 0; i < _laser_way; i++) {
        _papapLaserChipDepo[i] = NEW LaserChipDepository*[_laser_way];
        for (int j = 0; j < _laser_way; j++) {
            _papapLaserChipDepo[i][j] = NULL;
        }
    }

    _pCon_RefractionEffectDepository = connectToDepositoryManager("DpCon_EffRefraction001", NULL);
    _pCon_LaserChipDepoStore = connectToDepositoryManager(
            "DpCon_EnemyAstraeaLaserChip004DepoStore",
         //"DpCon_EnemyAstraeaLaserChip003DepoStore",
         //"DpCon_EnemyAstraeaLaserChip001DepoStore",
         //"DpCon_EnemyAstraeaLaserChip002DepoStore",
         _pCon_RefractionEffectDepository->use()
        );

    _papaPosLaser = NEW PosLaser*[_laser_way];
    angle* paAngWay = NEW angle[_laser_way];
    GgafDxUtil::getWayAngle2D(0, _laser_way, _angClearance, paAngWay);
    angle Rz,Ry;
    float vx, vy, vz;
    for (int i = 0; i < _laser_way; i++) {
        Rz = GgafDxUtil::simplifyAng(paAngWay[i]);
        _papaPosLaser[i] = NEW PosLaser[_laser_way];
        for (int j = 0; j < _laser_way; j++) {
            Ry = GgafDxUtil::simplifyAng(paAngWay[j]);
            GgafDxUtil::getNormalizeVectorZY(Rz, Ry, vx, vy, vz);
            _papaPosLaser[i][j].X = vx * PX2CO(100);
            _papaPosLaser[i][j].Y = vy * PX2CO(100);
            _papaPosLaser[i][j].Z = vz * PX2CO(100);
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);

    _pEffect_Appearance = NULL;

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
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, PX2CO(200));
    _pKurokoA->setRzRyMvAng(0, D180ANG);
    _pKurokoA->setMvVelo(PX2CO(5));
}

void EnemyAstraea::onActive() {
    //ステータスリセット
    _pStatus->reset();
    if (_pEffect_Appearance) {
        _pEffect_Appearance->activate();
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
                _pKurokoA->setFaceAngVelo(AXIS_Z, _ang_veloTurn*0.3);
                _pKurokoA->setFaceAngVelo(AXIS_Y, _ang_veloTurn*0.5);
                _pKurokoA->setMvVelo(5000);
                //_pKurokoA->setMvVelo(0);
            }
            if (getActivePartFrame() % _laser_interval == 0) {
                _pProg->change(ASTRAEA_PROG_TURN);
            }
            break;
        }

        case ASTRAEA_PROG_TURN: {
            if (_pProg->isJustChanged()) {
                //ターン開始
                _pKurokoA->execTurnFaceAngSequence(P_MYSHIP, _ang_veloTurn*20, 0,
                                                   TURN_COUNTERCLOCKWISE, false);
                _cnt_laserchip = 0;
            }
            if (_pKurokoA->isTurningFaceAng()) {
                //ターン中
            } else {
                //自機にがいた方向に振り向きが完了時
                _pKurokoA->setFaceAngVelo(AXIS_X, _ang_veloTurn*40);
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
                        (GgafActorDepositoryStore*)(_pCon_LaserChipDepoStore->use());
                bool can_fire = false;
                for (int i = 0; i < _laser_way; i++) {
                    for (int j = 0; j < _laser_way; j++) {
                        _papapLaserChipDepo[i][j] = (LaserChipDepository*)(pLaserChipDepoStore->dispatch());
                        if (_papapLaserChipDepo[i][j]) {
                            _papapLaserChipDepo[i][j]->config(_laser_length, 1);
                            can_fire = true;
                        }
                    }
                }
                if (can_fire) {
                    _pSeTransmitter->play3D(0); //発射音
                    changeEffectTechniqueInterim("Flush", 5); //フラッシュ
                }
            }
            if (_cnt_laserchip < _laser_length) {
                _cnt_laserchip++;
                LaserChip* pLaserChip;
                PosLaser* p;
                D3DXMATRIX matWorldRot;
                GgafDxUtil::setWorldMatrix_RxRzRy(this, matWorldRot);
                angle Rz, Ry;
                int vX, vY, vZ;
                for (int i = 0; i < _laser_way; i++) {
                    for (int j = 0; j < _laser_way; j++) {
                        if (_papapLaserChipDepo[i][j]) {
                            pLaserChip = _papapLaserChipDepo[i][j]->dispatch();
                            if (pLaserChip) {
                                //レーザーの向きを計算
                                //ローカルでのショットの方向ベクトルを(_Xorg,_Yorg,_Zorg)、
                                //ワールド変換行列の回転部分（matWorldRot)の成分を mat_xx、
                                //最終的な方向ベクトルを(vX, vY, vZ) とすると
                                //
                                //                       | mat_11 mat_12 mat_13 |
                                // | _Xorg _Yorg _Zorg | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                                //                       | mat_31 mat_32 mat_33 |
                                //よって
                                // vX = _Xorg*mat_11 + _Yorg*mat_21 + _Zorg*mat_31
                                // vY = _Xorg*mat_12 + _Yorg*mat_22 + _Zorg*mat_32
                                // vZ = _Xorg*mat_13 + _Yorg*mat_23 + _Zorg*mat_33
                                p = &(_papaPosLaser[i][j]);
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
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        _pSeTransmitter->play3D(1);
        sayonara();
        //消滅エフェクト
    } else {

    }

}


void EnemyAstraea::onInactive() {
    //レーザーデポジトリは遅れてから戻す
    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            if (_papapLaserChipDepo[i][j]) {
                _papapLaserChipDepo[i][j]->sayonara(60*10);
            }
        }
    }
    sayonara();
}


EnemyAstraea::~EnemyAstraea() {
    _pCon_RefractionEffectDepository->close();
    _pCon_LaserChipDepoStore->close();
    for (int i = 0; i < _laser_way; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaPosLaser[i]);
        DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDepo[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaPosLaser);
    DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDepo);
}
