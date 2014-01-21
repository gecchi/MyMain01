#include "stdafx.h"
#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage.h"
#include "part/Stage01_01.h"
#include "part/Stage01_02.h"
#include "part/Stage01_03.h"
#include "part/Stage01_Climax.h"
#include "part/Stage01WalledScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,40,100,120,160,220,280,300,340,400,460,500,502,505,520,540,580,600,605,640,700,760,780,820,880,940,1000,1020,1060,1120,1180,1200,1240,1300,1360,1420,1480,1540,1600,1660,1720,1780,1840,1900,1960,2020,2080,2140,2200,2260,2320,2380,2440,2500,2560,2620,2680,2740,2800,2860,2920,2980,3100,3400,3700,4000,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,6100,6400,6700,7000,7300,7600,7900,8200,8500,8800,9100,9400,9700,10000,10300,10600,10900,11200,11500,11800,12100,12400,12700,13000,13300,13600,13900,14200,14500,14800,15100,15400,15700,16000,16300,16600,16900,17200,17500,17800,18100,18400,18700,19000,19100,19300,19600,19900,20000,20200,20300,20500,20800,21100,21200,21400,21700,22000,22300,22600,22900,23200,23500,23800,24100,24400,24700,25000,25300,25600,25900,26200,26500,26800,27100,27400,27700,28000,28300,28600,28900,29100,29200,29500,29800,30000};
	_paFrame_NextEvent = new frame[170];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 170;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01-1");
	orderActorToFactory(10000004, FormationIda001, "FormationIda001-2");
	orderActorToFactory(10000008, FormationEbe001, "FormationEbe001-3");
	orderActorToFactory(10000009, FormationUnomia001a, "FormationUnomia001a-4");
	orderActorToFactory(10000010, FormationUnomia001b, "FormationUnomia001b-5");
	orderActorToFactory(10000011, EnemyStraea, "EnemyStraea-6");
	orderActorToFactory(10000012, EnemyEsperia, "EnemyEsperia-7");
	orderActorToFactory(10000013, EnemyEsperia, "EnemyEsperia-8");
	orderActorToFactory(10000014, EnemyEsperia, "EnemyEsperia-9");
	orderActorToFactory(10000112, FormationAppho001a, "FormationAppho001a-10");
	orderActorToFactory(10000113, FormationAppho001b, "FormationAppho001b-11");
	orderActorToFactory(10000114, FormationAppho001a, "FormationAppho001a-12");
	orderActorToFactory(10000138, FormationThagoras001, "FormationThagoras001-13");
	orderActorToFactory(10000139, FormationThagoras002, "FormationThagoras002-14");
	orderActorToFactory(10000140, FormationOrtuna001a, "FormationOrtuna001a-15");
	orderActorToFactory(10000142, EnemyGlaja, "EnemyGlaja-16");
	orderActorToFactory(10000143, EnemyGlaja, "EnemyGlaja-17");
	orderActorToFactory(10000144, EnemyGlaja, "EnemyGlaja-18");
	orderActorToFactory(10000145, EnemyDuna, "EnemyDuna-19");
	orderActorToFactory(10000146, EnemyDuna, "EnemyDuna-20");
	orderActorToFactory(10000147, EnemyDuna, "EnemyDuna-21");
	orderActorToFactory(10000148, EnemyDuna, "EnemyDuna-22");
	orderActorToFactory(10000149, EnemyDuna, "EnemyDuna-23");
	orderActorToFactory(10000150, EnemyDuna, "EnemyDuna-24");
	orderActorToFactory(10000151, EnemyDuna, "EnemyDuna-25");
	orderActorToFactory(10000152, EnemyDuna, "EnemyDuna-26");
	orderActorToFactory(10000153, EnemyDuna, "EnemyDuna-27");
	orderActorToFactory(10000189, EnemyOzartia, "EnemyOzartia-28");
	orderActorToFactory(10000190, EnemyOzartia, "EnemyOzartia-29");
    // gen01 end
    useProgress(Stage01PartController::PROG_BANPEI-1);
}

void Stage01PartController::initialize() {
    _pProg->reset(Stage01PartController::PROG_INIT);
}

void Stage01PartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 40: {
				orderActorToFactory(10000154, EnemyDuna, "EnemyDuna-30");
				break;
			}
			case 100: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				EnemyEsperia* p31 = (EnemyEsperia*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(p31);
				orderActorToFactory(10000015, EnemyEsperia, "EnemyEsperia-32");
				orderActorToFactory(10000117, FormationAllas001a, "FormationAllas001a-33");
				orderActorToFactory(10000118, FormationAllas001b, "FormationAllas001b-34");
				orderActorToFactory(10000119, FormationAllas001c, "FormationAllas001c-35");
				orderActorToFactory(10000120, FormationAllas001d, "FormationAllas001d-36");
				orderActorToFactory(10000121, FormationAllas001a, "FormationAllas001a-37");
				orderActorToFactory(10000122, FormationAllas001d, "FormationAllas001d-38");
				orderActorToFactory(10000123, FormationAllas001b, "FormationAllas001b-39");
				orderActorToFactory(10000124, FormationAllas001c, "FormationAllas001c-40");
				orderActorToFactory(10000125, FormationAllas001a, "FormationAllas001a-41");
				orderActorToFactory(10000126, FormationAllas001d, "FormationAllas001d-42");
				orderActorToFactory(10000127, FormationAllas001b, "FormationAllas001b-43");
				orderActorToFactory(10000128, FormationAllas001c, "FormationAllas001c-44");
				orderActorToFactory(10000141, FormationOrtuna001b, "FormationOrtuna001b-45");
				orderActorToFactory(10000155, EnemyDuna, "EnemyDuna-46");
				break;
			}
			case 120: {
				orderActorToFactory(10000115, FormationAppho001b, "FormationAppho001b-47");
				break;
			}
			case 160: {
				orderActorToFactory(10000156, EnemyDuna, "EnemyDuna-48");
				break;
			}
			case 220: {
				orderActorToFactory(10000157, EnemyDuna, "EnemyDuna-49");
				break;
			}
			case 280: {
				orderActorToFactory(10000158, EnemyDuna, "EnemyDuna-50");
				break;
			}
			case 300: {
				FormationIda001* p = (FormationIda001*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(p);
				p->getFkBase()->position(PX_C(800), 0, 0);
				orderActorToFactory(10000005, EnemyErmione, "EnemyErmione-51");
				FormationEbe001* pF52 = (FormationEbe001*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(pF52);
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pFSap = (FormationAppho001a*)obtainActorFromFactory(10000112);
				getSceneDirector()->addSubGroup(pFSap);
				FormationOrtuna001a* pF1 = (FormationOrtuna001a*)obtainActorFromFactory(10000140);
				getSceneDirector()->addSubGroup(pF1);
				break;
			}
			case 340: {
				orderActorToFactory(10000159, EnemyDuna, "EnemyDuna-53");
				break;
			}
			case 400: {
				EnemyEsperia* p54 = (EnemyEsperia*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(p54);
				orderActorToFactory(10000016, EnemyEsperia, "EnemyEsperia-55");
				EnemyGlaja* p = (EnemyGlaja*)obtainActorFromFactory(10000142);
				getSceneDirector()->addSubGroup(p);
				p->position(100000,0,0);
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000145);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000160, EnemyDuna, "EnemyDuna-56");
				break;
			}
			case 460: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000146);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000161, EnemyDuna, "EnemyDuna-57");
				break;
			}
			case 500: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				EnemyGlaja* p = (EnemyGlaja*)obtainActorFromFactory(10000143);
				getSceneDirector()->addSubGroup(p);
				p->position(100000,0,0);
				break;
			}
			case 502: {
				FormationThagoras001* pF1 = (FormationThagoras001*)obtainActorFromFactory(10000138);
				getSceneDirector()->addSubGroup(pF1);
				pF1->position(PX_C(-200), PX_C(  0), PX_C(500));
				FormationThagoras002* pF2 = (FormationThagoras002*)obtainActorFromFactory(10000139);
				getSceneDirector()->addSubGroup(pF2);
				pF2->position(PX_C(-200), PX_C(  0), PX_C(530));
				break;
			}
			case 505: {
				EnemyOzartia* p = (EnemyOzartia*)obtainActorFromFactory(10000189);
				getSceneDirector()->addSubGroup(p);
				p->position(1000000,0,0);
				break;
			}
			case 520: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000147);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000162, EnemyDuna, "EnemyDuna-58");
				break;
			}
			case 540: {
				FormationAppho001b* pFSap = (FormationAppho001b*)obtainActorFromFactory(10000113);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 580: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000148);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000163, EnemyDuna, "EnemyDuna-59");
				break;
			}
			case 600: {
				EnemyStraea* pStraea2 = (EnemyStraea*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(pStraea2);
				pStraea2->_z = 1000000;
				pStraea2->_y = 10000;
				EnemyGlaja* p = (EnemyGlaja*)obtainActorFromFactory(10000144);
				getSceneDirector()->addSubGroup(p);
				p->position(100000,0,0);
				break;
			}
			case 605: {
				EnemyOzartia* p = (EnemyOzartia*)obtainActorFromFactory(10000190);
				getSceneDirector()->addSubGroup(p);
				p->position(1000000,0,0);
				break;
			}
			case 640: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000149);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000164, EnemyDuna, "EnemyDuna-60");
				break;
			}
			case 700: {
				EnemyEsperia* p61 = (EnemyEsperia*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(p61);
				orderActorToFactory(10000017, EnemyEsperia, "EnemyEsperia-62");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000150);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000165, EnemyDuna, "EnemyDuna-63");
				break;
			}
			case 760: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000151);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000166, EnemyDuna, "EnemyDuna-64");
				break;
			}
			case 780: {
				FormationAppho001a* pFSap = (FormationAppho001a*)obtainActorFromFactory(10000114);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 820: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000152);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000167, EnemyDuna, "EnemyDuna-65");
				break;
			}
			case 880: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000153);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000168, EnemyDuna, "EnemyDuna-66");
				break;
			}
			case 940: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000154);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000169, EnemyDuna, "EnemyDuna-67");
				break;
			}
			case 1000: {
				EnemyEsperia* p68 = (EnemyEsperia*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(p68);
				orderActorToFactory(10000018, EnemyEsperia, "EnemyEsperia-69");
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-70");
				ta->setMaxPerformFrame(3000);
				addSubLast(ta);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(10000117)), 400);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(10000118)), 400);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(10000119)), 400);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(10000120)), 400);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(10000121)), 1);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(10000122)), 400);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(10000123)), 1);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(10000124)), 400);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(10000125)), 1);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(10000126)), 1);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(10000127)), 1);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(10000128)), 400);
				}
				FormationOrtuna001b* pF1 = (FormationOrtuna001b*)obtainActorFromFactory(10000141);
				getSceneDirector()->addSubGroup(pF1);
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000155);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000170, EnemyDuna, "EnemyDuna-71");
				break;
			}
			case 1020: {
				FormationAppho001b* pFSap = (FormationAppho001b*)obtainActorFromFactory(10000115);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 1060: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000156);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000171, EnemyDuna, "EnemyDuna-72");
				break;
			}
			case 1120: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000157);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000172, EnemyDuna, "EnemyDuna-73");
				break;
			}
			case 1180: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000158);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000173, EnemyDuna, "EnemyDuna-74");
				break;
			}
			case 1200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 1240: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000159);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000174, EnemyDuna, "EnemyDuna-75");
				break;
			}
			case 1300: {
				EnemyEsperia* p76 = (EnemyEsperia*)obtainActorFromFactory(10000016);
				getSceneDirector()->addSubGroup(p76);
				orderActorToFactory(10000019, EnemyEsperia, "EnemyEsperia-77");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000160);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000175, EnemyDuna, "EnemyDuna-78");
				break;
			}
			case 1360: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000161);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000176, EnemyDuna, "EnemyDuna-79");
				break;
			}
			case 1420: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000162);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000177, EnemyDuna, "EnemyDuna-80");
				break;
			}
			case 1480: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000163);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000178, EnemyDuna, "EnemyDuna-81");
				break;
			}
			case 1540: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000164);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000179, EnemyDuna, "EnemyDuna-82");
				break;
			}
			case 1600: {
				EnemyEsperia* p83 = (EnemyEsperia*)obtainActorFromFactory(10000017);
				getSceneDirector()->addSubGroup(p83);
				orderActorToFactory(10000020, EnemyEsperia, "EnemyEsperia-84");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000165);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000180, EnemyDuna, "EnemyDuna-85");
				break;
			}
			case 1660: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000166);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000181, EnemyDuna, "EnemyDuna-86");
				break;
			}
			case 1720: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000167);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000182, EnemyDuna, "EnemyDuna-87");
				break;
			}
			case 1780: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000168);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000183, EnemyDuna, "EnemyDuna-88");
				break;
			}
			case 1840: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000169);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000184, EnemyDuna, "EnemyDuna-89");
				break;
			}
			case 1900: {
				EnemyEsperia* p90 = (EnemyEsperia*)obtainActorFromFactory(10000018);
				getSceneDirector()->addSubGroup(p90);
				orderActorToFactory(10000021, EnemyEsperia, "EnemyEsperia-91");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000170);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000185, EnemyDuna, "EnemyDuna-92");
				break;
			}
			case 1960: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000171);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000186, EnemyDuna, "EnemyDuna-93");
				break;
			}
			case 2020: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000172);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000187, EnemyDuna, "EnemyDuna-94");
				break;
			}
			case 2080: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000173);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000188, EnemyDuna, "EnemyDuna-95");
				break;
			}
			case 2140: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000174);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2200: {
				EnemyEsperia* p96 = (EnemyEsperia*)obtainActorFromFactory(10000019);
				getSceneDirector()->addSubGroup(p96);
				orderActorToFactory(10000022, EnemyEsperia, "EnemyEsperia-97");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000175);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2260: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000176);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2320: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000177);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2380: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000178);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2440: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000179);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2500: {
				EnemyEsperia* p98 = (EnemyEsperia*)obtainActorFromFactory(10000020);
				getSceneDirector()->addSubGroup(p98);
				orderActorToFactory(10000023, EnemyEsperia, "EnemyEsperia-99");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000180);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2560: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000181);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2620: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000182);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2680: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000183);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2740: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000184);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2800: {
				EnemyEsperia* p100 = (EnemyEsperia*)obtainActorFromFactory(10000021);
				getSceneDirector()->addSubGroup(p100);
				orderActorToFactory(10000024, EnemyEsperia, "EnemyEsperia-101");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000185);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2860: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000186);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2920: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000187);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2980: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000188);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 3100: {
				EnemyEsperia* p102 = (EnemyEsperia*)obtainActorFromFactory(10000022);
				getSceneDirector()->addSubGroup(p102);
				orderActorToFactory(10000025, EnemyEsperia, "EnemyEsperia-103");
				break;
			}
			case 3400: {
				EnemyEsperia* p104 = (EnemyEsperia*)obtainActorFromFactory(10000023);
				getSceneDirector()->addSubGroup(p104);
				orderActorToFactory(10000026, EnemyEsperia, "EnemyEsperia-105");
				break;
			}
			case 3700: {
				EnemyEsperia* p106 = (EnemyEsperia*)obtainActorFromFactory(10000024);
				getSceneDirector()->addSubGroup(p106);
				orderActorToFactory(10000027, EnemyEsperia, "EnemyEsperia-107");
				break;
			}
			case 4000: {
				EnemyEsperia* p108 = (EnemyEsperia*)obtainActorFromFactory(10000025);
				getSceneDirector()->addSubGroup(p108);
				orderActorToFactory(10000028, EnemyEsperia, "EnemyEsperia-109");
				break;
			}
			case 4100: {
				orderActorToFactory(10000129, FormationDelheid001, "FormationDelheid001-110");
				break;
			}
			case 4200: {
				orderActorToFactory(10000130, FormationDelheid001, "FormationDelheid001-111");
				break;
			}
			case 4300: {
				EnemyEsperia* p112 = (EnemyEsperia*)obtainActorFromFactory(10000026);
				getSceneDirector()->addSubGroup(p112);
				orderActorToFactory(10000029, EnemyEsperia, "EnemyEsperia-113");
				orderActorToFactory(10000131, FormationDelheid001, "FormationDelheid001-114");
				break;
			}
			case 4400: {
				orderActorToFactory(10000132, FormationDelheid001, "FormationDelheid001-115");
				break;
			}
			case 4500: {
				orderActorToFactory(10000133, FormationDelheid001, "FormationDelheid001-116");
				break;
			}
			case 4600: {
				EnemyEsperia* p117 = (EnemyEsperia*)obtainActorFromFactory(10000027);
				getSceneDirector()->addSubGroup(p117);
				orderActorToFactory(10000030, EnemyEsperia, "EnemyEsperia-118");
				orderActorToFactory(10000134, FormationDelheid001, "FormationDelheid001-119");
				break;
			}
			case 4700: {
				orderActorToFactory(10000135, FormationDelheid001, "FormationDelheid001-120");
				break;
			}
			case 4800: {
				orderActorToFactory(10000136, FormationDelheid001, "FormationDelheid001-121");
				break;
			}
			case 4900: {
				EnemyEsperia* p122 = (EnemyEsperia*)obtainActorFromFactory(10000028);
				getSceneDirector()->addSubGroup(p122);
				orderActorToFactory(10000031, EnemyEsperia, "EnemyEsperia-123");
				orderActorToFactory(10000137, FormationDelheid001, "FormationDelheid001-124");
				break;
			}
			case 5000: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000129);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(-40), D_ANG(0));
				break;
			}
			case 5100: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000130);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(-30), D_ANG(0));
				break;
			}
			case 5200: {
				EnemyEsperia* p125 = (EnemyEsperia*)obtainActorFromFactory(10000029);
				getSceneDirector()->addSubGroup(p125);
				orderActorToFactory(10000032, EnemyEsperia, "EnemyEsperia-126");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000131);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(-20), D_ANG(0));
				break;
			}
			case 5300: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000132);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(-10), D_ANG(0));
				break;
			}
			case 5400: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000133);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(  0), PX_C(500), D_ANG(0), D_ANG(0));
				break;
			}
			case 5500: {
				EnemyEsperia* p127 = (EnemyEsperia*)obtainActorFromFactory(10000030);
				getSceneDirector()->addSubGroup(p127);
				orderActorToFactory(10000033, EnemyEsperia, "EnemyEsperia-128");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000134);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(10), D_ANG(0));
				break;
			}
			case 5600: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000135);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(20), D_ANG(0));
				break;
			}
			case 5700: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000136);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(30), D_ANG(0));
				break;
			}
			case 5800: {
				EnemyEsperia* p129 = (EnemyEsperia*)obtainActorFromFactory(10000031);
				getSceneDirector()->addSubGroup(p129);
				orderActorToFactory(10000034, EnemyEsperia, "EnemyEsperia-130");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000137);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(40), D_ANG(0));
				break;
			}
			case 6100: {
				EnemyEsperia* p131 = (EnemyEsperia*)obtainActorFromFactory(10000032);
				getSceneDirector()->addSubGroup(p131);
				orderActorToFactory(10000035, EnemyEsperia, "EnemyEsperia-132");
				break;
			}
			case 6400: {
				EnemyEsperia* p133 = (EnemyEsperia*)obtainActorFromFactory(10000033);
				getSceneDirector()->addSubGroup(p133);
				orderActorToFactory(10000036, EnemyEsperia, "EnemyEsperia-134");
				break;
			}
			case 6700: {
				EnemyEsperia* p135 = (EnemyEsperia*)obtainActorFromFactory(10000034);
				getSceneDirector()->addSubGroup(p135);
				orderActorToFactory(10000037, EnemyEsperia, "EnemyEsperia-136");
				break;
			}
			case 7000: {
				EnemyEsperia* p137 = (EnemyEsperia*)obtainActorFromFactory(10000035);
				getSceneDirector()->addSubGroup(p137);
				orderActorToFactory(10000038, EnemyEsperia, "EnemyEsperia-138");
				break;
			}
			case 7300: {
				EnemyEsperia* p139 = (EnemyEsperia*)obtainActorFromFactory(10000036);
				getSceneDirector()->addSubGroup(p139);
				orderActorToFactory(10000039, EnemyEsperia, "EnemyEsperia-140");
				break;
			}
			case 7600: {
				EnemyEsperia* p141 = (EnemyEsperia*)obtainActorFromFactory(10000037);
				getSceneDirector()->addSubGroup(p141);
				orderActorToFactory(10000040, EnemyEsperia, "EnemyEsperia-142");
				break;
			}
			case 7900: {
				EnemyEsperia* p143 = (EnemyEsperia*)obtainActorFromFactory(10000038);
				getSceneDirector()->addSubGroup(p143);
				orderActorToFactory(10000041, EnemyEsperia, "EnemyEsperia-144");
				break;
			}
			case 8200: {
				EnemyEsperia* p145 = (EnemyEsperia*)obtainActorFromFactory(10000039);
				getSceneDirector()->addSubGroup(p145);
				orderActorToFactory(10000042, EnemyEsperia, "EnemyEsperia-146");
				break;
			}
			case 8500: {
				EnemyEsperia* p147 = (EnemyEsperia*)obtainActorFromFactory(10000040);
				getSceneDirector()->addSubGroup(p147);
				orderActorToFactory(10000043, EnemyEsperia, "EnemyEsperia-148");
				break;
			}
			case 8800: {
				EnemyEsperia* p149 = (EnemyEsperia*)obtainActorFromFactory(10000041);
				getSceneDirector()->addSubGroup(p149);
				orderActorToFactory(10000044, EnemyEsperia, "EnemyEsperia-150");
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-151");
				EnemyEsperia* p152 = (EnemyEsperia*)obtainActorFromFactory(10000042);
				getSceneDirector()->addSubGroup(p152);
				orderActorToFactory(10000045, EnemyEsperia, "EnemyEsperia-153");
				break;
			}
			case 9400: {
				EnemyEsperia* p154 = (EnemyEsperia*)obtainActorFromFactory(10000043);
				getSceneDirector()->addSubGroup(p154);
				orderActorToFactory(10000046, EnemyEsperia, "EnemyEsperia-155");
				break;
			}
			case 9700: {
				EnemyEsperia* p156 = (EnemyEsperia*)obtainActorFromFactory(10000044);
				getSceneDirector()->addSubGroup(p156);
				orderActorToFactory(10000047, EnemyEsperia, "EnemyEsperia-157");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				EnemyEsperia* p158 = (EnemyEsperia*)obtainActorFromFactory(10000045);
				getSceneDirector()->addSubGroup(p158);
				orderActorToFactory(10000048, EnemyEsperia, "EnemyEsperia-159");
				break;
			}
			case 10300: {
				orderActorToFactory(10000006, EnemyErmione, "EnemyErmione-160");
				EnemyEsperia* p161 = (EnemyEsperia*)obtainActorFromFactory(10000046);
				getSceneDirector()->addSubGroup(p161);
				orderActorToFactory(10000049, EnemyEsperia, "EnemyEsperia-162");
				break;
			}
			case 10600: {
				EnemyEsperia* p163 = (EnemyEsperia*)obtainActorFromFactory(10000047);
				getSceneDirector()->addSubGroup(p163);
				orderActorToFactory(10000050, EnemyEsperia, "EnemyEsperia-164");
				break;
			}
			case 10900: {
				EnemyEsperia* p165 = (EnemyEsperia*)obtainActorFromFactory(10000048);
				getSceneDirector()->addSubGroup(p165);
				orderActorToFactory(10000051, EnemyEsperia, "EnemyEsperia-166");
				break;
			}
			case 11200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				EnemyEsperia* p167 = (EnemyEsperia*)obtainActorFromFactory(10000049);
				getSceneDirector()->addSubGroup(p167);
				orderActorToFactory(10000052, EnemyEsperia, "EnemyEsperia-168");
				break;
			}
			case 11500: {
				EnemyEsperia* p169 = (EnemyEsperia*)obtainActorFromFactory(10000050);
				getSceneDirector()->addSubGroup(p169);
				orderActorToFactory(10000053, EnemyEsperia, "EnemyEsperia-170");
				break;
			}
			case 11800: {
				EnemyEsperia* p171 = (EnemyEsperia*)obtainActorFromFactory(10000051);
				getSceneDirector()->addSubGroup(p171);
				orderActorToFactory(10000054, EnemyEsperia, "EnemyEsperia-172");
				break;
			}
			case 12100: {
				EnemyEsperia* p173 = (EnemyEsperia*)obtainActorFromFactory(10000052);
				getSceneDirector()->addSubGroup(p173);
				orderActorToFactory(10000055, EnemyEsperia, "EnemyEsperia-174");
				break;
			}
			case 12400: {
				EnemyEsperia* p175 = (EnemyEsperia*)obtainActorFromFactory(10000053);
				getSceneDirector()->addSubGroup(p175);
				orderActorToFactory(10000056, EnemyEsperia, "EnemyEsperia-176");
				break;
			}
			case 12700: {
				EnemyEsperia* p177 = (EnemyEsperia*)obtainActorFromFactory(10000054);
				getSceneDirector()->addSubGroup(p177);
				orderActorToFactory(10000057, EnemyEsperia, "EnemyEsperia-178");
				break;
			}
			case 13000: {
				EnemyEsperia* p179 = (EnemyEsperia*)obtainActorFromFactory(10000055);
				getSceneDirector()->addSubGroup(p179);
				orderActorToFactory(10000058, EnemyEsperia, "EnemyEsperia-180");
				break;
			}
			case 13300: {
				EnemyEsperia* p181 = (EnemyEsperia*)obtainActorFromFactory(10000056);
				getSceneDirector()->addSubGroup(p181);
				orderActorToFactory(10000059, EnemyEsperia, "EnemyEsperia-182");
				break;
			}
			case 13600: {
				EnemyEsperia* p183 = (EnemyEsperia*)obtainActorFromFactory(10000057);
				getSceneDirector()->addSubGroup(p183);
				orderActorToFactory(10000060, EnemyEsperia, "EnemyEsperia-184");
				break;
			}
			case 13900: {
				EnemyEsperia* p185 = (EnemyEsperia*)obtainActorFromFactory(10000058);
				getSceneDirector()->addSubGroup(p185);
				orderActorToFactory(10000061, EnemyEsperia, "EnemyEsperia-186");
				break;
			}
			case 14200: {
				EnemyEsperia* p187 = (EnemyEsperia*)obtainActorFromFactory(10000059);
				getSceneDirector()->addSubGroup(p187);
				orderActorToFactory(10000062, EnemyEsperia, "EnemyEsperia-188");
				break;
			}
			case 14500: {
				EnemyEsperia* p189 = (EnemyEsperia*)obtainActorFromFactory(10000060);
				getSceneDirector()->addSubGroup(p189);
				orderActorToFactory(10000063, EnemyEsperia, "EnemyEsperia-190");
				break;
			}
			case 14800: {
				EnemyEsperia* p191 = (EnemyEsperia*)obtainActorFromFactory(10000061);
				getSceneDirector()->addSubGroup(p191);
				orderActorToFactory(10000064, EnemyEsperia, "EnemyEsperia-192");
				break;
			}
			case 15100: {
				EnemyEsperia* p193 = (EnemyEsperia*)obtainActorFromFactory(10000062);
				getSceneDirector()->addSubGroup(p193);
				orderActorToFactory(10000065, EnemyEsperia, "EnemyEsperia-194");
				break;
			}
			case 15400: {
				EnemyEsperia* p195 = (EnemyEsperia*)obtainActorFromFactory(10000063);
				getSceneDirector()->addSubGroup(p195);
				orderActorToFactory(10000066, EnemyEsperia, "EnemyEsperia-196");
				break;
			}
			case 15700: {
				EnemyEsperia* p197 = (EnemyEsperia*)obtainActorFromFactory(10000064);
				getSceneDirector()->addSubGroup(p197);
				orderActorToFactory(10000067, EnemyEsperia, "EnemyEsperia-198");
				break;
			}
			case 16000: {
				EnemyEsperia* p199 = (EnemyEsperia*)obtainActorFromFactory(10000065);
				getSceneDirector()->addSubGroup(p199);
				orderActorToFactory(10000068, EnemyEsperia, "EnemyEsperia-200");
				break;
			}
			case 16300: {
				EnemyEsperia* p201 = (EnemyEsperia*)obtainActorFromFactory(10000066);
				getSceneDirector()->addSubGroup(p201);
				orderActorToFactory(10000069, EnemyEsperia, "EnemyEsperia-202");
				break;
			}
			case 16600: {
				EnemyEsperia* p203 = (EnemyEsperia*)obtainActorFromFactory(10000067);
				getSceneDirector()->addSubGroup(p203);
				orderActorToFactory(10000070, EnemyEsperia, "EnemyEsperia-204");
				break;
			}
			case 16900: {
				EnemyEsperia* p205 = (EnemyEsperia*)obtainActorFromFactory(10000068);
				getSceneDirector()->addSubGroup(p205);
				orderActorToFactory(10000071, EnemyEsperia, "EnemyEsperia-206");
				break;
			}
			case 17200: {
				EnemyEsperia* p207 = (EnemyEsperia*)obtainActorFromFactory(10000069);
				getSceneDirector()->addSubGroup(p207);
				orderActorToFactory(10000072, EnemyEsperia, "EnemyEsperia-208");
				break;
			}
			case 17500: {
				EnemyEsperia* p209 = (EnemyEsperia*)obtainActorFromFactory(10000070);
				getSceneDirector()->addSubGroup(p209);
				orderActorToFactory(10000073, EnemyEsperia, "EnemyEsperia-210");
				break;
			}
			case 17800: {
				EnemyEsperia* p211 = (EnemyEsperia*)obtainActorFromFactory(10000071);
				getSceneDirector()->addSubGroup(p211);
				orderActorToFactory(10000074, EnemyEsperia, "EnemyEsperia-212");
				break;
			}
			case 18100: {
				EnemyEsperia* p213 = (EnemyEsperia*)obtainActorFromFactory(10000072);
				getSceneDirector()->addSubGroup(p213);
				orderActorToFactory(10000075, EnemyEsperia, "EnemyEsperia-214");
				break;
			}
			case 18400: {
				EnemyEsperia* p215 = (EnemyEsperia*)obtainActorFromFactory(10000073);
				getSceneDirector()->addSubGroup(p215);
				orderActorToFactory(10000076, EnemyEsperia, "EnemyEsperia-216");
				break;
			}
			case 18700: {
				EnemyEsperia* p217 = (EnemyEsperia*)obtainActorFromFactory(10000074);
				getSceneDirector()->addSubGroup(p217);
				orderActorToFactory(10000077, EnemyEsperia, "EnemyEsperia-218");
				break;
			}
			case 19000: {
				EnemyEsperia* p219 = (EnemyEsperia*)obtainActorFromFactory(10000075);
				getSceneDirector()->addSubGroup(p219);
				orderActorToFactory(10000078, EnemyEsperia, "EnemyEsperia-220");
				break;
			}
			case 19100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-221");
				break;
			}
			case 19300: {
				EnemyEsperia* p222 = (EnemyEsperia*)obtainActorFromFactory(10000076);
				getSceneDirector()->addSubGroup(p222);
				orderActorToFactory(10000079, EnemyEsperia, "EnemyEsperia-223");
				break;
			}
			case 19600: {
				EnemyEsperia* p224 = (EnemyEsperia*)obtainActorFromFactory(10000077);
				getSceneDirector()->addSubGroup(p224);
				orderActorToFactory(10000080, EnemyEsperia, "EnemyEsperia-225");
				break;
			}
			case 19900: {
				EnemyEsperia* p226 = (EnemyEsperia*)obtainActorFromFactory(10000078);
				getSceneDirector()->addSubGroup(p226);
				orderActorToFactory(10000081, EnemyEsperia, "EnemyEsperia-227");
				break;
			}
			case 20000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				break;
			}
			case 20200: {
				EnemyEsperia* p228 = (EnemyEsperia*)obtainActorFromFactory(10000079);
				getSceneDirector()->addSubGroup(p228);
				orderActorToFactory(10000082, EnemyEsperia, "EnemyEsperia-229");
				break;
			}
			case 20300: {
				orderActorToFactory(10000007, EnemyErmione, "EnemyErmione-230");
				break;
			}
			case 20500: {
				EnemyEsperia* p231 = (EnemyEsperia*)obtainActorFromFactory(10000080);
				getSceneDirector()->addSubGroup(p231);
				orderActorToFactory(10000083, EnemyEsperia, "EnemyEsperia-232");
				break;
			}
			case 20800: {
				EnemyEsperia* p233 = (EnemyEsperia*)obtainActorFromFactory(10000081);
				getSceneDirector()->addSubGroup(p233);
				orderActorToFactory(10000084, EnemyEsperia, "EnemyEsperia-234");
				break;
			}
			case 21100: {
				EnemyEsperia* p235 = (EnemyEsperia*)obtainActorFromFactory(10000082);
				getSceneDirector()->addSubGroup(p235);
				orderActorToFactory(10000085, EnemyEsperia, "EnemyEsperia-236");
				break;
			}
			case 21200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 21400: {
				EnemyEsperia* p237 = (EnemyEsperia*)obtainActorFromFactory(10000083);
				getSceneDirector()->addSubGroup(p237);
				orderActorToFactory(10000086, EnemyEsperia, "EnemyEsperia-238");
				break;
			}
			case 21700: {
				EnemyEsperia* p239 = (EnemyEsperia*)obtainActorFromFactory(10000084);
				getSceneDirector()->addSubGroup(p239);
				orderActorToFactory(10000087, EnemyEsperia, "EnemyEsperia-240");
				break;
			}
			case 22000: {
				EnemyEsperia* p241 = (EnemyEsperia*)obtainActorFromFactory(10000085);
				getSceneDirector()->addSubGroup(p241);
				orderActorToFactory(10000088, EnemyEsperia, "EnemyEsperia-242");
				break;
			}
			case 22300: {
				EnemyEsperia* p243 = (EnemyEsperia*)obtainActorFromFactory(10000086);
				getSceneDirector()->addSubGroup(p243);
				orderActorToFactory(10000089, EnemyEsperia, "EnemyEsperia-244");
				break;
			}
			case 22600: {
				EnemyEsperia* p245 = (EnemyEsperia*)obtainActorFromFactory(10000087);
				getSceneDirector()->addSubGroup(p245);
				orderActorToFactory(10000090, EnemyEsperia, "EnemyEsperia-246");
				break;
			}
			case 22900: {
				EnemyEsperia* p247 = (EnemyEsperia*)obtainActorFromFactory(10000088);
				getSceneDirector()->addSubGroup(p247);
				orderActorToFactory(10000091, EnemyEsperia, "EnemyEsperia-248");
				break;
			}
			case 23200: {
				EnemyEsperia* p249 = (EnemyEsperia*)obtainActorFromFactory(10000089);
				getSceneDirector()->addSubGroup(p249);
				orderActorToFactory(10000092, EnemyEsperia, "EnemyEsperia-250");
				break;
			}
			case 23500: {
				EnemyEsperia* p251 = (EnemyEsperia*)obtainActorFromFactory(10000090);
				getSceneDirector()->addSubGroup(p251);
				orderActorToFactory(10000093, EnemyEsperia, "EnemyEsperia-252");
				break;
			}
			case 23800: {
				EnemyEsperia* p253 = (EnemyEsperia*)obtainActorFromFactory(10000091);
				getSceneDirector()->addSubGroup(p253);
				orderActorToFactory(10000094, EnemyEsperia, "EnemyEsperia-254");
				break;
			}
			case 24100: {
				EnemyEsperia* p255 = (EnemyEsperia*)obtainActorFromFactory(10000092);
				getSceneDirector()->addSubGroup(p255);
				orderActorToFactory(10000095, EnemyEsperia, "EnemyEsperia-256");
				break;
			}
			case 24400: {
				EnemyEsperia* p257 = (EnemyEsperia*)obtainActorFromFactory(10000093);
				getSceneDirector()->addSubGroup(p257);
				orderActorToFactory(10000096, EnemyEsperia, "EnemyEsperia-258");
				break;
			}
			case 24700: {
				EnemyEsperia* p259 = (EnemyEsperia*)obtainActorFromFactory(10000094);
				getSceneDirector()->addSubGroup(p259);
				orderActorToFactory(10000097, EnemyEsperia, "EnemyEsperia-260");
				break;
			}
			case 25000: {
				EnemyEsperia* p261 = (EnemyEsperia*)obtainActorFromFactory(10000095);
				getSceneDirector()->addSubGroup(p261);
				orderActorToFactory(10000098, EnemyEsperia, "EnemyEsperia-262");
				break;
			}
			case 25300: {
				EnemyEsperia* p263 = (EnemyEsperia*)obtainActorFromFactory(10000096);
				getSceneDirector()->addSubGroup(p263);
				orderActorToFactory(10000099, EnemyEsperia, "EnemyEsperia-264");
				break;
			}
			case 25600: {
				EnemyEsperia* p265 = (EnemyEsperia*)obtainActorFromFactory(10000097);
				getSceneDirector()->addSubGroup(p265);
				orderActorToFactory(10000100, EnemyEsperia, "EnemyEsperia-266");
				break;
			}
			case 25900: {
				EnemyEsperia* p267 = (EnemyEsperia*)obtainActorFromFactory(10000098);
				getSceneDirector()->addSubGroup(p267);
				orderActorToFactory(10000101, EnemyEsperia, "EnemyEsperia-268");
				break;
			}
			case 26200: {
				EnemyEsperia* p269 = (EnemyEsperia*)obtainActorFromFactory(10000099);
				getSceneDirector()->addSubGroup(p269);
				orderActorToFactory(10000102, EnemyEsperia, "EnemyEsperia-270");
				break;
			}
			case 26500: {
				EnemyEsperia* p271 = (EnemyEsperia*)obtainActorFromFactory(10000100);
				getSceneDirector()->addSubGroup(p271);
				orderActorToFactory(10000103, EnemyEsperia, "EnemyEsperia-272");
				break;
			}
			case 26800: {
				EnemyEsperia* p273 = (EnemyEsperia*)obtainActorFromFactory(10000101);
				getSceneDirector()->addSubGroup(p273);
				orderActorToFactory(10000104, EnemyEsperia, "EnemyEsperia-274");
				break;
			}
			case 27100: {
				EnemyEsperia* p275 = (EnemyEsperia*)obtainActorFromFactory(10000102);
				getSceneDirector()->addSubGroup(p275);
				orderActorToFactory(10000105, EnemyEsperia, "EnemyEsperia-276");
				break;
			}
			case 27400: {
				EnemyEsperia* p277 = (EnemyEsperia*)obtainActorFromFactory(10000103);
				getSceneDirector()->addSubGroup(p277);
				orderActorToFactory(10000106, EnemyEsperia, "EnemyEsperia-278");
				break;
			}
			case 27700: {
				EnemyEsperia* p279 = (EnemyEsperia*)obtainActorFromFactory(10000104);
				getSceneDirector()->addSubGroup(p279);
				orderActorToFactory(10000107, EnemyEsperia, "EnemyEsperia-280");
				break;
			}
			case 28000: {
				EnemyEsperia* p281 = (EnemyEsperia*)obtainActorFromFactory(10000105);
				getSceneDirector()->addSubGroup(p281);
				orderActorToFactory(10000108, EnemyEsperia, "EnemyEsperia-282");
				break;
			}
			case 28300: {
				EnemyEsperia* p283 = (EnemyEsperia*)obtainActorFromFactory(10000106);
				getSceneDirector()->addSubGroup(p283);
				orderActorToFactory(10000109, EnemyEsperia, "EnemyEsperia-284");
				break;
			}
			case 28600: {
				EnemyEsperia* p285 = (EnemyEsperia*)obtainActorFromFactory(10000107);
				getSceneDirector()->addSubGroup(p285);
				orderActorToFactory(10000110, EnemyEsperia, "EnemyEsperia-286");
				break;
			}
			case 28900: {
				EnemyEsperia* p287 = (EnemyEsperia*)obtainActorFromFactory(10000108);
				getSceneDirector()->addSubGroup(p287);
				orderActorToFactory(10000111, EnemyEsperia, "EnemyEsperia-288");
				break;
			}
			case 29100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-289");
				break;
			}
			case 29200: {
				EnemyEsperia* p290 = (EnemyEsperia*)obtainActorFromFactory(10000109);
				getSceneDirector()->addSubGroup(p290);
				break;
			}
			case 29500: {
				EnemyEsperia* p291 = (EnemyEsperia*)obtainActorFromFactory(10000110);
				getSceneDirector()->addSubGroup(p291);
				break;
			}
			case 29800: {
				EnemyEsperia* p292 = (EnemyEsperia*)obtainActorFromFactory(10000111);
				getSceneDirector()->addSubGroup(p292);
				break;
			}
			case 30000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 170-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case PROG_FAINAL: {
            if (_pProg->isJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("STG01Climax_終焉のStage01PartController::PROG_FAINALきた");
            }

            if (_pProg->getFrameInProgress() == 60) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STG01_CTRLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void Stage01PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01PARTCONTROLLER_ENDINGを投げる");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        _pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
