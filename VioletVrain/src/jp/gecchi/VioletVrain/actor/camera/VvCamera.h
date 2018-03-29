#ifndef VVCAMERA_H_
#define VVCAMERA_H_
#include "VioletVrain.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace VioletVrain {

/**
 * �J�����̐��` .
 * �J�����N���X�͖{�R�[�h�̂悤�� GgafLib::DefaultVvCamera ��
 * �p�����č쐬���ĉ������B<BR>
 * �u���̐��v���쐬����ۂɁA�����ŃJ�������K�v�ł��B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvCamera : public GgafLib::DefaultCamera {

public:

    VvCamera(const char* prm_name);

    virtual ~VvCamera(); //�f�X�g���N�^
};

}
#endif /*VVCAMERA_H_*/
