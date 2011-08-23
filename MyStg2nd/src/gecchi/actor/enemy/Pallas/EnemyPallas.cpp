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
    _pSplSeq = NULL;
    _pDepo_Shot = NULL;
    _pDepo_ShotEffect = NULL;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
    useProgress(10);
}

void EnemyPallas::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyPallas::initialize() {
    setHitAble(true);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -7000);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 40000);
}

void EnemyPallas::onActive() {
    if (_pSplSeq == NULL) {
        throwGgafCriticalException("EnemyPallas�̓X�v���C���K�{�ł�config���ĉ�����");
    }

    MyStgUtil::resetEnemyPallasStatus(_pStatus);

    _iMovePatternNo = 0; //�s���p�^�[�����Z�b�g
    _pProg->change(1);
}

void EnemyPallas::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�y�p�^�[��1�F�X�v���C���ړ��z
    if (_pProg->isJustChangedTo(1)) {
        _pSplSeq->exec(ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
    }
    if (_pProg->get() == 1) {
        //�X�v���C���ړ��I���҂�
        if (_pSplSeq->isExecuting()) {
            //�҂��ڂ���
        } else {
            _pProg->changeNext(); //���̃p�^�[����
        }
    }


    switch (_iMovePatternNo) {
        case 0:  //�y�p�^�[���O�F�X�v���C���ړ��J�n�z
            if (_pSplSeq) {
                _pSplSeq->exec(ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
            }
            _iMovePatternNo++; //���̍s���p�^�[����
            break;

        case 1:  //�y�p�^�[���P�F�X�v���C���ړ��I���҂��z
            if (_pSplSeq) {
                //�X�v���C���ړ��L��
                if (!(_pSplSeq->isExecuting())) {
                    _iMovePatternNo++; //�X�v���C���ړ����I�������玟�̍s���p�^�[����
                }
            } else {
                //�X�v���C���ړ�����
                _iMovePatternNo++; //�����Ɏ��̍s���p�^�[����
            }
            break;

        case 2:  //�y�p�^�[���Q�F���ˏ�V���b�g���˂Ǝ��@�֕����]���z
            if (_pDepo_Shot) {
                //���ˏ�V���b�g
                int way = R_EnemyPallas_ShotWay; //�V���b�gWAY��
                angle* paAngWay = NEW angle[way];
                GgafDx9Util::getRadialAngle2D(0, way, paAngWay);
                GgafDx9DrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDx9DrawableActor*)_pDepo_Shot->dispatch();
                    if (pActor_Shot) {
                        pActor_Shot->locateAs(this);
                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAngWay[i], ANGLE90);
                        pActor_Shot->activate();
                    }
                }
                DELETEARR_IMPOSSIBLE_NULL(paAngWay);
                //�V���b�g���˃G�t�F�N�g
                if (_pDepo_ShotEffect) {
                    GgafDx9DrawableActor* pTestActor_Shot = (GgafDx9DrawableActor*)_pDepo_ShotEffect->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->locateAs(this);
                    }
                }
            }
//            //���@�֕����]��
            _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
                                                2000, 0,
                                                TURN_CLOSE_TO);
            _iMovePatternNo++; //���̍s���p�^�[����
            break;

        case 3:  //�y�s���p�^�[���R�z

            break;
        default:
            break;
    }


    if (_pSplSeq) {
        _pSplSeq->behave(); //�X�v���C���ړ���U�镑��
    }
    _pKurokoA->behave();
    //_pSeTransmitter->behave();
}

void EnemyPallas::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyPallas::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyPallas::onHit!!! this="<<getName()<<"("<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    //_TRACE_("EnemyPallas::onHit!!! prm_pOtherActor="<<prm_pOtherActor->getName()<<"("<<prm_pOtherActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;

    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }

        //���@���Ɍ�����ď��ŁA���t�H���[�V���������̏ꍇ�A
        //�t�H�[���[�V�����Ɏ��g�������ꂽ����`����B
        if ((pOther->getKind() & KIND_MY) && (getParent()->_obj_class & Obj_GgafDx9FormationActor)) {
            ((GgafDx9FormationActor*)getParent())->wasDestroyedFollower(this);
        }
        setHitAble(false); //���ł����ꍇ�A����t���[�����̈ȍ~�̏����Ńq�b�g�����Ȃ����߁i�d�v�j
        sayonara();
    }
}

void EnemyPallas::onInactive() {
    sayonara();
}

EnemyPallas::~EnemyPallas() {
    DELETE_POSSIBLE_NULL(_pSplSeq);
}
