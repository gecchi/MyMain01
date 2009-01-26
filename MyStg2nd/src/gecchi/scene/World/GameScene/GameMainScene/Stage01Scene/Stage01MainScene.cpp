#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Stage01MainScene::Stage01MainScene(string prm_name) : GgafDx9LibStg::DefaultScene(prm_name) {

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,100,180,200,260,300,340,400,420,500,600,670,690,740,780,810,870,880,950,960,1100,1160,1180,1220,1260,1280,1340,1400,1420,1460,1500,1600,1650,1670,1700,1740,1750,1800,1810,1850,1880,1900,1950,2000,2100,2140,2160,2180,2220,2260,2280,2300,2340,2380,2400,2420,2460,2500,2600,2630,2650,2660,2690,2700,2720,2750,2780,2800,2810,2840,2850,2870,2900,2930,2950,2960,2990,3000,3100,3120,3140,3160,3180,3200,3220,3240,3260,3280,3300,3320,3340,3360,3380,3400,3420,3440,3460,3480,3500,3600,3630,3660,3690,3720,3750,3780,3810,3840,3870,3900,3930,3960,3990,4100,4120,4140,4160,4180,4200,4220,4240,4260,4280,4300,4320,4340,4360,4380,4400,4420,4440,4460,4480,4500};
	_paFrame_NextEvent = new DWORD[134];
	for (int i = 0; i < 134; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(11077100, EnemyCeres, "Ceres_1", "Ceres");
	orderActorToFactory(11077200, EnemyCeres, "Ceres_2", "Ceres");
	orderActorToFactory(11077300, EnemyCeres, "Ceres_3", "Ceres");
	orderActorToFactory(11077400, EnemyCeres, "Ceres_4", "Ceres");
	orderActorToFactory(11077500, EnemyCeres, "Ceres_5", "Ceres");
	orderActorToFactory(11087600, EnemyCeres, "Ceres_6", "Ceres");
	orderActorToFactory(11087690, EnemyCeres, "Ceres_7", "Ceres");
	orderActorToFactory(11087780, EnemyCeres, "Ceres_8", "Ceres");
	orderActorToFactory(11087870, EnemyCeres, "Ceres_9", "Ceres");
	orderActorToFactory(11087960, EnemyCeres, "Ceres_10", "Ceres");
	// gen01 end

	stopImmediately(); //GameMainSceneが解除してくれる
}

void Stage01MainScene::initialize() {
}

void Stage01MainScene::processBehavior() {
	// 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
	// gen02 start
	if (_dwFrame == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_dwFrame) {
			case 1:
				break;
			case 100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077100);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -400000;
				pActor->_iBeginVelocity = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(110971100, EnemyCeres, "Ceres_11", "Ceres");
				break;
			case 180:
				orderActorToFactory(110971180, EnemyCeres, "Ceres_12", "Ceres");
				break;
			case 200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077200);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -400000;
				pActor->_iBeginVelocity = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 260:
				orderActorToFactory(110971260, EnemyCeres, "Ceres_13", "Ceres");
				break;
			case 300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077300);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -400000;
				pActor->_iBeginVelocity = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 340:
				orderActorToFactory(110971340, EnemyCeres, "Ceres_14", "Ceres");
				break;
			case 400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077400);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -400000;
				pActor->_iBeginVelocity = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 420:
				orderActorToFactory(110971420, EnemyCeres, "Ceres_15", "Ceres");
				break;
			case 500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077500);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -400000;
				pActor->_iBeginVelocity = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(110971500, EnemyCeres, "Ceres_16", "Ceres");
				break;
			case 600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087600);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_iBeginVelocity = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111071600, EnemyCeres, "Ceres_17", "Ceres");
				break;
			case 670:
				orderActorToFactory(111071670, EnemyCeres, "Ceres_18", "Ceres");
				break;
			case 690:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087690);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_iBeginVelocity = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 740:
				orderActorToFactory(111071740, EnemyCeres, "Ceres_19", "Ceres");
				break;
			case 780:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087780);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_iBeginVelocity = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 810:
				orderActorToFactory(111071810, EnemyCeres, "Ceres_20", "Ceres");
				break;
			case 870:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087870);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_iBeginVelocity = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 880:
				orderActorToFactory(111071880, EnemyCeres, "Ceres_21", "Ceres");
				break;
			case 950:
				orderActorToFactory(111071950, EnemyCeres, "Ceres_22", "Ceres");
				break;
			case 960:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087960);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_iBeginVelocity = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971100);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_iBeginVelocity = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111172100, EnemyCeres, "Ceres_23", "Ceres");
				break;
			case 1160:
				orderActorToFactory(111172160, EnemyCeres, "Ceres_24", "Ceres");
				break;
			case 1180:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971180);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_iBeginVelocity = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1220:
				orderActorToFactory(111172220, EnemyCeres, "Ceres_25", "Ceres");
				break;
			case 1260:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971260);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_iBeginVelocity = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1280:
				orderActorToFactory(111172280, EnemyCeres, "Ceres_26", "Ceres");
				break;
			case 1340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971340);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_iBeginVelocity = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111172340, EnemyCeres, "Ceres_27", "Ceres");
				break;
			case 1400:
				orderActorToFactory(111172400, EnemyCeres, "Ceres_28", "Ceres");
				break;
			case 1420:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971420);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_iBeginVelocity = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1460:
				orderActorToFactory(111172460, EnemyCeres, "Ceres_29", "Ceres");
				break;
			case 1500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971500);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_iBeginVelocity = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071600);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -100000;
				pActor->_iBeginVelocity = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111272600, EnemyCeres, "Ceres_30", "Ceres");
				break;
			case 1650:
				orderActorToFactory(111272650, EnemyCeres, "Ceres_31", "Ceres");
				break;
			case 1670:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071670);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -100000;
				pActor->_iBeginVelocity = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1700:
				orderActorToFactory(111272700, EnemyCeres, "Ceres_32", "Ceres");
				break;
			case 1740:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071740);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -100000;
				pActor->_iBeginVelocity = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1750:
				orderActorToFactory(111272750, EnemyCeres, "Ceres_33", "Ceres");
				break;
			case 1800:
				orderActorToFactory(111272800, EnemyCeres, "Ceres_34", "Ceres");
				break;
			case 1810:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071810);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -100000;
				pActor->_iBeginVelocity = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1850:
				orderActorToFactory(111272850, EnemyCeres, "Ceres_35", "Ceres");
				break;
			case 1880:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071880);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -100000;
				pActor->_iBeginVelocity = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1900:
				orderActorToFactory(111272900, EnemyCeres, "Ceres_36", "Ceres");
				break;
			case 1950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071950);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -100000;
				pActor->_iBeginVelocity = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111272950, EnemyCeres, "Ceres_37", "Ceres");
				break;
			case 2000:
				orderActorToFactory(111273000, EnemyCeres, "Ceres_38", "Ceres");
				break;
			case 2100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111172100);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_iBeginVelocity = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111373100, EnemyCeres, "Ceres_39", "Ceres");
				break;
			case 2140:
				orderActorToFactory(111373140, EnemyCeres, "Ceres_40", "Ceres");
				break;
			case 2160:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111172160);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_iBeginVelocity = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2180:
				orderActorToFactory(111373180, EnemyCeres, "Ceres_41", "Ceres");
				break;
			case 2220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111172220);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_iBeginVelocity = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111373220, EnemyCeres, "Ceres_42", "Ceres");
				break;
			case 2260:
				orderActorToFactory(111373260, EnemyCeres, "Ceres_43", "Ceres");
				break;
			case 2280:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111172280);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_iBeginVelocity = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2300:
				orderActorToFactory(111373300, EnemyCeres, "Ceres_44", "Ceres");
				break;
			case 2340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111172340);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_iBeginVelocity = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111373340, EnemyCeres, "Ceres_45", "Ceres");
				break;
			case 2380:
				orderActorToFactory(111373380, EnemyCeres, "Ceres_46", "Ceres");
				break;
			case 2400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111172400);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_iBeginVelocity = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2420:
				orderActorToFactory(111373420, EnemyCeres, "Ceres_47", "Ceres");
				break;
			case 2460:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111172460);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_iBeginVelocity = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111373460, EnemyCeres, "Ceres_48", "Ceres");
				break;
			case 2500:
				orderActorToFactory(111373500, EnemyCeres, "Ceres_49", "Ceres");
				break;
			case 2600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272600);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 100000;
				pActor->_iBeginVelocity = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111473600, EnemyCeres, "Ceres_50", "Ceres");
				break;
			case 2630:
				orderActorToFactory(111473630, EnemyCeres, "Ceres_51", "Ceres");
				break;
			case 2650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272650);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 100000;
				pActor->_iBeginVelocity = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2660:
				orderActorToFactory(111473660, EnemyCeres, "Ceres_52", "Ceres");
				break;
			case 2690:
				orderActorToFactory(111473690, EnemyCeres, "Ceres_53", "Ceres");
				break;
			case 2700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272700);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 100000;
				pActor->_iBeginVelocity = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2720:
				orderActorToFactory(111473720, EnemyCeres, "Ceres_54", "Ceres");
				break;
			case 2750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272750);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 100000;
				pActor->_iBeginVelocity = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111473750, EnemyCeres, "Ceres_55", "Ceres");
				break;
			case 2780:
				orderActorToFactory(111473780, EnemyCeres, "Ceres_56", "Ceres");
				break;
			case 2800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272800);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 100000;
				pActor->_iBeginVelocity = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2810:
				orderActorToFactory(111473810, EnemyCeres, "Ceres_57", "Ceres");
				break;
			case 2840:
				orderActorToFactory(111473840, EnemyCeres, "Ceres_58", "Ceres");
				break;
			case 2850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272850);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 100000;
				pActor->_iBeginVelocity = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2870:
				orderActorToFactory(111473870, EnemyCeres, "Ceres_59", "Ceres");
				break;
			case 2900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272900);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 100000;
				pActor->_iBeginVelocity = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111473900, EnemyCeres, "Ceres_60", "Ceres");
				break;
			case 2930:
				orderActorToFactory(111473930, EnemyCeres, "Ceres_61", "Ceres");
				break;
			case 2950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272950);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 100000;
				pActor->_iBeginVelocity = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2960:
				orderActorToFactory(111473960, EnemyCeres, "Ceres_62", "Ceres");
				break;
			case 2990:
				orderActorToFactory(111473990, EnemyCeres, "Ceres_63", "Ceres");
				break;
			case 3000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111273000);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 100000;
				pActor->_iBeginVelocity = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111373100);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_iBeginVelocity = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111574100, EnemyCeres, "Ceres_64", "Ceres");
				break;
			case 3120:
				orderActorToFactory(111574120, EnemyCeres, "Ceres_65", "Ceres");
				break;
			case 3140:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111373140);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_iBeginVelocity = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111574140, EnemyCeres, "Ceres_66", "Ceres");
				break;
			case 3160:
				orderActorToFactory(111574160, EnemyCeres, "Ceres_67", "Ceres");
				break;
			case 3180:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111373180);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_iBeginVelocity = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111574180, EnemyCeres, "Ceres_68", "Ceres");
				break;
			case 3200:
				orderActorToFactory(111574200, EnemyCeres, "Ceres_69", "Ceres");
				break;
			case 3220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111373220);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_iBeginVelocity = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111574220, EnemyCeres, "Ceres_70", "Ceres");
				break;
			case 3240:
				orderActorToFactory(111574240, EnemyCeres, "Ceres_71", "Ceres");
				break;
			case 3260:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111373260);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_iBeginVelocity = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111574260, EnemyCeres, "Ceres_72", "Ceres");
				break;
			case 3280:
				orderActorToFactory(111574280, EnemyCeres, "Ceres_73", "Ceres");
				break;
			case 3300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111373300);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_iBeginVelocity = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111574300, EnemyCeres, "Ceres_74", "Ceres");
				break;
			case 3320:
				orderActorToFactory(111574320, EnemyCeres, "Ceres_75", "Ceres");
				break;
			case 3340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111373340);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_iBeginVelocity = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111574340, EnemyCeres, "Ceres_76", "Ceres");
				break;
			case 3360:
				orderActorToFactory(111574360, EnemyCeres, "Ceres_77", "Ceres");
				break;
			case 3380:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111373380);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_iBeginVelocity = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111574380, EnemyCeres, "Ceres_78", "Ceres");
				break;
			case 3400:
				orderActorToFactory(111574400, EnemyCeres, "Ceres_79", "Ceres");
				break;
			case 3420:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111373420);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_iBeginVelocity = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111574420, EnemyCeres, "Ceres_80", "Ceres");
				break;
			case 3440:
				orderActorToFactory(111574440, EnemyCeres, "Ceres_81", "Ceres");
				break;
			case 3460:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111373460);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_iBeginVelocity = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111574460, EnemyCeres, "Ceres_82", "Ceres");
				break;
			case 3480:
				orderActorToFactory(111574480, EnemyCeres, "Ceres_83", "Ceres");
				break;
			case 3500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111373500);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_iBeginVelocity = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(111574500, EnemyCeres, "Ceres_84", "Ceres");
				break;
			case 3600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473600);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3630:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473630);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3660:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473660);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3690:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473690);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3720:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473720);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473750);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3780:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473780);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3810:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473810);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3840:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473840);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3870:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473870);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473900);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3930:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473930);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3960:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473960);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3990:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111473990);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_iBeginVelocity = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574100);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4120:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574120);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4140:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574140);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4160:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574160);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4180:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574180);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574200);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574220);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4240:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574240);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4260:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574260);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4280:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574280);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574300);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4320:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574320);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574340);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4360:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574360);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4380:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574380);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574400);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4420:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574420);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4440:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574440);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4460:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574460);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4480:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574480);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111574500);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 400000;
				pActor->_iBeginVelocity = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
	// gen02 end

	if (_dwFrame == 2) {

		_TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
		// 共通シーンを配下に移動
		addSubLast(GameGlobal::_pSceneCommon->tear());

	}

}

void Stage01MainScene::processFinal() {
//	if (_dwFrame == 1) {
//		_TRACE_("Stage01MainScene::processFinally 私はいきなり停止します。GameMainSceneが解除してくれるはずー");
//		this->declareStop(); //GameMainSceneが解除してくれる
//	}
}

Stage01MainScene::~Stage01MainScene() {
}
