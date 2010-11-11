#ifndef MYSHIPDIVINGCAMWORKER_H_
#define MYSHIPDIVINGCAMWORKER_H_

namespace MyStg2nd {

/**
 * �X�e�[�W�˓����̃J�����}�� .
 * @version 1.00
 * @since 2010/11/11
 * @author Masatoshi Tsuge
 */
class MyShipDivingCamWorker : public CameraWorker {

public:
    MyShip* _pMyShip;

    /** ���_���珉���J����Z�ʒu�̋��� */
    int _dZ_camera_init;
    //�J�����̈ړ��ڕW���W
    int _move_target_X_CAM, _move_target_Y_CAM, _move_target_Z_CAM;
    //�J�����̃r���[�|�C���g�̈ړ��ڕW���W
    int _move_target_X_VP, _move_target_Y_VP, _move_target_Z_VP;
    //�J�����̖ڕWUP�A���O���l
    angle _move_target_XY_CAM_UP;
    angle _angXY_nowCamUp;

    /** �J�����̍ō����x�i����A�����ŉ����j */
    int _cam_velo_renge;
    /** �J�����̑��x���A���x���@�̒ʏ�ړ����x��1.0�{�ƂȂ�J�����ڕW���W����̋����B */
    int _stop_renge; //�J�����ڕW���W�������A�����菬�����ƁA     1.0�{��茸
                     //�J�����ڕW���W�������A������傫���Ƃ����� 1.0�{��蒴


    MyShipDivingCamWorker(const char* prm_name);

    virtual void initialize() override;



    virtual void onPushed() override {
    }

    virtual void onPoped() override {
    }

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }
    void setMoveTargetCamBy(GgafDx9Core::GgafDx9GeometricActor* pTarget);
    void setMoveTargetCamVpBy(GgafDx9Core::GgafDx9GeometricActor* pTarget);
    void setMoveTargetCam(int X, int Y, int Z);
    void setMoveTargetCamVp(int X, int Y, int Z);

    virtual ~MyShipDivingCamWorker(); //�f�X�g���N�^
};

}
#endif /*MYSHIPDIVINGCAMWORKER_H_*/
