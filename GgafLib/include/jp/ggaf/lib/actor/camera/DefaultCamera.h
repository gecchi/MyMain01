#ifndef GGAFLIB_DEFAULTCAMERA_H_
#define GGAFLIB_DEFAULTCAMERA_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCamera.h"

namespace GgafLib {

/**
 * �W���̃J����.
 * @version 1.00
 * @since 2010/10/22
 * @author Masatoshi Tsuge
 */
class DefaultCamera : public GgafDxCore::GgafDxCamera {

public:
    coord tx_, ty_, tz_;

public:
    DefaultCamera(const char* prm_name, double prm_rad_fovX, double prm_dep);
    DefaultCamera(const char* prm_name, double prm_rad_fovX);
    DefaultCamera(const char* prm_name);

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual GgafDxCore::GgafDxCameraViewPoint* createCameraViewPoint() override;

    virtual GgafDxCore::GgafDxCameraUpVector* createCameraUpVector() override;
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
    void slideMvTo(coord tx, coord ty, coord tz, frame t);

    void slideMvTo(coord tx, coord ty, coord tz, frame t,
                   float prm_x_p1, float prm_y_p1, float prm_z_p1);
    /**
     * �J�������w�̃A�N�^�[�̈ʒu�Ɋ��炩�ړ������܂��B .
     * @param pTarget
     * @param t ���v�t���[��
     */
    void slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);
    void slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t,
            float prm_x_p1, float prm_y_p1, float prm_z_p1);

    bool isSliding();

    virtual ~DefaultCamera(); //�f�X�g���N�^
};

}
#endif /*GGAFLIB_DEFAULTCAMERA_H_*/
