#ifndef MENUACTOR_H_
#define MENUACTOR_H_
namespace GgafLib {

enum MenuItemWay {
    ITEM_RELATION_EX_NEXT = 0,
    ITEM_RELATION_EX_PREV,
    ITEM_RELATION_TO_CANCEL,
};

/**
 * ���j���[GUI�e���v���[�g .
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
     * �J�[�\���ƂȂ�A�N�^�[�Ɠ�����ݒ肷��B
     * �y���Ӂz<BR>
     * �J�[�\���ړ��𐧌䂷�邽�߁AMenuActor<T>::processBehavior() ���ŁA<BR>
     * _pCursor->_pKurokoA->behave(); <BR>
     * �����s���Ă��܂��B���������āA�����̃J�[�\���N���X�ŁA
     * _pKurokoA->behave();
     * �����s����K�v�͂���܂���B<BR>
     * @param prm_pCursor �J�[�\���̃A�N�^�[
     * @param prm_move_frames �J�[�\�����A�C�e���Ԉړ��ɔ�₷�t���[��(�f�t�H���g10�t���[��)
     * @param prm_move_p1 �J�[�\�����ړ����A�A�C�e���Ԉړ������̑��x�O�`�ō����ɒB���鎞�_�̊���(�f�t�H���g0.2)
     * @param prm_move_p2 �J�[�\�����ړ����A�A�C�e���Ԉړ������̍ō������猸�����J�n���銄��(�f�t�H���g0.7)
     */
    virtual void setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor,
                           int prm_move_frames = 10, float prm_move_p1 = 0.2, float prm_move_p2 = 0.7);


    virtual void relationItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem);
//    virtual void relationItemExNext(int prm_index_of_fromitem, ...);
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
  T(prm_name, prm_model, NULL),_lstItems(3) { //�}���R��
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
    prm_pItem->_fAlpha = T::_fAlpha; //�������������L������B
    prm_pItem->inactivateImmediately();

    _lstItems.addLast(prm_pItem);
    T::addSubLast(prm_pItem);
}

template<class T>
void MenuActor<T>::setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor,
                             int prm_move_frames, float prm_move_p1, float prm_move_p2) {
    _pCursor = prm_pCursor;
    _cursor_move_frames = prm_move_frames;
    _cursor_move_p1 = prm_move_p1;
    _cursor_move_p2 = prm_move_p2;
    T::addSubLast(prm_pCursor);

    _pCursor->_fAlpha = T::_fAlpha;
    _pCursor->inactivateImmediately();
}

template<class T>
void MenuActor<T>:: relationItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

//template<class T>
//void MenuActor<T>:: relationItemExNext(int prm_index_of_fromitem, ...) {
//    va_list pArg;
//    va_start(pArg, prm_index_of_fromitem);         //�ϒ���������J�n
//        va_arg( argptr, int );
//
//
//
//    va_end(pArg);      //�ϒ���������I��
//}


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
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        _lstItems.gotoRelation(ITEM_RELATION_EX_NEXT);
        moveCursor();
    } else {

    }
}

template<class T>
void MenuActor<T>::moveCursorExPrev() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_PREV)) {
        _lstItems.gotoRelation(ITEM_RELATION_EX_PREV);
        moveCursor();
    } else {

    }
}

template<class T>
void MenuActor<T>::moveCursorCancel() {
    if (_lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        _lstItems.gotoRelation(ITEM_RELATION_TO_CANCEL);
        moveCursor();
    } else {

    }
}

template<class T>
void MenuActor<T>::moveCursor() {
    if (_pCursor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        _pCursor->_pKurokoA->setMvAng(pTargetItem);
        _pCursor->_pKurokoA->execSmoothMvVeloSequence(0, GgafDxCore::GgafDxUtil::getDistance(_pCursor, pTargetItem),
                                                    _cursor_move_frames,
                                                    _cursor_move_p1, _cursor_move_p2);
        _X_cursor_target_begin = pTargetItem->_X;
        _Y_cursor_target_begin = pTargetItem->_Y;
        _Z_cursor_target_begin = pTargetItem->_Z;
    }
}


template<class T>
void MenuActor<T>::rise() {
    //���j���[�A�C�e�����΂�
    GgafDxCore::GgafDxDrawableActor* pItem;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        pItem = pElem->_pValue;
        pItem->locate(T::_X + pItem->_X_local,
                      T::_Y + pItem->_Y_local,
                      T::_Z + pItem->_Z_local);
        pItem->_fAlpha = T::_fAlpha;
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


    //�J�[�\���ړ�
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

    //���j���[�A�C�e��
    GgafDxCore::GgafDxDrawableActor* pItem;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        pItem = pElem->_pValue;
        pItem->locate(T::_X + pItem->_X_local,
                      T::_Y + pItem->_Y_local,
                      T::_Z + pItem->_Z_local);
		pItem->_fAlpha = T::_fAlpha;
        pElem = pElem->_pNext;
    }

    //�J�[�\��
    GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
    if (_pCursor->_pKurokoA->isMoveingSmooth()) {
        _pCursor->_X += (pTargetItem->_X - _X_cursor_target_begin);
        _pCursor->_Y += (pTargetItem->_Y - _Y_cursor_target_begin);
        _pCursor->_Z += (pTargetItem->_Z - _Z_cursor_target_begin);
    } else {
        _pCursor->locateAs(pTargetItem);
    }
    _pCursor->_fAlpha = T::_fAlpha;
}


template<class T>
MenuActor<T>::~MenuActor() {
}

#define DefaultBoardMenu GgafLib::MenuActor<GgafLib::DefaultBoardActor>
#define DefaultBoardSetMenu GgafLib::MenuActor<GgafLib::DefaultBoardSetActor>


}
#endif /*FORMATION001_H_*/
