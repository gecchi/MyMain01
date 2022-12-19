#include "Stage01Part01.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"



using namespace GgafLib;
using namespace VioletVreath;

Stage01Part01::Stage01Part01(const char* prm_name) :
        Stage01Part<GgafLib::DefaultScene>(prm_name, EVENT_STAGE01_PART_01_WAS_FINISHED) {
    _class_name = "Stage01Part01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,500,1900,2400,2500,2900,3000,3400,3500,3900,4000,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,5900,6000,6400,6500,6900,7000,7400,7500,7900,8000,8400,8500,8900,9000,9400,9500,10000};
	_paFrame_NextEvent = new frame[43];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 43;
	
	requestActor(20000001, FormationAllas001a, "FormationAllas001a-20000001");
	requestActor(20000002, FormationAllas001b, "FormationAllas001b-20000002");
	requestActor(20000003, FormationAllas001c, "FormationAllas001c-20000003");
	requestActor(20000004, FormationAllas001d, "FormationAllas001d-20000004");
	requestActor(20000005, FormationAllas001a, "FormationAllas001a-20000005");
	requestActor(20000006, FormationAllas001d, "FormationAllas001d-20000006");
	requestActor(20000007, FormationAllas001b, "FormationAllas001b-20000007");
	requestActor(20000008, FormationAllas001c, "FormationAllas001c-20000008");
	requestActor(20000009, FormationAllas001a, "FormationAllas001a-20000009");
	requestActor(20000010, FormationAllas001d, "FormationAllas001d-20000010");
	requestActor(20000011, FormationAllas001b, "FormationAllas001b-20000011");
	requestActor(20000012, FormationAllas001c, "FormationAllas001c-20000012");
    // gen01 end

    getBgmConductor()->ready(0, "BGM_01_01");

}

void Stage01Part01::initialize() {

}

void Stage01Part01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 500: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-1");
				ta->setMaxPerformFrame(2000);
				appendChild(ta);
				ta->addToTable(((FormationAllas001a*)receiveActor(20000001)), 400);
				ta->addToTable(((FormationAllas001b*)receiveActor(20000002)), 400);
				ta->addToTable(((FormationAllas001c*)receiveActor(20000003)), 400);
				ta->addToTable(((FormationAllas001d*)receiveActor(20000004)), 400);
				ta->addToTable(((FormationAllas001a*)receiveActor(20000005)), 1);
				ta->addToTable(((FormationAllas001d*)receiveActor(20000006)), 400);
				ta->addToTable(((FormationAllas001b*)receiveActor(20000007)), 1);
				ta->addToTable(((FormationAllas001c*)receiveActor(20000008)), 400);
				ta->addToTable(((FormationAllas001a*)receiveActor(20000009)), 1);
				ta->addToTable(((FormationAllas001d*)receiveActor(20000010)), 1);
				ta->addToTable(((FormationAllas001b*)receiveActor(20000011)), 1);
				ta->addToTable(((FormationAllas001c*)receiveActor(20000012)), 400);
				}
				break;
			}
			case 1900: {
				requestActor(20000013, FormationUnomia001a, "FormationUnomia001a-20000013");
				requestActor(20000017, VarietyRatislavia001, "VarietyRatislavia001-20000017");
				requestActor(20000019, FormationAppho001a, "FormationAppho001a-20000019");
				break;
			}
			case 2400: {
				requestActor(20000015, FormationUnomia001b, "FormationUnomia001b-20000015");
				requestActor(20000018, VarietyRatislavia002, "VarietyRatislavia002-20000018");
				requestActor(20000027, FormationAppho001b, "FormationAppho001b-20000027");
				break;
			}
			case 2500: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000013));
				VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)receiveActor(20000017);
				bringSceneMediator()->appendGroupChild(pRatislavia);
				bringSceneMediator()->appendGroupChild(receiveActor(20000019));
				break;
			}
			case 2900: {
				requestActor(20000020, FormationAppho001a, "FormationAppho001a-20000020");
				break;
			}
			case 3000: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000015));
				VarietyRatislavia002* pRatislavia = (VarietyRatislavia002*)receiveActor(20000018);
				bringSceneMediator()->appendGroupChild(pRatislavia);
				bringSceneMediator()->appendGroupChild(receiveActor(20000027));
				break;
			}
			case 3400: {
				requestActor(20000028, FormationAppho001b, "FormationAppho001b-20000028");
				break;
			}
			case 3500: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000020));
				break;
			}
			case 3900: {
				requestActor(20000021, FormationAppho001a, "FormationAppho001a-20000021");
				break;
			}
			case 4000: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000028));
				break;
			}
			case 4400: {
				requestActor(20000029, FormationAppho001b, "FormationAppho001b-20000029");
				requestActor(20000035, FormationDelheid001, "FormationDelheid001-20000035");
				break;
			}
			case 4500: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000021));
				requestActor(20000036, FormationDelheid001, "FormationDelheid001-20000036");
				break;
			}
			case 4600: {
				requestActor(20000037, FormationDelheid001, "FormationDelheid001-20000037");
				break;
			}
			case 4700: {
				requestActor(20000038, FormationDelheid001, "FormationDelheid001-20000038");
				break;
			}
			case 4800: {
				requestActor(20000039, FormationDelheid001, "FormationDelheid001-20000039");
				break;
			}
			case 4900: {
				requestActor(20000022, FormationAppho001a, "FormationAppho001a-20000022");
				requestActor(20000040, FormationDelheid001, "FormationDelheid001-20000040");
				break;
			}
			case 5000: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000029));
				FormationDelheid001* pF = (FormationDelheid001*)receiveActor(20000035);
				bringSceneMediator()->appendGroupChild(pF);
				pF->setPosition(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(0), D_ANG(-40), D_ANG(0));
				requestActor(20000041, FormationDelheid001, "FormationDelheid001-20000041");
				break;
			}
			case 5100: {
				FormationDelheid001* pF = (FormationDelheid001*)receiveActor(20000036);
				bringSceneMediator()->appendGroupChild(pF);
				pF->setPosition(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(0), D_ANG(-30), D_ANG(0));
				requestActor(20000042, FormationDelheid001, "FormationDelheid001-20000042");
				break;
			}
			case 5200: {
				FormationDelheid001* pF = (FormationDelheid001*)receiveActor(20000037);
				bringSceneMediator()->appendGroupChild(pF);
				pF->setPosition(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(0), D_ANG(-20), D_ANG(0));
				requestActor(20000043, FormationDelheid001, "FormationDelheid001-20000043");
				break;
			}
			case 5300: {
				FormationDelheid001* pF = (FormationDelheid001*)receiveActor(20000038);
				bringSceneMediator()->appendGroupChild(pF);
				pF->setPosition(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(0), D_ANG(-10), D_ANG(0));
				break;
			}
			case 5400: {
				requestActor(20000030, FormationAppho001b, "FormationAppho001b-20000030");
				FormationDelheid001* pF = (FormationDelheid001*)receiveActor(20000039);
				bringSceneMediator()->appendGroupChild(pF);
				pF->setPosition(PX_C(-200), PX_C(   0), PX_C(500), D_ANG(0), D_ANG(  0), D_ANG(0));
				break;
			}
			case 5500: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000022));
				FormationDelheid001* pF = (FormationDelheid001*)receiveActor(20000040);
				bringSceneMediator()->appendGroupChild(pF);
				pF->setPosition(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(0), D_ANG( 10), D_ANG(0));
				break;
			}
			case 5600: {
				FormationDelheid001* pF = (FormationDelheid001*)receiveActor(20000041);
				bringSceneMediator()->appendGroupChild(pF);
				pF->setPosition(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(0), D_ANG( 20), D_ANG(0));
				break;
			}
			case 5700: {
				FormationDelheid001* pF = (FormationDelheid001*)receiveActor(20000042);
				bringSceneMediator()->appendGroupChild(pF);
				pF->setPosition(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(0), D_ANG( 30), D_ANG(0));
				break;
			}
			case 5800: {
				FormationDelheid001* pF = (FormationDelheid001*)receiveActor(20000043);
				bringSceneMediator()->appendGroupChild(pF);
				pF->setPosition(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(0), D_ANG( 40), D_ANG(0));
				break;
			}
			case 5900: {
				requestActor(20000014, FormationUnomia001a, "FormationUnomia001a-20000014");
				requestActor(20000023, FormationAppho001a, "FormationAppho001a-20000023");
				break;
			}
			case 6000: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000030));
				break;
			}
			case 6400: {
				requestActor(20000016, FormationUnomia001b, "FormationUnomia001b-20000016");
				requestActor(20000031, FormationAppho001b, "FormationAppho001b-20000031");
				break;
			}
			case 6500: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000014));
				bringSceneMediator()->appendGroupChild(receiveActor(20000023));
				break;
			}
			case 6900: {
				requestActor(20000024, FormationAppho001a, "FormationAppho001a-20000024");
				break;
			}
			case 7000: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000016));
				bringSceneMediator()->appendGroupChild(receiveActor(20000031));
				break;
			}
			case 7400: {
				requestActor(20000032, FormationAppho001b, "FormationAppho001b-20000032");
				break;
			}
			case 7500: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000024));
				break;
			}
			case 7900: {
				requestActor(20000025, FormationAppho001a, "FormationAppho001a-20000025");
				break;
			}
			case 8000: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000032));
				break;
			}
			case 8400: {
				requestActor(20000033, FormationAppho001b, "FormationAppho001b-20000033");
				break;
			}
			case 8500: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000025));
				break;
			}
			case 8900: {
				requestActor(20000026, FormationAppho001a, "FormationAppho001a-20000026");
				break;
			}
			case 9000: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000033));
				break;
			}
			case 9400: {
				requestActor(20000034, FormationAppho001b, "FormationAppho001b-20000034");
				break;
			}
			case 9500: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000026));
				break;
			}
			case 10000: {
				bringSceneMediator()->appendGroupChild(receiveActor(20000034));
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 43-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

}

Stage01Part01::~Stage01Part01() {

}
