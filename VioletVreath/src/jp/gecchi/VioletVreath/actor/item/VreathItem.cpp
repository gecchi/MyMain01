#include "VreathItem.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/Kago.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/core/util/Status.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_DRIFT      , //�ʏ�ړ����
    PROG_ATTACH     , //�z����(���z��)���
    PROG_ABSORB     , //�z����(�z����)���
    PROG_BANPEI,
};

VreathItem::VreathItem(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset)
               : Item(prm_name, prm_model, prm_pFuncStatusReset) {
    _class_name = "VreathItem";
    effectBlendOne(); //���Z��������Technique�w��
    setZEnableDraw(true);        //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
    setCullingDraw(false);
    GgafDx::Rikisha* const pRikisha = callRikisha();
    pRikisha->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    pRikisha->linkFaceAngByMvAng(true);
    kDX_ = kDY_ = kDZ_ = 0;
    setHitAble(true, false); //��ʊO�����蔻��͖���
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 400000);
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(0, "WAVE_GET_ITEM_001");
}

void VreathItem::initialize() {
}

void VreathItem::onActive() {
    // _x, _y, _z �͔��������W�ɐݒ�ς�
    setHitAble(true, false);
    GgafDx::Kago* const pKago = callKago();
    pKago->forceVxyzMvVeloRange(-30000, 30000);
    pKago->setZeroVxyzMvVelo();
    pKago->setZeroVxyzMvAcce();
    pKago->stopGravitationMvSequence();

    //���������ݒ�
    MyShip* pMyShip = pMYSHIP;
//    //�U��΂�͈͐����`�P�ӂ̒���
//    int scattered_renge    = pChecker->_pCollisionArea->_papColliPart[0]->_dx; //�����蔻��Ɠ���
//    //�����n�_����A���@�ւ̕����ւ̎U��΂�͈͐����`�̈悪�ʒu���鋗���iscattered_distance > (scattered_renge/2) �ł��邱��)
////    int scattered_distance = scattered_renge/2 + 400000;
//    //�]���āAscattered_distance ����Ă��Ă��A���@�͓����Ȃ��Ă����肬��S�ĉ���ł���B
    GgafDx::Rikisha* const pRikisha = callRikisha();
    pRikisha->forceMvVeloRange(0, 20000);
    float vX, vY, vZ;
    UTIL::getNormalizedVector(
            pMyShip->_x - _x,
            pMyShip->_y - _y,
            pMyShip->_z - _z,
            vX, vY, vZ);
    int d = PX_C(200);
    int r = PX_C(75);
    pRikisha->setMvAngTwd( (coord)(_x + (vX * d) + RND(-r, +r)),
                          (coord)(_y + (vY * d) + RND(-r, +r)),
                          (coord)(_z + (vZ * d) + RND(-r, +r)) );
    pRikisha->setMvVelo(2000);
    pRikisha->setMvAcce(100);

    getProgress()->reset(PROG_DRIFT);
    _sx = _sy = _sz = 1000;
}

void VreathItem::processBehavior() {
    //�ʏ�ړ�
    GgafDx::Rikisha* const pRikisha = callRikisha();
    GgafDx::Kago* const pKago = callKago();
    GgafCore::Progress* const pProg = getProgress();
    if (pProg->get() == PROG_DRIFT) {
        //TractorMagic��������PROG_ATTACH�ֈڍs
        if (getTractorMagic()->is_tracting_) {
            effectFlush(6); //�t���b�V��
            setHitAble(false);
            pProg->change(PROG_ATTACH);
        }
        //���邢�� onHit() �� PROG_ATTACH ��ԕω�����̂�҂�
    }

    //���@�Ɠ����蔻�肪�q�b�g���A���@�Ɍ���������
    if (pProg->get() == PROG_ATTACH) {
        MyShip* pMyShip = pMYSHIP;
        if (pProg->hasJustChanged()) {
            //���@�Ɉ��͂ň����񂹂���悤�ȓ����ݒ�
            pKago->setVxyzMvVelo(pRikisha->_vX * pRikisha->_velo_mv,
                                     pRikisha->_vY * pRikisha->_velo_mv,
                                     pRikisha->_vZ * pRikisha->_velo_mv );
            pKago->execGravitationMvSequenceTwd(pMyShip, PX_C(20), 200, PX_C(100));
            pRikisha->stopMv();
        }

        //�����@�ߕӂɓ��B�H
        if (ABS(pMyShip->_x - _x) < 20000 &&
            ABS(pMyShip->_y - _y) < 20000 &&
            ABS(pMyShip->_z - _z) < 20000 ) {

            kDX_ = pMyShip->_x - _x;
            kDY_ = pMyShip->_y - _y;
            kDZ_ = pMyShip->_z - _z;
            pProg->change(PROG_ABSORB); //�z���z����
        }

    }

    //���@�ߕӂɓ��B���A�z���A�z�����̓���
    if (pProg->get() == PROG_ABSORB) {
        MyShip* pMyShip = pMYSHIP;
        if (pProg->hasJustChanged()) {
            pKago->setZeroVxyzMvVelo();
            pKago->setZeroVxyzMvAcce();
            pKago->stopGravitationMvSequence();
        }
        _x = pMyShip->_x + kDX_;
        _y = pMyShip->_y + kDY_;
        _z = pMyShip->_z + kDZ_;
        _sx -= 100;
        _sy -= 100;
        _sz -= 100;
        if (_sx < 5) {
            getSeTransmitter()->play(0);
            pProg->changeNothing();
            sayonara(); //�I��
        }
        pMyShip->getStatus()->plus(STAT_Stamina, 1);
    }
    pRikisha->behave();
    pKago->behave();
}

void VreathItem::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
//    //�ʏ�ړ�
//    if (pProg->get() == PROG_DRIFT) {
//        //onHit() �ŏ�ԕω�����̂�҂�
//    }
//
//    //���@�Ɠ����蔻�肪�q�b�g��
//    if (pProg->get() == PROG_ATTACH) {
//
//    }
//
//    //���@�ɋz�����A�z�����̓���
//    if (pProg->get() == PROG_ABSORB) {
//    }
}

void VreathItem::onInactive() {
}

void VreathItem::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g

    GgafCore::Progress* const pProg = getProgress();
    if (pProg->get() == PROG_DRIFT && (pOther->lookUpKind() & KIND_MY_BODY))  {
        setHitAble(false);
        pProg->change(PROG_ATTACH);
    }
}

VreathItem::~VreathItem() {
}

