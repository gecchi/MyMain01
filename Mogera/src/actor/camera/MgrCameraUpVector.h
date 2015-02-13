#ifndef MGRCAMERAUPVECTOR_H_
#define MGRCAMERAUPVECTOR_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"

namespace Mogera {

/**
 * �J�����̏�̈ʒu�x�N�g�� .
 * @version 1.00
 * @since 2014/12/24
 * @author Masatoshi Tsuge
 */
class MgrCameraUpVector : public GgafLib::DefaultCameraUpVector {
public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:

    face26 up_face_;

    MgrCameraUpVector(const char* prm_name);

    virtual void processBehavior() override;


    /**
     * �J������UP�ʔԍ��A�����̖ʔԍ��ɃZ�b�g���AUP�x�N�g�����X���C�h�ړ����J�n�����܂��B
     * @param prm_face_no �J������UP�ʔԍ�
     */
    void moveTo(face26 prm_face_no, frame prm_spent);


    virtual ~MgrCameraUpVector(); //�f�X�g���N�^
};


}
#endif /*MGRCAMERAUPVECTOR_H_*/
