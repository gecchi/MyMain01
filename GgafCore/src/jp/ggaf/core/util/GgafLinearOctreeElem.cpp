#include "stdafx.h"
using namespace std;
using namespace GgafCore;


GgafLinearOctreeElem::GgafLinearOctreeElem(GgafObject* prm_pObject, UINT32 prm_kindbit) {
    _pSpace_Current = NULL;
    _pNext = NULL;
    _pPrev = NULL;
    _pObject = prm_pObject;
    _kindbit = prm_kindbit;
    _pLinearOctree = NULL;
    _pRegLinkNext = NULL;
}

void GgafLinearOctreeElem::extract() {
    if(_pSpace_Current == NULL) {
        //_TRACE_("GgafLinearOctreeElem::extract() できません。意図してますか？");
        return;
    }
    //情報リセット
    UINT32 index = _pSpace_Current->_my_index;
    while(true) {
        //一つでもextract()すると情報は崩れることを注意、アプリケーションロジックからextract() は使用しないこと。
        //基本ツリーは、登録と、クリアのみ行うという設計
        if (_pLinearOctree->_paSpace[index]._kindinfobit == 0 ) {
            break;
        } else {
            _pLinearOctree->_paSpace[index]._kindinfobit = 0;
            _pLinearOctree->_paSpace[index]._pElemFirst = NULL;
            _pLinearOctree->_paSpace[index]._pElemLast = NULL;
        }

        if (index == 0) {
            break;
        }
        // 親空間要素番号で繰り返す
        index = (index-1)>>3;
    }
    _pNext = NULL;
    _pPrev = NULL;
    _pSpace_Current = NULL;

//    if (this == _pSpace_Current->_pElemFirst && this == _pSpace_Current->_pElemLast) {
//        //先頭かつ末尾の場合
//        _pSpace_Current->_pElemFirst = NULL;
//        _pSpace_Current->_pElemLast = NULL;
//        _pSpace_Current = NULL;
//    } else if (this == _pSpace_Current->_pElemFirst) {
//        //先頭だった場合
//        _pSpace_Current->_pElemFirst = _pNext;
//        _pSpace_Current->_pElemFirst->_pPrev = NULL;
//        _pNext = NULL;
//        _pSpace_Current = NULL;
//    } else if (this == _pSpace_Current->_pElemLast) {
//        //末尾だった場合
//        _pSpace_Current->_pElemLast = _pPrev;
//        _pSpace_Current->_pElemLast->_pNext = NULL;
//        _pPrev = NULL;
//        _pSpace_Current = NULL;
//    } else {
//        //中間だった場合
//        _pPrev->_pNext = _pNext;
//        _pNext->_pPrev = _pPrev;
//        _pNext = NULL;
//        _pPrev = NULL;
//        _pSpace_Current = NULL;
//    }
}

void GgafLinearOctreeElem::addElem(GgafLinearOctreeSpace* prm_pSpace_target) {
    if (_pSpace_Current == prm_pSpace_target) {
        //_TRACE_("addElemせんでいい");
        return;
    } else {
        if (prm_pSpace_target->_pElemFirst == NULL) {
            //１番目に追加の場合
            prm_pSpace_target->_pElemFirst = this;
            prm_pSpace_target->_pElemLast = this;
            _pNext = NULL;
            _pPrev = NULL;
            _pSpace_Current = prm_pSpace_target;
        } else {
            //末尾に追加の場合
            prm_pSpace_target->_pElemLast->_pNext = this;
            _pPrev = prm_pSpace_target->_pElemLast;
            _pNext = NULL;
            prm_pSpace_target->_pElemLast = this;
            _pSpace_Current = prm_pSpace_target;
        }
    }
    //引数の要素番号
    UINT32 index = prm_pSpace_target->_my_index;
    //親空間すべてに要素種別情報を流す
    while(true) {
//        _pLinearOctree->_paSpace[index]._kindinfobit =
//                _pLinearOctree->_paSpace[index]._kindinfobit | this->_kindbit;
        _pLinearOctree->_paSpace[index]._kindinfobit |= this->_kindbit;
        if (index == 0) {
            break;
        }
        //一つ上の親空間要素番号で繰り返す
        index = (index-1)>>3;
    }
}

//void GgafLinearOctreeElem::moveToSpace(GgafLinearOctreeSpace* prm_pSpace_target) {
//    if (prm_pSpace_target == _pSpace_Current) {
//        return; //移動せんでいい
//    } else {
//        if(_pSpace_Current) {
//            extract(); //抜けますよ
//        }
//        addElem(prm_pSpace_target); //入りますよ
//        return;
//    }
//}

void GgafLinearOctreeElem::dump() {
    _TEXT_("o");
}

GgafLinearOctreeElem::~GgafLinearOctreeElem() {
}
