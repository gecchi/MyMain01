#include "VamSysCamWorker.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/Camera.h"
#include "jp/gecchi/VioletVreath/actor/ViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


VamSysCamWorker::VamSysCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "VamSysCamWorker";
    pMyShip_ = nullptr; //MyShipScene�ɐݒ肵�Ă��炤

    //�����J�����ړ��͈͐���
    float revise = 0.7; //�΂߂��猩��̂ŕ␳�l���|����B1.0�̏ꍇ�͌��_����Ńh���s�V���B����͔��������J��Ԃ���
    lim_CAM_top_     = MyShip::lim_y_top_     - (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_CAM_bottom_  = MyShip::lim_y_bottom_  + (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_CAM_front_   = MyShip::lim_x_front_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_CAM_behaind_ = MyShip::lim_x_behaind_ + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_CAM_zleft_   = MyShip::lim_z_left_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_CAM_zright_  = MyShip::lim_z_right_  + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;

    lim_VP_top_     = MyShip::lim_y_top_     - (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_VP_bottom_  = MyShip::lim_y_bottom_  + (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_VP_front_   = MyShip::lim_x_front_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_VP_behaind_ = MyShip::lim_x_behaind_ + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_VP_zleft_   = MyShip::lim_z_left_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_VP_zright_  = MyShip::lim_z_right_  + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    is_cam_pos_option_back_ = false;
    pos_camera_prev_ = -1;
    pos_camera_ = VAM_POS_RIGHT;
    pos_camera_pressed_ = VAM_POS_RIGHT;
    cam_mv_frame_base_ = 50;
    cam_mv_frame_ = cam_mv_frame_base_;
    mv_t_x_CAM_prev_ = 0;
    mv_t_y_CAM_prev_ = 0;
    mv_t_z_CAM_prev_ = 0;
}
void VamSysCamWorker::initialize() {
    CameraWorker::initialize();

    //�����J����Z�ʒu
    dZ_camera_init_ = -DX_C(pCam_->_cameraZ_org);

    //��ʔw��p�͈͍���
    //�w���Z���W��dZ_camera_init_/2
    correction_width_ = PX_C(30); //(PROPERTY::GAME_BUFFER_WIDTH*LEN_UNIT/2)/4;
    correction_height_ = PX_C(30); //(PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT/2)/4;
    pos_camera_ = VAM_POS_RIGHT;
    pos_camera_prev_ = -100;
    mv_t_x_CAM_prev_ = 0;
    mv_t_y_CAM_prev_ = 0;
    mv_t_z_CAM_prev_ = 0;
    _TRACE_("VamSysCamWorker::initialize() this="<<this);
    dump();
}
void VamSysCamWorker::onActive() {
    //CameraWorker::onActive();
    //cam_mv_frame_ = cam_mv_frame_base_;
}

void VamSysCamWorker::processBehavior() {
    VirtualButton* pVbPlay = VB_PLAY;
    //�Q�[�����J�������[�N����
    if (pMyShip_ == nullptr) {
        return; //MyShipScene�V�[���������Ȃ�J�������[�N�֎~
    }
    Camera* pCam = pCam_;
    ViewPoint* pVP = (ViewPoint*)(pCam->getViewPoint());
    MyOptionController* pOptCtrler = P_MYSHIP_SCENE->papOptionCtrler_[0];

    //�J�����ʒu�ԍ������菈��
    is_cam_pos_option_back_ = false;
//    if (pVbPlay->isBeingPressed(VB_OPTION)) { //�I�v�V�������쎞
//        if (MyOptionController::now_option_num_ >= 1 && pVbPlay->isBeingPressed(VB_VIEW)) {
//            is_cam_pos_option_back_ = true; //TODO:�I�v�V�������쒆�̃I�v�V����[0]�̔w�ʂɉ��
//        }
//    } else if (pVbPlay->isPushedDown(VB_VIEW)) { //�r���[�{�^���v�b�V��                              //�I�v�V�����񑀍쎞�i�ʏ펞�j
//        _TRACE_("VB_VIEW!! now pos_camera_="<<pos_camera_);
//        if (pos_camera_ < VAM_POS_TO_BEHIND) { //�w�ʃr���[�|�C���g�ł͂Ȃ��ꍇ�A
//            pos_camera_ += VAM_POS_TO_BEHIND;  //���ꂼ��̑Ή��w�ʃr���[�|�C���g��
//        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {//�w�ʃr���[�|�C���g�̏ꍇ
//            //�������͂ɂ��V���ȃr���[�|�C���g��
//            if (pVbPlay->isBeingPressed(VB_RIGHT)) {
//                pos_camera_ = VAM_POS_LEFT;
//            } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
//                pos_camera_ = VAM_POS_RIGHT;
//            } else if (pVbPlay->isBeingPressed(VB_UP)) {
//                pos_camera_ = VAM_POS_BOTTOM;
//            } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
//                pos_camera_ = VAM_POS_TOP;
//            } else {
//                //���������͂̏ꍇ�A���̃r���[�|�C���g��
//                pos_camera_ -= VAM_POS_TO_BEHIND;
//            }
//        }
//        _TRACE_("VB_VIEW!!  -> pos_camera_="<<pos_camera_);
//    }
    bool isBeingPressed_VB_VIEW_RIGHT = pVbPlay->isBeingPressed(VB_VIEW_RIGHT);
    bool isBeingPressed_VB_VIEW_LEFT = pVbPlay->isBeingPressed(VB_VIEW_LEFT);
    bool isBeingPressed_VB_VIEW_UP = pVbPlay->isBeingPressed(VB_VIEW_UP);
    bool isBeingPressed_VB_VIEW_DOWN = pVbPlay->isBeingPressed(VB_VIEW_DOWN);
    bool isBeingPressed_VB_VIEW = isBeingPressed_VB_VIEW_RIGHT || isBeingPressed_VB_VIEW_LEFT || isBeingPressed_VB_VIEW_UP || isBeingPressed_VB_VIEW_DOWN;


    bool isReleasedUp_VB_VIEW_RIGHT = pVbPlay->isReleasedUp(VB_VIEW_RIGHT);
    bool isReleasedUp_VB_VIEW_LEFT = pVbPlay->isReleasedUp(VB_VIEW_LEFT);
    bool isReleasedUp_VB_VIEW_UP = pVbPlay->isReleasedUp(VB_VIEW_UP);
    bool isReleasedUp_VB_VIEW_DOWN = pVbPlay->isReleasedUp(VB_VIEW_DOWN);
    bool isReleasedUp_VB_VIEW = isReleasedUp_VB_VIEW_RIGHT || isReleasedUp_VB_VIEW_LEFT || isReleasedUp_VB_VIEW_UP || isReleasedUp_VB_VIEW_DOWN;

    bool isPushedDown_VB_VIEW_RIGHT = pVbPlay->isPushedDown(VB_VIEW_RIGHT);
    bool isPushedDown_VB_VIEW_LEFT = pVbPlay->isPushedDown(VB_VIEW_LEFT);
    bool isPushedDown_VB_VIEW_UP = pVbPlay->isPushedDown(VB_VIEW_UP);
    bool isPushedDown_VB_VIEW_DOWN = pVbPlay->isPushedDown(VB_VIEW_DOWN);
    bool isPushedDown_VB_VIEW = isPushedDown_VB_VIEW_RIGHT || isPushedDown_VB_VIEW_LEFT || isPushedDown_VB_VIEW_UP || isPushedDown_VB_VIEW_DOWN;

    if (isPushedDown_VB_VIEW_LEFT) {
        pos_camera_pressed_ = pos_camera_;
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
                //�o���Ȃ�
            } else if (pos_camera_ == VAM_POS_LEFT) {
                pos_camera_ = VAM_POS_BEHIND_LEFT;
            } else if (pos_camera_ == VAM_POS_TOP) {
                pos_camera_ = VAM_POS_RIGHT;
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                pos_camera_ = VAM_POS_RIGHT;
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            pos_camera_ = VAM_POS_RIGHT;
        }
    } else if (isPushedDown_VB_VIEW_RIGHT) {
        pos_camera_pressed_ = pos_camera_;
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
                pos_camera_ = VAM_POS_BEHIND_RIGHT;
            } else if (pos_camera_ == VAM_POS_LEFT) {
                //�o���Ȃ�
            } else if (pos_camera_ == VAM_POS_TOP) {
                pos_camera_ = VAM_POS_LEFT;
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                pos_camera_ = VAM_POS_LEFT;
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            pos_camera_ = VAM_POS_LEFT;
        }
    } else if (isPushedDown_VB_VIEW_DOWN) {
        pos_camera_pressed_ = pos_camera_;
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
                pos_camera_ = VAM_POS_TOP;
            } else if (pos_camera_ == VAM_POS_LEFT) {
                pos_camera_ = VAM_POS_TOP;
            } else if (pos_camera_ == VAM_POS_TOP) {
                //�o���Ȃ�
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                pos_camera_ = VAM_POS_BEHIND_BOTTOM;
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            pos_camera_ = VAM_POS_TOP;
        }
    } else if (isPushedDown_VB_VIEW_UP) {
        pos_camera_pressed_ = pos_camera_;
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
                pos_camera_ = VAM_POS_BOTTOM;
            } else if (pos_camera_ == VAM_POS_LEFT) {
                pos_camera_ = VAM_POS_BOTTOM;
            } else if (pos_camera_ == VAM_POS_TOP) {
                pos_camera_ = VAM_POS_BEHIND_TOP;
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                //�o���Ȃ�
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            pos_camera_ = VAM_POS_BOTTOM;
        }
    }


    if (isReleasedUp_VB_VIEW_UP) {
        if (pVbPlay->isPushedUp(VB_VIEW_UP, 20)) {
            //�`���������̏ꍇ�A�Ȃɂ����Ȃ��i���ʂɃr���[�|�C���g�ړ��ƂȂ�j
        } else {
            //�������㗣�����ꍇ�A���̃r���[�|�C���g�֖߂�
            pos_camera_ = pos_camera_pressed_;
        }
    }
    if (isReleasedUp_VB_VIEW_DOWN) {
        if (pVbPlay->isPushedUp(VB_VIEW_DOWN, 20)) {
            //�`���������̏ꍇ�A�Ȃɂ����Ȃ��i���ʂɃr���[�|�C���g�ړ��ƂȂ�j
        } else {
            //�������㗣�����ꍇ�A���̃r���[�|�C���g�֖߂�
            pos_camera_ = pos_camera_pressed_;
        }
    }
    if (isReleasedUp_VB_VIEW_LEFT) {
        if (pVbPlay->isPushedUp(VB_VIEW_LEFT, 20)) {
            //�`���������̏ꍇ�A�Ȃɂ����Ȃ��i���ʂɃr���[�|�C���g�ړ��ƂȂ�j
        } else {
            //�������㗣�����ꍇ�A���̃r���[�|�C���g�֖߂�
            pos_camera_ = pos_camera_pressed_;
        }
    }
    if (isReleasedUp_VB_VIEW_RIGHT) {
        if (pVbPlay->isPushedUp(VB_VIEW_RIGHT, 20)) {
            //�`���������̏ꍇ�A�Ȃɂ����Ȃ��i���ʂɃr���[�|�C���g�ړ��ƂȂ�j
        } else {
            //�������㗣�����ꍇ�A���̃r���[�|�C���g�֖߂�
            pos_camera_ = pos_camera_pressed_;
        }
    }

//    //VB_VIEW���������̏���
//    if (pVbPlay->isReleasedUp(VB_VIEW)) {
//        if (pVbPlay->isPushedUp(VB_VIEW, 20)) {
//            //�`���������̏ꍇ�A�Ȃɂ����Ȃ��i���ʂɃr���[�|�C���g�ړ��ƂȂ�j
//        } else {
//            //�������㗣�����ꍇ�A���̃r���[�|�C���g�֖߂�
//            if (pos_camera_ < VAM_POS_TO_BEHIND) { //�w�ʃr���[�|�C���g�ȊO�ւ̈ړ��r���������ꍇ
//                //�w�ʃr���[�|�C���g�֖߂�B
//                pos_camera_ += VAM_POS_TO_BEHIND;
//            } else if (pos_camera_ > VAM_POS_TO_BEHIND) {//�w�ʃr���[�|�C���g�ւ̓r���������ꍇ
//                //���ꂼ��̌��̑Ή��r���[�|�C���g�֖߂�B
//                pos_camera_ -= VAM_POS_TO_BEHIND;
//            }
//        }
//    }

    //�J�����̈ړ��ڕW���W
    coord mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM;
    //�J�����̃r���[�|�C���g�̈ړ��ڕW���W
    coord mv_t_x_VP, mv_t_y_VP, mv_t_z_VP;

    //�J�����̖ڕW���W�A�r���[�|�C���g�̖ڕW���W��ݒ�
    static const coord Dx = PX_C(PROPERTY::GAME_BUFFER_WIDTH/4);
    static const int Ddx_hw = (int)((PROPERTY::GAME_BUFFER_WIDTH*LEN_UNIT/2) - (PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT/2));

    if (is_cam_pos_option_back_) { //TODO:�I�v�V�������쒆�̃I�v�V����[0]�w�ʂɉ��
        coord d = dZ_camera_init_*0.6;
        GgafDxKuroko* pOptCtrler_pKuroko = pOptCtrler->getKuroko();
        mv_t_x_CAM = pOptCtrler->_x + pOptCtrler_pKuroko->_vX*-d;
        mv_t_y_CAM = pOptCtrler->_y + pOptCtrler_pKuroko->_vY*-d;
        mv_t_z_CAM = pOptCtrler->_z + pOptCtrler_pKuroko->_vZ*-d;
        mv_t_x_VP = pOptCtrler->_x + pOptCtrler_pKuroko->_vX*d;
        mv_t_y_VP = pOptCtrler->_y + pOptCtrler_pKuroko->_vY*d;
        mv_t_z_VP = pOptCtrler->_z + pOptCtrler_pKuroko->_vZ*d;

    } else {//�ʏ펞VAM
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
    //            mv_t_x_CAM = 0;
    //            mv_t_y_CAM = 0;
    //            mv_t_z_CAM = -dZ_camera_init_;
    //            mv_t_x_VP = 0;
    //            mv_t_y_VP = 0;
    //            mv_t_z_VP = 0;

                mv_t_x_CAM = -Dx + (-pMyShip_->_x-200000)*2;
                //�� -200000 �̓J�����ړ��ʒu�A
                //   *2 �͎��@�����ɉ����������̃J�����̃p����B
                //   ���̕ӂ�̐��l�͔[�������܂Œ������J�����B
                //   TODO:�{���̓Q�[���̈�̑傫�����瓮�I�Ɍv�Z�ł���B���������������B
                if (-Dx > mv_t_x_CAM) {
                    mv_t_x_CAM = -Dx;
                } else if (mv_t_x_CAM > Dx/2) {
                    mv_t_x_CAM = Dx/2;
                }
                mv_t_y_CAM = pMyShip_->_y;
                mv_t_z_CAM = pMyShip_->_z - dZ_camera_init_;

                mv_t_x_VP = Dx - (-pMyShip_->_x-200000)*2;
                if (Dx < mv_t_x_VP) {
                    mv_t_x_VP = Dx;
                } else if ( mv_t_x_VP < -Dx/2) {
                    mv_t_x_VP = -Dx/2;
                }
                mv_t_y_VP = pMyShip_->_y;
                mv_t_z_VP = pMyShip_->_z-100000;
            } else if (pos_camera_ == VAM_POS_LEFT) {
                mv_t_x_CAM = -Dx + (-pMyShip_->_x-200000)*2;
                if (-Dx > mv_t_x_CAM) {
                    mv_t_x_CAM = -Dx;
                } else if (mv_t_x_CAM > Dx/2) {
                    mv_t_x_CAM = Dx/2;
                }
                mv_t_y_CAM = pMyShip_->_y;
                mv_t_z_CAM = pMyShip_->_z + dZ_camera_init_;
                mv_t_x_VP = Dx - (-pMyShip_->_x-200000)*2;
                if (Dx < mv_t_x_VP) {
                    mv_t_x_VP = Dx;
                } else if ( mv_t_x_VP < -Dx/2) {
                    mv_t_x_VP = -Dx/2;
                }
                mv_t_y_VP = pMyShip_->_y;
                mv_t_z_VP = pMyShip_->_z+100000;
            } else if (pos_camera_ == VAM_POS_TOP) {
                mv_t_x_CAM = -Dx - Ddx_hw + (-pMyShip_->_x-125000)*2;
                if ((-Dx - Ddx_hw) > mv_t_x_CAM) {
                    mv_t_x_CAM = -Dx - Ddx_hw;
                } else if (mv_t_x_CAM > (Dx + Ddx_hw)/2) {
                    mv_t_x_CAM = (Dx + Ddx_hw)/2;
                }
                mv_t_y_CAM = pMyShip_->_y + dZ_camera_init_ + Ddx_hw;
                mv_t_z_CAM = pMyShip_->_z;
                mv_t_x_VP = Dx + Ddx_hw - (-pMyShip_->_x-125000)*2;
                if (Dx + Ddx_hw < mv_t_x_VP) {
                    mv_t_x_VP = Dx + Ddx_hw;
                } else if ( mv_t_x_VP < -(Dx + Ddx_hw)/2) {
                    mv_t_x_VP = -(Dx + Ddx_hw)/2;
                }
                mv_t_y_VP = pMyShip_->_y;
                mv_t_z_VP = pMyShip_->_z;
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                mv_t_x_CAM = -Dx - Ddx_hw + (-pMyShip_->_x-125000)*2;
                if ((-Dx - Ddx_hw) > mv_t_x_CAM) {
                    mv_t_x_CAM = -Dx - Ddx_hw;
                } else if (mv_t_x_CAM > (Dx + Ddx_hw)/2) {
                    mv_t_x_CAM = (Dx + Ddx_hw)/2;
                }
                mv_t_y_CAM = pMyShip_->_y - dZ_camera_init_ - Ddx_hw;
                mv_t_z_CAM = pMyShip_->_z;
                mv_t_x_VP = Dx + Ddx_hw - (-pMyShip_->_x-125000)*2;
                if (Dx + Ddx_hw < mv_t_x_VP) {
                    mv_t_x_VP = Dx + Ddx_hw;
                } else if ( mv_t_x_VP < -(Dx + Ddx_hw)/2) {
                    mv_t_x_VP = -(Dx + Ddx_hw)/2;
                }
                mv_t_y_VP = pMyShip_->_y;
                mv_t_z_VP = pMyShip_->_z;
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            mv_t_x_CAM = pMyShip_->_x - (dZ_camera_init_*0.6);
            mv_t_y_CAM = pMyShip_->_y;
            mv_t_z_CAM = pMyShip_->_z;
            mv_t_x_VP = pMyShip_->_x + (dZ_camera_init_*2);
            mv_t_y_VP = pMyShip_->_y;
            mv_t_z_VP = pMyShip_->_z;
    //        if (pos_camera_ == VAM_POS_BEHIND_RIGHT) {
    //            mv_t_z_CAM -= Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_LEFT) {
    //            mv_t_z_CAM += Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_TOP) {
    //            mv_t_y_CAM += Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_BOTTOM) {
    //            mv_t_y_CAM -= Dd;
    //        }
        } else {
            throwGgafCriticalException("VamSysCamWorker::processBehavior() �s����pos_camera_="<<pos_camera_);
        }
        //�J�����̖ڕW���W�A�r���[�|�C���g�̖ڕW���W�ɂ��āA���݂̓����Ă�������ւ̎኱��ʊ����s���B�i��ɺ����j
        mv_t_z_CAM -= (pMyShip_->_z*0.08);
        mv_t_y_CAM -= (pMyShip_->_y*0.08);
    }

    //�J�����ړ����W�𐧌��B
    //���@�ړ��͈͂ɉ����āA��ʒ[�̊��������o���邽�߁B(�����Ƃ����Ȃ��H)
    if (pos_camera_ < VAM_POS_TO_BEHIND) {
        if (pos_camera_ == VAM_POS_RIGHT) {
            if (mv_t_y_CAM > lim_CAM_top_) {
                mv_t_y_CAM = lim_CAM_top_;
            }
            if (mv_t_y_CAM < lim_CAM_bottom_ ) {
                mv_t_y_CAM = lim_CAM_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_LEFT) {
            if (mv_t_y_CAM > lim_CAM_top_) {
                mv_t_y_CAM = lim_CAM_top_;
            }
            if (mv_t_y_CAM < lim_CAM_bottom_ ) {
                mv_t_y_CAM = lim_CAM_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_TOP) {
            if (mv_t_z_CAM > lim_CAM_zleft_) {
                mv_t_z_CAM = lim_CAM_zleft_;
            }
            if (mv_t_z_CAM < lim_CAM_zright_) {
                mv_t_z_CAM = lim_CAM_zright_;
            }
        } else if (pos_camera_ == VAM_POS_BOTTOM) {
            if (mv_t_z_CAM > lim_CAM_zleft_) {
                mv_t_z_CAM = lim_CAM_zleft_;
            }
            if (mv_t_z_CAM < lim_CAM_zright_) {
                mv_t_z_CAM = lim_CAM_zright_;
            }
        }
    } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
        if (mv_t_y_CAM > lim_CAM_top_ - correction_height_) {
            mv_t_y_CAM = lim_CAM_top_ - correction_height_;
        }
        if (mv_t_y_CAM < lim_CAM_bottom_ + correction_height_) {
            mv_t_y_CAM = lim_CAM_bottom_ + correction_height_;
        }
        if (mv_t_z_CAM > lim_CAM_zleft_ - correction_width_) {
            mv_t_z_CAM = lim_CAM_zleft_ - correction_width_;
        }
        if (mv_t_z_CAM < lim_CAM_zright_ + correction_width_) {
            mv_t_z_CAM = lim_CAM_zright_ + correction_width_;
        }
    }
    //�r���[�|�C���g�̈ړ����W�𐧌�
    if (pos_camera_ < VAM_POS_TO_BEHIND) {
        if (pos_camera_ == VAM_POS_RIGHT) {
            if (mv_t_y_VP > lim_VP_top_) {
                mv_t_y_VP = lim_VP_top_;
            }
            if (mv_t_y_VP < lim_VP_bottom_ ) {
                mv_t_y_VP = lim_VP_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_LEFT) {
            if (mv_t_y_VP > lim_VP_top_) {
                mv_t_y_VP = lim_VP_top_;
            }
            if (mv_t_y_VP < lim_VP_bottom_ ) {
                mv_t_y_VP = lim_VP_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_TOP) {
            if (mv_t_z_VP > lim_VP_zleft_) {
                mv_t_z_VP = lim_VP_zleft_;
            }
            if (mv_t_z_VP < lim_VP_zright_) {
                mv_t_z_VP = lim_VP_zright_;
            }
        } else if (pos_camera_ == VAM_POS_BOTTOM) {
            if (mv_t_z_VP > lim_VP_zleft_) {
                mv_t_z_VP = lim_VP_zleft_;
            }
            if (mv_t_z_VP < lim_VP_zright_) {
                mv_t_z_VP = lim_VP_zright_;
            }
        }
    } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
        if (mv_t_y_VP > lim_VP_top_ - correction_height_) {
            mv_t_y_VP = lim_VP_top_ - correction_height_;
        }
        if (mv_t_y_VP < lim_VP_bottom_ + correction_height_) {
            mv_t_y_VP = lim_VP_bottom_ + correction_height_;
        }
        if (mv_t_z_VP > lim_VP_zleft_ - correction_width_) {
            mv_t_z_VP = lim_VP_zleft_ - correction_width_;
        }
        if (mv_t_z_VP < lim_VP_zright_ + correction_width_) {
            mv_t_z_VP = lim_VP_zright_ + correction_width_;
        }
    }

    //�^�[�Q�b�g�ֈړ�
    if (onChangeToActive() ||
        isPushedDown_VB_VIEW || isReleasedUp_VB_VIEW ||
        mv_t_x_CAM_prev_ != mv_t_x_CAM ||
        mv_t_y_CAM_prev_ != mv_t_y_CAM ||
        mv_t_z_CAM_prev_ != mv_t_z_CAM ) {


        //VB_VIEW���������̏���
//        if (pVbPlay->isBeingPressed(VB_VIEW)) {
        if (isBeingPressed_VB_VIEW) {
            //VB_VIEW���������ςȂ����́A�������Ȉړ����x�ɐ���
            GgafDxAxesMover* pCamAxMvr = pCam_->pAxsMver_;
            pCamAxMvr->setZeroVxyzMvAcce();
            pCamAxMvr->setVxyzMvVelo(
                    pCamAxMvr->_velo_vx_mv*0.1,
                    pCamAxMvr->_velo_vy_mv*0.1,
                    pCamAxMvr->_velo_vz_mv*0.1);
            GgafDxAxesMover* pVpAxMvr = pVp_->pAxsMver_;
            pVpAxMvr->setZeroVxyzMvAcce();
            pVpAxMvr->setVxyzMvVelo(
                    pVpAxMvr->_velo_vx_mv*0.1,
                    pVpAxMvr->_velo_vy_mv*0.1,
                    pVpAxMvr->_velo_vz_mv*0.1);
            cam_mv_frame_ = cam_mv_frame_base_ * 20;
        } else {
            cam_mv_frame_ = cam_mv_frame_base_;
            if (MAX3(ABS(mv_t_x_CAM - pCam_->_x),
                     ABS(mv_t_y_CAM - pCam_->_y),
                     ABS(mv_t_z_CAM - pCam_->_z) ) > PX_C(4000)) {
                cam_mv_frame_ = cam_mv_frame_base_ * 3; //�����̏ꍇ�A���B���Ԃɏ����]�T������
            } else if ( pos_camera_ > VAM_POS_TO_BEHIND &&
                mv_t_x_CAM_prev_ == mv_t_x_CAM &&
                    (   mv_t_y_CAM_prev_ != mv_t_y_CAM ||
                        mv_t_z_CAM_prev_ != mv_t_z_CAM   )
            ) {
                cam_mv_frame_ = cam_mv_frame_base_ * 0.2 + 1;
            }
        }

//        _TRACE_("VamSysCamWorker::processBehavior() �^�[�Q�b�g�ֈړ� cam_mv_frame_="<<cam_mv_frame_<<" pos_camera_="<<pos_camera_);
        //�^�[�Q�b�g�փJ�����ړ�
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.9, 0.5, 0.1); //�~�ʂ�`���悤�ȃX���C�h
            } else if (pos_camera_ == VAM_POS_LEFT) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.9, 0.5, 0.1);
            } else if (pos_camera_ == VAM_POS_TOP) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.9, 0.1, 0.5);
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.9, 0.1, 0.5);
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_BEHIND_RIGHT) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.1, 0.5, 0.9);
            } else if (pos_camera_ == VAM_POS_BEHIND_LEFT) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.1, 0.5, 0.9);
            } else if (pos_camera_ == VAM_POS_BEHIND_TOP) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.1, 0.9, 0.5);
            } else if (pos_camera_ == VAM_POS_BEHIND_BOTTOM) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.1, 0.9, 0.5);
            }
        } else {
            throwGgafCriticalException("VamSysCamWorker::processBehavior() �ǂ��ɃJ�������s�����̂��킩��܂���(1)");
        }
        //�^�[�Q�b�g��VP�ړ�
        slideMvVpTo(mv_t_x_VP,
                    mv_t_y_VP,
                    mv_t_z_VP, cam_mv_frame_);

        //UP��␳
        if (onChangeToActive() || isPushedDown_VB_VIEW || isReleasedUp_VB_VIEW) {
            if (pos_camera_ == VAM_POS_RIGHT || pos_camera_ == VAM_POS_LEFT || pos_camera_ > VAM_POS_TO_BEHIND) {
                pCam_->slideUpCamTo(Camera::FACE_TOP, cam_mv_frame_/2);
            } else if (pos_camera_ == VAM_POS_TOP) {
                if (pCam_->vcv_face_ == Camera::FACE_NZZ) {
                    pCam_->slideUpCamTo(Camera::FACE_BOTTOM, cam_mv_frame_/2);
                } else {
                    pCam_->slideUpCamTo(Camera::FACE_PZZ, cam_mv_frame_/2);
                }
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                if (pCam_->vcv_face_ == Camera::FACE_NZZ) {
                    pCam_->slideUpCamTo(Camera::FACE_BOTTOM, cam_mv_frame_/2);
                } else {
                    pCam_->slideUpCamTo(Camera::FACE_NZZ, cam_mv_frame_/2);
                }
            } else {
                throwGgafCriticalException("VamSysCamWorker::processBehavior() �ǂ��ɃJ�������s�����̂��킩��܂���(2)");
            }
        }
    }


    pos_camera_prev_ = pos_camera_;
    mv_t_x_CAM_prev_ = mv_t_x_CAM;
    mv_t_y_CAM_prev_ = mv_t_y_CAM;
    mv_t_z_CAM_prev_ = mv_t_z_CAM;
}
VamSysCamWorker::~VamSysCamWorker() {
}
