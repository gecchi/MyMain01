#include "stdafx.h"
using namespace GgafCore;


GgafLinearOctreeElem::GgafLinearOctreeElem(GgafObject* prm_pObject, UINT32 prm_kindbit) {
    _pSpace_current = nullptr;
    _pNext = nullptr;
    _pPrev = nullptr;
    _pObject = prm_pObject;
    _kindbit = prm_kindbit;
    _pLinearOctree = nullptr;
    _pRegLinkNext = nullptr;
}

void GgafLinearOctreeElem::clear() {
    if(_pSpace_current == nullptr) {
        //_TRACE_("GgafLinearOctreeElem::extract() できません。意図してますか？");
        return;
    }
    //情報リセット
    UINT32 index = _pSpace_current->_my_index;
    GgafLinearOctreeSpace* paSpace = _pLinearOctree->_paSpace;
    while(true) {
        if (paSpace[index]._kindinfobit == 0 ) {
            break;
        } else {
            paSpace[index]._kindinfobit = 0;
            paSpace[index]._pElem_first = nullptr;
            paSpace[index]._pElem_last = nullptr;
        }

        if (index == 0) {
            break;
        }
        // 親空間要素番号で繰り返す
        index = (index-1)>>3;
    }
    _pNext = nullptr;
    _pPrev = nullptr;
    _pSpace_current = nullptr;

//要素は各空間にリストにぶら下がっているため、clear() の機能を本当に綺麗に実装するならば、
//所属空間の _kindinfobit も XOR などしてビットをアンセットし、
//_pElem_first、_pElem_last のポインタの鎖（リスト）から一つだけ切り離す処理をするべきである。
//しかし、どうせ clear() を使用するのは、全空間全要素クリアするときだけであるので、
//_kindinfobit は、何も考えず 0 を設定。鎖の _pElem_first も _pElem_last もいきなりnullptrでクリア。
//１つだけ clear() とかすると、空間情報は崩れることを注意、アプリケーションロジックから clear() は使用しないこと。
//基本ツリーは、登録と、クリアのみ行うという設計
}

void GgafLinearOctreeElem::belongTo(GgafLinearOctreeSpace* prm_pSpace_target) {
    if (_pSpace_current == prm_pSpace_target) {
        //_TRACE_("belongToせんでいい");
        return;
    } else {
        if (prm_pSpace_target->_pElem_first == nullptr) {
            //１番目に追加の場合
            prm_pSpace_target->_pElem_first = this;
            prm_pSpace_target->_pElem_last = this;
//nullptrはclear時設定済み。省略しても大丈夫なはず。
//            _pNext = nullptr;
//            _pPrev = nullptr;
            _pSpace_current = prm_pSpace_target;
        } else {
            //末尾に追加の場合
            prm_pSpace_target->_pElem_last->_pNext = this;
            _pPrev = prm_pSpace_target->_pElem_last;
//nullptrはclear時設定済み。省略しても大丈夫なはず。
//            _pNext = nullptr;
            prm_pSpace_target->_pElem_last = this;
            _pSpace_current = prm_pSpace_target;
        }
    }
    //引数の要素番号
    UINT32 index = prm_pSpace_target->_my_index;
    GgafLinearOctreeSpace* paSpace = _pLinearOctree->_paSpace;
    UINT32 this_kindbit = this->_kindbit;
    //親空間すべてに要素種別情報を流す
    while(true) {
        if (paSpace[index]._kindinfobit & this_kindbit) {
            //もう種別情報が設定済みならば、それ以上の親も設定済みの為、抜ける
            break;
        } else {
            //空間に種別情報が未設定ならば設定
            paSpace[index]._kindinfobit |= this_kindbit;
        }
        if (index == 0) {
            break;
        }
        //一つ上の親空間要素番号で繰り返す
        index = (index-1)>>3;
    }
}

void GgafLinearOctreeElem::dump() {
    _TEXT_("o");
}

GgafLinearOctreeElem::~GgafLinearOctreeElem() {
}
