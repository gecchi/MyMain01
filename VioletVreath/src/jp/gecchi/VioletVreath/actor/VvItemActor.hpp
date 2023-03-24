#ifndef VVITEMACTOR_H_
#define VVITEMACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvActor.hpp"

namespace VioletVreath {

template<class T>
class VvItemActor : public VvActor<T> {

public:
    VvItemActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr)
            : VvActor<T>(prm_name, prm_model) {
        T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
#ifdef MY_DEBUG
        if (!(T::getDefaultKind() & KIND_ITEM)) {
            throwCriticalException("KIND_ITEM と、ステータスが異なっています。name="<<prm_name);
        }
#endif
    }

    virtual ~VvItemActor() {
    }
};

}

#endif /* VVITEMACTOR_H_ */
