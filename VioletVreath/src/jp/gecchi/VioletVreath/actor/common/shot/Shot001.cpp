#include "stdafx.h"
#include "Shot001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineConnection.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineManager.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot001::Shot001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Flora", STATUS(Shot001)) {
    _class_name = "Shot001";
    pScaler_ = NEW GgafDxScaler(this);

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(0, "WAVE_EXPLOSION_002");

    pSplLineConnection_ = (SplineLineConnection*)(P_GOD->pSpl3DManager_->connect("Spl_HAN", this)); //�X�v���C����`
    pKurokoLeader_ = NEW FixedVelocitySplineKurokoLeader(getKuroko(), pSplLineConnection_->peek(), 10000); //�ړ����x�Œ�
}

void Shot001::initialize() {
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB_Cube(0, PX_C(16));
    setScale(2000);
    pScaler_->forceRange(2000, 3000);
}

void Shot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceWithMvAng(true);
    pKuroko->setMvVelo(RF_Shot001_MvVelo(G_RANK));    //�ړ����x
    pKuroko->setFaceAngVelo(AXIS_X, RF_Shot001_AngVelo(G_RANK)); //������݋
    pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION);
    pScaler_->beat(30,5,0,2,-1);
}

void Shot001::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    //���W�ɔ��f
    pKurokoLeader_->behave(); //�X�v���C���ړ���U�镑��
    pKuroko->behave();
    pScaler_->behave();
}

void Shot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot001::onHit(GgafActor* prm_pOtherActor) {
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

    //getSeTx()->behave();
}


void Shot001::onInactive() {
}


Shot001::~Shot001() {
    GGAF_DELETE(pKurokoLeader_);
    GGAF_DELETE(pScaler_);
    pSplLineConnection_->close();
}
