#ifndef GGAF_CORE_LINEAROCTREE_H_
#define GGAF_CORE_LINEAROCTREE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/util/lineartree/LinearTree.hpp"

#include "jp/ggaf/core/util/lineartree/LinearOctreeRounder.hpp"
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
template<class T>
class LinearOctree : public LinearTree<T, 3, 8> {

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
                 int x2, int y2, int z2) : LinearTree<T, 3, 8>(prm_level),
    _root_x1(x1),
    _root_y1(y1),
    _root_z1(z1),
    _root_x2(x2),
    _root_y2(y2),
    _root_z2(z2),
    _top_level_dx( (_root_x2-_root_x1) / ((double)(1<<LinearTree<T,3,8>::_top_space_level)) ),
    _top_level_dy( (_root_y2-_root_y1) / ((double)(1<<LinearTree<T,3,8>::_top_space_level)) ),
    _top_level_dz( (_root_z2-_root_z1) / ((double)(1<<LinearTree<T,3,8>::_top_space_level)) ),
    _r_top_level_dx(1.0 / _top_level_dx),
    _r_top_level_dy(1.0 / _top_level_dy),
    _r_top_level_dz(1.0 / _top_level_dz)
    {
    #ifdef MY_DEBUG
        if (prm_level > MAX_OCTREE_LEVEL) {
            throwCriticalException("LinearOctree::LinearOctree() ��ԃ��x���I�[�o�[�I prm_level="<<prm_level);
        }
    #endif
        _TRACE_("LinearOctree::LinearOctree("<<prm_level<<") ���`�����؋�Ԕz��v�f�� _num_space="<<(LinearTree<T,3,8>::_num_space));
        _TRACE_(FUNC_NAME<<" �����؃��[�g���x��(level=0)�̋�Ԉʒu=(" << _root_x1 << "," << _root_y1 << "," << _root_z1 << ")-(" << _root_x2 << "," << _root_y2 << "," << _root_z2 << ")");
        _TRACE_(FUNC_NAME<<" �����؃��[�g���x��(level=0)�̋�Ԃ̍L��=" << _root_x2-_root_x1 << "x" << _root_y2-_root_y1 << "x" << _root_z2-_root_z1);
        _TRACE_(FUNC_NAME<<" �����ؖ��[���x��(level="<<(LinearTree<T,3,8>::_top_space_level)<<")�̋�Ԃ̍L��=" << (uint32_t)_top_level_dx << "x" << (uint32_t)_top_level_dy << "x" << (uint32_t)_top_level_dz);
    }

    /**
     * �v�f�𔪕��؋�Ԃɓo�^����
     * ��Ԕԍ��͈͊O�ɂȂ����ꍇ�͖��������B
     * @param prm_pNodeElem �v�f
     * @param tx1 �v�f�ΏۃI�u�W�F�N�g�̊O�g�̍��W
     * @param ty1 �V
     * @param tz1 �V
     * @param tx2 �V
     * @param ty2 �V
     * @param tz2 �V
     */
    void registerElem(T* const prm_pNodeElem,
                      int tx1, int ty1, int tz1,
                      int tx2, int ty2, int tz2) {

        //�͂ݏo��ꍇ�͕␳
        if (tx1 <= _root_x1)  { tx1 = _root_x1; }
        if (tx2 >= _root_x2)  { tx2 = _root_x2; }
        if (ty1 <= _root_y1)  { ty1 = _root_y1; }
        if (ty2 >= _root_y2)  { ty2 = _root_y2; }
        if (tz1 <= _root_z1)  { tz1 = _root_z1; }
        if (tz2 >= _root_z2)  { tz2 = _root_z2; }
        //�����W�̑召�����Ԃ����ꍇ�A�܂�Level0���O���ALevel0�S�̂��傫���ꍇ�͖�������
        if (tx1 >= tx2 || ty1 >= ty2 || tz1 >= tz2) {
        return; //��ԊO�͓o�^���Ȃ�
        }
        //��tx1,ty1,tz1,tx2,ty2,tz2 ����A��Ԕԍ� �����߂遄
        //BOX�̈���W�����Ԕz��v�f�ԍ��i���`�����ؔz��̗v�f�ԍ��j���Z�o .
        //�܂��ABOX�̏������ Level �ƁA���̋��Level�̃��[�g�������ʂ���Ԕԍ�������
        //���[�g�������ʂ���Ԕԍ�����v�Z���Ĕz��� index �����߂�B

        //BOX�̍�����O��XYZ���W�_�����������Ԃ́A�ő僌�x���̋�ԁi��������Ȃ��ł��[����ԁj�Ń��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
        const uint32_t minnum_in_toplevel = LinearOctree::getMortonOrderNumFromXYZindex(
                            (uint32_t)((tx1 - _root_x1) * _r_top_level_dx),
                            (uint32_t)((ty1 - _root_y1) * _r_top_level_dy),
                            (uint32_t)((tz1 - _root_z1) * _r_top_level_dz)
                        );

        //BOX�̉E�㉜��XYZ���W�_�����������Ԃ́A�ő僌�x���̋�ԁi��������Ȃ��ł��[����ԁj�Ń��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
        const uint32_t maxnum_in_toplevel = LinearOctree::getMortonOrderNumFromXYZindex(
                            (uint32_t)((tx2 - _root_x1) * _r_top_level_dx),
                            (uint32_t)((ty2 - _root_y1) * _r_top_level_dy),
                            (uint32_t)((tz2 - _root_z1) * _r_top_level_dz)
                        );                 //��_root_x2,_root_y2,_root_z2 �ƊԈႦ�Ă��܂���B
        //��Ԃɓo�^����i���ʉ��j
       LinearTree<T,3,8>::registerElem((ITreeNodeElem*)prm_pNodeElem, minnum_in_toplevel,maxnum_in_toplevel);

//�ȉ��͋��ʉ��O�̃R�[�h
//    //������BOX�́A�ǂ̃��x���̋�Ԃɏ������Ă���̂��擾
//    const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
//    uint32_t shift_num = 0;
//    for (uint32_t i = 0; i < _top_space_level; i++) {
//        if (((differ_bit_pos>>(i*3)) & 0x7) != 0 ) {
//            shift_num = i+1;
//        }
//    }
//    //xor����differ_bit_pos �� �E��3�r�b�g�V�t�g���A�}�X�N &B111(&H7) ��AND�����A&B000 ��
//    //�Ȃ��Ȃ��Ă���ꍇ�Ashift_num�ɒl�����B
//    //�܂肱��� differ_bit_pos �� �܂� �R�r�b�g�ɋ�؂�A����3�r�b�g���H������Ă���ӏ��̂����A
//    //�ł������ʒu������ׂĂ���B
//    //�H���Ⴄ3�r�b�g�̈ʒu�́A���̃��x���̃��g�[�������ʒu���H������Ă��邱�Ƃ��Ӗ�����B
//    //���������čł�����3�r�b�g���H������Ă���ӏ�(�V�t�g�񐔁�shift_num)��菊����ԃ��x�����킩��
//    //�ő��ԕ���Level = 5�Ƃ��āA������O��6001�ԁA�E�㉜��6041�Ԃɏ������Ă���BOX���ɂ����
//    //
//    //                               lv0 lv1 lv2 lv3 lv4 lv5 ����e���x����Ԃ̃��[�g�������ʒu
//    //     6001 = 00 000 000 000 000 000 001 011 101 110 001
//    // XOR)6041 = 00 000 000 000 000 000 001 011 110 011 001
//    // -----------------------------------------------------
//    //      232 = 00 000 000 000 000 000 000 000 011 101 000
//    //
//    //                                                   111 �E�E�E �}�X�N
//    //                                               111
//    //                                           111
//    //                                       111
//    //  AND)                             111     <--- �����܂ōs���āA�ł�����3�r�b�g���H������Ă���ӏ���3��ڂ��������Ƃ�����
//    // ------------------------------------------------------
//    //                                   000 000 011 101 000     <--- ������̃}�X�N���ʂ�  000 �ŁA���ꂪ��������A6001�Ԃ�6041�Ԃ̃��[�g�������ʒu�������ł���i=�����Ԃɏ����j���Ӗ�����
//    //                                    f   f   t   t   f      if (differ_bit_pos>>(i*3)) & 0x7 != 0 ) �̔���
//    //                                    5   4   3   2   1   0  shift_num(�V�t�g��)
//    //                                    o   o   x(�ȍ~x)        �����Ԃɓ����Ă��锻��i������݂�j
//    //
//    //   ��L���A6001�Ԃ�6041�Ԃ͋�ԃ��x��1�A���x��2 �܂ł͓�����ԃ��x���ɑ����Ă������A
//    //   ��ԃ��x��3���烂�[�g�������ʒu���قȂ��Ă��܂����Ƃ�����B���������āA
//    //   �u������ԃ��x���v��Lv2��Ԃł���Ɗm��ł���B����𒲂ׂ邽�߂�
//    //   XOR��0�ȊO�ɂȂ�ō��̃V�t�g��  shift_num = 3 �����߂�B
//    //   ���߂邽�߂ɂ́A�E��3�r�b�g�V�t�g���� 0x7 �� AND�𒲂ׂ邱�Ƃ��J��Ԃ��K�v������Ƃ������Ƃ��B
//    //   Level = 5�̏ꍇ�A5��J��Ԃ��A�v�� shift_num �̃V�t�g�񐔂𒲂ׂ�΁A������ԃ��x��������I
//
//    //����XOR���ʂ�
//    // 00 000 000 000 000 000 000 000 000 111 �̏ꍇ�Ȃ�� shift_num=1
//    //�����
//    //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����4(=��ԃ��x��5�ŐH���Ⴄ)
//    //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����7(=��ԃ��x��8�ŐH���Ⴄ)
//
//    // 00 000 000 000 000 111 110 000 101 111 �Ȃǂ̏ꍇ�� shift_num=5
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
//    const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*3);
//    //�s�����̉��ʂ̃r�b�g��3�r�b�g�P�ʂŏ������A�����̃��[�g�������ԍ������߂�
//    //
//    // minnum_in_toplevel>>(shift_num*3); �ɂ��āA
//    // minnum_in_toplevel=6001 �ł� 6041�ł��ǂ���ł��悭
//    //        lv0 lv1 lv2 lv3 lv4 lv5          lv0 lv1 lv2
//    // 6001 = 000 001 011 101 110 001   -->    000 001 011 = 11
//    // 6041 = 000 001 011 110 011 001   -->    000 001 011 = 11
//    //                    ^^^ ^^^ ^^^
//    //                  (shift_num*3 �r�b�g����)
//    //
//    // �̂悤�ɕs�����̃r�b�g���E�փV�t�g���Ă���
//    // ����ŁA������O��6001�ԁA�E�㉜��6041�ԂƂ���BOX�́A�������Lv2�̏ꍇ�́A���[�g�������ʂ���Ԕԍ�11��(0�Ԃ��琔����)�ł��������Ƃ��킩��B
//    // ���Ƃ͂����z��Index�ɕϊ�����̂�
//
//    //�������(�V�t�g��)�Ƃ��̋�Ԃ̃��[�g�������ʂ���Ԕԍ�������`�����ؔz��̗v�f�ԍ������߂�
//    const uint32_t index = morton_order_space_num + (POW_N[_top_space_level-shift_num]-1)/7;
//    //(_POW8[_top_space_level-shift_num]-1)/7;
//    //�́A���`�����؋�Ԕz��́A������ԃ��x���̍ŏ��̋�Ԃ̗v�f�ԍ�������킷�B
//    //���䐔��̘a
//    // ��r^k = r^0 + r^1 + r^2 + ... + r^n
//    // ��r^k = (1 - r^(n+1)) / (1 - r)
//    //
//    //���`8���؂̔z��v�f�̋�ԃ��x�����܂ł̍��v��֐��� r=8 ��
//    //(1 - 8^(n+1)) / (1-8)  =  (1-8^(n+1)) / -7  =  (8^(n+1) - 1) / 7 �ƂȂ�
//    //�����ŁA������Ԃ̍ŏ��̋�ԗv�f�����߂邽�߁A n = ������ԃ��x��-1 �̌v�Z�l�i�e��ԃ��x���܂ł̗v�f���j�́A
//    //���̎��̗v�f��������ԃ��x���̐擪�̗v�f�ɂȂ�͂����I�B�Ƃ������ߕ�������B
//    //���������čŌ�ɒl�� +1 �������̂��ق����l�ł��邪�A�z���0�Ԃ���n�܂邽�߁A+1 -1 = 0 �ŁA�ȗ����Ă��܂����B
//    //��̗�ł����� shift_num = 3 �ŁA�ő��ԕ���Level(_top_space_level) = 5 �ł���̂�
//    // 5 - 3 = 2 �ŏ�����ԃ��x���� 2
//    // n = 2 - 1 = 1 ��������  (8^(1+1) - 1) / 7 = 9 ��
//    //������Ԃ̃��x��2����e�̋�ԃ��x���ł���A��ԃ��x��1�܂ł̔z��v�f�����v��9�Ƃ킩��B
//    //���]�̏�����ԃ��x���� 2�̍ŏ��̋�Ԃ͔z��� 9+1 ��10�Ԗڂ���n�܂�B
//    //�z���10�ԖڂƂ́A�z��v�f�ԍ���-1����9�ɂȂ�B
//    //+1 ���� -1 ����̂Ō��ǁA������ԃ��x��x�̍ŏ��̔z��v�f�ԍ���  (8^x - 1) / 7 �ƂȂ�
    }

    LinearOctreeRounder<T>* createRounder(void (T::*prm_pFuncHitCheck)(T*)) {
        LinearOctreeRounder<T>* pRounder = NEW LinearOctreeRounder<T>( LinearTree<T,3,8>::_paNodeSpaceArray,  LinearTree<T,3,8>::_num_space, prm_pFuncHitCheck);
        return pRounder;
    }

    virtual ~LinearOctree() {
    }
};

}
#endif /*GGAF_CORE_LINEAROCTREE_H_*/

