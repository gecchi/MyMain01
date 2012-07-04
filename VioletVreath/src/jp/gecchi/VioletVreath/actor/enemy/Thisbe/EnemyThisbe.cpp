#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    THISBE_PROG_WAIT = 1  ,
    THISBE_PROG_OPEN ,
    THISBE_PROG_FIRE   ,
    THISBE_PROG_CLOSE     ,
};

EnemyThisbe::EnemyThisbe(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Thisbe", STATUS(EnemyThisbe)) {
        //CubeMapMorphMeshActor(prm_name, "1/ThisbeCM", STATUS(EnemyThisbe)) {

    _class_name = "EnemyThisbe";
    pSplSeq_ = NULL;
    pDepo_Shot_ = NULL;
    pDepo_ShotEffect_ = NULL;

    pLaserChipDepo_ = NEW LaserChipDepository("ThisbeLaser");
    pLaserChipDepo_->config(100, 1, NULL); //Thisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B

//    EnemyThisbeLaserChip001* pChip;
//    for (int i = 0; i < 65; i++) { //���[�U�[�X�g�b�N
//        std::stringstream name;
//        name <<  "EnemyThisbeLaserChip001[" << i << "]";
//        pChip = NEW EnemyThisbeLaserChip001(name.str().c_str());
//        pLaserChipDepo_->addSubLast(pChip);
//    }


    pCon_RefractionEffectDepository_ = connectDepositoryManager("DpCon_EffRefraction001", NULL);

    EnemyThisbeLaserChip002* pChip;
    for (int i = 0; i < 100; i++) { //���[�U�[�X�g�b�N
        std::stringstream name;
        name <<  "EnemyThisbeLaserChip002[" << i << "]";
        pChip = NEW EnemyThisbeLaserChip002(name.str().c_str());
        int num_refraction = pChip->pSplManufCon_->fetch()->_pSplSrc->_pSp->_rnum;
        pChip->config(num_refraction, 1, 1, pCon_RefractionEffectDepository_->fetch());
        pLaserChipDepo_->addSubLast(pChip);
    }

    addSubGroup(pLaserChipDepo_);

    _pSeTx->useSe(2);
    _pSeTx->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
    _pSeTx->set(1, "laser001", GgafRepeatSeq::nextVal("CH_laser001"));
    useProgress(THISBE_PROG_CLOSE);
}

void EnemyThisbe::onCreateModel() {
}

void EnemyThisbe::initialize() {
    setHitAble(false);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 90000);
}

void EnemyThisbe::onActive() {
    _pStatus->reset();
    _pMorpher->reset();
    _pProg->set(THISBE_PROG_WAIT);
}

void EnemyThisbe::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
        case THISBE_PROG_WAIT: {
            if (_pProg->getFrameInProgress() > 120) {
                _pProg->changeNext();
            }

            break;
        }
        case THISBE_PROG_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->intoTargetLinerUntil(1, 1.0, 120);
            }
            if (_pProg->getFrameInProgress() > 120) {
                //�J������
                _pProg->changeNext();
            }
            break;
        }

        case THISBE_PROG_FIRE: {
            LaserChip* pLaser = pLaserChipDepo_->dispatch();
            if (pLaser) {
                pLaser->locateWith(this);
                pLaser->_pKurokoA->setRzRyMvAng(_pKurokoA->_angFace[AXIS_Z], _pKurokoA->_angFace[AXIS_Y]); //���[�U�[�̃X�v���C����RELATIVE_DIRECTION�̂���
                                                   //MvAng�̐ݒ肪�K�v�B
                if (pLaser->_pChip_front == NULL) {
                    _pSeTx->play3D(1);
                }
            } else {
                _pProg->change(THISBE_PROG_CLOSE);
            }
            break;
        }
        case THISBE_PROG_CLOSE: {
            //�P�T�C�N�����[�U�[�ł��؂���
            _pMorpher->intoTargetLinerUntil(1, 0.0, 120); //����
            _pProg->change(THISBE_PROG_WAIT);
            break;
        }

        default:
            break;
    }


    _pKurokoA->behave();
    _pMorpher->behave();
    _pSeTx->behave();
}

void EnemyThisbe::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyThisbe::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

//    if (_pProg->get() != THISBE_PROG_WAIT && (pOther->getKind() & KIND_MY) ) {
//        effectFlush(2); //�t���b�V��
//        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
//        if (pExplo001) {
//            pExplo001->locateWith(this);
//        }
//        _pSeTx->play3D(0);
//
//
//        if (UTIL::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//            EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
//            if (pExplo001) {
//                pExplo001->locateWith(this);
//            }
//            _pSeTx->play3D(0);
//
//
//            //�ł��Ԃ��e
//            if (pDepo_Shot_) {
//
//                UTIL::shotWay004(this, pDepo_Shot_,
//                                 PX_C(20),
//                                 8, D_ANG(10),
//                                 2000, 200,
//                                 12, 3, 0.9);
//
//            }
//            sayonara();
//        }
//
//    } else {
//
//    }

}

void EnemyThisbe::onInactive() {
    //sayonara();
}

EnemyThisbe::~EnemyThisbe() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
    pCon_RefractionEffectDepository_->close();
}
