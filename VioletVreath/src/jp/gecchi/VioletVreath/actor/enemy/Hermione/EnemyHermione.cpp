#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHermione::EnemyHermione(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Hermione", STATUS(EnemyHermione)) {
    _class_name = "EnemyHermione";

    num_arm_ = 6; //�r�̐�
    num_arm_part_ = 7;  //�r�̐ߐ��i3�ȏ�j
    angle pos_rz[] = {D_ANG(0),   D_ANG(90),   D_ANG(180),  D_ANG(270), D_ANG(0) , D_ANG(0)  }; //���₷�ꏊ
    angle pos_ry[] = {D_ANG(0),   D_ANG(0),    D_ANG(0)  ,  D_ANG(0)  , D_ANG(90), D_ANG(270) };
    static coord R = PX_C(100);     //�{��Hermione�̔��a
    static coord arm_R = PX_C(45);  //�����̘r�̊֐߂P�̔��a


    //���̂悤�ȃc���[�\�������(�r���R�{�̏ꍇ)
    //Hermione
    // ��
    //GroupHead()
    // ��
    //ArmPart(���{)  ��   ArmPart(���{)   ��  ArmPart(���{)
    // ��                   ��                  ��
    //ArmPart              ArmPart             ArmPart
    // ��                   ��                  ��
    //ArmPart(��_)        ArmPart(��_)       ArmPart(��_)
    // ��                   ��                  ��
    //ArmPart              ArmPart             ArmPart
    // ��                   ��                  ��
    //ArmPart              ArmPart             ArmPart
    // ��                   ��                  ��
    //ArmPart(��)          ArmPart(��)          ArmPart(��)

    paArm_ = NEW EnemyHermione::Arm[num_arm_];
    float vx,vy,vz;
    for (int arm = 0; arm < num_arm_; arm++) { //�r�̖{���Ń��[�v
        paArm_[arm].pos_Rz_ = pos_rz[arm];
        paArm_[arm].pos_Ry_ = pos_ry[arm];
        UTIL::getNormalizeVectorZY(paArm_[arm].pos_Rz_, paArm_[arm].pos_Ry_,
                                   vx, vy, vz); //�r����������̃x�N�g��
        paArm_[arm].papArmPart_ = NEW EnemyHermioneArm*[num_arm_part_];

        for (int i = 0; i < num_arm_part_; i++) { //�r�̓���(�֐�)
            if (i == (num_arm_part_-1)/2) {
                //�r�̐߂̎�_����(�r�̐ߐ��̔���������Ɏ�_�߂��쐬����)
                paArm_[arm].papArmPart_[i] = NEW EnemyHermioneArmWeak("ArmWeak");
            } else if (i == num_arm_part_-1) {
                //�r�̐߂̐擪����
                paArm_[arm].papArmPart_[i] = NEW EnemyHermioneArmHead("ArmHead");
            } else {
                //���ʂ̘r�̐�
                paArm_[arm].papArmPart_[i] = NEW EnemyHermioneArmBody("ArmBody");
            }
            if (i == 0) {
                //�߂����{�̏ꍇ
                //�֐ߌŒ肳����
                paArm_[arm].papArmPart_[i]->config(0, 0);
                //���g��y��Ƃ���FK�ݒ�
                this->addSubGroupAsFk(
                        paArm_[arm].papArmPart_[i],
                        vx*R, vy*R, vz*R,
                        D0ANG, paArm_[arm].pos_Ry_, paArm_[arm].pos_Rz_);
            } else {
                //�߂����{�ȊO�ꍇ
                //��ɍs���قǉ��͈͂Ɖ�]�X�s�[�h���傫������i����ŁAFK�Ȃ̂�IK���ۂ���������I�j
                paArm_[arm].papArmPart_[i]->config(D_ANG(25+(i*2.5)), 20+(i*60));
                //��O�̘r�̐߂�y��Ƃ���FK�ݒ�
                paArm_[arm].papArmPart_[i-1]->addSubGroupAsFk(
                                               paArm_[arm].papArmPart_[i],
                                               arm_R, 0, 0,
                                               D0ANG, D0ANG, D0ANG);
            }
        }
    }

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(5);
}

void EnemyHermione::onCreateModel() {
}

void EnemyHermione::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 90000);
}

void EnemyHermione::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);

    _pProg->reset(PROG_INIT);
    setHitAble(false);
}

void EnemyHermione::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            _pAFader->setAlpha(0);
            _pKurokoA->setMvVelo(0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }

        case PROG_ENTRY: {
            if (_pProg->getFrameInProgress() == 120) {
                _pAFader->intoTargetAlphaAcceStep(1.0, 0.000, 0.0001);
            }
            if (getAlpha() > 0.8) {
                setHitAble(true);
                throwEventLowerTree(EVENT_HERMIONE_ENTRY_DONE);
                _pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->setMvVelo(1000);
//                _pKurokoA->setFaceAngVelo(20, 67, 99);
                _pKurokoA->execTurnFaceAngSequenceTwd(P_MYSHIP,
                                                      1, 10,
                                                      TURN_ANTICLOSE_TO, false);
                _pKurokoA->setMvAngTwd(P_MYSHIP);
            }
            break;
        }

        default:
            break;
    }
    _pAFader->behave();
    _pKurokoA->behave();
    _pMorpher->behave();
    _pSeTx->behave();
}

void EnemyHermione::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyHermione::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //��������
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_EXPLOSION);

        //���@���Ɍ�����ď��ł̏ꍇ�A
        if (pOther->getKind() & KIND_MY) {
            //�A�C�e���o��
            UTIL::activateItemOf(this);
            //���ŃG�t�F�N�g
            UTIL::activateDestroyedEffectOf(this);
        }

        throwEventLowerTree(EVENT_HERMIONE_SAYONARA);

        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyHermione::onInactive() {
    //sayonara();
}

void EnemyHermione::addArm(angle prm_rz, angle prm_ry) {

}

EnemyHermione::~EnemyHermione() {
    GGAF_DELETEARR(paArm_);
}
