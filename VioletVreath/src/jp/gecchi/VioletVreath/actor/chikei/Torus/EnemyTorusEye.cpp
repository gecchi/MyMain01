#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyTorusEye::EnemyTorusEye(const char* prm_name, Torus* prm_pTorus) :
        DefaultMorphMeshActor(prm_name, "1/TorusEye", STATUS(EnemyTorusEye)) {
        //CubeMapMorphMeshActor(prm_name, "1/ThaliaCM", STATUS(EnemyTorusEye)) {

    _class_name = "EnemyTorusEye";
    setScaleR(0.3*10);
    pTorus_ = prm_pTorus;
    locateWith(pTorus_);
    pDepo_ShotEffect_ = NULL;

    pLaserChipDepo_ = NEW LaserChipDepository("DepoLaserChip");
    pLaserChipDepo_->config(60, 1, NULL); //Thalia�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
    EnemyTorusEyeStraightLaserChip001* pChip;
    for (int i = 0; i < 65; i++) { //���[�U�[�X�g�b�N
        std::string name = "EnemyTorusEyeStraightLaserChip001("+ ITOS(i) + ")";
        pChip = NEW EnemyTorusEyeStraightLaserChip001(name.c_str());
        pChip->setSource(this); //�ʒu��������
        pLaserChipDepo_->addSubLast(pChip);
    }
    addSubGroup(pLaserChipDepo_);

    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"   , GgafRepeatSeq::nextVal("CH_bomb1"));
    _pSeTxer->set(SE_FIRE     , "laser001", GgafRepeatSeq::nextVal("CH_laser001"));
    useProgress(PROG_CLOSE);

    is_wake_ = false;
}

void EnemyTorusEye::onCreateModel() {

    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyTorusEye::initialize() {
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 200000);

}

void EnemyTorusEye::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pProg->set(PROG_MOVE);

    locateWith(pTorus_);
    rotateWith(pTorus_);
    _pKurokoA->setRzMvAngVelo(pTorus_->_pKurokoA->_angveloFace[AXIS_Z]);
    _pKurokoA->setRyMvAngVelo(pTorus_->_pKurokoA->_angveloFace[AXIS_Y]);

}

void EnemyTorusEye::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    locateWith(pTorus_);
    switch (_pProg->get()) {
        case PROG_MOVE: {
            break;
        }
        case PROG_OPEN: {
            if (_pProg->hasJustChanged()) {
                _pMorpher->intoTargetLinerUntil(1, 1.0, 180); //�J��
            }
            if (_pProg->getFrameInProgress() > 240) {
                _pProg->changeNext();
            }
            _pKurokoA->followMvFrom(pTorus_->_pKurokoA);
            break;
        }

        case PROG_TURN: {
            if (_pProg->hasJustChanged()) {
                _pKurokoA->execTurnMvAngSequence(P_MYSHIP, D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            if (_pProg->getFrameInProgress() > 240) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE_BEGIN: {
            if (_pProg->hasJustChanged()) {
                _pKurokoA->execTurnMvAngSequence(P_MYSHIP, D_ANG(1), 0, TURN_ANTICLOSE_TO, false);
            }
            if (_pProg->getFrameInProgress() % 5) {
                effectFlush(2);
            }
            if (_pProg->getFrameInProgress() >= 180) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_IN_FIRE: {
            if (_pProg->hasJustChanged()) {
                _pKurokoA->execTurnMvAngSequence(P_MYSHIP, D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            LaserChip* pChip = pLaserChipDepo_->dispatch();
            if (pChip) {
                if (pChip->_pChip_front == NULL) {
                    _pSeTxer->play3D(SE_FIRE);
                }
            } else {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_FIRE_END: {
            if (_pProg->hasJustChanged()) {
                _pMorpher->intoTargetLinerUntil(1, 0.0, 180); //�J��
                _pKurokoA->setRzMvAngVelo(pTorus_->_pKurokoA->_angveloFace[AXIS_Z]);
                _pKurokoA->setRyMvAngVelo(pTorus_->_pKurokoA->_angveloFace[AXIS_Y]);
            }
            //�d��
            if (_pProg->getFrameInProgress() >= 300) {
                _pProg->change(PROG_TURN);
            }
            break;
        }

        default:
            break;
    }


    _pKurokoA->behave();
    _pMorpher->behave();
    _pSeTxer->behave();
}

void EnemyTorusEye::processJudgement() {
//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyTorusEye::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //��������
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);

        //�ł��Ԃ��e
//        if (pDepo_Shot_) {
//            UTIL::shotWay004(this, pDepo_Shot_,
//                             PX_C(20),
//                             8, D_ANG(10),
//                             2000, 200,
//                             12, 3, 0.9);
//
//        }

        //���@���Ɍ�����ď��ł̏ꍇ�A
        if (pOther->getKind() & KIND_MY) {
            //�A�C�e���o��
            UTIL::activateItemOf(this);
        }
        pTorus_->pEnemyTorusEye_ = NULL;
        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        _pSeTxer->play3D(SE_DAMAGED);
    }
}

void EnemyTorusEye::onInactive() {
    //sayonara();
}

void EnemyTorusEye::wake() {
    is_wake_ = true;
    _pProg->change(PROG_OPEN);
}

EnemyTorusEye::~EnemyTorusEye() {
}
