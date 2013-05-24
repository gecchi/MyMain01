#include "stdafx.h"
#include "Shot002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
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
    _pSeTx->set(0, "WAVE_EXPLOSION_002");
}

void Shot002::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -50000, -50000, -50000, 50000, 50000, 50000);
}

void Shot002::onActive() {
    _pStatus->reset();
    setHitAble(true);
    _pScaler->setScale(2000);
    _pKurokoA->relateMvFaceAng(true);
    _pKurokoA->setMvVelo(RF_Shot002_MvVelo(_RANK_));
    _pKurokoA->setFaceAngVelo(AXIS_X, RF_Shot002_AngVelo(_RANK_));
}

void Shot002::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (getActiveFrame() == 70) {
        _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                3000, 0,
                                TURN_CLOSE_TO, true);
    }

    if (getActiveFrame() > 70 && !_pKurokoA->isTurningMvAng()) {
        _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                100, 0,
                                TURN_CLOSE_TO, true);
    }
    //���W�ɔ��f
    _pKurokoA->behave();
    _pScaler->behave();
    _pSeTx->behave();
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
        _pSeTx->play3D(0);
        if (pOther->getKind() & KIND_MY) { //���@���Ɍ�����ď��ł̏ꍇ��
            UTIL::activateItemOf(this); //�A�C�e���o��
        }
        sayonara();
    }
}

Shot002::~Shot002() {

}
