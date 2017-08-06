#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"

#include "jp/ggaf/core/util/GgafLinearOctreeOctant.h"
#include "jp/ggaf/core/util/GgafLinearOctree.h"

using namespace GgafCore;

GgafLinearOctreeElem::GgafLinearOctreeElem(GgafLinearOctreeOctant* prm_paLinearOctant, GgafObject* prm_pObject, uint32_t prm_kindbit) : GgafObject() ,
        _paLinearOctant(prm_paLinearOctant),
    _pObject(prm_pObject)
{
    _kindbit = prm_kindbit;
    _pOctant_current = nullptr;
    _pNext = nullptr;
    _pPrev = nullptr;
    _pRegLinkNext = nullptr;
}

void GgafLinearOctreeElem::clear() {
    if(_pOctant_current == nullptr) {
        //_TRACE_(FUNC_NAME<<" できません。意図してますか？");
        return;
    }
    //情報リセット
    uint32_t index = _pOctant_current->_my_index;
//    GgafLinearOctreeOctant* paOctant = _pLinearOctree->_paLinearOctant;
    while (true) {
        if (_paLinearOctant[index]._kindinfobit == 0 ) {
            break;
        } else {
            _paLinearOctant[index]._kindinfobit = 0;
            _paLinearOctant[index]._pElem_first = nullptr;
            _paLinearOctant[index]._pElem_last = nullptr;
        }

        if (index == 0) {
            break;
        }
        // 親空間要素番号で繰り返す
        index = (index-1)>>3;
    }
    _pNext = nullptr;
    _pPrev = nullptr;
    _pOctant_current = nullptr;

//要素は各空間にリストにぶら下がっているため、clear() の機能を本当に綺麗に実装するならば、
//所属空間の _kindinfobit も XOR などしてビットをアンセットし、
//_pElem_first、_pElem_last のポインタの鎖（リスト）から一つだけ切り離す処理をするべきである。
//しかし、どうせ clear() を使用するのは、全空間全要素クリアするときだけであるので、
//_kindinfobit は、何も考えず 0 を設定。鎖の _pElem_first も _pElem_last もいきなりnullptrでクリア。
//１つだけ clear() とかすると、空間情報は崩れることを注意、アプリケーションロジックから clear() は使用しないこと。
//基本ツリーは、登録と、クリアのみ行うという設計
}

void GgafLinearOctreeElem::belongTo(GgafLinearOctreeOctant* const prm_pOctant_target) {
    if (_pOctant_current == prm_pOctant_target) {
        //_TRACE_("belongToせんでいい");
        return;
    } else {
        if (prm_pOctant_target->_pElem_first == nullptr) {
            //１番目に追加の場合
            prm_pOctant_target->_pElem_first = this;
            prm_pOctant_target->_pElem_last = this;
//nullptrはclear時設定済み。省略しても大丈夫なはず。
//            _pNext = nullptr;
//            _pPrev = nullptr;
            _pOctant_current = prm_pOctant_target;
        } else {
            //末尾に追加の場合
            prm_pOctant_target->_pElem_last->_pNext = this;
            _pPrev = prm_pOctant_target->_pElem_last;
//nullptrはclear時設定済み。省略しても大丈夫なはず。
//            _pNext = nullptr;
            prm_pOctant_target->_pElem_last = this;
            _pOctant_current = prm_pOctant_target;
        }
    }
    //引数の要素番号
    uint32_t index = prm_pOctant_target->_my_index;
//    GgafLinearOctreeOctant* const paOctant = _pLinearOctree->_paLinearOctant;
    const uint32_t this_kindbit = this->_kindbit;
    //親空間すべてに要素種別情報を流す
    while (true) {
        if (_paLinearOctant[index]._kindinfobit & this_kindbit) {
            //もう種別情報が設定済みならば、それ以上の親も設定済みの為、抜ける
            break;
        } else {
            //空間に種別情報が未設定ならば設定
            _paLinearOctant[index]._kindinfobit |= this_kindbit;
        }
        if (index == 0) {
            break;
        }
        //一つ上の親空間要素番号で繰り返す
        index = (index-1)>>3;
    }
}

void GgafLinearOctreeElem::dump() {
    _TRACE_N_("o");
}

GgafLinearOctreeElem::~GgafLinearOctreeElem() {
}
