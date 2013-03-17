#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbe::EnemyThisbe(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Thisbe", STATUS(EnemyThisbe)) {
        //CubeMapMorphMeshActor(prm_name, "1/ThisbeCM", STATUS(EnemyThisbe)) {

    _class_name = "EnemyThisbe";
    pSplSeq_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;

    pLaserChipDepo_ = NEW LaserChipDepository("ThisbeLaser");
    pLaserChipDepo_->config(100, 1, nullptr); //Thisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B

//    EnemyThisbeLaserChip001* pChip;
//    for (int i = 0; i < 65; i++) { //���[�U�[�X�g�b�N
//        std::stringstream name;
//        name <<  "EnemyThisbeLaserChip001[" << i << "]";
//        pChip = NEW EnemyThisbeLaserChip001(name.str().c_str());
//        pLaserChipDepo_->addSubLast(pChip);
//    }


    pConn_RefractionEffectDepository_ = connectToDepositoryManager("Conn_EffRefraction001", nullptr);

    EnemyThisbeLaserChip002* pChip;
    for (int i = 0; i < 100; i++) { //���[�U�[�X�g�b�N
        std::stringstream name;
        name <<  "EnemyThisbeLaserChip002[" << i << "]";
        pChip = NEW EnemyThisbeLaserChip002(name.str().c_str());
        int num_refraction = pChip->pSplSeq_->getPointNum();
        pChip->config(num_refraction, 1, 1, pConn_RefractionEffectDepository_->fetch());
        pLaserChipDepo_->addSubLast(pChip);
    }

    addSubGroup(pLaserChipDepo_);

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    _pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_CLOSE);
}

void EnemyThisbe::onCreateModel() {
}

void EnemyThisbe::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 40000);
}

void EnemyThisbe::onActive() {
    _pStatus->reset();
    _pMorpher->reset();
    _pProg->reset(PROG_WAIT);
}

void EnemyThisbe::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
        case PROG_WAIT: {
            if (pLaserChipDepo_->_num_chip_active == 0) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->intoTargetLinerUntil(1, 1.0, 120);
            }
            if (!_pMorpher->isMorphing()) {
                //���S�ɊJ������
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            LaserChip* pLaser = pLaserChipDepo_->dispatch();
            if (pLaser) {
                pLaser->locateWith(this);
                pLaser->_pKurokoA->setRzRyMvAng(_pKurokoA->_angFace[AXIS_Z], _pKurokoA->_angFace[AXIS_Y]);
                                   //���[�U�[�̃X�v���C����RELATIVE_DIRECTION�̂���MvAng�̐ݒ肪�K�v�B
                if (pLaser->_pChip_front == nullptr) {
                    _pSeTx->play3D(SE_FIRE);
                }
            } else {
                _pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_CLOSE: {
            //�P�T�C�N�����[�U�[�ł��؂���
            _pMorpher->intoTargetLinerUntil(1, 0.0, 120); //����
            if (!_pMorpher->isMorphing()) {
                //���S�ɕ�����
                _pProg->change(PROG_WAIT);
            }
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

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //��������
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_EXPLOSION);
        //���@���Ɍ�����ď��ŁH
        if (pOther->getKind() & KIND_MY) {
            //�Ȃ�΃A�C�e���o��
            UTIL::activateItemOf(this);
        }
        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyThisbe::onInactive() {
    //sayonara();
}

EnemyThisbe::~EnemyThisbe() {
    GGAF_DELETE_NULLABLE(pSplSeq_);
    pConn_RefractionEffectDepository_->close();
}
