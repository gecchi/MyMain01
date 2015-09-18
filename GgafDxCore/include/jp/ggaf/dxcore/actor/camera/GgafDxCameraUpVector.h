#ifndef GGAFDXCORE_GGAFDXCAMERAUPVECTOR_H_
#define GGAFDXCORE_GGAFDXCAMERAUPVECTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace GgafDxCore {

/**
 * カメラのUPのいちベクトル表すアクター .
 * 原点から自身の座標へのベクトルがカメラのUPと同期します
 * @version 1.00
 * @since 2014/12/22
 * @author Masatoshi Tsuge
 */
class GgafDxCameraUpVector : public GgafDxGeometricActor {

public:
    GgafDxCameraUpVector(const char* prm_name);

    virtual void processSettlementBehavior() override {
        _fX = C_DX(_x);
        _fY = C_DX(_y);
        _fZ = C_DX(_z);
    }

    void positionByFaceNo(dir26 prm_face_no);

    virtual ~GgafDxCameraUpVector();
};

}
#endif /*GGAFDXCORE_GGAFDXCAMERAUPVECTOR_H_*/
