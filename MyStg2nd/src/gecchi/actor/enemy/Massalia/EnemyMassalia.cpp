#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

EnemyMassalia::EnemyMassalia(const char* prm_name) :
        DefaultMeshActor(prm_name, "Massalia", STATUS(EnemyMassalia)) {

    _pDepoCon_Fragment = connectDepositoryManager("DpCon_MassaliaFragment", this);
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
}

void EnemyMassalia::onCreateModel() {
}

void EnemyMassalia::initialize() {
    setHitAble(true);

    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, PX2CO(200));
}

void EnemyMassalia::onActive() {
    //ステータスリセット
    MyStgUtil::resetEnemyMassaliaStatus(_pStatus);

    DWORD appearances_renge_Z = (MyShip::_lim_zleft - MyShip::_lim_zright) * 3;
    DWORD appearances_renge_Y = (MyShip::_lim_top - MyShip::_lim_bottom) * 3;
    _X = GgafDxUniverse::_X_goneRight - 1000;
    _Y = RND(-(appearances_renge_Y/2) , +(appearances_renge_Y/2));
    _Z = RND(-(appearances_renge_Z/2) , +(appearances_renge_Z/2));
    angle asobi_Rz = RND(-DEG2ANG(5), +DEG2ANG(5));
    angle asobi_Ry = RND(-DEG2ANG(5), +DEG2ANG(5));
    _pKurokoA->setMvAng(asobi_Rz, asobi_Ry);
}

void EnemyMassalia::processBehavior() {
    //加算ランクポイントを減少
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

    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        setHitAble(false); //消滅した場合、同一フレーム内の以降の処理でヒットさせないため（重要）
        sayonara();

        //断片出現
        for (int i =0; i < R_EnemyMassalia_ShotWay; i++) {
            EnemyMassaliaFragment* p = (EnemyMassaliaFragment*)_pDepoCon_Fragment->use()->dispatch();
            p->locateAs(this);
            p->_pKurokoA->takeoverMvFrom(this->_pKurokoA);
            p->_pKurokoA->addRyMvAng(RND(-DEG2ANG(5), +DEG2ANG(5)));
            p->_pKurokoA->addRzMvAng(RND(-DEG2ANG(5), +DEG2ANG(5)));
        }
    }
}


void EnemyMassalia::onInactive() {
    sayonara();
}


EnemyMassalia::~EnemyMassalia() {
    _pDepoCon_Fragment->close();
}
