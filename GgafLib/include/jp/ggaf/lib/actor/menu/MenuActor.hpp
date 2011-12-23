#ifndef MENUACTOR_H_
#define MENUACTOR_H_
namespace GgafLib {

enum MenuItemWay {
    ITEM_RELATION_EX_NEXT = 0,
    ITEM_RELATION_EX_PREV,
    ITEM_RELATION_TO_CANCEL,
};

/**
 * メニューGUIテンプレート .
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
template<class T>
class MenuActor : public T {

public:
    int _cursor_move_frames;
    float _cursor_move_p1;
    float _cursor_move_p2;

    coord _X_cursor_target_begin;
    coord _Y_cursor_target_begin;
    coord _Z_cursor_target_begin;

    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstItems;
    GgafDxCore::GgafDxDrawableActor* _pCursor;

    MenuActor(const char* prm_name, const char* prm_model);

    virtual void addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                         coord prm_X_local, coord prm_Y_local, coord prm_Z_local);

    /**
     * カーソルとなるアクターを設定する。
     * 【注意】<BR>
     * カーソル移動を制御するため、MenuActor<T>::processBehavior() 内で、<BR>
     * _pCursor->_pKurokoA->behave(); <BR>
     * を実行しています。したがって、引数のカーソルクラスで、
     * _pKurokoA->behave();
     * を実行する必要はありません。<BR>
     * @param prm_pCursor カーソルのアクター
     * @param prm_move_frames アイテム間移動に費やすフレーム
     * @param prm_move_p1 速度０～最高速に達する時点の割合
     * @param prm_move_p2 最高速から減速を開始する割合
     */
    virtual void setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor,
                           int prm_move_frames, float prm_move_p1 = 0.2, float prm_move_p2 = 0.7);

    virtual void relationItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem);
    virtual void relationItemExPrev(int prm_index_of_fromitem, int prm_index_of_toitem);

    virtual GgafDxCore::GgafDxDrawableActor* setSelectedItemIndex(int prm_index);
    virtual int getSelectedItemIndex();
    virtual GgafDxCore::GgafDxDrawableActor* getSelectedItem();

    virtual bool condCursorNext() {
        return false;
    }
    virtual bool condCursorPrev() {
        return false;
    }
    virtual bool condCursorExNext() {
        return false;
    }
    virtual bool condCursorExPrev() {
        return false;
    }
    virtual bool condCursorCancel() {
        return false;
    }
    virtual void moveCursor();
    virtual void moveCursorNext();
    virtual void moveCursorPrev();
    virtual void moveCursorExNext();
    virtual void moveCursorExPrev();
    virtual void moveCursorCancel();

    virtual void rise();
    virtual void processBehavior() override;
    virtual void sink();

    virtual ~MenuActor();
};


template<class T>
MenuActor<T>::MenuActor(const char* prm_name, const char* prm_model) :
  T(prm_name, prm_model, NULL),_lstItems(3) { //枝を３つ
    T::_class_name = "MenuActor";
    _cursor_move_frames = 10;
    _cursor_move_p1 = 0.2;
    _cursor_move_p2 = 0.7;
    _X_cursor_target_begin = T::_X;
    _Y_cursor_target_begin = T::_Y;
    _Z_cursor_target_begin = T::_Z;
    T::inactivateImmediately();
}


template<class T>
void MenuActor<T>::addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                           coord prm_X_local, coord prm_Y_local, coord prm_Z_local) {
    prm_pItem->_X_local = prm_X_local;
    prm_pItem->_Y_local = prm_Y_local;
    prm_pItem->_Z_local = prm_Z_local;
    _lstItems.addLast(prm_pItem);
    T::addSubLast(prm_pItem);
    prm_pItem->inactivateImmediately();
}

template<class T>
void MenuActor<T>::setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor,
                             int prm_move_frames, float prm_move_p1, float prm_move_p2) {
    _pCursor = prm_pCursor;
    _cursor_move_frames = prm_move_frames;
    _cursor_move_p1 = prm_move_p1;
    _cursor_move_p2 = prm_move_p2;
    T::addSubLast(prm_pCursor);
    _pCursor->inactivateImmediately();
}

template<class T>
void MenuActor<T>:: relationItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}
template<class T>
void MenuActor<T>:: relationItemExPrev(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::setSelectedItemIndex(int prm_index) {
    return _lstItems.current(prm_index);
}

template<class T>
int MenuActor<T>::getSelectedItemIndex() {
    return _lstItems.getCurrentIndex();
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getSelectedItem() {
    return _lstItems.getCurrent();
}

template<class T>
void MenuActor<T>::moveCursorNext() {
    _lstItems.next();
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorPrev() {
    _lstItems.prev();
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorExNext() {
    _lstItems.gotoRelation(ITEM_RELATION_EX_NEXT);
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorExPrev() {
    _lstItems.gotoRelation(ITEM_RELATION_EX_PREV);
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorCancel() {
    _lstItems.gotoRelation(ITEM_RELATION_TO_CANCEL);
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursor() {
    GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
    _pCursor->_pKurokoA->setMvAng(pTargetItem);
    _pCursor->_pKurokoA->execSmoothMvVeloSequence(0, GgafDxCore::GgafDxUtil::getDistance(_pCursor, pTargetItem),
                                                _cursor_move_frames,
                                                _cursor_move_p1, _cursor_move_p2);
    _X_cursor_target_begin = pTargetItem->_X;
    _Y_cursor_target_begin = pTargetItem->_Y;
    _Z_cursor_target_begin = pTargetItem->_Z;
}


template<class T>
void MenuActor<T>::rise() {
    //メニューアイテムを飛ばす
    GgafDxCore::GgafDxDrawableActor* pItem;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        pItem = pElem->_pValue;
        pItem->locate(T::_X + pItem->_X_local,
                      T::_Y + pItem->_Y_local,
                      T::_Z + pItem->_Z_local);
        pElem = pElem->_pNext;
    }
    T::activateTree();
}
template<class T>
void MenuActor<T>::sink() {
    T::inactivateTree();
}

template<class T>
void MenuActor<T>::processBehavior() {


    //カーソル移動
    if (condCursorNext()) {
        moveCursorNext();
    } else if (condCursorPrev()) {
        moveCursorPrev();
    } else if (condCursorExNext()) {
        moveCursorExNext();
    } else if (condCursorExPrev()) {
        moveCursorExPrev();
    } else if (condCursorCancel()) {
        moveCursorCancel();
    }
    _pCursor->_pKurokoA->behave();

    GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
    if (_pCursor->_pKurokoA->isMoveingSmooth()) {
        _pCursor->_X += (pTargetItem->_X - _X_cursor_target_begin);
        _pCursor->_Y += (pTargetItem->_Y - _Y_cursor_target_begin);
        _pCursor->_Z += (pTargetItem->_Z - _Z_cursor_target_begin);
    } else {
        _pCursor->locateAs(pTargetItem);
    }
}


template<class T>
MenuActor<T>::~MenuActor() {
}


}
#endif /*FORMATION001_H_*/
