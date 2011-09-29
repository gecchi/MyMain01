#ifndef GGAFDXQUATERNION_H_
#define GGAFDXQUATERNION_H_
namespace GgafDxCore {

/**
 * とりあえずクォータニオンクラス .
 * TODO:もっと汎用化
 * @version 1.00
 * @since 2009/04/07
 * @author Masatoshi Tsuge
 */
class GgafDxQuaternion : public GgafCore::GgafObject {
public:
    float   _t; //虚部
    float   _x;
    float   _y;
    float   _z;

    GgafDxQuaternion() : GgafObject() {
        _t = 0;
        _x = 0;
        _y = 0;
        _z = 0;
    }

//    GgafDxQuaternion(float prm_t, float prm_x, float prm_y, float prm_z);

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
#endif /*GGAFDXQUATERNION_H_*/

