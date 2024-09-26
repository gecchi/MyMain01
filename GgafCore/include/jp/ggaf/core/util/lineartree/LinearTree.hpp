#ifndef GGAF_CORE_LINEARTREE_H_
#define GGAF_CORE_LINEARTREE_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/util/Util.h"
#include "jp/ggaf/core/util/lineartree/ITreeNodeElem.hpp"

#include <math.h>

namespace GgafCore {

#define MAX_TREE_LEVEL (20)

/**
 * ���`N���؋��� .
 * ���`4���؂Ɛ��`8���؂̋��ʏ������܂Ƃ߂��N���X
 * @tparam T ��Ԃɓo�^������I�u�W�F�N�g�̌^
 * @tparam DIM �����B2�̏ꍇ4���؁A3�̏ꍇ8���؂̋@�\�ƂȂ�B
 * @version 1.00
 * @since 2022/12/11
 * @author Masatoshi Tsuge
 */
template<class T, int DIM, int N>
class LinearTree : public Object {

public:

    /**
     * ���`N���ؔz��p��ԃN���X .
     * @version 1.00
     * @since 2009/11/23
     * @author Masatoshi Tsuge
     */
    class NodeSpace : public Object {
    public:
        /** [r]���`N���ؔz��̎��g�̗v�f�ԍ� */
        uint32_t _self_index;
        /** [r]���̋�ԁ{�q����Ԃɏ������Ă�v�f�̎�ʏ�� */
        kind_t _kind_bit_field;
        /** [r]���̋�Ԃɓo�^���ꂽ�v�f�A�����X�g�̍��{�B_pNextNodeElem �ŘA������Ă���B */
        ITreeNodeElem* _pRootNodeElem;
        /** [r]�o�^���s������ԘA�����X�g�p�A���̋��(�J�����Ɏg�p) */
        NodeSpace* _pRegNodeSpaceNext;

    public:
        /**
         * �R���X�g���N�^
         * @return
         */
        NodeSpace() : Object() {
            _pRootNodeElem = nullptr;
            _kind_bit_field = 0;
            _self_index = 0xffffffff; //���肦�Ȃ�0xffffffff�����Ă���
            _pRegNodeSpaceNext = nullptr;
        }

        /**
         * �v�f�o�^ .
         * @param prm_pNodeElem �v�f
         * @return true:���̃C���f�b�N�X�ɏ���o�^ �^ false:����ȊO
         */
        void registerElem(ITreeNodeElem* prm_pNodeElem) {
            //�����̗v�f�ԍ�
            uint32_t index = _self_index;
            const kind_t this_kind = prm_pNodeElem->_kind;
            NodeSpace* p = this; //= & _paNodeSpaceArray[index]
            while (true) {
                if (p->_kind_bit_field & this_kind) {
                    //������ʏ�񂪐ݒ�ς݂Ȃ�΁A����ȏ�̐e���ݒ�ςׁ݂̈A������
                    break;
                } else {
                    //��ԂɎ�ʏ�񂪖��ݒ�Ȃ�ΐݒ�
                    p->_kind_bit_field |= this_kind;
                }
                if (index == 0) {
                    break;
                }
                //���̐e��ԗv�f�ԍ��ŌJ��Ԃ�
                index = (index-1)>>DIM;
                p = p - (p->_self_index - index);
            }
            prm_pNodeElem->_pNextNodeElem = _pRootNodeElem; //����� _pRootNodeElem == nullptr
            _pRootNodeElem = prm_pNodeElem;
        }

        void dump() {
            if (_pRootNodeElem == nullptr) {
                _TRACE_N_(""); //�m�[�h�Ȃ�
            } else {
                ITreeNodeElem* pElem = _pRootNodeElem;
                while (pElem) {
                    pElem->dump();
                    pElem = pElem ->_pNextNodeElem;
                }
            }
        }
        virtual ~NodeSpace() {
        }
    };

public:
    /** [r]N���؂�N�A2��DIM��̒l������iDIM:2��4, DIM:3��8,�c)�B	 */
//    const uint32_t _N;
    /** [r]N���؂̋�Ԃ��꒼���ɕ��ׂ����`�z�� */
    NodeSpace* _paNodeSpaceArray; //_paNodeSpaceArray[0] �� ROOT��Ԃւ̃|�C���^
    /** [r]�o�^���s������ԘA�����X�g�̍��{�B��ԊJ�����Ɏg�p�B_pRegNodeSpaceNext �ŘA������Ă���B�iclearAllElem() �Ŏg�p����j */
    NodeSpace* _pRegNodeSpaceList;
    /** [r]�ő��ԃ��x�� */
    const uint32_t _top_space_level; //���[�g��Ԃ�Level=0
    /** [r]�S��Ԑ� */
    uint32_t _num_space;
    char _aChar_strbit[33];
    /** [r]N�iN���؂�N�j��2��̔z��A�v�Z�p�B(20�͏\���ő僌�x����ԂƎv����K���Ȓl) */
    uint32_t POW_N[MAX_TREE_LEVEL];

    /**
     * �R���X�g���N�^ .
     * @param prm_level �\�z�����ԃ��x��
     * @param prm_max_tree_level �z��ł���ő��ԃ��x��
     */
    LinearTree(uint32_t prm_level) : Object(),
    _top_space_level(prm_level) {
#ifdef MY_DEBUG
    if (prm_level > MAX_TREE_LEVEL) {
        throwCriticalException("LinearTree::LinearTree() ��ԃ��x���I�[�o�[�I prm_level="<<prm_level);
    }
#endif
        //�v�Z�p�ݏ�̔z��
        for (int lv = 0; lv < MAX_TREE_LEVEL; lv++) {
            POW_N[lv] = (uint32_t)(pow((double)N , lv));
        }
        //�S��Ԑ������߂�
        _num_space = ((uint32_t)((POW_N[_top_space_level+1] -1) / (N-1)));
        //���`N���ؔz��쐬
        _paNodeSpaceArray = NEW NodeSpace[_num_space];
        for (uint32_t i = 0; i < _num_space; i++) {
            _paNodeSpaceArray[i]._self_index = i;
        }
        _pRegNodeSpaceList = nullptr;
    }

    /**
     * �v�f����Ԃɓo�^ .
     * @param prm_pNodeElem
     * @param minnum_in_toplevel BOX�̍�����O��XYZ���W�_�����������Ԃ́A�ő僌�x���̋�ԁi��������Ȃ��ł��[����ԁj�ł̃��[�g�������ʂ���Ԕԍ�
     * @param maxnum_in_toplevel BOX�̉E�㉜��XYZ���W�_�����������Ԃ́A�ő僌�x���̋�ԁi��������Ȃ��ł��[����ԁj�ł̃��[�g�������ʂ���Ԕԍ�
     */
    void registerElem(ITreeNodeElem* prm_pNodeElem, const uint32_t minnum_in_toplevel, const uint32_t maxnum_in_toplevel) {
        //�ǂ̃��x���̋�Ԃɏ������Ă���̂��擾
        const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
        uint32_t shift_num = 0;
        for (uint32_t i = 0; i < _top_space_level; i++) {
            if (((differ_bit_pos>>(i*DIM)) & (N-1)) != 0 ) {
                shift_num = i+1;
            }
        }
        //�yDIM=3, N=8 �̐��`�����؋�Ԕz��ł̏��������z
        //xor����differ_bit_pos �� �E��3�r�b�g�V�t�g���A�}�X�N &B111(&H7) ��AND�����A&B000 ��
        //�Ȃ��Ȃ��Ă���ꍇ�Ashift_num�ɒl�����B
        //�܂肱��� differ_bit_pos �� �܂� �R�r�b�g�ɋ�؂�A����3�r�b�g���H������Ă���ӏ��̂����A
        //�ł������ʒu������ׂĂ���B
        //�H���Ⴄ3�r�b�g�̈ʒu�́A���̃��x���̃��g�[�������ʒu���H������Ă��邱�Ƃ��Ӗ�����B
        //���������čł�����3�r�b�g���H������Ă���ӏ�(�V�t�g�񐔁�shift_num)��菊����ԃ��x�����킩��
        //�ő��ԕ���Level = 5�Ƃ��āA������O��6001�ԁA�E�㉜��6041�Ԃɏ������Ă���BOX���ɂ����
        //
        //                               lv0 lv1 lv2 lv3 lv4 lv5 ����e���x����Ԃ̃��[�g�������ʒu
        //     6001 = 00 000 000 000 000 000 001 011 101 110 001
        // XOR)6041 = 00 000 000 000 000 000 001 011 110 011 001
        // -----------------------------------------------------
        //      232 = 00 000 000 000 000 000 000 000 011 101 000
        //
        //                                                   111 �E�E�E �}�X�N
        //                                               111
        //                                           111
        //                                       111
        //  AND)                             111     <--- �����܂ōs���āA�ł�����3�r�b�g���H������Ă���ӏ���3��ڂ��������Ƃ�����
        // ------------------------------------------------------
        //                                   000 000 011 101 000     <--- ������̃}�X�N���ʂ�  000 �ŁA���ꂪ��������A6001�Ԃ�6041�Ԃ̃��[�g�������ʒu�������ł���i=�����Ԃɏ����j���Ӗ�����
        //                                    f   f   t   t   f      if (differ_bit_pos>>(i*3)) & 0x7 != 0 ) �̔���
        //                                    5   4   3   2   1   0  shift_num(�V�t�g��)
        //                                    o   o   x(�ȍ~x)        �����Ԃɓ����Ă��锻��i������݂�j
        //
        //   ��L���A6001�Ԃ�6041�Ԃ͋�ԃ��x��1�A���x��2 �܂ł͓�����ԃ��x���ɑ����Ă������A
        //   ��ԃ��x��3���烂�[�g�������ʒu���قȂ��Ă��܂����Ƃ�����B���������āA
        //   �u������ԃ��x���v��Lv2��Ԃł���Ɗm��ł���B����𒲂ׂ邽�߂�
        //   XOR��0�ȊO�ɂȂ�ō��̃V�t�g��  shift_num = 3 �����߂�B
        //   ���߂邽�߂ɂ́A�E��3�r�b�g�V�t�g���� 0x7 �� AND�𒲂ׂ邱�Ƃ��J��Ԃ��K�v������Ƃ������Ƃ��B
        //   Level = 5�̏ꍇ�A5��J��Ԃ��A�v�� shift_num �̃V�t�g�񐔂𒲂ׂ�΁A������ԃ��x��������I

        //����XOR���ʂ�
        // 00 000 000 000 000 000 000 000 000 111 �̏ꍇ�Ȃ�� shift_num=1
        //�����
        //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����4(=��ԃ��x��5�ŐH���Ⴄ)
        //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����7(=��ԃ��x��8�ŐH���Ⴄ)

        // 00 000 000 000 000 111 110 000 101 111 �Ȃǂ̏ꍇ�� shift_num=5
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
        const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*DIM);

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
        // ����ŁA������O��6001�ԁA�E�㉜��6041�ԂƂ���BOX�́A�������Lv2�̏ꍇ�́A���[�g�������ʂ���Ԕԍ�11��(0�Ԃ��琔����)�ł��������Ƃ��킩��B
        // ���Ƃ͂����z��Index�ɕϊ�����̂�

        //�������(�V�t�g��)�Ƃ��̋�Ԃ̃��[�g�������ʂ���Ԕԍ�������`�����ؔz��̗v�f�ԍ������߂�
        const uint32_t index = morton_order_space_num + (POW_N[_top_space_level-shift_num]-1)/(N-1);

        //(_POW8[_top_space_level-shift_num]-1)/7;
        //�́A���`�����؋�Ԕz��́A������ԃ��x���̍ŏ��̋�Ԃ̗v�f�ԍ�������킷�B
        //���䐔��̘a
        // ��r^k = r^0 + r^1 + r^2 + ... + r^n
        // ��r^k = (1 - r^(n+1)) / (1 - r)
        //
        //���`8���؂̔z��v�f�̋�ԃ��x�����܂ł̍��v��֐��� r=8 ��
        //(1 - 8^(n+1)) / (1-8)  =  (1-8^(n+1)) / -7  =  (8^(n+1) - 1) / 7 �ƂȂ�
        //�����ŁA������Ԃ̍ŏ��̋�ԗv�f�����߂邽�߁A n = ������ԃ��x��-1 �̌v�Z�l�i�e��ԃ��x���܂ł̗v�f���j�́A
        //���̎��̗v�f��������ԃ��x���̐擪�̗v�f�ɂȂ�͂����I�B�Ƃ������ߕ�������B
        //���������čŌ�ɒl�� +1 �������̂��ق����l�ł��邪�A�z���0�Ԃ���n�܂邽�߁A+1 -1 = 0 �ŁA�ȗ����Ă��܂����B
        //��̗�ł����� shift_num = 3 �ŁA�ő��ԕ���Level(_top_space_level) = 5 �ł���̂�
        // 5 - 3 = 2 �ŏ�����ԃ��x���� 2
        // n = 2 - 1 = 1 ��������  (8^(1+1) - 1) / 7 = 9 ��
        //������Ԃ̃��x��2����e�̋�ԃ��x���ł���A��ԃ��x��1�܂ł̔z��v�f�����v��9�Ƃ킩��B
        //���]�̏�����ԃ��x���� 2�̍ŏ��̋�Ԃ͔z��� 9+1 ��10�Ԗڂ���n�܂�B
        //�z���10�ԖڂƂ́A�z��v�f�ԍ���-1����9�ɂȂ�B
        //+1 ���� -1 ����̂Ō��ǁA������ԃ��x��x�̍ŏ��̔z��v�f�ԍ���  (8^x - 1) / 7 �ƂȂ�

#ifdef MY_DEBUG
        if (index > _num_space-1) {
            throwCriticalException(
               "LinearOctree::registerElem() ��ԃI�[�o�[ !. \n"
               "minnum_in_toplevel="<<minnum_in_toplevel<<" maxnum_in_toplevel="<<maxnum_in_toplevel<<"\n"
               "differ_bit_pos="<<differ_bit_pos<<" shift_num="<<shift_num<<" morton_order_space_num="<<morton_order_space_num<<"\n"
               "index="<<index<<" _num_space="<<_num_space
            );
        }
#endif
        //�v�f����`N���؋�Ԃɓo�^(����������)
        NodeSpace* pNodeSpace = &(_paNodeSpaceArray[index]);
        if (pNodeSpace->_pRootNodeElem) {
            pNodeSpace->registerElem(prm_pNodeElem);
        } else {
            pNodeSpace->registerElem(prm_pNodeElem);
            pNodeSpace->_pRegNodeSpaceNext = _pRegNodeSpaceList;
            _pRegNodeSpaceList = pNodeSpace;
        }
    }

    /**
     * �o�^���s������Ԃ̃N���A����
     */
    void clearAllElem() {
        //�o�^�ς݋�ԃ��X�g���g�p���ăN���A
        NodeSpace* pNodeSpace = _pRegNodeSpaceList;
        while (pNodeSpace) {
            pNodeSpace->_pRootNodeElem = nullptr; //�o�^�ς݋�Ԃ̍��{�� nullptr �ŃN���A
            uint32_t index = pNodeSpace->_self_index;
            //_kind_bit_field �̒l�͐e��Ԃɑk���� 0 �Ń��Z�b�g����B
            while (true) {
                if (_paNodeSpaceArray[index]._kind_bit_field == 0) {
                    break;
                }
                _paNodeSpaceArray[index]._kind_bit_field = 0;
                if (index == 0) {
                    break;
                }
                //�e��ԗv�f�ԍ��ŌJ��Ԃ�
                index = (index-1)>>DIM;
            }
            pNodeSpace = pNodeSpace->_pRegNodeSpaceNext;
        }
        //�o�^�ς݃��X�g���N���A
        _pRegNodeSpaceList = nullptr;
    }


    /**
     * �f�o�b�O�p�B�o�^�󋵏o�� .
     */
    void putTree() {
        putTree(0);
    }

    void putTree(uint32_t prm_index, int prm_lv = 0, int prm_pos = 0) {
        int space_no = prm_index;
        if (_paNodeSpaceArray[prm_index]._kind_bit_field != 0) {
            for (int i = 0; i < prm_lv; i++) {
                space_no -= POW_N[i];
                _TRACE_N_("  ");
            }
            UTIL::dec2bin(_paNodeSpaceArray[prm_index]._kind_bit_field, _aChar_strbit);
            _TRACE_N_("LV"<<prm_lv<<"-"<<space_no<<"(POS:"<<prm_pos<<")["<<prm_index<<"]="<<_aChar_strbit<<" /Node->");
            _paNodeSpaceArray[prm_index].dump();
            _TRACE_N_("\n");
        }
        uint32_t lower_level_index = (prm_index<<DIM) + 1;
        if ( lower_level_index >= _num_space) {
            //�v�f���I�[�o�[�A�܂胊�[�t
            return; //�e��Ԃ֖߂�
        } else {
            //������
            for (int i = 0; i < (1<<DIM); i++) {
                putTree(lower_level_index+i, prm_lv+1, i);
            }
            return; //�e��Ԃ֖߂�
        }
    }

    virtual ~LinearTree() {
        GGAF_DELETEARR(_paNodeSpaceArray);
    }
};

//template<int DIM>
//const uint32_t LinearTree<DIM>::_POW8[(MAX_WORLD_HIT_CHECK_OCTREE_LEVEL+1)+1] = {1, 8, 64, 512, 4096, 32768, 262144, 2097152, 16777216, 134217728};
//
//template<int DIM>
//const uint32_t LinearTree<DIM>::_POW4[(MAX_WORLD_HIT_CHECK_QUADTREE_LEVEL+1)+1] =
//    {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216, 67108864, 268435456, 1073741824};
}
#endif /*GGAF_CORE_LINEARTREE_H_*/

