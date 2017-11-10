#include "EnemyIda.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyIda::EnemyIda(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ida", STATUS(EnemyIda)) {
    _class_name = "EnemyIda";
    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    useProgress(PROG_BANPEI);
}

void EnemyIda::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyIda::initialize() {
    getKuroko()->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, 40000);
}

void EnemyIda::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyIda::processBehavior() {
    changeGeoLocal(); //���[�J�����W�n��

    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            pKuroko->setRollFaceAngVelo(D_ANG(4));
            setAlpha(0);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pProg->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pProg->hasArrivedAt(frame_of_entering)) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE01: {
            if (pProg->hasJustChanged()) {
            }
            //���@�֌�����
            GgafDxGeometricActor* pTargetActor = pMYSHIP;
            coord mvx = pTargetActor->_x - _x_final; //_x_final�͐�΍��W
            coord mvy = pTargetActor->_y - _y_final;
            coord mvz = pTargetActor->_z - _z_final;
            //�x�[�X�܂ł�(��]�~���s�ړ�)�s��̋t�s��擾
            D3DXMATRIX* pBaseInvMat = _pActor_base->getInvMatWorldRotMv();
            //���[�J�����W�Ō����Ă����ׂ������x�N�g���v�Z
            coord tvx = mvx*pBaseInvMat->_11 + mvy*pBaseInvMat->_21 + mvz*pBaseInvMat->_31;
            coord tvy = mvx*pBaseInvMat->_12 + mvy*pBaseInvMat->_22 + mvz*pBaseInvMat->_32;
            coord tvz = mvx*pBaseInvMat->_13 + mvy*pBaseInvMat->_23 + mvz*pBaseInvMat->_33;

            angle rz_target, ry_target;
            UTIL::convVectorToRzRy(tvx, tvy, tvz, rz_target, ry_target); //RzRy�ɒu��������
            pKuroko->setRzRyMvAng(rz_target, ry_target);
            break;
        }
    }

    getAlphaFader()->behave();
    pKuroko->behave();

    changeGeoFinal(); //��΍��W�n��
}

void EnemyIda::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyIda::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyIda::onInactive() {
}

EnemyIda::~EnemyIda() {
}


