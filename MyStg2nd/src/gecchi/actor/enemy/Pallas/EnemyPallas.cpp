#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyPallas::EnemyPallas(const char* prm_name) : DefaultMeshSetActor(prm_name, "Pallas") {
    _class_name = "EnemyPallas";
    MyStgUtil::resetEnemyPallasStatus(_pStatus);
    _iMovePatternNo = 0;
    _pSplineProgram = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
}

void EnemyPallas::onCreateModel() {
}

void EnemyPallas::initialize() {
    setHitAble(true);
    _pMover->setFaceAngVelo(AXIS_Z, -7000);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 40000);
}

void EnemyPallas::onActive() {
    if (_pSplineProgram == NULL) {
        throwGgafCriticalException("EnemyPallas�̓X�v���C���K�{�ł�config���ĉ�����");
    }

    MyStgUtil::resetEnemyPallasStatus(_pStatus);

    _iMovePatternNo = 0; //�s���p�^�[�����Z�b�g
    setProgress(1);
}

void EnemyPallas::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�y�p�^�[��1�F�X�v���C���ړ��z
    if (onChangeProgressAt(1)) {
        _pSplineProgram->begin(0); //�X�v���C���ړ����J�n(1:���W����)
    }
    if (getProgress() == 1) {
        //�X�v���C���ړ��I���҂�
        if (_pSplineProgram->isExecuting()) {
            //�҂��ڂ���
        } else {
            nextProgress(); //���̃p�^�[����
        }
    }


    switch (_iMovePatternNo) {
        case 0:  //�y�p�^�[���O�F�X�v���C���ړ��J�n�z
            if (_pSplineProgram) {
                _pSplineProgram->begin(0); //�X�v���C���ړ����J�n(1:���W����)
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
                    GgafDx9DrawableActor* pEffectActor_Shot = (GgafDx9DrawableActor*)_pDispatcher_ShotEffect->employ();
                    if (pEffectActor_Shot) {
                        pEffectActor_Shot->setGeometry(this);
                        pEffectActor_Shot->activate();
                    }
                }
            }
//            //���@�֕����]��
            _pMover->execTagettingMvAngSequence(pMYSHIP->_X, _Y, pMYSHIP->_Z,
                                                2000, 0,
                                                TURN_CLOSE_TO);
            _iMovePatternNo++; //���̍s���p�^�[����
            break;

        case 3:  //�y�s���p�^�[���R�z

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

void EnemyPallas::processJudgement() {
    if (isOutOfGameSpace()) {
        sayonara();
    }
}

void EnemyPallas::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyPallas::onHit!!! this="<<getName()<<"("<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    //_TRACE_("EnemyPallas::onHit!!! prm_pOtherActor="<<prm_pOtherActor->getName()<<"("<<prm_pOtherActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;

    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion003* pExplo003 = (EffectExplosion003*)pCOMMONSCENE->_pDispatcher_EffectExplosion003->employ();
        _pSeTransmitter->play3D(0);
        if (pExplo003 != NULL) {
            pExplo003->activate();
            pExplo003->setGeometry(this);
        }

        //���@���Ɍ�����ď��ŁA���t�H���[�V���������̏ꍇ�A
        //�t�H�[���[�V�����Ɏ��g�������ꂽ����`����B
        if ((pOther->getKind() & KIND_MY) && (getParent()->_actor_class & Obj_GgafDx9FormationActor)) {
            ((GgafDx9FormationActor*)getParent())->wasDestroyedFollower(this);
        }
        setHitAble(false); //����t���[�����ŕ�����q�b�g�����Ȃ����ߏd�v
        sayonara();
    }
}

void EnemyPallas::onInactive() {
    sayonara();
}

EnemyPallas::~EnemyPallas() {
    DELETE_POSSIBLE_NULL(_pSplineProgram);
}
