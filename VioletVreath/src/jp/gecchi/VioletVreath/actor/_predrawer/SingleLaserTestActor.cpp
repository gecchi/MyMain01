#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SingleLaserTestActor::SingleLaserTestActor(const char* prm_name) :
        SingleLaser(prm_name, "_chk_SingleLaserTestModel", NULL) { //SingleLaser�͍ő�27�Z�b�g�ł���
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaser�͍ő�27�Z�b�g�ł���
    _class_name = "SingleLaserTestActor";
}

void SingleLaserTestActor::initialize() {
    setHitAble(false);
//    _pColliChecker->makeCollision(1);
//    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);

}
void SingleLaserTestActor::onReset() {
//    setScaleR(100.0);
    setAlpha(0.99); //�������ɂ��邱�Ƃŗ��ʃ����_�����O
//    _pKurokoA->setMvVelo(40000);             //�ړ����x
//    _pKurokoA->setMvAcce(1000);             //�ړ����x
//    _pKurokoA->relateFaceAngWithMvAng(true);
}

void SingleLaserTestActor::onActive() {
    setHitAble(true, false);
}

void SingleLaserTestActor::processBehavior() {
    //���Z�����N�|�C���g������
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //�e�Ȃ̂ŕs�v

    //���W�ɔ��f
//    _pKurokoA->behave();
}

void SingleLaserTestActor::processJudgement() {
//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void SingleLaserTestActor::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
////    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //�j�󂳂ꂽ�ꍇ
//        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
//        EffectExplosion001* pExplo001 = getFromCommon(EffectExplosion001);
//        if (pExplo001) {
//            pExplo001->locatedBy(this);
//        }
//        sayonara();
//    }
}


SingleLaserTestActor::~SingleLaserTestActor() {
}
