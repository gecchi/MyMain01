#ifndef GGAFCORE_GGAFLINEARQUADTREE_H_
#define GGAFCORE_GGAFLINEARQUADTREE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/core/util/GgafTreeSpace.hpp"
#include "jp/ggaf/core/util/GgafTreeElem.hpp"

namespace GgafCore {

/**
 * ���`�l���؃N���X .
 * ���`�l���؂Ƃ́A�l���؋�ԕ�����@�̊e��Ԃ��A���̔z��(���`)�ɕ��ׂ���Ԃ��Ӗ����܂��B
 * �{�N���X�ł̗p������̂悤�ɒ�߂鎖�Ƃ���B
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
 * <BR>
 * <B>����ԃ��x����</B><BR>
 * ��L�}�̉E�ɏ����Ă���A�e��Ԃ̃��x�����w���B<BR>
 * <BR>
 * <B>�����[�g�������ʂ��ԍ��A��Ԕԍ���</B><BR>
 * ��L�}�̊eLevel��ԂɐU���Ă��镪����Ԃ̔ԍ��̂��Ƃ��w�����Ƃ���B<BR>
 * ��L�}�̗�ł�Lv1��Ԃ̃��[�g�������ʂ��ԍ��� 0�`3�ALv2��Ԃ̃��[�g�������ʂ��ԍ���0�`15 �Ƃ����悤�Ɏg���B<BR>
 * <BR>
 * <B>���q��ԁA�e��ԁB�i�q���x���A�e���x���j��</B><BR>
 * �����ԃ��x���� +1 ���q��ԁA�����ԃ��x���� -1 ��e��ԂƌĂԂ��Ƃɂ���B<BR>
 * <BR>
 * <B>�����[�g�������ʒu��</B><BR>
 * �����Ԃ�4�������A����A�E��A�����A�E����
 * ���ꂼ�� 0 1 2 3 (8���؂ł� 0�`7)�ƕ\���������ꍇ������A
 * ���� 0 1 2 3 �̎������[�g�������ʒu�ƌĂԂ��ƂƂ���B<BR>
 * <BR>
 * <B>�����(�z��)�v�f�ԍ���</B><BR>
 * ��Ԕԍ��ɑΉ�������`�z��̃C���f�b�N�X���w���B<BR>
 * ��̓I�ɂ� _paQuadrant �̗v�f�ԍ��B<BR>
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
 * �T�C�g���R���e���c�� �u����8 4���؋�ԕ������œK������I�v http://marupeke296.com/COL_2D_No8_QuadTree.html<BR>
 * �̋L�����Q�l�Ɂi�Ƃ������w�ǂ��̂܂܁j�쐬���Ă��܂��B<BR>
 * �ڂ���؂̔��ɉ���₷������Ɋ��ӂ������܂��B<BR>
 * <BR>
 * @version 1.00
 * @since 2017/08/02
 * @author Masatoshi Tsuge
 */
class GgafLinearQuadtree : public GgafObject {

private:
    /**
     * ����Level��Ԃ̎l���؃��[�g�������̒ʂ���Ԕԍ��擾 .
     * ����Level�Ƃ� <BR>
     * �u�����ƌ��ʂ͓���level��Ԃł���v<BR>
     * �Ƃ����Ӗ��B�{���\�b�h�̈����͔C�ӂ�Level��Ԃ��󂯓����B<BR>
     * ����Ă��邱�Ƃ�<BR>
     * �E���������ꂼ��3bit���ƂɊԊu���J����<BR>
     * �E����2�̌��ʂ�1�r�b�g�A����2�̌��ʂ�2�r�b�g  ���炵�� OR �����<BR>
     * �ȏ�B<BR>
     * <BR>
     * �}������ƁA�܂�
     * <pre><code>
     * 000000000000000000000000abcdefgh ,
     * 000000000000000000000000ijklmnop ,
     * ��
     * 0000000000000000 0a 0b 0c 0d 0e 0f 0g 0h  --> X�������
     * 0000000000000000 i0 j0 k0 l0 m0 n0 o0 p0  --> Y�������
     * �������āAOR��������(���̌���)���߂�l�ɂȂ�B�Ӗ��́A
     * 0000000000000000 ia jb kc ld me nf og ph
     *                                       ^^-->&B(ph)        = ����Level�̋�Ԃ̃��[�g�������ʂ���Ԕԍ� 0�`3
     *                                    ^^ ^^-->&B(ogph)      = ����Level�̐e��Ԃ̃��[�g�������ʂ���Ԕԍ� 0�`15
     *                                 ^^ ^^ ^^-->&B(nfogph)    = ����Level�̐e�̐e��Ԃ̃��[�g�������ʂ���Ԕԍ� 0�`63
     *                              ^^ ^^ ^^ ^^
     *                               |  |  |  |
     *                               |  |  |  &B(ph) = ����Level�̋�Ԃ̃��[�g�������̈ʒu 0�`3
     *                 ............  |  |  `---&B(og) = ����Level�̐e��Ԃ̃��[�g�������̈ʒu  0�`3
     *                               |  `-------&B(nf) = ����Level�̐e�̐e�̋�Ԃ̃��[�g�������̈ʒu 0�`3
     * </code></pre>
     * @param x_space_index ����̃��x����Ԃ�x���W��ԃC���f�b�N�X (������ 0�`255 �Ƃ���)
     * @param y_space_index ����̃��x����Ԃ�y���W��ԃC���f�b�N�X (������ 0�`255 �Ƃ���)
     * @return ����Levell��Ԃ�(x_index, y_index)�Ŏ�������ԂɑΉ�����
     *         �l���؃��[�g�������̒ʂ���Ԕԍ�(�ő�Level8�ŁA0�`87380)
     */
    static inline uint32_t getMortonOrderNumFromXYindex( uint32_t x_space_index, uint32_t y_space_index) {
        return GgafLinearQuadtree::separateEveryTwoBit(x_space_index) |
               GgafLinearQuadtree::separateEveryTwoBit(y_space_index)<<1;
    }

    /**
     * 2bit���ƂɊԊu���J���� .
     * <pre><code>
     * 0000000000000000abcdefghijklmnop  ��
     * 0a0b0c0d0e0f0g0h0i0j0k0l0m0n0o0p  �ɂ��܂�
     * ���A���S���Y����
     * n          = 0000 0000 0000 0000 abcd efgh ijkl mnop �̂Ƃ�
     * n<<8       = 0000 0000 abcd efgh ijkl mnop 0000 0000
     * n|n<<8     = 0000 0000 abcd efgh ???? ???? ijkl mnop
     * 0x00ff00ff = 0000 0000 1111 1111 0000 0000 1111 1111 �ł���̂�
     * (n|n<<8) & 0x00ff00ff =
     *              0000 0000 abcd efgh 0000 0000 ijkl mnop �ƂȂ�B
     * ���̌��ʂ��܂� n �ɑ������(�ȉ����l��)
     * n          = 0000 0000 abcd efgh 0000 0000 ijkl mnop
     * n<<4       = 0000 abcd efgh 0000 0000 ijkl mnop 0000
     * n|n<<4     = 0000 abcd ???? efgh 0000 ijkl ???? mnop
     * 0x0f0f0f0f = 0000 1111 0000 1111 0000 1111 0000 1111
     * n �� (n|n<<4) & 0x0f0f0f0f =
     *              0000 abcd 0000 efgh 0000 ijkl 0000 mnop
     * n<<2       = 00ab cd00 00ef gh00 00ij kl00 00mn op00
     * n|n(n<<2)  = 00ab ??cd 00ef ??gh 00ij ??kl 00mn ??op
     * 0x33333333 = 0011 0011 0011 0011 0011 0011 0011 0011
     * n �� (n|n<<2) & 0x33333333 =
     *              00ab 00cd 00ef 00gh 00ij 00kl 00mn 00op
     * n<<1       = 0ab0 0cd0 0ef0 0gh0 0ij0 0kl0 0mn0 0op0
     * n|n(n<<1)  = 0a?b 0c?d 0e?f 0g?h 0i?j 0k?l 0m?n 0o?p
     * 0x55555555 = 0101 0101 0101 0101 0101 0101 0101 0101
     * n �� (n|n<<2) & 0x55555555 =
     *              0a0b 0c0d 0e0f 0g0h 0i0j 0k0l 0m0n 0o0p
     * </code></pre>
     * @param n 0�`255�܂ł̐��l
     * @return 3bit���ƂɊԊu���󂯂�ꂽ�l
     */
    static inline uint32_t separateEveryTwoBit(uint32_t n) {
           n = (n | (n<<8) ) & 0x00ff00ff;
           n = (n | (n<<4) ) & 0x0f0f0f0f;
           n = (n | (n<<2) ) & 0x33333333;
           return (n | (n<<1) ) & 0x55555555;
    }

public:
    /** [r]�l���؂̋�Ԃ��꒼���ɕ��ׂ����`�z�� */
    GgafTreeSpace<2u>* _paQuadrant; //_paQuadrant[0] �� ROOT��Ԃւ̃|�C���^
    /** [r]�l���؂̋�Ԃɓo�^���s�����v�f�̐擪�v�f */
    GgafTreeElem<2u>* _pRegElemFirst;
    /** [r]�ő��ԃ��x�� */
    const uint32_t _top_space_level; //���[�g��Ԃ�Level=0
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�x���W�̏������� */
    const int _root_x1;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�̏������� */
    const int _root_y1;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�z���W�̏������� */
    const int _root_x2;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�傫���� */
    const int _root_y2;
    /** [r]�ŏ����(=�ō������̋��)��1��Ԃ�X�������̋��� */
    const int _top_level_dx;
    /** [r]�ŏ����(=�ō������̋��)��1��Ԃ�Y�������̋��� */
    const int _top_level_dy;

    const double _r_top_level_dx;
    const double _r_top_level_dy;

    /** [r]8�̗ݏ�̒l��\�ߌv�Z���ĕێ����Ă���z�� */
    uint32_t* _pa_4pow;
    /** [r]�S��Ԑ� */
    uint32_t _num_space;

public:
    /**
     * ���`�l���؋�Ԃ��\�z����.
     * @param prm_level �\�z�����ԃ��x��
     * @param x1 �\�z����O�g�̋�ԍ��W
     * @param y1 �V
     * @param x2 �V
     * @param y2 �V
     */
    GgafLinearQuadtree(uint32_t prm_level,
                       int x1, int y1,
                       int x2, int y2);

    /**
     * �v�f���l���؋�Ԃɓo�^����
     * ��Ԕԍ��͈͊O�ɂȂ����ꍇ�͖��������B
     * @param prm_pElem �v�f
     * @param tx1 �v�f�ΏۃI�u�W�F�N�g�̊O�g�̍��W
     * @param ty1 �V
     * @param tx2 �V
     * @param ty2 �V
     */
    void registerElem(GgafTreeElem<2u>* const prm_pElem,
                      int tx1, int ty1,
                      int tx2, int ty2);

    /**
     * �l���؋�Ԃɓo�^����Ă���S�v�f����������i��������Ԃɂ���j.
     * �{���\�b�h�N���A�����Ȃ�΁A<BR>
     * registerElem() <BR>
     * �ɂ��l���؂֍ēx�v�f�o�^���\�ƂȂ�B
     */
    void clearAllElem();

    /**
     * �f�o�b�O�p�B�l���ؓo�^�󋵏o�́i���x���W�܂ł����Ή����Ă��Ȃ��j .
     */
    void putTree();

    virtual ~GgafLinearQuadtree();
};

}
#endif /*GGAFCORE_GGAFLINEARQUADTREE_H_*/

