#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

int EnemyHesperia::max_laser_way_ = RR_EnemyHesperia_ShotWay(1.0);
//RR_EnemyHesperia_ShotWay�����N���� 1.0�ōő�����悤�ɂ��Ȃ���΂Ȃ�Ȃ�

EnemyHesperia::EnemyHesperia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Hesperia", STATUS(EnemyHesperia)) {

    cnt_laserchip_ = 0;
    laser_length_ = 40;
    //�؂���ꃌ�[�U�[�Z�b�g�̃f�|�W�g���ێ��p
    papLaserChipDepo_ = NEW LaserChipDepository*[max_laser_way_];
    for (int i = 0; i < max_laser_way_; i++) {
        papLaserChipDepo_[i] = NULL;
    }

    pCon_LaserChipDepoStore_ = connectToDepositoryManager("DpCon_EnemyHesperiaLaserChip001DepoStore", NULL);
    pLaserChipDepoStore_ = (GgafActorDepositoryStore*)(pCon_LaserChipDepoStore_->fetch());



    paLocalPos_Laser_ = NEW GgafDxGeoElem[max_laser_way_];
    paPos_Target_ = NEW GgafDxGeoElem[max_laser_way_];
    coord dX = PX_C(10); //���[�U�[���ˌ��̊Ԋu
    for (int i = 0; i < max_laser_way_; i++) {
        paLocalPos_Laser_[i].set(PX_C(-40) + (i*dX),  PX_C(10), 0); //���[�U�[���ˌ��̃��[�J�����W
    }

    _pSeTxer->set(SE_EXPLOSION  , "bomb1"        , GgafRepeatSeq::nextVal("CH_bomb1"));
    _pSeTxer->set(SE_DAMAGED    , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_HATCH_OPEN , "warp"         , GgafRepeatSeq::nextVal("CH_warp"));
    _pSeTxer->set(SE_FIRE       , "yume_Sbend"   , GgafRepeatSeq::nextVal("CH_yume_Sbend"));
    _pSeTxer->set(SE_HATCH_CLOSE, "yume_organ_01", GgafRepeatSeq::nextVal("CH_yume_organ_01"));
    dX_= dZ_ = 0;
    useProgress(PROG_NOTHING);
}

void EnemyHesperia::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.97, 0.5, 12.0);
    _pModel->_pTextureBlinker->setBlink(1.0);
    _pModel->_pTextureBlinker->beat(60*6, 60*2, 60*2, -1);
}

void EnemyHesperia::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(200));
}

void EnemyHesperia::onActive() {
    _pStatus->reset();
    setHitAble(false);
    _pKurokoA->setRzRyMvAng(0, D180ANG);
    _pKurokoA->setMvVelo(1000);
    dX_= dZ_ = 0;
    //_X = PX_C(800); //GgafDxCore::GgafDxUniverse::_X_goneRight - 100;
    _pProg->set(PROG_ENTRY);
}

void EnemyHesperia::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;
    switch (_pProg->get()) {
        case PROG_ENTRY: {
            if (_pProg->isJustChanged()) {
                UTIL::activateEntryEffectOf(this);
                _pFader->setAlpha(0);
                _pFader->intoTargetAlphaLinerUntil(0.98, 20);
            }
            if (_pFader->isWorking()) {
                _pFader->behave();
            } else {
                setHitAble(true);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE: {
            if (_pProg->isJustChanged()) {

            }
            if (_pProg->getFrameInProgress() == 100) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_HATCH_OPEN: {
            if (_pProg->isJustChanged()) {
                _pSeTxer->play3D(SE_HATCH_OPEN);
                _pMorpher->intoTargetLinerUntil(1, 1.0, 120);
            }
            if (_pProg->getFrameInProgress() == 120) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            if (_pProg->isJustChanged()) {
                //���[�U�[�Z�b�g�i���[�U�[�`�b�v�̃f�|�W�g���ŁA�P�{���̃��[�U�[�j�̃f�|�W�g������A
                //���[�U�[�Z�b�g�̎ؓ������݂�
                int laser_way = RR_EnemyHesperia_ShotWay(_RANK_); //���񔭎˃��[�U�[�{��
                coord laser_density = RR_EnemyHesperia_Density(_RANK_); //���񃌁[�U�[�ƃ��[�U�[�̌���
                bool can_fire = false; //���Ȃ��Ƃ���{�͔��˂ł��邩�ǂ���

                for (int i = 0; i < max_laser_way_; i++) {
                    if (laser_way > i) {
                        LaserChipDepository* pLaserChipDepo = (LaserChipDepository*)(pLaserChipDepoStore_->dispatch());
                        if (pLaserChipDepo) {
                            //���[�U�[�Z�b�g�i���[�U�[�`�b�v�̃f�|�W�g���j���؂����o�����B
                            papLaserChipDepo_[i] = pLaserChipDepo;
                            papLaserChipDepo_[i]->config(laser_length_, 1);
                            can_fire = true;
                        } else {
                            //���[�U�[�Z�b�g�i���[�U�[�`�b�v�̃f�|�W�g���j���؂����o���Ȃ������B
                            papLaserChipDepo_[i] = NULL;
                        }
                    } else {
                        papLaserChipDepo_[i] = NULL;
                    }
                }

                if (can_fire) { //���˂���Ł[
                    //������^�[�Q�b�g���W�ݒ�
                    //                    ^
                    //                    | X
                    //                    |
                    //              (b)   |   (c)
                    //                    |
                    //                    |
                    //                    |
                    //       (a)          |              (d)
                    //  Z                 |
                    //  <---------------�� �@------------------
                    //                    |
                    //                    |
                    //                    |
                    //                    |
                    //                    |
                    //                    |
                    //                    |
                    //                    |
                    //                    |
                    //
                    //  (a)(d) �̏ꍇ�AX�����������Z���������������̂�
                    //         X�̏�����������
                    //                    ^
                    //                    | X
                    //                    |
                    //                    |
                    //  �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�� [3]
                    //                    |
                    //                    |
                    //  �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�� [2]
                    //  Z                 |
                    //  <---------------�� �@------------------
                    //                    |
                    //  �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�� [1]
                    //                    |
                    //                    |
                    //  �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�� [0]
                    //                    |
                    //                    |
                    //                    |
                    //�Ƃ���B
                    //
                    //
                    //  (b)(c) �̏ꍇ�AZ�����������X���������������̂�
                    //  Z     �b     �b       �b     �b
                    //  <-----�b-----�b-�� �@-�b-----�b------
                    //        �b     �b       �b     �b
                    //        �b     �b       �b     �b
                    //        ��     ��       ��     ��
                    //       [0]     [1]      [2]    [3]  �E�E�E (b)
                    //       [3]     [2]      [1]    [0]  �E�E�E (c)
                    //  �Ƃ���
                    coord total_laser_effect = laser_density*laser_way+1; //�����ꃌ�[�U�[�̂����ꋗ���i�͈́j

                    dX_ = ABS(_X - pMyShip->_X);
                    dZ_ = ABS(_Z - pMyShip->_Z);
                    if (dX_ < dZ_)  {
                        //(a)(d) �̏ꍇ�AX�����������Z��������������
                        for (int i = 0, tX = -total_laser_effect/2; i < laser_way; i++, tX+=laser_density) {
                            paPos_Target_[i].set(tX, 0, 0);
                        }
                    } else {
                        //(b)(c)  �̏ꍇ�AZ�����������X��������������
                        if (pMyShip->_Z < _Z) {
                            //(b)���@����O�A�w�X�y���A����
                            for (int i = 0, tZ = total_laser_effect/2; i < laser_way; i++, tZ-=laser_density) {
                                paPos_Target_[i].set(0, 0, tZ);
                            }
                        } else {
                            //(c)���@�����A�w�X�y���A����O
                            for (int i = 0, tZ = -total_laser_effect/2; i < laser_way; i++, tZ+=laser_density) {
                                paPos_Target_[i].set(0, 0, tZ);
                            }
                        }
                    }

                    _pSeTxer->play3D(SE_FIRE); //���ˉ�
                    effectFlush(2); //�t���b�V��
                    cnt_laserchip_ = 0;
                }
            }

            //laser_length_�ȓ��̊ԁA���[�U�[�`�b�v��dispatch()�����ݑ�����
            if (cnt_laserchip_ < laser_length_) {
                cnt_laserchip_++;
                EnemyHesperiaLaserChip001* pLaserChip;
                GgafDxGeoElem* p;
                coord turn_dY = getTurnDY(this, pMyShip, (dX_ > dZ_ ? dX_ : dZ_) );
                //��turn_dY �� ���� EnemyHesperiaLaserChip001::turn_dY_�Ɠ�������鎖
                for (int i = 0; i < max_laser_way_; i++) {
                    if (papLaserChipDepo_[i]) {
                        pLaserChip = (EnemyHesperiaLaserChip001*)papLaserChipDepo_[i]->dispatch();
                        if (pLaserChip) {
                            p = &(paLocalPos_Laser_[i]);
                            //���ˌ����W
                            pLaserChip->locate(_X+p->_X, _Y+p->_Y, _Z+p->_Z);
                            //�܂�Ԃ��n�_�֌�����
                            pLaserChip->_pKurokoA->setMvAng(_X + paPos_Target_->_X,
                                                            _Y + paPos_Target_->_Y + turn_dY,
                                                            _Z + paPos_Target_->_Z);
                            pLaserChip->_pKurokoA->setMvVelo(40000);
                            pLaserChip->_pKurokoA->setMvAcce(100+(max_laser_way_-i)*120);
                            //�ŏI�ڕW�n�_��ݒ�
                            pLaserChip->tX_ = pMyShip->_X + paPos_Target_[i]._X;
                            pLaserChip->tY_ = pMyShip->_Y + paPos_Target_[i]._Y;
                            pLaserChip->tZ_ = pMyShip->_Z + paPos_Target_[i]._Z;

                        }
                    }
                }
            } else {
                //���[�U�[��ł��؂���
                _pProg->changeNext();
            }
            break;
        }

        case PROG_HATCH_CLOSE: {
            if (_pProg->isJustChanged()) {
                _pSeTxer->play3D(SE_HATCH_CLOSE);
                _pMorpher->intoTargetLinerUntil(1, 0.0, 120);
            }
            if (_pProg->getFrameInProgress() == 120) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_NOTHING: {
            if (_pProg->getFrameInProgress() == 600) {
                _pProg->change(PROG_MOVE);
            }
            break;
        }
    }
    _pSeTxer->behave();
    _pKurokoA->behave();
}

void EnemyHesperia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyHesperia::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        _pSeTxer->play3D(SE_DAMAGED);
    }
}

void EnemyHesperia::onInactive() {
    //���[�U�[�f�|�W�g���͒x��Ă���߂�
    for (int i = 0; i < max_laser_way_; i++) {
        if (papLaserChipDepo_[i]) {
            papLaserChipDepo_[i]->sayonara(60*10);
        }
    }
    sayonara();
}

coord EnemyHesperia::getTurnDY(GgafDxCore::GgafDxGeometricActor* pThis,
                               GgafDxCore::GgafDxGeometricActor* pMyShip,
                               coord DT) {
    //                        ^ Y
    //                        |
    //                        |�c�c�c�c
    //                      �^|     ^
    //                    �^  |     |
    //                  �^    |     | TurnDY�i�Ԃ��l�j
    //                �^      |     |
    //              �^        |     v
    //            �^         �G�c�c�c�c
    //          �^��=33��     |
    //    ---���@-------------+--------->
    //      �^:               |
    //    �^  :               |
    //  �^    :<------------->|
    //        :     DT(����)  |
    //
    //DY = DT�Etan(30��) - (�G_Y - ���@_Y)
    static double tan33 = tan(PI/12);
    coord dY = pThis->_Y - pMyShip->_Y;
    coord TurnDY = DT*tan33 - dY;
    if (TurnDY < 0) {
        return PX_C(100);
    } else {
        return TurnDY;
    }
}

EnemyHesperia::~EnemyHesperia() {
    pCon_LaserChipDepoStore_->close();
    DELETEARR_IMPOSSIBLE_NULL(paLocalPos_Laser_);
    DELETEARR_IMPOSSIBLE_NULL(paPos_Target_);
    DELETEARR_IMPOSSIBLE_NULL(papLaserChipDepo_);
}
