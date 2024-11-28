#include "MagicPointItem.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_DRIFT      , //�ʏ�ړ����
    PHASE_ATTACH     , //�z����(���z��)���
    PHASE_ABSORB     , //�z����(�z����)���
    PHASE_BANPEI,
};
enum {
    SE_GET_ITEM ,
};

MagicPointItem::MagicPointItem(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset)
               : VvItemActor<GgafLib::DefaultMassMeshActor>(prm_name, prm_model, prm_pFuncStatusReset) {
    _class_name = "MagicPointItem";
    effectBlendOne(); //���Z��������Technique�w��
    setZEnableDraw(true);        //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
    setCullingDraw(false);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    pLocusVehicle->linkFaceAngByMvAng(true);
    kDX_ = kDY_ = kDZ_ = 0;
    setHitAble(true, false); //��ʊO�����蔻��͖���
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 400000);
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_GET_ITEM, "SE_GET_ITEM_001");
}

void MagicPointItem::initialize() {
}

void MagicPointItem::onActive() {
    // _x, _y, _z �͔��������W�ɐݒ�ς�
    setHitAble(true, false);
    GgafDx::CoordVehicle* const pCoordVehicle = getCoordVehicle();
    pCoordVehicle->forceVeloXYZRange(-30000, 30000);
    pCoordVehicle->setXYZZero();
    pCoordVehicle->setAcceXYZZero();
    pCoordVehicle->stopGravitationMvSequence();

    //���������ݒ�
    MyShip* pMyShip = pMYSHIP;
//    //�U��΂�͈͐����`�P�ӂ̒���
//    int scattered_renge    = pChecker->_pCollisionArea->_papColliPart[0]->_dx; //�����蔻��Ɠ���
//    //�����n�_����A���@�ւ̕����ւ̎U��΂�͈͐����`�̈悪�ʒu���鋗���iscattered_distance > (scattered_renge/2) �ł��邱��)
////    int scattered_distance = scattered_renge/2 + 400000;
//    //�]���āAscattered_distance ����Ă��Ă��A���@�͓����Ȃ��Ă����肬��S�ĉ���ł���B
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->forceMvVeloRange(0, 20000);
    double vX, vY, vZ;
    UTIL::getNormalizedVector(
            pMyShip->_x - _x,
            pMyShip->_y - _y,
            pMyShip->_z - _z,
            vX, vY, vZ);
    int d = PX_C(200);
    int r = PX_C(75);
    pLocusVehicle->setMvAngTwd( (coord)(_x + (vX * d) + RND(-r, +r)),
                          (coord)(_y + (vY * d) + RND(-r, +r)),
                          (coord)(_z + (vZ * d) + RND(-r, +r)) );
    pLocusVehicle->setMvVelo(2000);
    pLocusVehicle->setMvAcce(100);

    getPhase()->reset(PHASE_DRIFT);
    _sx = _sy = _sz = 1000;
}

void MagicPointItem::processBehavior() {
    MyShip* pMyShip = pMYSHIP;
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafDx::CoordVehicle* const pCoordVehicle = getCoordVehicle();
    GgafCore::Phase* pPhase = getPhase();
    //�ʏ�ړ�
    if (pPhase->getCurrent() == PHASE_DRIFT) {
        //TractorMagic��������PHASE_ATTACH�ֈڍs
        if (getTractorMagic()->is_tracting_) {
            effectFlush(6); //�t���b�V��
            setHitAble(false);
            pPhase->change(PHASE_ATTACH);
        }
        //���邢�� onHit() �� PHASE_ATTACH ��ԕω�����̂�҂�
    }

    //���@�Ɠ����蔻�肪�q�b�g���A���@�Ɍ���������
    if (pPhase->getCurrent() == PHASE_ATTACH) {
        MyMagicEnergyCore* pE = pMyShip->pMyMagicEnergyCore_;
        if (pPhase->hasJustChanged()) {
            //���@�Ɉ��͂ň����񂹂���悤�ȓ����ݒ�
            pCoordVehicle->setVeloXYZ(pLocusVehicle->_vX * pLocusVehicle->_velo_mv,
                                     pLocusVehicle->_vY * pLocusVehicle->_velo_mv,
                                     pLocusVehicle->_vZ * pLocusVehicle->_velo_mv);
            pCoordVehicle->execGravitationMvSequenceTwd(pE,
                                                    PX_C(50), 300, PX_C(300));
            pLocusVehicle->stop();
        }

        //�����@�ߕӂɓ��B�H
        if (ABS(pE->_x - _x) < PX_C(20) &&
            ABS(pE->_y - _y) < PX_C(20) &&
            ABS(pE->_z - _z) < PX_C(20) )
        {
            kDX_ = pE->_x - _x;
            kDY_ = pE->_y - _y;
            kDZ_ = pE->_z - _z;
            pPhase->change(PHASE_ABSORB); //�z���z����
        }
    }

    //���@�ߕӂɓ��B���A�z���A�z�����̓���
    if (pPhase->getCurrent() == PHASE_ABSORB) {
        MyMagicEnergyCore* pE = pMyShip->pMyMagicEnergyCore_;
        if (pPhase->hasJustChanged()) {
            pCoordVehicle->setXYZZero();
            pCoordVehicle->setAcceXYZZero();
            pCoordVehicle->stopGravitationMvSequence();
        }
        _x = pE->_x + kDX_;
        _y = pE->_y + kDY_;
        _z = pE->_z + kDZ_;
        addScale(-100);
        pMyShip->mp_ += 12; //���������I

        if (_sx < 100) {
            getSeXmtr()->play(SE_GET_ITEM);
            pPhase->changeNothing();
            sayonara(); //�I��
        }
    }
    pLocusVehicle->behave();
    pCoordVehicle->behave();
}

void MagicPointItem::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
//    //�ʏ�ړ�
//    if (pPhase->getCurrent() == PHASE_DRIFT) {
//        //onHit() �ŏ�ԕω�����̂�҂�
//    }
//
//    //���@�Ɠ����蔻�肪�q�b�g��
//    if (pPhase->getCurrent() == PHASE_ATTACH) {
//
//    }
//
//    //���@�ɋz�����A�z�����̓���
//    if (pPhase->getCurrent() == PHASE_ABSORB) {
//    }
}

void MagicPointItem::onInactive() {
}

void MagicPointItem::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g

    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->getCurrent() == PHASE_DRIFT && (pOther->getCheckerKind() & KIND_MY_BODY))  {
        setHitAble(false);
        pPhase->change(PHASE_ATTACH);
    }
}

MagicPointItem::~MagicPointItem() {
}

