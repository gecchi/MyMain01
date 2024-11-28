#ifndef VVITEMACTOR_H_
#define VVITEMACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvGeometricActor.hpp"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"

namespace VioletVreath {

template<class T>
class VvItemActor : public VvGeometricActor<T> {

public:
    TractorMagic* pTractorMagic_;

public:
    VvItemActor(const char* prm_name, const char* prm_model, void* prm_pFuncResetStatus = nullptr)
            : VvGeometricActor<T>(prm_name, prm_model, prm_pFuncResetStatus) {

        pTractorMagic_ = nullptr;
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind & KIND_ITEM)) {
            throwCriticalException("KIND_ITEM と、ステータスが異なっています。name="<<prm_name);
        }
#endif
    }

    TractorMagic* getTractorMagic() {
        if (pTractorMagic_ == nullptr) {
            pTractorMagic_ = pMAGICMETER->pTractorMagic_;
        }
        return pTractorMagic_;
    }


    virtual ~VvItemActor() {
    }
};

}

#endif /* VVITEMACTOR_H_ */
