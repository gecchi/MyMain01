#include "stdafx.h"
#include "EnemyOzartiaShot01.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyOzartiaShot01::EnemyOzartiaShot01(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "myvic", STATUS(EnemyOzartiaShot01)) {
    _class_name = "EnemyOzartiaShot01";
    pAFader_ = NEW GgafDxAlphaFader(this);
}

void EnemyOzartiaShot01::initialize() {
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
    getProgress()->reset(PROG_INIT);
}

void EnemyOzartiaShot01::onActive() {
    getStatus()->reset();
}

void EnemyOzartiaShot01::processBehavior() {
    UTIL::updateEnemyRankPoint(this);
    //�{�̈ړ��n�̏��� �������� --->
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (pProg->isJustChanged()) {
                pAFader_->transitionLinerUntil(1.0, 15);
            }
            if (pProg->getFrameInProgress() == 8) {
                setHitAble(true);
                pProg->change(PROG_MOVE01);
            }
            break;
        }
        case PROG_MOVE01: {
            if (pProg->isJustChanged()) {
            }
            if (pProg->getFrameInProgress() == 60*10) {
                pProg->change(PROG_LEAVE);
            }
            break;
        }
        case PROG_LEAVE: {
             if (pProg->isJustChanged()) {
                 UTIL::activateLeaveEffectOf(this);
                 pAFader_->transitionLinerUntil(0.0, 15);
             }
             if (pProg->getFrameInProgress() == 60) {
                 sayonara();
                 pProg->changeNothing(); //�����܂��I
             }
             break;
         }
        default :
            break;
    }
    pKuroko->behave();
}

void EnemyOzartiaShot01::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyOzartiaShot01::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //��������
        UTIL::activateExplosionEffectOf(this);
//        getSeTx()->play3D(ERESSHOT001_SE_EXPLOSION);

        sayonara();
    }
}

void EnemyOzartiaShot01::onInactive() {
    sayonara();
}

EnemyOzartiaShot01::~EnemyOzartiaShot01() {
    GGAF_DELETE(pAFader_);
}