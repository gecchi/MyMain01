#include "CommonScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/core/actor/ex/ActorDepositoryStore.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

#define REGISTER_DEPO(TYPE, NUM)   do { \
        CommonScene_pCOMMON_DEPO(TYPE) = NEW GgafCore::ActorDepository("Depo_" #TYPE); \
        CommonScene_pCOMMON_DEPO(TYPE)->putn<TYPE>(NUM); \
        bringSceneMediator()->appendGroupChild(CommonScene_pCOMMON_DEPO(TYPE)); \
}while(0)
#define REGISTER_LASERDEPO_STORE(TYPE, SET_NUM, LASER_NUM) do { \
    CommonScene_pCOMMON_DEPO_STORE(TYPE) = NEW GgafCore::ActorDepositoryStore("DepoStore_" #TYPE); \
    LaserChipDepository* pLaserChipDepo; \
    for (int laser_set = 0; laser_set < SET_NUM; laser_set++) { \
        std::string name_depo = "LaserChipDepo["+XTOS(laser_set)+"]"; \
        pLaserChipDepo = NEW LaserChipDepository(name_depo.c_str()); \
        pLaserChipDepo->putn<TYPE>(LASER_NUM); \
        CommonScene_pCOMMON_DEPO_STORE(TYPE)->put(pLaserChipDepo); \
    } \
    bringSceneMediator()->appendGroupChild(CommonScene_pCOMMON_DEPO_STORE(TYPE)); \
}while(0)


CommonScene::CommonScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "CommonScene";

    //全シーンに渡って常時使用な汎用的なアクター類は
    //ココにそのデポジトリを事前作成する。
    //汎用爆発エフェクト
    REGISTER_DEPO(EffectExplosion001, 300);
    //汎用爆発エフェクト
    REGISTER_DEPO(EffectExplosion002, 100);
    //汎用爆発エフェクト
    REGISTER_DEPO(EffectExplosion003, 50);
    //汎用爆発エフェクト大
    REGISTER_DEPO(EffectExplosion004, 100);
    //アイテム小
    REGISTER_DEPO(MagicPointItem001, 400);
    //アイテム中
    REGISTER_DEPO(MagicPointItem002, 30);
    //アイテム大
    REGISTER_DEPO(MagicPointItem003, 10);
    //Effect EffectTurbo002 ターボ噴射
    REGISTER_DEPO(EffectTurbo002, 10);
    //汎用出現エフェクト EffectBlink001
    REGISTER_DEPO(EffectBlink001, 200);
    //汎用出現エフェクト EffectBlink002
    REGISTER_DEPO(EffectBlink002, 30);
    //汎用出現エフェクト EffectBlink003
    REGISTER_DEPO(EffectBlink003, 30);
    //ボーナスポイント表示エフェクト
    REGISTER_DEPO(SpriteLabelBonus001, 30);
    //汎用ショット
    REGISTER_DEPO(Shot004, 30);

    REGISTER_LASERDEPO_STORE(EnemyWateringLaserChip001, 30, 40);
    REGISTER_LASERDEPO_STORE(EnemyStraightLaserChip001, 8 , 40);

}

void CommonScene::initialize() {
}

void CommonScene::onReset() {
    //スクロール解除
    setFeatureFunction(nullptr);
    setFeatureParam1(0);

    fadeinScene(0);
}

void CommonScene::processBehavior() {

}

void CommonScene::scrollX(GgafCore::Object* pThat, void* p1, void* p2, void* p3) {

    if (pThat->instanceOf(Obj_GgafDx_GeometricActor)) {
        GgafDx::GeometricActor* pActor = (GgafDx::GeometricActor*)pThat;

        if (pActor->lookUpKind() & KIND_ITEM) {
            //Itemはスクロールの影響を受けない
        } else {
            pActor->_x -= (*((coord*)p1));
            //setVehicleLeader() されていたら、スクロールの影響を受ける
            GgafDx::VehicleLeader* pVehicleLeader = pActor->getVehicleLeader();
            if (pVehicleLeader) {
                pVehicleLeader->_x_start_in_loop -= (*((coord*)p1));
            }
        }


        //ここだめ_was_paused_flg
//        if (pActor->getSceneMediator()->getPlatformScene()->_was_paused_flg == false) {
//            if (pActor->lookUpKind() & KIND_ITEM) {
//                //Itemはスクロールの影響を受けない
//            } else {
//                pActor->_x -= (*((coord*)p1));
//                //setVehicleLeader() されていたら、スクロールの影響を受ける
//                GgafDx::VehicleLeader* pVehicleLeader = pActor->getVehicleLeader();
//                if (pVehicleLeader) {
//                    pVehicleLeader->_x_start_in_loop -= (*((coord*)p1));
//                }
//            }
//        }
    }
}

CommonScene::~CommonScene() {
}
