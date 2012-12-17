#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VamSysCamWorker::VamSysCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "VamSysCamWorker";
    pMyShip_ = nullptr; //MyShipScene�ɐݒ肵�Ă��炤

    //�����J�����ړ��͈͐���
    float revise = 0.7; //�΂߂��猩��̂ŕ␳�l���|����B1.0�̏ꍇ�͌��_����Ńh���s�V���B����͔��������J��Ԃ���
    lim_CAM_top_     = MyShip::lim_top_     - (PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT))/2)*revise;
    lim_CAM_bottom_  = MyShip::lim_bottom_  + (PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT))/2)*revise;
    lim_CAM_front_   = MyShip::lim_front_   - (PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    lim_CAM_behaind_ = MyShip::lim_behaind_ + (PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    lim_CAM_zleft_   = MyShip::lim_zleft_   - (PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    lim_CAM_zright_  = MyShip::lim_zright_  + (PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;

    lim_VP_top_     = MyShip::lim_top_     - (PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT))/2)*revise;
    lim_VP_bottom_  = MyShip::lim_bottom_  + (PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT))/2)*revise;
    lim_VP_front_   = MyShip::lim_front_   - (PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    lim_VP_behaind_ = MyShip::lim_behaind_ + (PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    lim_VP_zleft_   = MyShip::lim_zleft_   - (PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    lim_VP_zright_  = MyShip::lim_zright_  + (PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    is_cam_pos_option_back_ = false;
}
void VamSysCamWorker::initialize() {
    GgafDxCamera* pCam = P_CAM;
    GgafDxGeometricActor* pVP = pCam->_pViewPoint;

    //�����J����Z�ʒu
    dZ_camera_init_ = -DX_C(pCam->_cameraZ_org);


    //��ʔw��p�͈͍���
    //�w���Z���W��dZ_camera_init_/2
    correction_width_ = 0;//(GGAF_PROPERTY(GAME_BUFFER_WIDTH)*LEN_UNIT/2)/4;
    correction_height_ = 0;//(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)*LEN_UNIT/2)/4;

    pos_camera_ = VAM_POS_RIGHT;

//    pCam->_X = 0;
//    pCam->_Y = 0;
//    pCam->_Z = 0;
//    pCam->setViewPoint(0,0,0);
//    pCam->_pKurokoB->setRzRyMvAngTwd(0,0,0);

    cam_velo_renge_ = 30000;
    pCam->_pKurokoB->forceVxMvVeloRange(-cam_velo_renge_, cam_velo_renge_);
    pCam->_pKurokoB->forceVyMvVeloRange(-cam_velo_renge_, cam_velo_renge_);
    pCam->_pKurokoB->forceVzMvVeloRange(-cam_velo_renge_, cam_velo_renge_);
    pVP->_pKurokoB->forceVxMvVeloRange(-cam_velo_renge_, cam_velo_renge_);
    pVP->_pKurokoB->forceVyMvVeloRange(-cam_velo_renge_, cam_velo_renge_);
    pVP->_pKurokoB->forceVzMvVeloRange(-cam_velo_renge_, cam_velo_renge_);

    stop_renge_ = 60000;
    angXY_nowCamUp_ = UTIL::getAngle2D(P_CAM->_pVecCamUp->x, P_CAM->_pVecCamUp->y);
    stop_dZ_ = 0;
    stop_dY_ = 0;
    _TRACE_("VamSysCamWorker::initialize() this="<<this);
    dump();
}

void VamSysCamWorker::processBehavior() {

    //DefaultVamSysCamWorker::processBehavior();

    //�Q�[�����J�������[�N����
    if (pMyShip_ == nullptr) {
        return; //MyShipScene�V�[���������Ȃ�J�������[�N�֎~
    }

    GgafDxCamera* pCam = P_CAM;
    GgafDxGeometricActor* pVP = pCam->_pViewPoint;
    MyOptionController* pOptCtrler = P_MYSHIP_SCENE->papOptionCtrler_[0];

    //�J�����ʒu�ԍ������菈��
    is_cam_pos_option_back_ = false;
    if (VB_PLAY->isBeingPressed(VB_OPTION)) { //�I�v�V�������쎞
        if (VB_PLAY->isBeingPressed(VB_VIEW)) {
            is_cam_pos_option_back_ = true;
        }
    } else if (VB_PLAY->isPushedDown(VB_VIEW)) { //�r���[�{�^���v�b�V��                              //�I�v�V�����񑀍쎞�i�ʏ펞�j
        _TRACE_("VB_VIEW!! now pos_camera_="<<pos_camera_);
        if (pos_camera_ < VAM_POS_TO_BEHIND) { //�w�ʃr���[�|�C���g�ł͂Ȃ��ꍇ�A
            pos_camera_ += VAM_POS_TO_BEHIND;  //���ꂼ��̑Ή��w�ʃr���[�|�C���g��
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {//�w�ʃr���[�|�C���g�̏ꍇ
            //�������͂ɂ��V���ȃr���[�|�C���g��
            if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                pos_camera_ = VAM_POS_LEFT;
            } else if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                pos_camera_ = VAM_POS_RIGHT;
            } else if (VB_PLAY->isBeingPressed(VB_UP)) {
                pos_camera_ = VAM_POS_BOTTOM;
            } else if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                pos_camera_ = VAM_POS_TOP;
            } else {
                //���������͂̏ꍇ�A���̃r���[�|�C���g��
                pos_camera_ -= VAM_POS_TO_BEHIND;
            }
        }
        _TRACE_("VB_VIEW!!  -> pos_camera_="<<pos_camera_);
    }

    //�J�����̈ړ��ڕW���W
    coord move_target_X_CAM, move_target_Y_CAM, move_target_Z_CAM;
    //�J�����̃r���[�|�C���g�̈ړ��ڕW���W
    coord move_target_X_VP, move_target_Y_VP, move_target_Z_VP;
    //�J�����̖ڕWUP�A���O���l
    angle move_target_XY_CAM_UP;

    //�J�����̖ڕW���W�A�r���[�|�C���g�̖ڕW���W��ݒ�
    static coord Dx = PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)/4);
    static int Ddx_hw = (int)((GGAF_PROPERTY(GAME_BUFFER_WIDTH)*LEN_UNIT/2) - (GGAF_PROPERTY(GAME_BUFFER_HEIGHT)*LEN_UNIT/2));

    if (is_cam_pos_option_back_) {
        //�I�v�V�������쒆�̃I�v�V�����w�ʂɉ��
        coord d = dZ_camera_init_*0.6;
        move_target_X_CAM = pOptCtrler->_X + pOptCtrler->_pKurokoA->_vX*-d;
        move_target_Y_CAM = pOptCtrler->_Y + pOptCtrler->_pKurokoA->_vY*-d;
        move_target_Z_CAM = pOptCtrler->_Z + pOptCtrler->_pKurokoA->_vZ*-d;
        move_target_X_VP = pOptCtrler->_X + pOptCtrler->_pKurokoA->_vX*d;
        move_target_Y_VP = pOptCtrler->_Y + pOptCtrler->_pKurokoA->_vY*d;
        move_target_Z_VP = pOptCtrler->_Z + pOptCtrler->_pKurokoA->_vZ*d;
        move_target_XY_CAM_UP = UTIL::simplifyAng(pOptCtrler->_pKurokoA->_angRzMv+D90ANG);

    } else {//�ʏ펞VAM
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
    //            move_target_X_CAM = 0;
    //            move_target_Y_CAM = 0;
    //            move_target_Z_CAM = -dZ_camera_init_;
    //            move_target_X_VP = 0;
    //            move_target_Y_VP = 0;
    //            move_target_Z_VP = 0;

                move_target_X_CAM = -Dx + (-pMyShip_->_X-200000)*2;
                //�� -200000 �̓J�����ړ��ʒu�A
                //   *2 �͎��@�����ɉ����������̃J�����̃p����B
                //   ���̕ӂ�̐��l�͔[�������܂Œ������J�����B
                //   TODO:�{���̓Q�[���̈�̑傫�����瓮�I�Ɍv�Z�ł���B���������������B
                if (-Dx > move_target_X_CAM) {
                    move_target_X_CAM = -Dx;
                } else if (move_target_X_CAM > Dx/2) {
                    move_target_X_CAM = Dx/2;
                }
                move_target_Y_CAM = pMyShip_->_Y;
                move_target_Z_CAM = pMyShip_->_Z - dZ_camera_init_;

                move_target_X_VP = Dx - (-pMyShip_->_X-200000)*2;
                if (Dx < move_target_X_VP) {
                    move_target_X_VP = Dx;
                } else if ( move_target_X_VP < -Dx/2) {
                    move_target_X_VP = -Dx/2;
                }
                move_target_Y_VP = pMyShip_->_Y;
                move_target_Z_VP = pMyShip_->_Z-100000;
                move_target_XY_CAM_UP = D90ANG;
            } else if (pos_camera_ == VAM_POS_LEFT) {
                move_target_X_CAM = -Dx + (-pMyShip_->_X-200000)*2;
                if (-Dx > move_target_X_CAM) {
                    move_target_X_CAM = -Dx;
                } else if (move_target_X_CAM > Dx/2) {
                    move_target_X_CAM = Dx/2;
                }
                move_target_Y_CAM = pMyShip_->_Y;
                move_target_Z_CAM = pMyShip_->_Z + dZ_camera_init_;
                move_target_X_VP = Dx - (-pMyShip_->_X-200000)*2;
                if (Dx < move_target_X_VP) {
                    move_target_X_VP = Dx;
                } else if ( move_target_X_VP < -Dx/2) {
                    move_target_X_VP = -Dx/2;
                }
                move_target_Y_VP = pMyShip_->_Y;
                move_target_Z_VP = pMyShip_->_Z+100000;
                move_target_XY_CAM_UP = D90ANG;
            } else if (pos_camera_ == VAM_POS_TOP) {
                move_target_X_CAM = -Dx - Ddx_hw + (-pMyShip_->_X-125000)*2;
                if ((-Dx - Ddx_hw) > move_target_X_CAM) {
                    move_target_X_CAM = -Dx - Ddx_hw;
                } else if (move_target_X_CAM > (Dx + Ddx_hw)/2) {
                    move_target_X_CAM = (Dx + Ddx_hw)/2;
                }
                move_target_Y_CAM = pMyShip_->_Y + dZ_camera_init_ + Ddx_hw;
                move_target_Z_CAM = pMyShip_->_Z;
                move_target_X_VP = Dx + Ddx_hw - (-pMyShip_->_X-125000)*2;
                if (Dx + Ddx_hw < move_target_X_VP) {
                    move_target_X_VP = Dx + Ddx_hw;
                } else if ( move_target_X_VP < -(Dx + Ddx_hw)/2) {
                    move_target_X_VP = -(Dx + Ddx_hw)/2;
                }
                move_target_Y_VP = pMyShip_->_Y;
                move_target_Z_VP = pMyShip_->_Z;
                if (pCam->_X < pVP->_X) {
                    move_target_XY_CAM_UP = D45ANG;
                } else {
                    move_target_XY_CAM_UP = D315ANG;
                }
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                move_target_X_CAM = -Dx - Ddx_hw + (-pMyShip_->_X-125000)*2;
                if ((-Dx - Ddx_hw) > move_target_X_CAM) {
                    move_target_X_CAM = -Dx - Ddx_hw;
                } else if (move_target_X_CAM > (Dx + Ddx_hw)/2) {
                    move_target_X_CAM = (Dx + Ddx_hw)/2;
                }
                move_target_Y_CAM = pMyShip_->_Y - dZ_camera_init_ - Ddx_hw;
                move_target_Z_CAM = pMyShip_->_Z;
                move_target_X_VP = Dx + Ddx_hw - (-pMyShip_->_X-125000)*2;
                if (Dx + Ddx_hw < move_target_X_VP) {
                    move_target_X_VP = Dx + Ddx_hw;
                } else if ( move_target_X_VP < -(Dx + Ddx_hw)/2) {
                    move_target_X_VP = -(Dx + Ddx_hw)/2;
                }
                move_target_Y_VP = pMyShip_->_Y;
                move_target_Z_VP = pMyShip_->_Z;
                if (pCam->_X < pVP->_X) {
                    move_target_XY_CAM_UP = D135ANG;
                } else {
                    move_target_XY_CAM_UP = D255ANG;
                }
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            move_target_X_CAM = pMyShip_->_X - (dZ_camera_init_*0.6);
            move_target_Y_CAM = pMyShip_->_Y;
            move_target_Z_CAM = pMyShip_->_Z;
            move_target_X_VP = pMyShip_->_X + (dZ_camera_init_*2);
            move_target_Y_VP = pMyShip_->_Y;
            move_target_Z_VP = pMyShip_->_Z;
            move_target_XY_CAM_UP = D90ANG;
    //        if (pos_camera_ == VAM_POS_BEHIND_RIGHT) {
    //            move_target_Z_CAM -= Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_LEFT) {
    //            move_target_Z_CAM += Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_TOP) {
    //            move_target_Y_CAM += Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_BOTTOM) {
    //            move_target_Y_CAM -= Dd;
    //        }
        } else {
            throwGgafCriticalException("World::processBehavior() �s����pos_camera_="<<pos_camera_);
        }
        //�J�����̖ڕW���W�A�r���[�|�C���g�̖ڕW���W�ɂ��āA���݂̓����Ă�������ւ̎኱��ʊ����s���B�i��ɺ����j
        move_target_Z_CAM -= (pMyShip_->_Z*0.05);
        move_target_Y_CAM -= (pMyShip_->_Y*0.05);
    }

//
//    GgafDxGeoElem* pGeoMyShip = pMyShip_->pRing_GeoHistory_->getCurrent(); //���݂̎��@���W
//    GgafDxGeoElem* pGeoMyShip_prev= pMyShip_->pRing_GeoHistory_->getPrev(); //���݂̂ЂƂO�̃t���[���̎��@���W
//    stop_dZ_ += (pGeoMyShip_prev->_Z - pGeoMyShip->_Z)*0.1; //���@�̈ړ��ʂ�1���̈ړ��ʂ�
//    stop_dY_ += (pGeoMyShip_prev->_Y - pGeoMyShip->_Y)*0.1; //�J�����̖ڕW���W�ɉ��Z���Ă܂��B
//    move_target_Z_CAM += stop_dZ_;
//    move_target_Y_CAM += stop_dY_;


    int cam_velo_renge;  //�J�����̈ړ����x�̍ő�A�ŏ��~���l
    //VB_VIEW���������̏���
    if (VB_PLAY->isBeingPressed(VB_VIEW)) {
        //VB_VIEW���������ςȂ����́A�������Ȉړ����x�ɐ���
        cam_velo_renge = cam_velo_renge_ / 100;
    } else {
        //�ʏ�̃J�����ړ����x�����ɂ���
        cam_velo_renge = cam_velo_renge_;
    }
    //VB_VIEW���������̏���
    if (VB_PLAY->isReleasedUp(VB_VIEW)) {
        if (VB_PLAY->isPushedUp(VB_VIEW, 20)) {
            //�`���������̏ꍇ�A�Ȃɂ����Ȃ��i���ʂɃr���[�|�C���g�ړ��ƂȂ�j
        } else {
            //����������������AVB_VIEW��������
            if (pos_camera_ < VAM_POS_TO_BEHIND) { //�w�ʃr���[�|�C���g�ł͂Ȃ��ꍇ�A
                //���ꂼ��̌��̑Ή��r���[�|�C���g�֖߂�B
                pos_camera_ += VAM_POS_TO_BEHIND;
            } else if (pos_camera_ > VAM_POS_TO_BEHIND) {//�w�ʃr���[�|�C���g�������ꍇ
                //���̂܂�

                //���ꂼ��̌��̑Ή��w�ʃr���[�|�C���g�֖߂�B
                //pos_camera_ -= VAM_POS_TO_BEHIND;
            }
        }
    }
    //�J�����̈ړ����x�̍ő�A�ŏ�������ݒ�
    pCam->_pKurokoB->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pKurokoB->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pKurokoB->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKurokoB->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKurokoB->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKurokoB->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);

    //�J�����ƃr���[�|�C���g�̈ړ����W�𐧌��B
    //���@�ړ��͈͂ɉ����āA��ʒ[�̊��������o���邽�߁B(�����Ƃ����Ȃ��H)
    if (pos_camera_ < VAM_POS_TO_BEHIND) {
        if (pos_camera_ == VAM_POS_RIGHT) {
            if (move_target_Y_CAM > lim_CAM_top_) {
                move_target_Y_CAM = lim_CAM_top_;
            }
            if (move_target_Y_CAM < lim_CAM_bottom_ ) {
                move_target_Y_CAM = lim_CAM_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_LEFT) {
            if (move_target_Y_CAM > lim_CAM_top_) {
                move_target_Y_CAM = lim_CAM_top_;
            }
            if (move_target_Y_CAM < lim_CAM_bottom_ ) {
                move_target_Y_CAM = lim_CAM_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_TOP) {
            if (move_target_Z_CAM > lim_CAM_zleft_) {
                move_target_Z_CAM = lim_CAM_zleft_;
            }
            if (move_target_Z_CAM < lim_CAM_zright_) {
                move_target_Z_CAM = lim_CAM_zright_;
            }
        } else if (pos_camera_ == VAM_POS_BOTTOM) {
            if (move_target_Z_CAM > lim_CAM_zleft_) {
                move_target_Z_CAM = lim_CAM_zleft_;
            }
            if (move_target_Z_CAM < lim_CAM_zright_) {
                move_target_Z_CAM = lim_CAM_zright_;
            }
        }
    } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
        if (move_target_Y_CAM > lim_CAM_top_ - correction_height_) {
            move_target_Y_CAM = lim_CAM_top_ - correction_height_;
        }
        if (move_target_Y_CAM < lim_CAM_bottom_ + correction_height_) {
            move_target_Y_CAM = lim_CAM_bottom_ + correction_height_;
        }
        if (move_target_Z_CAM > lim_CAM_zleft_ - correction_width_) {
            move_target_Z_CAM = lim_CAM_zleft_ - correction_width_;
        }
        if (move_target_Z_CAM < lim_CAM_zright_ + correction_width_) {
            move_target_Z_CAM = lim_CAM_zright_ + correction_width_;
        }
    }
    if (pos_camera_ < VAM_POS_TO_BEHIND) {
        if (pos_camera_ == VAM_POS_RIGHT) {
            if (move_target_Y_VP > lim_VP_top_) {
                move_target_Y_VP = lim_VP_top_;
            }
            if (move_target_Y_VP < lim_VP_bottom_ ) {
                move_target_Y_VP = lim_VP_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_LEFT) {
            if (move_target_Y_VP > lim_VP_top_) {
                move_target_Y_VP = lim_VP_top_;
            }
            if (move_target_Y_VP < lim_VP_bottom_ ) {
                move_target_Y_VP = lim_VP_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_TOP) {
            if (move_target_Z_VP > lim_VP_zleft_) {
                move_target_Z_VP = lim_VP_zleft_;
            }
            if (move_target_Z_VP < lim_VP_zright_) {
                move_target_Z_VP = lim_VP_zright_;
            }
        } else if (pos_camera_ == VAM_POS_BOTTOM) {
            if (move_target_Z_VP > lim_VP_zleft_) {
                move_target_Z_VP = lim_VP_zleft_;
            }
            if (move_target_Z_VP < lim_VP_zright_) {
                move_target_Z_VP = lim_VP_zright_;
            }
        }
    } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
        if (move_target_Y_VP > lim_VP_top_ - correction_height_) {
            move_target_Y_VP = lim_VP_top_ - correction_height_;
        }
        if (move_target_Y_VP < lim_VP_bottom_ + correction_height_) {
            move_target_Y_VP = lim_VP_bottom_ + correction_height_;
        }
        if (move_target_Z_VP > lim_VP_zleft_ - correction_width_) {
            move_target_Z_VP = lim_VP_zleft_ - correction_width_;
        }
        if (move_target_Z_VP < lim_VP_zright_ + correction_width_) {
            move_target_Z_VP = lim_VP_zright_ + correction_width_;
        }
    }

    //�J�����A�y�уr���[�|�C���g�̈ړ����x�����߂�B

    //�J�����̖ڕW���W�܂ł̊e���̋����i���W�����j
    int dX_CAM = move_target_X_CAM - pCam->_X;
    int dY_CAM = move_target_Y_CAM - pCam->_Y;
    int dZ_CAM = move_target_Z_CAM - pCam->_Z;
    //�r���[�|�C���g�̖ڕW���W�܂ł̊e���̋����i���W�����j
    int dX_VP = move_target_X_VP - pVP->_X;
    int dY_VP = move_target_Y_VP - pVP->_Y;
    int dZ_VP = move_target_Z_VP - pVP->_Z;
    velo veloVxRenge = 4000;
    velo veloVyRenge = 4000;
    velo veloVzRenge = 4000;
    if (pos_camera_ == VAM_POS_BEHIND_RIGHT || pos_camera_ == VAM_POS_BEHIND_LEFT) {
        if (pMyShip_->_X > -Dx) {
            //���Z���ړ��𑁂�����
            veloVzRenge *= 1.8;
            veloVxRenge *= 0.2;
        } else {
            //���Z���ړ���x������
            veloVzRenge *= 0.2;
            veloVxRenge *= 1.8;
        }
    } else if (pos_camera_ == VAM_POS_BEHIND_TOP || pos_camera_ == VAM_POS_BEHIND_BOTTOM) {
        if (pMyShip_->_X > -Dx) {
            //���Y���ړ��𑁂�����
            veloVyRenge *= 1.8;
            veloVxRenge *= 0.2;
        } else {
            //���Y���ړ���x������
            veloVyRenge *= 0.2;
            veloVxRenge *= 1.8;
        }
    } else if (pos_camera_ == VAM_POS_RIGHT || pos_camera_ == VAM_POS_LEFT) {
        if (pMyShip_->_X > -Dx) {
            //���X���ړ��𑁂�����
            veloVxRenge *= 1.8;
            veloVzRenge *= 0.2;
        } else {
            //���X���ړ���x������
            veloVxRenge *= 0.2;
            veloVzRenge *= 1.8;
        }
    } else if (pos_camera_ == VAM_POS_TOP || pos_camera_ == VAM_POS_BOTTOM) {
        if (pMyShip_->_X > -Dx) {
            //���X���ړ��𑁂�����
            veloVxRenge *= 1.8;
            veloVyRenge *= 0.2;
        } else {
            //���X���ړ���x������
            veloVxRenge *= 0.2;
            veloVyRenge *= 1.8;
        }
    }

    velo last_CAM_veloVxMv = pCam->_pKurokoB->_veloVxMv;
    velo  new_CAM_veloVxMv = pMyShip_->iMoveSpeed_*(dX_CAM*1.0 / stop_renge_);
    if (last_CAM_veloVxMv-veloVxRenge <= new_CAM_veloVxMv && new_CAM_veloVxMv <= last_CAM_veloVxMv+veloVxRenge) {
        pCam->_pKurokoB->setVxMvVelo(new_CAM_veloVxMv);
    } else {
        if (last_CAM_veloVxMv-veloVxRenge > new_CAM_veloVxMv) {
            pCam->_pKurokoB->setVxMvVelo(last_CAM_veloVxMv-veloVxRenge);
        } else if (new_CAM_veloVxMv > last_CAM_veloVxMv+veloVxRenge) {
            pCam->_pKurokoB->setVxMvVelo(last_CAM_veloVxMv+veloVxRenge);
        }
    }
    velo last_VP_veloVxMv = pVP->_pKurokoB->_veloVxMv;
    velo  new_VP_veloVxMv = pMyShip_->iMoveSpeed_*(dX_VP*1.0 / stop_renge_);
    if (last_VP_veloVxMv-veloVxRenge <= new_VP_veloVxMv && new_VP_veloVxMv <= last_VP_veloVxMv+veloVxRenge) {
        pVP->_pKurokoB->setVxMvVelo(new_VP_veloVxMv);
    } else {
        if (last_VP_veloVxMv-veloVxRenge > new_VP_veloVxMv) {
            pVP->_pKurokoB->setVxMvVelo(last_VP_veloVxMv-veloVxRenge);
        } else if (new_VP_veloVxMv > last_VP_veloVxMv+veloVxRenge) {
            pVP->_pKurokoB->setVxMvVelo(last_VP_veloVxMv+veloVxRenge);
        }
    }

    velo last_CAM_veloVyMv = pCam->_pKurokoB->_veloVyMv;
    velo  new_CAM_veloVyMv = pMyShip_->iMoveSpeed_*(dY_CAM*1.0 / stop_renge_);
    if (last_CAM_veloVyMv-veloVyRenge <= new_CAM_veloVyMv && new_CAM_veloVyMv <= last_CAM_veloVyMv+veloVyRenge) {
        pCam->_pKurokoB->setVyMvVelo(new_CAM_veloVyMv);
    } else {
        if (last_CAM_veloVyMv-veloVyRenge > new_CAM_veloVyMv) {
            pCam->_pKurokoB->setVyMvVelo(last_CAM_veloVyMv-veloVyRenge);
        } else if (new_CAM_veloVyMv > last_CAM_veloVyMv+veloVyRenge) {
            pCam->_pKurokoB->setVyMvVelo(last_CAM_veloVyMv+veloVyRenge);
        }
    }
    velo last_VP_veloVyMv = pVP->_pKurokoB->_veloVyMv;
    velo  new_VP_veloVyMv = pMyShip_->iMoveSpeed_*(dY_VP*1.0 / stop_renge_);
    if (last_VP_veloVyMv-veloVyRenge <= new_VP_veloVyMv && new_VP_veloVyMv <= last_VP_veloVyMv+veloVyRenge) {
        pVP->_pKurokoB->setVyMvVelo(new_VP_veloVyMv);
    } else {
        if (last_VP_veloVyMv-veloVyRenge > new_VP_veloVyMv) {
            pVP->_pKurokoB->setVyMvVelo(last_VP_veloVyMv-veloVyRenge);
        } else if (new_VP_veloVyMv > last_VP_veloVyMv+veloVyRenge) {
            pVP->_pKurokoB->setVyMvVelo(last_VP_veloVyMv+veloVyRenge);
        }
    }

    velo last_CAM_veloVzMv = pCam->_pKurokoB->_veloVzMv;
    velo  new_CAM_veloVzMv = pMyShip_->iMoveSpeed_*(dZ_CAM*1.0 / stop_renge_);
    if (last_CAM_veloVzMv-veloVzRenge <= new_CAM_veloVzMv && new_CAM_veloVzMv <= last_CAM_veloVzMv+veloVzRenge) {
        pCam->_pKurokoB->setVzMvVelo(new_CAM_veloVzMv);
    } else {
        if (last_CAM_veloVzMv-veloVzRenge > new_CAM_veloVzMv) {
            pCam->_pKurokoB->setVzMvVelo(last_CAM_veloVzMv-veloVzRenge);
        } else if (new_CAM_veloVzMv > last_CAM_veloVzMv+veloVzRenge) {
            pCam->_pKurokoB->setVzMvVelo(last_CAM_veloVzMv+veloVzRenge);
        }
    }

    velo last_VP_veloVzMv = pVP->_pKurokoB->_veloVzMv;
    velo  new_VP_veloVzMv = pMyShip_->iMoveSpeed_*(dZ_VP*1.0 / stop_renge_);
    if (last_VP_veloVzMv-veloVzRenge <= new_VP_veloVzMv && new_VP_veloVzMv <= last_VP_veloVzMv+veloVzRenge) {
        pVP->_pKurokoB->setVzMvVelo(new_VP_veloVzMv);
    } else {
        if (last_VP_veloVzMv-veloVzRenge > new_VP_veloVzMv) {
            pVP->_pKurokoB->setVzMvVelo(last_VP_veloVzMv-veloVzRenge);
        } else if (new_VP_veloVzMv > last_VP_veloVzMv+veloVzRenge) {
            pVP->_pKurokoB->setVzMvVelo(last_VP_veloVzMv+veloVzRenge);
        }
    }

    //�J������UP���v�Z
    angvelo angvelo_cam_up = cam_velo_renge/20; //cam_velo_renge��VB_VIEW�������ςŒ��ᑬ�ɂȂ���̑��x
    if (angXY_nowCamUp_ != move_target_XY_CAM_UP) {
        angle da = UTIL::getAngDiff(angXY_nowCamUp_, move_target_XY_CAM_UP);
        if (-angvelo_cam_up < da && da < angvelo_cam_up) {
            angXY_nowCamUp_ = move_target_XY_CAM_UP;
        } else {
            angXY_nowCamUp_ += (angvelo_cam_up * SGN(da));
        }
        angXY_nowCamUp_ = UTIL::simplifyAng(angXY_nowCamUp_);
        pCam->_pVecCamUp->x = ANG_COS(angXY_nowCamUp_);
        pCam->_pVecCamUp->y = ANG_SIN(angXY_nowCamUp_);
        pCam->_pVecCamUp->z = 0.0f;
    }

    pCam->_pKurokoB->behave();
    pVP->_pKurokoB->behave();

//    _TRACE_(getActivePartFrame()<<","<<dX_CAM<<","<<dY_CAM<<","<<dZ_CAM<<","<<pCam->_X<<","<<pCam->_Y<<","<<pCam->_Z<<","<<last_CAM_veloVxMv<<","<<new_CAM_veloVxMv<<","<<last_CAM_veloVyMv<<","<<new_CAM_veloVyMv<<","<<last_CAM_veloVzMv<<","<<new_CAM_veloVzMv<<","<<pCam->_pKurokoB->_veloVxMv<<","<<pCam->_pKurokoB->_veloVyMv<<","<<pCam->_pKurokoB->_veloVzMv);

}
VamSysCamWorker::~VamSysCamWorker() {
}
