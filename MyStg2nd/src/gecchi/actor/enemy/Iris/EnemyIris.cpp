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
    _pSplProgram = NULL;
    _pStore_Shot = NULL;
    _pStore_ShotEffect = NULL;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
}

void EnemyIris::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.5, 2.0);
    _pModel->_pTextureBlinker->setBlink(0.5);
    _pModel->_pTextureBlinker->beat(60, 3, 1, -1);
}

void EnemyIris::initialize() {
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 5000);
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
            if (_pSplProgram) {
                _pSplProgram->begin(0); //�X�v���C���ړ����J�n
            }
            _iMovePatternNo++; //���̍s���p�^�[����
            break;

        case 1:  //�y�p�^�[���P�F�X�v���C���ړ��I���҂��z
            if (_pSplProgram) {
                //�X�v���C���ړ��L��
                if (!(_pSplProgram->isExecuting())) {
                    _iMovePatternNo++; //�X�v���C���ړ����I�������玟�̍s���p�^�[����
                }
            } else {
                //�X�v���C���ړ�����
                _iMovePatternNo++; //�����Ɏ��̍s���p�^�[����
            }
            break;

        case 2:  //�y�p�^�[���Q�F���ˏ�V���b�g���˂Ǝ��@�֕����]���z
            if (_pStore_Shot) {
                //���ˏ�V���b�g
                int way = R_EnemyIris_ShotWay; //�V���b�gWAY��
                angle* paAngWay = NEW angle[way];
                GgafDx9Util::getRadialAngle2D(0, way, paAngWay);
                GgafDx9DrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDx9DrawableActor*)_pStore_Shot->dispatch();
                    if (pActor_Shot) {
                        pActor_Shot->locateAs(this);
                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAngWay[i], ANGLE90);
                    }
                }
                DELETEARR_IMPOSSIBLE_NULL(paAngWay);
                //�V���b�g���˃G�t�F�N�g
                if (_pStore_ShotEffect) {
                    GgafDx9DrawableActor* pTestActor_Shot = (GgafDx9DrawableActor*)_pStore_ShotEffect->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->locateAs(this);
                    }
                }
            }
            //���@�֕����]��
            _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                3000, 0,
                                                TURN_CLOSE_TO);
            _iMovePatternNo++; //���̍s���p�^�[����
            break;

        case 3:  //�y�s���p�^�[���R�F���@�փO���b�Ƌt��]�ŕ����]���J�n�z
            if (_Z-10000 < P_MYSHIP->_Z && P_MYSHIP->_Z < _Z+10000) {
                //���@��Z�����ڋ߂�����O���b�Ƌt��]�ŕ����]��
                _pKurokoA->execTurnMvAngSequence(MyShip::_lim_behaind - 500000 , _Y, _Z,
                                                   10000, 0,
                                                   TURN_CLOSE_TO);
                _pKurokoA->setMvAcce(100);
                _iMovePatternNo++;
            } else {
                //���@��Z�����ڋ߂���܂ő҂�
            }
            break;
        default:
            break;
    }


    if (_pSplProgram) {
        _pSplProgram->behave(); //�X�v���C���ړ���U�镑��
    }
    _pKurokoA->behave();
    //_pSeTransmitter->behave();
}

void EnemyIris::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyIris::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyIris::onHit!!! this="<<getName()<<"("<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    //_TRACE_("EnemyIris::onHit!!! prm_pOtherActor="<<prm_pOtherActor->getName()<<"("<<prm_pOtherActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {

        //���@���Ɍ�����ď��ŁA���t�H���[�V���������̏ꍇ�A
        //�t�H�[���[�V�����Ɏ��g�������ꂽ����`����B
        if ((pOther->getKind() & KIND_MY) && (getParent()->_obj_class & Obj_GgafDx9FormationActor)) {
            ((GgafDx9FormationActor*)getParent())->wasDestroyedFollower(this);
        }

        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        setHitAble(false); //����t���[�����ŕ�����q�b�g�����Ȃ����ߏd�v
        sayonara();
    }
}

void EnemyIris::onInactive() {
    sayonara();
}

EnemyIris::~EnemyIris() {
    DELETE_POSSIBLE_NULL(_pSplProgram);
}
