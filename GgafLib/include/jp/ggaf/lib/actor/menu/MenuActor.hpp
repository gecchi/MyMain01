#ifndef MENUACTOR_H_
#define MENUACTOR_H_
namespace GgafLib {

enum MenuItemWay {
    ACTIVE_ITEM_NEXT,
    ACTIVE_ITEM_PREV,
    ACTIVE_ITEM_RELATION_NEXT,
    ACTIVE_ITEM_RELATION_PREV,
    ACTIVE_ITEM_CANCEL,
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
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstItems;
    GgafDxCore::GgafDxDrawableActor* pCursor;

    MenuActor(const char* prm_name, const char* prm_model);

    virtual void addItem(GgafDxCore::GgafDxDrawableActor** prm_papMenuItem, int prm_num);

    virtual void relationItemNext(GgafDxDrawableActor* );
    virtual void relationItemNext();

    virtual int getSelectedItemIndex();

    virtual void moveCursorNext();
    virtual void moveCursorPrev();
    virtual void moveCursorRelationNext();
    virtual void moveCursorRelationPrev();
    virtual void moveCursorCancel();

    virtual ~MenuActor();
};


template<class T>
MenuActor<T>::MenuActor(const char* prm_name, const char* prm_model) :
  T(prm_name, prm_model, NULL),_lstItems(3) {
    T::_class_name = "MenuActor";
}


template<class T>
MenuActor<T>::~MenuActor() {
}


}
#endif /*FORMATION001_H_*/
