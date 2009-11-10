#ifndef GGAFLINEAROCTREE_H_
#define GGAFLINEAROCTREE_H_
namespace GgafCore {

#define SPACE_MAXLEVEL     7
/**
 * ���`�����؃N���X .
 *
 *   �p���`(4���؂ł̗�)
 *
 *
 *
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
 *
 *  �����[�g������ ��
 *  Z�̏��ԂŔԍ���U�邱�Ƃ��w��(8���؂ł�Z��Z)
 *  �����[�g�������ʂ��ԍ��A��Ԕԍ���
 *  ��L�̊e���x����ԂɐU���Ă��镪����Ԃ̔ԍ��̂���
 *  Lv2��Ԃ̃��[�g�������ʂ��ԍ���0�`15 �Ƃ����悤�Ɏg�����ƂƂ���B
 *  �����[�g�������ʒu��
 *  4���������ꍇ(8���؂ł�8����)�̍���A�E��A�����A�E���� ���ꂼ�� 0 1 2 3 (8���؂ł� 0�`7)�ƌĂԏꍇ������A
 *  �y��P�z
 *  Lv2 ��Ԃ� ���[�g�������ʒu  2 �Ƃ�����
 *  +--+--+
 *  | 8| 9|
 *  +--+--+
 *  |10|11|
 *  +--+--+
 *  ���w�����ƂƂ���B
 *
 *  �y��Q�z
 *  �uLv1�̋�Ԕԍ�3�̎q��Ԃ̃��[�g�������ʒu3�v�ƕ\�������ꍇ�́A
 *  Lv1�̋�Ԕԍ�3�̎q��ԁ�Lv2��Ԃ̉E���S��
 *  +--+--+
 *  |12|13|
 *  +--+--+
 *  |14|15|
 *  +--+--+
 *  �̂��Ƃ��w���A����̃��[�g�������ʒu3�Ȃ̂ŁALv2��ԃ��[�g�������ʂ��ԍ� 14 ���w���Ă邱�ƂƂ���B
 */
class GgafLinearOctree {

public:
    class Elem;

    /**
     * ��ԃN���X .
     */
    class Space {
    public:
        /** �v�f�̐擪 */
        int _my_index;
        int _belong_elem;
        Elem* _pElemFirst;
        Elem* _pElemLast;
        Space();
        void dump();
    };

    /**
     * ��ԗv�f�N���X .
     */
    class Elem {
    public:
        /** �����c���[ */
        GgafLinearOctree* _pLinearOctree;
        /** ������� */
        Space* _pSpace_Current;
        /** ���v�f */
        Elem* _pNext;
        /** �O�v�f */
        Elem* _pPrev;
        /** �ΏۃI�u�W�F�N�g */
        GgafObject* _pObject;
        /** �o�^���X�g�p�����N */
        Elem* _pRegLinkNext;

        Elem(GgafObject* prm_pObject);

        /**
         * ���g�����痣�E
         */
        void extract();

        /**
         * ���g�������Ԃ̖����ɒǉ�
         */
        void addElem(Space* prm_pSpace_target);

        /**
         * ���g�����瑼��Ԃֈړ�
         * extract()����addElem()���܂�.
         * @param prm_pSpace_target
         */
        void moveToSpace(Space* prm_pSpace_target);
        void dump();
    };

    /** 8���؂̋�Ԃ��Ӗ�������`�z�� */
    Space** _papSpace; //_papSpace[0] �� ROOT��Ԃւ̃|�C���^
    /**s     */
    Elem* _pRegElemFirst;
    /** root��Ԃ̑Ίp�̒��_�ƂȂ�x���W�̏������� */
    int _root_X1;
    /** root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�̏������� */
    int _root_Y1;
    /** root��Ԃ̑Ίp�̒��_�ƂȂ�z���W�̏������� */
    int _root_Z1;
    /** root��Ԃ̑Ίp�̒��_�ƂȂ�x���W�傫���� */
    int _root_X2;
    /** root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�傫���� */
    int _root_Y2;
    /** root��Ԃ̑Ίp�̒��_�ƂȂ�z���W�傫���� */
    int _root_Z2;
    /** �ŏ����(=�ō���ԃ��x��)��X�̋��� */
    int _top_level_dX;
    /** �ŏ����(=�ō���ԃ��x��)��Y�̋��� */
    int _top_level_dY;
    /** �ŏ����(=�ō���ԃ��x��)��Z�̋��� */
    int _top_level_dZ;

    /** 8�̗ݏ�̒l��\�ߌv�Z���ĕێ����Ă���z�� */
    DWORD* _paPow;
    /** �S��Ԑ� */
    DWORD _num_space;
    /** �ő��ԃ��x�� */
    DWORD _top_space_level; //���[�g��Ԃ�Level=0

    /**
     * ���`�����؋�Ԃ��\�z����.
     * @param prm_level �\�z�����ԃ��x��
     * @param X1 �\�z����O�g�̋�ԍ��W
     * @param Y1
     * @param Z1
     * @param X2
     * @param Y2
     * @param Z2
     * @return
     */
    GgafLinearOctree(int prm_level);



    virtual void setRootSpace(int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2);


    /**
     * �v�f�𔪕��؋�Ԃɓo�^����
     * @param prm_pElem �v�f
     * @param prm_X �v�f�ΏۃI�u�W�F�N�g��X���W
     * @param prm_Y �v�f�ΏۃI�u�W�F�N�g��Y���W
     * @param prm_Z �v�f�ΏۃI�u�W�F�N�g��Z���W
     */
    virtual void registElem(Elem* prm_pElem, int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2);


    virtual void clearElem();



    /**
     * ���W�����Ԕz��v�f�ԍ��i���`�����ؔz��̗v�f�ԍ��j���Z�o .
     * �܂��ABOX�̏������ Level �ƁA���̋��Level�̃��[�g�������ʂ���Ԕԍ�������
     * �v�Z���Ĕz��Index��Ԃ��܂�
     * @param tX1 �ΏۃI�u�W�F�N�g��BOX���W
     * @param tY1
     * @param tZ1
     * @param tX2
     * @param tY2
     * @param tZ2
     * @return ��Ԕԍ�
     */
    virtual DWORD getSpaceIndex(int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2);

    /**
     * ���W�����`8���ؗv�f�ԍ��ϊ��֐�
     * @param tX ���W
     * @param tY
     * @param tZ
     * @return
     */
    inline DWORD getIndex(int tX, int tY, int tZ) {
        return getMortonOrderNumFromXYZindex(
                    (tX - _root_X1) / _top_level_dX,
                    (tY - _root_Y1) / _top_level_dY,
                    (tZ - _root_Z1) / _top_level_dZ
               );
    }

    /**
     * ����Level��Ԃ̔����؃��[�g�������̒ʂ���Ԕԍ��擾.
     * ����Level�Ƃ͔C�ӂ�Level��Ԃ̂��Ƃł����A�����ƌ��ʂ͓���level��Ԃł���Ƃ����Ӗ��ł��B
     * ����Ă��邱�Ƃ�
     * �E���������ꂼ��3bit���ƂɊԊu���J����
     * �E����2�̌��ʂ�1�r�b�g�A����2�̌��ʂ�2�r�b�g  ���炵�� OR �����
     * �܂�
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
     *
     *                          ^^^ ^^^ ^^^ ^^^
     *                           |   |   |   |
     *                           |   |   |   &B(xph) = ����Level�̋�Ԃ̃��[�g�������̈ʒu 0�`7
     *             ............  |   |   +---&B(wog) = ����Level�̐e��Ԃ̃��[�g�������̈ʒu  0�`7
     *                           |   +-------&B(vnf) = ����Level�̐e�̐e�̋�Ԃ̃��[�g�������̈ʒu 0�`7
     *
     *
     * @param x_index ����̃��x����Ԃ�x���W��ԃC���f�b�N�X (������ 0�`255 �Ƃ���)
     * @param y_index ����̃��x����Ԃ�y���W��ԃC���f�b�N�X (������ 0�`255 �Ƃ���)
     * @param z_index ����̃��x����Ԃ�z���W��ԃC���f�b�N�X (������ 0�`255 �Ƃ���)
     * @return ����Levell��Ԃ�(x_index, y_index, z_index)�Ŏ�������ԂɑΉ�����
     *         �����؃��[�g�������̒ʂ���Ԕԍ�(�ő�Level8�ŁA0�`23068671)
     */
    inline DWORD getMortonOrderNumFromXYZindex( DWORD x_space_index, DWORD y_space_index, DWORD z_space_index ) {
       return separateEveryThirdBit(x_space_index)    |
              separateEveryThirdBit(y_space_index)<<1 |
              separateEveryThirdBit(z_space_index)<<2;
    }


    /**
     * 3bit���ƂɊԊu���J���� .
     * <code>
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
     * </code>
     * @param n 0�`255�܂ł̐��l
     * @return 3bit���ƂɊԊu���󂯂�ꂽ�l
     */
    inline DWORD separateEveryThirdBit(DWORD n) {
       n = ( n | n<<8 ) & 0x0000f00f;
       n = ( n | n<<4 ) & 0x000c30c3;
       n = ( n | n<<2 ) & 0x00249249;
       return n;
    }


    virtual ~GgafLinearOctree();

    void putTree();
};

}
#endif /*GGAFLINEAROCTREE_H_*/

