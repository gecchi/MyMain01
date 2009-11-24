#ifndef FORMATION001_H_
#define FORMATION001_H_
namespace MyStg2nd {

#define ACTOR_NUM_FORMATION001 32
/**
 * フォーメーションアクタークラス .
 */
template<class T>
class Formation001 : public GgafDx9LibStg::FormationActor {

    GgafDx9LibStg::ActorDispatcher* _pDispatcher;
    bool _was_create_dispatcher;
public:
    Formation001(const char* prm_name, GgafDx9LibStg::ActorDispatcher* prm_pDispatcher = NULL);

    virtual void initialize();

    virtual ~Formation001();
};


template<class T>
Formation001<T>::Formation001(const char* prm_name, GgafDx9LibStg::ActorDispatcher* prm_pDispatcher) : GgafDx9LibStg::FormationActor(prm_name) {
    _class_name = "Formation001";
    if (prm_pDispatcher == NULL) {
        _was_create_dispatcher = true;
        _pDispatcher = NEW GgafDx9LibStg::ActorDispatcher("Dispatcher_Formation001");
        T* _paActor = NEW T[ACTOR_NUM_FORMATION001];
        T* pActor;
        for (int i = 0; i < ACTOR_NUM_FORMATION001; i++) {
            pActor = NEW T("Actor_Formation001");
            pActor->inactivateImmediately(); //最初非表示
            _pDispatcher->addSubLast(pActor);
        }
    } else {
        _was_create_dispatcher = false;
        _pDispatcher = prm_pDispatcher;


    }
}

template<class T>
void Formation001<T>::initialize() {
    if (_pParent != NULL){
    }
}

template<class T>
Formation001<T>::~Formation001() {
}


}
#endif /*FORMATION001_H_*/
