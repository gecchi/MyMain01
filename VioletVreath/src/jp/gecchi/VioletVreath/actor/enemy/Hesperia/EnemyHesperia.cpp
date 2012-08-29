#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyHesperia::EnemyHesperia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "Hesperia", STATUS(EnemyHesperia)) {

    //レーザー
    max_laser_way_ = RR_EnemyHesperia_ShotWay(1.0);
    laser_way_ = 0;
    cnt_laserchip_ = 0;
    _X = 0;
    _Y = 0;
    _Z = 0;
    laser_length_ = 30;
    laser_interval_ = 300;
    angveloTurn_ = 5000;
    angClearance_ = 30000;//開き具合

    //借り入れレーザーセットのデポジトリ保持用
    papLaserChipDepo_ = NEW LaserChipDepository*[max_laser_way_];
    for (int i = 0; i < max_laser_way_; i++) {
        papLaserChipDepo_[i] = NULL;
    }

    pCon_LaserChipDepoStore_ = connectToDepositoryManager("DpCon_EnemyHesperiaLaserChip001DepoStore", NULL);

    paPosLaser_ = NEW PosLaser[max_laser_way_];
    coord dX = PX_C(10); //レーザー発射口の間隔
    int sign = 1;
    //                              dX
    //                            <----->
    //   [9]   [7]   [5]   [3]   [1]   [0]   [2]   [4]   [6]   [8]   発射口の順
    // ------------------------------+------------------------------>x
    //                               0
    for (int i = 0; i < max_laser_way_; i++) {
        if (i % 2 == 0) {  //0,2,4
            paPosLaser_[i].X = (dX/2) + (i/2 * dX);
        } else {           //1,3,5
            paPosLaser_[i].X = -(dX/2) - ((i-1)/2 * dX);
        }
        paPosLaser_[i].Y = PX_C(10);
        paPosLaser_[i].Z = 0;
    }

    _pSeTxer->set(SE_EXPLOSION, "bomb1"     , GgafRepeatSeq::nextVal("CH_bomb1"));
    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_FIRE     , "yume_Sbend", GgafRepeatSeq::nextVal("CH_yume_Sbend"));

    useProgress(PROG_FIRE);
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
    _X = PX_C(800); //GgafDxCore::GgafDxUniverse::_X_goneRight - 100;
    _pProg->set(PROG_ENTRY);
}

void EnemyHesperia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
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
                _pMorpher->intoTargetLinerUntil(1, 1.0, 120);
            }
            if (_pProg->getFrameInProgress() == 120) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            if (_pProg->isJustChanged()) {
                //レーザーセット、借入
                laser_way_ = RR_EnemyHesperia_ShotWay(_RANK_);
                GgafActorDepositoryStore* pLaserChipDepoStore =
                        (GgafActorDepositoryStore*)(pCon_LaserChipDepoStore_->fetch());
                bool can_fire = false;
                for (int i = 0; i < laser_way_; i++) {
                    papLaserChipDepo_[i] = (LaserChipDepository*)(pLaserChipDepoStore->dispatch());
                    if (papLaserChipDepo_[i]) {
                        papLaserChipDepo_[i]->config(laser_length_, 1);
                        can_fire = true;
                    }
                }
                if (can_fire) {
                    _pSeTxer->play3D(SE_FIRE); //発射音
                    effectFlush(2); //フラッシュ
                }
            }

            if (cnt_laserchip_ < laser_length_) {
                cnt_laserchip_++;
                LaserChip* pLaserChip;
                PosLaser* p;
                for (int i = 0; i < laser_way_; i++) {
                    if (papLaserChipDepo_[i]) {
                        pLaserChip = papLaserChipDepo_[i]->dispatch();
                        if (pLaserChip) {
                            p = &(paPosLaser_[i]);
                            pLaserChip->locate(_X + p->X, _Y + p->Y, _Z + p->Z);
                            pLaserChip->_pKurokoA->setRzRyMvAng(D90ANG, 0);
                            pLaserChip->_pKurokoA->_angFace[AXIS_Z] = D90ANG;
                            pLaserChip->_pKurokoA->_angFace[AXIS_Y] = 0;
                        }
                    }
                }
            } else {
                //ハッチを閉じる
                _pMorpher->intoTargetLinerUntil(1, 0, 120);
                _pProg->change(PROG_NOTHING);
            }
            break;
        }
    }
    _pSeTxer->behave();
    _pKurokoA->behave();
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
    for (int i = 0; i < laser_way_; i++) {
        if (papLaserChipDepo_[i]) {
            papLaserChipDepo_[i]->sayonara(60*10);
        }
    }
    sayonara();
}


EnemyHesperia::~EnemyHesperia() {
    pCon_LaserChipDepoStore_->close();
    DELETEARR_IMPOSSIBLE_NULL(paPosLaser_);
    DELETEARR_IMPOSSIBLE_NULL(papLaserChipDepo_);
}
