#include "stdafx.h"
#include "CommonScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CommonScene::CommonScene(const char* prm_name) : DefaultScene(prm_name),

P_COMMON_DEPO(EffectExplosion001) (NEW GgafActorDepository("CommonDepo_Explosion001") ),
P_COMMON_DEPO(EffectExplosion002) ( NEW GgafActorDepository("CommonDepo_Explosion002") ),
P_COMMON_DEPO(EffectExplosion003) ( NEW GgafActorDepository("CommonDepo_Explosion003") ),
P_COMMON_DEPO(EffectExplosion004) ( NEW GgafActorDepository("CommonDepo_Explosion004") ),
P_COMMON_DEPO(MagicPointItem001) ( NEW GgafActorDepository("CommonDepo_MagicPointItem001") ),
P_COMMON_DEPO(MagicPointItem002) ( NEW GgafActorDepository("CommonDepo_MagicPointItem002") ),
P_COMMON_DEPO(MagicPointItem003) ( NEW GgafActorDepository("CommonDepo_MagicPointItem003") ),
P_COMMON_DEPO(EffectTurbo002) ( NEW GgafActorDepository("CommonDepo_EffectTurbo002") ),
P_COMMON_DEPO(EffectEntry001) ( NEW GgafActorDepository("CommonDepo_EffectEntry001") ),
P_COMMON_DEPO(EffectEntry002) ( NEW GgafActorDepository("CommonDepo_EffectEntry002") ),
P_COMMON_DEPO(EffectEntry003) ( NEW GgafActorDepository("CommonDepo_EffectEntry003") ),
P_COMMON_DEPO(SpriteLabelBonus001) ( NEW GgafActorDepository("CommonDepo_SpriteLabelBonus001") ),
P_COMMON_DEPO(Shot004) ( NEW GgafActorDepository("CommonDepo_Shot004") )
{
    _class_name = "CommonScene";

    //�S�V�[���ɓn���ď펞�g�p�Ȕėp�I�ȃA�N�^�[�ނ�
    //�R�R�ɂ��̃f�|�W�g�������O�쐬����B

    //�ėp�����G�t�F�N�g EffectExplosion001
    {
//        P_COMMON_DEPO(EffectExplosion001) = NEW GgafActorDepository("CommonDepo_Explosion001");
        for (int i = 0; i < 300; i++) {
            std::string name = "EffectExplosion001("+XTOS(i)+")";
            P_COMMON_DEPO(EffectExplosion001)->put(NEW EffectExplosion001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectExplosion001));
    }

    //�ėp�����G�t�F�N�g EffectExplosion002
    {
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectExplosion002("+XTOS(i)+")";
            P_COMMON_DEPO(EffectExplosion002)->put(NEW EffectExplosion002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectExplosion002));
    }
    //�ėp�����G�t�F�N�g EffectExplosion003
    {
        for (int i = 0; i < 10; i++) {
            std::string name = "EffectExplosion003("+XTOS(i)+")";
            P_COMMON_DEPO(EffectExplosion003)->put(NEW EffectExplosion003(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectExplosion003));
    }

    //�ėp�����G�t�F�N�g�� EffectExplosion004
    {
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectExplosion004("+XTOS(i)+")";
            P_COMMON_DEPO(EffectExplosion004)->put(NEW EffectExplosion004(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectExplosion004));
    }

    //�A�C�e����
    { //P_COMMON_DEPO(MagicPointItem001)
        for (int i = 0; i < 400; i++) {
            std::string name = "MagicPointItem001("+XTOS(i)+")";
            P_COMMON_DEPO(MagicPointItem001)->put(NEW MagicPointItem001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(MagicPointItem001));
    }

    //�A�C�e����
    { //P_COMMON_DEPO(MagicPointItem002)
        for (int i = 0; i < 30; i++) {
            std::string name = "MagicPointItem002("+XTOS(i)+")";
            P_COMMON_DEPO(MagicPointItem002)->put(NEW MagicPointItem002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(MagicPointItem002));
    }

    //�A�C�e����
    { //P_COMMON_DEPO(MagicPointItem003)
        for (int i = 0; i < 10; i++) {
            std::string name = "MagicPointItem003("+XTOS(i)+")";
            P_COMMON_DEPO(MagicPointItem003)->put(NEW MagicPointItem003(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(MagicPointItem003));
    }

    { //Effect EffectTurbo002 �^�[�{����
        for (int i = 0; i < 10; i++) {
            std::string name = "EffectTurbo002("+XTOS(i)+")";
            P_COMMON_DEPO(EffectTurbo002)->put(NEW EffectTurbo002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectTurbo002));
    }


    //�ėp�o���G�t�F�N�g EffectEntry001
    {
        for (int i = 0; i < 200; i++) {
            std::string name = "EffectEntry001("+XTOS(i)+")";
            P_COMMON_DEPO(EffectEntry001)->put(NEW EffectEntry001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectEntry001));
    }

    //�ėp�o���G�t�F�N�g EffectEntry002
    {
        for (int i = 0; i < 30; i++) {
            std::string name = "EffectEntry002("+XTOS(i)+")";
            P_COMMON_DEPO(EffectEntry002)->put(NEW EffectEntry002(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectEntry002));
    }
    //�ėp�o���G�t�F�N�g EffectEntry003
    {
        for (int i = 0; i < 30; i++) {
            std::string name = "EffectEntry003("+XTOS(i)+")";
            P_COMMON_DEPO(EffectEntry003)->put(NEW EffectEntry003(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(EffectEntry003));
    }

    //�{�[�i�X�|�C���g�\���G�t�F�N�g
    {
        for (int i = 0; i < 40; i++) {
            std::string name = "SpriteLabelBonus001("+XTOS(i)+")";
            P_COMMON_DEPO(SpriteLabelBonus001)->put(NEW SpriteLabelBonus001(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(SpriteLabelBonus001));
    }

    //�ėp�V���b�g
    {
        for (int i = 0; i < 800; i++) {
            std::string name = "Shot004("+XTOS(i)+")";
            P_COMMON_DEPO(Shot004)->put(NEW Shot004(name.c_str()));
        }
        getSceneDirector()->addSubGroup(P_COMMON_DEPO(Shot004));
    }


    //    { //EnemyShot001
    //        pDepo_EnemyShots001_ = NEW GgafActorDepository("TAMAS001");
    //        EnemyEresShot001* pEnemyShot;
    //        for (int i = 0; i < 36*7; i++) { //�X�g�b�N256��
    //            pEnemyShot = NEW EnemyEresShot001("EnemyEresShot001");
    //            pEnemyShot->inactivateTreeImmed(); //�ŏ���\��
    //            pDepo_EnemyShots001_->addSubLast(pEnemyShot);
    //        }
    //        getSceneDirector()->addSubGroup(pDepo_EnemyShots001_);
    //    }



    //    { //Effect EffectExplosion001
    //        P_COMMON_DEPO(EffectExplosion003) = NEW GgafActorDepository("RotExplo003");
    //        EffectExplosion003* pEffectExplosion;
    //        for (int i = 0; i < 50; i++) { //�X�g�b�N100��
    //            pEffectExplosion = NEW EffectExplosion003("EffectExplosion003");
    //            pEffectExplosion->inactivateTreeImmed(); //�ŏ���\��
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
    //�X�N���[������
    setScrollingFunction(nullptr);
    setScrollSpeed(0);

    fadeinScene(0);
}

void CommonScene::processBehavior() {

}

CommonScene::~CommonScene() {
}
