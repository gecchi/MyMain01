#include "Shot004Yellow.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot004Yellow::Shot004Yellow(const char* prm_name) :
        DefaultMassMeshActor(prm_name, "Shot004Yellow", STATUS(Shot004)) { //SingleLaser�͍ő�27�Z�b�g�ł���
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaser�͍ő�27�Z�b�g�ł���
    _class_name = "Shot004Yellow";
    view_in_ = false;
}

void Shot004Yellow::initialize() {
    setHitAble(false);
    setZEnableDraw(true);   //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    effectBlendOne();       //���Z����
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}
void Shot004Yellow::onReset() {
    setScaleR(3.0);
    setAlpha(0.99); //�������ɂ��邱�Ƃŗ��ʃ����_�����O
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setRollFaceAngVelo(D_ANG(3));
    pKuroko->setMvVelo(40000);             //�ړ����x
    pKuroko->setMvAcce(1000);             //�ړ����x
    pKuroko->linkFaceAngByMvAng(true);
}

void Shot004Yellow::onActive() {
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004Yellow::processBehavior() {
    //���W�ɔ��f
    getKuroko()->behave();
}

void Shot004Yellow::processJudgement() {
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

void Shot004Yellow::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

Shot004Yellow::~Shot004Yellow() {
}
