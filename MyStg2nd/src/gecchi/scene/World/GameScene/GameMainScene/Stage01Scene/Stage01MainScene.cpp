#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Stage01MainScene::Stage01MainScene(string prm_name) : GgafDx9LibStg::DefaultScene(prm_name) {

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,620,640,660,680,700,720,760,800};
	_paFrame_NextEvent = new DWORD[39];
	for (int i = 0; i < 39; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1087100, EnemyCeres, "Ceres_1", "Ceres");
	orderActorToFactory(1087140, EnemyCeres, "Ceres_2", "Ceres");
	orderActorToFactory(1087180, EnemyCeres, "Ceres_3", "Ceres");
	orderActorToFactory(1087220, EnemyCeres, "Ceres_4", "Ceres");
	orderActorToFactory(1087260, EnemyCeres, "Ceres_5", "Ceres");
	orderActorToFactory(1087300, EnemyCeres, "Ceres_6", "Ceres");
	orderActorToFactory(1157200, EnemyCeres, "Ceres_7", "Ceres");
	orderActorToFactory(1157240, EnemyCeres, "Ceres_8", "Ceres");
	orderActorToFactory(1157280, EnemyCeres, "Ceres_9", "Ceres");
	orderActorToFactory(1157320, EnemyCeres, "Ceres_10", "Ceres");
	orderActorToFactory(1157360, EnemyCeres, "Ceres_11", "Ceres");
	orderActorToFactory(1157400, EnemyCeres, "Ceres_12", "Ceres");
	orderActorToFactory(1217300, EnemyCeres, "Ceres_13", "Ceres");
	orderActorToFactory(1217340, EnemyCeres, "Ceres_14", "Ceres");
	orderActorToFactory(1217380, EnemyCeres, "Ceres_15", "Ceres");
	orderActorToFactory(1217420, EnemyCeres, "Ceres_16", "Ceres");
	orderActorToFactory(1217460, EnemyCeres, "Ceres_17", "Ceres");
	orderActorToFactory(1217500, EnemyCeres, "Ceres_18", "Ceres");
	orderActorToFactory(1277400, EnemyCeres, "Ceres_19", "Ceres");
	orderActorToFactory(1277440, EnemyCeres, "Ceres_20", "Ceres");
	orderActorToFactory(1277480, EnemyCeres, "Ceres_21", "Ceres");
	orderActorToFactory(1337500, EnemyCeres, "Ceres_22", "Ceres");
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
				orderActorToFactory(1277520, EnemyCeres, "Ceres_23", "Ceres");
				break;
			case 40:
				orderActorToFactory(1337540, EnemyCeres, "Ceres_24", "Ceres");
				break;
			case 60:
				orderActorToFactory(1277560, EnemyCeres, "Ceres_25", "Ceres");
				break;
			case 80:
				orderActorToFactory(1337580, EnemyCeres, "Ceres_26", "Ceres");
				break;
			case 100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1087100);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1277600, EnemyCeres, "Ceres_27", "Ceres");
				orderSceneToFactory(1397600, EnemyCeres, "Ceres_28");
				break;
			case 120:
				orderActorToFactory(1337620, EnemyCeres, "Ceres_29", "Ceres");
				break;
			case 140:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1087140);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderSceneToFactory(1397640, EnemyCeres, "Ceres_30");
				break;
			case 160:
				orderActorToFactory(1337660, EnemyCeres, "Ceres_31", "Ceres");
				break;
			case 180:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1087180);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderSceneToFactory(1397680, EnemyCeres, "Ceres_32");
				break;
			case 200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1157200);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(1337700, EnemyCeres, "Ceres_33", "Ceres");
				break;
			case 220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1087220);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderSceneToFactory(1397720, EnemyCeres, "Ceres_34");
				break;
			case 240:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1157240);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 260:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1087260);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderSceneToFactory(1397760, EnemyCeres, "Ceres_35");
				break;
			case 280:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1157280);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1087300);
				pActor->_Y_turn = -100000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1217300);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderSceneToFactory(1397800, EnemyCeres, "Ceres_36");
				break;
			case 320:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1157320);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1217340);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 360:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1157360);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 380:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1217380);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1157400);
				pActor->_Y_turn = -80000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1277400);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 420:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1217420);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 440:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1277440);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 460:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1217460);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 480:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1277480);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1217500);
				pActor->_Y_turn = -60000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1337500);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 520:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1277520);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 540:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1337540);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1277560);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 580:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1337580);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1277600);
				pActor->_Y_turn = -40000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pScene = (EnemyCeres*)obtainSceneFromFactory(1397600);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1337620);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 640:
				{
				EnemyCeres* pScene = (EnemyCeres*)obtainSceneFromFactory(1397640);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 660:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1337660);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 680:
				{
				EnemyCeres* pScene = (EnemyCeres*)obtainSceneFromFactory(1397680);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1337700);
				pActor->_Y_turn = -20000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 720:
				{
				EnemyCeres* pScene = (EnemyCeres*)obtainSceneFromFactory(1397720);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 760:
				{
				EnemyCeres* pScene = (EnemyCeres*)obtainSceneFromFactory(1397760);
				pActor->_Y_turn = 0;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 800:
				{
				EnemyCeres* pScene = (EnemyCeres*)obtainSceneFromFactory(1397800);
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
