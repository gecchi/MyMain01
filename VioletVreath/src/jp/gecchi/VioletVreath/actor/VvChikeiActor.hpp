#ifndef VVCHIKEIACTOR_H_
#define VVCHIKEIACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvActor.hpp"

namespace VioletVreath {

template<class T>
class VvChikeiActor : public VvActor<T> {

public:
    VvChikeiActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr)
            : VvActor<T>(prm_name, prm_model) {
        T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
#ifdef MY_DEBUG
        if (!(T::getDefaultKind() & KIND_CHIKEI)) {
            throwCriticalException("KIND_CHIKEI と、ステータスが異なっています。name="<<prm_name);
        }
#endif
    }

    virtual ~VvChikeiActor() {

    }
};

}

#endif /* VVCHIKEIACTOR_H_ */
