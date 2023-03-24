#ifndef GGAF_DX_CAMERAUPPOINT_H_
#define GGAF_DX_CAMERAUPPOINT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * ���_�i�J�������猩���ڕW�_�j��\���N���X .
 * @version 1.00
 * @since 2009/10/14
 * @author Masatoshi Tsuge
 */
class CameraViewPoint : public GeometricActor {

public:
    CameraViewPoint(const char* prm_name);

    virtual void processSettlementBehavior() override {
        _fX = C_DX(_x);
        _fY = C_DX(_y);
        _fZ = C_DX(_z);
    }

    virtual ~CameraViewPoint();
};

}
#endif /*GGAF_DX_CAMERAUPPOINT_H_*/
