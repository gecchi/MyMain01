#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CommonScene::CommonScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "CommonScene";

    //�S�V�[���ɓn���ď펞�g�p�Ȕėp�I�ȃA�N�^�[�ނ�
    //�R�R�ɂ��̃f�|�W�g�������O�쐬����B

    //�ėp�����G�t�F�N�g EffectExplosion001
    {
        pDepo_EffectExplosion001_ = NEW GgafActorDepository("CommonDepo_Explo001");
        for (int i = 0; i < 300; i++) {
            std::string name = "EffectExplosion001("+ITOS(i)+")";
            pDepo_EffectExplosion001_->addSubLast(NEW EffectExplosion001(name.c_str()));
        }
        getDirector()->addSubGroup(pDepo_EffectExplosion001_);
    }

    //�ėp�����G�t�F�N�g EffectExplosion002
    {
        pDepo_EffectExplosion002_ = NEW GgafActorDepository("CommonDepo_Explo002");
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectExplosion002("+ITOS(i)+")";
            pDepo_EffectExplosion002_->addSubLast(NEW EffectExplosion002(name.c_str()));
        }
        getDirector()->addSubGroup(pDepo_EffectExplosion002_);
    }
    //�ėp�����G�t�F�N�g EffectExplosion003
    {
        pDepo_EffectExplosion003_ = NEW GgafActorDepository("CommonDepo_Explo003");
        for (int i = 0; i < 10; i++) {
            std::string name = "EffectExplosion003("+ITOS(i)+")";
            pDepo_EffectExplosion003_->addSubLast(NEW EffectExplosion003(name.c_str()));
        }
        getDirector()->addSubGroup(pDepo_EffectExplosion003_);
    }

    //�A�C�e����
    { //pDepo_MagicPointItem001_
        pDepo_MagicPointItem001_ = NEW GgafActorDepository("CommonDepo_MpItem001");
        for (int i = 0; i < 300; i++) {
            std::string name = "MagicPointItem001("+ITOS(i)+")";
            pDepo_MagicPointItem001_->addSubLast(NEW MagicPointItem001(name.c_str()));
        }
        getDirector()->addSubGroup(pDepo_MagicPointItem001_);
    }

    //�A�C�e����
    { //pDepo_MagicPointItem002_
        pDepo_MagicPointItem002_ = NEW GgafActorDepository("CommonDepo_MpItem002");
        for (int i = 0; i < 10; i++) {
            std::string name = "MagicPointItem002("+ITOS(i)+")";
            pDepo_MagicPointItem002_->addSubLast(NEW MagicPointItem002(name.c_str()));
        }
        getDirector()->addSubGroup(pDepo_MagicPointItem002_);
    }

    { //Effect EffectTurbo002 �^�[�{����
        pDepo_EffectTurbo002_ = NEW GgafActorDepository("RotExplo002");
        for (int i = 0; i < 10; i++) {
            std::string name = "EffectTurbo002("+ITOS(i)+")";
            pDepo_EffectTurbo002_->addSubLast(NEW EffectTurbo002(name.c_str()));
        }
        getDirector()->addSubGroup(pDepo_EffectTurbo002_);
    }


    //�ėp�o���G�t�F�N�g EffectEntry001
    {
        pDepo_EffectEntry001_ = NEW GgafActorDepository("CommonDepo_Explo001");
        for (int i = 0; i < 100; i++) {
            std::string name = "EffectEntry001("+ITOS(i)+")";
            pDepo_EffectEntry001_->addSubLast(NEW EffectEntry001(name.c_str()));
        }
        getDirector()->addSubGroup(pDepo_EffectEntry001_);
    }

    //�ėp�o���G�t�F�N�g EffectEntry002
    {
        pDepo_EffectEntry002_ = NEW GgafActorDepository("CommonDepo_Explo002");
        for (int i = 0; i < 30; i++) {
            std::string name = "EffectEntry002("+ITOS(i)+")";
            pDepo_EffectEntry002_->addSubLast(NEW EffectEntry002(name.c_str()));
        }
        getDirector()->addSubGroup(pDepo_EffectEntry002_);
    }
    //�ėp�o���G�t�F�N�g EffectEntry003
    {
        pDepo_EffectEntry003_ = NEW GgafActorDepository("CommonDepo_Explo003");
        for (int i = 0; i < 30; i++) {
            std::string name = "EffectEntry003("+ITOS(i)+")";
            pDepo_EffectEntry003_->addSubLast(NEW EffectEntry003(name.c_str()));
        }
        getDirector()->addSubGroup(pDepo_EffectEntry003_);
    }

    //    { //EnemyShot001
    //        pDepo_EnemyShots001_ = NEW GgafActorDepository("TAMAS001");
    //        EnemyCeresShot001* pEnemyShot;
    //        for (int i = 0; i < 36*7; i++) { //�X�g�b�N256��
    //            pEnemyShot = NEW EnemyCeresShot001("EnemyCeresShot001");
    //            pEnemyShot->inactivateTreeImmed(); //�ŏ���\��
    //            pDepo_EnemyShots001_->addSubLast(pEnemyShot);
    //        }
    //        getDirector()->addSubGroup(pDepo_EnemyShots001_);
    //    }



    //    { //Effect EffectExplosion001
    //        pDepo_EffectExplosion003_ = NEW GgafActorDepository("RotExplo003");
    //        EffectExplosion003* pEffectExplosion;
    //        for (int i = 0; i < 50; i++) { //�X�g�b�N100��
    //            pEffectExplosion = NEW EffectExplosion003("EffectExplosion003");
    //            pEffectExplosion->inactivateTreeImmed(); //�ŏ���\��
    //            pDepo_EffectExplosion003_->addSubLast(pEffectExplosion);
    //        }
    //        getDirector()->addSubGroup(pDepo_EffectExplosion003_);
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
//        getDirector()->addSubGroup(pDepo_LaserChipDepository_);
//    }
}

void CommonScene::initialize() {
}
void CommonScene::onReset() {
    fadeinScene(0);
}

void CommonScene::processBehavior() {

}

CommonScene::~CommonScene() {
}
