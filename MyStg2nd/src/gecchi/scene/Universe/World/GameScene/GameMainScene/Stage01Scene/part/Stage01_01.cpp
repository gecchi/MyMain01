#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,130,160,190,220,250,280,310,340,370,400,430,460,490,520,550,580,610,640,670,700,730,760,790,820,850,880,910,940,970,1000,2000};
	_paFrame_NextEvent = new frame[33];
	for (int i = 0; i < 33; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderActorToFactory(31037100, EnemyMetis, "Metis_1");
	orderActorToFactory(31037130, EnemyMetis, "Metis_2");
	orderActorToFactory(31037160, EnemyMetis, "Metis_3");
	orderActorToFactory(31037190, EnemyMetis, "Metis_4");
	orderActorToFactory(31037220, EnemyMetis, "Metis_5");
	orderActorToFactory(31037250, EnemyMetis, "Metis_6");
	orderActorToFactory(31037280, EnemyMetis, "Metis_7");
	orderActorToFactory(31037310, EnemyMetis, "Metis_8");
	orderActorToFactory(31037340, EnemyMetis, "Metis_9");
	orderActorToFactory(31037370, EnemyMetis, "Metis_10");
	orderActorToFactory(31037400, EnemyMetis, "Metis_11");
	orderActorToFactory(31037430, EnemyMetis, "Metis_12");
	orderActorToFactory(31037460, EnemyMetis, "Metis_13");
	orderActorToFactory(31037490, EnemyMetis, "Metis_14");
	orderActorToFactory(31037520, EnemyMetis, "Metis_15");
	orderActorToFactory(31037550, EnemyMetis, "Metis_16");
	orderActorToFactory(31037580, EnemyMetis, "Metis_17");
	orderActorToFactory(31037610, EnemyMetis, "Metis_18");
	orderActorToFactory(31037640, EnemyMetis, "Metis_19");
	orderActorToFactory(31037670, EnemyMetis, "Metis_20");
	orderActorToFactory(31037700, EnemyMetis, "Metis_21");
	orderActorToFactory(31037730, EnemyMetis, "Metis_22");
	orderActorToFactory(31037760, EnemyMetis, "Metis_23");
	orderActorToFactory(31037790, EnemyMetis, "Metis_24");
	orderActorToFactory(31037820, EnemyMetis, "Metis_25");
	orderActorToFactory(31037850, EnemyMetis, "Metis_26");
	orderActorToFactory(31037880, EnemyMetis, "Metis_27");
	orderActorToFactory(31037910, EnemyMetis, "Metis_28");
	orderActorToFactory(31037940, EnemyMetis, "Metis_29");
	orderActorToFactory(31037970, EnemyMetis, "Metis_30");
	orderActorToFactory(310371000, EnemyMetis, "Metis_31");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037130);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037160);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037190);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037220);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037250);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037280);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037310);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037340);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037370);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037400);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037430);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037460);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037490);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037520);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037550);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037580);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037610);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037640);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037670);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037700);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037730);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037760);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037790);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037820);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037850);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037880);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037910);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037940);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(31037970);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 1000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(310371000);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 2000:
				throwEventToUpperTree(EVENT_STG01_01_WAS_BROKEN,this);
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 33-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

}

void Stage01_01::processFinal() {
}

Stage01_01::~Stage01_01() {

}
