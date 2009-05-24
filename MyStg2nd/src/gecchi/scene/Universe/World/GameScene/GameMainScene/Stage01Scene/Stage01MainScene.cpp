#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01MainScene::Stage01MainScene(const char* prm_name) : DefaultScene(prm_name) {

    _pDispatcher = NEW ActorDispatcher("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 100; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivateTreeImmediately(); //最初非表示
        _pDispatcher->addSubLast(pEnemyMeshShot);
    }
    getLordActor()->accept(KIND_ENEMY_SHOT_CHOKI, _pDispatcher);

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,10,20,30,40,50,60,70,80,90,100,110,120,600,610,620,630,640,650,660,670,680,690,700,710,720};
	_paFrame_NextEvent = new DWORD[26];
	for (int i = 0; i < 26; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105610, EnemyAstraea, "Astraea_1");
	orderActorToFactory(11077600, EnemyAstraea, "Astraea_2");
	orderActorToFactory(11217600, EnemyAstraea, "Astraea_3");
	orderActorToFactory(11357600, EnemyAstraea, "Astraea_4");
	// gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
	if (_lifeframe == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_lifeframe) {
			case 1:
				break;
			case 10:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610));
				orderActorToFactory(11087610, EnemyAstraea, "Astraea_5");
				orderActorToFactory(11227610, EnemyAstraea, "Astraea_6");
				orderActorToFactory(11367610, EnemyAstraea, "Astraea_7");
				break;
			case 20:
				orderActorToFactory(11097620, EnemyAstraea, "Astraea_8");
				orderActorToFactory(11237620, EnemyAstraea, "Astraea_9");
				orderActorToFactory(11377620, EnemyAstraea, "Astraea_10");
				break;
			case 30:
				orderActorToFactory(11107630, EnemyAstraea, "Astraea_11");
				orderActorToFactory(11247630, EnemyAstraea, "Astraea_12");
				orderActorToFactory(11387630, EnemyAstraea, "Astraea_13");
				break;
			case 40:
				orderActorToFactory(11117640, EnemyAstraea, "Astraea_14");
				orderActorToFactory(11257640, EnemyAstraea, "Astraea_15");
				orderActorToFactory(11397640, EnemyAstraea, "Astraea_16");
				break;
			case 50:
				orderActorToFactory(11127650, EnemyAstraea, "Astraea_17");
				orderActorToFactory(11267650, EnemyAstraea, "Astraea_18");
				orderActorToFactory(11407650, EnemyAstraea, "Astraea_19");
				break;
			case 60:
				orderActorToFactory(11137660, EnemyAstraea, "Astraea_20");
				orderActorToFactory(11277660, EnemyAstraea, "Astraea_21");
				orderActorToFactory(11417660, EnemyAstraea, "Astraea_22");
				break;
			case 70:
				orderActorToFactory(11147670, EnemyAstraea, "Astraea_23");
				orderActorToFactory(11287670, EnemyAstraea, "Astraea_24");
				orderActorToFactory(11427670, EnemyAstraea, "Astraea_25");
				break;
			case 80:
				orderActorToFactory(11157680, EnemyAstraea, "Astraea_26");
				orderActorToFactory(11297680, EnemyAstraea, "Astraea_27");
				orderActorToFactory(11437680, EnemyAstraea, "Astraea_28");
				break;
			case 90:
				orderActorToFactory(11167690, EnemyAstraea, "Astraea_29");
				orderActorToFactory(11307690, EnemyAstraea, "Astraea_30");
				orderActorToFactory(11447690, EnemyAstraea, "Astraea_31");
				break;
			case 100:
				orderActorToFactory(11177700, EnemyAstraea, "Astraea_32");
				orderActorToFactory(11317700, EnemyAstraea, "Astraea_33");
				orderActorToFactory(11457700, EnemyAstraea, "Astraea_34");
				break;
			case 110:
				orderActorToFactory(11187710, EnemyAstraea, "Astraea_35");
				orderActorToFactory(11327710, EnemyAstraea, "Astraea_36");
				orderActorToFactory(11467710, EnemyAstraea, "Astraea_37");
				break;
			case 120:
				orderActorToFactory(11197720, EnemyAstraea, "Astraea_38");
				orderActorToFactory(11337720, EnemyAstraea, "Astraea_39");
				orderActorToFactory(11477720, EnemyAstraea, "Astraea_40");
				break;
			case 600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11077600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11217600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = -300000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11357600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = -300000;
				}
				break;
			case 610:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11087610);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = -250000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11227610);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = -250000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11367610);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = -250000;
				}
				break;
			case 620:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11097620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = -200000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11237620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = -200000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11377620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = -200000;
				}
				break;
			case 630:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11107630);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = -150000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11247630);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = -150000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11387630);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = -150000;
				}
				break;
			case 640:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11117640);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = -400000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11257640);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = -400000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11397640);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = -400000;
				}
				break;
			case 650:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11127650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = -50000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11267650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = -50000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11407650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = -50000;
				}
				break;
			case 660:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11137660);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = -0;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11277660);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = -0;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11417660);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = -0;
				}
				break;
			case 670:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11147670);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = 50000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11287670);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = 50000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11427670);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = 50000;
				}
				break;
			case 680:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11157680);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = 400000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11297680);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = 400000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11437680);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = 400000;
				}
				break;
			case 690:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11167690);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = 150000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11307690);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = 150000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11447690);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = 150000;
				}
				break;
			case 700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11177700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = 200000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11317700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = 200000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11457700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = 200000;
				}
				break;
			case 710:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11187710);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = 250000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11327710);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = 250000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11467710);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = 250000;
				}
				break;
			case 720:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11197720);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = -200000;
				pActor->_Y = 300000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11337720);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 200000;
				pActor->_Y = 300000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11477720);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 400000;
				pActor->_Z = 0;
				pActor->_Y = 300000;
				}
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
    // gen02 end

    if (_lifeframe== 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->breakAwayFromTree());

    }

}

void Stage01MainScene::processFinal() {
    //	if (_lifeframe== 1) {
    //		_TRACE_("Stage01MainScene::processFinally 私はいきなり停止します。GameMainSceneが解除してくれるはずー");
    //		this->inactivateTree(); //GameMainSceneが解除してくれる
    //	}
}

Stage01MainScene::~Stage01MainScene() {
    //NEWからprocessBehaviorまでの間に強制終了された場合、
    //_pDispatcherはどのツリーにも所属していない。
    if (_pDispatcher->getParent() == NULL) {
        _TRACE_("_pDispatcherが未所属のため独自delete");
        DELETE_IMPOSSIBLE_NULL(_pDispatcher);
    }
}
