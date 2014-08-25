#ifndef SMPCAMERA_H_
#define SMPCAMERA_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"

namespace SimpleSample {

/**
 * �J�����̐��` .
 * �J�����N���X�͖{�R�[�h�̂悤�� GgafLib::DefaultCamera ��
 * �p�����č쐬���ĉ������B<BR>
 * �u���̐��v���쐬����ۂɁA�����ŃJ�������K�v�ł��B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpCamera : public GgafLib::DefaultCamera {

public:
    SmpCamera(const char* prm_name);

    virtual ~SmpCamera();
};

}
#endif /*SMPCAMERA_H_*/
