#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_02::Stage01_02(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_02";
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,40,100,160,220,280,340,400,460,520,580,640,700,760,820,880,940,1000,1060,1120,1180,1240,1300,1360,1420,1480,1540,1600,1660,1720,1780,1840,1900,1960,2020,2080,2140,2200,2260,2320,2380,2440,2500,2560,2620,2680,2740,2800,2860,2920,2980,3040,3100,3160,3220,3280,3340,3400,3460,3520,3580,3640,3700,3760,3820,3880,3940,4000,4060,4120,4180,4240,4300,4360,4420,4480,4540,4600,4660,4720,4780,4840,4900,4960,10000};
	_paFrame_NextEvent = new frame[85];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 85;
	orderActorToFactory(40000000, EnemyMetis, "Metis_1");
	orderActorToFactory(40000001, EnemyMetis, "Metis_2");
	orderActorToFactory(40000002, EnemyMetis, "Metis_3");
	orderActorToFactory(40000003, EnemyMetis, "Metis_4");
	orderActorToFactory(40000004, EnemyMetis, "Metis_5");
	orderActorToFactory(40000005, EnemyMetis, "Metis_6");
	orderActorToFactory(40000006, EnemyMetis, "Metis_7");
	orderActorToFactory(40000007, EnemyMetis, "Metis_8");
	orderActorToFactory(40000008, EnemyMetis, "Metis_9");
	orderActorToFactory(40000009, EnemyMetis, "Metis_10");
	orderActorToFactory(40000010, EnemyMetis, "Metis_11");
	orderActorToFactory(40000011, EnemyMetis, "Metis_12");
	orderActorToFactory(40000012, EnemyMetis, "Metis_13");
	orderActorToFactory(40000013, EnemyMetis, "Metis_14");
    // gen01 end
}

void Stage01_02::initialize() {

}

void Stage01_02::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 40: {
				orderActorToFactory(40000014, EnemyMetis, "Metis_15");
				break;
			}
			case 100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000000);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000015, EnemyMetis, "Metis_16");
				orderActorToFactory(40000082, VarietyTorus001, "VarietyTorus001_17");
				break;
			}
			case 160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000001);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000016, EnemyMetis, "Metis_18");
				break;
			}
			case 220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000002);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000017, EnemyMetis, "Metis_19");
				break;
			}
			case 280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000003);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000018, EnemyMetis, "Metis_20");
				break;
			}
			case 340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000004);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000019, EnemyMetis, "Metis_21");
				break;
			}
			case 400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000005);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000020, EnemyMetis, "Metis_22");
				break;
			}
			case 460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000006);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000021, EnemyMetis, "Metis_23");
				break;
			}
			case 520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000007);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000022, EnemyMetis, "Metis_24");
				break;
			}
			case 580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000008);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000023, EnemyMetis, "Metis_25");
				break;
			}
			case 640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000009);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000024, EnemyMetis, "Metis_26");
				break;
			}
			case 700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000010);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000025, EnemyMetis, "Metis_27");
				break;
			}
			case 760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000011);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000026, EnemyMetis, "Metis_28");
				break;
			}
			case 820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000012);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000027, EnemyMetis, "Metis_29");
				break;
			}
			case 880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000013);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000028, EnemyMetis, "Metis_30");
				break;
			}
			case 940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000014);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000029, EnemyMetis, "Metis_31");
				break;
			}
			case 1000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000015);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000030, EnemyMetis, "Metis_32");
				VarietyTorus001* pTorus = (VarietyTorus001*)obtainActorFromFactory(40000082);
				getDirector()->addSubGroup(pTorus);
				break;
			}
			case 1060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000016);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000031, EnemyMetis, "Metis_33");
				break;
			}
			case 1120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000017);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000032, EnemyMetis, "Metis_34");
				break;
			}
			case 1180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000018);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000033, EnemyMetis, "Metis_35");
				break;
			}
			case 1240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000019);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000034, EnemyMetis, "Metis_36");
				break;
			}
			case 1300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000020);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000035, EnemyMetis, "Metis_37");
				break;
			}
			case 1360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000021);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000036, EnemyMetis, "Metis_38");
				break;
			}
			case 1420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000022);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000037, EnemyMetis, "Metis_39");
				break;
			}
			case 1480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000023);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000038, EnemyMetis, "Metis_40");
				break;
			}
			case 1540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000024);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000039, EnemyMetis, "Metis_41");
				break;
			}
			case 1600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000025);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000040, EnemyMetis, "Metis_42");
				break;
			}
			case 1660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000026);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000041, EnemyMetis, "Metis_43");
				break;
			}
			case 1720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000027);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000042, EnemyMetis, "Metis_44");
				break;
			}
			case 1780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000028);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000043, EnemyMetis, "Metis_45");
				break;
			}
			case 1840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000029);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000044, EnemyMetis, "Metis_46");
				break;
			}
			case 1900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000030);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000045, EnemyMetis, "Metis_47");
				break;
			}
			case 1960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000031);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000046, EnemyMetis, "Metis_48");
				break;
			}
			case 2020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000032);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000047, EnemyMetis, "Metis_49");
				break;
			}
			case 2080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000033);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000048, EnemyMetis, "Metis_50");
				break;
			}
			case 2140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000034);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000049, EnemyMetis, "Metis_51");
				break;
			}
			case 2200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000035);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000050, EnemyMetis, "Metis_52");
				break;
			}
			case 2260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000036);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000051, EnemyMetis, "Metis_53");
				break;
			}
			case 2320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000037);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000052, EnemyMetis, "Metis_54");
				break;
			}
			case 2380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000038);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000053, EnemyMetis, "Metis_55");
				break;
			}
			case 2440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000039);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000054, EnemyMetis, "Metis_56");
				break;
			}
			case 2500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000040);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000055, EnemyMetis, "Metis_57");
				break;
			}
			case 2560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000041);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000056, EnemyMetis, "Metis_58");
				break;
			}
			case 2620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000042);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000057, EnemyMetis, "Metis_59");
				break;
			}
			case 2680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000043);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000058, EnemyMetis, "Metis_60");
				break;
			}
			case 2740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000044);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000059, EnemyMetis, "Metis_61");
				break;
			}
			case 2800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000045);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000060, EnemyMetis, "Metis_62");
				break;
			}
			case 2860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000046);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000061, EnemyMetis, "Metis_63");
				break;
			}
			case 2920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000047);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000062, EnemyMetis, "Metis_64");
				break;
			}
			case 2980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000048);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000063, EnemyMetis, "Metis_65");
				break;
			}
			case 3040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000049);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000064, EnemyMetis, "Metis_66");
				break;
			}
			case 3100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000050);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000065, EnemyMetis, "Metis_67");
				break;
			}
			case 3160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000051);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000066, EnemyMetis, "Metis_68");
				break;
			}
			case 3220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000052);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000067, EnemyMetis, "Metis_69");
				break;
			}
			case 3280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000053);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000068, EnemyMetis, "Metis_70");
				break;
			}
			case 3340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000054);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000069, EnemyMetis, "Metis_71");
				break;
			}
			case 3400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000055);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000070, EnemyMetis, "Metis_72");
				break;
			}
			case 3460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000056);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000071, EnemyMetis, "Metis_73");
				break;
			}
			case 3520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000057);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000072, EnemyMetis, "Metis_74");
				break;
			}
			case 3580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000058);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000073, EnemyMetis, "Metis_75");
				break;
			}
			case 3640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000059);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000074, EnemyMetis, "Metis_76");
				break;
			}
			case 3700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000060);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000075, EnemyMetis, "Metis_77");
				break;
			}
			case 3760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000061);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000076, EnemyMetis, "Metis_78");
				break;
			}
			case 3820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000062);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000077, EnemyMetis, "Metis_79");
				break;
			}
			case 3880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000063);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000078, EnemyMetis, "Metis_80");
				break;
			}
			case 3940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000064);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000079, EnemyMetis, "Metis_81");
				break;
			}
			case 4000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000065);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000080, EnemyMetis, "Metis_82");
				break;
			}
			case 4060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000066);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000081, EnemyMetis, "Metis_83");
				break;
			}
			case 4120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000067);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000068);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000069);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000070);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000071);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000072);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000073);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000074);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000075);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000076);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000077);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000078);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000079);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000080);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000081);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 10000: {
				throwEventToUpperTree(EVENT_STG01_02_WAS_BROKEN,this);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 85-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end
}

Stage01_02::~Stage01_02() {

}
