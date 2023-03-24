#ifndef VVMYACTOR_H_
#define VVMYACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvActor.hpp"

namespace VioletVreath {

template<class T>
class VvMyActor : public VvActor<T> {

public:
    VvMyActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr)
            : VvActor<T>(prm_name, prm_model) {
        T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
#ifdef MY_DEBUG
        if (!(T::getDefaultKind() & KIND_MY)) {
            throwCriticalException("KIND_MY と、ステータスが異なっています。name="<<prm_name);
        }
#endif
    }

    virtual ~VvMyActor() {
    }
};

}

#endif /* VVMIKATAACTOR_H_ */
