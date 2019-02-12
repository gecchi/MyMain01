#ifndef GGAF_DX_CAMERAUPVECTOR_H_
#define GGAF_DX_CAMERAUPVECTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * カメラのUPのいちベクトル表すアクター .
 * 原点から自身の座標へのベクトルがカメラのUPと同期します
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
