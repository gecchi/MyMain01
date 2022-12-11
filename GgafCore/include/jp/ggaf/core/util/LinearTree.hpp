#ifndef GGAF_CORE_LINEARTREE_H_
#define GGAF_CORE_LINEARTREE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/util/TreeNode.hpp"
#include "jp/ggaf/core/util/TreeElem.hpp"
#include "jp/ggaf/core/util/Util.h"
#include <math.h>

namespace GgafCore {

/**
 * ���`N���؋��� .
 * ���`4���؂Ɛ��`8���؂̋��ʏ������܂Ƃ߂��N���X
 * @tparam DIM �����B2�̏ꍇ4���؁A3�̏ꍇ8���؂̋@�\�ƂȂ�B
 * @version 1.00
 * @since 2022/12/11
 * @author Masatoshi Tsuge
 */
template<int DIM>
class LinearTree : public Object {

public:
    /** [r]N���؂�N	 */
    const uint32_t _N;
    /** [r]N���؂̋�Ԃ��꒼���ɕ��ׂ����`�z�� */
    TreeNode<DIM>* _paTreeNodeArray; //_paTreeNodeArray[0] �� ROOT��Ԃւ̃|�C���^
    /** [r]�o�^���s������ԘA�����X�g�̍��{�B_pRegTreeNodeNext �ŘA������Ă���B�iclearAllElem() �Ŏg�p����j */
    TreeNode<DIM>* _pRegTreeNodeList;
    /** [r]�ő��ԃ��x�� */
    const uint32_t _top_space_level; //���[�g��Ԃ�Level=0
    /** [r]�S��Ԑ� */
    uint32_t _num_space;
    char _aChar_strbit[33];
    /** [r]N�iN���؂�N�j�̗ݏ�̔z��B�v�Z�p�B(20�͏\���ő僌�x����ԂƎv����K���Ȓl) */
    uint32_t POW_N[20];

    /**
     * �R���X�g���N�^ .
     * @param prm_level �\�z�����ԃ��x��
     * @param prm_max_tree_level �z��ł���ő��ԃ��x��
     */
    LinearTree(uint32_t prm_level) : Object(),
    _N((uint32_t)pow(2.0, DIM)),
    _top_space_level(prm_level) {
        //�v�Z�p�ݏ�̔z��
        for (int lv = 0; lv < 20; lv++) {
            POW_N[lv] = (uint32_t)(pow((double)_N , lv));
        }
        //�S��Ԑ������߂�
        _num_space = ((uint32_t)((POW_N[_top_space_level+1] -1) / (_N-1)));
        //���`N���ؔz��쐬
        _paTreeNodeArray = NEW TreeNode<DIM>[_num_space];
        for (uint32_t i = 0; i < _num_space; i++) {
            _paTreeNodeArray[i]._self_index = i;
        }
        _pRegTreeNodeList = nullptr;
    }

    /**
     * �o�^���s������Ԃ̃N���A����
     */
    void clearAllElem() {
        //�o�^�ς݋�ԃ��X�g���g�p���ăN���A
        TreeNode<DIM>* pTreeNode = _pRegTreeNodeList;
        while (pTreeNode) {
            pTreeNode->_pBelongElemList = nullptr; //�o�^�ς݋�Ԃ̍��{�� nullptr �ŃN���A
            uint32_t index = pTreeNode->_self_index;
            //_kind_bit_field �̒l�͐e��Ԃɑk���� 0 �Ń��Z�b�g����B
            while (true) {
                if (_paTreeNodeArray[index]._kind_bit_field == 0) {
                    break;
                }
                _paTreeNodeArray[index]._kind_bit_field = 0;
                if (index == 0) {
                    break;
                }
                //�e��ԗv�f�ԍ��ŌJ��Ԃ�
                index = (index-1)>>DIM;
            }
            pTreeNode = pTreeNode->_pRegTreeNodeNext;
        }
        //�o�^�ς݃��X�g���N���A
        _pRegTreeNodeList = nullptr;
    }

    /**
     *
     * @param prm_pElem
     * @param minnum_in_toplevel BOX�̍�����O��XYZ���W�_�����������Ԃ́A�ő僌�x���̋�ԁi��������Ȃ��ł��[����ԁj�Ń��[�g�������ʂ���Ԕԍ��͉��Ԃ�
     * @param maxnum_in_toplevel BOX�̉E�㉜��XYZ���W�_�����������Ԃ́A�ő僌�x���̋�ԁi��������Ȃ��ł��[����ԁj�Ń��[�g�������ʂ���Ԕԍ��͉��Ԃ�
     */
    void registerElem(TreeElem<DIM>* const prm_pElem, const uint32_t minnum_in_toplevel, const uint32_t maxnum_in_toplevel) {
        //�ǂ̃��x���̋�Ԃɏ������Ă���̂��擾
        const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
        uint32_t shift_num = 0;
        for (uint32_t i = 0; i < _top_space_level; i++) {
            if (((differ_bit_pos>>(i*DIM)) & (_N-1)) != 0 ) {
                shift_num = i+1;
            }
        }
        //���̂Q�s�̈Ӗ��́ALinearOctree.cpp�ALinearQuadtree.cpp �̃R�����g�u�ȉ��͋��ʉ��O�̃R�[�h�v�ȍ~���Q��
        const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*DIM);
        const uint32_t index = morton_order_space_num + (POW_N[_top_space_level-shift_num]-1)/(_N-1);

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
        TreeNode<DIM>* pTreeNode = &(_paTreeNodeArray[index]);
        if (pTreeNode->_pBelongElemList) {
            pTreeNode->registerElem(prm_pElem);
        } else {
            pTreeNode->registerElem(prm_pElem);
            pTreeNode->_pRegTreeNodeNext = _pRegTreeNodeList;
            _pRegTreeNodeList = pTreeNode;
        }
    }
    /**
     * �f�o�b�O�p�B�o�^�󋵏o�� .
     */
    void putTree() {
        putTree(0);
    }

    void putTree(uint32_t prm_index, int prm_lv = 0, int prm_pos = 0) {
        int space_no = prm_index;
        if (_paTreeNodeArray[prm_index]._kind_bit_field != 0) {
            for (int i = 0; i < prm_lv; i++) {
                space_no -= POW_N[i];
                _TRACE_N_("  ");
            }
            UTIL::strbin(_paTreeNodeArray[prm_index]._kind_bit_field, _aChar_strbit);
            _TRACE_N_("LV"<<prm_lv<<"-"<<space_no<<"(POS:"<<prm_pos<<")["<<prm_index<<"]="<<_aChar_strbit<<" /TreeElem->");
            _paTreeNodeArray[prm_index].dump();
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
        GGAF_DELETEARR(_paTreeNodeArray);
    }
};

//template<int DIM>
//const uint32_t LinearTree<DIM>::_POW8[(MAX_OCTREE_LEVEL+1)+1] = {1, 8, 64, 512, 4096, 32768, 262144, 2097152, 16777216, 134217728};
//
//template<int DIM>
//const uint32_t LinearTree<DIM>::_POW4[(MAX_QUADTREE_LEVEL+1)+1] =
//    {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216, 67108864, 268435456, 1073741824};
}
#endif /*GGAF_CORE_LINEARTREE_H_*/

