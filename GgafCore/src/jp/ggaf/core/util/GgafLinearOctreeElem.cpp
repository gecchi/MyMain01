#include "stdafx.h"
using namespace GgafCore;


GgafLinearOctreeElem::GgafLinearOctreeElem(GgafObject* prm_pObject, UINT32 prm_kindbit) {
    _pSpace_current = NULL;
    _pNext = NULL;
    _pPrev = NULL;
    _pObject = prm_pObject;
    _kindbit = prm_kindbit;
    _pLinearOctree = NULL;
    _pRegLinkNext = NULL;
}

void GgafLinearOctreeElem::clear() {
    if(_pSpace_current == NULL) {
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
            paSpace[index]._pElem_first = NULL;
            paSpace[index]._pElem_last = NULL;
        }

        if (index == 0) {
            break;
        }
        // 親空間要素番号で繰り返す
        index = (index-1)>>3;
    }
    _pNext = NULL;
    _pPrev = NULL;
    _pSpace_current = NULL;

//要素は各空間にリストにぶら下がっているため、clear() の機能を本当に綺麗に実装するならば、
//所属空間の _kindinfobit も XOR などしてビットをアンセットし、
//_pElem_first、_pElem_last のポインタの鎖（リスト）から一つだけ切り離す処理をするべきである。
//しかし、どうせ clear() を使用するのは、全空間全要素クリアするときだけであるので、
//_kindinfobit は、何も考えず 0 を設定。鎖の _pElem_first も _pElem_last もいきなりNULLでクリア。
//１つだけ clear() とかすると、空間情報は崩れることを注意、アプリケーションロジックから clear() は使用しないこと。
//基本ツリーは、登録と、クリアのみ行うという設計
}

void GgafLinearOctreeElem::belongTo(GgafLinearOctreeSpace* prm_pSpace_target) {
    if (_pSpace_current == prm_pSpace_target) {
        //_TRACE_("belongToせんでいい");
        return;
    } else {
        if (prm_pSpace_target->_pElem_first == NULL) {
            //１番目に追加の場合
            prm_pSpace_target->_pElem_first = this;
            prm_pSpace_target->_pElem_last = this;
            _pNext = NULL;
            _pPrev = NULL;
            _pSpace_current = prm_pSpace_target;
        } else {
            //末尾に追加の場合
            prm_pSpace_target->_pElem_last->_pNext = this;
            _pPrev = prm_pSpace_target->_pElem_last;
            _pNext = NULL;
            prm_pSpace_target->_pElem_last = this;
            _pSpace_current = prm_pSpace_target;
        }
    }
    //引数の要素番号
    UINT32 index = prm_pSpace_target->_my_index;
    GgafLinearOctreeSpace* paSpace = _pLinearOctree->_paSpace;
    //親空間すべてに要素種別情報を流す
    while(true) {
        paSpace[index]._kindinfobit |= this->_kindbit;
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
