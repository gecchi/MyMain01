#ifndef GGAF_CORE_TREESPACE_H_
#define GGAF_CORE_TREESPACE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafCore {

/**
 * 線形N分木配列用空間クラス .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
template<int DIMENSION>
class TreeSpace : public Object {

public:
    /** [r]線形N分木配列の自身の要素番号 */
    uint32_t _my_index;
    /** [r]この空間＋子孫空間に所属してる要素の種別情報 */
    kind_t _kind_bit_field;
    /** [r]この空間に登録された要素連結リストの根本 */
    TreeElem<DIMENSION>* _pBelongElems;
    /** [r]登録を行った空間連結リスト用、次の空間 */
    TreeSpace<DIMENSION>* _pRegTreeSpaceNext;

public:
    /**
     * コンストラクタ
     * @return
     */
    TreeSpace() : Object() {
        _pBelongElems = nullptr;
        _kind_bit_field = 0;
        _my_index = 0xffffffff; //ありえない0xffffffffを入れておく
        _pRegTreeSpaceNext = nullptr;
    }

    /**
     * 要素登録 .
     * @param prm_pElem 要素
     * @return true:そのインデックスに初回登録 ／ false:それ以外
     */
    void registerElem(TreeElem<DIMENSION>* const prm_pElem) {
        //引数の要素番号
        uint32_t index = _my_index;
        const kind_t this_kind = prm_pElem->_kind;
        TreeSpace<DIMENSION>* p = this; //= & _paTreeSpaceArray[index]
        while (true) {
            if (p->_kind_bit_field & this_kind) {
                //もう種別情報が設定済みならば、それ以上の親も設定済みの為、抜ける
                break;
            } else {
                //空間に種別情報が未設定ならば設定
                p->_kind_bit_field |= this_kind;
            }
            if (index == 0) {
                break;
            }
            //一つ上の親空間要素番号で繰り返す
            index = (index-1)>>DIMENSION;
            p = p - (p->_my_index - index);
        }
        prm_pElem->_pSpace_current = this;
        prm_pElem->_pBelongNext = _pBelongElems; //初回は _pBelongElems == nullptr
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

