#ifndef VVVCAMERA_H_
#define VVVCAMERA_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"

namespace VVViewer {

/**
 * VVViewer�̃J���� .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCamera : public GgafLib::DefaultCamera {

    /** �J������UP�v�f�x�N�g���̖ʔԍ��ƁA�����̔��΃x�N�g���̖ʔԍ��Ƃ̊֘A�e�[�u�� */
    int relation_up_vec_[3*3*3][3*3*3];

public:
    int vcv_face_;
    int vcv_face_prev_;

    /** ����UP����@�\���ꎞ�I��OFF�ɂ���t���[�� */
    frame auto_up_wait_frames;

    /** relation_up_vec_�A�N�Z�X�p */
    int (*relation_up_by_vec_)[3*3*3];


    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    VvvCamera(const char* prm_name);

    GgafDxCore::GgafDxCameraUpVector* createCameraUpVector() override;
    GgafDxCore::GgafDxCameraViewPoint* createCameraViewPoint() override;

    virtual void initialize() override;

    void processBehavior() override;


    /**
     * �J���������_�x�N�g�����˂��h����̖ʔԍ����擾���܂� .
     * @return �J���������_�x�N�g�����˂��h����ʔԍ�
     */
    int getCamToVpFaceNo();


    /**
     * �J�������w��ʒu�Ɋ��炩�ړ������܂��B .
     * @param tx
     * @param ty
     * @param tz
     * @param t ���v�t���[��
     */
    void slideMvTo(coord tx, coord ty, coord tz, frame t);

    /**
     * �J�������w�̃A�N�^�[�̈ʒu�Ɋ��炩�ړ������܂��B .
     * @param pTarget
     * @param t ���v�t���[��
     */
    void slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);


    virtual ~VvvCamera();
};

}
#endif /*VVVCAMERAH_*/
