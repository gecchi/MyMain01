#ifndef VAMSYSCAMWORKER_H_
#define VAMSYSCAMWORKER_H_
#include "jp/gecchi/VioletVreath/actor/camera_worker/CameraWorker.h"

#define VAM_POS_RIGHT 1
#define VAM_POS_LEFT 2
#define VAM_POS_TOP 3
#define VAM_POS_BOTTOM 4
#define VAM_POS_TO_BEHIND 10
#define VAM_POS_BEHIND_RIGHT 11
#define VAM_POS_BEHIND_LEFT 12
#define VAM_POS_BEHIND_TOP 13
#define VAM_POS_BEHIND_BOTTOM 14

namespace VioletVreath {

/**
 * VamSystem�̃J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class VamSysCamWorker : public CameraWorker {

public:
    MyShip* pMyShip_;

    /** �J����Y���W��� */
    coord lim_CAM_top_;
    /** �J����Y���W���� */
    coord lim_CAM_bottom_;
    /** �J����X���W��� */
    coord lim_CAM_front_;
    /** �J����X���W���� */
    coord lim_CAM_behaind_;
    /** �J����Z���W��� */
    coord lim_CAM_zleft_;
    /** �J����Z���W���� */
    coord lim_CAM_zright_;
    /** �r���[�|�C���gY���W��� */
    coord lim_VP_top_;
    /** �r���[�|�C���gY���W���� */
    coord lim_VP_bottom_;
    /** �r���[�|�C���gX���W��� */
    coord lim_VP_front_;
    /** �r���[�|�C���gX���W���� */
    coord lim_VP_behaind_;
    /** �r���[�|�C���gZ���W��� */
    coord lim_VP_zleft_;
    /** �r���[�|�C���gZ���W���� */
    coord lim_VP_zright_;

    /** ��ʔw�㎞�pZ���␳�͈͍��� */
    coord correction_width_;
    /** ��ʔw�㎞�pY���␳�͈͍��� */
    coord correction_height_;
    /** �J�����ڕW���W�ɉ�������Z�����W�I�t�Z�b�g�␳�l */
    coord stop_dZ_;
    /** �J�����ڕW���W�ɉ�������Y�����W�I�t�Z�b�g�␳�l */
    coord stop_dY_;
    /** �J�����̓I�v�V�����w�ʒ��ł���ꍇtrue */
    bool is_cam_pos_option_back_;

    int pos_camera_;
    int pos_camera_prev_;
    coord dZ_camera_init_;
    int target_up_face_no_prev_;

    coord move_target_x_CAM_prev_, move_target_y_CAM_prev_, move_target_z_CAM_prev_;
    //�J�����̃r���[�|�C���g�̈ړ��ڕW���W
    coord move_target_x_VP_prev_, move_target_y_VP_prev_, move_target_z_VP_prev_;
public:
    VamSysCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }

    virtual ~VamSysCamWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
