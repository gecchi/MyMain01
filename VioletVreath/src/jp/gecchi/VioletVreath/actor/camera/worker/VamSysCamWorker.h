#ifndef VAMSYSCAMWORKER_H_
#define VAMSYSCAMWORKER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/worker/DefaultCamWorker.h"

#define VAM_POS_BEHIND_ZRIGHT_DOWN  DIR26(-1,-1,-1) // -13 �J�����͂��̕����͎��Ȃ�
#define VAM_POS_BEHIND_DOWN         DIR26(-1,-1, 0) // -12
#define VAM_POS_BEHIND_ZLEFT_DOWN   DIR26(-1,-1,+1) // -11 �J�����͂��̕����͎��Ȃ�
#define VAM_POS_BEHIND_ZRIGHT       DIR26(-1, 0,-1) // -10
#define VAM_POS_BEHIND              DIR26(-1, 0, 0) // -9
#define VAM_POS_BEHIND_ZLEFT        DIR26(-1, 0,+1) // -8
#define VAM_POS_BEHIND_ZRIGHT_UP    DIR26(-1,+1,-1) // -7  �J�����͂��̕����͎��Ȃ�
#define VAM_POS_BEHIND_UP           DIR26(-1,+1, 0) // -6
#define VAM_POS_BEHIND_ZLEFT_UP     DIR26(-1,+1,+1) // -5  �J�����͂��̕����͎��Ȃ�
#define VAM_POS_ZRIGHT_DOWN         DIR26( 0,-1,-1) // -4
#define VAM_POS_DOWN                DIR26( 0,-1, 0) // -3
#define VAM_POS_ZLEFT_DOWN          DIR26( 0,-1,+1) // -2
#define VAM_POS_ZRIGHT              DIR26( 0, 0,-1) // -1  �����J�����ʒu
#define VAM_POS_NON                 DIR26( 0, 0, 0) //  0
#define VAM_POS_ZLEFT               DIR26( 0, 0,+1) //  1
#define VAM_POS_ZRIGHT_UP           DIR26( 0,+1,-1) //  2
#define VAM_POS_UP                  DIR26( 0,+1, 0) //  3
#define VAM_POS_ZLEFT_UP            DIR26( 0,+1,+1) //  4
#define VAM_POS_FRONT_ZRIGHT_DOWN   DIR26(+1,-1,-1) //  5   �J�����͂��̕����͎��Ȃ�
#define VAM_POS_FRONT_DOWN          DIR26(+1,-1, 0) //  6
#define VAM_POS_FRONT_ZLEFT_DOWN    DIR26(+1,-1,+1) //  7   �J�����͂��̕����͎��Ȃ�
#define VAM_POS_FRONT_ZRIGHT        DIR26(+1, 0,-1) //  8
#define VAM_POS_FRONT               DIR26(+1, 0, 0) //  9
#define VAM_POS_FRONT_ZLEFT         DIR26(+1, 0,+1) //  10
#define VAM_POS_FRONT_ZRIGHT_UP     DIR26(+1,+1,-1) //  11  �J�����͂��̕����͎��Ȃ�
#define VAM_POS_FRONT_UP            DIR26(+1,+1, 0) //  12
#define VAM_POS_FRONT_ZLEFT_UP      DIR26(+1,+1,+1) //  13  �J�����͂��̕����͎��Ȃ�

namespace VioletVreath {

/**
 * VamSystem�̃J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class VamSysCamWorker : public GgafLib::DefaultCamWorker {
public:
    /** �p�̕���(XYZ�v�f��0���܂܂�Ȃ��W��̕���) �� ���̗אڂ�����ӂ̕����U�� */
    static dir26 nbhd_dir_entity_[3*3*3][6];
    static dir26 (*nbhd_dir_)[6];
    /** �J�����̕����ieye�x�N�g��) �� ���̕������猩�߂��ꍇ��(�[��)�W���� */
    static dir26 cam_to_8dir_entity_[3*3*3][8];
    static dir26 (*cam_to_8dir_)[8];
    //���@�ƃJ�����̔��a
    static coord  cam_radius_;

    class FovInfo {
    public:
        int x_fov;
        int y_fov;
        int z_fov;
        FovInfo() {
            x_fov = 0;
            y_fov = 0;
            z_fov = 0;
        }
        void set(int prm_x_fov, int prm_y_fov, int prm_z_fov) {
            x_fov = prm_x_fov;
            y_fov = prm_y_fov;
            z_fov = prm_z_fov;
        }
    };

    /**  [���J��������][UP����] = �e���̃J�����ړ��␳�l */
    static FovInfo cam_hosei_fov_entity_[3*3*3][3*3*3];
    static FovInfo (*cam_hosei_fov_)[3*3*3];
    /**  [���J��������][UP����] = �e����VP�ړ��␳�l */
    static FovInfo vp_hosei_fov_entity_[3*3*3][3*3*3];
    static FovInfo (*vp_hosei_fov_)[3*3*3];
    /** �J��������]���������p�x */
    static double mv_ang_;
    static double mv_ang_sinHalf_;
    static double mv_ang_cosHalf_;
//////////////////////////////////////////
    coord mv_t_x_vUP_;
    coord mv_t_y_vUP_;
    coord mv_t_z_vUP_;

    coord mv_t_x_vCAM_;
    coord mv_t_y_vCAM_;
    coord mv_t_z_vCAM_;

    int cam_sgn_x_;
    int cam_sgn_y_;
    int cam_sgn_z_;
    int up_sgn_x_;
    int up_sgn_y_;
    int up_sgn_z_;
    dir26 pos_vam_camera_;
    dir26 pos_vam_camera_prev_;
    dir26 pos_vam_up_;
    dir26 pos_vam_up_prev_;
    /** [r]�J�����̕����ʒu���؂�ւ�����ipos_vam_camera_�̒l���ω������j�Ȃ��true */
    bool is_just_changed_pos_vam_cam_;
    /** [r]�J�������z�[���|�W�V�����Ɏ����߂蒆�̏ꍇ true */
    bool returning_cam_pos_;
    /** [r]�J�������z�[���|�W�V�����߂�̂ɔ�₷����(�t���[��) */
    frame returning_cam_pos_frames_;


public:
    MyShip* pMyShip_;
    GgafDx::SeTransmitter* pSe_;

public:
    VamSysCamWorker(const char* prm_name, Camera* prm_pCamera);

    static bool initStatic(Camera* prm_pCamera);

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


    virtual ~VamSysCamWorker();

    /**
     * �����x�N�g�����A���߂�18�����ɕϊ������ꍇ�́AXYZ���e�v�f�̐����̕������擾 .
     * @param prm_vx �����x�N�g��X�v�f
     * @param prm_vy �����x�N�g��Y�v�f
     * @param prm_vz �����x�N�g��Z�v�f
     * @param out_sgn_x X���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_y Y���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_z Z���v�f�̐��� (-1 or 0 or 1)
     */
    static void cnvVec2VamSgn(const coord prm_vx, const coord prm_vy, const coord prm_vz,
                              int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);


    static void cnvVec2VamUpSgn(const dir26 prm_vam_cam_pos,
                                const coord prm_vx, const coord prm_vy, const coord prm_vz,
                                int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);
};

}
#endif /*VAMSYSCAMWORKER_H_*/

