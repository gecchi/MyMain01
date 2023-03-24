#ifndef VVENEMYACTOR_H_
#define VVENEMYACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvActor.hpp"

namespace VioletVreath {

template<class T>
class VvEnemyActor : public VvActor<T> {

public:
    VvEnemyActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr)
            : VvActor<T>(prm_name, prm_model) {
        T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
#ifdef MY_DEBUG
        if (!(T::getDefaultKind() & KIND_ENEMRY)) {
            throwCriticalException("KIND_ENEMRY と、ステータスが異なっています。name="<<prm_name);
        }
#endif
    }

    virtual ~VvEnemyActor() {
    }
};

}

#endif /* VVTEKIACTOR_H_ */
