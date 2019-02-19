#include "VvItemActor.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

template <class T>
VvItemActor<T>::VvItemActor(const char* prm_name, const char* prm_model_id, void* prm_pPrm1)
    : VvActor<T>(prm_name, prm_model_id) {
    T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
}

template <class T>
VvItemActor<T>::~VvItemActor() {
}

//���̉�
template class VvItemActor<GgafLib::DefaultSpriteActor>;

