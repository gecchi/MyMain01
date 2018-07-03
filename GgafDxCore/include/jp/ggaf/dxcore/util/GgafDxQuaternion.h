#ifndef GGAFDXCORE_GGAFDXQUATERNION_H_
#define GGAFDXCORE_GGAFDXQUATERNION_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * �l����(�N�H�[�^�j�I��)�N���X .
 * @version 1.00
 * @since 2009/04/07
 * @author Masatoshi Tsuge
 */
class GgafDxQuaternion : public GgafCore::GgafObject {
public:
    /** ���� */
    float   R;
    /** ���� i */
    float   i;
    /** ���� j */
    float   j;
    /** ���� k */
    float   k;

public:
    GgafDxQuaternion() : GgafObject() {
        R = 0;
        i = 0;
        j = 0;
        k = 0;
    }

    GgafDxQuaternion(const float prm_R, const float prm_i, const float prm_j, const float prm_k) : GgafObject(),
        R(prm_R),
        i(prm_i),
        j(prm_j),
        k(prm_k) {
    }


    inline void set(const float prm_R, const float prm_i, const float prm_j, const float prm_k) {
        R = prm_R;
        i = prm_i;
        j = prm_j;
        k = prm_k;
    }

    /**
     * �n�~���g���� .
     * @param t2
     * @param x2
     * @param y2
     * @param z2
     */
    inline void mul(const float a2, const float b2, const float c2, const float d2) {
        float a1 = R;
        float b1 = i;
        float c1 = j;
        float d1 = k;
        R = a1*a2 - b1*b2 - c1*c2 - d1*d2;
        i = a1*b2 + b1*a2 + c1*d2 - d1*c2;
        j = a1*c2 - b1*d2 + c1*a2 + d1*b2;
        k = a1*d2 + b1*c2 - c1*b2 + d1*a2;
    }

    inline void mul(const GgafDxQuaternion& H) {
        mul(H.R, H.i, H.j, H.k);
    }

    virtual ~GgafDxQuaternion();
};

}
#endif /*GGAFDXCORE_GGAFDXQUATERNION_H_*/

