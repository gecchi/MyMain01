#include "VvEnemyActor.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

template <class T>
VvEnemyActor<T>::VvEnemyActor(const char* prm_name, const char* prm_model, void* prm_pPrm1)
    : VvActor<T>(prm_name, prm_model) {
    T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
}


template <class T>
VvEnemyActor<T>::~VvEnemyActor() {
}


//���̉�
template class VvEnemyActor<GgafLib::DefaultSpriteActor>;

