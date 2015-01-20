#ifndef CAMERA_H_
#define CAMERA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"

namespace VioletVreath {

/**
 * �J����.
 * @version 1.00
 * @since 2010/10/22
 * @author Masatoshi Tsuge
 */
class Camera : public GgafLib::DefaultCamera {

    coord tx_, ty_, tz_;

public:

    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    Camera(const char* prm_name);

    GgafDxCore::GgafDxCameraViewPoint* createCameraViewPoint() override;

    GgafDxCore::GgafDxCameraUpVector* createCameraUpVector() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    /**
     * �J���������_�x�N�g�����˂��h����ʔԍ����擾���܂� .
     * @return �J���������_�x�N�g�����˂��h����ʔԍ�(1�`26)
     */
    face26 getVpFaceNo();

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
    virtual ~Camera(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
