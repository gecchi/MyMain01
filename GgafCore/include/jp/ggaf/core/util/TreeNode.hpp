#ifndef GGAF_CORE_TREESPACE_H_
#define GGAF_CORE_TREESPACE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafCore {

/**
 * ���`N���ؔz��p��ԃN���X .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
template<int DIM>
class TreeNode : public Object {

public:
    /** [r]���`N���ؔz��̎��g�̗v�f�ԍ� */
    uint32_t _self_index;
    /** [r]���̋�ԁ{�q����Ԃɏ������Ă�v�f�̎�ʏ�� */
    kind_t _kind_bit_field;
    /** [r]���̋�Ԃɓo�^���ꂽ�v�f�A�����X�g�̍��{�B_pBelongNext �ŘA������Ă���B */
    TreeElem<DIM>* _pBelongElemList;
    /** [r]�o�^���s������ԘA�����X�g�p�A���̋�� */
    TreeNode<DIM>* _pRegTreeNodeNext;

public:
    /**
     * �R���X�g���N�^
     * @return
     */
    TreeNode() : Object() {
        _pBelongElemList = nullptr;
        _kind_bit_field = 0;
        _self_index = 0xffffffff; //���肦�Ȃ�0xffffffff�����Ă���
        _pRegTreeNodeNext = nullptr;
    }

    /**
     * �v�f�o�^ .
     * @param prm_pElem �v�f
     * @return true:���̃C���f�b�N�X�ɏ���o�^ �^ false:����ȊO
     */
    void registerElem(TreeElem<DIM>* const prm_pElem) {
        //�����̗v�f�ԍ�
        uint32_t index = _self_index;
        const kind_t this_kind = prm_pElem->_kind;
        TreeNode<DIM>* p = this; //= & _paTreeNodeArray[index]
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
        prm_pElem->_pSpace_current = this;
        prm_pElem->_pBelongNext = _pBelongElemList; //����� _pBelongElemList == nullptr
        _pBelongElemList = prm_pElem;
    }

    void dump() {
        if (_pBelongElemList == nullptr) {
            _TRACE_N_("x");
        } else {
            TreeElem<DIM>* pElem = _pBelongElemList;
            while (pElem) {
                pElem->dump();
                pElem = pElem ->_pBelongNext;
            }
        }
    }

    virtual ~TreeNode() {
    }
};

}
#endif /*GGAF_CORE_TREESPACE_H_*/

