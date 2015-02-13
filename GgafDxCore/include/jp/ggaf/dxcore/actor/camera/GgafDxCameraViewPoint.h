#ifndef GGAFDXCORE_GGAFDXCAMERAUPPOINT_H_
#define GGAFDXCORE_GGAFDXCAMERAUPPOINT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace GgafDxCore {

/**
 * カメラの視点の目標点クラス.
 * @version 1.00
 * @since 2009/10/14
 * @author Masatoshi Tsuge
 */
class GgafDxCameraViewPoint : public GgafDxGeometricActor {

public:
    GgafDxCameraViewPoint(const char* prm_name);

    virtual void processSettlementBehavior() override {
        _fX = C_DX(_x);
        _fY = C_DX(_y);
        _fZ = C_DX(_z);
    }

    virtual ~GgafDxCameraViewPoint();
};

}
#endif /*GGAFDXCORE_GGAFDXCAMERAUPPOINT_H_*/
