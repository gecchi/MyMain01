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
    /** �Ίp���ƎΖʂ̌�_ */
    coord _l_px, _l_py, _l_pz;

    double _rad_xy;
    double _rad_yz;
    double _rad_zx;
public:
    ColliAAPyramid();

    void set(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2, int prm_pos_pyramid, bool prm_rot_x, bool prm_rot_y, bool prm_rot_z);

    virtual ~ColliAAPyramid();
};

}
#endif /*GGAFLIB_COLLIAAPYRAMID_H_*/
