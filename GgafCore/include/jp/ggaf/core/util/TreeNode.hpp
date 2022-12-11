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
template<int DIM>
class TreeNode : public Object {

public:
    /** [r]線形N分木配列の自身の要素番号 */
    uint32_t _self_index;
    /** [r]この空間＋子孫空間に所属してる要素の種別情報 */
    kind_t _kind_bit_field;
    /** [r]この空間に登録された要素連結リストの根本。_pBelongNext で連結されている。 */
    TreeElem<DIM>* _pBelongElemList;
    /** [r]登録を行った空間連結リスト用、次の空間 */
    TreeNode<DIM>* _pRegTreeNodeNext;

public:
    /**
     * コンストラクタ
     * @return
     */
    TreeNode() : Object() {
        _pBelongElemList = nullptr;
        _kind_bit_field = 0;
        _self_index = 0xffffffff; //ありえない0xffffffffを入れておく
        _pRegTreeNodeNext = nullptr;
    }

    /**
     * 要素登録 .
     * @param prm_pElem 要素
     * @return true:そのインデックスに初回登録 ／ false:それ以外
     */
    void registerElem(TreeElem<DIM>* const prm_pElem) {
        //引数の要素番号
        uint32_t index = _self_index;
        const kind_t this_kind = prm_pElem->_kind;
        TreeNode<DIM>* p = this; //= & _paTreeNodeArray[index]
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
            index = (index-1)>>DIM;
            p = p - (p->_self_index - index);
        }
        prm_pElem->_pSpace_current = this;
        prm_pElem->_pBelongNext = _pBelongElemList; //初回は _pBelongElemList == nullptr
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

