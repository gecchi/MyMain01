#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemySylviaEye::EnemySylviaEye(const char* prm_name, EnemySylvia* prm_pSylvia) :
        DefaultMorphMeshActor(prm_name, "1/SylviaEye", STATUS(EnemySylviaEye)) {
        //CubeMapMorphMeshActor(prm_name, "1/ThaliaCM", STATUS(EnemySylviaEye)) {

    _class_name = "EnemySylviaEye";
    setScaleR(0.3*10);
    pSylvia_ = prm_pSylvia;
    locateWith(pSylvia_);

    pLaserChipDepo_ = NEW LaserChipDepository("DepoLaserChip");
    pLaserChipDepo_->config(60, 1, NULL); //Thalia�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
    EnemySylviaEyeStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //���[�U�[�X�g�b�N
        std::string name = "LaserChip("+ ITOS(i) + ")";
        pChip = NEW EnemySylviaEyeStraightLaserChip001(name.c_str());
        pChip->setSource(this); //�ʒu��������
        pLaserChipDepo_->addSubLast(pChip);
    }
    addSubGroup(pLaserChipDepo_);

    pEffect_ = NEW EffectSylviaEye001("EffectSylviaEye001");
    pEffect_->inactivateImmed();
    addSubGroup(pEffect_);

    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"   , GgafRepeatSeq::nextVal("CH_bomb1"));
    _pSeTxer->set(SE_FIRE     , "laser001", GgafRepeatSeq::nextVal("CH_laser001"));
    useProgress(PROG_CLOSE);

    is_wake_ = false;
}

void EnemySylviaEye::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemySylviaEye::initialize() {
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 200000);
}

void EnemySylviaEye::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pProg->set(PROG_MOVE);
    locateWith(pSylvia_);
    rotateWith(pSylvia_);
    _pKurokoA->setRzMvAngVelo(pSylvia_->_pKurokoA->_angveloFace[AXIS_Z]);
    _pKurokoA->setRyMvAngVelo(pSylvia_->_pKurokoA->_angveloFace[AXIS_Y]);
}

void EnemySylviaEye::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    locateWith(pSylvia_);
    switch (_pProg->get()) {
        case PROG_MOVE: {
            break;
        }
        case PROG_OPEN: {
            if (_pProg->hasJustChanged()) {
                _pMorpher->intoTargetLinerUntil(1, 1.0, 180); //�J��
            }
            if (_pProg->getFrameInProgress() > 240) {
                _pProg->changeNext();
            }
            _pKurokoA->followMvFrom(pSylvia_->_pKurokoA);
            _pKurokoA->setRzMvAngVelo(pSylvia_->_pKurokoA->_angveloFace[AXIS_Z]);
            _pKurokoA->setRyMvAngVelo(pSylvia_->_pKurokoA->_angveloFace[AXIS_Y]);
            break;
        }

        case PROG_TURN: {
            if (_pProg->hasJustChanged()) {
                _pKurokoA->execTurnMvAngSequence(P_MYSHIP, D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            if (_pProg->getFrameInProgress() > 240) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE_BEGIN: {
            if (_pProg->hasJustChanged()) {
                //_pKurokoA->execTurnMvAngSequence(P_MYSHIP, D_ANG(1), 0, TURN_ANTICLOSE_TO, false);
                pEffect_->activate();
            }
            pEffect_->locateWith(this);
            if (pEffect_->onChangeToInactive()) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_IN_FIRE: {
            if (_pProg->hasJustChanged()) {
                _pKurokoA->execTurnMvAngSequence(P_MYSHIP, 10, 0, TURN_CLOSE_TO, false);
            }
            LaserChip* pChip = pLaserChipDepo_->dispatch();
            if (pChip) {
                if (pChip->_pChip_front == NULL) {
                    _pSeTxer->play3D(SE_FIRE);
                }
            } else {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_FIRE_END: {
            if (_pProg->hasJustChanged()) {
                _pMorpher->intoTargetLinerUntil(1, 0.0, 180); //����
                _pKurokoA->setRzMvAngVelo(pSylvia_->_pKurokoA->_angveloFace[AXIS_Z]);
                _pKurokoA->setRyMvAngVelo(pSylvia_->_pKurokoA->_angveloFace[AXIS_Y]);
            }
            //�d��
            if (_pProg->getFrameInProgress() >= 300) {
                _pProg->change(PROG_OPEN);
            }
            break;
        }

        default:
            break;
    }


    _pKurokoA->behave();
    _pMorpher->behave();
    _pSeTxer->behave();
}

void EnemySylviaEye::processJudgement() {
//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemySylviaEye::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //��������
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);

        //�ł��Ԃ��e
//        if (pDepo_Shot_) {
//            UTIL::shotWay004(this, pDepo_Shot_,
//                             PX_C(20),
//                             8, D_ANG(10),
//                             2000, 200,
//                             12, 3, 0.9);
//
//        }

        //���@���Ɍ�����ď��ł̏ꍇ�A
        if (pOther->getKind() & KIND_MY) {
            //�A�C�e���o��
            UTIL::activateItemOf(this);
        }
        _TRACE_("EnemySylviaEye::onHit() ��ʂɂȂ������ throwEventToUpperTree(SYLVIA_EXPLOSION)");
        throwEventToUpperTree(SYLVIA_EXPLOSION); //�e��EnemySylvia��j�󂷂�C�x���g�𓊂���
        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        pSylvia_->effectFlush(2);
        _pSeTxer->play3D(SE_DAMAGED);
    }
}

void EnemySylviaEye::onInactive() {
    //sayonara();
}

void EnemySylviaEye::wake() {
    is_wake_ = true;
    _pProg->change(PROG_OPEN);
}

EnemySylviaEye::~EnemySylviaEye() {
}