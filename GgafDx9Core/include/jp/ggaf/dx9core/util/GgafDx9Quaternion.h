#ifndef GGAFDX9QUATERNION_H_
#define GGAFDX9QUATERNION_H_
namespace GgafDx9Core {

/**
 * クォータニオンクラス .
 * TODO:もっと汎用化
 * @version 1.00
 * @since 2009/04/07
 * @author Masatoshi Tsuge
 */
class GgafDx9Quaternion : public GgafCore::GgafObject {
public:
    float   _t; //虚部
    float   _x;
    float   _y;
    float   _z;

    GgafDx9Quaternion() {
        _t = 0;
        _x = 0;
        _y = 0;
        _z = 0;
    }

    GgafDx9Quaternion(float prm_t, float prm_x, float prm_y, float prm_z);
    void set(float prm_t, float prm_x, float prm_y, float prm_z) {
        _t = prm_t;
        _x = prm_x;
        _y = prm_y;
        _z = prm_z;
    }
    void mul(float t2, float x2, float y2, float z2) {
        static float t1, x1, y1, z1;
        t1 = _t;
        x1 = _x;
        y1 = _y;
        z1 = _z;

        _t = t1*t2 - x1*x2 - y1*y2 - z1*z2;
        _x = t1*x2 + t2*x1 + y1*z2 - z1*y2;
        _y = t1*y2 + t2*y1 + z1*x2 - x1*z2;
        _z = t1*z2 + t2*z1 + x1*y2 - y1*x2;
    }
    virtual ~GgafDx9Quaternion();
};

}
#endif /*GGAFDX9QUATERNION_H_*/

