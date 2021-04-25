#ifndef VVACTOR_H_
#define VVACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"


namespace VioletVreath {

template<class T>
class VvActor : public T {
//    GgafLib::DefaultScene* pFeatureScene_;
//    GgafDx::DriverLeader* pFeatureDriverLeader_;
public:
    VvActor(const char* prm_name, const char* prm_model_id)
        : T(prm_name, prm_model_id) {
//        pFeatureScene_ = nullptr;
//        pFeatureDriverLeader_ = nullptr;
    }
//    void registerpFeatureDriverLeader(GgafDx::DriverLeader* prm_pDriverLeader) {
//        pFeatureDriverLeader_ = prm_pDriverLeader;
//        pFeatureScene_ = ((GgafLib::DefaultScene*)(T::getSceneMediator()->getPlatformScene()))->getNearestFeatureScene();
//        //pFeatureScene_->_pFuncFeature(pFeatureDriverLeader_, &(pFeatureScene_->_feature_p1), nullptr, nullptr);
//            //pDriverLeader_->_x_start_in_loop -= pFeatureScene_->getFeatureParam1();
//    }
//    void executeFuncLowerTree(void (*pFunc)(GgafCore::Object*, void*, void*, void*), void* prm1, void* prm2, void* prm3) override {
//        T::executeFuncLowerTree(pFunc, prm1, prm2, prm3);
//        if (pFeatureDriverLeader_ && pFunc == pFeatureScene_->_pFuncFeature) {
//            if (T::_can_live_flg && T::_is_active_flg) {
//                pFunc((GgafCore::Object*)pFeatureDriverLeader_, &(pFeatureScene_->_feature_p1), prm2, prm3);
//            }
//        }
//    }
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
//                    pE->getVecDriver()->takeoverMvFrom(this->getVecDriver());
//                }
//                break;
//            }
//            case MyStgUtil::EF_EXPLOSION002: {
//                pE = dispatchForceFromCommon(EffectExplosion002);
//                if (pE) {
//                    pE->setPositionAt(this);
//                    pE->getVecDriver()->takeoverMvFrom(this->getVecDriver());
//                }
//                break;
//            }
//            case MyStgUtil::EF_EXPLOSION003: {
//                pE = dispatchForceFromCommon(EffectExplosion003);
//                if (pE) {
//                    pE->setPositionAt(this);
//                    pE->getVecDriver()->takeoverMvFrom(this->getVecDriver());
//                }
//                break;
//            }
//            case MyStgUtil::EF_EXPLOSION001_STAY: {
//                pE = dispatchForceFromCommon(EffectExplosion001);
//                if (pE) {
//                    pE->setPositionAt(this);
//                    pE->getVecDriver()->setMvVelo(0);
//                    pE->getVecDriver()->setMvAcce(0);
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
