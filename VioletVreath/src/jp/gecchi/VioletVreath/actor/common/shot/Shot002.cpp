#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot002::Shot002(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Flora", STATUS(Shot002)) {
    _class_name = "Shot002";
    my_frame_ = 0;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "break_glass01", GgafRepeatSeq::nextVal("CH_break_glass01"));
}

void Shot002::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -50000, -50000, -50000, 50000, 50000, 50000);
}

void Shot002::onActive() {
    _pStatus->reset();
    setHitAble(true);
    _pScaler->setScale(2000);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setMvVelo(R_Shot002_MvVelo);
    _pKurokoA->setFaceAngVelo(AXIS_X, R_Shot002_AngVelo);
    my_frame_ = 0;
}

void Shot002::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));



    if (my_frame_ == 70) {
        _pKurokoA->execTurnMvAngSequence(P_MYSHIP,
                                           3000, 0,
                                           TURN_CLOSE_TO);
    }

    if (my_frame_ > 70 && _pKurokoA->_mv_ang_ry_target_flg == false && _pKurokoA->_mv_ang_rz_target_flg == false) {
        _pKurokoA->execTurnMvAngSequence(
                    P_MYSHIP,
                    100, 0,
                    TURN_CLOSE_TO);
    }
    //���W�ɔ��f
    _pKurokoA->behave();
    _pScaler->behave();
    _pSeTransmitter->behave();
    my_frame_++;
}

void Shot002::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot002::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        EffectExplosion001* pExplo001 = getFromCommon(EffectExplosion001);
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locatedBy(this);
        }
        sayonara();
    }
}

Shot002::~Shot002() {

}
