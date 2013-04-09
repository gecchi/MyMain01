#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbe::EnemyThisbe(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Thisbe", STATUS(EnemyThisbe)) {
        //CubeMapMorphMeshActor(prm_name, "1/ThisbeCM", STATUS(EnemyThisbe)) {

    _class_name = "EnemyThisbe";
    pKurokoStepper_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;

//    //���t���N�V����------>
//    GgafActorDepository* pDepoEffect = NEW GgafActorDepository("ThisbeLaser");
//    EffectLaserRefraction001* pEffect;
//    for (int i = 0; i < 100; i++) {
//        std::string name = "EffectLaserRefraction001["+XTOS(i)+"]";
//        pEffect = NEW EffectLaserRefraction001(name.c_str());
//        pDepoEffect->addSubLast(pEffect);
//    }
//    addSubGroup(pDepoEffect);
//
//    pLaserChipDepo_ = NEW LaserChipDepository("ThisbeLaser");
//    pLaserChipDepo_->config(100, 1, nullptr); //Thisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
//    for (int i = 0; i < 100; i++) { //���[�U�[�X�g�b�N
//        std::string name = "EnemyThisbeLaserChip002["+XTOS(i)+"]";
//        EnemyThisbeLaserChip002* pChip = NEW EnemyThisbeLaserChip002(name.c_str());
//        int num_refraction = pChip->pKurokoStepper_->getPointNum();
//        pChip->config(num_refraction, 1, 1, false, pDepoEffect);
//        pLaserChipDepo_->addSubLast(pChip);
//    }
//    addSubGroup(pLaserChipDepo_);
//    //<---------------------

//    //�z�[�~���O------>
//    pLaserChipDepo_ = NEW LaserChipDepository("ThisbeLaser");
//    pLaserChipDepo_->config(300, 1, nullptr); //Thisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
//    for (int i = 0; i < 300; i++) { //���[�U�[�X�g�b�N
//        std::string name = "EnemyThisbeLaserChip001["+XTOS(i)+"]";
//        EnemyThisbeLaserChip001* pChip = NEW EnemyThisbeLaserChip001(name.c_str());
//        pChip->_is_fix_begin_pos = false;
//        pLaserChipDepo_->addSubLast(pChip);
//    }
//    addSubGroup(pLaserChipDepo_);
//    //<---------------------

//    //��------>
//    pLaserChipDepo_ = NEW LaserChipDepository("ThisbeLaser");
//    pLaserChipDepo_->config(100, 1, nullptr); //Thisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
//    for (int i = 0; i < 100; i++) { //���[�U�[�X�g�b�N
//        std::string name = "EnemyThisbeLaserChip003["+XTOS(i)+"]";
//        EnemyThisbeLaserChip003* pChip = NEW EnemyThisbeLaserChip003(name.c_str());
//        pLaserChipDepo_->addSubLast(pChip);
//    }
//    addSubGroup(pLaserChipDepo_);
//    //<---------------------


    //�z�[�~���O(���|�W�g��)------>
//    pConnection_LaserChipDepoStore_ = connectToDepositoryManager("EnemyThisbeLaserChip001DepoStore");
//    pLaserChipDepo_ = nullptr;
    //<---------------------

    //���t���N�V����(���|�W�g��)------>
    pConnection_LaserChipDepoStore_ = connectToDepositoryManager("EnemyThisbeLaserChip002DepoStore");
    pLaserChipDepo_ = nullptr;


    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    _pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_CLOSE);
}

void EnemyThisbe::onCreateModel() {
}

void EnemyThisbe::initialize() {
    _pKurokoA->relateMvFaceAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 40000);

//    if (pConnection_LaserChipDepoStore_->chkFirstConnectionIs(this)) {
//        _TRACE_("pConnection_LaserChipDepoStore_�́A���V("<<this<<")����Ă��G�w���I")
//        getPlatformScene()->getSceneDirector()->addSubGroup(
//                pConnection_LaserChipDepoStore_->peek()->extract()
//                );
//    }
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
            if (pLaserChipDepo_) {
                if (pLaserChipDepo_->_num_chip_active == 0) {
                    pLaserChipDepo_ = nullptr;
                }
            } else {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->morphLinerUntil(1, 1.0, 120);
            }
            if (!_pMorpher->isMorphing()) {
                //���S�ɊJ������
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            if (_pProg->isJustChanged()) {
                pLaserChipDepo_ = (LaserChipDepository*)(pConnection_LaserChipDepoStore_->peek()->dispatch()); //���[�U�[�Z�b�g��{�؂�܂��B
            }
            if (pLaserChipDepo_) {
                LaserChip* pLaser = pLaserChipDepo_->dispatch();
                if (pLaser) {
                    pLaser->locateAs(this);
                    pLaser->_pKurokoA->setRzRyMvAng(_pKurokoA->_angFace[AXIS_Z], _pKurokoA->_angFace[AXIS_Y]);
                                       //���[�U�[�̃X�v���C����RELATIVE_DIRECTION�̂���MvAng�̐ݒ肪�K�v�B
                    if (pLaser->_pChip_front == nullptr) {
                        _pSeTx->play3D(SE_FIRE);
                    }
                } else {
                    _pProg->change(PROG_CLOSE);
                }
            } else {
                //�؂��Ȃ������I
                _pProg->change(PROG_CLOSE);
            }
            break;
        }

        case PROG_CLOSE: {
            //�P�T�C�N�����[�U�[�ł��؂���
            _pMorpher->morphLinerUntil(1, 0.0, 120); //����
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
        if (_X >= GgafDxUniverse::_X_gone_right) {
            //WALL������
        } else {
            sayonara();
        }
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
    GGAF_DELETE_NULLABLE(pKurokoStepper_);
        pConnection_LaserChipDepoStore_->close();
    //pConnection_RefractionEffectDepository_->close();
}
