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
public:
    coord tx_, ty_, tz_;
    int vcv_face_;
    int vcv_face_prev_;
    static int cnvVec2FaceNo(float vx, float vy, float vz);
    static void cnvFaceNo2Vec(int face_no, float& out_vx, float& out_vy, float& out_vz);

    int up_face_;
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** �J������UP�x�N�g���p�A�N�^�[ */
    GgafLib::DefaultGeometricActor* pUp_;
    /** pUp_ �̕��s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_Up_;

public:


    VvvCamera(const char* prm_name);
    GgafDxCore::GgafDxCameraViewPoint* createViewPoint() override;

    virtual void initialize() override;
    void processBehavior() override;


    /**
     * �J���������_�x�N�g�����˂��h����̖ʔԍ����擾���܂� .
     * @return �J���������_�x�N�g�����˂��h����ʔԍ�
     */
    int getCamToVpFaceNo();

    /**
     * �J������UP�ʔԍ��A�����̖ʔԍ��ɃZ�b�g���AUP�x�N�g�����X���C�h�ړ����J�n�����܂��B
     * @param prm_face_no �J������UP�ʔԍ�
     */
    void slideUpCamTo(int prm_face_no);

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
