#include "VvEffectActor.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

template <class T>
VvEffectActor<T>::VvEffectActor(const char* prm_name, const char* prm_model_id, void* prm_pPrm1)
    : VvActor<T>(prm_name, prm_model_id) {
    T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
}


template <class T>
VvEffectActor<T>::~VvEffectActor() {
}


//ŽÀ‘Ì‰»
template class VvEffectActor<GgafLib::DefaultSpriteActor>;

