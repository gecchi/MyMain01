#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Stage01MainScene::Stage01MainScene(string prm_name) : GgafDx9LibStg::DefaultScene(prm_name) {

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,620,640,660,680,700,720,740,760,780,800};
	_paFrame_NextEvent = new DWORD[41];
	for (int i = 0; i < 41; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1096100, EnemyCeres, "Ceres_1", "Ceres");
	orderActorToFactory(1096120, EnemyCeres, "Ceres_2", "Ceres");
	orderActorToFactory(1096140, EnemyCeres, "Ceres_3", "Ceres");
	orderActorToFactory(1096160, EnemyCeres, "Ceres_4", "Ceres");
	orderActorToFactory(1096180, EnemyCeres, "Ceres_5", "Ceres");
	orderActorToFactory(1096200, EnemyCeres, "Ceres_6", "Ceres");
	orderActorToFactory(1096220, EnemyCeres, "Ceres_7", "Ceres");
	orderActorToFactory(1096240, EnemyCeres, "Ceres_8", "Ceres");
	orderActorToFactory(1096260, EnemyCeres, "Ceres_9", "Ceres");
	orderActorToFactory(1096280, EnemyCeres, "Ceres_10", "Ceres");
	orderActorToFactory(1096300, EnemyCeres, "Ceres_11", "Ceres");
	orderActorToFactory(1156200, EnemyCeres, "Ceres_12", "Ceres");
	orderActorToFactory(1156220, EnemyCeres, "Ceres_13", "Ceres");
	orderActorToFactory(1156240, EnemyCeres, "Ceres_14", "Ceres");
	orderActorToFactory(1156260, EnemyCeres, "Ceres_15", "Ceres");
	orderActorToFactory(1156280, EnemyCeres, "Ceres_16", "Ceres");
	orderActorToFactory(1156300, EnemyCeres, "Ceres_17", "Ceres");
	orderActorToFactory(1156320, EnemyCeres, "Ceres_18", "Ceres");
	orderActorToFactory(1156340, EnemyCeres, "Ceres_19", "Ceres");
	orderActorToFactory(1156360, EnemyCeres, "Ceres_20", "Ceres");
	orderActorToFactory(1156380, EnemyCeres, "Ceres_21", "Ceres");
	orderActorToFactory(1156400, EnemyCeres, "Ceres_22", "Ceres");
	orderActorToFactory(1216300, EnemyCeres, "Ceres_23", "Ceres");
	orderActorToFactory(1216320, EnemyCeres, "Ceres_24", "Ceres");
	orderActorToFactory(1216340, EnemyCeres, "Ceres_25", "Ceres");
	orderActorToFactory(1216360, EnemyCeres, "Ceres_26", "Ceres");
	orderActorToFactory(1216380, EnemyCeres, "Ceres_27", "Ceres");
	orderActorToFactory(1216400, EnemyCeres, "Ceres_28", "Ceres");
	orderActorToFactory(1216420, EnemyCeres, "Ceres_29", "Ceres");
	orderActorToFactory(1216440, EnemyCeres, "Ceres_30", "Ceres");
	orderActorToFactory(1216460, EnemyCeres, "Ceres_31", "Ceres");
	orderActorToFactory(1216480, EnemyCeres, "Ceres_32", "Ceres");
	orderActorToFactory(1216500, EnemyCeres, "Ceres_33", "Ceres");
	orderActorToFactory(1276400, EnemyCeres, "Ceres_34", "Ceres");
	orderActorToFactory(1276420, EnemyCeres, "Ceres_35", "Ceres");
	orderActorToFactory(1276440, EnemyCeres, "Ceres_36", "Ceres");
	orderActorToFactory(1276460, EnemyCeres, "Ceres_37", "Ceres");
	orderActorToFactory(1276480, EnemyCeres, "Ceres_38", "Ceres");
	orderActorToFactory(1276500, EnemyCeres, "Ceres_39", "Ceres");
	orderActorToFactory(1336500, EnemyCeres, "Ceres_40", "Ceres");
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
			case 20:
				orderActorToFactory(1276520, EnemyCeres, "Ceres_41", "Ceres");
				orderActorToFactory(1336520, EnemyCeres, "Ceres_42", "Ceres");
				break;
			case 40:
				orderActorToFactory(1276540, EnemyCeres, "Ceres_43", "Ceres");
				orderActorToFactory(1336540, EnemyCeres, "Ceres_44", "Ceres");
				break;
			case 60:
				orderActorToFactory(1276560, EnemyCeres, "Ceres_45", "Ceres");
				orderActorToFactory(1336560, EnemyCeres, "Ceres_46", "Ceres");
				break;
			case 80:
				orderActorToFactory(1276580, EnemyCeres, "Ceres_47", "Ceres");
				orderActorToFactory(1336580, EnemyCeres, "Ceres_48", "Ceres");
				break;
			case 100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1096100);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1276600, EnemyCeres, "Ceres_49", "Ceres");
				orderActorToFactory(1336600, EnemyCeres, "Ceres_50", "Ceres");
				orderActorToFactory(1396600, EnemyCeres, "Ceres_51", "Ceres");
				break;
			case 120:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1096120);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1336620, EnemyCeres, "Ceres_52", "Ceres");
				orderActorToFactory(1396620, EnemyCeres, "Ceres_53", "Ceres");
				break;
			case 140:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1096140);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1336640, EnemyCeres, "Ceres_54", "Ceres");
				orderActorToFactory(1396640, EnemyCeres, "Ceres_55", "Ceres");
				break;
			case 160:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1096160);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1336660, EnemyCeres, "Ceres_56", "Ceres");
				orderActorToFactory(1396660, EnemyCeres, "Ceres_57", "Ceres");
				break;
			case 180:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1096180);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1336680, EnemyCeres, "Ceres_58", "Ceres");
				orderActorToFactory(1396680, EnemyCeres, "Ceres_59", "Ceres");
				break;
			case 200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1096200);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1156200);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1336700, EnemyCeres, "Ceres_60", "Ceres");
				orderActorToFactory(1396700, EnemyCeres, "Ceres_61", "Ceres");
				break;
			case 220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1096220);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1156220);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1396720, EnemyCeres, "Ceres_62", "Ceres");
				break;
			case 240:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1096240);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1156240);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1396740, EnemyCeres, "Ceres_63", "Ceres");
				break;
			case 260:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1096260);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1156260);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1396760, EnemyCeres, "Ceres_64", "Ceres");
				break;
			case 280:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1096280);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1156280);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1396780, EnemyCeres, "Ceres_65", "Ceres");
				break;
			case 300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1096300);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1156300);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1216300);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1396800, EnemyCeres, "Ceres_66", "Ceres");
				break;
			case 320:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1156320);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1216320);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1156340);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1216340);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 360:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1156360);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1216360);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 380:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1156380);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1216380);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1156400);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1216400);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1276400);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 420:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1216420);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1276420);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 440:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1216440);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1276440);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 460:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1216460);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1276460);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 480:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1216480);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1276480);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1216500);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1276500);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1336500);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 520:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1276520);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1336520);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 540:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1276540);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1336540);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1276560);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1336560);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 580:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1276580);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1336580);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1276600);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1336600);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1396600);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1336620);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1396620);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 640:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1336640);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1396640);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 660:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1336660);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1396660);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 680:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1336680);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1396680);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1336700);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1396700);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 720:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1396720);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 740:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1396740);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 760:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1396760);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 780:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1396780);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1396800);
				pActor->_Y_turn = 0;
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
