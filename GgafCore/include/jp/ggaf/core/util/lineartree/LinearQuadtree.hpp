#ifndef GGAF_CORE_LINEARQUADTREE_H_
#define GGAF_CORE_LINEARQUADTREE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/util/lineartree/LinearTree.hpp"

#include "jp/ggaf/core/util/lineartree/LinearQuadtreeRounder.hpp"

namespace GgafCore {


#define MAX_QUADTREE_LEVEL 14

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
 * �T�C�g���R���e���c�� �u����8 4���؋�ԕ������œK������I�v http://marupeke296.com/COL_2D_No8_QuadTree.html<BR>
 * �̋L�����Q�l�Ɂi�Ƃ������w�ǂ��̂܂܁j�쐬���Ă��܂��B<BR>
 * �ڂ���؂̔��ɉ���₷������Ɋ��ӂ������܂��B<BR>
 * <BR>
 * @version 1.00
 * @since 2017/08/02
 * @author Masatoshi Tsuge
 */
template<class T>
class LinearQuadtree : public LinearTree<T, 2, 4> {

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
        return LinearQuadtree::separateEveryTwoBit(x_space_index) |
               LinearQuadtree::separateEveryTwoBit(y_space_index)<<1;
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
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�x���W�̏������� */
    const int _root_x1;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�̏������� */
    const int _root_y1;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�z���W�̏������� */
    const int _root_x2;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�傫���� */
    const int _root_y2;
    /** [r]�ŏ����(=�ō������̋��)��1��Ԃ�X�������̋��� */
    const double _top_level_dx;
    /** [r]�ŏ����(=�ō������̋��)��1��Ԃ�Y�������̋��� */
    const double _top_level_dy;

    const double _r_top_level_dx;
    const double _r_top_level_dy;

public:
    /**
     * ���`�l���؋�Ԃ��\�z����.
     * @param prm_level �\�z�����ԃ��x��
     * @param x1 �\�z����O�g�̋�ԍ��W
     * @param y1 �V
     * @param x2 �V
     * @param y2 �V
     */
    LinearQuadtree(uint32_t prm_level,
                   int x1, int y1,
                   int x2, int y2) : LinearTree<T,2,4>(prm_level),
    _root_x1(x1),
    _root_y1(y1),
    _root_x2(x2),
    _root_y2(y2),
    _top_level_dx( ((_root_x2-_root_x1) / ((float)(1<<LinearTree<T,2,4>::_top_space_level))) + 1),
    _top_level_dy( ((_root_y2-_root_y1) / ((float)(1<<LinearTree<T,2,4>::_top_space_level))) + 1),
    _r_top_level_dx(1.0 / _top_level_dx),
    _r_top_level_dy(1.0 / _top_level_dy)
    {
    #ifdef MY_DEBUG
        if (prm_level > MAX_QUADTREE_LEVEL) {
            throwCriticalException("LinearQuadtree::LinearQuadtree() ��ԃ��x���I�[�o�[�I prm_level="<<prm_level);
        }
    #endif
        _TRACE_("LinearQuadtree::LinearQuadtree("<<prm_level<<") ���`�l���؋�Ԕz��v�f�� _num_space="<<(LinearTree<T,2,4>::_num_space));
        _TRACE_(FUNC_NAME<<" �l���؃��[�g���x��(level=0)�̋�Ԉʒu=(" << _root_x1 << "," << _root_y1 << ")-(" << _root_x2 << "," << _root_y2 << ")");
        _TRACE_(FUNC_NAME<<" �l���؃��[�g���x��(level=0)�̋�Ԃ̍L��=" << _root_x2-_root_x1 << "x" << _root_y2-_root_y1 );
        _TRACE_(FUNC_NAME<<" �l���ؖ��[���x��(level="<<(LinearTree<T,2,4>::_top_space_level)<<")�̋�Ԃ̍L��=" << (uint32_t)_top_level_dx << "x" << (uint32_t)_top_level_dy );
    }

    /**
     * �v�f���l���؋�Ԃɓo�^����
     * ��Ԕԍ��͈͊O�ɂȂ����ꍇ�͖��������B
     * @param prm_pNodeElem �v�f
     * @param tx1 �v�f�ΏۃI�u�W�F�N�g�̊O�g�̍��W
     * @param ty1 �V
     * @param tx2 �V
     * @param ty2 �V
     */
    void registerElem(T* prm_pNodeElem,
            int tx1, int ty1,
            int tx2, int ty2 ) {
        //�͂ݏo��ꍇ�͕␳
        if (tx1 <= _root_x1)  { tx1 = _root_x1; }
        if (tx2 >= _root_x2)  { tx2 = _root_x2; }
        if (ty1 <= _root_y1)  { ty1 = _root_y1; }
        if (ty2 >= _root_y2)  { ty2 = _root_y2; }
        //�����W�̑召�����Ԃ����ꍇ�A�܂�Level0���O���ALevel0�S�̂��傫���ꍇ�͖�������
        if (tx1 >= tx2 || ty1 >= ty2) {
        return; //��ԊO�͓o�^���Ȃ�
        }

        //��tx1,ty1,tx2,ty2 ����A��Ԕԍ� �����߂遄
        //Rect(�v�f)�̈���W�����Ԕz��v�f�ԍ��i���`�l���ؔz��̗v�f�ԍ��j���Z�o .
        //�܂��ARect(�v�f)�̏������ Level �ƁA���̋��Level�̃��[�g�������ʂ���Ԕԍ�������
        //���[�g�������ʂ���Ԕԍ�����v�Z���Ĕz��� index �����߂�B

        //Rect(�v�f)�̍����XY���W�_�����������Ԃ́A�ő僌�x���̋�ԁi��������Ȃ��ł��[����ԁj�Ń��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
        const uint32_t minnum_in_toplevel = LinearQuadtree::getMortonOrderNumFromXYindex(
                              (uint32_t)((tx1 - _root_x1) * _r_top_level_dx),
                              (uint32_t)((ty1 - _root_y1) * _r_top_level_dy)
                          );

        //Rect(�v�f)�̉E����XY���W�_�����������Ԃ́A�ő僌�x���̋�ԁi��������Ȃ��ł��[����ԁj�Ń��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
        const uint32_t maxnum_in_toplevel = LinearQuadtree::getMortonOrderNumFromXYindex(
                              (uint32_t)((tx2 - _root_x1) * _r_top_level_dx),
                              (uint32_t)((ty2 - _root_y1) * _r_top_level_dy)
                          );                 //��_root_x2,_root_y2 �ƊԈႦ�Ă��܂���B
        //��Ԃɓo�^����i���ʉ��j
        LinearTree<T,2,4>::registerElem((ITreeNodeElem*)prm_pNodeElem, minnum_in_toplevel, maxnum_in_toplevel);
//�ȉ��͋��ʉ��O�̃R�[�h
//    //������Rect(�v�f)�́A�ǂ̃��x���̋�Ԃɏ����i�����Ă���j���Ă���̂��A�ő�̃��x����Ԃ��擾
//    const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
//    uint32_t shift_num = 0;
//    for (uint32_t i = 0; i < _top_space_level; i++) {
//        if (((differ_bit_pos>>(i*2)) & 0x3) != 0 ) {
//            shift_num = i+1;
//        }
//    }
//    //xor����differ_bit_pos �� �E��2�r�b�g�V�t�g���A�}�X�N &B11(&H3) ��AND�����A&B000 ��
//    //�Ȃ��Ȃ��Ă���ꍇ�Ashift_num�ɒl�����B
//    //�܂肱��� differ_bit_pos �� �܂�2�r�b�g�ɋ�؂�A����2�r�b�g���H������Ă���ӏ��̂����A
//    //�ł������ʒu������ׂĂ���B
//    //�H���Ⴄ2�r�b�g�̈ʒu�́A���̃��x���̃��g�[�������ʒu���H������Ă��邱�Ƃ��Ӗ�����B
//    //���������čł�����2�r�b�g���H������Ă���ӏ�(�V�t�g�񐔁�shift_num)��菊����ԃ��x�����킩��
//    //�ő��ԕ��� Level = 5 �Ƃ��āA���オ804�ԁA�E����877�Ԃɏ������Ă���Rect(�v�f)���ɂ����
//    //
//    //                                         L0 L1 L2 L3 L4 L5 �E�E�E�e���x����Ԃ̃��[�g�������ʒu
//    //     804 = 00 00 00 00 00 00 00 00 00 00 00 11 01 00 10 00
//    // XOR)877 = 00 00 00 00 00 00 00 00 00 00 00 11 01 10 11 01
//    // ------------------------------------------------------------
//    //      37 = 00 00 00 00 00 00 00 00 00 00 00 00 00 10 01 01
//    //
//    //                                                        11 �E�E�E �}�X�N
//    //                                                     11
//    //                                                  11
//    //                                               11
//    //  AND)                                      11     <--- �����܂ōs���āA�ł�����3�r�b�g���H������Ă���ӏ���3��ڂ��������Ƃ�����
//    // -------------------------------------------------------------
//    //                                            00 00 10 01 01     <--- ������̃}�X�N���ʂ�  00 �ŁA���ꂪ��������A�A804�Ԃ�877�Ԃ̃��[�g�������ʒu�������ł���i=�����Ԃɏ����j���Ӗ�����
//    //                                            f  f  t  t  t      if (differ_bit_pos>>(i*2)) & 0x3 != 0 ) �̔���
//    //                                            5  4  3  2  1  0   shift_num(�V�t�g��)
//    //                                            o  o  x(�ȍ~x)      �����Ԃɓ����Ă��锻��i������݂�j
//    //
//    //   ��L���A804�Ԃ�877�Ԃ͋�ԃ��x��1�A���x��2 �܂ł͓�����ԃ��x���ɑ����Ă������A
//    //   ��ԃ��x��3���烂�[�g�������ʒu���قȂ��Ă��܂����Ƃ�����B���������āA
//    //   �u������ԁiMAX�j���x���v��Lv2��Ԃł���Ɗm��ł���B����𒲂ׂ邽�߂�
//    //   XOR��0�ȊO�ɂȂ�ō��̃V�t�g��  shift_num = 3 �����߂�B
//    //   ���߂邽�߂ɂ́A�E��3�r�b�g�V�t�g���� 0x3 �� AND�𒲂ׂ邱�Ƃ��J��Ԃ��K�v������Ƃ������Ƃ��B
//    //   Level = 5�̏ꍇ�A5��J��Ԃ��A�v�� shift_num �̃V�t�g�񐔂𒲂ׂ�΁A������ԃ��x��������I
//
//    //����XOR���ʂ�
//    // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 11 �̏ꍇ�Ȃ�� shift_num=1
//    //�����
//    //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����4(=��ԃ��x��5�ŐH���Ⴄ)
//    //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����7(=��ԃ��x��8�ŐH���Ⴄ)
//
//    // 00 00 00 00 00 00 00 00 00 00 00 11 10 00 10 00 �̏ꍇ�� shift_num=5
//    //�����
//    //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����0 �܂胋�[�g��ԃ��x������
//    //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����4
//
//    //�܂Ƃ߂��
//    //�ő��ԕ���Level = 5 �̏ꍇ
//    //shift_num   = 0 1 2 3 4 5
//    //�������Level = 5 4 3 2 1 0
//    //�ő��ԕ���Level=8 �̏ꍇ
//    //shift_num   = 0 1 2 3 4 5 6 7 8
//    //�������Level = 8 7 6 5 4 3 2 1 0
//
//    //������Ԃ̃��[�g�������̒ʂ���Ԕԍ������߂�
//    const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*2);
//    //�s�����̉��ʂ̃r�b�g��2�r�b�g�P�ʂŏ������A�����̃��[�g�������ԍ������߂�
//    //
//    // minnum_in_toplevel>>(shift_num*2); �ɂ��āA
//    // minnum_in_toplevel=804 �ł� 877�ł��ǂ���ł��悭
//    //       L0 L1 L2 L3 L4 L5          L0 L1 L2
//    // 804 = 00 11 01 00 10 00   -->    00 11 01 = 13
//    // 877 = 00 11 01 10 11 01   -->    00 11 01 = 13
//    //                ^^ ^^ ^^
//    //                  (shift_num*2 �r�b�g����)
//    //
//    // �̂悤�ɕs�����̃r�b�g���E�փV�t�g���Ă���
//    // ����ŁA���オ804�ԁA�E����877�ԂƂ���Rect(�v�f)�́A�������Lv2�̏ꍇ�́A���[�g�������ʂ���Ԕԍ�13��(0�Ԃ��琔����)�ł��������Ƃ��킩��B
//    // ���Ƃ͂����z��Index�ɕϊ�����̂�
//
//    //�������(�V�t�g��)�Ƃ��̋�Ԃ̃��[�g�������ʂ���Ԕԍ�������`�l���ؔz��̗v�f�ԍ������߂�
//    const uint32_t index = morton_order_space_num + (POW_N[_top_space_level-shift_num]-1)/3;
//    //(_POW4[_top_space_level-shift_num]-1)/7;
//    //�́A���`�l���؋�Ԕz��́A������ԃ��x���̍ŏ��̋�Ԃ̗v�f�ԍ�������킷�B
//    //���䐔��̘a
//    // ��r^k = r^0 + r^1 + r^2 + ... + r^n
//    // ��r^k = (1 - r^(n+1)) / (1 - r)
//    //
//    //���`4���؂̔z��v�f�̋�ԃ��x�����܂ł̍��v��֐��� r=4 ��
//    //(1 - 4^(n+1)) / (1-4)  =  (1-4^(n+1)) / -3  =  (4^(n+1) - 1) / 3 �ƂȂ�
//    //�����ŁA������Ԃ̍ŏ��̋�ԗv�f�����߂邽�߁A n = ������ԃ��x��-1 �̌v�Z�l�i�e��ԃ��x���܂ł̗v�f���j�́A
//    //���̎��̗v�f��������ԃ��x���̐擪�̗v�f�ɂȂ�͂����I�B�Ƃ������ߕ�������B
//    //���������čŌ�ɒl�� +1 �������̂��ق����l�ł��邪�A�z���0�Ԃ���n�܂邽�߁A+1 -1 = 0 �ŁA�ȗ����Ă��܂����B
//    //��̗�ł����� shift_num = 3 �ŁA�ő��ԕ���Level(_top_space_level) = 5 �ł���̂�
//    // 5 - 3 = 2 �ŏ�����ԃ��x���� 2
//    // n = 2 - 1 = 1 ��������  (4^(1+1) - 1) / 3 = 5 ��
//    //������Ԃ̃��x��2����e�̋�ԃ��x���ł���A��ԃ��x��1�܂ł̔z��v�f�����v��5�Ƃ킩��B
//    //���]�̏�����ԃ��x���� 2�̍ŏ��̋�Ԃ͔z��� 5+1 ��6�Ԗڂ���n�܂�B
//    //�z���6�ԖڂƂ́A�z��v�f�ԍ���-1����5�ɂȂ�B
//    //+1 ���� -1 ����̂Ō��ǁA������ԃ��x��x�̍ŏ��̔z��v�f�ԍ���  (4^x - 1) / 3 �ƂȂ�
//
    }
    LinearQuadtreeRounder<T>* createRounder(void (T::*prm_pFuncHitCheck)(T*)) {
        LinearQuadtreeRounder<T>* pRounder = NEW LinearQuadtreeRounder<T>(LinearTree<T,2,4>::_paNodeSpaceArray, LinearTree<T,2,4>::_num_space, prm_pFuncHitCheck);
        return pRounder;
    }

    virtual ~LinearQuadtree() {
    }
};

}
#endif /*GGAF_CORE_LINEARQUADTREE_H_*/

