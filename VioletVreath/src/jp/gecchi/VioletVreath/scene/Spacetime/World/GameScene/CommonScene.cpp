#include "CommonScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define REGISTER(TYPE, NUM)   do { \
        pCOMMON_DEPO(TYPE) = NEW GgafActorDepository("CommonDepo_" #TYPE); \
        pCOMMON_DEPO(TYPE)->put<TYPE>(NUM); \
        bringSceneMediator()->addSubGroup(pCOMMON_DEPO(TYPE)); \
}while(0)

CommonScene::CommonScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "CommonScene";

    //全シーンに渡って常時使用な汎用的なアクター類は
    //ココにそのデポジトリを事前作成する。
    //汎用爆発エフェクト
    REGISTER(EffectExplosion001, 300);
    //汎用爆発エフェクト
    REGISTER(EffectExplosion002, 100);
    //汎用爆発エフェクト
    REGISTER(EffectExplosion003, 10);
    //汎用爆発エフェクト大
    REGISTER(EffectExplosion004, 100);
    //アイテム小
    REGISTER(MagicPointItem001, 400);
    //アイテム中
    REGISTER(MagicPointItem002, 30);
    //アイテム大
    REGISTER(MagicPointItem003, 10);
    //Effect EffectTurbo002 ターボ噴射
    REGISTER(EffectTurbo002, 10);
    //汎用出現エフェクト EffectBlink001
    REGISTER(EffectBlink001, 200);
    //汎用出現エフェクト EffectBlink002
    REGISTER(EffectBlink002, 30);
    //汎用出現エフェクト EffectBlink003
    REGISTER(EffectBlink003, 30);
    //ボーナスポイント表示エフェクト
    REGISTER(SpriteLabelBonus001, 30);
    //汎用ショット
    REGISTER(Shot004, 30);
    //汎用Wateringレーザー
    {
        pStore_EnemyWateringLaser001_ = NEW GgafActorDepositoryStore("CommonDepoStore_EnemyWateringLaser001");
        LaserChipDepository* pLaserChipDepo;
        for (int laser_no = 0; laser_no < 30; laser_no++) { //セット本数
            std::string name_depo = "LaserChipDepo["+XTOS(laser_no)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name_depo.c_str());
            for (int chip_no = 0; chip_no < 40; chip_no++) { //１本の長さ
                std::string name_chip = "EnemyWateringLaserChip001["+XTOS(laser_no)+"]["+XTOS(chip_no)+"]";
                pLaserChipDepo->put(NEW EnemyWateringLaserChip001(name_chip.c_str()));
            }
            pStore_EnemyWateringLaser001_->put(pLaserChipDepo);
        }
        bringSceneMediator()->addSubGroup(pStore_EnemyWateringLaser001_);
    }
    //汎用ストレートレーザー
    {
        pStore_EnemyStraightLaser001_ = NEW GgafActorDepositoryStore("CommonDepoStore_EnemyStraightLaser001");
        LaserChipDepository* pLaserChipDepo;
        for (int laser_no = 0; laser_no < 8; laser_no++) { //セット本数
            std::string name_depo = "LaserChipDepo["+XTOS(laser_no)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name_depo.c_str());
            for (int chip_no = 0; chip_no < 40; chip_no++) { //１本の長さ
                std::string name_chip = "EnemyStraightLaserChip001["+XTOS(laser_no)+"]["+XTOS(chip_no)+"]";
                pLaserChipDepo->put(NEW EnemyStraightLaserChip001(name_chip.c_str()));
            }
            pStore_EnemyStraightLaser001_->put(pLaserChipDepo);
        }
        bringSceneMediator()->addSubGroup(pStore_EnemyStraightLaser001_);
    }
    //    { //EnemyShot001
    //        pDepo_EnemyShots001_ = NEW GgafActorDepository("TAMAS001");
    //        EnemyEresShot001* pEnemyShot;
    //        for (int i = 0; i < 36*7; i++) { //ストック256個
    //            pEnemyShot = NEW EnemyEresShot001("EnemyEresShot001");
    //            pEnemyShot->inactivateTreeImmed(); //最初非表示
    //            pDepo_EnemyShots001_->addSubLast(pEnemyShot);
    //        }
    //        bringSceneMediator()->addSubGroup(pDepo_EnemyShots001_);
    //    }



    //    { //Effect EffectExplosion001
    //        pCOMMON_DEPO(EffectExplosion003) = NEW GgafActorDepository("RotExplo003");
    //        EffectExplosion003* pEffectExplosion;
    //        for (int i = 0; i < 50; i++) { //ストック100個
    //            pEffectExplosion = NEW EffectExplosion003("EffectExplosion003");
    //            pEffectExplosion->inactivateTreeImmed(); //最初非表示
    //            pCOMMON_DEPO(EffectExplosion003)->addSubLast(pEffectExplosion);
    //        }
    //        bringSceneMediator()->addSubGroup(pCOMMON_DEPO(EffectExplosion003));
    //    }

//
//    {
//        pDepo_LaserChipDepository_ = NEW GgafActorDepository("LCDD");
//        LaserChipDepository* pLaserChipDepo;
//        EnemyStraeaLaserChip002* pChip;
//        for (int nLaser = 0; nLaser < 27; nLaser++) {
//            std::stringstream name;
//            name <<  "LaserChipDepository["<<nLaser<<"]";
//            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
//            for (int nChip = 0; nChip < 50; nChip++) {
//                std::stringstream name;
//                name <<  "EnemyStraeaLaserChip002["<<nLaser<<"]["<<nChip<<"]";
//                pChip = NEW EnemyStraeaLaserChip002(name.str().c_str());
//                pChip->inactivate();
//                pLaserChipDepo->addSubLast(pChip);
//            }
//            pLaserChipDepo->inactivate();
//            pDepo_LaserChipDepository_->addSubLast(pLaserChipDepo);
//        }
//        bringSceneMediator()->addSubGroup(pDepo_LaserChipDepository_);
//    }
}

void CommonScene::initialize() {
}
void CommonScene::onReset() {
    //スクロール解除
    setScrollingFunction(nullptr);
    setScrollSpeed(0);

    fadeinScene(0);
}

void CommonScene::processBehavior() {

}

void CommonScene::scrollX(GgafObject* pThat, void* p1, void* p2, void* p3) {
    if (pThat->instanceOf(Obj_GgafDxGeometricActor)) {
        GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)pThat;
        if (!pActor->_was_paused_flg) {
            if (pActor->lookUpKind() & KIND_ITEM) {
                //Itemはスクロールの影響を受けない
            } else {
                pActor->_x -= (*((coord*)p1));
            }
        }
    }
}

CommonScene::~CommonScene() {
}
