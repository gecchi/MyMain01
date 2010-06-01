#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyIris::EnemyIris(const char* prm_name) : DefaultMeshSetActor(prm_name, "Iris") {
    _class_name = "EnemyIris";
    MyStgUtil::resetEnemyIrisStatus(_pStatus);
    _iMovePatternNo = 0;
    _pProgram_IrisMove = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;
    _pSeReflector->useSe(1);
    _pSeReflector->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
}

void EnemyIris::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.5, 2.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
    _pGgafDx9Model->_pTextureBlinker->beat(60, 3, 1, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
}

void EnemyIris::initialize() {
    setHitAble(true);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->setFaceAngVelo(AXIS_X, 5000);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, -30000, 30000, 30000, 30000);
}

void EnemyIris::onActive() {
    MyStgUtil::resetEnemyIrisStatus(_pStatus);
    if (_pProgram_IrisMove) {
        _pProgram_IrisMove->begin(0); //�X�v���C���ړ����J�n
    }
    _iMovePatternNo = 0;
}

void EnemyIris::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (_iMovePatternNo == 0) {
        if (_pProgram_IrisMove) {
            //�X�v���C���ړ���
            if (!(_pProgram_IrisMove->isExecuting())) {
                _iMovePatternNo++; //�X�v���C���ړ����I�������玟�̍s���p�^�[����
            }
        } else {
            _iMovePatternNo++;
        }
    }

    if (_iMovePatternNo == 1) {
        //�X�v���C���ړ��I����
        _pMover->execTagettingMvAngSequence(pMYSHIP->_X, pMYSHIP->_Y, pMYSHIP->_Z,
                                            3000, 0,
                                            TURN_CLOSE_TO);
        if (_pDispatcher_Shot) {
            //���ˏ�V���b�g����
            int way = 5+5*_RANK_;
            angle* paAngWay = new angle[way];
            GgafDx9Util::getRadialAngle2D(0, way, paAngWay);
            GgafDx9DrawableActor* pActor;
            for (int i = 0; i < way; i++) {
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(-ANGLE180 + paAngWay[i], ANGLE90);
                    pActor->activate();
                }
            }
            DELETEARR_IMPOSSIBLE_NULL(paAngWay);
            //�V���b�g���˃G�t�F�N�g
            if (_pDispatcher_ShotEffect) {
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    pActor->setGeometry(_X, _Y, _Z);
                }
            }

        }
        _iMovePatternNo++; //���̍s���p�^�[����
    }

    if (_iMovePatternNo == 2) {
        if (_Z-10000 < pMYSHIP->_Z && pMYSHIP->_Z < _Z+10000) {
            //���@��Z�����ڋ�
            _pMover->execTagettingMvAngSequence(MyShip::_lim_behaind - 500000 , _Y, _Z,
                                                       2000, 0,
                                                       TURN_CLOSE_TO);
            _pMover->setMvAcce(100);
            _iMovePatternNo++;
        }
    }

    if (_iMovePatternNo == 3) {

    }


    if (_pProgram_IrisMove) {
        _pProgram_IrisMove->behave(); //�X�v���C���ړ���U�镑��
    }
    _pMover->behave();
    //_pSeReflector->behave();
}

void EnemyIris::processJudgement() {
    if (isOutOfGameSpace()) {
        sayonara();
    }
}

void EnemyIris::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyIris::onHit!!! this="<<getName()<<"("<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    //_TRACE_("EnemyIris::onHit!!! prm_pOtherActor="<<prm_pOtherActor->getName()<<"("<<prm_pOtherActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {

        EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        _pSeReflector->play3D(0);
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setGeometry(this);
        }
        sayonara();
    }
}

void EnemyIris::onInactive() {
    sayonara();
}

EnemyIris::~EnemyIris() {
    DELETE_POSSIBLE_NULL(_pProgram_IrisMove);
}
