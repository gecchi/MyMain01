#include "stdafx.h"
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
        pDepo_EffectExplosion001_ = NEW GgafActorDepository("CommonDepo_Explo001");
        for (int i = 0; i < 300; i++) {
            std::string name = "EffectExplosion001("+XTOS(i)+")";
            pDepo_EffectExplosion001_->addSubLast(NEW EffectExplosion001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_EffectExplosion001_);
    }

    //汎用爆発エフェクト EffectExplosion002
    {
        pDepo_EffectExplosion002_ = NEW GgafActorDepository("CommonDepo_Explo002");
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectExplosion002("+XTOS(i)+")";
            pDepo_EffectExplosion002_->addSubLast(NEW EffectExplosion002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_EffectExplosion002_);
    }
    //汎用爆発エフェクト EffectExplosion003
    {
        pDepo_EffectExplosion003_ = NEW GgafActorDepository("CommonDepo_Explo003");
        for (int i = 0; i < 10; i++) {
            std::string name = "EffectExplosion003("+XTOS(i)+")";
            pDepo_EffectExplosion003_->addSubLast(NEW EffectExplosion003(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_EffectExplosion003_);
    }

    //汎用爆発エフェクト大 EffectExplosion004
    {
        pDepo_EffectExplosion004_ = NEW GgafActorDepository("CommonDepo_Explo004");
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectExplosion004("+XTOS(i)+")";
            pDepo_EffectExplosion004_->addSubLast(NEW EffectExplosion004(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_EffectExplosion004_);
    }

    //アイテム小
    { //pDepo_MagicPointItem001_
        pDepo_MagicPointItem001_ = NEW GgafActorDepository("CommonDepo_MpItem001");
        for (int i = 0; i < 300; i++) {
            std::string name = "MagicPointItem001("+XTOS(i)+")";
            pDepo_MagicPointItem001_->addSubLast(NEW MagicPointItem001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_MagicPointItem001_);
    }

    //アイテム中
    { //pDepo_MagicPointItem002_
        pDepo_MagicPointItem002_ = NEW GgafActorDepository("CommonDepo_MpItem002");
        for (int i = 0; i < 10; i++) {
            std::string name = "MagicPointItem002("+XTOS(i)+")";
            pDepo_MagicPointItem002_->addSubLast(NEW MagicPointItem002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_MagicPointItem002_);
    }

    { //Effect EffectTurbo002 ターボ噴射
        pDepo_EffectTurbo002_ = NEW GgafActorDepository("RotExplo002");
        for (int i = 0; i < 10; i++) {
            std::string name = "EffectTurbo002("+XTOS(i)+")";
            pDepo_EffectTurbo002_->addSubLast(NEW EffectTurbo002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_EffectTurbo002_);
    }


    //汎用出現エフェクト EffectEntry001
    {
        pDepo_EffectEntry001_ = NEW GgafActorDepository("CommonDepo_Explo001");
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectEntry001("+XTOS(i)+")";
            pDepo_EffectEntry001_->addSubLast(NEW EffectEntry001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_EffectEntry001_);
    }

    //汎用出現エフェクト EffectEntry002
    {
        pDepo_EffectEntry002_ = NEW GgafActorDepository("CommonDepo_Explo002");
        for (int i = 0; i < 30; i++) {
            std::string name = "EffectEntry002("+XTOS(i)+")";
            pDepo_EffectEntry002_->addSubLast(NEW EffectEntry002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_EffectEntry002_);
    }
    //汎用出現エフェクト EffectEntry003
    {
        pDepo_EffectEntry003_ = NEW GgafActorDepository("CommonDepo_Explo003");
        for (int i = 0; i < 30; i++) {
            std::string name = "EffectEntry003("+XTOS(i)+")";
            pDepo_EffectEntry003_->addSubLast(NEW EffectEntry003(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_EffectEntry003_);
    }

    //ボーナスポイント表示エフェクト
    {
        pDepo_SpriteLabelBonus001_ = NEW GgafActorDepository("CommonDepo_FormationDestroyedEffect001");
        for (int i = 0; i < 10; i++) {
            std::string name = "SpriteLabelBonus001("+XTOS(i)+")";
            pDepo_SpriteLabelBonus001_->addSubLast(NEW SpriteLabelBonus001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_SpriteLabelBonus001_);
    }

    //汎用ショット
    {
        pDepo_Shot004_ = NEW GgafActorDepository("CommonDepo_Shot004");
        for (int i = 0; i < 1000; i++) {
            std::string name = "Shot004("+XTOS(i)+")";
            pDepo_Shot004_->addSubLast(NEW Shot004(name.c_str()));
        }
        getSceneDirector()->addSubGroup(pDepo_Shot004_);
    }


    //    { //EnemyShot001
    //        pDepo_EnemyShots001_ = NEW GgafActorDepository("TAMAS001");
    //        EnemyCeresShot001* pEnemyShot;
    //        for (int i = 0; i < 36*7; i++) { //ストック256個
    //            pEnemyShot = NEW EnemyCeresShot001("EnemyCeresShot001");
    //            pEnemyShot->inactivateTreeImmed(); //最初非表示
    //            pDepo_EnemyShots001_->addSubLast(pEnemyShot);
    //        }
    //        getSceneDirector()->addSubGroup(pDepo_EnemyShots001_);
    //    }



    //    { //Effect EffectExplosion001
    //        pDepo_EffectExplosion003_ = NEW GgafActorDepository("RotExplo003");
    //        EffectExplosion003* pEffectExplosion;
    //        for (int i = 0; i < 50; i++) { //ストック100個
    //            pEffectExplosion = NEW EffectExplosion003("EffectExplosion003");
    //            pEffectExplosion->inactivateTreeImmed(); //最初非表示
    //            pDepo_EffectExplosion003_->addSubLast(pEffectExplosion);
    //        }
    //        getSceneDirector()->addSubGroup(pDepo_EffectExplosion003_);
    //    }

//
//    {
//        pDepo_LaserChipDepository_ = NEW GgafActorDepository("LCDD");
//        LaserChipDepository* pLaserChipDepo;
//        EnemyAstraeaLaserChip002* pChip;
//        for (int nLaser = 0; nLaser < 27; nLaser++) {
//            std::stringstream name;
//            name <<  "LaserChipDepository["<<nLaser<<"]";
//            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
//            for (int nChip = 0; nChip < 50; nChip++) {
//                std::stringstream name;
//                name <<  "EnemyAstraeaLaserChip002["<<nLaser<<"]["<<nChip<<"]";
//                pChip = NEW EnemyAstraeaLaserChip002(name.str().c_str());
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
