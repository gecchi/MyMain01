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
template<int DIMENSION>
class TreeSpace : public Object {

public:
    /** [r]���`N���ؔz��̎��g�̗v�f�ԍ� */
    uint32_t _my_index;
    /** [r]���̋�ԁ{�q����Ԃɏ������Ă�v�f�̎�ʏ�� */
    kind_t _kind_bit_field;
    /** [r]���̋�Ԃɓo�^���ꂽ�v�f�A�����X�g�̍��{ */
    TreeElem<DIMENSION>* _pBelongElems;
    /** [r]�o�^���s������ԘA�����X�g�p�A���̋�� */
    TreeSpace<DIMENSION>* _pRegTreeSpaceNext;

public:
    /**
     * �R���X�g���N�^
     * @return
     */
    TreeSpace() : Object() {
        _pBelongElems = nullptr;
        _kind_bit_field = 0;
        _my_index = 0xffffffff; //���肦�Ȃ�0xffffffff�����Ă���
        _pRegTreeSpaceNext = nullptr;
    }

    /**
     * �v�f�o�^ .
     * @param prm_pElem �v�f
     * @return true:���̃C���f�b�N�X�ɏ���o�^ �^ false:����ȊO
     */
    void registerElem(TreeElem<DIMENSION>* const prm_pElem) {
        //�����̗v�f�ԍ�
        uint32_t index = _my_index;
        const kind_t this_kind = prm_pElem->_kind;
        TreeSpace<DIMENSION>* p = this; //= & _paTreeSpaceArray[index]
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
            index = (index-1)>>DIMENSION;
            p = p - (p->_my_index - index);
        }
        prm_pElem->_pSpace_current = this;
        prm_pElem->_pBelongNext = _pBelongElems; //����� _pBelongElems == nullptr
        _pBelongElems = prm_pElem;
    }

    void dump() {
        if (_pBelongElems == nullptr) {
            _TRACE_N_("x");
        } else {
            TreeElem<DIMENSION>* pElem = _pBelongElems;
            while (pElem) {
                pElem->dump();
                pElem = pElem ->_pBelongNext;
            }
        }
    }

    virtual ~TreeSpace() {
    }
};

}
#endif /*GGAF_CORE_TREESPACE_H_*/

