#include "GgafCommonHeader.h"
#define DEBUG
#define MaxSplineSize 100


#define SPACE_MAXLEVEL     7
/**
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
 *
 *
 */
template<class T>
class GgafLinearOctree {

public:


    class Elem;

    class Space {
    public:
        /** �v�f�̐擪 */
        int _ary_index;
        int _belong_elem;
        Elem* _pElemFirst;
        Elem* _pElemLast;

        Space() {
            _pElemFirst = NULL;
            _pElemLast = NULL;
            _ary_index = 0;
            _belong_elem = 0;
        }

        bool push(Elem* prm_pElem) {
            if(prm_pElem) {
                return false;
            } else {
                processOnIncommingElem(prm_pElem);
                return true;
            }
        }

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
                _pElemLast = prm_pElem;
            } else {
                _pElemLast->_pNext = prm_pElem;
                prm_pElem->_pPrev = _pElemLast;
                prm_pElem->_pNext = NULL;
            }

        }

        void dump() {
            if (!_pElemFirst) {
                _TEXT_("x");
            } else {
                Elem* pElem = _pElemFirst;
                while (true) {
                    pElem->dump();

                    if (pElem == _pElemLast) {
                        break;
                    }
                    pElem = pElem -> _pNext;
                }
            }
        }
    };

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

        Elem(T* prm_pObject) {
            _pSpace_Current = NULL;
            _pNext = NULL;
            _pPrev = NULL;
            _pObject = prm_pObject;
        }

        /**
         * ���g������Ԃֈړ�
         * @param prm_pSpace_target
         */
        Elem* moveToSpace(Space* prm_pSpace_target) {
            if (prm_pSpace_target == _pSpace_Current) {
                return NULL; //�ړ�����ł���
            }
            if (_pSpace_Current) { //���ɏ������Ă�ꍇ(�V�KElem����Ȃ��ꍇ)
                _pSpace_Current->processOnRemoveElem(this); //�����܂���ʒm
            }
            _pNext = NULL;
            _pPrev = NULL;
            prm_pSpace_target->processOnIncommingElem(this); //����܂���ʒm
            return this;
        }

        /**
         * ���g�����E
         */
        Elem* extractFromCurrentSpace() {
            _pSpace_Current->processOnRemoveElem(this);
            _pNext = NULL;
            _pPrev = NULL;
        }

        void dump() {
            _TEXT_("o");
        }
    };

    /** 8���؂̋�Ԃ��Ӗ�������`�z�� */
    Space** _papSpace; //_papSpace[0] �� ROOT��Ԃւ̃|�C���^


    int _root_X1; //root��Ԃ�x���W�̏�������
    int _root_Y1; //root��Ԃ�y���W�̏�������
    int _root_Z1; //root��Ԃ�z���W�̏�������
    int _root_X2; //root��Ԃ̑Ίp�̒��_�ƂȂ�x���W�傫����
    int _root_Y2; //root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�傫����
    int _root_Z2; //root��Ԃ̑Ίp�̒��_�ƂȂ�z���W�傫����
    int _top_level_dX;  //�ŏ���Ԃ�X�̋���
    int _top_level_dY;  //�ŏ���Ԃ�Y�̋���
    int _top_level_dZ;  //�ŏ���Ԃ�Z�̋���


    DWORD* _paPow;
    DWORD _num_space;
    /** �ő��ԃ��x�� */
    DWORD _top_space_level; //���[�g��Ԃ�Level=0



    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�pActor
     */
    GgafLinearOctree(int prm_level, int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2) {
        _top_space_level = prm_level;
        //�ׂ���쐬
        _paPow = NEW DWORD[SPACE_MAXLEVEL+1];
        _paPow[0] = 1;
        for(int i = 1; i < SPACE_MAXLEVEL + 1; i++) {
            _paPow[i] = _paPow[i-1] * 8;
            _TRACE_("_paPow["<<i<<"]="<< _paPow[i]);
        }

        //���`�W���ؔz��쐬
        _num_space = (_paPow[_top_space_level+1] -1) / 7; //��Ԑ�
        _TRACE_("_num_space="<<_num_space);
        if (_num_space > 100000) {
            return;
        }
        _papSpace = NEW Space*[_num_space];
        for (int i = 0; i < _num_space; i++) {
            _papSpace[i] = NEW Space();
            _papSpace[i]->_ary_index = i;
        }

        _root_X1 = X1;
        _root_Y1 = Y1;
        _root_Z1 = Z1;
        _root_X2 = X2;
        _root_Y2 = Y2;
        _root_Z2 = Z2;
        _top_level_dX = (_root_X2-_root_X1) / ((float)(1<<_top_space_level));
        _top_level_dY = (_root_Y2-_root_Y1) / ((float)(1<<_top_space_level));
        _top_level_dZ = (_root_Z2-_root_Z1) / ((float)(1<<_top_space_level));
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
    void registElem(Elem* prm_pElem, int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {
        //��ԍ��W�C���f�b�N�X
        DWORD index = getSpaceIndex(tX1, tY1, tZ1, tX2, tY2, tZ2);


        _TRACE_("registElem:index="<<index);
        prm_pElem->moveToSpace(_papSpace[index]);

        // �����̗v�f�ԍ�
        while(true) {
            //�v�f���ǉ�����܂�����J�E���g
            _papSpace[index]->_belong_elem ++;
            _TRACE_("_papSpace["<<index<<"]->_belong_elem ++  "<<(_papSpace[index]->_belong_elem));
            if (index == 0) {
                break;
            }
            // �e��ԗv�f�ԍ��ŌJ��Ԃ�
            index = (index-1)>>3;

        }
    }



    // ���W�����Ԕԍ��i���`�����؁j���Z�o

    /**
     * ���W�����Ԕz��v�f�ԍ��i���`�����ؔz��̗v�f�ԍ��j���Z�o .
     * �܂��ABOX�̏������ Level �ƁA���̋��Level�̃��[�g�������ʂ���Ԕԍ�������
     * �v�Z���Ĕz��Index��Ԃ��܂�
     * @param tX1
     * @param tY1
     * @param tZ1
     * @param tX2
     * @param tY2
     * @param tZ2
     * @return ��Ԕԍ�
     */
    DWORD getSpaceIndex(int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {

        //�܂��ABOX�̏������ Level �ƁA���̋��Level�̃��[�g�������ʂ���Ԕԍ������߂�

        //BOX�̍����O��XYZ���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
        DWORD minnum_in_toplevel = getMortonOrderNumFromXYZindex(
                                      (DWORD)((tX1 - _root_X1) / _top_level_dX),
                                      (DWORD)((tY1 - _root_Y1) / _top_level_dY),
                                      (DWORD)((tZ1 - _root_Z1) / _top_level_dZ)
                                    );


        //BOX�̉E������XYZ���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
        DWORD maxnum_in_toplevel = getMortonOrderNumFromXYZindex(
                                      (DWORD)((tX2 - _root_X1) / _top_level_dX),
                                      (DWORD)((tY2 - _root_Y1) / _top_level_dY),
                                      (DWORD)((tZ2 - _root_Z1) / _top_level_dZ)
                                    );


        //������BOX�́A�ǂ̃��x���̋�Ԃɏ������Ă���̂��擾
        DWORD differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
        DWORD shift_num = 0;
        for(DWORD i = 0; i < _top_space_level; i++) {
            if ((differ_bit_pos>>(i*3)) & 0x7 != 0 ) {
                shift_num = i+1;
            }
        }
        //xor����differ_bit_pos �� �E��3�r�b�g�V�t�g���A�}�X�N &B111(&H7) ��AND�����A&B000 �łȂ��Ȃ��Ă���ʒu������ׂ�B
        //����� differ_bit_pos �� �R�r�b�g�ɋ�؂�A����3�r�b�g���H������Ă���ӏ�������ׂĂ���
        //�H���Ⴄ3�r�b�g�̈ʒu�́A���̃��x���̃��g�[�������ʒu���H������Ă��邱�Ƃ��Ӗ�����B
        //�ł�����3�r�b�g���H������Ă���ӏ�(�V�t�g�񐔁�shift_num)��菊����ԃ��x�����킩��
        //�ő��ԕ���Level = 5�Ƃ��āA�����O��6001�ԁA�E������6041�Ԃɏ������Ă���BOX���ɂ����
        //
        //�e���x����Ԃ̃��[�g�������ʒu                             lv0 lv1 lv2 lv3 lv4 lv5
        //     6001 = 00 000 000 000 000 000 001 011 101 110 001
        // XOR)6041 = 00 000 000 000 000 000 001 011 110 011 001
        // -----------------------------------------------------
        //      232 = 00 000 000 000 000 000 000 000 011 101 000
        //
        //                                                   111
        //                                               111
        //                                           111
        //                                       111
        //  AND)                             111     <--- �����܂ōs���āA�ł�����3�r�b�g���H������Ă���ӏ���3��ڂ��������Ƃ�����
        // ------------------------------------------------------
        //                                   000 000 011 101 000
        //                                    o   o   x   x   o      if (differ_bit_pos>>(i*3)) & 0x7 != 0 ) �̔���
        //                                    5   4   3   2   1   0   shift_num(�V�t�g��)
        //
        //   ��L���A6001�Ԃ�6041�Ԃ͋�ԃ��x��1�A���x��2 �܂ł͓�����ԃ��x���ɑ����Ă�����
        //   ��ԃ��x��3���烂�[�g�������ʒu���قȂ��Ă��܂����Ƃ�����B���������āA
        //   �u������ԃ��x���v��Lv2��Ԃł���Ƃ킩��B����𒲂ׂ邽�߂�
        //   XOR��0�ȊO�ɂȂ�ō��̃V�t�g��  shift_num = 3�� �����߂�B
        //   ���߂邽�߂ɂ́A�E��3�r�b�g�V�t�g���� 0x7 �� AND�𒲂ׂ邱�Ƃ��J��Ԃ��K�v������Ƃ������Ƃ��B
        //   shift_num �̃V�t�g�񐔂𒲂ׂ�΁A������ԃ��x��������I

        //����XOR���ʂ�
        // 000 000 000 000 000 000 000 111 �̏ꍇ�Ȃ�� shift_num=1
        //�����
        //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����4(=��ԃ��x��5�ŐH���Ⴄ)
        //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����7(=��ԃ��x��8�ŐH���Ⴄ)

        // 000 000 000 111 110 000 101 111 �Ȃǂ̏ꍇ�� shift_num=5
        //�����
        //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����0 �܂胋�[�g��ԃ��x������
        //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����4

        //�܂Ƃ߂��
        //�ő��ԕ���Level = 5 �̏ꍇ
        //shift_num   = 0 1 2 3 4 5
        //�������Level = 5 4 3 2 1 0
        //�ő��ԕ���Level=8 �̏ꍇ
        //shift_num   = 0 1 2 3 4 5 6 7 8
        //�������Level = 8 7 6 5 4 3 2 1 0

        //������Ԃ̃��[�g�������̒ʂ���Ԕԍ������߂�
        DWORD morton_order_space_num = minnum_in_toplevel>>(shift_num*3);
        //�s�����̉��ʂ̃r�b�g��3�r�b�g�P�ʂŏ������A�����̃��[�g�������ԍ������߂�
        //
        // minnum_in_toplevel>>(shift_num*3); �ɂ��āA
        // minnum_in_toplevel=6001 �ł� 6041�ł��ǂ���ł��悭
        //        lv0 lv1 lv2 lv3 lv4 lv5          lv0 lv1 lv2
        // 6001 = 000 001 011 101 110 001   -->    000 001 011 = 11
        // 6041 = 000 001 011 110 011 001   -->    000 001 011 = 11
        //                    ^^^ ^^^ ^^^
        //                  (shift_num*3 �r�b�g����)
        //
        // �̂悤�ɕs�����̃r�b�g���E�փV�t�g���Ă���
        // ����ŁA�����O��6001�ԁA�E������6041�ԂƂ���BOX�́A�������Lv2�̏ꍇ�́A���[�g�������ʂ���Ԕԍ�11�Ԃł��������Ƃ��킩��B
        // ���Ƃ͂����z��Index�ɕϊ�����̂�

        //�������(�V�t�g��)�Ƃ��̋�Ԃ̃��[�g�������ʂ���Ԕԍ�������`�����ؔz��̗v�f�ԍ������߂�
        DWORD index = morton_order_space_num + (_paPow[_top_space_level-shift_num]-1)/7;
        //������ԃ��x����  _top_space_level - shift_num �ŋ��܂�
        //�u8�̋�ԃ��x����v���邱�ƂŁA���̃��x����Ԃ�0�Ԃ̔z��v�f�ԍ����Z�o(-1 �� �z��� 0 ����n�܂邽��)
        //��̗�ł����� shift_num = 3 �ŁA�ő��ԕ���Level(_top_space_level) = 5 �ł���̂�
        // 5 - 3 = 2 �ŏ�����ԃ��x���� 2
        // 8 ^ 2 = 64 �܂� ��ԃ��x��2 �̃��[�g�������ʂ���Ԕԍ���0�Ԃ́A�z���64�ԖځB64�Ԗڂ̗v�f�ԍ���-1���� 63�B
        //�Ō�ɁA���̏�����ԃ��x���̃��[�g�������ʂ���Ԕԍ�(morton_order_space_num)�𑫂��B
        //11 + 63 = 74 ����Ĕz��v�f�ԍ���74�ƂȂ�
        _TRACE_("minnum_in_toplevel="<<minnum_in_toplevel<<"/maxnum_in_toplevel="<<maxnum_in_toplevel<<
                "differ_bit_pos="<<differ_bit_pos<<"/shift_num="<<shift_num<<"/morton_order_space_num="<<morton_order_space_num<<
                "index="<<index);
#ifdef OREDEBUG
        if(index > _num_space) {
            _TRACE_("minnum_in_toplevel="<<minnum_in_toplevel<<"/maxnum_in_toplevel="<<maxnum_in_toplevel<<
                    "differ_bit_pos="<<differ_bit_pos<<"/shift_num="<<shift_num<<"/morton_order_space_num="<<morton_order_space_num<<
                    "index="<<index);
        }
#endif
        return index;
    }


    // ���W�����`8���ؗv�f�ԍ��ϊ��֐�
    WORD getIndex(int tX, int tY, int tZ) {
        return getMortonOrderNumFromXYZindex(
                    (tX - _root_X1) / _top_level_dX,
                    (tY - _root_Y1) / _top_level_dY,
                    (tZ - _root_Z1) / _top_level_dZ
               );
    }

    // 3D���[�g����Ԕԍ��Z�o�֐�


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

    void dump() {
        int idx = 0;
        Space* _pSpace;
        for (int lv = 0; lv < _top_space_level; lv++) {
            for (int n = 0; n < _paPow[lv]; n++) {
                _pSpace = _papSpace[idx];
                _TEXT_("["<<idx<<"] ("<<lv<<"-"<<n<<")=");
                _pSpace.dump();
                _TEXT_("\n");
            }
        }
    }

    virtual ~GgafLinearOctree() {
    }
};

#define VULL ((void *)1)

int main() {
    GgafLinearOctree<int>* pLinearOctree =
            NEW GgafLinearOctree<int>
                (
                    5,
                    -8000 ,-8000 ,-8000 ,8000 ,8000 ,8000
                );
    int* xxx = NEW int(2);

    GgafLinearOctree<int>::Elem* pElem = NEW GgafLinearOctree<int>::Elem(xxx);
    pLinearOctree->registElem(pElem, 10 ,10 ,10, 41 ,51 ,61);
    pLinearOctree->registElem(pElem, 7000 ,7000 ,7000, 7999 ,7999 ,7999);
    pLinearOctree->registElem(pElem, 1 ,1 ,1, 1 ,1 ,1);
    _TRACE_("----------------------------------------------------------------������")
    int aPow[8];
    aPow[0] = 1;
    for(int i = 1; i < 8; i++) {
        aPow[i] = aPow[i-1] * 8;
    }
    int idx0 = 0;
    int LV0 = 0;

    for (int LV1 = 0; LV1 < 8; LV1++) {
        int mn1 = LV1;
        int idx1 = aPow[0] +
                    LV1;

        if (pLinearOctree->_papSpace[idx1]->_belong_elem == 0) {
            continue;
        } else {
            _TEXT_(" L1["<<LV1<<","<<mn1<<","<<idx1<<"]");
            pLinearOctree->_papSpace[idx1]->dump();
            _TEXT_("\n");
        }
        for (int LV2 = 0; LV2 < 8; LV2++) {
            int mn2 = LV1*aPow[1] +
                      LV2;
            int idx2 = aPow[0]+ aPow[1] +
                       LV1*aPow[1] +
                       LV2;


            if (pLinearOctree->_papSpace[idx2]->_belong_elem == 0) {
                continue;
            } else {
                _TEXT_("   L2["<<LV2<<","<<mn2<<","<<idx2<<"]");
                pLinearOctree->_papSpace[idx2]->dump();
                _TEXT_("\n");
            }
            for (int LV3 = 0; LV3 < 8; LV3++) {
                int mn3 = LV1*aPow[2] +
                          LV2*aPow[1] +
                          LV3;
                int idx3 = aPow[0]+ aPow[1] + aPow[2] +
                            LV1*aPow[2] +
                            LV2*aPow[1] +
                            LV3;

                if (pLinearOctree->_papSpace[idx3]->_belong_elem == 0) {
                    continue;
                } else {
                    _TEXT_("    L3["<<LV3<<","<<mn3<<","<<idx3<<"]");
                    pLinearOctree->_papSpace[idx3]->dump();
                    _TEXT_("\n");
                }
                for (int LV4 = 0; LV4 < 8; LV4++) {
                    int mn4 =LV1*aPow[3] +
                            LV2*aPow[2] +
                            LV3*aPow[1] +
                            LV4;
                    int idx4 = aPow[0]+ aPow[1] + aPow[2] + aPow[3] +
                                LV1*aPow[3] +
                                LV2*aPow[2] +
                                LV3*aPow[1] +
                                LV4;



                    if (pLinearOctree->_papSpace[idx4]->_belong_elem == 0) {
                        continue;
                    } else {
                        _TEXT_("     L4["<<LV4<<","<<mn4<<","<<idx4<<"]");
                        pLinearOctree->_papSpace[idx4]->dump();
                        _TEXT_("\n");
                    }
                    for (int LV5 = 0; LV5 < 8; LV5++) {
                        int mn5 =   LV1*aPow[4] +
                                    LV2*aPow[3] +
                                    LV3*aPow[2] +
                                    LV4*aPow[1] +
                                    LV5;
                        int idx5 =  aPow[0]+ aPow[1] + aPow[2] + aPow[3] + aPow[4] +
                                    LV1*aPow[4] +
                                    LV2*aPow[3] +
                                    LV3*aPow[2] +
                                    LV4*aPow[1] +
                                    LV5;

                        if (pLinearOctree->_papSpace[idx5]->_belong_elem == 0) {
                            continue;
                        } else {
                            _TEXT_("      L5["<<LV5<<","<<mn5<<","<<idx5<<"]");
                            pLinearOctree->_papSpace[idx5]->dump();
                            _TEXT_("\n");
                        }

                    }
                }
            }
        }
    }

}



