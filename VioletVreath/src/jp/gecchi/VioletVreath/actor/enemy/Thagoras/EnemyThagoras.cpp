#include "stdafx.h"
#include "EnemyThagoras.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/FormationThagoras.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThagoras::EnemyThagoras(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Thagoras", STATUS(EnemyThagoras)) {
    _class_name = "EnemyThagoras";
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(_BANPEI_-1);
    pKurokoLeader_ = nullptr; //フォーメーションオブジェクトが設定する
}

void EnemyThagoras::onCreateModel() {
//    _pModel->setSpecular(5.0, 1.0);
}

void EnemyThagoras::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    _pKurokoA->relateMvFaceAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 2000);
    _pKurokoA->forceMvVeloRange(PX_C(15));
}

void EnemyThagoras::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
    pActor4Sc_ = ((FormationThagoras*)(getFormation()))->pActor4Sc_;
}

void EnemyThagoras::processBehavior() {
    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            _pAFader->setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (_pProg->isJustChanged()) {
                _pAFader->fadeLinerUntil(1.0, 30);
            }
            if (_pProg->getFrameInProgress() == 10) {
                setHitAble(true);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE01: {
            if (_pProg->isJustChanged()) {
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_COORD,2);
            }
            if (pKurokoLeader_->isFinished()) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_LEAVE: {
            if (_pProg->isJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                _pAFader->fadeLinerUntil(0.0, 30);
            }
            if (_pProg->getFrameInProgress() == 60) {
                sayonara();
                _pProg->changeNothing(); //おしまい！
            }
            break;
        }
        default :
            break;
    }
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    pKurokoLeader_->behave(); //スプライン移動を振る舞い
    _pAFader->behave();
    _pKurokoA->behave();

    _SX = pActor4Sc_->_SX;
    _SY = pActor4Sc_->_SY;
    _SZ = pActor4Sc_->_SZ;
}

void EnemyThagoras::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyThagoras::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyThagoras::onInactive() {
    sayonara();
}

EnemyThagoras::~EnemyThagoras() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
