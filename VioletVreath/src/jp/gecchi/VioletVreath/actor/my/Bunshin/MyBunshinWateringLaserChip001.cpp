#include "MyBunshinWateringLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/LinkedListRing.hpp"
#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/GeoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/LockonCursor001_Main.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"

using namespace GgafLib;
using namespace VioletVreath;

const velo MyBunshinWateringLaserChip001::MAX_VELO_RENGE = PX_C(512); //���̒l��傫������ƁA�ō����x�������Ȃ�B
const double MyBunshinWateringLaserChip001::INV_MAX_VELO_RENGE = 1.0 / MAX_VELO_RENGE;
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 15; //���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�
const velo MyBunshinWateringLaserChip001::INITIAL_VELO = MAX_VELO_RENGE*0.5; //���[�U�[���ˎ��̏������x
const double MyBunshinWateringLaserChip001::RR_MAX_ACCE = 1.0 / R_MAX_ACCE; //�v�Z�ȑf���p
const float MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO_RENGE/R_MAX_ACCE;
const velo MyBunshinWateringLaserChip001::MIN_VELO_ = MyBunshinWateringLaserChip001::INITIAL_VELO/10; // ��10 �́A�Œ�ړ�����e����INITIAL_VELO�̊���
GgafDx::Model* MyBunshinWateringLaserChip001::pModel_ = nullptr;
int MyBunshinWateringLaserChip001::tex_no_ = 0;


MyBunshinWateringLaserChip001::MyBunshinWateringLaserChip001(const char* prm_name) :
        VvMyActor<WateringLaserChip>(prm_name, "MyLaserChip001", StatusReset(MyBunshinWateringLaserChip001)) {
    _class_name = "MyBunshinWateringLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    pOrg_ = nullptr;
    pLockonCursor_ = nullptr;
    is_lockon_ = false;
    GgafDx::Model* pModel = getModel();
    if (!MyBunshinWateringLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwCriticalException("MyBunshinWateringLaserChip001���f���́A�e�N�X�`���i�}�e���A���j��"<<MAX_LASER_LEVEL<<"�K�v�ł��B");
        }
        MyBunshinWateringLaserChip001::pModel_ = pModel;
    }
    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
    sgn_vx0_ = 0;
    sgn_vy0_ = 0;
    sgn_vz0_ = 0;
    pAimInfo_ = nullptr;
    inv_cnt_ = 0;
}

void MyBunshinWateringLaserChip001::initialize() {
    getVecVehicle()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(PX_C(80));
    setHitAble(true);
    setScaleR(6.0);
    setCullingDraw(false);

}

void MyBunshinWateringLaserChip001::onCreateModel() {

}

void MyBunshinWateringLaserChip001::setOrg(MyBunshin* prm_pOrg) {
    pOrg_ = prm_pOrg;
    pLockonCursor_ = pOrg_->pLockonCtrler_->pMainLockonEffect_;
}

void MyBunshinWateringLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    WateringLaserChip::onActive();
    pAimInfo_ = nullptr;
    inv_cnt_ = 0;
    sgn_vx0_ = 0;
    sgn_vy0_ = 0;
    sgn_vz0_ = 0;
    GgafDx::GeoVehicle* pGeoVehicle = getGeoVehicle();
    pGeoVehicle->forceVeloRange(MIN_VELO_, MAX_VELO_RENGE);
    pGeoVehicle->forceAcceRange(0, MAX_ACCE_RENGE);
}

void MyBunshinWateringLaserChip001::processBehavior() {
    frame active_frame = getActiveFrame();
    double power = active_frame <= 300 ? UTIL::SHOT_POWER[active_frame] : UTIL::SHOT_POWER[300];
    getStatus()->set(STAT_AttackPowerRate, power);
    _power = power;

    GgafDx::GeoVehicle* const pGeoVehicle = getGeoVehicle();

//    if (strcmp(getName(), "Bunshin4's LaserChip(75)") == 0 && _frame_of_life > 4413) {
//        _TRACE_("�Ȃ�ł�1 "<<pGeoVehicle->_velo_x<<","<<pGeoVehicle->_velo_y<<","<<pGeoVehicle->_velo_z);
//    }

    MyBunshin::AimInfo* pAimInfo = pAimInfo_;

    if (active_frame >= 60*20) {
        sayonara(); //�ی��̃^�C���A�E�g20�b
    } else if (pAimInfo == nullptr || active_frame < 7) {
        //�Ȃɂ����Ȃ�
    } else {
        GgafDx::GeometricActor* pAimTarget = pAimInfo->pTarget;
        if (pAimTarget) {
            frame aim_time_out_t1 = pAimInfo->aim_time_out_t1;
            //��[�`�b�v���i������\���̂���LeaderChip�ɂ��炸�I�j�AT1�����ς�炸���b�N�I���^�[�Q�b�g�Ȃ�΍X�V
            if (getInfrontChip() == nullptr && pAimTarget == pLockonCursor_->pTarget_ && pAimInfo->spent_frames_to_t1 < aim_time_out_t1) {
                pAimInfo->t1_x = pAimTarget->_x; //t1�X�V
                pAimInfo->t1_y = pAimTarget->_y;
                pAimInfo->t1_z = pAimTarget->_z;
            }

            MyBunshinWateringLaserChip001* pAimLeaderChip = pAimInfo->pLeaderChip;
            if (this == pAimLeaderChip) {
                if (pAimInfo->spent_frames_to_t1 == 0) {
                    //��Leader �� t1 �� Aim
                    if (pAimTarget->isActiveInTheTree() && active_frame < aim_time_out_t1)  {
                        //pAimTarget ������
                        int vx1 = pGeoVehicle->_velo_x;
                        int vy1 = pGeoVehicle->_velo_y;
                        int vz1 = pGeoVehicle->_velo_z;

                        aimChip(pAimInfo->t1_x,
                                pAimInfo->t1_y,
                                pAimInfo->t1_z );

                        int vx2 = pGeoVehicle->_velo_x;
                        int vy2 = pGeoVehicle->_velo_y;
                        int vz2 = pGeoVehicle->_velo_z;

                        int sgn_vx = SGN(vx1 - vx2);
                        int sgn_vy = SGN(vy1 - vy2);
                        int sgn_vz = SGN(vz1 - vz2);

                        if (sgn_vy0_ != sgn_vy) {
                            inv_cnt_++;
                            sgn_vy0_ = sgn_vy;
                        } else if (sgn_vz0_ != sgn_vz) {
                            inv_cnt_++;
                            sgn_vz0_ = sgn_vz;
                        } else if (sgn_vx0_ != sgn_vx) {
                            inv_cnt_++;
                            sgn_vx0_ = sgn_vx;
                        }
                        if (inv_cnt_ > 10) { //10������x�̐���������ւ������I��
                            pAimInfo_->spent_frames_to_t1 = active_frame; //Aim t1 �I��
                        } else {
                            static const coord renge = MyBunshinWateringLaserChip001::INITIAL_VELO;
                            static const ucoord renge2 = renge*2;
                            if ( (ucoord)(_x - pAimInfo->t1_x + renge) <= renge2) {
                                if ( (ucoord)(_y - pAimInfo->t1_y + renge) <= renge2) {
                                    if ( (ucoord)(_z - pAimInfo->t1_z + renge) <= renge2) {
                                        pAimInfo_->spent_frames_to_t1 = active_frame; //Aim t1 �I��
                                    }
                                }
                            }
                        }

                    } else {
                        //���߂� pAimTarget ���������̂ɁA�r���ŏ������B
                        pAimInfo_->spent_frames_to_t1 = active_frame; //Aim t1 �I��
                    }
                } else if (pAimInfo->spent_frames_to_t2 == 0) {
                    //��Leader �� t1 �� Aim ���I���������
                    //t2�����߂�
                    static const Spacetime* pSpaceTime =  pGOD->getSpacetime();
                    static const double zf_r = UTIL::getDistance(
                                                      0.0, 0.0, 0.0,
                                                      (double)(pSpaceTime->_x_bound_right),
                                                      (double)(pSpaceTime->_y_bound_top),
                                                      (double)(pSpaceTime->_z_bound_far)
                                                     ) * 1.2;
                    LaserChip* pB = getBehindChip();
                    if (pB) {
                        pB = pB->getBehindChip();
                        if (pB) {
                            pB = pB->getBehindChip();
                        }
                    }
                    if (pB) {
                        pAimInfo->setT2(zf_r, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                    } else {
                        pAimInfo->setT2(zf_r, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                    }
                    coord t2_d = UTIL::getDistance(_x, _y, _z,
                                                   pAimInfo->t2_x,
                                                   pAimInfo->t2_y,
                                                   pAimInfo->t2_z);
                    pAimInfo->spent_frames_to_t2 = active_frame + (frame)(t2_d*MyBunshinWateringLaserChip001::INV_MAX_VELO_RENGE); //t2���B���ԊT�Z
                    aimChip(pAimInfo->t2_x,
                            pAimInfo->t2_y,
                            pAimInfo->t2_z );
                } else {
                    //��Leader �� t2 ��ݒ肵�����ƁB
                    if (active_frame < pAimInfo->spent_frames_to_t2)  {
                        aimChip(pAimInfo->t2_x,
                                pAimInfo->t2_y,
                                pAimInfo->t2_z );
                    } else {
                        aimChip(_x + pGeoVehicle->_velo_x*4+1,
                                _y + pGeoVehicle->_velo_y*4+1,
                                _z + pGeoVehicle->_velo_z*4+1 );
                    }
                }
            } else {
//                MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
//                if (pF) {
//                    pF = (MyBunshinWateringLaserChip001*)pF->getInfrontChip();
//                    if (pF) {
//                        pF = (MyBunshinWateringLaserChip001*)pF->getInfrontChip();
//                        if (pF) {
//                            pF = (MyBunshinWateringLaserChip001*)pF->getInfrontChip();
//                        }
//                    }
//                }
//                if (pF) {
//                    aimChip(pF->_x,
//                            pF->_y,
//                            pF->_z );
//                } else {
//                }
                //��Leader�ȊO
                if (pAimInfo->spent_frames_to_t1 == 0) {
                    //��Leader�ȊO�� t1 ����܂�܂ł̓���
                    if (pAimLeaderChip) {
                        aimChip(pAimLeaderChip->_x,
                                pAimLeaderChip->_y,
                                pAimLeaderChip->_z );
                    } else {
                        aimChip(pAimInfo->t1_x,
                                pAimInfo->t1_y,
                                pAimInfo->t1_z );
                    }
                } else if (active_frame <= pAimInfo->spent_frames_to_t1) {
                    //��Leader�ȊO�� t1 ����܂��Ă��� t1 ���B�܂ł̓���
                    aimChip(pAimInfo->t1_x,
                            pAimInfo->t1_y,
                            pAimInfo->t1_z );
                } else if (active_frame > pAimInfo->spent_frames_to_t1) {
                    //��Leader�ȊO�� t1 ��ʉ�
                    if (pAimInfo->spent_frames_to_t2 == 0) {
                        //�����̌� Leader�ȊO�� t2 ����܂�܂ł̓���
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pGeoVehicle->_velo_x*4+1,
                                    _y + pGeoVehicle->_velo_y*4+1,
                                    _z + pGeoVehicle->_velo_z*4+1 );
                        }
                    } else if (active_frame <= pAimInfo->spent_frames_to_t2) {
                        //�����̌� Leader�ȊO�� t2 ����܂��āAt2�Ɍ������܂ł̓���
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(pAimInfo->t2_x,
                                    pAimInfo->t2_y,
                                    pAimInfo->t2_z );
                        }
                    } else if (active_frame > pAimInfo->spent_frames_to_t2) {
                        //�����̌� Leader�ȊO�� t2 ��ʉ߂�����̓���
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pGeoVehicle->_velo_x*4+1,
                                    _y + pGeoVehicle->_velo_y*4+1,
                                    _z + pGeoVehicle->_velo_z*4+1 );
                        }
                    } else {
                        _TRACE_("�y�x���z���肦�Ȃ�");
                    }
                }
            }

        } //if (pAimTarget)

    }


//    if (strcmp(getName(), "Bunshin4's LaserChip(75)") == 0 && _frame_of_life > 4413) {
//        _TRACE_("�Ȃ�ł�3 "<<pGeoVehicle->_velo_x<<","<<pGeoVehicle->_velo_y<<","<<pGeoVehicle->_velo_z);
//    }
//
//    if (strcmp(getName(), "Bunshin4's LaserChip(75)") == 0 && _frame_of_life == 4416) {
//        _TRACE_("������3 "<<pGeoVehicle->_velo_x<<","<<pGeoVehicle->_velo_y<<","<<pGeoVehicle->_velo_z);
//    }


    pGeoVehicle->behave();

//    if (strcmp(getName(), "Bunshin4's LaserChip(75)") == 0 && _frame_of_life > 4413) {
////    	&& pGeoVehicle->_velo_x == 0 && pGeoVehicle->_velo_y == 0 && pGeoVehicle->_velo_z == 0) {
//        _TRACE_("�Ȃ�ł�4 "<<pGeoVehicle->_velo_x<<","<<pGeoVehicle->_velo_y<<","<<pGeoVehicle->_velo_z);
//    }
    WateringLaserChip::processBehavior();

    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
}

void MyBunshinWateringLaserChip001::processSettlementBehavior() {
    //���g��FK�Ȃ̂ŁA��΍��W�̊m�肪 processSettlementBehavior() �ȍ~�ƂȂ邽�߁A�����ŏ����ݒ肪�K�v
    GgafDx::GeoVehicle* const pGeoVehicle = getGeoVehicle();

//    if (strcmp(getName(), "Bunshin4's LaserChip(75)") == 0 && _frame_of_life > 4413) {
//        _TRACE_("�Ȃ�ł�5 "<<pGeoVehicle->_velo_x<<","<<pGeoVehicle->_velo_y<<","<<pGeoVehicle->_velo_z);
//    }

    if (hasJustChangedToActive()) {
        //�`�b�v�̏����ݒ�
        //���b�N�I�����̈����p��
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getInfrontChip();
        if (pF == nullptr) {
            //��[�`�b�v
            GgafDx::GeometricActor* pLockonTarget = pLockonCursor_->pTarget_;
            if (pLockonTarget && pLockonTarget->isActiveInTheTree()) {
                //��[�Ń��b�N�I����
                pAimInfo_ = pOrg_->getAimInfo();
                pAimInfo_->pLeaderChip = this;
                pAimInfo_->pTarget = pLockonTarget;
                pAimInfo_->t1_x = pAimInfo_->pTarget->_x;
                pAimInfo_->t1_y = pAimInfo_->pTarget->_y;
                pAimInfo_->t1_z = pAimInfo_->pTarget->_z;
                // aim_time_out_t1 ���T�Z�ŋ��߂Ă���
                coord t1_d = UTIL::getDistance(this, pLockonTarget);
                pAimInfo_->aim_time_out_t1 = (t1_d / MyBunshinWateringLaserChip001::INITIAL_VELO)*1.2;
            } else {
                //��[�Ń��b�N�I�����Ă��Ȃ�
                pAimInfo_ = pOrg_->getAimInfo();
                pAimInfo_->pLeaderChip = this;
                pAimInfo_->pTarget = nullptr;
            }
            pGeoVehicle->forceVeloRange(MIN_VELO_, MAX_VELO_RENGE);
        } else {
            //��[�ȊO�͑O�̂��󂯌p��
            pAimInfo_ = pF->pAimInfo_; //�󂯌p��

            pGeoVehicle->forceVeloRange(MIN_VELO_, MAX_VELO_RENGE);

//            velo v = MAX_VELO_RENGE - PX_C(1); //���[�U�[���o�܂Ȃ��悤�� PX_C(1) �x������
//            pGeoVehicle->forceVeloRange(MIN_VELO_, v);
#ifdef MY_DEBUG
if (pAimInfo_ == nullptr) {
throwCriticalException("pAimInfo_ �������p����Ă��܂���I"<<this<<
                       " _frame_of_life_when_activation="<<_frame_of_life_when_activation);
}
#endif
        }
        //�����J�n����t���[���A�`�b�v�̑��x�ƌ����̏����ݒ�
        setFaceAngAs(pOrg_);
        setPositionAt(pOrg_);
        pGeoVehicle->setVeloTwd(_rz, _ry, INITIAL_VELO); //�����͂�����
        pGeoVehicle->setAcceZero();
    }

    //���ϋȐ����W�ݒ�B(���[�U�[�����炩�ɂ���m�[�}���C�Y�j
    //processSettlementBehavior() �̃��\�b�h�̈Ӌ`�Ƃ͗���č��W��������ړ����Ă���B
    //�{���� processBehaviorAfter() �I�ȈӖ��̏����ł��邪�A�S���[�U�[�`�b�v���ړ���łȂ��ƈӖ����Ȃ��̂�
    //�d���Ȃ��̂�processSettlementBehavior()�ɐH������ł��܂��B
    //���������Ė{�N���X���p�������ꍇ�A�p���N���X��processSettlementBehavior()�ł́A�擪�ŌĂяo���������ǂ��B
    if (getActiveFrame() > 3) {//FK�I�u�W�F�N�g����̃��[�U�[���˂��l������ƁA_tmpXYZ �����܂�̂�3�t���[���ȍ~�B
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
        if (pF && pF->isActive()) {
            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB && pB->isActive()) {
                //_pChip_behind == nullptr �̔��肾���ł͂��߁B_pChip_behind->_is_active_flg �Ɣ��肷�邱��
                //�Ȃ��Ȃ� dispatch �̏u�Ԃ�_pChip_behind != nullptr �ƂȂ邪�Aactive()�ɂ��L���ɂȂ�͎̂��t���[��������
                //_x,_y,_z �ɂ͂܂��ςȒl�������Ă���B
                //���ԍ��W�ɍĐݒ�
                //���W�̏d�݂́A�i�ЂƂO, ���g, ���j�� (0.2, 0.5, 0.3)
                if (pAimInfo_->pTarget) {
                    _x = tmp_x_ + (coord)((pB->tmp_x_-tmp_x_)*0.1 + (pF->tmp_x_-tmp_x_)*0.4);
                    _y = tmp_y_ + (coord)((pB->tmp_y_-tmp_y_)*0.1 + (pF->tmp_y_-tmp_y_)*0.4);
                    _z = tmp_z_ + (coord)((pB->tmp_z_-tmp_z_)*0.1 + (pF->tmp_z_-tmp_z_)*0.4);
                } else {
                    _x = tmp_x_ + (coord)((pB->tmp_x_-tmp_x_)*0.1 + (pF->tmp_x_-tmp_x_)*0.1);
                    _y = tmp_y_ + (coord)((pB->tmp_y_-tmp_y_)*0.1 + (pF->tmp_y_-tmp_y_)*0.1);
                    _z = tmp_z_ + (coord)((pB->tmp_z_-tmp_z_)*0.1 + (pF->tmp_z_-tmp_z_)*0.1);
                }
            } else {
                if (pAimInfo_->pTarget) {
                    //�␳��̈�O�̍��W�ƁA���g�̍��W�𒼐��Ō���ŁA���z�̎����̌��̓_���쐬�B
                    //�␳�O�̈�O�̍��W�A���g�̍��W�A���z�̎����̌��̓_�ŕ��ς����
                    coord v_b_x = _x - (pF->_x - _x);
                    coord v_b_y = _y - (pF->_y - _y);
                    coord v_b_z = _z - (pF->_z - _z);
                    _x = tmp_x_ + (coord)((v_b_x-tmp_x_)*0.2 + (pF->tmp_x_-tmp_x_)*0.3);
                    _y = tmp_y_ + (coord)((v_b_y-tmp_y_)*0.2 + (pF->tmp_y_-tmp_y_)*0.3);
                    _z = tmp_z_ + (coord)((v_b_z-tmp_z_)*0.2 + (pF->tmp_z_-tmp_z_)*0.3);
                }

            }

//            //���[�U�[�`�b�v�̌�������O�̃`�b�v�ɐݒ�
//            setFaceAngTwd(pF);
        } else {
//            //���[�U�[�`�b�v�̌������ړ������ɐݒ�i��[�`�b�v�j
//            UTIL::convVectorToRzRy(pGeoVehicle->_velo_x,
//                                   pGeoVehicle->_velo_y,
//                                   pGeoVehicle->_velo_z,
//                                   _rz, _ry );
        }

//        if (strcmp(getName(), "Bunshin4's LaserChip(75)") == 0 && _frame_of_life > 4413) {
//            _TRACE_("�Ȃ�ł�6 "<<pGeoVehicle->_velo_x<<","<<pGeoVehicle->_velo_y<<","<<pGeoVehicle->_velo_z);
//        }
        UTIL::convVectorToRzRy(pGeoVehicle->_velo_x,
                               pGeoVehicle->_velo_y,
                               pGeoVehicle->_velo_z,
                               _rz, _ry );
    }
    WateringLaserChip::processSettlementBehavior();
}

void MyBunshinWateringLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        if (pAimInfo_->pLeaderChip == this) {
            pAimInfo_->t2_x = _x;
            pAimInfo_->t2_y = _y;
            pAimInfo_->t2_z = _z;
            pAimInfo_->spent_frames_to_t2 = getActiveFrame();
            if (pAimInfo_->spent_frames_to_t1 == 0) {
                pAimInfo_->t1_x = pAimInfo_->t2_x;
                pAimInfo_->t1_y = pAimInfo_->t2_y;
                pAimInfo_->t1_z = pAimInfo_->t2_z;
                pAimInfo_->spent_frames_to_t1 = getActiveFrame();
            }
        }
        sayonara();
    }
}
void MyBunshinWateringLaserChip001::aimChip(int tX, int tY, int tZ) {
    //    |                            vVT ���I                              |
    //    |                                ^ ��                              |
    //    |               |���I| > |����| /    �_  vVP ���������I            |      ���I
    //    |                 �ƂȂ�悤�� /       �_                          |       ��
    //    |                 vVT��ݒ�   /         ��                         |      ����
    //    |               (|����|*1.2) /        �^vVM  ����                  |       ��
    //    |                           /       �^ =(vMx*5,vMy*5,vMz*5)        |       �b
    //    |                          /      �^                               |       �b
    //    |                         /     �^                                 |       �b
    //    |                        /    �^ |����| = lVM * 5                  |       �b
    //    |                      �I vT(vTx,vTy,vTz)                          |       �I
    //    |             ��       ^  �^                                       |       ��
    //    |               �_    / ��vM ���݂̈ړ������x�N�g��                |       �b
    //    | vVP ���������I  �_ /�^ (vMx,vMy,vMz)                             |       �b
    //    |                   ��                                             |       ��
    //    |                     (_x,_y,_z)                                   |
    // ---+------------------------------------------                     ---+---------------------------
    //    |                                                                  |
    //
    // vVP ���������������BvVP�����߂�I
#ifdef MY_DEBUG
    if (tX == INT_MAX) {
        throwCriticalException("��������");
    }
#endif


    static const coord rv = 10.0;
    GgafDx::GeoVehicle* pGeoVehicle = getGeoVehicle();
    //�������A�������x�N�g��(vM)
    coord vMx = pGeoVehicle->_velo_x;
    coord vMy = pGeoVehicle->_velo_y;
    coord vMz = pGeoVehicle->_velo_z;
    //|vM|
//    double lvM = sqrt(vMx*vMx + vMy*vMy + vMz*vMz);
//    coord lvM = UTIL::getDistanceFromOrigin(vMx, vMy, vMz);

    coord lvM = pGeoVehicle->_velo;
    //|vM|�����܂�ɏ������ꍇ�����x���x������ꍇ���l��
//    if  (lvM < MIN_VELO_) { //�k���܂�Ȃ��悤��
//        if (ZEROd_EQ(lvM)) {
//            //���x���w�ǂO�ł����ǂ��������Ă邩�킩���̂ŁAX�������ɔ�΂�
//            pGeoVehicle->setVelo(MIN_VELO_, 0, 0);
//        } else {
//            //���x MIN_VELO_ ��ۏ؂���
//            double r = (1.0*MIN_VELO_/lvM);
//            pGeoVehicle->setVelo(vMx*r, vMy*r, vMz*r);
//        }
//        vMx = pGeoVehicle->_velo_x;
//        vMy = pGeoVehicle->_velo_y;
//        vMz = pGeoVehicle->_velo_z;
//        lvM = MIN_VELO_;
//    }
    coord vVMx = vMx * rv;
    coord vVMy = vMy * rv;
    coord vVMz = vMz * rv;
    coord lvVM = lvM * rv;


    //�����I�A�����x�N�g�� (vT)
    coord vTx = tX - _x;
    coord vTy = tY - _y;
    coord vTz = tZ - _z;
    //|vT|
//    double lvT = sqrt(vTx*vTx + vTy*vTy + vTz*vTz);
    coord lvT = UTIL::getDistanceFromOrigin(vTx, vTy, vTz);
    //|���I| �� lvVM �̒����ɍ��킹�č쐬
    double rMT = (lvVM * 1.2 / lvT) ;
    //1.2�͉E��}�̂悤�Ɉ꒼���ɕ��񂾍ۂ��A�i�s�������ێ����邽�߂ɁA
    //|����| < |���I| �Ƃ����֌W���ێ����邽�߂ɂ������K���Ȋ���
    coord vVTx = vTx * rMT;
    coord vVTy = vTy * rMT;
    coord vVTz = vTz * rMT;
    coord lvVT = lvT * rMT;
//    double cos_th = ((vMx*vTx + vMy*vTy + vMz*vTz) / (lvT * lvM)); //�Ȃ��p
//    if (cos_th < 0.5) {
//        cos_th = 0.5;
//    }
    //vVP ���������I �̉����x�ݒ�
    //��vVP=( vVTx-vVMx, vVTy-vVMy, vVTz-vVMz )
    const acce accX = (vVTx-vVMx) * RR_MAX_ACCE; // * cos_th;
    const acce accY = (vVTy-vVMy) * RR_MAX_ACCE; // * cos_th;
    const acce accZ = (vVTz-vVMz) * RR_MAX_ACCE; // * cos_th;
//    double top_acce_mv = pGeoVehicle->_top_acce_x*1.05; //������Ƃ��Ȃ�g�������傢��݂�����
//    if (MAX_VELO_RENGE < top_acce_mv && top_acce_mv < MAX_VELO_RENGE) {
//        pGeoVehicle->forceAcceXYZRange(-top_acce_mv, top_acce_mv);
//    }
    pGeoVehicle->setAcce(accX, accY, accZ);
}


void MyBunshinWateringLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*) prm_pOtherActor;
    //�q�b�g�G�t�F�N�g
    GgafDx::FigureActor* pE = UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g�o��
    GgafDx::CollisionPart* pColliPart = getCollisionChecker()->getLastHitCollisionPart();
    pE->setPosition(pE->_x + pColliPart->_cx, pE->_y + pColliPart->_cy, pE->_z + pColliPart->_cz); //�����G�t�F�N�g�ʒu��␳

    if ((pOther->lookUpKind() & KIND_ENEMY_BODY) ) {
        //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I��
        if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
            pOrg_->pLockonCtrler_->lockon(pOther);
        }

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //�ꌂ�Ń`�b�v���ł̍U����
            getStatus()->set(STAT_Stamina, default_stamina_);
//TODO:������ sayonara() �����ɁA���΂炭���z�̃z�[�~���O���[�U�[�O�Ղ���������I
            //sayonara();
        } else {
            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
            getStatus()->set(STAT_Stamina, default_stamina_);
        }
        MyBunshin::AimInfo* pAimInfo = pAimInfo_;
        if (this == pAimInfo->pLeaderChip && pAimInfo->pTarget == prm_pOtherActor) {
            //��[���ڕW�Ɍ������������ꍇ��T1�I��
            pAimInfo->t1_x = _x;
            pAimInfo->t1_y = _y;
            pAimInfo->t1_z = _z;
            pAimInfo->spent_frames_to_t1 = getActiveFrame();
        }

    } else if (pOther->lookUpKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::onInactive() {
    MyBunshin::AimInfo* pAimInfo = pAimInfo_;
    if (pAimInfo && pAimInfo->pLeaderChip == this) {
        if (pAimInfo->spent_frames_to_t2 == 0) {
            frame aim_time_out_t1 = pAimInfo_->aim_time_out_t1;
            static const Spacetime* pSpaceTime =  pGOD->getSpacetime();
            static const double zf_r = UTIL::getDistance(
                                               0.0, 0.0, 0.0,
                                               (double)(pSpaceTime->_x_bound_right),
                                               (double)(pSpaceTime->_y_bound_top),
                                               (double)(pSpaceTime->_z_bound_far)
                                             ) * 1.2;

            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB) {
                pAimInfo->setT2(zf_r, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                pAimInfo->spent_frames_to_t2 = getActiveFrame() + aim_time_out_t1;
            } else {
                pAimInfo->setT2(zf_r, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                pAimInfo->spent_frames_to_t2 = getActiveFrame() + aim_time_out_t1;
            }

            if (pAimInfo->spent_frames_to_t1 == 0) {
                pAimInfo->t1_x = pAimInfo->t2_x;
                pAimInfo->t1_y = pAimInfo->t2_y;
                pAimInfo->t1_z = pAimInfo->t2_z;
                pAimInfo->spent_frames_to_t1 = getActiveFrame() + aim_time_out_t1;
            }

        }
        pAimInfo->pLeaderChip = nullptr;
    }
    pOrg_ = nullptr;
    pLockonCursor_ = nullptr;
    pAimInfo_ = nullptr;

    WateringLaserChip::onInactive();
}

void MyBunshinWateringLaserChip001::chengeTex(int prm_tex_no) {
    if (MyBunshinWateringLaserChip001::pModel_) {
        MyBunshinWateringLaserChip001::tex_no_ = prm_tex_no;
        MyBunshinWateringLaserChip001::pModel_->setDefaultTextureMaterialNo(prm_tex_no);
    }
}

MyBunshinWateringLaserChip001::~MyBunshinWateringLaserChip001() {
    MyBunshinWateringLaserChip001::pModel_ = nullptr;
}

