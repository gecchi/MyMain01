#include "stdafx.h"
#include "EnemyAida.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAida::EnemyAida(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Aida", STATUS(EnemyAida)) {
    _class_name = "EnemyAida";
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    useProgress(PROG_MOVE01);
    pEntryEffect_ = nullptr;
}

void EnemyAida::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAida::initialize() {
    _pKurokoA->relateMvFaceAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAida::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemyAida::processBehavior() {
    changeGeoLocal();

    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(4));
            _pAFader->setAlpha(0);
            pEntryEffect_ = UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (_pProg->isJustChanged()) {
                _pAFader->fadeLinerUntil(1.0, 30);
            }
            if (_pProg->getFrameInProgress() == 25) {
                setHitAble(true);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE01: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->setMvVelo(1000);
                _pKurokoA->setRzRyMvAngVelo(1000,2000);
            }
            //自機へ向ける
            GgafDxGeometricActor* pTargetActor = P_MYSHIP;
            coord MvX = pTargetActor->_X - _X_final; //ここでの _X, _Y, _Z は絶対座標である
            coord MvY = pTargetActor->_Y - _Y_final;
            coord MvZ = pTargetActor->_Z - _Z_final;
            //逆行列取得
            D3DXMATRIX* pBaseInvMatRM = _pActor_Base->getInvMatWorldRotMv();
            //ローカル座標でのターゲットとなる方向ベクトル計算
            coord TvX = MvX*pBaseInvMatRM->_11 + MvY*pBaseInvMatRM->_21 + MvZ * pBaseInvMatRM->_31;
            coord TvY = MvX*pBaseInvMatRM->_12 + MvY*pBaseInvMatRM->_22 + MvZ * pBaseInvMatRM->_32;
            coord TvZ = MvX*pBaseInvMatRM->_13 + MvY*pBaseInvMatRM->_23 + MvZ * pBaseInvMatRM->_33;

            angle angRz_Target, angRy_Target;
            UTIL::convVectorToRzRy(TvX, TvY, TvZ, angRz_Target, angRy_Target); //RzRyに置き換える
            _pKurokoA->setRzRyMvAng(angRz_Target, angRy_Target);
            break;
        }
    }

    _pAFader->behave();


    _pKurokoA->behave();
    changeGeoFinal();

}

void EnemyAida::processJudgement() {
    if (pEntryEffect_) {
        if (pEntryEffect_->onChangeToInactive()) {
            pEntryEffect_ = nullptr;
        } else {
            pEntryEffect_->locateAs(this);
        }
    }
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAida::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyAida::onInactive() {
}

EnemyAida::~EnemyAida() {
}


