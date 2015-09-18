#ifndef CAMERAUPVECTOR_H_
#define CAMERAUPVECTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"

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

    dir26 up_dir_;

    CameraUpVector(const char* prm_name);

    virtual void processBehavior() override;


    /**
     * �J������UP�ʔԍ��A�����̖ʔԍ��ɃZ�b�g���AUP�x�N�g�����X���C�h�ړ����J�n�����܂��B
     * @param prm_face_no �J������UP�ʔԍ�
     */
    void moveTo(dir26 prm_dir_no, frame prm_spent);
    void moveTo(coord tx, coord ty, coord tz, frame prm_spent);

    virtual ~CameraUpVector(); //�f�X�g���N�^
};


}
#endif /*CAMERAUPVECTOR_H_*/
