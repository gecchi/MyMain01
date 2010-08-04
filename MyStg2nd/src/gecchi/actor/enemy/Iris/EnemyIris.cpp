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
    _pSplineProgram = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
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

    _iMovePatternNo = 0; //�s���p�^�[�����Z�b�g
}

void EnemyIris::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_iMovePatternNo) {
        case 0:  //�y�p�^�[���O�F�X�v���C���ړ��J�n�z
            if (_pSplineProgram) {
                _pSplineProgram->begin(0); //�X�v���C���ړ����J�n
            }
            _iMovePatternNo++; //���̍s���p�^�[����
            break;

        case 1:  //�y�p�^�[���P�F�X�v���C���ړ��I���҂��z
            if (_pSplineProgram) {
                //�X�v���C���ړ��L��
                if (!(_pSplineProgram->isExecuting())) {
                    _iMovePatternNo++; //�X�v���C���ړ����I�������玟�̍s���p�^�[����
                }
            } else {
                //�X�v���C���ړ�����
                _iMovePatternNo++; //�����Ɏ��̍s���p�^�[����
            }
            break;

        case 2:  //�y�p�^�[���Q�F���ˏ�V���b�g���˂Ǝ��@�֕����]���z
            if (_pDispatcher_Shot) {
                //���ˏ�V���b�g
                int way = 5+5*_RANK_; //�V���b�gWAY��
                angle* paAngWay = new angle[way];
                GgafDx9Util::getRadialAngle2D(0, way, paAngWay);
                GgafDx9DrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                    if (pActor_Shot) {
                        pActor_Shot->setGeometry(this);
                        pActor_Shot->_pMover->setRzRyMvAng(paAngWay[i], ANGLE90);
                        pActor_Shot->activate();
                    }
                }
                DELETEARR_IMPOSSIBLE_NULL(paAngWay);
                //�V���b�g���˃G�t�F�N�g
                if (_pDispatcher_ShotEffect) {
                    GgafDx9DrawableActor* pActo_Effect = (GgafDx9DrawableActor*)_pDispatcher_ShotEffect->employ();
                    if (pActo_Effect) {
                        pActo_Effect->setGeometry(this);
                        pActo_Effect->activate();
                    }
                }
            }
            //���@�֕����]��
            _pMover->execTagettingMvAngSequence(pMYSHIP->_X, pMYSHIP->_Y, pMYSHIP->_Z,
                                                3000, 0,
                                                TURN_CLOSE_TO);
            _iMovePatternNo++; //���̍s���p�^�[����
            break;

        case 3:  //�y�s���p�^�[���R�F���@�փO���b�Ƌt��]�ŕ����]���J�n�z
            if (_Z-10000 < pMYSHIP->_Z && pMYSHIP->_Z < _Z+10000) {
                //���@��Z�����ڋ߂�����O���b�Ƌt��]�ŕ����]��
                _pMover->execTagettingMvAngSequence(MyShip::_lim_behaind - 500000 , _Y, _Z,
                                                   10000, 0,
                                                   TURN_CLOSE_TO);
                _pMover->setMvAcce(100);
                _iMovePatternNo++;
            } else {
                //���@��Z�����ڋ߂���܂ő҂�
            }
            break;
        default:
            break;
    }


    if (_pSplineProgram) {
        _pSplineProgram->behave(); //�X�v���C���ړ���U�镑��
    }
    _pMover->behave();
    //_pSeTransmitter->behave();
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
        _pSeTransmitter->play3D(0);
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
    DELETE_POSSIBLE_NULL(_pSplineProgram);
}
