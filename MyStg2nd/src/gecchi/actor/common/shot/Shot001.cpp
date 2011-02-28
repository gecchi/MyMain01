#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot001::Shot001(const char* prm_name) : DefaultMeshSetActor(prm_name, "Flora") {
    _class_name = "Shot001";
    MyStgUtil::resetShot001Status(_pStatus);
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "break_glass01", GgafRepeatSeq::nextVal("CH_break_glass01"));
    _pSplineCon = (Spline3DConnection*)(P_GOD->_pSpline3DManager->getConnection("SpCon_HAN")); //�X�v���C����`
    _pSplineProgram = NEW GgafDx9FixedVelocitySplineProgram(this, _pSplineCon->refer(), 10000); //�ړ����x�Œ�
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
    _pKuroko->relateRzRyFaceAngToMvAng(true);
    _pKuroko->setMvVelo(5000+_RANK_*5000);             //�ړ����x
    _pKuroko->setFaceAngVelo(AXIS_X, 6000+_RANK_*6000); //������݋
    _pSplineProgram->begin(2);
    _pScaler->beat(30,5,2,-1);
}

void Shot001::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //���W�ɔ��f
    _pSplineProgram->behave(); //�X�v���C���ړ���U�镑��
    _pKuroko->behave();
    _pScaler->behave();
}

void Shot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->activate();
            pExplo001->locateWith(this);
        }

        sayonara();
    }

    //_pSeTransmitter->behave();
}


void Shot001::onInactive() {
}


Shot001::~Shot001() {
    DELETE_IMPOSSIBLE_NULL(_pSplineProgram);
    _pSplineCon->close();
}
