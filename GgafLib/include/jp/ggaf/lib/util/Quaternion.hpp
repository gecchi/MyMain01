#ifndef GGAF_LIB_QUATERNION_HPP_
#define GGAF_LIB_QUATERNION_HPP_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafLib {

/**
 * 四元数(クォータニオン)クラス .
 * @version 1.00
 * @since 2009/04/07
 * @author Masatoshi Tsuge
 */
template<typename T>
class Quaternion : public GgafCore::Object {
public:
    /** 実部 */
    T   R;
    /** 虚部 i */
    T   i;
    /** 虚部 j */
    T   j;
    /** 虚部 k */
    T   k;

public:
    Quaternion() : GgafCore::Object() {
        R = 0;
        i = 0;
        j = 0;
        k = 0;
    }

    Quaternion(const T prm_R, const T prm_i, const T prm_j, const T prm_k) : GgafCore::Object(),
        R(prm_R),
        i(prm_i),
        j(prm_j),
        k(prm_k) {
    }


    inline void set(const T prm_R, const T prm_i, const T prm_j, const T prm_k) {
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
    inline void mul(const T a2, const T b2, const T c2, const T d2) {
        float a1 = R;
        float b1 = i;
        float c1 = j;
        float d1 = k;
        R = a1*a2 - b1*b2 - c1*c2 - d1*d2;
        i = a1*b2 + b1*a2 + c1*d2 - d1*c2;
        j = a1*c2 - b1*d2 + c1*a2 + d1*b2;
        k = a1*d2 + b1*c2 - c1*b2 + d1*a2;
    }

    inline void mul(const Quaternion<T>& H) {
        mul(H.R, H.i, H.j, H.k);
    }

    virtual ~Quaternion() {
    }
};

}
#endif /*GGAF_LIB_QUATERNION_HPP_*/

