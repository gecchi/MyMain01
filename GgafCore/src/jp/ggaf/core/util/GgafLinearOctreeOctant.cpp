#include "jp/ggaf/core/util/GgafTreeSpace.hpp"


using namespace GgafCore;

//void GgafTreeSpace::dump() {
//    if (_pElem_first == nullptr) {
//        _TRACE_N_("x");
//    } else {
//        GgafTreeElem* pElem = _pElem_first;
//        while (true) {
//            pElem->dump();
//            if (pElem == _pElem_last) {
//                break;
//            }
//            pElem = pElem -> _pNext;
//        }
//    }
//}
//void GgafTreeSpace::registerElem(GgafTreeElem* const prm_pElem) {
//    if (prm_pElem->_pSpace_current == this) {
//        //_TRACE_("belongTo����ł���");
//        return;
//    } else {
//        if (_pElem_first == nullptr) {
//            //�P�Ԗڂɒǉ��̏ꍇ
//            _pElem_first = prm_pElem;
//            _pElem_last = prm_pElem;
//            //nullptr��clear���ݒ�ς݁B�ȗ����Ă����v�Ȃ͂��B
//            //            _pNext = nullptr;
//            //            _pPrev = nullptr;
//            prm_pElem->_pSpace_current = this;
//        } else {
//            //�����ɒǉ��̏ꍇ
//            _pElem_last->_pNext = prm_pElem;
//            prm_pElem->_pPrev = _pElem_last;
//            //nullptr��clear���ݒ�ς݁B�ȗ����Ă����v�Ȃ͂��B
//            //            _pNext = nullptr;
//            _pElem_last = prm_pElem;
//            prm_pElem->_pSpace_current = this;
//        }
//    }
//    //�����̗v�f�ԍ�
//    uint32_t index = _my_index;
//    const uint32_t this_kindbit = prm_pElem->_kindbit;
//    GgafTreeSpace* p = this; //= & _paOctant[index]
//    while (true) {
//        if (p->_kind_bit_field & this_kindbit) {
//            //������ʏ�񂪐ݒ�ς݂Ȃ�΁A����ȏ�̐e���ݒ�ςׁ݂̈A������
//            break;
//        } else {
//            //��ԂɎ�ʏ�񂪖��ݒ�Ȃ�ΐݒ�
//            p->_kind_bit_field |= this_kindbit;
//        }
//        if (index == 0) {
//            break;
//        }
//        //���̐e��ԗv�f�ԍ��ŌJ��Ԃ�
//        index = (index-1)>>3;
//        p = p - (p->_my_index - index);
//    }
//}
//
//
//GgafTreeSpace::~GgafTreeSpace() {
//}
