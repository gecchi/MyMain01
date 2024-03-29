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
     * 相手から攻撃を受けた場合の、自分の体力計算結果取得 .
     * @param prm_pOpp 相手アクター
     * @return 自分の残り体力
     */
    int calcStamina(const GgafCore::MainActor* prm_pOpp) {
        GgafCore::Status* pStatThis = this->getStatus();
        const GgafCore::Status* pStatOpp = prm_pOpp->getStatus();
        //自身の属性（優性劣性判定）
        int advantage = MyStgUtil::judgeAdvantage(pStatThis->getUint(STAT_Attribute),pStatOpp->getUint(STAT_Attribute));
        //相手攻撃力
        int opp_attack = pStatOpp->get(STAT_Attack) * pStatOpp->getDouble(STAT_AttackPowerRate);
        //優性劣性に応じて防御率を乗ずる
        int result_stamina;
        if (advantage > 0) {
            //自分が優性時
            result_stamina = pStatThis->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatThis->getDouble(STAT_DominantDefenceRate)));
        } else if (advantage < 0) {
            //自分が劣性時
            result_stamina = pStatThis->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatThis->getDouble(STAT_RecessiveDefenceRate)));
        } else {
            //相手と同格時
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
