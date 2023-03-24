#ifndef GGAF_LIB_QUATERNION_HPP_
#define GGAF_LIB_QUATERNION_HPP_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafLib {

/**
 * 四元数(クォータニオン)クラス .
 * @version 1.00
 * @since 2009/04/07
 * @author Masatoshi Tsuge
 */
class Quaternion : public GgafCore::Object {
public:
    /** 実部 */
    double R;
    /** 虚部 i */
    double i;
    /** 虚部 j */
    double j;
    /** 虚部 k */
    double k;

public:
    Quaternion() : GgafCore::Object() {
        R = 0;
        i = 0;
        j = 0;
        k = 0;
    }

    Quaternion(const double prm_R, const double prm_i, const double prm_j, const double prm_k) : GgafCore::Object(),
        R(prm_R),
        i(prm_i),
        j(prm_j),
        k(prm_k) {
    }


    inline void set(const double prm_R, const double prm_i, const double prm_j, const double prm_k) {
        R = prm_R;
        i = prm_i;
        j = prm_j;
        k = prm_k;
    }

    /**
     * ハミルトン積 .
     * @param t2
     * @param x2
     * @param y2
     * @param z2
     */
    inline void mul(const double a2, const double b2, const double c2, const double d2) {
        double a1 = R;
        double b1 = i;
        double c1 = j;
        double d1 = k;
        R = a1*a2 - b1*b2 - c1*c2 - d1*d2;
        i = a1*b2 + b1*a2 + c1*d2 - d1*c2;
        j = a1*c2 - b1*d2 + c1*a2 + d1*b2;
        k = a1*d2 + b1*c2 - c1*b2 + d1*a2;
    }

    inline void mul(const Quaternion& H) {
        mul(H.R, H.i, H.j, H.k);
    }

    virtual ~Quaternion() {
    }
};

}
#endif /*GGAF_LIB_QUATERNION_HPP_*/

