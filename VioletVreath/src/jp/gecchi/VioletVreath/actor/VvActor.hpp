#ifndef VVACTOR_H_
#define VVACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"


namespace VioletVreath {

template<class T>
class VvActor : public T {
//    GgafLib::DefaultScene* pFeatureScene_;
//    GgafDx::VehicleLeader* pFeatureVehicleLeader_;
public:
    VvActor(const char* prm_name, const char* prm_model)
        : T(prm_name, prm_model) {
//        pFeatureScene_ = nullptr;
//        pFeatureVehicleLeader_ = nullptr;
    }
    /**
     * ‘ŠŽè‚©‚çUŒ‚‚ðŽó‚¯‚½ê‡‚ÌAŽ©•ª‚Ì‘Ì—ÍŒvŽZŒ‹‰ÊŽæ“¾ .
     * @param prm_pOpp ‘ŠŽèƒAƒNƒ^[
     * @return Ž©•ª‚ÌŽc‚è‘Ì—Í
     */
    int calcStamina(const GgafCore::MainActor* prm_pOpp) {
        GgafCore::Status* pStatThis = this->getStatus();
        const GgafCore::Status* pStatOpp = prm_pOpp->getStatus();
        //Ž©g‚Ì‘®«i—D«—ò«”»’èj
        int advantage = MyStgUtil::judgeAdvantage(pStatThis->getUint(STAT_Attribute),pStatOpp->getUint(STAT_Attribute));
        //‘ŠŽèUŒ‚—Í
        int opp_attack = pStatOpp->get(STAT_Attack) * pStatOpp->getDouble(STAT_AttackPowerRate);
        //—D«—ò«‚É‰ž‚¶‚Ä–hŒä—¦‚ðæ‚¸‚é
        int result_stamina;
        if (advantage > 0) {
            //Ž©•ª‚ª—D«Žž
            result_stamina = pStatThis->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatThis->getDouble(STAT_DominantDefenceRate)));
        } else if (advantage < 0) {
            //Ž©•ª‚ª—ò«Žž
            result_stamina = pStatThis->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatThis->getDouble(STAT_RecessiveDefenceRate)));
        } else {
            //‘ŠŽè‚Æ“¯ŠiŽž
            result_stamina = pStatThis->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatThis->getDouble(STAT_DefaultDefenceRate)));
        }
        return result_stamina;
    }

//    void registerpFeatureVehicleLeader(GgafDx::VehicleLeader* prm_pVehicleLeader) {
//        pFeatureVehicleLeader_ = prm_pVehicleLeader;
//        pFeatureScene_ = ((GgafLib::DefaultScene*)(T::getSceneChief()->getPlatformScene()))->getNearestFeatureScene();
//        //pFeatureScene_->_pFuncFeature(pFeatureVehicleLeader_, &(pFeatureScene_->_feature_p1), nullptr, nullptr);
//            //pVehicleLeader_->_x_start_in_loop -= pFeatureScene_->getFeatureParam1();
//    }
//    void executeFuncLowerTree(void (*pFunc)(GgafCore::Object*, void*, void*, void*), void* prm1, void* prm2, void* prm3) override {
//        T::executeFuncLowerTree(pFunc, prm1, prm2, prm3);
//        if (pFeatureVehicleLeader_ && pFunc == pFeatureScene_->_pFuncFeature) {
//            if (T::_can_live_flg && T::_is_active_flg) {
//                pFunc((GgafCore::Object*)pFeatureVehicleLeader_, &(pFeatureScene_->_feature_p1), prm2, prm3);
//            }
//        }
//    }

    virtual ~VvActor() {
    }
};

}

#endif /* VVACTOR_H_ */
