#include "Shot002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot002::Shot002(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Flora", STATUS(Shot002)) {
    _class_name = "Shot002";
    pScaler_ = NEW GgafDxScaler(this);

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(0, "WAVE_EXPLOSION_002");
}

void Shot002::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB(0, -50000, -50000, -50000, 50000, 50000, 50000);
}

void Shot002::onActive() {
    getStatus()->reset();
    setHitAble(true);
    setScale(2000);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceByMvAng(true);
    pKuroko->setMvVelo(RF_Shot002_MvVelo(G_RANK));
    pKuroko->setFaceAngVelo(AXIS_X, RF_Shot002_AngVelo(G_RANK));
}

void Shot002::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    if (getActiveFrame() == 70) {
        pKuroko->turnMvAngTwd(P_MYSHIP,
                              3000, 0,
                              TURN_CLOSE_TO, true);
    }

    if (getActiveFrame() > 70 && !pKuroko->isTurningMvAng()) {
        pKuroko->turnMvAngTwd(P_MYSHIP,
                              100, 0,
                              TURN_CLOSE_TO, true);
    }
    //���W�ɔ��f
    pKuroko->behave();
    pScaler_->behave();
    getSeTx()->behave();
}

void Shot002::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot002::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false); //�ȍ~����t���[�����Ńq�b�g�����Ȃ��B
        UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g�o��
        getSeTx()->play3D(0);
        if (pOther->getKind() & KIND_MY) { //���@���Ɍ�����ď��ł̏ꍇ��
            UTIL::activateItemOf(this); //�A�C�e���o��
        }
        sayonara();
    }
}

Shot002::~Shot002() {
    GGAF_DELETE(pScaler_);
}
