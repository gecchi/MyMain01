#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CommonScene::CommonScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "CommonScene";

    //�S�V�[���ɓn���ď펞�g�p�Ȕėp�I�ȃA�N�^�[�ނ�
    //�R�R�ɂ��̃X�g�A�[���쐬����B

    //�ėp�����G�t�F�N�g EffectExplosion001
    {
        _pDP_EffectExplosion001 = NEW GgafActorStore("DpExplo001");
        EffectExplosion001* pEffectExplosion;
        for (int i = 0; i < 100; i++) { //�X�g�b�N100��
            pEffectExplosion = NEW EffectExplosion001("EffectExplosion001");
            pEffectExplosion->inactivateTreeImmediately(); //�ŏ���\��
            _pDP_EffectExplosion001->addSubLast(pEffectExplosion);
        }
        getLordActor()->addSubGroup(_pDP_EffectExplosion001);
    }

    //�A�C�e��
    { //_pDP_MagicPointItem001
        _pDP_MagicPointItem001 = NEW GgafActorStore("DpMpItem001");
        MagicPointItem001* pMpItem001;
        for (int i = 0; i < 500; i++) { //�X�g�b�N100��
            pMpItem001 = NEW MagicPointItem001("MP001");
            pMpItem001->inactivateTreeImmediately(); //�ŏ���\��
            _pDP_MagicPointItem001->addSubLast(pMpItem001);
        }
        getLordActor()->addSubGroup(_pDP_MagicPointItem001);
    }

    { //Effect EffectTurbo002 �^�[�{����
        _pStore_EffectTurbo002 = NEW GgafActorStore("RotExplo002");
        EffectTurbo002* pEffectTurbo;
        for (int i = 0; i < 10; i++) { //�X�g�b�N100��
            pEffectTurbo = NEW EffectTurbo002("EffectTurbo002");
            pEffectTurbo->inactivateTreeImmediately(); //�ŏ���\��
            _pStore_EffectTurbo002->addSubLast(pEffectTurbo);
        }
        getLordActor()->addSubGroup(_pStore_EffectTurbo002);
    }

    //    { //EnemyShot001
    //        _pStore_EnemyShots001 = NEW GgafActorStore("TAMAS001");
    //        EnemyCeresShot001* pEnemyShot;
    //        for (int i = 0; i < 36*7; i++) { //�X�g�b�N256��
    //            pEnemyShot = NEW EnemyCeresShot001("EnemyCeresShot001");
    //            pEnemyShot->inactivateTreeImmediately(); //�ŏ���\��
    //            _pStore_EnemyShots001->addSubLast(pEnemyShot);
    //        }
    //        getLordActor()->addSubGroup(_pStore_EnemyShots001);
    //    }



    //    { //Effect EffectExplosion001
    //        _pStore_EffectExplosion003 = NEW GgafActorStore("RotExplo003");
    //        EffectExplosion003* pEffectExplosion;
    //        for (int i = 0; i < 50; i++) { //�X�g�b�N100��
    //            pEffectExplosion = NEW EffectExplosion003("EffectExplosion003");
    //            pEffectExplosion->inactivateTreeImmediately(); //�ŏ���\��
    //            _pStore_EffectExplosion003->addSubLast(pEffectExplosion);
    //        }
    //        getLordActor()->addSubGroup(_pStore_EffectExplosion003);
    //    }

//
//    {
//        _pStore_LaserChipStore = NEW GgafActorStore("LCDD");
//        LaserChipStore* pLaserChipStore;
//        EnemyAstraeaLaserChip002* pChip;
//        for (int nLaser = 0; nLaser < 27; nLaser++) {
//            stringstream name;
//            name <<  "LaserChipStore["<<nLaser<<"]";
//            pLaserChipStore = NEW LaserChipStore(name.str().c_str());
//            for (int nChip = 0; nChip < 50; nChip++) {
//                stringstream name;
//                name <<  "EnemyAstraeaLaserChip002["<<nLaser<<"]["<<nChip<<"]";
//                pChip = NEW EnemyAstraeaLaserChip002(name.str().c_str());
//                pChip->inactivateImmediately();
//                pLaserChipStore->addSubLast(pChip);
//            }
//            pLaserChipStore->inactivateImmediately();
//            _pStore_LaserChipStore->addSubLast(pLaserChipStore);
//        }
//        getLordActor()->addSubGroup(_pStore_LaserChipStore);
//    }
}

void CommonScene::initialize() {
}

void CommonScene::processBehavior() {


}

CommonScene::~CommonScene() {
}
