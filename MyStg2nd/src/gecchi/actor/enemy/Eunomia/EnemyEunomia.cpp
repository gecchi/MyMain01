#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyEunomia::EnemyEunomia(const char* prm_name) : DefaultMeshSetActor(prm_name, "Eunomia") {
    _class_name = "EnemyEunomia";
    MyStgUtil::resetEnemyEunomiaStatus(_pStatus);
    _iMovePatternNo = 0;
    _pSplineProgram = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
    useProgress(10);
}

void EnemyEunomia::onCreateModel() {
}

void EnemyEunomia::initialize() {
    setHitAble(true);
    _pKuroko->setFaceAngVelo(AXIS_X, -4000);
    _pKuroko->relateRzRyFaceAngToMvAng(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 40000);
}

void EnemyEunomia::onReset() {
    MyStgUtil::resetEnemyEunomiaStatus(_pStatus);
    _iMovePatternNo = 0; //�s���p�^�[�����Z�b�g
    _pProgress->change(1);
}


void EnemyEunomia::onActive() {
    if (_pSplineProgram == NULL) {
        throwGgafCriticalException("EnemyEunomia�̓X�v���C���K�{�ł�config���ĉ�����");
    }
    reset();
}

void EnemyEunomia::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�y�p�^�[��1�F�X�v���C���ړ��z
    if (_pProgress->wasChangedTo(1)) {
        _pSplineProgram->begin(0); //�X�v���C���ړ����J�n(1:���W����)
    }
    if (_pProgress->get() == 1) {
        //�X�v���C���ړ��I���҂�
        if (_pSplineProgram->isExecuting()) {
            //�҂��ڂ���
        } else {
            _pProgress->changeNext(); //���̃p�^�[����
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
                int way = 10+_RANK_*10; //�V���b�gWAY��
                angle* paAngWay = NEW angle[way];
                GgafDx9Util::getRadialAngle2D(0, way, paAngWay);
                GgafDx9DrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                    if (pActor_Shot) {
                        pActor_Shot->locateAs(this);
                        pActor_Shot->_pKuroko->setRzRyMvAng(paAngWay[i], ANGLE90);
                        pActor_Shot->activate();
                    }
                }
                DELETEARR_IMPOSSIBLE_NULL(paAngWay);
                //�V���b�g���˃G�t�F�N�g
                if (_pDispatcher_ShotEffect) {
                    GgafDx9DrawableActor* pEffectActor_Shot = (GgafDx9DrawableActor*)_pDispatcher_ShotEffect->employ();
                    if (pEffectActor_Shot) {
                        pEffectActor_Shot->locateAs(this);
                        pEffectActor_Shot->activate();
                    }
                }
            }
//            //���@�֕����]��
            _pKuroko->orderTagettingMvAngSequence(P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
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
    _pKuroko->behave();
    //_pSeTransmitter->behave();
}

void EnemyEunomia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyEunomia::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyEunomia::onHit!!! this="<<getName()<<"("<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    //_TRACE_("EnemyEunomia::onHit!!! prm_pOtherActor="<<prm_pOtherActor->getName()<<"("<<prm_pOtherActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;

    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->activate();
            pExplo001->locateAs(this);
            pExplo001->_pKuroko->takeoverMvFrom(_pKuroko);
        }

        //���@���Ɍ�����ď��ŁA���t�H���[�V���������̏ꍇ�A
        //�t�H�[���[�V�����Ɏ��g�������ꂽ����`����B
        if ((pOther->getKind() & KIND_MY) && (getParent()->_obj_class & Obj_GgafDx9FormationActor)) {
            ((GgafDx9FormationActor*)getParent())->wasDestroyedFollower(this);
        }
        setHitAble(false); //���ł����ꍇ�A����t���[�����̈ȍ~�̏����Ńq�b�g�����Ȃ����߁i�d�v�j
        sayonara();

        Item* pItem = (Item*)P_COMMON_SCENE->_pDP_MagicPointItem001->employ();
        if (pItem) {
            pItem->locateAs(this);
            pItem->activate();
        }
    }
}

void EnemyEunomia::onInactive() {
    sayonara();
}

EnemyEunomia::~EnemyEunomia() {
    DELETE_POSSIBLE_NULL(_pSplineProgram);
}
