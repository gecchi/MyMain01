#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


CommonScene::CommonScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "CommonScene";

    //�S�V�[���ɓn���ď펞�g�p�Ȕėp�I�ȃA�N�^�[�ނ�
    //�R�R�ɂ��̃f�|�W�g�������O�쐬����B

    //�ėp�����G�t�F�N�g EffectExplosion001
    {
        _pDP_EffectExplosion001 = NEW GgafActorDepository("DpExplo001");
        EffectExplosion001* pEffectExplosion;
        for (int i = 0; i < 100; i++) { //�X�g�b�N100��
            pEffectExplosion = NEW EffectExplosion001("EffectExplosion001");
            pEffectExplosion->inactivateTreeImmediately(); //�ŏ���\��
            _pDP_EffectExplosion001->addSubLast(pEffectExplosion);
        }
        getDirector()->addSubGroup(_pDP_EffectExplosion001);
    }

    //�A�C�e����
    { //_pDP_MagicPointItem001
        _pDP_MagicPointItem001 = NEW GgafActorDepository("DpMpItem001");
        MagicPointItem001* pMpItem001;
        for (int i = 0; i < 500; i++) { //�X�g�b�N100��
            pMpItem001 = NEW MagicPointItem001("MP001");
            pMpItem001->inactivateTreeImmediately(); //�ŏ���\��
            _pDP_MagicPointItem001->addSubLast(pMpItem001);
        }
        getDirector()->addSubGroup(_pDP_MagicPointItem001);
    }

    //�A�C�e����
    { //_pDP_MagicPointItem002
        _pDP_MagicPointItem002 = NEW GgafActorDepository("DpMpItem002");
        MagicPointItem002* pMpItem002;
        for (int i = 0; i < 10; i++) { //�X�g�b�N100��
            pMpItem002 = NEW MagicPointItem002("MP002");
            pMpItem002->inactivateTreeImmediately(); //�ŏ���\��
            _pDP_MagicPointItem002->addSubLast(pMpItem002);
        }
        getDirector()->addSubGroup(_pDP_MagicPointItem002);
    }

    { //Effect EffectTurbo002 �^�[�{����
        _pDepo_EffectTurbo002 = NEW GgafActorDepository("RotExplo002");
        EffectTurbo002* pEffectTurbo;
        for (int i = 0; i < 10; i++) { //�X�g�b�N100��
            pEffectTurbo = NEW EffectTurbo002("EffectTurbo002");
            pEffectTurbo->inactivateTreeImmediately(); //�ŏ���\��
            _pDepo_EffectTurbo002->addSubLast(pEffectTurbo);
        }
        getDirector()->addSubGroup(_pDepo_EffectTurbo002);
    }

    //    { //EnemyShot001
    //        _pDepo_EnemyShots001 = NEW GgafActorDepository("TAMAS001");
    //        EnemyCeresShot001* pEnemyShot;
    //        for (int i = 0; i < 36*7; i++) { //�X�g�b�N256��
    //            pEnemyShot = NEW EnemyCeresShot001("EnemyCeresShot001");
    //            pEnemyShot->inactivateTreeImmediately(); //�ŏ���\��
    //            _pDepo_EnemyShots001->addSubLast(pEnemyShot);
    //        }
    //        getDirector()->addSubGroup(_pDepo_EnemyShots001);
    //    }



    //    { //Effect EffectExplosion001
    //        _pDepo_EffectExplosion003 = NEW GgafActorDepository("RotExplo003");
    //        EffectExplosion003* pEffectExplosion;
    //        for (int i = 0; i < 50; i++) { //�X�g�b�N100��
    //            pEffectExplosion = NEW EffectExplosion003("EffectExplosion003");
    //            pEffectExplosion->inactivateTreeImmediately(); //�ŏ���\��
    //            _pDepo_EffectExplosion003->addSubLast(pEffectExplosion);
    //        }
    //        getDirector()->addSubGroup(_pDepo_EffectExplosion003);
    //    }

//
//    {
//        _pDepo_LaserChipDepository = NEW GgafActorDepository("LCDD");
//        LaserChipDepository* pLaserChipDepo;
//        EnemyAstraeaLaserChip002* pChip;
//        for (int nLaser = 0; nLaser < 27; nLaser++) {
//            stringstream name;
//            name <<  "LaserChipDepository["<<nLaser<<"]";
//            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
//            for (int nChip = 0; nChip < 50; nChip++) {
//                stringstream name;
//                name <<  "EnemyAstraeaLaserChip002["<<nLaser<<"]["<<nChip<<"]";
//                pChip = NEW EnemyAstraeaLaserChip002(name.str().c_str());
//                pChip->inactivateImmediately();
//                pLaserChipDepo->addSubLast(pChip);
//            }
//            pLaserChipDepo->inactivateImmediately();
//            _pDepo_LaserChipDepository->addSubLast(pLaserChipDepo);
//        }
//        getDirector()->addSubGroup(_pDepo_LaserChipDepository);
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
