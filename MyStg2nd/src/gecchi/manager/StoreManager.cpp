#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

StoreManager::StoreManager(const char* prm_manager_name) :
    GgafResourceManager<GgafActorStore> (prm_manager_name) {
}

GgafActorStore* StoreManager::processCreateResource(char* prm_idstr, void* prm_p) {
    GgafActorStore* pResource = NULL;

    if (GgafUtil::strcmp_ascii("StCon_Shot001", prm_idstr) == 0) {
        pResource = NEW GgafActorStore("DP_Shot001_Stock");
        Shot001* pShot001;
        for (int i = 0; i < 100; i++) { //ストック100個
            pShot001 = NEW Shot001("Shot001");
            pResource->addSubLast(pShot001);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource); //最後にaddSubGroupすべし（さもないと直ぐに削除対象になる）
    }

    if (GgafUtil::strcmp_ascii("StCon_Shot002", prm_idstr) == 0) {
        pResource = NEW GgafActorStore("DP_Shot002_Stock");
        Shot002* pShot002;
        for (int i = 0; i < 100; i++) { //ストック100個
            pShot002 = NEW Shot002("Shot002");
            pResource->addSubLast(pShot002);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("StCon_Shot003", prm_idstr) == 0) {
        pResource = NEW GgafActorStore("DP_Shot003_Stock");
        Shot003* pShot003;
        for (int i = 0; i < 300; i++) {
            pShot003 = NEW Shot003("Shot003");
            pResource->addSubLast(pShot003);
            if (i % 20 == 0) { Sleep(1); }
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("StCon_Shot004", prm_idstr) == 0) {
        pResource = NEW GgafActorStore("DP_Shot004_Stock");
        Shot004* pShot004;
        for (int i = 0; i < 1600; i++) {
            pShot004 = NEW Shot004("Shot004");
            pResource->addSubLast(pShot004);
            if (i % 20 == 0) { Sleep(1); }
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("StCon_EffRefraction001", prm_idstr) == 0) {
        pResource = NEW GgafActorStore("DP_EffRefraction001");
        EffectLaserRefraction001* p;
        for (int i = 0; i < 100; i++) {
            p = NEW EffectLaserRefraction001("EffRefraction001");
            pResource->addSubLast(p);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("StCon_EnemyAstraeaLaserChip001StoreDp", prm_idstr) == 0) {
        pResource = NEW GgafActorStoreDispatcher("EnemyAstraeaLaserChip001StoreDp");
        LaserChipStore* pLaserChipStore;
        EnemyAstraeaLaserChip001* pChip;
        for (int nLaser = 0; nLaser < 27; nLaser++) {
            stringstream name;
            name <<  "LaserChipStore["<<nLaser<<"]";
            pLaserChipStore = NEW LaserChipStore(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                stringstream name;
                name <<  "EnemyAstraeaLaserChip001["<<nLaser<<"]["<<nChip<<"]";
                pChip = NEW EnemyAstraeaLaserChip001(name.str().c_str());
                pLaserChipStore->addSubLast(pChip);
            }
            pResource->addSubLast(pLaserChipStore);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }



    if (GgafUtil::strcmp_ascii("StCon_EnemyAstraeaLaserChip002StoreDp", prm_idstr) == 0) {
        pResource = NEW GgafActorStoreDispatcher("EnemyAstraeaLaserChip002StoreDp");
        LaserChipStore* pLaserChipStore;
        EnemyAstraeaLaserChip002* pChip;
        for (int nLaser = 0; nLaser < 27; nLaser++) {
            stringstream name;
            name <<  "LaserChipStore["<<nLaser<<"]";
            pLaserChipStore = NEW LaserChipStore(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                stringstream name;
                name <<  "EnemyAstraeaLaserChip002["<<nLaser<<"]["<<nChip<<"]";
                pChip = NEW EnemyAstraeaLaserChip002(name.str().c_str());
                pChip->config(30, 20, 8, (GgafActorStore*)prm_p);
                pLaserChipStore->addSubLast(pChip);
            }
            pResource->addSubLast(pLaserChipStore);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }


    if (GgafUtil::strcmp_ascii("StCon_EnemyAstraeaLaserChip003StoreDp", prm_idstr) == 0) {
        pResource = NEW GgafActorStoreDispatcher("EnemyAstraeaLaserChip001StoreDp");
        LaserChipStore* pLaserChipStore;
        EnemyAstraeaLaserChip003* pChip;
        for (int nLaser = 0; nLaser < 27; nLaser++) {
            stringstream name;
            name <<  "LaserChipStore["<<nLaser<<"]";
            pLaserChipStore = NEW LaserChipStore(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                stringstream name;
                name <<  "EnemyAstraeaLaserChip003["<<nLaser<<"]["<<nChip<<"]";
                pChip = NEW EnemyAstraeaLaserChip003(name.str().c_str());
                pLaserChipStore->addSubLast(pChip);
            }
            pResource->addSubLast(pLaserChipStore);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }
    //敵カーブレーザー01未使用。こぴぺのために残す
    /*
    if (GgafUtil::strcmp_ascii("StCon_EneWateringLaser001Dp", prm_idstr) == 0) {
        pResource = NEW LaserChipStoreDispatcher("DPDP_EneWateringLaser001");
        LaserChipStore* pLaserChipStore;
        EnemyWateringLaserChip001* pChip;
        for (int set = 0; set < 20; set++) {
            stringstream name;
            name <<  "EneWateringLaser001Dp["<<set<<"]";
            pLaserChipStore = NEW LaserChipStore(name.str().c_str());
            for (int n = 0; n < 50; n++) {
                stringstream name;
                name <<  "EneWateringLaser001["<<set<<"]["<<n<<"]";
                pChip = NEW EnemyWateringLaserChip001(name.str().c_str());
                pChip->inactivateImmediately();
                pLaserChipStore->addSubLast(pChip);
                if (n % 20 == 0) { Sleep(1); }
            }
            pLaserChipStore->inactivateImmediately();
            pResource->addSubLast(pLaserChipStore);

        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }
*/

    if (pResource == NULL) {
        throwGgafCriticalException("StoreManager::processCreateResource("<<prm_idstr<<") 想定外のIDです。Storeが作成できません。");
    }
    return pResource;
}

GgafResourceConnection<GgafActorStore>* StoreManager::processCreateConnection(char* prm_idstr, GgafActorStore* prm_pResource) {
    TRACE3(" StoreManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    StoreConnection* pConnection = NEW StoreConnection(prm_idstr, prm_pResource);
    TRACE3(" StoreManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
