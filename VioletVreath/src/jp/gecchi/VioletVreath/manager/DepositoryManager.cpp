#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DepositoryManager::DepositoryManager(const char* prm_manager_name) :
    GgafResourceManager<GgafActorDepository> (prm_manager_name) {
}

GgafActorDepository* DepositoryManager::processCreateResource(char* prm_idstr, void* prm_pConnector) {
    GgafActorDepository* pResource = nullptr;

    if (UTIL::strcmp_ascii("Shot001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot001Stock");
        for (int i = 0; i < 100; i++) {
            pResource->addSubLast(NEW Shot001("Shot001"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource); //最後にaddSubGroupすべし（さもないと直ぐに削除対象になる）
    }

    if (UTIL::strcmp_ascii("Shot002", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot002Stock");
        for (int i = 0; i < 100; i++) { //ストック100個
            pResource->addSubLast(NEW Shot002("Shot002"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Shot003", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot003Stock");
        for (int i = 0; i < 100; i++) {
            pResource->addSubLast(NEW Shot003("Shot003"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Shot004", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot004Stock");
        for (int i = 0; i < 1000; i++) {
            pResource->addSubLast(NEW Shot004("Shot004"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Shot004Blue", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot004BlueStock");
        for (int i = 0; i < 300; i++) {
            pResource->addSubLast(NEW Shot004Blue("Shot004Blue"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("Shot004Yellow", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot004YellowStock");
        for (int i = 0; i < 300; i++) {
            pResource->addSubLast(NEW Shot004Yellow("Shot004Yellow"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("EffRefraction001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_EffRefraction001");
        for (int i = 0; i < 100; i++) {
            pResource->addSubLast(NEW EffectLaserRefraction001("EffRefraction001"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("EnemyAstraeaLaserChip001DepoStore", prm_idstr) == 0) {
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



    if (UTIL::strcmp_ascii("EnemyAstraeaLaserChip002DepoStore", prm_idstr) == 0) {
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
                pChip->config(30, 20, 8, true, nullptr);

                pLaserChipDepo->addSubLast(pChip);
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }


    if (UTIL::strcmp_ascii("EnemyAstraeaLaserChip003DepoStore", prm_idstr) == 0) {
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

    if (UTIL::strcmp_ascii("EnemyAstraeaLaserChip004DepoStore", prm_idstr) == 0) {
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

    if (UTIL::strcmp_ascii("EnemyEunomia4Formation", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("EnemyEunomiaDepo");
        for (int i = 0; i < 800; i++) {
            pResource->addSubLast(NEW EnemyEunomia("Eunomia"));
            Sleep(1);
        }

        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
//        if (prm_p) {
//            ((FormationActor*)prm_p)->setFormationMemberDepo()
//        } else {
//            throwGgafCriticalException("DepositoryManager::processCreateResource("<<prm_idstr<<") Formationを指定して下さい");
//        }
    }

    if (UTIL::strcmp_ascii("Massalia", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_Massalia");
        for (int i = 0; i < 200; i++) {
            pResource->addSubLast(NEW EnemyMassalia("EnemyMassalia"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("MassaliaFragment", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_MassaliaFragment");
        for (int i = 0; i < 200; i++) {
            pResource->addSubLast(NEW EnemyMassaliaFragment("EMF"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }
    if (UTIL::strcmp_ascii("MassaliaFragment2", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_MassaliaFragment2");
        for (int i = 0; i < 300; i++) {
            pResource->addSubLast(NEW EnemyMassaliaFragment2("EMF2"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }
    if (UTIL::strcmp_ascii("MassaliaFragment3", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_MassaliaFragment3");
        for (int i = 0; i < 400; i++) {
            pResource->addSubLast(NEW EnemyMassaliaFragment3("EMF3"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }



    if (UTIL::strcmp_ascii("EnemyHebe4Formation", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_Hebe");
        for (int i = 0; i < RR_FormationHebe_Num(2.0); i++) {
            pResource->addSubLast(NEW EnemyHebe("EnemyMassalia"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }


    if (UTIL::strcmp_ascii("EnemyHesperiaLaserChip001DepoStore", prm_idstr) == 0) {
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

    if (UTIL::strcmp_ascii("Atalante", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_AtalanteStock");
        for (int i = 0; i < 2000; i++) {
            std::string name = "EnemyAtalante("+XTOS(i)+")";
            pResource->addSubLast(NEW EnemyAtalante(name.c_str()));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }


    if (UTIL::strcmp_ascii("EnemyRemusLaserChip001DepoStore", prm_idstr) == 0) {
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


    if (UTIL::strcmp_ascii("EnemyThisbeLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyRemusLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 3; nLaser++) { //２本
            std::string name = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name.c_str());
            for (int nChip = 0; nChip < 300; nChip++) {
                std::string name = "EnemyThisbeLaserChip001["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                EnemyThisbeLaserChip001* pChip = NEW EnemyThisbeLaserChip001(name.c_str());
                pChip->_is_fix_begin_pos = false;
                pLaserChipDepo->addSubLast(pChip);
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("EnemyThisbeLaserChip002DepoStore", prm_idstr) == 0) {
        GgafActorDepository* pDepoEffect = NEW GgafActorDepository("ThisbeLaser");
        EffectLaserRefraction001* pEffect;
        for (int i = 0; i < 200; i++) {
            std::string name = "EffectLaserRefraction001["+XTOS(i)+"]";
            pEffect = NEW EffectLaserRefraction001(name.c_str());
            pDepoEffect->addSubLast(pEffect);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pDepoEffect);

        pResource = NEW GgafActorDepositoryStore("EnemyRemusLaserChip002DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 4; nLaser++) { //4本
            std::string name = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name.c_str());
            for (int nChip = 0; nChip < 200; nChip++) {
                std::string name = "EnemyThisbeLaserChip002["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                EnemyThisbeLaserChip002* pChip = NEW EnemyThisbeLaserChip002(name.c_str());
                int num_refraction = pChip->pKurokoLeader_->getPointNum();
                pChip->config(num_refraction, 1, 1, false, pDepoEffect);
                pLaserChipDepo->addSubLast(pChip);
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }


    if (UTIL::strcmp_ascii("AntiopeP", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_AntiopeP");
        for (int i = 0; i < 120; i++) {
            std::string name = "AntiopeP("+XTOS(i)+")";
            pResource->addSubLast(NEW EnemyAntiopeP(name.c_str()));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("AntiopeN", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_AntiopeN");
        for (int i = 0; i < 120; i++) {
            std::string name = "AntiopeN("+XTOS(i)+")";
            pResource->addSubLast(NEW EnemyAntiopeP(name.c_str()));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (UTIL::strcmp_ascii("EnemyAdelheid4Formation", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_AdelheidStock");
        for (int i = 0; i < 300; i++) {
            std::string name = "EnemyAdelheid("+XTOS(i)+")";
            pResource->addSubLast(NEW EnemyAdelheid(name.c_str()));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }
    if (UTIL::strcmp_ascii("EnemyAdelheidShot", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_AdelheidShotStock");
        for (int i = 0; i < 3; i++) {
            pResource->addSubLast(NEW Shot004Yellow("Shot004Yellow"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    //    pLaserChipDepo_ = NEW LaserChipDepository("ThisbeLaser");
    //    pLaserChipDepo_->config(300, 1, nullptr); //Thisbeは弾切れフレームを1にしないとパクパクしちゃいます。
    //    for (int i = 0; i < 300; i++) { //レーザーストック
    //        std::string name = "EnemyThisbeLaserChip001["+XTOS(i)+"]";
    //        EnemyThisbeLaserChip001* pChip = NEW EnemyThisbeLaserChip001(name.c_str());
    //        pChip->_is_fix_begin_pos = false;
    //        pLaserChipDepo_->addSubLast(pChip);
    //    }
    //    addSubGroup(pLaserChipDepo_);


    //敵カーブレーザー01未使用。こぴぺのために残す
    /*
    if (UTIL::strcmp_ascii("EneWateringLaser001Dp", prm_idstr) == 0) {
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
