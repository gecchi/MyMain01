#include "EnemyErmione.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArmWeak.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArmHead.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArmBody.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyErmione::EnemyErmione(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Ermione", STATUS(EnemyErmione)) {
    _class_name = "EnemyErmione";
    pAFader_ = NEW GgafDxAlphaFader(this);
    num_arm_ = 6; //�r�̍��v�{��
    num_arm_part_ = 11;  //�e�r�̐ߐ��i3�ȏ�j
    angle pos_rz[] = {D_ANG(0),   D_ANG(90),   D_ANG(180),  D_ANG(270), D_ANG(0) , D_ANG(0)  }; //���₷�ꏊ
    angle pos_ry[] = {D_ANG(0),   D_ANG(0),    D_ANG(0)  ,  D_ANG(0)  , D_ANG(90), D_ANG(270) };
    static coord R = PX_C(130);     //�{��Ermione�̔��a
    static coord arm_R = PX_C(45);  //�����̘r�̊֐߂P�̔��a

    //���̂悤�ȃc���[�\�������(�r���R�{�̏ꍇ)
    //Ermione
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
    //ArmPart(��)          ArmPart(��)         ArmPart(��)

    paArm_ = NEW EnemyErmione::Arm[num_arm_];
    float vx, vy, vz;
    for (int arm = 0; arm < num_arm_; arm++) { //�r�̖{���Ń��[�v
        paArm_[arm].pos_Rz_ = pos_rz[arm];
        paArm_[arm].pos_Ry_ = pos_ry[arm];
        UTIL::convRzRyToVector(paArm_[arm].pos_Rz_, paArm_[arm].pos_Ry_,
                               vx, vy, vz); //�r����������̃x�N�g��
        paArm_[arm].papArmPart_ = NEW EnemyErmioneArm*[num_arm_part_];

        for (int i = 0; i < num_arm_part_; i++) { //�r�̓���(�֐�)
            if (i == (num_arm_part_-1)/2) {
                //�r�̐߂̎�_����(�r�̐ߐ��̔���������Ɏ�_�߂��쐬����)
                paArm_[arm].papArmPart_[i] = NEW EnemyErmioneArmWeak("ArmWeak");
            } else if (i == num_arm_part_-1) {
                //�r�̐߂̐擪����
                paArm_[arm].papArmPart_[i] = NEW EnemyErmioneArmHead("ArmHead");
            } else {
                //���ʂ̘r�̐�
                paArm_[arm].papArmPart_[i] = NEW EnemyErmioneArmBody("ArmBody");
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
                paArm_[arm].papArmPart_[i]->config(D_ANG(10+(i*2.5)), 20+(i*60));
                //��O�̘r�̐߂�y��Ƃ���FK�ݒ�
                paArm_[arm].papArmPart_[i-1]->addSubGroupAsFk(
                                               paArm_[arm].papArmPart_[i],
                                               arm_R, 0, 0,
                                               D0ANG, D0ANG, D0ANG); //�y��ڍs�͐^����������̂� Face rz,ry=0,0 �ŗǂ�
            }
        }
    }
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyErmione::onCreateModel() {
}

void EnemyErmione::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliSphere(0, 90000);
}

void EnemyErmione::onActive() {
    getStatus()->reset();
    setMorphWeight(1, 0.0);

    getProgress()->reset(PROG_INIT);
    setHitAble(false);
}

void EnemyErmione::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pKuroko->setMvVelo(10);
            UTIL::activateEntryEffectOf(this);
            pProg->changeNext();
            break;
        }

        case PROG_ENTRY: {
            if (pProg->hasArrivedAt(120)) {
                pAFader_->transitionAcceStep(1.0, 0.000, 0.0001);
            }
            if (getAlpha() > 0.8) {
                setHitAble(true);
                throwEventLowerTree(EVENT_ERMIONE_ENTRY_DONE);
                pKuroko->setMvAngTwd(P_MYSHIP);
                pKuroko->setMvVelo(10);
                pKuroko->asstB()->turnFaceAngByDtTwd(
                        P_MYSHIP, TURN_CLOSE_TO, true, 60*30,
                        0.4, 0.6, 0, true);

                pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE: {
            if (pProg->isJustChanged()) {
                pKuroko->setFaceAngVelo(AXIS_X, 15);
                pKuroko->setFaceAngVelo(AXIS_Y, 13);
                pKuroko->setFaceAngVelo(AXIS_Z, 11);
            }
            break;
        }

        default: {
            break;
        }
    }
    pAFader_->behave();
    pKuroko->behave();
    getMorpher()->behave();
    getSeTx()->behave();
}

void EnemyErmione::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyErmione::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        getSeTx()->play3D(SE_EXPLOSION);
        throwEventLowerTree(EVENT_ERMIONE_SAYONARA);
    } else {
        //��j��
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyErmione::onInactive() {
    //sayonara();
}

void EnemyErmione::addArm(angle prm_rz, angle prm_ry) {

}

EnemyErmione::~EnemyErmione() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETEARR(paArm_);
}
