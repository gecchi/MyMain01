#include "EnemyErmione.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArmWeak.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArmHead.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArmBody.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyErmione::EnemyErmione(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Ermione", STATUS(EnemyErmione)) {
    _class_name = "EnemyErmione";
    pAFader_ = NEW GgafDxAlphaFader(this);
//    num_arm_ = 6; //�r�̍��v�{��
//    num_arm_part_ = 11;  //�e�r�̐ߐ��i3�ȏ�j
//    angle pos_rz[] = {D_ANG(0),   D_ANG(90),   D_ANG(180),  D_ANG(270), D_ANG(0) , D_ANG(0)   }; //���₷�ꏊ
//    angle pos_ry[] = {D_ANG(0),   D_ANG(0),    D_ANG(0)  ,  D_ANG(0)  , D_ANG(90), D_ANG(270) };


    num_arm_ = 4; //�r�̍��v�{��
    num_arm_part_ = 11;  //�e�r�̐ߐ��i3�ȏ�j
    //���l�ʑ̂̒��_�ɘr�𐶂₻���I
    //1�ӂ�a �Ƃ���ƍ�����  (��6)a / 3
    //�d�S�͍�����1/4
    //  (��6)a / 3) * (3/4) = (��6)a / 4
    //  (��6)a / 3) * (1/4) = (��6)a / 12
    //�d�S��(0,0,0)�Ƃ��A�E�̒��_�����
    //(   (��6)a / 4 ,            0,     0 ) �Ƃ����
    //�c���
    //( -((��6)a / 12),  (��3)a / 2,     0 )
    //( -((��6)a / 12), -(��3)a / 6,   a/2 )
    //( -((��6)a / 12), -(��3)a / 6,  -a/2 )
    //http://sansuu.noblog.net/blog/e/10762566.writeback
    double a = 1.0;
    angle pos_rz[4];
    angle pos_ry[4];
    const double sqrt6 = sqrt(6.0);
    const double sqrt3 = sqrt(3.0);
    pos_rz[0] = D_ANG(0);   pos_ry[0] = D_ANG(0);
    UTIL::convVectorToRzRy( -(sqrt6*a)/12.0,  (sqrt3*a)/2.0,    0.0,   pos_rz[1], pos_ry[1]);
    UTIL::convVectorToRzRy( -(sqrt6*a)/12.0, -(sqrt3*a)/6.0,  a/2.0,   pos_rz[2], pos_ry[2]);
    UTIL::convVectorToRzRy( -(sqrt6*a)/12.0, -(sqrt3*a)/6.0, -a/2.0,   pos_rz[3], pos_ry[3]);


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
                paArm_[arm].papArmPart_[i]->config(arm, i, 0, 0);
                //���g��y��Ƃ���FK�ݒ�
                this->addSubGroupAsFk(
                        paArm_[arm].papArmPart_[i],
                        vx*R, vy*R, vz*R,
                        D0ANG, paArm_[arm].pos_Ry_, paArm_[arm].pos_Rz_);
            } else {
                //�߂����{�ȊO�ꍇ
                //��ɍs���قǉ��͈͂Ɖ�]�X�s�[�h���傫������i����ŁAFK�Ȃ̂�IK���ۂ���������I�j
                paArm_[arm].papArmPart_[i]->config(arm, i, D_ANG(10+(i*2.5)), 10+(i*10));
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
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, 90000);
}

void EnemyErmione::onActive() {
    getStatus()->reset();
    setMorphWeight(1, 0.0);

    getProgress()->reset(PROG_INIT);
    setHitAble(false);
}

void EnemyErmione::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pKuroko->setMvVelo(10);
            pProg->changeNext();
            break;
        }

        case PROG_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pProg->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons = pEffectEntry->getFrameOfSummonsBegin();
            static const frame summoning_frames = pEffectEntry->getSummoningFrames();
            if (pProg->hasArrivedAt(frame_of_summons)) {
                pAFader_->transitionLinerUntil(1.0, summoning_frames);
            }
            if (pProg->hasArrivedAt(frame_of_summons + summoning_frames)) {
                setHitAble(true);
                throwEventLowerTree(EVENT_ERMIONE_ENTRY_DONE);
                pKuroko->setMvAngTwd(P_MYSHIP);
                pKuroko->setMvVelo(0);
                pKuroko->asstFaceAng()->turnFaceAngByDtTwd(
                        P_MYSHIP, TURN_CLOSE_TO, true, 60*30,
                        0.4, 0.6, 0, true);

                pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE: {
            if (pProg->hasJustChanged()) {
                pKuroko->setFaceAngVelo(AXIS_X, 55);
                pKuroko->setFaceAngVelo(AXIS_Y, 53);
                pKuroko->setFaceAngVelo(AXIS_Z, 51);
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
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyErmione::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
        throwEventLowerTree(EVENT_ERMIONE_SAYONARA);
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
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
