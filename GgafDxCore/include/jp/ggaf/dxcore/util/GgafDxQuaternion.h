#ifndef GGAFDXCORE_GGAFDXQUATERNION_H_
#define GGAFDXCORE_GGAFDXQUATERNION_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * とりあえず四元数(クォータニオン)クラス .
 * @version 1.00
 * @since 2009/04/07
 * @author Masatoshi Tsuge
 */
class GgafDxQuaternion : public GgafCore::GgafObject {
public:
    /** スカラー部 */
    float   _t;
    /** 虚部 i */
    float   _x;
    /** 虚部 j */
    float   _y;
    /** 虚部 k */
    float   _z;

public:
    GgafDxQuaternion() : GgafObject() {
        _t = 0;
        _x = 0;
        _y = 0;
        _z = 0;
    }

    GgafDxQuaternion(float prm_t, float prm_x, float prm_y, float prm_z) : GgafObject(),
        _t(prm_t),
        _x(prm_x),
        _y(prm_y),
        _z(prm_z) {
    }


    inline void set(float prm_t, float prm_x, float prm_y, float prm_z) {
        _t = prm_t;
        _x = prm_x;
        _y = prm_y;
        _z = prm_z;
    }

    /**
     * ハミルトン積 .
     * @param t2
     * @param x2
     * @param y2
     * @param z2
     */
    inline void mul(float t2, float x2, float y2, float z2) {
        float t1 = _t;
        float x1 = _x;
        float y1 = _y;
        float z1 = _z;
        _t = t1*t2 - x1*x2 - y1*y2 - z1*z2;
        _x = t1*x2 + t2*x1 + y1*z2 - z1*y2;
        _y = t1*y2 + t2*y1 + z1*x2 - x1*z2;
        _z = t1*z2 + t2*z1 + x1*y2 - y1*x2;
    }
    virtual ~GgafDxQuaternion();
};

}
#endif /*GGAFDXCORE_GGAFDXQUATERNION_H_*/

