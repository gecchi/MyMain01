#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot004::Shot004(const char* prm_name) :
        SingleLaser(prm_name, "Shot004") { //SingleLaser�͍ő�27�Z�b�g�ł���
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaser�͍ő�27�Z�b�g�ł���
    _class_name = "Shot004";
    MyStgUtil::resetShot004Status(_pStatus);
}

void Shot004::initialize() {
    setHitAble(false);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);

}
void Shot004::onReset() {
    setScaleRate(100.0);
    setAlpha(0.99); //�������ɂ��邱�Ƃŗ��ʃ����_�����O
    _pMvNavigator->setMvVelo(40000);             //�ړ����x
    _pMvNavigator->setMvAcce(1000);             //�ړ����x
    _pMvNavigator->relateFaceAngWithMvAng(true);
}

void Shot004::onActive() {
    setHitAble(true, false);
}

void Shot004::processBehavior() {
    //���Z�����N�|�C���g������
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //�e�Ȃ̂ŕs�v

    //���W�ɔ��f
    _pMvNavigator->behave();
}

void Shot004::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot004::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
        if (pExplo001) {
            pExplo001->activate();
            pExplo001->locateAs(this);
        }
        sayonara();
    }
}


void Shot004::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}
Shot004::~Shot004() {
}
