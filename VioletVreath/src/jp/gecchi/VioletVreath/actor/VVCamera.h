#ifndef VVCAMERA_H_
#define VVCAMERA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"

namespace VioletVreath {


/**
 * �J����2.
 * @version 1.00
 * @since 2014/12/05
 * @author Masatoshi Tsuge
 */
class VVCamera : public GgafLib::DefaultCamera {

    coord tx_, ty_, tz_;

    static int cnvVec2FaceNo(float vx, float vy, float vz);
    static void cnvFaceNo2Vec(int face_no, float& out_vx, float& out_vy, float& out_vz);

public:

    int up_face_;
    /** [r]�J�����������x�N�g�����˂��h����ʔԍ� */
    int vcv_face_;
    /** [r]�J�����������x�N�g�����˂��h����ʔԍ� */
    int vcv_face_prev_;

    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** [r]�J������UP�x�N�g���ɃR�s�[����ē��������x�N�g�����W�̃A�N�^�[ */
    GgafLib::DefaultGeometricActor* pUp_;
    /** [r]pUp_�����炩�Ɉړ������邽�߂̃w���p�[ */
    GgafDxCore::GgafDxAxesMover* pAxsMver_Up_;

    VVCamera(const char* prm_name);

    GgafDxCore::GgafDxCameraViewPoint* createViewPoint() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    /**
     * �J���������_�x�N�g���̖ʔԍ����擾���܂� .
     * @return �J���������_�x�N�g���̖ʔԍ�(1�`6)
     */
    int getCamToVpFaceNo();

    /**
     * �J������UP��ݒ�AUP�x�N�g�����X���C�h�ړ����J�n�����܂��B
     * @param tx �J������UP�x�N�g��X�v�f�^�[�Q�b�g
     * @param ty �J������UP�x�N�g��Y�v�f�^�[�Q�b�g
     * @param tz �J������UP�x�N�g��Z�v�f�^�[�Q�b�g
     * @param t �X���C�h�ړ����v����
     */
    void slideUpCamTo(coord tx, coord ty, coord tz, frame t);

    /**
     * �J������UP��ʔԍ��Őݒ�AUP�x�N�g�����X���C�h�ړ����J�n�����܂��B
     * @param prm_face_no �J������UP�ʔԍ�
     * @param prm_t �X���C�h�ړ����v����
     */
    void slideUpCamTo(int prm_face_no, frame prm_t);

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
    virtual ~VVCamera(); //�f�X�g���N�^
};

}
#endif /*VVCAMERA_H_*/
