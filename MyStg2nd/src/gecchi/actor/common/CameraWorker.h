#ifndef CAMERAWORKER_H_
#define CAMERAWORKER_H_



namespace MyStg2nd {

/**
 * �J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class CameraWorker : public GgafCore::GgafMainActor {

public:
    /** �J�����ʒu�ԍ� */
    int _pos_camera;

    GgafDxCore::GgafDxGeometricActor* _pLockOnTarget;

    /** ���_���珉���J����Z�ʒu�̋��� */
    coord _dZ_camera_init;
    //�J�����̈ړ��ڕW���W
    coord _move_target_X_CAM, _move_target_Y_CAM, _move_target_Z_CAM;
    //�J�����̃r���[�|�C���g�̈ړ��ڕW���W
    coord _move_target_X_VP, _move_target_Y_VP, _move_target_Z_VP;
    //�J�����̖ڕWUP�A���O���l
    angle _move_target_XY_CAM_UP;
    angle _angXY_nowCamUp;

    /** �J�����̍ō����x�i����A�����ŉ����j */
    velo _cam_velo_renge;
    /** �J�����̑��x���A���x���@�̒ʏ�ړ����x��1.0�{�ƂȂ�J�����ڕW���W����̋����B */
    coord _stop_renge; //�J�����ڕW���W�������A�����菬�����ƁA     1.0�{��茸
                     //�J�����ڕW���W�������A������傫���Ƃ����� 1.0�{��蒴

    /** �����Ńu���Ȃ��X�s�[�h */
    velo _burenai_speed;

    CameraWorker(const char* prm_name);

    virtual void initialize() override {
    }

    virtual void onSwitchCameraWork();

    virtual void onUndoCameraWork();

    virtual void onSwitchToOherCameraWork();

    virtual void onCameBackFromOtherCameraWork();



    virtual void processBehavior() override;

    virtual void processJudgement() override {

    }

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }
    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }
    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }


    void setMoveTargetCamBy(GgafDxCore::GgafDxGeometricActor* pTarget);
    void setMoveTargetCamVpBy(GgafDxCore::GgafDxGeometricActor* pTarget);
    void setMoveTargetCam(coord X, coord Y, coord Z);
    void setMoveTargetCamVp(coord X, coord Y, coord Z);
    void lockCamVp(GgafDxCore::GgafDxGeometricActor* pTarget);

    void unlockCamVp();
    virtual ~CameraWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
