#ifndef GGAF_LIB_DEFAULTCAMERA_H_
#define GGAF_LIB_DEFAULTCAMERA_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/camera/Camera.h"

namespace GgafLib {

/**
 * �W���̃J����.
 * @version 1.00
 * @since 2010/10/22
 * @author Masatoshi Tsuge
 */
class DefaultCamera : public GgafDx::Camera {

public:
    coord tx_, ty_, tz_;

public:
    DefaultCamera(const char* prm_name, double prm_rad_fovX, double prm_dep);
    DefaultCamera(const char* prm_name, double prm_rad_fovX);
    DefaultCamera(const char* prm_name);

    virtual void processJudgement() override {
    }

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual GgafDx::CameraViewPoint* createCameraViewPoint() override;

    virtual GgafDx::CameraUpVector* createCameraUpVector() override;
    virtual void initialize() override;

    virtual void processBehavior() override;

    /**
     * �J���������_�x�N�g�����˂��h����ʔԍ����擾���܂� .
     * @return �J���������_�x�N�g�����˂��h����ʔԍ�(1�`26)
     */
    dir26 getVpDirNo();

    /**
     * �J�������w��ʒu�Ɋ��炩�ړ������܂��B .
     * @param tx
     * @param ty
     * @param tz
     * @param t ���v�t���[��
     */
    void slideMvTo(coord tx, coord ty, coord tz, frame t, double prm_p1, double prm_p2);
    void slideMvTo(coord tx, coord ty, coord tz, frame t, double prm_x_p1, double prm_y_p1, double prm_z_p1);

    /**
     * �J�������w�̃A�N�^�[�̈ʒu�Ɋ��炩�ړ������܂��B .
     * @param pTarget
     * @param t ���v�t���[��
     */
    void slideMvTo(GgafDx::GeometricActor* pTarget, frame t, double prm_p1, double prm_p2);
    void slideMvTo(GgafDx::GeometricActor* pTarget, frame t, double prm_x_p1, double prm_y_p1, double prm_z_p1);

    bool isSliding();

    virtual ~DefaultCamera();
};

}
#endif /*GGAF_LIB_DEFAULTCAMERA_H_*/
