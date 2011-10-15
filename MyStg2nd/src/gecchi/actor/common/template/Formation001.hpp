#ifndef FORMATION001_H_
#define FORMATION001_H_
namespace MyStg2nd {

#define ACTOR_NUM_FORMATION001 32
/**
 * フォーメーションアクタークラス .
 */
template<class T>
class Formation001 : public GgafLib::TreeFormation {

    GgafCore::GgafActorDepository* _pDepo;
    bool _was_create_dispatcher;
public:
    Formation001(const char* prm_name, GgafCore::GgafActorDepository* prm_pDepo = NULL);

    virtual void initialize() override;

    virtual ~Formation001();
};


template<class T>
Formation001<T>::Formation001(const char* prm_name, GgafCore::GgafActorDepository* prm_pDepo) : GgafLib::TreeFormation(prm_name) {
    _class_name = "Formation001";
    if (prm_pDepo == NULL) {
        _was_create_dispatcher = true;
        _pDepo = NEW GgafCore::GgafActorDepository("Depository_Formation001");
        T* _paActor = NEW T[ACTOR_NUM_FORMATION001];
        T* pActor;
        for (int i = 0; i < ACTOR_NUM_FORMATION001; i++) {
            pActor = NEW T("Actor_Formation001");
            pActor->inactivateImmediately(); //最初非表示
            _pDepo->addSubLast(pActor);
        }
    } else {
        _was_create_dispatcher = false;
        _pDepo = prm_pDepo;
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
