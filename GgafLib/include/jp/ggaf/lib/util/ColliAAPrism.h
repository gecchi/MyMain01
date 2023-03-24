#ifndef GGAF_LIB_COLLIAAPRISM_H_
#define GGAF_LIB_COLLIAAPRISM_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/ColliAABox.h"

namespace GgafLib {

/**
 * �����s�̒����O�p�� (Axis-Aligned Prism)�����蔻��v�f�N���X
 * �����s�̒����O�p���Ƃ́AAAB(�����s������)�̂���ʂ��A�Ίp���ŃX���C�X���P��s�������̂̎��B
 * @version 1.00
 * @since 2010/12/28
 * @author Masatoshi Tsuge
 */
class ColliAAPrism : public ColliAABox {

public:
    /** �v���Y���Εӂ̋��E���X�� */
    double _a;
    /** �v���Y���Εӂ̋��E���̐ؕ�(���[�J�����W) */
    double _b;
    /** �v���Y���ΕӖʂ̖@���x�N�g���̋t�x�N�g��X�v�f(�����蔻��v�Z�p) */
    float _vIH_x;
    /** �v���Y���ΕӖʂ̖@���x�N�g���̋t�x�N�g��Y�v�f(�����蔻��v�Z�p) */
    float _vIH_y;

public:
    ColliAAPrism();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z);

    virtual ~ColliAAPrism();
};

}
#endif /*GGAF_LIB_COLLIAAPRISM_H_*/
