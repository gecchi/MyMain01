#ifndef GGAF_CORE_LINEARTREE_H_
#define GGAF_CORE_LINEARTREE_H_
#include "GgafCommonHeader.h"
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
        /** [r]���̋�Ԃɓo�^���ꂽ�v�f�A�����X�g�̍��{�B_pNextValue �ŘA������Ă���B */
        ITreeNodeElem* _pNodeValueList;
        /** [r]�o�^���s������ԘA�����X�g�p�A���̋��(�J�����Ɏg�p) */
        NodeSpace* _pRegNodeSpaceNext;

    public:
        /**
         * �R���X�g���N�^
         * @return
         */
        NodeSpace() : Object() {
            _pNodeValueList = nullptr;
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
            prm_pNodeElem->_pNextValue = _pNodeValueList; //����� _pNodeValueList == nullptr
            _pNodeValueList = prm_pNodeElem;
        }

        void dump() {
            if (_pNodeValueList == nullptr) {
                _TRACE_N_(""); //�m�[�h�Ȃ�
            } else {
                ITreeNodeElem* pElem = _pNodeValueList;
                while (pElem) {
                    pElem->dump();
                    pElem = pElem ->_pNextValue;
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
        //���̂Q�s�̈Ӗ��́ALinearOctree.cpp�ALinearQuadtree.cpp �̃R�����g�u�ȉ��͋��ʉ��O�̃R�[�h�v�ȍ~���Q��
        const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*DIM);
        const uint32_t index = morton_order_space_num + (POW_N[_top_space_level-shift_num]-1)/(N-1);

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
        if (pNodeSpace->_pNodeValueList) {
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
            pNodeSpace->_pNodeValueList = nullptr; //�o�^�ς݋�Ԃ̍��{�� nullptr �ŃN���A
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
            UTIL::strbin(_paNodeSpaceArray[prm_index]._kind_bit_field, _aChar_strbit);
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

