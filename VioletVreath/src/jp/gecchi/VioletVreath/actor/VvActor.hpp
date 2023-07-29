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
     * ���肩��U�����󂯂��ꍇ�́A�����̗̑͌v�Z���ʎ擾 .
     * @param prm_pOpp ����
     * @return �����̗̑�
     */
    int calcStamina(const GgafCore::MainActor* prm_pOpp) {
//    int MyStgUtil::calcEnemyStamina(GgafCore::MainActor* prm_pEnemy, const GgafCore::MainActor* const prm_pOpp) {
        GgafCore::Status* pStatThis = this->getStatus();
        const GgafCore::Status* pStatOpp = prm_pOpp->getStatus();
        //���g�̑����i�D���򐫔���j
        //int advantage = MyStgUtil::judgeEnemyAdvantage(pStatThis->getUint(STAT_Attribute),pStatOpp->getUint(STAT_Attribute));
        int advantage = MyStgUtil::judgeAdvantage(pStatThis->getUint(STAT_Attribute),pStatOpp->getUint(STAT_Attribute));
        //����U����
        int opp_attack = pStatOpp->get(STAT_Attack) * pStatOpp->getDouble(STAT_AttackPowerRate);
        //�D���򐫂ɉ����Ėh�䗦���悸��
        int result_stamina;
        if (advantage > 0) {
            //�������D����
            result_stamina = pStatThis->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatThis->getDouble(STAT_DominantDefenceRate)));
        } else if (advantage < 0) {
            //�������򐫎�
            result_stamina = pStatThis->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatThis->getDouble(STAT_RecessiveDefenceRate)));
        } else {
            //����Ɠ��i��
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
//    GgafDx::FigureActor* activateExplosionEffect() {
//        GgafDx::FigureActor* pE = nullptr;
//        switch (T::getStatus()->get(STAT_ExplosionEffectKind)) {
//            case 0: {
//                pE = nullptr; //�����G�t�F�N�g����
//                break;
//            }
//            case MyStgUtil::EF_EXPLOSION001: {
//                pE = CommonScene_dispatchForce(EffectExplosion001);
//                pE->setPositionAt(this);
//                pE->getLocoVehicle()->takeoverFrom(this->getLocoVehicle());
//                break;
//            }
//            case MyStgUtil::EF_EXPLOSION002: {
//                pE = CommonScene_dispatchForce(EffectExplosion002);
//                pE->setPositionAt(this);
//                pE->getLocoVehicle()->takeoverFrom(this->getLocoVehicle());
//                break;
//            }
//            case MyStgUtil::EF_EXPLOSION003: {
//                pE = CommonScene_dispatchForce(EffectExplosion003);
//                pE->setPositionAt(this);
//                pE->getLocoVehicle()->takeoverFrom(this->getLocoVehicle());
//                break;
//            }
//            case MyStgUtil::EF_EXPLOSION001_STAY: {
//                pE = CommonScene_dispatchForce(EffectExplosion001);
//                pE->setPositionAt(this);
//                pE->getLocoVehicle()->setMvVelo(0);
//                pE->getLocoVehicle()->setMvAcce(0);
//                break;
//            }
//            default: {
//                throwCriticalException("�Ή� ExplosionEffect ����`����ĂȂ��Bthis="<<this->getName()<<"("<<this<<")");
//                pE = nullptr;
//                break;
//            }
//        }
//        if (pE) {
//            //�o�����W��ݒ�
//
//        }
//        return pE;
//    }

    virtual ~VvActor() {
    }
};

}

#endif /* VVACTOR_H_ */
