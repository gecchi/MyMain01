#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    ITEM_PROG_NOTIONG = 1, //�������Ă��Ȃ����
    ITEM_PROG_DRIFT      , //�ʏ�ړ����
    ITEM_PROG_ATTACH     , //�z����(���z��)���
    ITEM_PROG_ABSORB     , //�z����(�z����)���
};


MagicPointItem::MagicPointItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat)
               : Item(prm_name, prm_model, prm_pStat) {
    _class_name = "MagicPointItem";
    changeEffectTechnique("DestBlendOne"); //���Z��������Technique�w��
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    setAlpha(0.9);

    _pKurokoA->setFaceAngVelo(AXIS_X, DEG2ANG(3));
    _pKurokoA->setFaceAngVelo(AXIS_Y, DEG2ANG(5));
    _pKurokoA->setFaceAngVelo(AXIS_Z, DEG2ANG(7));
    _pKurokoA->relateFaceAngWithMvAng(true);
    _kDX = _kDY = _kDZ = 0;
    useProgress();
    setHitAble(true, false); //��ʊO�����蔻��͖���
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 400000);
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "decide1");
}

void MagicPointItem::initialize() {
}

void MagicPointItem::onActive() {
    setHitAble(true, false);
    _pKurokoA->setMvVelo(2000);
    _pKurokoA->setMvAcce(100);
    _pKurokoA->forceMvVeloRange(0, 20000);
    _pKurokoB->forceVxyzMvVeloRange(-20000, 20000);
    _pKurokoB->setZeroVxyzMvVelo();
    _pKurokoB->setZeroVxyzMvAcce();
    _pKurokoB->_gravitation_mv_seq_flg = false;
    _pProg->set(ITEM_PROG_DRIFT);
    _SX = _SY = _SZ = 1000;

    //���������ݒ�
    MyShip* pMyShip = P_MYSHIP;
    GgafCore::CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
    //�U��΂�͈͐����`�P�ӂ̒���
    int scattered_renge    = _pCollisionChecker->_pCollisionArea->_papColliPart[0]->_dx; //�����蔻��Ɠ���
    //�����n�_����A���@�ւ̕����ւ̎U��΂�͈͐����`�̈悪�ʒu���鋗���iscattered_distance > (scattered_renge/2) �ł��邱��)
    int scattered_distance = scattered_renge/2 + 800000;
    //�]���āAscattered_distance ����Ă��Ă��A���@�͓����Ȃ��Ă����肬��S�ĉ���ł���B

    float vX, vY, vZ;
    GgafDxUtil::getNormalizeVector(
            pMyShip->_X - _X,
            pMyShip->_Y - _Y,
            pMyShip->_Z - _Z,
            vX, vY, vZ);

    _pKurokoA->setMvAng(
            (int)(_X + (vX * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))),
            (int)(_Y + (vY * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))),
            (int)(_Z + (vZ * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2)))
    );
}

void MagicPointItem::processBehavior() {
    //�ʏ�ړ�
    if (_pProg->get() == ITEM_PROG_DRIFT) {
        //TractorMagic��������ITEM_PROG_ATTACH�ֈڍs
        if (getTractorMagic()->_is_tracting) {
            changeEffectTechniqueInterim("Flush", 6); //�t���b�V��
            setHitAble(false);
            _pProg->change(ITEM_PROG_ATTACH);
        }
        //���邢�� onHit() �� ITEM_PROG_ATTACH ��ԕω�����̂�҂�
    }

    //���@�Ɠ����蔻�肪�q�b�g���A���@�Ɍ���������
    if (_pProg->get() == ITEM_PROG_ATTACH) {
        MyShip* pMyShip = P_MYSHIP;
        if (_pProg->isJustChanged()) {
            //���@�Ɉ��͂ň����񂹂���悤�ȓ����ݒ�
            _pKurokoB->setVxMvVelo(_pKurokoA->_vX*_pKurokoA->_veloMv);
            _pKurokoB->setVyMvVelo(_pKurokoA->_vY*_pKurokoA->_veloMv);
            _pKurokoB->setVzMvVelo(_pKurokoA->_vZ*_pKurokoA->_veloMv);
            _pKurokoB->execGravitationVxyzMvSequence(pMyShip, 20000, 1000, 50000);
            _pKurokoA->setMvVelo(0);
            _pKurokoA->setMvAcce(0);
        }

        //�����@�ߕӂɓ��B�H
        if (abs(pMyShip->_X - _X) < 20000 &&
            abs(pMyShip->_Y - _Y) < 20000 &&
            abs(pMyShip->_Z - _Z) < 20000 ) {

            _kDX = pMyShip->_X - _X;
            _kDY = pMyShip->_Y - _Y;
            _kDZ = pMyShip->_Z - _Z;
            _pProg->change(ITEM_PROG_ABSORB); //�z���z����
        }

    }

    //���@�ߕӂɓ��B���A�z���A�z�����̓���
    if (_pProg->get() == ITEM_PROG_ABSORB) {
        MyShip* pMyShip = P_MYSHIP;
        if (_pProg->isJustChanged()) {
            _pKurokoB->setZeroVxyzMvVelo();
            _pKurokoB->setZeroVxyzMvAcce();
            _pKurokoB->stopGravitationVxyzMvSequence();
        }
        _X = pMyShip->_X + _kDX;
        _Y = pMyShip->_Y + _kDY;
        _Z = pMyShip->_Z + _kDZ;
        _SX -= 100;
        _SY -= 100;
        _SZ -= 100;
        if (_SX < 5) {
            _pSeTransmitter->playImmed(0);
            _pProg->change(ITEM_PROG_NOTIONG);
            sayonara(); //�I��
        }
        P_MYSHIP_SCENE->_pMagicMeter->_pEnagyBar->_pAmount->inc(1);
    }
    _pKurokoA->behave();
    _pKurokoB->behave();
}

void MagicPointItem::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
//    //�ʏ�ړ�
//    if (_pProg->get() == ITEM_PROG_DRIFT) {
//        //onHit() �ŏ�ԕω�����̂�҂�
//    }
//
//    //���@�Ɠ����蔻�肪�q�b�g��
//    if (_pProg->get() == ITEM_PROG_ATTACH) {
//
//    }
//
//    //���@�ɋz�����A�z�����̓���
//    if (_pProg->get() == ITEM_PROG_ABSORB) {
//    }
}

void MagicPointItem::onInactive() {
}

void MagicPointItem::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g


    if (_pProg->get() == ITEM_PROG_DRIFT && (pOther->getKind() & KIND_MY_BODY))  {
        setHitAble(false);
        _pProg->change(ITEM_PROG_ATTACH);
    }

}

MagicPointItem::~MagicPointItem() {
}
