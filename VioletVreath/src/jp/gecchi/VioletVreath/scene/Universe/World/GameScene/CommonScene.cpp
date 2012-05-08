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
        pDepo_EffectExplosion001_ = NEW GgafActorDepository("DpExplo001");
        for (int i = 0; i < 700; i++) {
            pDepo_EffectExplosion001_->addSubLast(NEW EffectExplosion001("EffectExplosion001"));
        }
        getDirector()->addSubGroup(pDepo_EffectExplosion001_);
    }

    //�A�C�e����
    { //pDepo_MagicPointItem001_
        pDepo_MagicPointItem001_ = NEW GgafActorDepository("DpMpItem001");
        for (int i = 0; i < 500; i++) {
            pDepo_MagicPointItem001_->addSubLast(NEW MagicPointItem001("MP001"));
        }
        getDirector()->addSubGroup(pDepo_MagicPointItem001_);
    }

    //�A�C�e����
    { //pDepo_MagicPointItem002_
        pDepo_MagicPointItem002_ = NEW GgafActorDepository("DpMpItem002");
        for (int i = 0; i < 10; i++) {
            pDepo_MagicPointItem002_->addSubLast(NEW MagicPointItem002("MP002"));
        }
        getDirector()->addSubGroup(pDepo_MagicPointItem002_);
    }

    { //Effect EffectTurbo002 �^�[�{����
        pDepo_EffectTurbo002_ = NEW GgafActorDepository("RotExplo002");
        for (int i = 0; i < 10; i++) { //�X�g�b�N100��
            pDepo_EffectTurbo002_->addSubLast(NEW EffectTurbo002("EffectTurbo002"));
        }
        getDirector()->addSubGroup(pDepo_EffectTurbo002_);
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
