#ifndef FORMATION001_H_
#define FORMATION001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"
namespace VioletVreath {

#define ACTOR_NUM_FORMATION001 32
/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 */
template<class T>
class Formation001 : public GgafLib::TreeFormation {

    GgafCore::GgafActorDepository* pDepo_;
    bool was_create_dispatcher_;
public:
    Formation001(const char* prm_name, GgafCore::GgafActorDepository* prm_pDepo = nullptr);

    virtual void initialize() override;

    virtual ~Formation001();
};


template<class T>
Formation001<T>::Formation001(const char* prm_name, GgafCore::GgafActorDepository* prm_pDepo) : GgafLib::TreeFormation(prm_name) {
    _class_name = "Formation001";
    if (prm_pDepo == nullptr) {
        was_create_dispatcher_ = true;
        pDepo_ = NEW GgafCore::GgafActorDepository("Depository_Formation001");
        T* pActor;
        for (int i = 0; i < ACTOR_NUM_FORMATION001; i++) {
            pActor = NEW T("Actor_Formation001");
            pActor->inactivate(); //�ŏ���\��
            pDepo_->addSubLast(pActor);
        }
    } else {
        was_create_dispatcher_ = false;
        pDepo_ = prm_pDepo;
    }
}

template<class T>
void Formation001<T>::initialize() {
    if (getParent()){
    }
}

template<class T>
Formation001<T>::~Formation001() {
}


}
#endif /*FORMATION001_H_*/
