#ifndef VAMSYSCAMWORKER2_H_
#define VAMSYSCAMWORKER2_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"
#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"

#define VAM_POS_BEHIND              DIR26(-1, 0, 0)
#define VAM_POS_BEHIND_ZRIGHT       DIR26(-1, 0,-1)
//#define VAM_POS_BEHIND_ZRIGHT_UP    DIR26(-1,+1,-1)
#define VAM_POS_BEHIND_UP           DIR26(-1,+1, 0)
//#define VAM_POS_BEHIND_ZLEFT_UP     DIR26(-1,+1,+1)
#define VAM_POS_BEHIND_ZLEFT        DIR26(-1, 0,+1)
//#define VAM_POS_BEHIND_ZLEFT_DOWN   DIR26(-1,-1,+1)
#define VAM_POS_BEHIND_DOWN         DIR26(-1,-1, 0)
//#define VAM_POS_BEHIND_ZRIGHT_DOWN  DIR26(-1,-1,-1)

#define VAM_POS_NON                 DIR26( 0, 0, 0)
#define VAM_POS_ZRIGHT              DIR26( 0, 0,-1)
#define VAM_POS_ZRIGHT_UP           DIR26( 0,+1,-1)
#define VAM_POS_UP                  DIR26( 0,+1, 0)
#define VAM_POS_ZLEFT_UP            DIR26( 0,+1,+1)
#define VAM_POS_ZLEFT               DIR26( 0, 0,+1)
#define VAM_POS_ZLEFT_DOWN          DIR26( 0,-1,+1)
#define VAM_POS_DOWN                DIR26( 0,-1, 0)
#define VAM_POS_ZRIGHT_DOWN         DIR26( 0,-1,-1)

#define VAM_POS_FRONT               DIR26(+1, 0, 0)
#define VAM_POS_FRONT_ZRIGHT        DIR26(+1, 0,-1)
//#define VAM_POS_FRONT_ZRIGHT_UP     DIR26(+1,+1,-1)
#define VAM_POS_FRONT_UP            DIR26(+1,+1, 0)
//#define VAM_POS_FRONT_ZLEFT_UP      DIR26(+1,+1,+1)
#define VAM_POS_FRONT_ZLEFT         DIR26(+1, 0,+1)
//#define VAM_POS_FRONT_ZLEFT_DOWN    DIR26(+1,-1,+1)
#define VAM_POS_FRONT_DOWN          DIR26(+1,-1, 0)
//#define VAM_POS_FRONT_ZRIGHT_DOWN   DIR26(+1,-1,-1)

namespace VioletVreath {

/**
 * VamSystem�̃J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class VamSysCamWorker2 : public GgafLib::CameraWorker {
public:
    /** �p�̕���(XYZ�v�f��0���܂܂�Ȃ��W��̕���) �� ���̗אڂ�����ӂ̕����U�� */
    static int nbhd_dir_entity_[3*3*3][6];
    static int (*nbhd_dir_)[6];
    /** �΂ߕ���(XYZ�v�f��0��1�܂܂��12��̕���) �� ���̕������猩�߂��ꍇ��(�[��)�W���� */
    static int slant_8dir_entity_[3*3*3][8];
    static int (*slant_8dir_)[8];

//////////////////////////////////////////
    //���@�ƃJ�����̔��a
    coord  cam_radius_;
    coord mv_t_x_vUP_;
    coord mv_t_y_vUP_;
    coord mv_t_z_vUP_;

    coord mv_t_x_vCAM_;
    coord mv_t_y_vCAM_;
    coord mv_t_z_vCAM_;

//    coord mv_t_x_VP_;
//    coord mv_t_y_VP_;
//    coord mv_t_z_VP_;

    dir26 pos_vam_camera_;
    dir26 pos_vam_camera_prev_;
    dir26 pos_vam_up_;
    /** [r]�J�����̕����ʒu���؂�ւ�����ipos_vam_camera_�̒l���ω������j�Ȃ��true */
    bool is_just_changed_pos_vam_cam_;
    /** [r]�J�������z�[���|�W�V�����Ɏ����߂蒆�̏ꍇ true */
    bool returning_cam_pos_;
    /** [r]�J�������z�[���|�W�V�����߂�̂ɔ�₷����(�t���[��) */
    frame returning_cam_pos_frames_;



    coord DZC_;
    coord DXC_;
    coord DX2_C_;
    coord X_P_C_;
public:
    MyShip* pMyShip_;
    GgafDxCore::GgafDxSeTransmitter* pSe_;

public:
    VamSysCamWorker2(const char* prm_name, Camera* prm_pCamera);

    static bool initStatic();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }
    inline dir26 getPosCam() {
        return pos_vam_camera_;
    }
    inline dir26 getPosUp() {
        return pos_vam_up_;
    }
    inline bool isJustChangedPosCam() {
        return is_just_changed_pos_vam_cam_;
    }
    virtual void onSwitchCameraWork() override;


    virtual ~VamSysCamWorker2(); //�f�X�g���N�^

    /**
     * �����x�N�g�����A���߂�18�����ɕϊ������ꍇ�́AXYZ���e�v�f�̐����̕������擾 .
     * @param prm_vx �����x�N�g��X�v�f
     * @param prm_vy �����x�N�g��Y�v�f
     * @param prm_vz �����x�N�g��Z�v�f
     * @param out_sgn_x X���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_y Y���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_z Z���v�f�̐��� (-1 or 0 or 1)
     */
    static void cnvVec2VamSgn(coord prm_vx, coord prm_vy, coord prm_vz,
                              int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);


    static void cnvVec2VamUpSgn(dir26 prm_vam_cam_pos,
                                coord prm_vx, coord prm_vy, coord prm_vz,
                                int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);
};

}
#endif /*VAMSYSCAMWORKER2_H_*/

