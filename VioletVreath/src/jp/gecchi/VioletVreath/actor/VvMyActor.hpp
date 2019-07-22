#ifndef VVMYACTOR_H_
#define VVMYACTOR_H_
#include "VioletVreath.h"
#include "VvActor.hpp"

namespace VioletVreath {

template<class T>
class VvMyActor : public VvActor<T> {

public:
    VvMyActor(const char* prm_name, const char* prm_model_id, void* prm_pPrm1 = nullptr)
            : VvActor<T>(prm_name, prm_model_id) {
        T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
#ifdef MY_DEBUG
        if (!(T::getDefaultKind() & KIND_MY)) {
            throwCriticalException("KIND_MY �ƁA�X�e�[�^�X���قȂ��Ă��܂��Bname="<<prm_name);
        }
#endif
    }

    virtual ~VvMyActor() {
    }
};

}

#endif /* VVMIKATAACTOR_H_ */
