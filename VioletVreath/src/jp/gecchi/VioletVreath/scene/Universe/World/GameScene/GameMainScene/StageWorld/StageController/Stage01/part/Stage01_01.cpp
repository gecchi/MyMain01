#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,500,1600,2100,2500,2600,3000,3100,3500,3600,4000,4100,4500,4600,5000,5100,5500,5600,6000,6100,6500,6600,7000,7100,7500,7600,8000,8100,8500,8600,9000,9100,9500,10000};
	_paFrame_NextEvent = new frame[34];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 34;
	
	orderActorToFactory(30000001, FormationPallas001a, "FormationPallas001a-1");
	orderActorToFactory(30000002, FormationPallas001b, "FormationPallas001b-2");
	orderActorToFactory(30000003, FormationPallas001c, "FormationPallas001c-3");
	orderActorToFactory(30000004, FormationPallas001d, "FormationPallas001d-4");
	orderActorToFactory(30000005, FormationPallas001a, "FormationPallas001a-5");
	orderActorToFactory(30000006, FormationPallas001d, "FormationPallas001d-6");
	orderActorToFactory(30000007, FormationPallas001b, "FormationPallas001b-7");
	orderActorToFactory(30000008, FormationPallas001c, "FormationPallas001c-8");
	orderActorToFactory(30000009, FormationPallas001a, "FormationPallas001a-9");
	orderActorToFactory(30000010, FormationPallas001d, "FormationPallas001d-10");
	orderActorToFactory(30000011, FormationPallas001b, "FormationPallas001b-11");
	orderActorToFactory(30000012, FormationPallas001c, "FormationPallas001c-12");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 500: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-13");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(30000001)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(30000002)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(30000003)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(30000004)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(30000005)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(30000006)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(30000007)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(30000008)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(30000009)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(30000010)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(30000011)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(30000012)), 400);
				}
				break;
			}
			case 1600: {
				orderActorToFactory(30000013, FormationEunomia001a, "FormationEunomia001a-14");
				break;
			}
			case 2100: {
				orderActorToFactory(30000021, FormationEunomia001b, "FormationEunomia001b-15");
				break;
			}
			case 2500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000013);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 2600: {
				orderActorToFactory(30000014, FormationEunomia001a, "FormationEunomia001a-16");
				break;
			}
			case 3000: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000021);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 3100: {
				orderActorToFactory(30000022, FormationEunomia001b, "FormationEunomia001b-17");
				break;
			}
			case 3500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000014);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 3600: {
				orderActorToFactory(30000015, FormationEunomia001a, "FormationEunomia001a-18");
				break;
			}
			case 4000: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000022);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 4100: {
				orderActorToFactory(30000023, FormationEunomia001b, "FormationEunomia001b-19");
				orderActorToFactory(30000029, VarietySylvia001, "VarietySylvia001-20");
				break;
			}
			case 4500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000015);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 4600: {
				orderActorToFactory(30000016, FormationEunomia001a, "FormationEunomia001a-21");
				break;
			}
			case 5000: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000023);
				getDirector()->addSubGroup(pFormationEunomia);
				VarietySylvia001* pSylvia = (VarietySylvia001*)obtainActorFromFactory(30000029);
				getDirector()->addSubGroup(pSylvia);
				break;
			}
			case 5100: {
				orderActorToFactory(30000024, FormationEunomia001b, "FormationEunomia001b-22");
				break;
			}
			case 5500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000016);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 5600: {
				orderActorToFactory(30000017, FormationEunomia001a, "FormationEunomia001a-23");
				break;
			}
			case 6000: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000024);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 6100: {
				orderActorToFactory(30000025, FormationEunomia001b, "FormationEunomia001b-24");
				break;
			}
			case 6500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000017);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 6600: {
				orderActorToFactory(30000018, FormationEunomia001a, "FormationEunomia001a-25");
				break;
			}
			case 7000: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000025);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 7100: {
				orderActorToFactory(30000026, FormationEunomia001b, "FormationEunomia001b-26");
				orderActorToFactory(30000030, VarietySylvia002, "VarietySylvia002-27");
				break;
			}
			case 7500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000018);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 7600: {
				orderActorToFactory(30000019, FormationEunomia001a, "FormationEunomia001a-28");
				break;
			}
			case 8000: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000026);
				getDirector()->addSubGroup(pFormationEunomia);
				VarietySylvia002* pSylvia = (VarietySylvia002*)obtainActorFromFactory(30000030);
				getDirector()->addSubGroup(pSylvia);
				break;
			}
			case 8100: {
				orderActorToFactory(30000027, FormationEunomia001b, "FormationEunomia001b-29");
				break;
			}
			case 8500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000019);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 8600: {
				orderActorToFactory(30000020, FormationEunomia001a, "FormationEunomia001a-30");
				break;
			}
			case 9000: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000027);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 9100: {
				orderActorToFactory(30000028, FormationEunomia001b, "FormationEunomia001b-31");
				break;
			}
			case 9500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000020);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 10000: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000028);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 34-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    //シーン終了のイベントを通知
    if (getActivePartFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        throwEventUpperTree(EVENT_STG01_01_WAS_BROKEN);
    }
}

Stage01_01::~Stage01_01() {

}
