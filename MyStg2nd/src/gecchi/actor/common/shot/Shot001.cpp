#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot001::Shot001(const char* prm_name) : DefaultMeshSetActor(prm_name, "Flora") {
    _class_name = "Shot001";
    MyStgUtil::resetShot001Status(_pStatus);
    _pSeReflector->useSe(1);
    _pSeReflector->set(0, "break_glass01", GgafRepeatSeq::nextVal("CH_break_glass01"));
    _pSplineCon = (DefiniteSplineConnection*)(pGOD->_pDefiniteSplineManager->connect("SpCon_HAN")); //�X�v���C����`
    _pSplineProgram = NULL;
}

void Shot001::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    _pScaler->setScale(2000);
    _pScaler->forceScaleRange(2000, 3000);
}

void Shot001::onActive() {
    MyStgUtil::resetShot001Status(_pStatus);
    setHitAble(true);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->setMvVelo(5000*_RANK_);             //�ړ����x
    _pMover->setFaceAngVelo(AXIS_X, 6000*_RANK_); //������݋
    _pSplineProgram = NEW GgafDx9FixedVelocitySplineProgram(this, _pSplineCon->view(), 10000); //�ړ����x�Œ�
    _pSplineProgram->begin(2);
    _pScaler->beat(30,5,2,-1);
}

void Shot001::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //���W�ɔ��f
    _pSplineProgram->behave(); //�X�v���C���ړ���U�镑��
    _pMover->behave();
    _pScaler->behave();
}

void Shot001::processJudgement() {
    if (isOutOfGameSpace()) {
        sayonara();
    }
}

void Shot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        _pSeReflector->play3D(0);
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setGeometry(this);
        }

        sayonara();
    }

    //_pSeReflector->behave();
}


void Shot001::onInactive() {
    DELETE_POSSIBLE_NULL(_pSplineProgram);
}


Shot001::~Shot001() {
    _pSplineCon->close();
}
