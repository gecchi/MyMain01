#ifndef FORMATION001_H_
#define FORMATION001_H_
namespace MyStg2nd {

#define ACTOR_NUM_FORMATION001 32
/**
 * フォーメーションアクタークラス .
 */
template<class T>
class Formation001 : public GgafDx9Core::GgafDx9FormationActor {

    GgafCore::GgafActorStore* _pStore;
    bool _was_create_dispatcher;
public:
    Formation001(const char* prm_name, GgafCore::GgafActorStore* prm_pStore = NULL);

    virtual void initialize() override;

    virtual ~Formation001();
};


template<class T>
Formation001<T>::Formation001(const char* prm_name, GgafCore::GgafActorStore* prm_pStore) : GgafDx9Core::GgafDx9FormationActor(prm_name) {
    _class_name = "Formation001";
    if (prm_pStore == NULL) {
        _was_create_dispatcher = true;
        _pStore = NEW GgafCore::GgafActorStore("Store_Formation001");
        T* _paActor = NEW T[ACTOR_NUM_FORMATION001];
        T* pActor;
        for (int i = 0; i < ACTOR_NUM_FORMATION001; i++) {
            pActor = NEW T("Actor_Formation001");
            pActor->inactivateImmediately(); //最初非表示
            _pStore->addSubLast(pActor);
        }
    } else {
        _was_create_dispatcher = false;
        _pStore = prm_pStore;
    }
}

template<class T>
void Formation001<T>::initialize() {
    if (_pParent){
    }
}

template<class T>
Formation001<T>::~Formation001() {
}


}
#endif /*FORMATION001_H_*/
