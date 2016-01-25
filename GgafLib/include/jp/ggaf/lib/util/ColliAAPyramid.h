#ifndef GGAFLIB_COLLIAAPYRAMID_H_
#define GGAFLIB_COLLIAAPYRAMID_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/ColliAABox.h"

namespace GgafLib {

/**
 * �����s�̒��p�O�p��(Axis-Aligned Pyramid) �����蔻��v�f�N���X
 * �����s�̒��p�O�p���Ƃ́AAABox �̂��钸�_�̋ߗׂR���_��ʂ�ʂ�
 * �X���C�X���ďo���オ�����O�p���̎��ł��B
 * @version 1.00
 * @since 2016/01/15
 * @author Masatoshi Tsuge
 */
class ColliAAPyramid : public ColliAABox {

public:
    /** �O�p���ʒu */
    int _pos_pyramid;
    /** �O�p���Ζʖ@���x�N�g�� */
    float _s_nvx, _s_nvy, _s_nvz, _s_d;
    /** �O�p���Ζʖ@���x�N�g���̒��� */
    float _d_nv;
    /** BOX���S����Ίp���̋��� */
    coord _d_c2vtx;
    /** XY���ʂŃX���C�X�����ꍇ�̎Ζʂ̒����̌X�� */
    float _a_xy;
    /** XY���ʂŃX���C�X�����ꍇ�̎Ζʂ̒����̃��[�J�����W�ؕЁiZ��=z1�j */
    float _b_xy_z1;
    /** XY���ʂŃX���C�X�����ꍇ�̎Ζʂ̒����̃��[�J�����W�ؕЁiZ��=z2�j */
    float _b_xy_z2;

//    /** �e��(XY��,YZ��,ZX��) �Εӂ̌X�� */
//    float _a_xy[2], _a_yz[2], _a_zx[2];
//    /** �e��(XY��,YZ��,ZX��) �ؕ� */
//    float _b_xy[2], _b_yz[2], _b_zx[2];
public:
    ColliAAPyramid();

    void set(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2, int prm_pos_pyramid, bool prm_rot_x, bool prm_rot_y, bool prm_rot_z);

    virtual ~ColliAAPyramid();
};

}
#endif /*GGAFLIB_COLLIAAPYRAMID_H_*/
