#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot003::Shot003(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "laser_single", STATUS(Shot003)) {
    _class_name = "Shot003";
}

void Shot003::initialize() {
    setHitAble(false);
    _SX = _SY = _SZ = R_SC(50);
    setAlpha(0.99); //�������ɂ��邱�Ƃŗ��ʃ����_�����O
    changeEffectTechnique("DestBlendOne"); //���Z����
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void Shot003::onActive() {
    setHitAble(true);
    _pKurokoA->setMvVelo(20000);             //�ړ����x

}

void Shot003::processBehavior() {
    //���Z�����N�|�C���g������
    //���W�ɔ��f
    _pKurokoA->behave();
}

void Shot003::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot003::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //�j�󂳂ꂽ�ꍇ
//        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
//        EffectExplosion003* pExplo003 = (EffectExplosion003*)P_COMMON_SCENE->pDepo_EffectExplosion003_->dispatch();
//        playSe3D1();
//        if (pExplo003) {
//            pExplo003->locatedBy(this);
//        }
//        sayonara();
//    }
}

Shot003::~Shot003() {
}
