#ifndef GGAFLINEAROCTREE_H_
#define GGAFLINEAROCTREE_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafCore {

/**
 * ���`�����؃N���X .
 * ���`�����؂Ƃ́A�����؋�ԕ�����@�̊e��Ԃ��A���̔z��(���`)�ɕ��ׂ���Ԃ��Ӗ����܂��B
 * �{�N���X�ł̗p������̂悤�ɒ�߂鎖�Ƃ���B
 * ���̐}���R�����gAA�ŕ\���ł��Ȃ����߁A4���؂̐}���Ɍ��t�̐������邪�B�{�N���X�̋@�\�͗��̂̂W���؂ł��B
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
 * ���ۂ͂W���؂ŗ��̂Ȃ̂ŁBLv1��ԃ��[�g�������ʂ��ԍ���0�`7�ALv2��ԃ��[�g�������ʂ��ԍ���0�`63 �ɂȂ�B<BR>
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
 * ��̓I�ɂ� _paSpace �̗v�f�ԍ��B<BR>
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
class GgafLinearOctree : public GgafObject {

public:
    /** [r]�����؂̋�Ԃ��꒼���ɕ��ׂ����`�z�� */
    GgafLinearOctreeSpace* _paSpace; //_paSpace[0] �� ROOT��Ԃւ̃|�C���^
    /** [r]�����؂̋�Ԃɓo�^���s�����v�f�̐擪�v�f */
    GgafLinearOctreeElem* _pRegElemFirst;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�x���W�̏������� */
    int _root_X1;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�̏������� */
    int _root_Y1;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�z���W�̏������� */
    int _root_Z1;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�x���W�傫���� */
    int _root_X2;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�傫���� */
    int _root_Y2;
    /** [r]root��Ԃ̑Ίp�̒��_�ƂȂ�z���W�傫���� */
    int _root_Z2;
    /** [r]�ŏ����(=�ō������̋��)��1��Ԃ�X�������̋��� */
    int _top_level_dX;
    /** [r]�ŏ����(=�ō������̋��)��1��Ԃ�Y�������̋��� */
    int _top_level_dY;
    /** [r]�ŏ����(=�ō������̋��)��1��Ԃ�Z�������̋��� */
    int _top_level_dZ;

    double _r_top_level_dX;
    double _r_top_level_dY;
    double _r_top_level_dZ;

    /** [r]8�̗ݏ�̒l��\�ߌv�Z���ĕێ����Ă���z�� */
    uint32_t* _pa_8pow;
    /** [r]�S��Ԑ� */
    uint32_t _num_space;
    /** [r]�ő��ԃ��x�� */
    int _top_space_level; //���[�g��Ԃ�Level=0

public:
    /**
     * ���`�����؋�Ԃ��\�z����.
     * @param prm_level �\�z�����ԃ��x��
     */
    GgafLinearOctree(int prm_level);

    /**
     * ��ԃ��x��0�̎��͈͂��X�V.
     * �����ύX�\�B
     * @param X1 �\�z����O�g�̋�ԍ��W
     * @param Y1 �V
     * @param Z1 �V
     * @param X2 �V
     * @param Y2 �V
     * @param Z2 �V
     */
    virtual void setRootSpace(int X1, int Y1, int Z1,
                              int X2, int Y2, int Z2);

    /**
     * �v�f�𔪕��؋�Ԃɓo�^����
     * ��Ԕԍ��͈͊O�ɂȂ����ꍇ�͖��������B
     * @param prm_pElem �v�f
     * @param tX1 �v�f�ΏۃI�u�W�F�N�g�̊O�g�̍��W
     * @param tY1 �V
     * @param tZ1 �V
     * @param tX2 �V
     * @param tY2 �V
     * @param tZ2 �V
     */
    virtual void registerElem(GgafLinearOctreeElem* prm_pElem,
                              int tX1, int tY1, int tZ1,
                              int tX2, int tY2, int tZ2);

    /**
     * �����؋�Ԃɓo�^����Ă���S�v�f����������i��������Ԃɂ���j.
     * �{���\�b�h�N���A�����Ȃ�΁A<BR>
     * registerElem() <BR>
     * �ɂ�蔪���؂֍ēx�v�f�o�^���\�ƂȂ�B
     */
    virtual void clearElem();

    /**
     * ����Level��Ԃ̔����؃��[�g�������̒ʂ���Ԕԍ��擾 .
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
    inline uint32_t getMortonOrderNumFromXYZindex( uint32_t x_space_index, uint32_t y_space_index, uint32_t z_space_index ) {
        return separateEveryThirdBit(x_space_index) | separateEveryThirdBit(y_space_index)<<1 | separateEveryThirdBit(z_space_index)<<2;
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
    inline uint32_t separateEveryThirdBit(uint32_t n) {
        n = ( n | n<<8 ) & 0x0000f00f;
        n = ( n | n<<4 ) & 0x000c30c3;
        n = ( n | n<<2 ) & 0x00249249;
        return n;
    }


    virtual ~GgafLinearOctree();
    /**
     * �f�o�b�O�p�c���[�󋵏o�� .
     */
    void putTree();
};

}
#endif /*GGAFLINEAROCTREE_H_*/

