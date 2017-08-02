#ifndef HGRCAMERA_H_
#define HGRCAMERA_H_
#include "Hogera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace Hogera {

/**
 * �J�����̐��` .
 * �J�����N���X�͖{�R�[�h�̂悤�� GgafLib::DefaultHgrCamera ��
 * �p�����č쐬���ĉ������B<BR>
 * �u���̐��v���쐬����ۂɁA�����ŃJ�������K�v�ł��B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class HgrCamera : public GgafLib::DefaultCamera {

public:

    HgrCamera(const char* prm_name);

    virtual ~HgrCamera(); //�f�X�g���N�^
};

}
#endif /*HGRCAMERA_H_*/
