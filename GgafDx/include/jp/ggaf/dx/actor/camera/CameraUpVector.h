#ifndef GGAF_DX_CAMERAUPVECTOR_H_
#define GGAF_DX_CAMERAUPVECTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * �J������UP�̂����x�N�g���\���A�N�^�[ .
 * ���_���玩�g�̍��W�ւ̃x�N�g�����J������UP�Ɠ������܂�
 * @version 1.00
 * @since 2014/12/22
 * @author Masatoshi Tsuge
 */
class CameraUpVector : public GeometricActor {

public:
    CameraUpVector(const char* prm_name);

    virtual void processSettlementBehavior() override {
        _fX = C_DX(_x);
        _fY = C_DX(_y);
        _fZ = C_DX(_z);
    }

    virtual ~CameraUpVector();
};

}
#endif /*GGAF_DX_CAMERAUPVECTOR_H_*/
