#ifndef GGAFCORE_GGAFTREESPACE_H_
#define GGAFCORE_GGAFTREESPACE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"


namespace GgafCore {

/**
 * 線形N分木配列用空間クラス .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
template<int BIT_SHIFT_NUM>
class GgafTreeSpace : public GgafObject {

public:
    /** [r]線形N分木配列の自身の要素番号 */
    uint32_t _my_index;
    /** [r]所属してる要素の種別情報 */
    actorkind _kind_bit_field;
    /** [r]ぶら下がる要素の先頭 */
    GgafTreeElem<BIT_SHIFT_NUM>* _pElem_first;
    /** [r]ぶら下がる要素の末尾 */
    GgafTreeElem<BIT_SHIFT_NUM>* _pElem_last;

public:
    /**
     * コンストラクタ
     * @return
     */
    GgafTreeSpace() : GgafObject() {
        _pElem_first = nullptr;
        _pElem_last = nullptr;
        _kind_bit_field = 0;
        _my_index = 0xffffffff; //ありえない0xffffffffを入れておく
    }

    void registerElem(GgafTreeElem<BIT_SHIFT_NUM>* const prm_pElem) {
        if (prm_pElem->_pSpace_current == this) {
            //_TRACE_("belongToせんでいい");
            return;
        } else {
            if (_pElem_first == nullptr) {
                //１番目に追加の場合
                _pElem_first = prm_pElem;
                _pElem_last = prm_pElem;
                //nullptrはclear時設定済み。省略しても大丈夫なはず。
                //            _pNext = nullptr;
                //            _pPrev = nullptr;
                prm_pElem->_pSpace_current = this;
            } else {
                //末尾に追加の場合
                _pElem_last->_pNext = prm_pElem;
                prm_pElem->_pPrev = _pElem_last;
                //nullptrはclear時設定済み。省略しても大丈夫なはず。
                //            _pNext = nullptr;
                _pElem_last = prm_pElem;
                prm_pElem->_pSpace_current = this;
            }
        }
        //引数の要素番号
        uint32_t index = _my_index;
        const uint32_t this_kindbit = prm_pElem->_kindbit;
        GgafTreeSpace<BIT_SHIFT_NUM>* p = this; //= & _paOctant[index]
        while (true) {
            if (p->_kind_bit_field & this_kindbit) {
                //もう種別情報が設定済みならば、それ以上の親も設定済みの為、抜ける
                break;
            } else {
                //空間に種別情報が未設定ならば設定
                p->_kind_bit_field |= this_kindbit;
            }
            if (index == 0) {
                break;
            }
            //一つ上の親空間要素番号で繰り返す
            index = (index-1)>>BIT_SHIFT_NUM;
            p = p - (p->_my_index - index);
        }
    }
    void dump() {
        if (_pElem_first == nullptr) {
            _TRACE_N_("x");
        } else {
            GgafTreeElem<BIT_SHIFT_NUM>* pElem = _pElem_first;
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

