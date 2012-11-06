#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHermione::EnemyHermione(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Hermione", STATUS(EnemyHermione)) {
    _class_name = "EnemyHermione";


    num_arm_ = 3; //�r�̐�
    num_arm_body_ = 5;  //ArmBody�̌��i�P�ȏ�j
    angle pos_rz[] = {D_ANG(0),   D_ANG(45),   D_ANG(90)  }; //���₷�ꏊ
    angle pos_ry[] = {D_ANG(0),   D_ANG(0),    D_ANG(0)   };
    static coord R = PX_C(500);     //�{��Hermione�̔��a
    static coord arm_R = PX_C(40);  //�����̘r�̊֐߂P�̔��a


    EnemyHermione::Arm* paArm_ = NEW EnemyHermione::Arm[num_arm];
    float vx,vy,vz;
    EnemyHermioneArmBody* pArmBody;

    //���̂悤�ȃc���[�\�������(�r���R�{�̏ꍇ)
    //Hermione
    // ��
    //GroupHead()
    // ��
    //ArmBody(���{)  ��   ArmBody(���{)   ��  ArmBody(���{)
    // ��                   ��                  ��
    //ArmBody              ArmBody             ArmBody
    // ��                   ��                  ��
    //ArmBody              ArmBody             ArmBody
    // ��                   ��                  ��
    //ArmBody              ArmBody             ArmBody
    // ��                   ��                  ��
    //ArmBody              ArmBody             ArmBody
    // ��                   ��                  ��
    //GroupHead()          GroupHead()         GroupHead()
    // ��                   ��                  ��
    //ArmHead              ArmHead             ArmHead
    for (int arm = 0; arm < num_arm_; arm++) { //�r�̖{���Ń��[�v
        paArm_[arm].pos_Rz_ = pos_rz[arm];
        paArm_[arm].pos_Ry_ = pos_ry[arm];
        UTIL::getNormalizeVectorZY(paArm_[arm].pos_Rz_, paArm_[arm].pos_Ry_,
                                   vx, vy, vz);
        paArm_[arm].papArmBody_ = NEW EnemyHermioneArmBody*[num_arm_body_];

        for (int i = 0; i < num_arm_body_; i++) { //�r�̓���(�֐�)
            paArm_[arm].papArmBody_[i] = NEW EnemyHermioneArmBody("BD");
            if (i == 0) {
                //ArmBody���{
                this->addSubGroupAsFk(
                        paArm_[arm].papArmBody_[i],
                        vx*R, vy*R, vz*R,
                        D0ANG, paArm_[arm].pos_Ry_, paArm_[arm].pos_Rz_);
            } else {
                //ArmBody�c��B�^�����������łȂ���
                paArm_[arm].papArmBody_[i-1]->addSubGroupAsFk(
                                               paArm_[arm].papArmBody_[i],
                                               arm_R, 0, 0,
                                               D0ANG, D0ANG, D0ANG);
            }
        }
        //ArmHead�A�Ō�Ƀw�b�h������
        paArm_[arm].pArmHead_ = NEW EnemyHermioneArmHead("HD");
        paArm_[arm].papArmBody_[num_arm_body_-1]->addSubGroupAsFk(paArm_[arm].pArmHead_,
                                                                 arm_R, 0, 0,
                                                                 D0ANG, D0ANG, D0ANG);
    }
_TRACE_("�E��I�I�I�I�I�I");
dump();

    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"   , GgafRepeatSeq::nextVal("CH_bomb1"));
    useProgress(5);
}

void EnemyHermione::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyHermione::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 90000);
    setScaleR(0.3);
}

void EnemyHermione::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
    _pProg->set(PROG_MOVE);
}

void EnemyHermione::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case PROG_MOVE: {
            break;
        }

        default:
            break;
    }


    _pKurokoA->behave();
    _pMorpher->behave();
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
        _pSeTxer->play3D(SE_EXPLOSION);

        //���@���Ɍ�����ď��ł̏ꍇ�A
        if (pOther->getKind() & KIND_MY) {
            //�A�C�e���o��
            UTIL::activateItemOf(this);
        }
        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        _pSeTxer->play3D(SE_DAMAGED);
    }
}

void EnemyHermione::onInactive() {
    //sayonara();
}

void EnemyHermione::addArm(angle prm_rz, angle prm_ry) {

}

EnemyHermione::~EnemyHermione() {
    DELETEARR_IMPOSSIBLE_NULL(paArm_);
}
