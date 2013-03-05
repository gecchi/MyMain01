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
    now_laser_way_ = 0;
    //�؂���ꃌ�[�U�[�Z�b�g�̃f�|�W�g���ێ��p
    papLaserChipDepo_ = NEW LaserChipDepository*[max_laser_way_];
    for (int i = 0; i < max_laser_way_; i++) {
        papLaserChipDepo_[i] = nullptr;
    }

    pConn_LaserChipDepoStore_ = connectToDepositoryManager("Conn_EnemyHesperiaLaserChip001DepoStore", nullptr);
    pLaserChipDepoStore_ = (GgafActorDepositoryStore*)(pConn_LaserChipDepoStore_->fetch());

    paLocalPos_Laser_ = NEW GgafDxGeoElem[max_laser_way_];
    paPos_Target_ = NEW GgafDxGeoElem[max_laser_way_];
    coord dX = PX_C(10); //���[�U�[���ˌ��̊Ԋu
    for (int i = 0; i < max_laser_way_; i++) {
        paLocalPos_Laser_[i].set(PX_C(-40) + (i*dX),  PX_C(10), 0); //���[�U�[���ˌ��̃��[�J�����W
    }

    _pSeTx->set(SE_EXPLOSION  , "WAVE_EXPLOSION_MIDDLE_001");
    _pSeTx->set(SE_DAMAGED    , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_HATCH_OPEN , "WAVE_HATCH_OPEN_001");
    _pSeTx->set(SE_FIRE       , "WAVE_ENEMY_FIRE_LASER_001");
    _pSeTx->set(SE_HATCH_CLOSE, "WAVE_HATCH_CLOSE_001");
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
    //�o���ʒu
    static coord appearances_renge_Z = (MyShip::lim_zleft_ - MyShip::lim_zright_) * 3;
    static coord appearances_renge_Y = (MyShip::lim_top_ - MyShip::lim_bottom_) * 3;
    _X = GgafDxUniverse::_X_gone_right - 1000;
    _Y = RND(-(appearances_renge_Y/2) , +(appearances_renge_Y/2));
    _Z = RND(-(appearances_renge_Z/2) , +(appearances_renge_Z/2));

    _pProg->set(PROG_ENTRY);
}

void EnemyHesperia::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;
    switch (_pProg->get()) {
        case PROG_ENTRY: {
            if (_pProg->hasJustChanged()) {
                UTIL::activateEntryEffectOf(this);
                _pFader->setAlpha(0);
                _pFader->intoTargetAlphaLinerUntil(0.98, 20);
            }
            if (_pFader->isHaveingEffect()) {
                _pFader->behave();
            } else {
                setHitAble(true);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE: {
            if (_pProg->hasJustChanged()) {

            }
            if (_pProg->getFrameInProgress() == 100) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_HATCH_OPEN: {
            if (_pProg->hasJustChanged()) {
                _pSeTx->play3D(SE_HATCH_OPEN);
                _pMorpher->intoTargetLinerUntil(1, 1.0, 120);
            }
            if (_pProg->getFrameInProgress() == 120) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            if (_pProg->hasJustChanged()) {
                //���[�U�[�Z�b�g�i���[�U�[�`�b�v�̃f�|�W�g���ŁA�P�{���̃��[�U�[�j�̃f�|�W�g������A
                //���[�U�[�Z�b�g�̎ؓ������݂�
                now_laser_way_ = RR_EnemyHesperia_ShotWay(_RANK_); //���񔭎˃��[�U�[�{��
                coord laser_density = RR_EnemyHesperia_Density(_RANK_); //���񃌁[�U�[�ƃ��[�U�[�̌���
                bool can_fire = false; //���Ȃ��Ƃ���{�͔��˂ł��邩�ǂ���

                for (int i = 0; i < max_laser_way_; i++) {
                    if (now_laser_way_ > i) {
                        LaserChipDepository* pLaserChipDepo = (LaserChipDepository*)(pLaserChipDepoStore_->dispatch());
                        if (pLaserChipDepo) {
                            //���[�U�[�Z�b�g�i���[�U�[�`�b�v�̃f�|�W�g���j���؂����o�����B
                            papLaserChipDepo_[i] = pLaserChipDepo;
                            papLaserChipDepo_[i]->config(laser_length_, 1);
                            can_fire = true;
                        } else {
                            //���[�U�[�Z�b�g�i���[�U�[�`�b�v�̃f�|�W�g���j���؂����o���Ȃ������B
                            papLaserChipDepo_[i] = nullptr;
                        }
                    } else {
                        papLaserChipDepo_[i] = nullptr;
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
                    //               (e)  |    (f)
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
                    coord total_laser_effect = laser_density*(now_laser_way_-1)+1; //�����ꃌ�[�U�[�̂����ꋗ���i�͈́j

                    dX_ = ABS(_X - pMyShip->_X);
                    dZ_ = ABS(_Z - pMyShip->_Z);
                    if (dX_ < dZ_)  {
                        //(a)(d) �̏ꍇ�AX�����������Z��������������
                        for (int i = 0, tX = -total_laser_effect/2; i < now_laser_way_; i++, tX+=laser_density) {
                            paPos_Target_[i].set(tX, 0, 0);
                        }
                    } else {
                        if (pMyShip->_X < _X) { //���@���O
                            //(b)(c)�̏ꍇ�AZ�����������X��������������
                            if (pMyShip->_Z < _Z) {
                                //(b)���@����O�A�w�X�y���A����
                                for (int i = 0, tZ = total_laser_effect/2; i < now_laser_way_; i++, tZ-=laser_density) {
                                    paPos_Target_[i].set(0, 0, tZ);
                                }
                            } else {
                                //(c)���@�����A�w�X�y���A����O
                                for (int i = 0, tZ = -total_laser_effect/2; i < now_laser_way_; i++, tZ+=laser_density) {
                                    paPos_Target_[i].set(0, 0, tZ);
                                }
                            }
                        } else { //���@����� (e)(f)
                            if (pMyShip->_Z < _Z) {
                                //(e)���@����O�A�w�X�y���A����
                                for (int i = 0, tZ = -total_laser_effect/2; i < now_laser_way_; i++, tZ+=laser_density) {
                                    paPos_Target_[i].set(0, 0, tZ);
                                }
                            } else {
                                //(f)���@�����A�w�X�y���A����O
                                for (int i = 0, tZ = total_laser_effect/2; i < now_laser_way_; i++, tZ-=laser_density) {
                                    paPos_Target_[i].set(0, 0, tZ);
                                }
                            }
                        }
                    }

                    _pSeTx->play3D(SE_FIRE); //���ˉ�
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
                //��turn_dY �� ������ EnemyHesperiaLaserChip001::turn_dY_�Ɠ�������鎖
                for (int i = 0; i < max_laser_way_; i++) {
                    if (papLaserChipDepo_[i]) {
                        pLaserChip = (EnemyHesperiaLaserChip001*)papLaserChipDepo_[i]->dispatch();
                        if (pLaserChip) {
                            p = &(paLocalPos_Laser_[i]);
                            //���ˌ����W�ɐݒ�
                            pLaserChip->locate(_X+p->_X, _Y+p->_Y, _Z+p->_Z);
                            //�ŏ��̖ڕW�n�_(�܂�Ԃ��n�_)��ݒ�
                            //�V���o�����b�N�t�߂�����邽�߂������Y���X
                            if (dX_ < dZ_)  {
                                //X�����������Z��������������
                                if (pMyShip->_Z < _Z) {
                                    //���@����O�A�w�X�y���A����
                                    pLaserChip->tX1_ = _X + paPos_Target_[i]._X;
                                    pLaserChip->tY1_ = _Y + paPos_Target_[i]._Y + turn_dY;
                                    pLaserChip->tZ1_ = _Z + paPos_Target_[i]._Z + PX_C(100);
                                } else {
                                    //���@�����A�w�X�y���A����O
                                    pLaserChip->tX1_ = _X + paPos_Target_[i]._X;
                                    pLaserChip->tY1_ = _Y + paPos_Target_[i]._Y + turn_dY;
                                    pLaserChip->tZ1_ = _Z + paPos_Target_[i]._Z - PX_C(100);
                                }
                            } else {
                                //�V���o�����b�N�t�߂�����邽��X-100
                                pLaserChip->tX1_ = _X + paPos_Target_[i]._X - PX_C(100);
                                pLaserChip->tY1_ = _Y + paPos_Target_[i]._Y + turn_dY;
                                pLaserChip->tZ1_ = _Z + paPos_Target_[i]._Z;
                            }

                            pLaserChip->turn_dY_ = turn_dY;
                            //�ŏI�ڕW�n�_��ݒ�
                            pLaserChip->tX2_ = pMyShip->_X + paPos_Target_[i]._X;
                            pLaserChip->tY2_ = pMyShip->_Y + paPos_Target_[i]._Y;
                            pLaserChip->tZ2_ = pMyShip->_Z + paPos_Target_[i]._Z;
                            //�����Ɖ����x
                            pLaserChip->_pKurokoA->setMvVelo(10000); //�������x
                            pLaserChip->_pKurokoA->setMvAcce(150+(max_laser_way_-i)*10); //�����o������悤��
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
            if (_pProg->hasJustChanged()) {
                _pSeTx->play3D(SE_HATCH_CLOSE);
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
    _pKurokoA->behave();
    _pMorpher->behave();
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
        _pSeTx->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        _pSeTx->play3D(SE_DAMAGED);
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
    //          �^��=5��      |
    //    ---���@-------------+--------->
    //      �^:               |
    //    �^  :               |
    //  �^    :<------------->|
    //        :     DT(����)  |
    //
    //DY = DT�Etan(5��) - (�G_Y - ���@_Y)
    static double tan5 = tan(5*(PI/180.0)); //�T�x�ォ��ł����낷
    coord dY = pThis->_Y - pMyShip->_Y;
    coord TurnDY = DT*tan5 - dY;
    if (TurnDY < PX_C(100)) {
        return PX_C(100);
    } else {
        return TurnDY;
    }
}

EnemyHesperia::~EnemyHesperia() {
    pConn_LaserChipDepoStore_->close();
    DELETEARR_IMPOSSIBLE_NULL(paLocalPos_Laser_);
    DELETEARR_IMPOSSIBLE_NULL(paPos_Target_);
    DELETEARR_IMPOSSIBLE_NULL(papLaserChipDepo_);
}
