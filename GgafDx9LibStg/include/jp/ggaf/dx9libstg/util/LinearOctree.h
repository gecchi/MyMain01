#ifndef LINEAROCTREE_H_
#define LINEAROCTREE_H_
namespace GgafDx9LibStg {

template<class T>
class LinearOctree {

public:


    class Elem;

    class Space {
    public:
        /** �v�f�̐擪 */
        Elem* _pElemFirst;
        Elem* _pElemLast;
        /**
         * �v�f���ړ�����Ƃ��ɌĂяo�����R�[���o�b�N�B
         * @param prm_pElem �ړ����������Ă�v�f�B
         */
        void processOnRemoveElem(Elem* prm_pElem) {
            prm_pElem->_pPrev->_pNext = prm_pElem->_pNext;
            prm_pElem->_pNext->_pPrev = prm_pElem->_pPrev;
            if (prm_pElem == _pElemFirst) {
                _pElemFirst = prm_pElem->_pNext;
            }
            if (prm_pElem == _pElemLast) {
                _pElemLast = prm_pElem->_pPrev;
            }
        }

        /**
         * �V�����v�f�̎󂯓���B .
         * �v�f�𖖔��ɒǉ�
         * @param prm_pElem �j���[�J�}�[�v�f�i�������A�O��v�f��NULL���O��)
         */
        void processOnIncommingElem(Elem* prm_pElem) {
            if (_pElemFirst == NULL) {
                _pElemFirst = prm_pElem;
            } else {
                _pElemLast->_pNext = prm_pElem;
                prm_pElem->_pPrev = _pElemLast;
                prm_pElem->_pNext = NULL;
            }

        }
    }

    class Elem {
    public:
        /** ������� */
        Space* _pSpace_Current;

        /** ���v�f */
        Elem* _pNext;
        /** �O�v�f */
        Elem* _pPrev;
        /** �ΏۃI�u�W�F�N�g */
        T* _pObject;

        /**
         * ���g������Ԃֈړ�
         * @param prm_pSpace_target
         */
        Elem* moveTo(Space* prm_pSpace_target) {
            if (prm_pSpace_target == _pSpace_Current) {
                return; //�ړ�����ł���
            }
            _pSpace_Current->processOnRemoveElem(this);
            _pNext = NULL;
            _pPrev = NULL;
            prm_pSpace_target->processOnIncommingElem(this);
            return this;
        }

        /**
         * ���g�����E
         */
        Elem* extract() {
            _pSpace_Current->processOnRemoveElem(this);
            _pNext = NULL;
            _pPrev = NULL;
        }
    }

    /** 8���؂̋�Ԃ��Ӗ�������`�z�� */
    Space** _papSpace[]; //_papSpace[0] �� ROOT��Ԃւ̃|�C���^


    int _root_X1; //root��Ԃ�x���W�̏�������
    int _root_Y1; //root��Ԃ�y���W�̏�������
    int _root_Z1; //root��Ԃ�z���W�̏�������
    int _root_X2; //root��Ԃ̑Ίp�̒��_�ƂȂ�x���W�傫����
    int _root_Y2; //root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�傫����
    int _root_Z2; //root��Ԃ̑Ίp�̒��_�ƂȂ�z���W�傫����
    int _max_level_dX;  //�ŏ���Ԃ�X�̋���
    int _max_level_dY;  //�ŏ���Ԃ�Y�̋���
    int _max_level_dZ;  //�ŏ���Ԃ�Z�̋���


    int* _paPow[];
    int _num_space;
    /** �ő��ԃ��x�� */
    DWORD _level; //���[�g��Ԃ�Level=0



    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    LinearOctree(int prm_level, int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2) {
        _level = prm_level;
        //�ׂ���쐬
        _paPow = NEW int[_level+1];
        _paPow[0] = 1;
        for(int i = 1; i < _level + 1; i++) {
            _paPow[i] = _paPow[i-1]*8;
        }

        //���`�W���ؔz��쐬
        _num_space = (_paPow[_level+1] -1) / 7; //��Ԑ�
        _papSpace = NEW Space*[_num_space];
        for (int i = 0; i < _num_space; i++) {
            _papSpace[i] = NEW Space();
        }

        _X1 = X1;
        _Y1 = Y1;
        _Z1 = Z1;
        _X2 = X2;
        _Y2 = Y2;
        _Z2 = Z2;
        _min_dX = (_X2-_X1) / ((float)(1<<Level));
        _min_dY = (_Y2-_Y1) / ((float)(1<<Level));
        _min_dZ = (_Z2-_Z1) / ((float)(1<<Level));
    }


    /**
     *
     * @return
     */

    /**
     * �v�f�𔪕��؋�Ԃɓo�^����
     * @param prm_pElem �v�f
     * @param prm_X �v�f�ΏۃI�u�W�F�N�g��X���W
     * @param prm_Y �v�f�ΏۃI�u�W�F�N�g��Y���W
     * @param prm_Z �v�f�ΏۃI�u�W�F�N�g��Z���W
     */
    void regist(Elem* prm_pElem, int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {
        //��ԍ��W�C���f�b�N�X


    }


    // ���W�����Ԕԍ����Z�o
    DWORD GetMortonNumber(int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {

        //BOX�̍����O��XYZ���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ԍ����Ԃ����擾
        DWORD min_num_in_maxlevel = getMortonOrderNumFromXYZindex(
                                      (DWORD)((tX1 - _root_X1) / _max_level_dX),
                                      (DWORD)((tY1 - _root_Y1) / _max_level_dY),
                                      (DWORD)((tZ1 - _root_Z1) / _max_level_dZ)
                                    );

        //BOX�̉E������XYZ���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ԍ����Ԃ����擾
        DWORD max_num_in_maxlevel = getMortonOrderNumFromXYZindex(
                                      (DWORD)((tX2 - _root_X2) / _max_level_dX),
                                      (DWORD)((tY2 - _root_Y2) / _max_level_dY),
                                      (DWORD)((tZ2 - _root_Z2) / _max_level_dZ)
                                     );
        //������BOX�́A�ǂ̃��x���̋�Ԃɂ����ۂ���܂��Ă��邩�擾

        DWORD differ_bit_pos = max_num_in_maxlevel ^ min_num_in_maxlevel;
        //differ_bit_pos �� �E��3�r�b�g���炵�Ȃ���}�X�N 111 ��AND�����A 000 �łȂ��Ȃ��Ă���ʒu������ׂ�B
        //����� differ_bit_pos �� �R�r�b�g�ɋ�؂�A����3�r�b�g���H������Ă���ӏ�������ׂĂ���
        //�ł�����3�r�b�g���H������Ă���ӏ�(�V�t�g�񐔁�shift_pos)��菊�����x�����킩��

        //XOR���ʂ�
        // 000 000 000 000 000 000 000 111 �̏ꍇshift_pos=1
        //�����
        //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����4
        //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����8

        // 000 000 000 000 000 000 101 000 �̏ꍇ�� shift_pos=2
        //�����
        //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����3
        //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����7

        // 000 000 000 111 110 111 101 111 �Ȃǂ̏ꍇ�� shift_pos=5
        //�����
        //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����0 �܂胋�[�g��ԏ���
        //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����4

        DWORD shift_pos = 0;
        //���၄
        //�ő��ԕ���Level = 5 �̏ꍇ
        //shift_pos =  0 1 2 3 4 5
        //����Level   =  5 4 3 2 1 0
        //�ő��ԕ���Level=8 �̏ꍇ
        //shift_pos =  1 2 3 4 5 6 7 8
        //����Level   =  7 6 5 4 3 2 1 0
        for(DWORD bit3_index = 0; bit3_index < _level; lv++) {
            if (differ_bit_pos>>(bit3_index*3)) & 0x7 != 0 ) {
                shift_pos = bit3_index+1;
            }
        }

   255        11 11 11 11
   768     11 00 00 00 00

 bit3_index   4  3  2  1  0
             11 11 11 11 11


        DWORD SpaceNum = RB>>(HiLevel*3);
        DWORD AddNum = (m_iPow[m_uiLevel-HiLevel]-1)/7;
        SpaceNum += AddNum;

        if(SpaceNum > m_dwCellNum)
            return 0xffffffff;

        return SpaceNum;
    }


    // ���W�����`8���ؗv�f�ԍ��ϊ��֐�
    WORD getIndex(int tX, int tY, int tZ) {
        return Get3DMortonNumber(
            (tX - _X1) / _min_dX,
            (tY - _Y1) / _min_dY,
            (tZ - _Z1) / _min_dZ
            );
    }

    // 3D���[�g����Ԕԍ��Z�o�֐�


    /**
     * ����Level��Ԃ̔����؃��[�g�������擾.
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
     * �������āAOR���܂��B�Ӗ��́A
     * 00000000 qia rjb skc tld ume vnf wog xph
     *                                      ^^^-->&B(xph) = ����Level�̋�Ԃ̒ʂ����[�g�������ԍ� 0�`7
     *                                  ^^^^^^^-->&B(wogxph) = ����Level�̐e��Ԃ̒ʂ����[�g�������ԍ� 0�`63
     *                              ^^^^^^^^^^^-->&B(vnfwogxph) = ����Level�̐e�̐e��Ԃ̒ʂ����[�g�������ԍ� 0�`511
     *
     *                          ^^^ ^^^ ^^^ ^^^
     *                           |   |   |   |
     *                           |   |   |   &B(xph) = ����Level�̋�Ԃ̃��[�g�������ʒu 0�`7
     *             ............  |   |   +---&B(wog) = ����Level�̐e��Ԃ̃��[�g�������ʒu  0�`7
     *                           |   +-------&B(vnf) = ����Level�̐e�̐e�̋�Ԃ̃��[�g�������ʒu 0�`7
     *
     *
     * @param x_index ����̃��x����Ԃ�x���W��ԃC���f�b�N�X (������ 0�`255 �Ƃ���)
     * @param y_index ����̃��x����Ԃ�y���W��ԃC���f�b�N�X (������ 0�`255 �Ƃ���)
     * @param z_index ����̃��x����Ԃ�z���W��ԃC���f�b�N�X (������ 0�`255 �Ƃ���)
     * @return ����Levell��Ԃ�(x_index, y_index, z_index)�Ŏ�������ԂɑΉ�����
     *         �����؃��[�g���ʂ����[�g�������ԍ�(�ő�Level8�ŁA0�`23068671)
     */
    DWORD getMortonOrderNumFromXYZindex( DWORD x_space_index, DWORD y_space_index, DWORD z_space_index ) {
       return separateEveryThirdBit(x_space_index)    |
              separateEveryThirdBit(y_space_index)<<1 |
              separateEveryThirdBit(z_space_index)<<2;
    }

    //�r�b�g�����֐�

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
     * n|n(n<<8) & 0x0000f00f =
     *              0000 0000 0000 0000 abcd 0000 0000 efgh �ƂȂ�B
     * ���̌��ʂ��܂� n �ɑ������
     * n          = 0000 0000 0000 0000 abcd 0000 0000 efgh
     * �ȉ����l��
     * n<<4       = 0000 0000 0000 abcd 0000 0000 efgh 0000
     * n|n<<4     = 0000 0000 0000 abcd abcd 0000 efgh efgh
     * 0x000c30c3 = 0000 0000 0000 1100 0011 0000 1100 0011
     * n �� n|n(n<<4) & 0x000c30c3 =
     *              0000 0000 0000 ab00 00cd 0000 ef00 00gh
     * n<<2       = 0000 0000 00ab 0000 cd00 00ef 0000 gh00
     * n|n(n<<2)  = 0000 0000 00ab ab00 cdcd 00ef ef00 ghgh
     * 0x00249249 = 0000 0000 0010 0100 1001 0010 0100 1001
     * n �� n|n(n<<2) & 0x00249249 =
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


    virtual ~LinearOctree();
};

}
#endif /*LINEAROCTREE_H_*/

