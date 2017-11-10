#ifndef GGAFCORE_GGAFTREESPACE_H_
#define GGAFCORE_GGAFTREESPACE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"


namespace GgafCore {

/**
 * ���`N���ؔz��p��ԃN���X .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
template<uint32_t DIMENSION>
class GgafTreeSpace : public GgafObject {

public:
    /** [r]���`N���ؔz��̎��g�̗v�f�ԍ� */
    uint32_t _my_index;
    /** [r]�������Ă�v�f�̎�ʏ�� */
    kind_t _kind_bit_field;
    /** [r]�Ԃ牺����v�f�̐擪 */
    GgafTreeElem<DIMENSION>* _pElem_first;
    /** [r]�Ԃ牺����v�f�̖��� */
    GgafTreeElem<DIMENSION>* _pElem_last;

public:
    /**
     * �R���X�g���N�^
     * @return
     */
    GgafTreeSpace() : GgafObject() {
        _pElem_first = nullptr;
        _pElem_last = nullptr;
        _kind_bit_field = 0;
        _my_index = 0xffffffff; //���肦�Ȃ�0xffffffff�����Ă���
    }

    void registerElem(GgafTreeElem<DIMENSION>* const prm_pElem) {
        if (prm_pElem->_pSpace_current == this) {
            //_TRACE_("belongTo����ł���");
            return;
        } else {
            if (_pElem_first == nullptr) {
                //�P�Ԗڂɒǉ��̏ꍇ
                _pElem_first = prm_pElem;
                _pElem_last = prm_pElem;
                //nullptr��clear���ݒ�ς݁B�ȗ����Ă����v�Ȃ͂��B
                //            _pNext = nullptr;
                //            _pPrev = nullptr;
                prm_pElem->_pSpace_current = this;
            } else {
                //�����ɒǉ��̏ꍇ
                _pElem_last->_pNext = prm_pElem;
                prm_pElem->_pPrev = _pElem_last;
                //nullptr��clear���ݒ�ς݁B�ȗ����Ă����v�Ȃ͂��B
                //            _pNext = nullptr;
                _pElem_last = prm_pElem;
                prm_pElem->_pSpace_current = this;
            }
        }
        //�����̗v�f�ԍ�
        uint32_t index = _my_index;
        const kind_t this_kind = prm_pElem->_kind;
        GgafTreeSpace<DIMENSION>* p = this; //= & _paOctant[index]
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
    }

    void dump() {
        if (_pElem_first == nullptr) {
            _TRACE_N_("x");
        } else {
            GgafTreeElem<DIMENSION>* pElem = _pElem_first;
            while (true) {
                pElem->dump();
                if (pElem == _pElem_last) {
                    break;
                }
                pElem = pElem -> _pNext;
            }
        }
    }

    virtual ~GgafTreeSpace() {
    }
};

}
#endif /*GGAFCORE_GGAFTREESPACE_H_*/
