#ifndef GGAF_CORE_LINEAROCTREE_H_
#define GGAF_CORE_LINEAROCTREE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/util/lineartree/LinearTree.hpp"

namespace GgafCore {

#define MAX_OCTREE_LEVEL 8

/**
 * ���`�����؃N���X .
 * ���`�����؂Ƃ́A�����؋�ԕ�����@�̊e��Ԃ��A���̔z��(���`)�ɕ��ׂ���Ԃ��Ӗ����܂��B
 * �{�N���X�ł̗p������̂悤�ɒ�߂鎖�Ƃ���B
 * ���̐}���R�����gAA�ŕ\���ł��Ȃ����߁A4���؂̐}���Ɍ��t�̐������邪�B�{�N���X�̋@�\�͗��̂̔����؂ł��B
 * <pre><code>
 *  +-----------+
 *  |           |
 *  |           |
 *  |     0     |
 *  |           |   Lv0 ���
 *  |           |
 *  |           |
 *  +-----------+
 *
 *  +-----+-----+
 *  |     |     |
 *  |  0  |  1  |
 *  |     |     |
 *  +-----+-----+   Lv1 ���
 *  |     |     |
 *  |  2  |  3  |
 *  |     |     |
 *  +-----+-----+
 *
 *  +--+--+--+--+
 *  | 0| 1| 4| 5|
 *  +--+--+--+--+
 *  | 2| 3| 6| 7|
 *  +--+--+--+--+   Lv2 ���
 *  | 8| 9|12|13|
 *  +--+--+--+--+
 *  |10|11|14|15|
 *  +--+--+--+--+
 * </code></pre>
 * <BR>
 * <B>�p���`</B>
 * <BR>
 * <B>�����[�g��������</B><BR>
 * Z���̂悤�ȏ��ԂŔԍ���U���@���Ԃ��w�����t�B
 * 4���؂ł͕��ʂ�4����������A�E��A�����A�E���̏����ŐU��u��@�v�̎��B<BR>
 * 8���؂ł͗��̋�ԁi�����́j��8�����AZ��*2��Ŕԍ���U��u��@�v�̎����w���B<BR>
 * <BR>
 * <B>����ԃ��x����</B><BR>
 * ��L�}�̉E�ɏ����Ă���A�e��Ԃ̃��x�����w���B<BR>
 * <BR>
 * <B>�����[�g�������ʂ��ԍ��A��Ԕԍ���</B><BR>
 * ��L�}�̊eLevel��ԂɐU���Ă��镪����Ԃ̔ԍ��̂��Ƃ��w�����Ƃ���B<BR>
 * ��L�}�̗�ł�Lv1��Ԃ̃��[�g�������ʂ��ԍ��� 0�`3�ALv2��Ԃ̃��[�g�������ʂ��ԍ���0�`15 �Ƃ����悤�Ɏg���B<BR>
 * ���ۂ͔����؂ŗ��̂Ȃ̂ŁBLv1��ԃ��[�g�������ʂ��ԍ���0�`7�ALv2��ԃ��[�g�������ʂ��ԍ���0�`63 �ɂȂ�B<BR>
 * <BR>
 * <B>���q��ԁA�e��ԁB�i�q���x���A�e���x���j��</B><BR>
 * �����ԃ��x���� +1 ���q��ԁA�����ԃ��x���� -1 ��e��ԂƌĂԂ��Ƃɂ���B<BR>
 * <BR>
 * <B>���q����ԁ�</B><BR>
 * �����ԃ��x���� +1�`���[���x���̋�Ԃ��ׂĂ��q����ԂƌĂԂ��Ƃɂ���B<BR>
 * <BR>
 * <B>�����[�g�������ʒu��</B><BR>
 * �����Ԃ�4�������A����A�E��A�����A�E����
 * ���ꂼ�� 0 1 2 3 (8���؂ł� 0�`7)�ƕ\���������ꍇ������A
 * ���� 0 1 2 3 �̎������[�g�������ʒu�ƌĂԂ��ƂƂ���B<BR>
 * <BR>
 * <B>�����(�z��)�v�f�ԍ���</B><BR>
 * ��Ԕԍ��ɑΉ�������`�z��̃C���f�b�N�X���w���B<BR>
 * ��̓I�ɂ� _paNodeSpaceArray �̗v�f�ԍ��B<BR>
 * <BR>
 *
 *  <B>�y��P�z</B><BR>
 *  Lv2 ��Ԃ� ���[�g�������ʒu 2 �̋�ԂƂ�����
 *  <pre><code>
 *  +--+--+
 *  | 8| 9|
 *  +--+--+
 *  |10|11|
 *  +--+--+
 *  </code></pre>
 *  ���w�����ƂƂ���B<BR>
 *
 *  <B>�y��Q�z</B><BR>
 *  �uLv1��Ԃ̋�Ԕԍ�3�̎q��Ԃ̃��[�g�������ʒu2�v�ƕ\�������ꍇ�́A
 *  Lv1�̋�Ԕԍ�3�̎q��ԁ�Lv2��Ԃ��S���������̉E��
 *  <pre><code>
 *  +--+--+
 *  |12|13|
 *  +--+--+
 *  |14|15|
 *  +--+--+
 *  </code></pre>
 *  �̂��Ƃ��w���A����̃��[�g�������ʒu2�Ȃ̂ŁALv2��ԃ��[�g�������ʂ��ԍ�<B>14</B>���w���Ă邱�ƂƂ���B<BR>
 *  �y���̑��g�p��z<BR>
 *  �ELv1 ��Ԃ̃��[�g�������ʒu 1 �� Lv2 ��Ԃ̋�Ԕԍ� 4 5 6 7 �ɓ�����B<BR>
 *  �ELv2 ��Ԕԍ� 13 �́A�e��Ԃ̃��[�g�������ʒu 3 �ɑ��݂���B<BR>
 *  �Ƃ����悤�ɕ\�������肷��i�ƒ�`����j�B<BR>
 * <BR>
 * �y�ӎ��z<BR>
 * �{�v���O�����́A<BR>
 * �u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html<BR>
 * �T�C�g���R���e���c�� �u����15 8���؋�ԕ������œK������I�v http://marupeke296.com/COL_3D_No15_Octree.html<BR>
 * �̋L�����Q�l�Ɂi�Ƃ������w�ǂ��̂܂܁j�쐬���Ă��܂��B<BR>
 * �ڂ���؂̔��ɉ���₷������Ɋ��ӂ������܂��B<BR>
 * <BR>
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class LinearOctree : public LinearTree<3> {

private:
    /**
     * �����̍��W�C���f�b�N�X�ɑΉ�����A�ő僌�x���̋�ԁi��������Ȃ��ł��[����ԁj�ł̃��[�g�������̒ʂ���Ԕԍ��擾 .
     * ����Ă��邱�Ƃ�<BR>
     * �E���������ꂼ��3bit���ƂɊԊu���J����<BR>
     * �E����2�̌��ʂ�1�r�b�g�A����2�̌��ʂ�2�r�b�g  ���炵�� OR �����<BR>
     * �ȏ�B<BR>
     * <BR>
     * �}������ƁA�܂�
     * <pre><code>
     * 000000000000000000000000abcdefgh ,
     * 000000000000000000000000ijklmnop ,
     * 000000000000000000000000qrstuvwx
     * ��
     * 00000000 00a 00b 00c 00d 00e 00f 00g 00h  --> X�������
     * 00000000 0i0 0j0 0k0 0l0 0m0 0n0 0o0 0p0  --> Y�������
     * 00000000 q00 r00 s00 t00 u00 v00 w00 x00  --> Z�������
     * �������āAOR��������(���̌���)���߂�l�ɂȂ�B�Ӗ��́A
     * 00000000 qia rjb skc tld ume vnf wog xph
     *                                      ^^^-->&B(xph)       = ����Level�̋�Ԃ̃��[�g�������ʂ���Ԕԍ� 0�`7
     *                                  ^^^^^^^-->&B(wogxph)    = ����Level�̐e��Ԃ̃��[�g�������ʂ���Ԕԍ� 0�`63
     *                              ^^^^^^^^^^^-->&B(vnfwogxph) = ����Level�̐e�̐e��Ԃ̃��[�g�������ʂ���Ԕԍ� 0�`511
     *                          ^^^ ^^^ ^^^ ^^^
     *                           |   |   |   |
     *                           |   |   |   &B(xph) = ����Level�̋�Ԃ̃��[�g�������̈ʒu 0�`7
     *             ............  |   |   `---&B(wog) = ����Level�̐e��Ԃ̃��[�g�������̈ʒu  0�`7
     *                           |   `-------&B(vnf) = ����Level�̐e�̐e�̋�Ԃ̃��[�g�������̈ʒu 0�`7
     * </code></pre>
     * @param x_space_index ����̃��x����Ԃ�x���W��ԃC���f�b�N�X (������ 0�`255 �Ƃ���)
     * @param y_space_index ����̃��x����Ԃ�y���W��ԃC���f�b�N�X (������ 0�`255 �Ƃ���)
     * @param z_space_index ����̃��x����Ԃ�z���W��ԃC���f�b�N�X (������ 0�`255 �Ƃ���)
     * @return ����Levell��Ԃ�(x_index, y_index, z_index)�Ŏ�������ԂɑΉ�����
     *         �����؃��[�g�������̒ʂ���Ԕԍ�(�ő�Level8�ŁA0�`23068671)
     */
    static inline uint32_t getMortonOrderNumFromXYZindex( uint32_t x_space_index, uint32_t y_space_index, uint32_t z_space_index ) {
        return LinearOctree::separateEveryThreeBit(x_space_index)    |
               LinearOctree::separateEveryThreeBit(y_space_index)<<1 |
               LinearOctree::separateEveryThreeBit(z_space_index)<<2;
    }


    /**
     * 3bit���ƂɊԊu���J���� .
     * <pre><code>
     * 000000000000000000000000abcdefgh  ��
     * 0000000000a00b00c00d00e00f00g00h  �ɂ��܂�
     * ���A���S���Y����
     * n          = 0000 0000 0000 0000 0000 0000 abcd efgh �̂Ƃ�
     * n<<8       = 0000 0000 0000 0000 abcd efgh 0000 0000
     * n|n<<8     = 0000 0000 0000 0000 abcd efgh abcd efgh
     * 0x0000f00f = 0000 0000 0000 0000 1111 0000 0000 1111 �ł���̂�
     * (n|n<<8) & 0x0000f00f =
     *              0000 0000 0000 0000 abcd 0000 0000 efgh �ƂȂ�B
     * ���̌��ʂ��܂� n �ɑ������
     * n          = 0000 0000 0000 0000 abcd 0000 0000 efgh
     * �ȉ����l��
     * n<<4       = 0000 0000 0000 abcd 0000 0000 efgh 0000
     * n|n<<4     = 0000 0000 0000 abcd abcd 0000 efgh efgh
     * 0x000c30c3 = 0000 0000 0000 1100 0011 0000 1100 0011
     * n �� (n|n<<4) & 0x000c30c3 =
     *              0000 0000 0000 ab00 00cd 0000 ef00 00gh
     * n<<2       = 0000 0000 00ab 0000 cd00 00ef 0000 gh00
     * n|n(n<<2)  = 0000 0000 00ab ab00 cdcd 00ef ef00 ghgh
     * 0x00249249 = 0000 0000 0010 0100 1001 0010 0100 1001
     * n �� (n|n<<2) & 0x00249249 =
     *              0000 0000 00a0 0b00 c00d 00e0 0f00 g00h
     * </code></pre>
     * @param n 0�`255�܂ł̐��l
     * @return 3bit���ƂɊԊu���󂯂�ꂽ�l
     */
    static inline uint32_t separateEveryThreeBit(uint32_t n) {
        n = ( n | n<<8 ) & 0x0000f00f;
        n = ( n | n<<4 ) & 0x000c30c3;
        n = ( n | n<<2 ) & 0x00249249;
        return n;
    }

public:
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�x���W�̏������� */
    const int _root_x1;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�̏������� */
    const int _root_y1;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�z���W�̏������� */
    const int _root_z1;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�x���W�傫���� */
    const int _root_x2;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�傫���� */
    const int _root_y2;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�z���W�傫���� */
    const int _root_z2;
    /** [r]�ŏ����(=�ō������̋��)��1��Ԃ�X�������̋��� */
    const double _top_level_dx;
    /** [r]�ŏ����(=�ō������̋��)��1��Ԃ�Y�������̋��� */
    const double _top_level_dy;
    /** [r]�ŏ����(=�ō������̋��)��1��Ԃ�Z�������̋��� */
    const double _top_level_dz;

    const double _r_top_level_dx;
    const double _r_top_level_dy;
    const double _r_top_level_dz;

public:
    /**
     * ���`�����؋�Ԃ��\�z����.
     * @param prm_level �\�z�����ԃ��x��
     * @param x1 �\�z����O�g�̋�ԍ��W
     * @param y1 �V
     * @param z1 �V
     * @param x2 �V
     * @param y2 �V
     * @param z2 �V
     */
    LinearOctree(uint32_t prm_level,
                 int x1, int y1, int z1,
                 int x2, int y2, int z2);

    /**
     * �v�f�𔪕��؋�Ԃɓo�^����
     * ��Ԕԍ��͈͊O�ɂȂ����ꍇ�͖��������B
     * @param prm_pElem �v�f
     * @param tx1 �v�f�ΏۃI�u�W�F�N�g�̊O�g�̍��W
     * @param ty1 �V
     * @param tz1 �V
     * @param tx2 �V
     * @param ty2 �V
     * @param tz2 �V
     */
    void registerElem(NodeElem* const prm_pElem,
                      int tx1, int ty1, int tz1,
                      int tx2, int ty2, int tz2);

    virtual ~LinearOctree();
};

}
#endif /*GGAF_CORE_LINEAROCTREE_H_*/

