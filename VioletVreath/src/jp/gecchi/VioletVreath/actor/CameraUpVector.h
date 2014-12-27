#ifndef CAMERAUPVECTOR_H_
#define CAMERAUPVECTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultCameraUpVector.h"

namespace VioletVreath {

/**
 * �J�����̏�̈ʒu�x�N�g�� .
 * @version 1.00
 * @since 2014/12/24
 * @author Masatoshi Tsuge
 */
class CameraUpVector : public GgafLib::DefaultCameraUpVector {
public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:

    int up_face_;

    CameraUpVector(const char* prm_name);

    virtual void processBehavior() override;


    /**
     * �J������UP�ʔԍ��A�����̖ʔԍ��ɃZ�b�g���AUP�x�N�g�����X���C�h�ړ����J�n�����܂��B
     * @param prm_face_no �J������UP�ʔԍ�
     */
    void setFaceNo(int prm_face_no);


    virtual ~CameraUpVector(); //�f�X�g���N�^
};


}
#endif /*CAMERAUPVECTOR_H_*/
