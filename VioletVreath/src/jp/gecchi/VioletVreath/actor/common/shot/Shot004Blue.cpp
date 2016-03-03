#include "Shot004Blue.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot004Blue::Shot004Blue(const char* prm_name) :
        DefaultMassMeshActor(prm_name, "Shot004Blue", STATUS(Shot004)) { //SingleLaser�͍ő�27�Z�b�g�ł���
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaser�͍ő�27�Z�b�g�ł���
    _class_name = "Shot004Blue";
    view_in_ = false;
}

void Shot004Blue::initialize() {
    setHitAble(false);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, PX_C(16));
}
void Shot004Blue::onReset() {
    setScaleR(3.0);
    setAlpha(0.99); //�������ɂ��邱�Ƃŗ��ʃ����_�����O
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setRollFaceAngVelo(D_ANG(3));
    pKuroko->setMvVelo(40000);             //�ړ����x
    pKuroko->setMvAcce(1000);             //�ړ����x
    pKuroko->linkFaceAngByMvAng(true);
}

void Shot004Blue::onActive() {
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004Blue::processBehavior() {
    //���W�ɔ��f
    getKuroko()->behave();
}

void Shot004Blue::processJudgement() {
    if (isOutOfView()) {
        if (view_in_) {
            sayonara();
        }
        if (getActiveFrame() > 60) {
            sayonara();
        }
    } else {
        view_in_ = true;
    }
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot004Blue::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

Shot004Blue::~Shot004Blue() {
}
