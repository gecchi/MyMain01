#include "VvMyActor.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

template <class T>
VvMyActor<T>::VvMyActor(const char* prm_name, const char* prm_model, void* prm_pPrm1)
    : VvGeometricActor<T>(prm_name, prm_model) {
    T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
}


template <class T>
VvMyActor<T>::~VvMyActor() {
}


//ŽÀ‘Ì‰»
template class VvMyActor<GgafLib::DefaultSpriteActor>;

