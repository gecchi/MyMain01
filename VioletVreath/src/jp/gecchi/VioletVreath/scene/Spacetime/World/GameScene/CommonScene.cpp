#include "CommonScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CommonScene::CommonScene(const char* prm_name) : DefaultScene(prm_name),

pCOMMON_DEPO(EffectExplosion001) (NEW GgafActorDepository("CommonDepo_Explosion001") ),
pCOMMON_DEPO(EffectExplosion002) ( NEW GgafActorDepository("CommonDepo_Explosion002") ),
pCOMMON_DEPO(EffectExplosion003) ( NEW GgafActorDepository("CommonDepo_Explosion003") ),
pCOMMON_DEPO(EffectExplosion004) ( NEW GgafActorDepository("CommonDepo_Explosion004") ),
pCOMMON_DEPO(MagicPointItem001) ( NEW GgafActorDepository("CommonDepo_MagicPointItem001") ),
pCOMMON_DEPO(MagicPointItem002) ( NEW GgafActorDepository("CommonDepo_MagicPointItem002") ),
pCOMMON_DEPO(MagicPointItem003) ( NEW GgafActorDepository("CommonDepo_MagicPointItem003") ),
pCOMMON_DEPO(EffectTurbo002) ( NEW GgafActorDepository("CommonDepo_EffectTurbo002") ),
pCOMMON_DEPO(EffectBlink001) ( NEW GgafActorDepository("CommonDepo_EffectBlink001") ),
pCOMMON_DEPO(EffectBlink002) ( NEW GgafActorDepository("CommonDepo_EffectBlink002") ),
pCOMMON_DEPO(EffectBlink003) ( NEW GgafActorDepository("CommonDepo_EffectBlink003") ),
pCOMMON_DEPO(SpriteLabelBonus001) ( NEW GgafActorDepository("CommonDepo_SpriteLabelBonus001") ),
pCOMMON_DEPO(Shot004) ( NEW GgafActorDepository("CommonDepo_Shot004") ),
pStore_EnemyWateringLaser001_(NEW GgafActorDepositoryStore("CommonDepoStore_EnemyWateringLaser001") ),
pStore_EnemyStraightLaser001_(NEW GgafActorDepositoryStore("CommonDepoStore_EnemyStraightLaser001") )

{
    _class_name = "CommonScene";

    //全シーンに渡って常時使用な汎用的なアクター類は
    //ココにそのデポジトリを事前作成する。

    //汎用爆発エフェクト EffectExplosion001
    {
        for (int i = 0; i < 300; i++) {
            std::string name = "EffectExplosion001("+XTOS(i)+")";
            pCOMMON_DEPO(EffectExplosion001)->put(NEW EffectExplosion001(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(EffectExplosion001));
    }

    //汎用爆発エフェクト EffectExplosion002
    {
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectExplosion002("+XTOS(i)+")";
            pCOMMON_DEPO(EffectExplosion002)->put(NEW EffectExplosion002(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(EffectExplosion002));
    }
    //汎用爆発エフェクト EffectExplosion003
    {
        for (int i = 0; i < 10; i++) {
            std::string name = "EffectExplosion003("+XTOS(i)+")";
            pCOMMON_DEPO(EffectExplosion003)->put(NEW EffectExplosion003(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(EffectExplosion003));
    }

    //汎用爆発エフェクト大 EffectExplosion004
    {
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectExplosion004("+XTOS(i)+")";
            pCOMMON_DEPO(EffectExplosion004)->put(NEW EffectExplosion004(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(EffectExplosion004));
    }

    //アイテム小
    { //pCOMMON_DEPO(MagicPointItem001)
        for (int i = 0; i < 400; i++) {
            std::string name = "MagicPointItem001("+XTOS(i)+")";
            pCOMMON_DEPO(MagicPointItem001)->put(NEW MagicPointItem001(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(MagicPointItem001));
    }

    //アイテム中
    { //pCOMMON_DEPO(MagicPointItem002)
        for (int i = 0; i < 30; i++) {
            std::string name = "MagicPointItem002("+XTOS(i)+")";
            pCOMMON_DEPO(MagicPointItem002)->put(NEW MagicPointItem002(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(MagicPointItem002));
    }

    //アイテム大
    { //pCOMMON_DEPO(MagicPointItem003)
        for (int i = 0; i < 10; i++) {
            std::string name = "MagicPointItem003("+XTOS(i)+")";
            pCOMMON_DEPO(MagicPointItem003)->put(NEW MagicPointItem003(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(MagicPointItem003));
    }

    { //Effect EffectTurbo002 ターボ噴射
        for (int i = 0; i < 10; i++) {
            std::string name = "EffectTurbo002("+XTOS(i)+")";
            pCOMMON_DEPO(EffectTurbo002)->put(NEW EffectTurbo002(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(EffectTurbo002));
    }

    //汎用出現エフェクト EffectBlink001
    {
        for (int i = 0; i < 200; i++) {
            std::string name = "EffectBlink001("+XTOS(i)+")";
            pCOMMON_DEPO(EffectBlink001)->put(NEW EffectBlink001(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(EffectBlink001));
    }

    //汎用出現エフェクト EffectBlink002
    {
        for (int i = 0; i < 30; i++) {
            std::string name = "EffectBlink002("+XTOS(i)+")";
            pCOMMON_DEPO(EffectBlink002)->put(NEW EffectBlink002(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(EffectBlink002));
    }

    //汎用出現エフェクト EffectBlink003
    {
        for (int i = 0; i < 30; i++) {
            std::string name = "EffectBlink003("+XTOS(i)+")";
            pCOMMON_DEPO(EffectBlink003)->put(NEW EffectBlink003(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(EffectBlink003));
    }

    //ボーナスポイント表示エフェクト
    {
        for (int i = 0; i < 40; i++) {
            std::string name = "SpriteLabelBonus001("+XTOS(i)+")";
            pCOMMON_DEPO(SpriteLabelBonus001)->put(NEW SpriteLabelBonus001(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(SpriteLabelBonus001));
    }

    //汎用ショット
    {
        for (int i = 0; i < 500; i++) {
            std::string name = "Shot004("+XTOS(i)+")";
            pCOMMON_DEPO(Shot004)->put(NEW Shot004(name.c_str()));
        }
        bringDirector()->addSubGroup(pCOMMON_DEPO(Shot004));
    }

    //汎用Wateringレーザー
    {
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
        bringDirector()->addSubGroup(pStore_EnemyWateringLaser001_);
    }
    //汎用ストレートレーザー
    {
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
        bringDirector()->addSubGroup(pStore_EnemyStraightLaser001_);
    }
    //    { //EnemyShot001
    //        pDepo_EnemyShots001_ = NEW GgafActorDepository("TAMAS001");
    //        EnemyEresShot001* pEnemyShot;
    //        for (int i = 0; i < 36*7; i++) { //ストック256個
    //            pEnemyShot = NEW EnemyEresShot001("EnemyEresShot001");
    //            pEnemyShot->inactivateTreeImmed(); //最初非表示
    //            pDepo_EnemyShots001_->addSubLast(pEnemyShot);
    //        }
    //        bringDirector()->addSubGroup(pDepo_EnemyShots001_);
    //    }



    //    { //Effect EffectExplosion001
    //        pCOMMON_DEPO(EffectExplosion003) = NEW GgafActorDepository("RotExplo003");
    //        EffectExplosion003* pEffectExplosion;
    //        for (int i = 0; i < 50; i++) { //ストック100個
    //            pEffectExplosion = NEW EffectExplosion003("EffectExplosion003");
    //            pEffectExplosion->inactivateTreeImmed(); //最初非表示
    //            pCOMMON_DEPO(EffectExplosion003)->addSubLast(pEffectExplosion);
    //        }
    //        bringDirector()->addSubGroup(pCOMMON_DEPO(EffectExplosion003));
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
//        bringDirector()->addSubGroup(pDepo_LaserChipDepository_);
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

CommonScene::~CommonScene() {
}
