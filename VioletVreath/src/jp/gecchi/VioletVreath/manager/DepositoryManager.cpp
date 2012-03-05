#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DepositoryManager::DepositoryManager(const char* prm_manager_name) :
    GgafResourceManager<GgafActorDepository> (prm_manager_name) {
}

GgafActorDepository* DepositoryManager::processCreateResource(char* prm_idstr, void* prm_p) {
    GgafActorDepository* pResource = NULL;

    if (GgafUtil::strcmp_ascii("DpCon_Shot001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("DP_Shot001Stock_");
        Shot001* pShot001;
        for (int i = 0; i < 100; i++) { //ストック100個
            pShot001 = NEW Shot001("Shot001");
            pResource->addSubLast(pShot001);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource); //最後にaddSubGroupすべし（さもないと直ぐに削除対象になる）
    }

    if (GgafUtil::strcmp_ascii("DpCon_Shot002", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("DP_Shot002Stock_");
        Shot002* pShot002;
        for (int i = 0; i < 100; i++) { //ストック100個
            pShot002 = NEW Shot002("Shot002");
            pResource->addSubLast(pShot002);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_Shot003", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("DP_Shot003Stock_");
        Shot003* pShot003;
        for (int i = 0; i < 300; i++) {
            pShot003 = NEW Shot003("Shot003");
            pResource->addSubLast(pShot003);
            if (i % 20 == 0) { Sleep(1); }
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_Shot004", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("DP_Shot004Stock_");
        Shot004* pShot004;
        for (int i = 0; i < 1600; i++) {
            pShot004 = NEW Shot004("Shot004");
            pResource->addSubLast(pShot004);
            if (i % 2 == 0) { Sleep(1); }
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_EffRefraction001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("DP_EffRefraction001");
        EffectLaserRefraction001* p;
        for (int i = 0; i < 100; i++) {
            p = NEW EffectLaserRefraction001("EffRefraction001");
            pResource->addSubLast(p);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_EnemyAstraeaLaserChip001DepoStore", prm_idstr) == 0) {
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
                if (nChip % 4 == 0) { Sleep(1); }
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }



    if (GgafUtil::strcmp_ascii("DpCon_EnemyAstraeaLaserChip002DepoStore", prm_idstr) == 0) {
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
                if (nChip % 4 == 0) { Sleep(1); }
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }


    if (GgafUtil::strcmp_ascii("DpCon_EnemyAstraeaLaserChip003DepoStore", prm_idstr) == 0) {
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
                if (nChip % 4 == 0) { Sleep(1); }
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_EnemyAstraeaLaserChip004DepoStore", prm_idstr) == 0) {
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
                if (nChip % 4 == 0) { Sleep(1); }
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_EnemyEunomia4Formation", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("EnemyEunomiaDepo");
        EnemyEunomia* p;
        for (int i = 0; i < 800; i++) {
            p = NEW EnemyEunomia("Eunomia");
            pResource->addSubLast(p);
            if (i % 4 == 0) { Sleep(1); }
        }

        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
//        if (prm_p) {
//            ((FormationActor*)prm_p)->setFormationAbleActorDepository()
//        } else {
//            throwGgafCriticalException("DepositoryManager::processCreateResource("<<prm_idstr<<") Formationを指定して下さい");
//        }
    }

    if (GgafUtil::strcmp_ascii("DpCon_Massalia", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_Massalia");
        EnemyMassalia* p;
        for (int i = 0; i < 200; i++) {
            p = NEW EnemyMassalia("EnemyMassalia");
            pResource->addSubLast(p);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_MassaliaFragment", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_MassaliaFragment");
        EnemyMassaliaFragment* p;
        for (int i = 0; i < 200; i++) {
            p = NEW EnemyMassaliaFragment("EnemyMassaliaFragment");
            pResource->addSubLast(p);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }
    if (GgafUtil::strcmp_ascii("DpCon_MassaliaFragment2", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_MassaliaFragment2");
        EnemyMassaliaFragment2* p;
        for (int i = 0; i < 200; i++) {
            p = NEW EnemyMassaliaFragment2("EnemyMassaliaFragment2");
            pResource->addSubLast(p);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }
    if (GgafUtil::strcmp_ascii("DpCon_MassaliaFragment3", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_MassaliaFragment3");
        EnemyMassaliaFragment3* p;
        for (int i = 0; i < 200; i++) {
            p = NEW EnemyMassaliaFragment3("EnemyMassaliaFragment3");
            pResource->addSubLast(p);
        }
        P_COMMON_SCENE->getDirector()->addSubGroup(pResource);
    }
    //敵カーブレーザー01未使用。こぴぺのために残す
    /*
    if (GgafUtil::strcmp_ascii("DpCon_EneWateringLaser001Dp", prm_idstr) == 0) {
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
                pChip->inactivateImmed();
                pLaserChipDepo->addSubLast(pChip);
                if (n % 20 == 0) { Sleep(1); }
            }
            pLaserChipDepo->inactivateImmed();
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
