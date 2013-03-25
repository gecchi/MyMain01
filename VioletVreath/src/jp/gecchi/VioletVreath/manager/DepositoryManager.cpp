#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DepositoryManager::DepositoryManager(const char* prm_manager_name) :
    GgafResourceManager<GgafActorDepository> (prm_manager_name) {
}

GgafActorDepository* DepositoryManager::processCreateResource(char* prm_idstr, void* prm_p) {
    GgafActorDepository* pResource = nullptr;

    if (UTIL::strcmp_ascii("Conn_Shot001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot001Stock");
        for (int i = 0; i < 100; i++) {
            pResource->addSubLast(NEW Shot001("Shot001"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource); //最後にaddSubGroupすべし（さもないと直ぐに削除対象になる）
    }

    if (UTIL::strcmp_ascii("Conn_Shot002", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot002Stock");
        for (int i = 0; i < 100; i++) { //ストック100個
            pResource->addSubLast(NEW Shot002("Shot002"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Conn_Shot003", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot003Stock");
        for (int i = 0; i < 100; i++) {
            pResource->addSubLast(NEW Shot003("Shot003"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Conn_Shot004", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot004Stock");
        for (int i = 0; i < 1000; i++) {
            pResource->addSubLast(NEW Shot004("Shot004"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Conn_Shot004Blue", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot004BlueStock");
        for (int i = 0; i < 300; i++) {
            pResource->addSubLast(NEW Shot004Blue("Shot004Blue"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Conn_Shot004Yellow", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot004YellowStock");
        for (int i = 0; i < 300; i++) {
            pResource->addSubLast(NEW Shot004Yellow("Shot004Yellow"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Conn_EffRefraction001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_EffRefraction001");
        for (int i = 0; i < 100; i++) {
            pResource->addSubLast(NEW EffectLaserRefraction001("EffRefraction001"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Conn_EnemyAstraeaLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyAstraeaLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 27; nLaser++) {
            std::stringstream name;
            name <<  "LaserChipDepository["<<nLaser<<"]";
            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::stringstream name;
                name <<  "EnemyAstraeaLaserChip001["<<nLaser<<"]["<<nChip<<"]";
                pLaserChipDepo->addSubLast(NEW EnemyAstraeaLaserChip001(name.str().c_str()));
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }



    if (UTIL::strcmp_ascii("Conn_EnemyAstraeaLaserChip002DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyAstraeaLaserChip002DepoStore");
        LaserChipDepository* pLaserChipDepo;
        EnemyAstraeaLaserChip002* pChip;
        for (int nLaser = 0; nLaser < 27; nLaser++) {
            std::stringstream name;
            name <<  "LaserChipDepository["<<nLaser<<"]";
            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::stringstream name;
                name <<  "EnemyAstraeaLaserChip002["<<nLaser<<"]["<<nChip<<"]";
                pChip = NEW EnemyAstraeaLaserChip002(name.str().c_str());
                pChip->config(30, 20, 8, (GgafActorDepository*)prm_p);
                pLaserChipDepo->addSubLast(pChip);
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }


    if (UTIL::strcmp_ascii("Conn_EnemyAstraeaLaserChip003DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyAstraeaLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 30; nLaser++) {
            std::stringstream name;
            name <<  "LaserChipDepository["<<nLaser<<"]";
            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::stringstream name;
                name <<  "EnemyAstraeaLaserChip003["<<nLaser<<"]["<<nChip<<"]";
                pLaserChipDepo->addSubLast(NEW EnemyAstraeaLaserChip003(name.str().c_str()));
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Conn_EnemyAstraeaLaserChip004DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyAstraeaLaserChip004DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 30; nLaser++) {
            std::stringstream name;
            name <<  "LaserChipDepository["<<nLaser<<"]";
            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::stringstream name;
                name <<  "EnemyAstraeaLaserChip004["<<nLaser<<"]["<<nChip<<"]";
                pLaserChipDepo->addSubLast(NEW EnemyAstraeaLaserChip004(name.str().c_str()));
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Conn_EnemyEunomia4Formation", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("EnemyEunomiaDepo");
        for (int i = 0; i < 800; i++) {
            pResource->addSubLast(NEW EnemyEunomia("Eunomia"));
            Sleep(1);
        }

        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
//        if (prm_p) {
//            ((FormationActor*)prm_p)->setFormationMemberDepository()
//        } else {
//            throwGgafCriticalException("DepositoryManager::processCreateResource("<<prm_idstr<<") Formationを指定して下さい");
//        }
    }

    if (UTIL::strcmp_ascii("Conn_Massalia", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_Massalia");
        for (int i = 0; i < 200; i++) {
            pResource->addSubLast(NEW EnemyMassalia("EnemyMassalia"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Conn_MassaliaFragment", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_MassaliaFragment");
        for (int i = 0; i < 200; i++) {
            pResource->addSubLast(NEW EnemyMassaliaFragment("EMF"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }
    if (UTIL::strcmp_ascii("Conn_MassaliaFragment2", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_MassaliaFragment2");
        for (int i = 0; i < 300; i++) {
            pResource->addSubLast(NEW EnemyMassaliaFragment2("EMF2"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }
    if (UTIL::strcmp_ascii("Conn_MassaliaFragment3", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_MassaliaFragment3");
        for (int i = 0; i < 400; i++) {
            pResource->addSubLast(NEW EnemyMassaliaFragment3("EMF3"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }



    if (UTIL::strcmp_ascii("Conn_EnemyHebe4Formation", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_Hebe");
        for (int i = 0; i < RR_FormationHebe_Num(2.0); i++) {
            pResource->addSubLast(NEW EnemyHebe("EnemyMassalia"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }


    if (UTIL::strcmp_ascii("Conn_EnemyHesperiaLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyHesperiaLaserChip0014DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < RR_EnemyHesperia_ShotWay(1.0)*8; nLaser++) {
            std::string name = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name.c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::string name = "EnemyHesperiaLaserChip001["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->addSubLast(NEW EnemyHesperiaLaserChip001(name.c_str()));
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Conn_Atalante", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_AtalanteStock");
        for (int i = 0; i < 2000; i++) {
            std::string name = "EnemyAtalante("+XTOS(i)+")";
            pResource->addSubLast(NEW EnemyAtalante(name.c_str()));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }


    if (UTIL::strcmp_ascii("Conn_EnemyRemusLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyRemusLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 20; nLaser++) { //２０本
            std::string name = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name.c_str());
            for (int nChip = 0; nChip < 100; nChip++) {
                std::string name = "EnemyRemusLaserChip001["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->addSubLast(NEW EnemyRemusLaserChip001(name.c_str()));
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }



    //敵カーブレーザー01未使用。こぴぺのために残す
    /*
    if (UTIL::strcmp_ascii("Conn_EneWateringLaser001Dp", prm_idstr) == 0) {
        pResource = NEW LaserChipDepositoryStore("DPDP_EneWateringLaser001");
        LaserChipDepository* pLaserChipDepo;
        EnemyWateringLaserChip001* pChip;
        for (int set = 0; set < 20; set++) {
            std::stringstream name;
            name <<  "EneWateringLaser001Dp["<<set<<"]";
            pLaserChipDepo = NEW LaserChipDepository(name.str().c_str());
            for (int n = 0; n < 50; n++) {
                std::stringstream name;
                name <<  "EneWateringLaser001["<<set<<"]["<<n<<"]";
                pChip = NEW EnemyWateringLaserChip001(name.str().c_str());
                pChip->inactivateImmed();
                pLaserChipDepo->addSubLast(pChip);
                if (n % 20 == 0) { Sleep(1); }
            }
            pLaserChipDepo->inactivateImmed();
            pResource->addSubLast(pLaserChipDepo);

        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }
*/

    if (pResource == nullptr) {
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
