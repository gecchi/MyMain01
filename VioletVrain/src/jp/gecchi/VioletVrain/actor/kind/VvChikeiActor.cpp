#include "VvChikeiActor.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

template <class T>
VvChikeiActor<T>::VvChikeiActor(const char* prm_name, const char* prm_model_id, void* prm_pPrm1)
    : VvActor<T>(prm_name, prm_model_id) {
    T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
}


template <class T>
VvChikeiActor<T>::~VvChikeiActor() {
}


//���̉�
template class VvChikeiActor<GgafLib::DefaultSpriteActor>;
template class VvChikeiActor<GgafLib::DefaultBoardActor>;
