#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyMetis::EnemyMetis(const char* prm_name) : DefaultMeshSetActor(prm_name, "Metis") {
    _class_name = "EnemyMetis";
    MyStgUtil::resetEnemyMetisStatus(_pStatus);
    _width_X = 220*2*LEN_UNIT;
    _height_Z = 220*2*LEN_UNIT;
    _depth_Y = 36*2*LEN_UNIT;
    _iMovePatternNo = 0;
    _pSeReflector->useSe(2);
    _pSeReflector->set(0, "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeReflector->set(1, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
}

void EnemyMetis::initialize() {
    int nArea = 0;
    for (int i = 0; i < (_width_X - _depth_Y) ; i+= _depth_Y) {
        nArea++;
    }
    _pCollisionChecker->makeCollision(nArea);
    for (int i = 0, n = 0; i < (_width_X - _depth_Y)  ; i+= _depth_Y, n++) {
        _pCollisionChecker->setColliAAB(n, i - ((_depth_Y/2.0)/1.5)-(_width_X/2 - _depth_Y/2.0), -((_depth_Y/2.0)/1.5), -(_height_Z/2.0),
                                       i + ((_depth_Y/2.0)/1.5)-(_width_X/2 - _depth_Y/2.0),  ((_depth_Y/2.0)/1.5),  (_height_Z/2.0),
                                       false, false, true
                                   );
    }
}

void EnemyMetis::onActive() {
    MyStgUtil::resetEnemyMetisStatus(_pStatus);
    _iMovePatternNo = 0;
    setAlpha(0.6);
    _pMover->setMvVelo(0);
    _pMover->setVxMvVelo(-3000);
    _pMover->setFaceAngVelo(AXIS_Z, 1000);

    CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
    pRndGen->changeSeed(GameGlobal::_pSceneGame->_frame_of_behaving);
    DWORD appearances_renge_Z = (MyShip::_lim_zleft - MyShip::_lim_zright) * 3;
    DWORD appearances_renge_Y = (MyShip::_lim_top - MyShip::_lim_bottom) * 3;
    _X = GgafDx9Universe::_X_goneRight - 1000;
    _Y = (pRndGen->genrand_int32() % (appearances_renge_Y)) - (appearances_renge_Y/2);
    _Z = (pRndGen->genrand_int32() % (appearances_renge_Z)) - (appearances_renge_Z/2);
    setHitAble(true);
}

void EnemyMetis::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //���W�ɔ��f
    _pMover->behave();
    //_pSeReflector->behave();
}

void EnemyMetis::processJudgement() {
    if (isOutOfGameSpace()) {
        sayonara();
    }
}

void EnemyMetis::onHit(GgafActor* prm_pOtherActor) {
    if (_pStatus->get(STAT_Stamina) < 0) {
        return;
    }
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;

    //�����Ƀq�b�g�G�t�F�N�g
    chengeEffectTechniqueInterim("Flush", 2); //�t���b�V��
    _pSeReflector->play3D(0);
        //�����ɏ��ŃG�t�F�N�g
    if (pOther->getKind() & KIND_MY) {
        EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->setGeometry((GgafDx9GeometricActor*)prm_pOtherActor);
            pExplo001->activate();
        }
    } else {
        //�n�`��������G�t�F�N�g�Ȃ��i�n�`�̐^�񒆂ɕ\������Ă��܂�����);
    }
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�����ɏ��ŃG�t�F�N�g

        EffectExplosion001* pExplo001_2 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        _pSeReflector->play3D(1);
        if (pExplo001_2 != NULL) {
            pExplo001_2->setGeometry((GgafDx9GeometricActor*)prm_pOtherActor);
            pExplo001_2->activate();
        }
        inactivate();
    }
}

void EnemyMetis::onInactive() {
    sayonara();
}
EnemyMetis::~EnemyMetis() {
}
