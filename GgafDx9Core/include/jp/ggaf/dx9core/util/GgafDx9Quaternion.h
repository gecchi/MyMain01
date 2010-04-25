#ifndef GGAFDX9QUATERNION_H_
#define GGAFDX9QUATERNION_H_
namespace GgafDx9Core {

/**
 * とりあえずクォータニオンクラス .
 * TODO:もっと汎用化
 * @version 1.00
 * @since 2009/04/07
 * @author Masatoshi Tsuge
 */
class GgafDx9Quaternion : public GgafCore::GgafObject {
public:
    double   _t; //虚部
    double   _x;
    double   _y;
    double   _z;

    GgafDx9Quaternion() {
        _t = 0;
        _x = 0;
        _y = 0;
        _z = 0;
    }

    GgafDx9Quaternion(double prm_t, double prm_x, double prm_y, double prm_z);
    void set(double prm_t, double prm_x, double prm_y, double prm_z) {
        _t = prm_t;
        _x = prm_x;
        _y = prm_y;
        _z = prm_z;
    }
    void mul(double t2, double x2, double y2, double z2) {
        static double t1, x1, y1, z1;
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

