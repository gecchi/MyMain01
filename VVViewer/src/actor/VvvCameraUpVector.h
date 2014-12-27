#ifndef VVVVIEWPOINT_H_
#define VVVVIEWPOINT_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultCameraUpVector.h"

namespace VVViewer {

/**
 * ���_.
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class VvvCameraUpVector : public GgafLib::DefaultCameraUpVector {
public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:

    int up_face_;

    VvvCameraUpVector(const char* prm_name);

    virtual void processBehavior() override;


    /**
     * �J������UP�ʔԍ��A�����̖ʔԍ��ɃZ�b�g���AUP�x�N�g�����X���C�h�ړ����J�n�����܂��B
     * @param prm_face_no �J������UP�ʔԍ�
     */
    void setFaceNo(int prm_face_no);


    virtual ~VvvCameraUpVector(); //�f�X�g���N�^
};


}
#endif /*VVVVIEWPOINT_H_*/
