#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot003::Shot003(const char* prm_name) : DefaultMeshSetActor(prm_name, "laser_single") {
    _class_name = "Shot003";
    MyStgUtil::resetShot003Status(_pStatus);
}

void Shot003::initialize() {
    setHitAble(false);
    _SX = _SY = _SZ = 50 * 1000;
    setAlpha(0.99); //�������ɂ��邱�Ƃŗ��ʃ����_�����O
    chengeEffectTechnique("DestBlendOne"); //���Z����
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void Shot003::onActive() {
    setHitAble(true);
    _pMover->setMvVelo(20000);             //�ړ����x

}

void Shot003::processBehavior() {
    //���Z�����N�|�C���g������
    //���W�ɔ��f
    _pMover->behave();
}

void Shot003::processJudgement() {
    if (isOutOfGameSpace()) {
        sayonara();
    }
}

void Shot003::onHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //�j�󂳂ꂽ�ꍇ
//        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
//        EffectExplosion003* pExplo003 = (EffectExplosion003*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion003->employ();
//        playSe3D1();
//        if (pExplo003 != NULL) {
//            pExplo003->activate();
//            pExplo003->setGeometry(this);
//        }
//        sayonara();
//    }
}

Shot003::~Shot003() {
}
