#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot004Blue::Shot004Blue(const char* prm_name) :
        SingleLaser(prm_name, "Shot004Blue", STATUS(Shot004)) { //SingleLaser�͍ő�27�Z�b�g�ł���
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaser�͍ő�27�Z�b�g�ł���
    _class_name = "Shot004Blue";
    view_in_ = false;
}

void Shot004Blue::initialize() {

    setHitAble(false);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}
void Shot004Blue::onReset() {
    setScaleR(3.0);
    setAlpha(0.99); //�������ɂ��邱�Ƃŗ��ʃ����_�����O
    _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(3));
    _pKurokoA->setMvVelo(40000);             //�ړ����x
    _pKurokoA->setMvAcce(1000);             //�ړ����x
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void Shot004Blue::onActive() {
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004Blue::processBehavior() {
    //���Z�����N�|�C���g������
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //�e�Ȃ̂ŕs�v

    //���W�ɔ��f
    _pKurokoA->behave();
}

void Shot004Blue::processJudgement() {
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

void Shot004Blue::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locateWith(this);
        }
        sayonara();
    }
}


void Shot004Blue::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}
Shot004Blue::~Shot004Blue() {
}
