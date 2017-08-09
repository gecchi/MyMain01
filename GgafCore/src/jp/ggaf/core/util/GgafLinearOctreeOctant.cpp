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
//        //_TRACE_("belongToせんでいい");
//        return;
//    } else {
//        if (_pElem_first == nullptr) {
//            //１番目に追加の場合
//            _pElem_first = prm_pElem;
//            _pElem_last = prm_pElem;
//            //nullptrはclear時設定済み。省略しても大丈夫なはず。
//            //            _pNext = nullptr;
//            //            _pPrev = nullptr;
//            prm_pElem->_pSpace_current = this;
//        } else {
//            //末尾に追加の場合
//            _pElem_last->_pNext = prm_pElem;
//            prm_pElem->_pPrev = _pElem_last;
//            //nullptrはclear時設定済み。省略しても大丈夫なはず。
//            //            _pNext = nullptr;
//            _pElem_last = prm_pElem;
//            prm_pElem->_pSpace_current = this;
//        }
//    }
//    //引数の要素番号
//    uint32_t index = _my_index;
//    const uint32_t this_kindbit = prm_pElem->_kindbit;
//    GgafTreeSpace* p = this; //= & _paOctant[index]
//    while (true) {
//        if (p->_kind_bit_field & this_kindbit) {
//            //もう種別情報が設定済みならば、それ以上の親も設定済みの為、抜ける
//            break;
//        } else {
//            //空間に種別情報が未設定ならば設定
//            p->_kind_bit_field |= this_kindbit;
//        }
//        if (index == 0) {
//            break;
//        }
//        //一つ上の親空間要素番号で繰り返す
//        index = (index-1)>>3;
//        p = p - (p->_my_index - index);
//    }
//}
//
//
//GgafTreeSpace::~GgafTreeSpace() {
//}
