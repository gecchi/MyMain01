#ifndef VVACTOR_H_
#define VVACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"


namespace VioletVreath {

template<class T>
class VvActor : public T {

public:
    VvActor(const char* prm_name, const char* prm_model_id)
        : T(prm_name, prm_model_id) {
    }

//    GgafDx::FigureActor* activateExplosionEffect() {
//        GgafDx::FigureActor* pE = nullptr;
//        switch (T::getStatus()->get(STAT_ExplosionEffectKind)) {
//            case 0: {
//                pE = nullptr; //爆発エフェクト無し
//                break;
//            }
//            case MyStgUtil::EF_EXPLOSION001: {
//                pE = dispatchForceFromCommon(EffectExplosion001);
//                if (pE) {
//                    if (pE->isActiveInTheTree()) {
//                        pE->onInactive();
//                        pE->_frame_of_behaving_since_onActive = 1;
//                        pE->onActive();
//                    }
//                    pE->setPositionAt(this);
//                    pE->callRikisha()->takeoverMvFrom(this->callRikisha());
//                }
//                break;
//            }
//            case MyStgUtil::EF_EXPLOSION002: {
//                pE = dispatchForceFromCommon(EffectExplosion002);
//                if (pE) {
//                    pE->setPositionAt(this);
//                    pE->callRikisha()->takeoverMvFrom(this->callRikisha());
//                }
//                break;
//            }
//            case MyStgUtil::EF_EXPLOSION003: {
//                pE = dispatchForceFromCommon(EffectExplosion003);
//                if (pE) {
//                    pE->setPositionAt(this);
//                    pE->callRikisha()->takeoverMvFrom(this->callRikisha());
//                }
//                break;
//            }
//            case MyStgUtil::EF_EXPLOSION001_STAY: {
//                pE = dispatchForceFromCommon(EffectExplosion001);
//                if (pE) {
//                    pE->setPositionAt(this);
//                    pE->callRikisha()->setMvVelo(0);
//                    pE->callRikisha()->setMvAcce(0);
//                }
//                break;
//            }
//            default: {
//                throwCriticalException("対応 ExplosionEffect が定義されてない。this="<<this->getName()<<"("<<this<<")");
//                pE = nullptr;
//                break;
//            }
//        }
//        if (pE) {
//            //出現座標を設定
//
//        }
//        return pE;
//    }

    virtual ~VvActor() {
    }
};

}

#endif /* VVACTOR_H_ */
