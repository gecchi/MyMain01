#ifndef MGRCAMERA_H_
#define MGRCAMERA_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace Mogera {

/**
 * �J�����̐��` .
 * �J�����N���X�͖{�R�[�h�̂悤�� GgafLib::DefaultMgrCamera ��
 * �p�����č쐬���ĉ������B<BR>
 * �u���̐��v���쐬����ۂɁA�����ŃJ�������K�v�ł��B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrCamera : public GgafLib::DefaultCamera {

public:

    MgrCamera(const char* prm_name);

    GgafDxCore::GgafDxCameraViewPoint* createCameraViewPoint() override;

    GgafDxCore::GgafDxCameraUpVector* createCameraUpVector() override;

    virtual ~MgrCamera(); //�f�X�g���N�^
};

}
#endif /*MGRCAMERA_H_*/
