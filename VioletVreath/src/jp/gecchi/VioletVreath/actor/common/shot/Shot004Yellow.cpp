#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot004Yellow::Shot004Yellow(const char* prm_name) :
        SingleLaser(prm_name, "Shot004Yellow", STATUS(Shot004)) { //SingleLaser�͍ő�27�Z�b�g�ł���
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaser�͍ő�27�Z�b�g�ł���
    _class_name = "Shot004Yellow";
    view_in_ = false;
}

void Shot004Yellow::initialize() {

    setHitAble(false);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}
void Shot004Yellow::onReset() {
    setScaleR(3.0);
    setAlpha(0.99); //�������ɂ��邱�Ƃŗ��ʃ����_�����O
    _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(3));
    _pKurokoA->setMvVelo(40000);             //�ړ����x
    _pKurokoA->setMvAcce(1000);             //�ړ����x
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void Shot004Yellow::onActive() {
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004Yellow::processBehavior() {
    //���Z�����N�|�C���g������
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //�e�Ȃ̂ŕs�v

    //���W�ɔ��f
    _pKurokoA->behave();
}

void Shot004Yellow::processJudgement() {
    if (isOutOfView()) {
        if (view_in_) {
            sayonara();
        }
        if (getActivePartFrame() > 60) {
            sayonara();
        }
    } else {
        view_in_ = true;
    }
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot004Yellow::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (UTIL::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locateWith(this);
        }
        sayonara();
    }
}


void Shot004Yellow::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}
Shot004Yellow::~Shot004Yellow() {
}
