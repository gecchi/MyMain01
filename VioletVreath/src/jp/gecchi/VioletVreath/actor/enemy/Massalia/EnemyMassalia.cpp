#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassalia::EnemyMassalia(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Massalia", STATUS(EnemyMassalia)) {
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
}

void EnemyMassalia::onCreateModel() {
}

void EnemyMassalia::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, PX2CO(100));
    _pKurokoA->setFaceAngVelo(DEG2ANG(1), DEG2ANG(2), DEG2ANG(3));
    setScaleR(0.5);
}

void EnemyMassalia::onActive() {
    //�X�e�[�^�X���Z�b�g
    MyStgUtil::resetEnemyMassaliaStatus(_pStatus);
    setHitAble(true);
    static DWORD appearances_renge_Z = (MyShip::lim_zleft_ - MyShip::lim_zright_) * 3;
    static DWORD appearances_renge_Y = (MyShip::lim_top_ - MyShip::lim_bottom_) * 3;
    _X = GgafDxUniverse::_X_goneRight - 1000;
    _Y = RND(-(appearances_renge_Y/2) , +(appearances_renge_Y/2));
    _Z = RND(-(appearances_renge_Z/2) , +(appearances_renge_Z/2));
    _pKurokoA->setMvAng(0, D180ANG);
    _pKurokoA->addRyMvAng(RND(DEG2ANG(-5), DEG2ANG(+5)));
    _pKurokoA->addRzMvAng(RND(DEG2ANG(-5), DEG2ANG(+5)));
}

void EnemyMassalia::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
}

void EnemyMassalia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMassalia::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    changeEffectTechniqueInterim("Flush", 2); //�t���b�V��
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->pDP_EffectExplosion001_->dispatch();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        setHitAble(false); //���ł����ꍇ�A����t���[�����̈ȍ~�̏����Ńq�b�g�����Ȃ����߁i�d�v�j
        sayonara();
        //�f�Џo��
        DepositoryConnection* pCon = connectToDepositoryManager("DpCon_MassaliaFragment", this);
        GgafActorDepository* pDepo = pCon->use();
        for (int i =0; i < R_EnemyMassalia_ShotWay; i++) {
            EnemyMassaliaFragment* p = (EnemyMassaliaFragment*)(pDepo->dispatch());
            if (p) {
                p->locateAs(this);
                p->_pKurokoA->takeoverMvFrom(this->_pKurokoA);
                p->_pKurokoA->setMvVelo(p->_pKurokoA->_veloMv/2); //�����̃X�s�[�h��
                p->_pKurokoA->addRyMvAng(RND(DEG2ANG(-45), DEG2ANG(+45)));
                p->_pKurokoA->addRzMvAng(RND(DEG2ANG(-45), DEG2ANG(+45)));
            }
        }
        pCon->close();
    }
}


void EnemyMassalia::onInactive() {
    sayonara();
}


EnemyMassalia::~EnemyMassalia() {
}