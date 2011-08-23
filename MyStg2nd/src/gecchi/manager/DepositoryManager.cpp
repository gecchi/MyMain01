#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DepositoryManager::DepositoryManager(const char* prm_manager_name) :
    GgafResourceManager<GgafActorDepository> (prm_manager_name) {
}

GgafActorDepository* DepositoryManager::processCreateResource(char* prm_idstr, void* prm_p) {
    GgafActorDepository* pResource = NULL;

    if (GgafUtil::strcmp_ascii("StCon_Shot001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("DP_Shot001_Stock");
        Shot001* pShot001;
        for (int i = 0; i < 100; i++) { //ストック100個
            pShot001 = NEW Shot001("Shot001");
            pResource->addSubLast(pShot001);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource); //最後にaddSubGroupすべし（さもないと直ぐに削除対象になる）
    }

    if (GgafUtil::strcmp_ascii("StCon_Shot002", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("DP_Shot002_Stock");
        Shot002* pShot002;
        for (int i = 0; i < 100; i++) { //ストック100個
            pShot002 = NEW Shot002("Shot002");
            pResource->addSubLast(pShot002);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("StCon_Shot003", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("DP_Shot003_Stock");
        Shot003* pShot003;
        for (int i = 0; i < 300; i++) {
            pShot003 = NEW Shot003("Shot003");
            pResource->addSubLast(pShot003);
            if (i % 20 == 0) { Sleep(1); }
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("StCon_Shot004", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("DP_Shot004_Stock");
        Shot004* pShot004;
        for (int i = 0; i < 1600; i++) {
            pShot004 = NEW Shot004("Shot004");
            pResource->addSubLast(pShot004);
            if (i % 20 == 0) { Sleep(1); }
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("StCon_EffRefraction001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("DP_EffRefraction001");
        EffectLaserRefraction001* p;
        for (int i = 0; i < 100; i++) {
            p = NEW EffectLaserRefraction001("EffRefraction001");
            pResource->addSubLast(p);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("StCon_EnemyAstraeaLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyAstraeaLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        EnemyAstraeaLaserChip001* pChip;
        for (int nLaser = 0; nLaser < 27; nLaser++) {
            stringstream name;
            name <<  "LaserChipDepository["<<nLaser<<"]";
            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                stringstream name;
                name <<  "EnemyAstraeaLaserChip001["<<nLaser<<"]["<<nChip<<"]";
                pChip = NEW EnemyAstraeaLaserChip001(name.str().c_str());
                pLaserChipDepo->addSubLast(pChip);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }



    if (GgafUtil::strcmp_ascii("StCon_EnemyAstraeaLaserChip002DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyAstraeaLaserChip002DepoStore");
        LaserChipDepository* pLaserChipDepo;
        EnemyAstraeaLaserChip002* pChip;
        for (int nLaser = 0; nLaser < 27; nLaser++) {
            stringstream name;
            name <<  "LaserChipDepository["<<nLaser<<"]";
            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                stringstream name;
                name <<  "EnemyAstraeaLaserChip002["<<nLaser<<"]["<<nChip<<"]";
                pChip = NEW EnemyAstraeaLaserChip002(name.str().c_str());
                pChip->config(30, 20, 8, (GgafActorDepository*)prm_p);
                pLaserChipDepo->addSubLast(pChip);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }


    if (GgafUtil::strcmp_ascii("StCon_EnemyAstraeaLaserChip003DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyAstraeaLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        EnemyAstraeaLaserChip003* pChip;
        for (int nLaser = 0; nLaser < 50; nLaser++) {
            stringstream name;
            name <<  "LaserChipDepository["<<nLaser<<"]";
            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                stringstream name;
                name <<  "EnemyAstraeaLaserChip003["<<nLaser<<"]["<<nChip<<"]";
                pChip = NEW EnemyAstraeaLaserChip003(name.str().c_str());
                pLaserChipDepo->addSubLast(pChip);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("StCon_EnemyAstraeaLaserChip004DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyAstraeaLaserChip004DepoStore");
        LaserChipDepository* pLaserChipDepo;
        EnemyAstraeaLaserChip004* pChip;
        for (int nLaser = 0; nLaser < 50; nLaser++) {
            stringstream name;
            name <<  "LaserChipDepository["<<nLaser<<"]";
            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                stringstream name;
                name <<  "EnemyAstraeaLaserChip004["<<nLaser<<"]["<<nChip<<"]";
                pChip = NEW EnemyAstraeaLaserChip004(name.str().c_str());
                pLaserChipDepo->addSubLast(pChip);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    //敵カーブレーザー01未使用。こぴぺのために残す
    /*
    if (GgafUtil::strcmp_ascii("StCon_EneWateringLaser001Dp", prm_idstr) == 0) {
        pResource = NEW LaserChipDepositoryStore("DPDP_EneWateringLaser001");
        LaserChipDepository* pLaserChipDepo;
        EnemyWateringLaserChip001* pChip;
        for (int set = 0; set < 20; set++) {
            stringstream name;
            name <<  "EneWateringLaser001Dp["<<set<<"]";
            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
            for (int n = 0; n < 50; n++) {
                stringstream name;
                name <<  "EneWateringLaser001["<<set<<"]["<<n<<"]";
                pChip = NEW EnemyWateringLaserChip001(name.str().c_str());
                pChip->inactivateImmediately();
                pLaserChipDepo->addSubLast(pChip);
                if (n % 20 == 0) { Sleep(1); }
            }
            pLaserChipDepo->inactivateImmediately();
            pResource->addSubLast(pLaserChipDepo);

        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }
*/

    if (pResource == NULL) {
        throwGgafCriticalException("DepositoryManager::processCreateResource("<<prm_idstr<<") 想定外のIDです。Depositoryが作成できません。");
    }
    return pResource;
}

GgafResourceConnection<GgafActorDepository>* DepositoryManager::processCreateConnection(char* prm_idstr, GgafActorDepository* prm_pResource) {
    TRACE3(" DepositoryManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    DepositoryConnection* pConnection = NEW DepositoryConnection(prm_idstr, prm_pResource);
    TRACE3(" DepositoryManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
