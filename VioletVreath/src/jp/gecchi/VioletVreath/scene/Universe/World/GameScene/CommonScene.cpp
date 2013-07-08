#include "stdafx.h"
#include "CommonScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CommonScene::CommonScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "CommonScene";

    //全シーンに渡って常時使用な汎用的なアクター類は
    //ココにそのデポジトリを事前作成する。

    //汎用爆発エフェクト EffectExplosion001
    {
        P_COMMON_DEPO(EffectExplosion001) = NEW GgafActorDepository("CommonDepo_Explosion001");
        for (int i = 0; i < 300; i++) {
            std::string name = "EffectExplosion001("+XTOS(i)+")";
            P_COMMON_DEPO(EffectExplosion001)->addSubLast(NEW EffectExplosion001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectExplosion001));
    }

    //汎用爆発エフェクト EffectExplosion002
    {
        P_COMMON_DEPO(EffectExplosion002) = NEW GgafActorDepository("CommonDepo_Explosion002");
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectExplosion002("+XTOS(i)+")";
            P_COMMON_DEPO(EffectExplosion002)->addSubLast(NEW EffectExplosion002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectExplosion002));
    }
    //汎用爆発エフェクト EffectExplosion003
    {
        P_COMMON_DEPO(EffectExplosion003) = NEW GgafActorDepository("CommonDepo_Explosion003");
        for (int i = 0; i < 10; i++) {
            std::string name = "EffectExplosion003("+XTOS(i)+")";
            P_COMMON_DEPO(EffectExplosion003)->addSubLast(NEW EffectExplosion003(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectExplosion003));
    }

    //汎用爆発エフェクト大 EffectExplosion004
    {
        P_COMMON_DEPO(EffectExplosion004) = NEW GgafActorDepository("CommonDepo_Explosion004");
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectExplosion004("+XTOS(i)+")";
            P_COMMON_DEPO(EffectExplosion004)->addSubLast(NEW EffectExplosion004(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectExplosion004));
    }

    //アイテム小
    { //P_COMMON_DEPO(MagicPointItem001)
        P_COMMON_DEPO(MagicPointItem001) = NEW GgafActorDepository("CommonDepo_MagicPointItem001");
        for (int i = 0; i < 300; i++) {
            std::string name = "MagicPointItem001("+XTOS(i)+")";
            P_COMMON_DEPO(MagicPointItem001)->addSubLast(NEW MagicPointItem001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(MagicPointItem001));
    }

    //アイテム中
    { //P_COMMON_DEPO(MagicPointItem002)
        P_COMMON_DEPO(MagicPointItem002) = NEW GgafActorDepository("CommonDepo_MagicPointItem002");
        for (int i = 0; i < 10; i++) {
            std::string name = "MagicPointItem002("+XTOS(i)+")";
            P_COMMON_DEPO(MagicPointItem002)->addSubLast(NEW MagicPointItem002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(MagicPointItem002));
    }

    { //Effect EffectTurbo002 ターボ噴射
        P_COMMON_DEPO(EffectTurbo002) = NEW GgafActorDepository("CommonDepo_EffectTurbo002");
        for (int i = 0; i < 10; i++) {
            std::string name = "EffectTurbo002("+XTOS(i)+")";
            P_COMMON_DEPO(EffectTurbo002)->addSubLast(NEW EffectTurbo002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectTurbo002));
    }


    //汎用出現エフェクト EffectEntry001
    {
        P_COMMON_DEPO(EffectEntry001) = NEW GgafActorDepository("CommonDepo_EffectEntry001");
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectEntry001("+XTOS(i)+")";
            P_COMMON_DEPO(EffectEntry001)->addSubLast(NEW EffectEntry001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectEntry001));
    }

    //汎用出現エフェクト EffectEntry002
    {
        P_COMMON_DEPO(EffectEntry002) = NEW GgafActorDepository("CommonDepo_EffectEntry002");
        for (int i = 0; i < 30; i++) {
            std::string name = "EffectEntry002("+XTOS(i)+")";
            P_COMMON_DEPO(EffectEntry002)->addSubLast(NEW EffectEntry002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectEntry002));
    }
    //汎用出現エフェクト EffectEntry003
    {
        P_COMMON_DEPO(EffectEntry003) = NEW GgafActorDepository("CommonDepo_EffectEntry003");
        for (int i = 0; i < 30; i++) {
            std::string name = "EffectEntry003("+XTOS(i)+")";
            P_COMMON_DEPO(EffectEntry003)->addSubLast(NEW EffectEntry003(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectEntry003));
    }

    //ボーナスポイント表示エフェクト
    {
        P_COMMON_DEPO(SpriteLabelBonus001) = NEW GgafActorDepository("CommonDepo_SpriteLabelBonus001");
        for (int i = 0; i < 10; i++) {
            std::string name = "SpriteLabelBonus001("+XTOS(i)+")";
            P_COMMON_DEPO(SpriteLabelBonus001)->addSubLast(NEW SpriteLabelBonus001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(SpriteLabelBonus001));
    }

    //汎用ショット
    {
        P_COMMON_DEPO(Shot004) = NEW GgafActorDepository("CommonDepo_Shot004");
        for (int i = 0; i < 1000; i++) {
            std::string name = "Shot004("+XTOS(i)+")";
            P_COMMON_DEPO(Shot004)->addSubLast(NEW Shot004(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(Shot004));
    }


    //    { //EnemyShot001
    //        pDepo_EnemyShots001_ = NEW GgafActorDepository("TAMAS001");
    //        EnemyEresShot001* pEnemyShot;
    //        for (int i = 0; i < 36*7; i++) { //ストック256個
    //            pEnemyShot = NEW EnemyEresShot001("EnemyEresShot001");
    //            pEnemyShot->inactivateTreeImmed(); //最初非表示
    //            pDepo_EnemyShots001_->addSubLast(pEnemyShot);
    //        }
    //        getSceneDirector()->addSubGroup(pDepo_EnemyShots001_);
    //    }



    //    { //Effect EffectExplosion001
    //        P_COMMON_DEPO(EffectExplosion003) = NEW GgafActorDepository("RotExplo003");
    //        EffectExplosion003* pEffectExplosion;
    //        for (int i = 0; i < 50; i++) { //ストック100個
    //            pEffectExplosion = NEW EffectExplosion003("EffectExplosion003");
    //            pEffectExplosion->inactivateTreeImmed(); //最初非表示
    //            P_COMMON_DEPO(EffectExplosion003)->addSubLast(pEffectExplosion);
    //        }
    //        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectExplosion003));
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
//                pChip->inactivateImmed();
//                pLaserChipDepo->addSubLast(pChip);
//            }
//            pLaserChipDepo->inactivateImmed();
//            pDepo_LaserChipDepository_->addSubLast(pLaserChipDepo);
//        }
//        getSceneDirector()->addSubGroup(pDepo_LaserChipDepository_);
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
