#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMetis::EnemyMetis(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Metis", STATUS(EnemyMetis)) {
    _class_name = "EnemyMetis";
    width_X_ = 220*2*LEN_UNIT;
    height_Z_ = 220*2*LEN_UNIT;
    depth_Y_ = 36*2*LEN_UNIT;
    iMovePatternNo_ = 0;
    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "yume_shototsu", GgafRepeatSeq::nextVal("CH_MetisHit"));
    _pSeTransmitter->set(1, "bom10", GgafRepeatSeq::nextVal("CH_MetisDestroy"));     //����
}

void EnemyMetis::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyMetis::initialize() {
    int nArea = 0;
    for (int i = 0; i < (width_X_ - depth_Y_) ; i+= depth_Y_) {
        nArea++;
    }
    _pCollisionChecker->makeCollision(nArea);
    for (int i = 0, n = 0; i < (width_X_ - depth_Y_)  ; i+= depth_Y_, n++) {
        _pCollisionChecker->setColliAAB(n, i - ((depth_Y_/2.0)/1.5)-(width_X_/2 - depth_Y_/2.0), -((depth_Y_/2.0)/1.5), -(height_Z_/2.0),
                                           i + ((depth_Y_/2.0)/1.5)-(width_X_/2 - depth_Y_/2.0),  ((depth_Y_/2.0)/1.5),  (height_Z_/2.0),
                                           false, false, true
                                       );
    }
}

void EnemyMetis::onActive() {
    _pStatus->reset();
    iMovePatternNo_ = 0;
    setAlpha(1.0);
    _pKurokoA->setMvVelo(0);
    _pKurokoB->setVxMvVelo(-3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);
    static DWORD appearances_renge_Z = (MyShip::lim_zleft_ - MyShip::lim_zright_) * 3;
    static DWORD appearances_renge_Y = (MyShip::lim_top_ - MyShip::lim_bottom_) * 3;
    _X = GgafDxUniverse::_X_goneRight - 1000;
    _Y = RND(-(appearances_renge_Y/2) , +(appearances_renge_Y/2));
    _Z = RND(-(appearances_renge_Z/2) , +(appearances_renge_Z/2));
    setHitAble(true);
}

void EnemyMetis::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //���W�ɔ��f
    _pKurokoA->behave();
    _pKurokoB->behave();
    //_pSeTransmitter->behave();
}

void EnemyMetis::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMetis::onHit(GgafActor* prm_pOtherActor) {
    if (_pStatus->get(STAT_Stamina) < 0) {
        return;
    }
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    //�����Ƀq�b�g�G�t�F�N�g
    changeEffectTechniqueInterim("Flush", 2); //�t���b�V��
    _pSeTransmitter->play3D(0);
        //�����ɏ��ŃG�t�F�N�g
    if (pOther->getKind() & KIND_MY) {
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->pDP_EffectExplosion001_->dispatch();
        if (pExplo001) {
            pExplo001->locateAs((GgafDxGeometricActor*)prm_pOtherActor);
            pExplo001->activate();
        }
    } else {
        //�n�`��������G�t�F�N�g�Ȃ��i�n�`�̐^�񒆂ɕ\������Ă��܂�����);
    }
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�����ɏ��ŃG�t�F�N�g

        EffectExplosion001* pExplo0012_ = (EffectExplosion001*)P_COMMON_SCENE->pDP_EffectExplosion001_->dispatch();
        _pSeTransmitter->play3D(1);
        if (pExplo0012_) {
            pExplo0012_->locateAs((GgafDxGeometricActor*)prm_pOtherActor);
            pExplo0012_->activate();
        }
        sayonara();

        //�A�C�e���o��
        Item* pItem = (Item*)P_COMMON_SCENE->pDP_MagicPointItem001_->dispatch();
        if (pItem) {
            pItem->locateAs(this);
        }
    }
}

void EnemyMetis::onInactive() {
    sayonara();
}
EnemyMetis::~EnemyMetis() {
}
