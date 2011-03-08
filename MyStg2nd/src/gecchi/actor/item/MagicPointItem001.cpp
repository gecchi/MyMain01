#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MagicPointItem001::MagicPointItem001(const char* prm_name)
               : Item(prm_name, "EffectMagic001") {
    _class_name = "MagicPointItem001";
    MyStgUtil::resetMagicPointItem001Status(_pStatus);
    changeEffectTechnique("DestBlendOne"); //���Z��������Technique�w��
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    setAlpha(0.9);

    _pKuroko->setFaceAngVelo(AXIS_X, 3*1000);
    _pKuroko->setFaceAngVelo(AXIS_Y, 5*1000);
    _pKuroko->setFaceAngVelo(AXIS_Z, 7*1000);
    _pKuroko->relateRzRyFaceAngToMvAng(true);
    _kDX = _kDY = _kDZ = 0;
}

void MagicPointItem001::initialize() {
    setHitAble(true, false);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 300000);
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "decide1");
    useProgress();
}

void MagicPointItem001::onReset() {

    MyStgUtil::resetMagicPointItem001Status(_pStatus);
    setHitAble(true, false);
    _pKuroko->setMvVelo(2000);
//    _pKuroko->forceMvVeloRange(0, 20000);
//    _pKuroko->forceVxMvVeloRange(-20000, 20000);
//    _pKuroko->forceVyMvVeloRange(-20000, 20000);
//    _pKuroko->forceVzMvVeloRange(-20000, 20000);
//    _pKuroko->setVxMvVelo(0);
//    _pKuroko->setVyMvVelo(0);
//    _pKuroko->setVzMvVelo(0);
//    _pKuroko->setVxMvAcce(0);
//    _pKuroko->setVyMvAcce(0);
//    _pKuroko->setVzMvAcce(0);
//    _pKuroko->_gravitation_mv_seq_flg = false;
    _pProgress->set(ITEM_PROG_DRIFT);
    _SX = _SY = _SZ = 1000;
}
void MagicPointItem001::onActive() {
//    _pKuroko->setFaceAngVelo(AXIS_Y, 5*1000);
//    _pKuroko->setFaceAngVelo(AXIS_Z, 7*1000);
    reset();
    MyShip* pMyShip = P_MYSHIP;
    CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
    //�U��΂�͈͐����`�P�ӂ̒���
    int scattered_renge    = _pCollisionChecker->_pCollisionArea->_papColliPart[0]->_dx; //�����蔻��Ɠ���
    //�����n�_����A���@�ւ̕����ւ̎U��΂�͈͐����`�̈悪�ʒu���鋗���iscattered_distance > (scattered_renge/2) �ł��邱��)
    int scattered_distance = scattered_renge/2 + 800000;
    //�]���āAscattered_distance ����Ă��Ă��A���@�͓����Ȃ��Ă����肬��S�ĉ���ł���B

    float vX, vY, vZ;
    GgafDx9Util::getNormalizeVector(
            pMyShip->_X - _X,
            pMyShip->_Y - _Y,
            pMyShip->_Z - _Z,
            vX, vY, vZ);

    _pKuroko->setMvAng(
            (int)(_X + (vX * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))),
            (int)(_Y + (vY * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))),
            (int)(_Z + (vZ * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2)))
    );
//    _TRACE_("---");
//    _TRACE_("(X,Y,Z)=("<<_X<<","<<_Y<<","<<_Z<<")");
//    _TRACE_("(pMyShip->_X,pMyShip->Y,pMyShip->Z)=("<<pMyShip->_X<<","<<pMyShip->_Y<<","<<pMyShip->_Z<<")");
//    _TRACE_("(vX,vY,vZ)=("<<vX<<","<<vY<<","<<vZ<<")");
//    _TRACE_("scattered_renge="<<scattered_renge<<"");
//    _TRACE_("scattered_distance="<<scattered_distance<<"");
//    _TRACE_("tX="<<(int)(_X + (vX * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))));
//    _TRACE_("tY="<<(int)(_Y + (vY * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))));
//    _TRACE_("tZ="<<(int)(_Z + (vZ * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))));

}

void MagicPointItem001::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;

    //�ʏ�ړ�
    if (_pProgress->get() == ITEM_PROG_DRIFT) {
        //�q�b�g����܂ő҂��ڂ���
    }

    //���@�ƃq�b�g���A���@�Ɍ���������
    if (_pProgress->get() == ITEM_PROG_ATTACH) {
        if (_pProgress->isJustChanged()) {
//            _pKuroko->setVxMvVelo(_pKuroko->_vX*_pKuroko->_veloMv);
//            _pKuroko->setVyMvVelo(_pKuroko->_vY*_pKuroko->_veloMv);
//            _pKuroko->setVzMvVelo(_pKuroko->_vZ*_pKuroko->_veloMv);
//            _pKuroko->setMvVelo(0);
//            _pKuroko->setMvAcce(0);
//            _pKuroko->orderGravitationMvSequence(
//                    pMyShip, 20000, 1000, 50000);
            _pKuroko->keepTagetingMvAngAllTime(pMyShip, 1000, 100, TURN_CLOSE_TO);
            _pKuroko->setMvVelo(5000);
        }

//        _pKuroko->orderTagettingMvAngSequence(pMyShip, 1000, 500, TURN_CLOSE_TO);



        if (abs(pMyShip->_X - _X) < 20000 &&
            abs(pMyShip->_Y - _Y) < 20000 &&
            abs(pMyShip->_Z - _Z) < 20000 ) {
            _kDX = pMyShip->_X - _X;
            _kDY = pMyShip->_Y - _Y;
            _kDZ = pMyShip->_Z - _Z;
            _pKuroko->stopTagettingMvAngSequence();
            _pProgress->change(ITEM_PROG_ABSORB);
        }
    }

    //���@�ɋz�����A�z�����̓���
    if (_pProgress->get() == ITEM_PROG_ABSORB) {
        if (_pProgress->isJustChanged()) {
            _pKuroko->setVxMvVelo(0);
            _pKuroko->setVyMvVelo(0);
            _pKuroko->setVzMvVelo(0);
            _pKuroko->_gravitation_mv_seq_flg = false;
        }
        _X = pMyShip->_X + _kDX;
        _Y = pMyShip->_Y + _kDY;
        _Z = pMyShip->_Z + _kDZ;
        _SX -= 100;
        _SY -= 100;
        _SZ -= 100;
        if (_SX < 5) {
            _pSeTransmitter->playImmediately(0);
            _pProgress->change(ITEM_PROG_NOTIONG);
            sayonara(); //�I��
        }
        P_MYSHIP_SCENE->_pEnagyBar->_enagy += 1;
    }
    _pKuroko->behave();
}

void MagicPointItem001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void MagicPointItem001::onInactive() {
}

void MagicPointItem001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g


    if (_pProgress->get() == ITEM_PROG_DRIFT && pOther->getKind() & KIND_MY_BODY)  {
        setHitAble(false);
        _pProgress->change(ITEM_PROG_ATTACH);
    }
//
//        P_MYSHIP_SCENE->_pEnagyBar->_enagy += 10;
//        _pSeTransmitter->playImmediately(0);
//        setHitAble(false);
//        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
//        if (pExplo001) {
//            pExplo001->locateWith(this);
//            pExplo001->activate();
//        }
//        sayonara();
//    }


}

MagicPointItem001::~MagicPointItem001() {
}
