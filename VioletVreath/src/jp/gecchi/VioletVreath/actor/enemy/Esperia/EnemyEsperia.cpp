#include "EnemyEsperia.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Esperia/EnemyEsperiaLaserChip001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

int EnemyEsperia::max_laser_way_ = RF_EnemyEsperia_ShotWay(1.0);
//RF_EnemyEsperia_ShotWay�����N���� 1.0�ōő�����悤�ɂ��Ȃ���΂Ȃ�Ȃ�

EnemyEsperia::EnemyEsperia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Esperia", STATUS(EnemyEsperia)) {
    pAFader_ = NEW GgafDxAlphaFader(this);
    cnt_laserchip_ = 0;
    laser_length_ = 40;
    now_laser_way_ = 0;
    //�؂���ꃌ�[�U�[�Z�b�g�̃f�|�W�g���ێ��p
    papLaserChipDepo_ = NEW LaserChipDepository*[max_laser_way_];
    for (int i = 0; i < max_laser_way_; i++) {
        papLaserChipDepo_[i] = nullptr;
    }

    pConn_pDepoStore_laser_set = connectToDepositoryManager("EnemyEsperiaLaserChip001DepoStore");
    pDepoStore_laser_set = (GgafActorDepositoryStore*)(pConn_pDepoStore_laser_set->peek());

    paLocalPos_laser_ = NEW GgafDxGeoElem[max_laser_way_];
    paPos_target_ = NEW GgafDxGeoElem[max_laser_way_];
    coord dX = PX_C(10); //���[�U�[���ˌ��̊Ԋu
    for (int i = 0; i < max_laser_way_; i++) {
        paLocalPos_laser_[i].set(PX_C(-40) + (i*dX),  PX_C(10), 0); //���[�U�[���ˌ��̃��[�J�����W
    }

    GgafDxSeTransmitterForActor* pSetx = getSeTransmitter();
    pSetx->set(SE_EXPLOSION  , "WAVE_EXPLOSION_MIDDLE_001");
    pSetx->set(SE_DAMAGED    , "WAVE_ENEMY_DAMAGED_001");
    pSetx->set(SE_HATCH_OPEN , "WAVE_HATCH_OPEN_001");
    pSetx->set(SE_FIRE       , "WAVE_ENEMY_FIRE_LASER_001");
    pSetx->set(SE_HATCH_CLOSE, "WAVE_HATCH_CLOSE_001");
    dX_= dZ_ = 0;
    useProgress(PROG_BANPEI);
}

void EnemyEsperia::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(1.0, 0.97);
    pModel->getTexBlinker()->setRange(0.5, 12.0);
    pModel->getTexBlinker()->beat(60*6, 60*2, 0, 60*2, -1);
}

void EnemyEsperia::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(200));
}

void EnemyEsperia::onActive() {
    getStatus()->reset();
    setHitAble(false);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setRzRyMvAng(0, D180ANG);
    pKuroko->setMvVelo(1000);

    dX_= dZ_ = 0;
    //�o���ʒu
    const coord appearances_renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 3;
    const coord appearances_renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 3;
    Spacetime* pSpacetime =  P_GOD->getSpacetime();
    _x = pSpacetime->_x_bound_right - 1000;
    _y = RND(-(appearances_renge_y/2) , +(appearances_renge_y/2));
    _z = RND(-(appearances_renge_z/2) , +(appearances_renge_z/2));


   // setPositionAroundAt(P_MYSHIP, PX_C(400));


    getProgress()->reset(PROG_INIT);
}

void EnemyEsperia::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pProg->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                pAFader_->transitionLinerUntil(0.999, frame_of_entering);
            }
            if (pProg->hasArrivedAt(frame_of_entering)) {
                setHitAble(true);
                pProg->changeNext();
            }
            pAFader_->behave();
            break;
        }
        case PROG_MOVE: {
            if (pProg->hasJustChanged()) {

            }
            if (pProg->hasArrivedAt(100)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_HATCH_OPEN: {
            if (pProg->hasJustChanged()) {
                getSeTransmitter()->play3D(SE_HATCH_OPEN);
                getMorpher()->transitionLinerUntil(1, 1.0, 120);
            }
            if (pProg->hasArrivedAt(120)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            if (pProg->hasJustChanged()) {
                //���[�U�[�Z�b�g�i���[�U�[�`�b�v�̃f�|�W�g���ŁA�P�{���̃��[�U�[�j�̃f�|�W�g������A
                //���[�U�[�Z�b�g�̎ؓ������݂�
                now_laser_way_ = RF_EnemyEsperia_ShotWay(G_RANK); //���񔭎˃��[�U�[�{��
                coord laser_density = RF_EnemyEsperia_Density(G_RANK); //���񃌁[�U�[�ƃ��[�U�[�̌���
                bool can_fire = false; //���Ȃ��Ƃ���{�͔��˂ł��邩�ǂ���

                for (int i = 0; i < max_laser_way_; i++) {
                    if (now_laser_way_ > i) {
                        LaserChipDepository* pLaserChipDepo = (LaserChipDepository*)(pDepoStore_laser_set->dispatch());
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

                    dX_ = ABS(_x - pMyShip->_x);
                    dZ_ = ABS(_z - pMyShip->_z);
                    if (dX_ < dZ_)  {
                        //(a)(d) �̏ꍇ�AX�����������Z��������������
                        for (int i = 0, tX = -total_laser_effect/2; i < now_laser_way_; i++, tX+=laser_density) {
                            paPos_target_[i].set(tX, 0, 0);
                        }
                    } else {
                        if (pMyShip->_x < _x) { //���@���O
                            //(b)(c)�̏ꍇ�AZ�����������X��������������
                            if (pMyShip->_z < _z) {
                                //(b)���@����O�A�G�X�y���A����
                                for (int i = 0, tZ = total_laser_effect/2; i < now_laser_way_; i++, tZ-=laser_density) {
                                    paPos_target_[i].set(0, 0, tZ);
                                }
                            } else {
                                //(c)���@�����A�G�X�y���A����O
                                for (int i = 0, tZ = -total_laser_effect/2; i < now_laser_way_; i++, tZ+=laser_density) {
                                    paPos_target_[i].set(0, 0, tZ);
                                }
                            }
                        } else { //���@����� (e)(f)
                            if (pMyShip->_z < _z) {
                                //(e)���@����O�A�G�X�y���A����
                                for (int i = 0, tZ = -total_laser_effect/2; i < now_laser_way_; i++, tZ+=laser_density) {
                                    paPos_target_[i].set(0, 0, tZ);
                                }
                            } else {
                                //(f)���@�����A�G�X�y���A����O
                                for (int i = 0, tZ = total_laser_effect/2; i < now_laser_way_; i++, tZ-=laser_density) {
                                    paPos_target_[i].set(0, 0, tZ);
                                }
                            }
                        }
                    }

                    getSeTransmitter()->play3D(SE_FIRE); //���ˉ�
                    effectFlush(2); //�t���b�V��
                    cnt_laserchip_ = 0;
                }
            }

            //laser_length_�ȓ��̊ԁA���[�U�[�`�b�v��dispatch()�����ݑ�����
            if (cnt_laserchip_ < laser_length_) {
                cnt_laserchip_++;
                EnemyEsperiaLaserChip001* pLaserChip;
                GgafDxGeoElem* p;
                coord turn_dy = getTurnDY(this, pMyShip, (dX_ > dZ_ ? dX_ : dZ_) );
                //��turn_dy �� ������ EnemyEsperiaLaserChip001::turn_dy_�Ɠ�������鎖
                for (int i = 0; i < max_laser_way_; i++) {
                    if (papLaserChipDepo_[i]) {
                        pLaserChip = (EnemyEsperiaLaserChip001*)papLaserChipDepo_[i]->dispatch();
                        if (pLaserChip) {
                            p = &(paLocalPos_laser_[i]);
                            //���ˌ����W�ɐݒ�
                            pLaserChip->setPosition(_x+p->x, _y+p->y, _z+p->z);
                            //�ŏ��̖ڕW�n�_(�܂�Ԃ��n�_)��ݒ�
                            //�V���o�����b�N�t�߂�����邽�߂������Y���X
                            if (dX_ < dZ_)  {
                                //X�����������Z��������������
                                if (pMyShip->_z < _z) {
                                    //���@����O�A�G�X�y���A����
                                    pLaserChip->tx1_ = _x + paPos_target_[i].x;
                                    pLaserChip->ty1_ = _y + paPos_target_[i].y + turn_dy;
                                    pLaserChip->tz1_ = _z + paPos_target_[i].z + PX_C(100);
                                } else {
                                    //���@�����A�G�X�y���A����O
                                    pLaserChip->tx1_ = _x + paPos_target_[i].x;
                                    pLaserChip->ty1_ = _y + paPos_target_[i].y + turn_dy;
                                    pLaserChip->tz1_ = _z + paPos_target_[i].z - PX_C(100);
                                }
                            } else {
                                //�V���o�����b�N�t�߂�����邽��X-100
                                pLaserChip->tx1_ = _x + paPos_target_[i].x - PX_C(100);
                                pLaserChip->ty1_ = _y + paPos_target_[i].y + turn_dy;
                                pLaserChip->tz1_ = _z + paPos_target_[i].z;
                            }

                            pLaserChip->turn_dy_ = turn_dy;
                            //�ŏI�ڕW�n�_��ݒ�
                            pLaserChip->tx2_ = pMyShip->_x + paPos_target_[i].x;
                            pLaserChip->ty2_ = pMyShip->_y + paPos_target_[i].y;
                            pLaserChip->tz2_ = pMyShip->_z + paPos_target_[i].z;
                            //�����Ɖ����x
                            pLaserChip->getKuroko()->setMvVelo(10000); //�������x
                            pLaserChip->getKuroko()->setMvAcce(150+(max_laser_way_-i)*20); //�����o������悤��
                        }
                    }
                }
            } else {
                //���[�U�[��ł��؂���
                pProg->changeNext();
            }
            break;
        }

        case PROG_HATCH_CLOSE: {
            if (pProg->hasJustChanged()) {
                getSeTransmitter()->play3D(SE_HATCH_CLOSE);
                getMorpher()->transitionLinerUntil(1, 0.0, 120);
            }
            if (pProg->hasArrivedAt(120)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_NOTHING: {
            if (pProg->hasArrivedAt(600)) {
                pProg->change(PROG_MOVE);
            }
            break;
        }
    }
    pKuroko->behave();
    getMorpher()->behave();
}

void EnemyEsperia::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEsperia::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyEsperia::onInactive() {
    //���[�U�[�f�|�W�g���͒x��Ă���߂�
    for (int i = 0; i < max_laser_way_; i++) {
        if (papLaserChipDepo_[i]) {
            papLaserChipDepo_[i]->sayonara(60*10);
        }
    }
    sayonara();
}

coord EnemyEsperia::getTurnDY(GgafDxCore::GgafDxGeometricActor* pThis,
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
    //DY = DT�Etan(5��) - (�G_y - ���@_y)
    static const double TAN5 = tan(5*(PI/180.0)); //�T�x�ォ��ł����낷
    coord dY = pThis->_y - pMyShip->_y;
    coord TurnDY = DT*TAN5 - dY;
    if (TurnDY < PX_C(100)) {
        return PX_C(100);
    } else {
        return TurnDY;
    }
}

EnemyEsperia::~EnemyEsperia() {
    GGAF_DELETE(pAFader_);
    pConn_pDepoStore_laser_set->close();
    GGAF_DELETEARR(paLocalPos_laser_);
    GGAF_DELETEARR(paPos_target_);
    GGAF_DELETEARR(papLaserChipDepo_);
}
