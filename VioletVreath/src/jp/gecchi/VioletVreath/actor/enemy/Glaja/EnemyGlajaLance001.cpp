#include "stdafx.h"
#include "EnemyGlajaLance001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperB.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyGlajaLance001::EnemyGlajaLance001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "GlajaLance001", STATUS(EnemyGlajaLance001)) {
    _class_name = "EnemyGlajaLance001";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne(); //���Z����
    setZEnable(true);
    setZWriteEnable(false);
    useProgress(PROG_BANPEI);
}

void EnemyGlajaLance001::initialize() {
    setHitAble(false);
    _pColliChecker->makeCollision(3);
    _pColliChecker->setColliAAB_Cube(0, PX_C(20));
    _pColliChecker->setColliAAB_Cube(1, -PX_C(80), 0, 0,
                                        PX_C(10),
                                        true, true, true);
    _pColliChecker->setColliAAB_Cube(2, PX_C(80), 0, 0,
                                        PX_C(10),
                                        true, true, true);

}
void EnemyGlajaLance001::onReset() {

}

void EnemyGlajaLance001::onActive() {
    _pKuroko->setMvAcce(0);
    _pKuroko->setMvVelo(PX_C(3));
    setFaceAng(0,
                          RND(D_ANG(0), D_ANG(360)),
                          RND(D_ANG(0), D_ANG(360)) );
    _pKuroko->setFaceAngVelo(D_ANG(33), D_ANG(15), D_ANG(20));
    _pKuroko->relateFaceWithMvAng(true);
    _pColliChecker->disable(1);
    _pColliChecker->disable(2);
    pScaler_->reset();
    pScaler_->behave();
    _pStatus->reset();
    setAlpha(0.99);
    _pProg->reset(PROG_INIT);
}

void EnemyGlajaLance001::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(true, false);
            //_pKuroko->setMvAngTwd(&turning_pos_);
            _pProg->changeNext();
            break;
        }
        case PROG_MOVE01: {
            if (_pProg->isJustChanged()) {

            }
            if (_pProg->getFrameInProgress() == 120) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_AIM_ANIME01: {
            if (_pProg->isJustChanged()) {
                //�V���L�[���Ƒ��ɂȂ�I�i�L�т�I�j
                _pKuroko->stopMv();
                _pKuroko->setFaceAngVelo(0, 0, 0);
                pScaler_->transitionAcceStep(AXIS_X, R_SC(30), R_SC(1), R_SC(0.1));
            }
            if (!pScaler_->isScaling()) {
                //���̗��[�����蔻��o��
                _pColliChecker->enable(1);
                _pColliChecker->enable(2);
                _pProg->changeNext();
             }

             break;
        }
        case PROG_AIM_ANIME02: {
            if (_pProg->isJustChanged()) {
                //���@�ɃO�����ƌ���
                _pKuroko->hlprB()->turnFaceAngByDtTwd(pMyShip, TURN_ANTICLOSE_TO, false,
                                                        30, 0.2, 0.4, 0, true );
            }
            if (!_pKuroko->isTurningFaceAng()) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE02: {
            if (_pProg->isJustChanged()) {
                _pKuroko->setMvAngByFaceAng(); //�������Ă�����ɂ��ꂩ��ړ�����
                _pKuroko->setMvVelo(-PX_C(2)); //������ƃo�b�N���Ē��߂�\��
                setRzFaceAng(D_ANG(27)); //�X�s���X�s��
            }
            if (_pProg->getFrameInProgress() >= 10) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE03: {
            if (_pProg->isJustChanged()) {
                //�Y�L���[�[���ƈړ�
                _pKuroko->setMvVelo(PX_C(60));
            }
            //��ʊO or HIT �܂őҋ@
            break;
        }

        case PROG_LEAVE: {
            if (_pProg->isJustChanged()) {
                //HIT�������܂�
            }
            addAlpha(-1.0/90.0); //sayonara(90);������
            break;
        }
    }
    //���W�ɔ��f
    pScaler_->behave();
    _pKuroko->behave();
}

void EnemyGlajaLance001::processJudgement() {
    if (isOutOfView()) {
        if (getActiveFrame() > 60) {
            sayonara();
        }
    }
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyGlajaLance001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g
        _pKuroko->stopMv();
        sayonara(90);
        _pProg->change(PROG_LEAVE);
    }
}

EnemyGlajaLance001::~EnemyGlajaLance001() {
    GGAF_DELETE(pScaler_);
}
