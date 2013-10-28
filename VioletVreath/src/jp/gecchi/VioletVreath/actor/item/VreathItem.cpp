#include "stdafx.h"
#include "VreathItem.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VreathItem::VreathItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat)
               : Item(prm_name, prm_model, prm_pStat) {
    _class_name = "VreathItem";
    effectBlendOne(); //���Z��������Technique�w��
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    setAlpha(0.9);

    _pKurokoA->setFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    _pKurokoA->relateFaceWithMvAng(true);
    kDX_ = kDY_ = kDZ_ = 0;
    useProgress(_BANPEI_-1);
    setHitAble(true, false); //��ʊO�����蔻��͖���
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 400000);
    _pSeTx->set(0, "WAVE_GET_ITEM_001");
}

void VreathItem::initialize() {
}

void VreathItem::onActive() {
    // _x, _y, _z �͔��������W�ɐݒ�ς�
    setHitAble(true, false);

    _pKurokoB->forceVxyzMvVeloRange(-30000, 30000);
    _pKurokoB->setZeroVxyzMvVelo();
    _pKurokoB->setZeroVxyzMvAcce();
    _pKurokoB->stopGravitationMvSequence();

    //���������ݒ�
    MyShip* pMyShip = P_MYSHIP;
//    //�U��΂�͈͐����`�P�ӂ̒���
//    int scattered_renge    = _pColliChecker->_pCollisionArea->_papColliPart[0]->_dx; //�����蔻��Ɠ���
//    //�����n�_����A���@�ւ̕����ւ̎U��΂�͈͐����`�̈悪�ʒu���鋗���iscattered_distance > (scattered_renge/2) �ł��邱��)
////    int scattered_distance = scattered_renge/2 + 400000;
//    //�]���āAscattered_distance ����Ă��Ă��A���@�͓����Ȃ��Ă����肬��S�ĉ���ł���B

    _pKurokoA->forceMvVeloRange(0, 20000);
    float vX, vY, vZ;
    UTIL::getNormalizeVector(
            pMyShip->_x - _x,
            pMyShip->_y - _y,
            pMyShip->_z - _z,
            vX, vY, vZ);
    int d = PX_C(200);
    int r = PX_C(75);
    _pKurokoA->setMvAngTwd( (coord)(_x + (vX * d) + RND(-r, +r)),
                            (coord)(_y + (vY * d) + RND(-r, +r)),
                            (coord)(_z + (vZ * d) + RND(-r, +r)) );
    _pKurokoA->setMvVelo(2000);
    _pKurokoA->setMvAcce(100);

    _pProg->reset(PROG_DRIFT);
    _sx = _sy = _sz = 1000;
}

void VreathItem::processBehavior() {
    //�ʏ�ړ�
    if (_pProg->get() == PROG_DRIFT) {
        //TractorMagic��������PROG_ATTACH�ֈڍs
        if (getTractorMagic()->is_tracting_) {
            effectFlush(6); //�t���b�V��
            setHitAble(false);
            _pProg->change(PROG_ATTACH);
        }
        //���邢�� onHit() �� PROG_ATTACH ��ԕω�����̂�҂�
    }

    //���@�Ɠ����蔻�肪�q�b�g���A���@�Ɍ���������
    if (_pProg->get() == PROG_ATTACH) {
        MyShip* pMyShip = P_MYSHIP;
        if (_pProg->isJustChanged()) {
            //���@�Ɉ��͂ň����񂹂���悤�ȓ����ݒ�
            _pKurokoB->setVxyzMvVelo(_pKurokoA->_vX*_pKurokoA->_veloMv,
                                     _pKurokoA->_vY*_pKurokoA->_veloMv,
                                     _pKurokoA->_vZ*_pKurokoA->_veloMv );
            _pKurokoB->execGravitationMvSequenceTwd(pMyShip, PX_C(20), 200, PX_C(100));
            _pKurokoA->stopMv();
        }

        //�����@�ߕӂɓ��B�H
        if (ABS(pMyShip->_x - _x) < 20000 &&
            ABS(pMyShip->_y - _y) < 20000 &&
            ABS(pMyShip->_z - _z) < 20000 ) {

            kDX_ = pMyShip->_x - _x;
            kDY_ = pMyShip->_y - _y;
            kDZ_ = pMyShip->_z - _z;
            _pProg->change(PROG_ABSORB); //�z���z����
        }

    }

    //���@�ߕӂɓ��B���A�z���A�z�����̓���
    if (_pProg->get() == PROG_ABSORB) {
        MyShip* pMyShip = P_MYSHIP;
        if (_pProg->isJustChanged()) {
            _pKurokoB->setZeroVxyzMvVelo();
            _pKurokoB->setZeroVxyzMvAcce();
            _pKurokoB->stopGravitationMvSequence();
        }
        _x = pMyShip->_x + kDX_;
        _y = pMyShip->_y + kDY_;
        _z = pMyShip->_z + kDZ_;
        _sx -= 100;
        _sy -= 100;
        _sz -= 100;
        if (_sx < 5) {
            _pSeTx->play(0);
            _pProg->changeNothing();
            sayonara(); //�I��
        }
        pMyShip->_pStatus->plus(STAT_Stamina, 1);
    }
    _pKurokoA->behave();
    _pKurokoB->behave();
}

void VreathItem::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
//    //�ʏ�ړ�
//    if (_pProg->get() == PROG_DRIFT) {
//        //onHit() �ŏ�ԕω�����̂�҂�
//    }
//
//    //���@�Ɠ����蔻�肪�q�b�g��
//    if (_pProg->get() == PROG_ATTACH) {
//
//    }
//
//    //���@�ɋz�����A�z�����̓���
//    if (_pProg->get() == PROG_ABSORB) {
//    }
}

void VreathItem::onInactive() {
}

void VreathItem::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g


    if (_pProg->get() == PROG_DRIFT && (pOther->getKind() & KIND_MY_BODY))  {
        setHitAble(false);
        _pProg->change(PROG_ATTACH);
    }

}

VreathItem::~VreathItem() {
}
