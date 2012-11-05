#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHermione::EnemyHermione(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Hermione", STATUS(EnemyHermione)) {
    _class_name = "EnemyHermione";


    int num_arm = 3; //�r�̐�
    int num_arm_body = 5;  //ArmBody�̌��i�P�ȏ�j
    angle pos_rz[] = {D_ANG(0),   D_ANG(45),   D_ANG(90)  }; //���₷�ꏊ
    angle pos_ry[] = {D_ANG(0),   D_ANG(0),    D_ANG(0)   };
    static coord R = PX_C(500);     //�{��Hermione�̔��a
    static coord arm_R = PX_C(40);  //�����̘r�̊֐߂P�̔��a


    EnemyHermione::Arm* paArm_ = NEW EnemyHermione::Arm[num_arm];
    float vx,vy,vz;
    EnemyHermioneArmBody* pArmBody;
    for (int arm = 0; arm < num_arm; arm++) {
        paArm_[arm].pos_Rz = pos_rz[arm];
        paArm_[arm].pos_Ry = pos_ry[arm];
        UTIL::getNormalizeVectorZY(paArm_[arm].pos_Rz, paArm_[arm].pos_Ry,
                                   vx, vy, vz);
        paArm_[arm].papArmBody = NEW EnemyHermioneArmBody*[num_arm_body];
        for (int i = 0; i < num_arm_body; i++) {
            paArm_[arm].papArmBody[i] = NEW EnemyHermioneArmBody("BD");
            if (i == 0) {
                //���{
                this->addSubGroupAsFk(
                        paArm_[arm].papArmBody[i],
                        vx*R, vy*R, vz*R,
                        D0ANG, paArm_[arm].pos_Ry, paArm_[arm].pos_Rz);
            } else {
                //�c��͐^�����������łȂ���
                paArm_[arm].papArmBody[i-1]->addSubGroupAsFk(
                                               paArm_[arm].papArmBody[i],
                                               arm_R, 0, 0,
                                               D0ANG, D0ANG, D0ANG);
            }
        }
        //�Ō�Ƀw�b�h������
        paArm_[arm].pArmHead = NEW EnemyHermioneArmHead("HD");
        paArm_[arm].papArmBody[num_arm_body-1]->
          addSubGroupAsFk(paArm_[arm].pArmHead,
                          arm_R, 0, 0,
                          D0ANG, D0ANG, D0ANG);

    }



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
}
