#include "Shot003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot003::Shot003(const char* prm_name) :
        DefaultMassMeshActor(prm_name, "laser_single", STATUS(Shot003)) {
    _class_name = "Shot003";
}

void Shot003::initialize() {
    setHitAble(false);
    _sx = _sy = _sz = R_SC(50);
    setAlpha(0.99); //�������ɂ��邱�Ƃŗ��ʃ����_�����O
    setZEnableDraw(true);   //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    effectBlendOne();       //���Z����
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, PX_C(16));
}

void Shot003::onActive() {
    setHitAble(true);
    getKuroko()->setMvVelo(20000);

}

void Shot003::processBehavior() {
    //���Z�����N�|�C���g������
    //���W�ɔ��f
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->behave();
}

void Shot003::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot003::onHit(const GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
//    if (MyStgUtil::calcEnemyStamina(this, pOther) <= 0) {
//        //�j�󂳂ꂽ�ꍇ
//        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
//        EffectExplosion003* pExplo003 = (EffectExplosion003*)P_COMMON_SCENE->pDepo_EffectExplosion003_->dispatch();
//        playSe3D1();
//        if (pExplo003) {
//            pExplo003->positionAs(this);
//        }
//        sayonara();
//    }
}

Shot003::~Shot003() {
}
