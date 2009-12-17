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
    DWORD dw[] = {1,100,1700,1900,3100,3500,3700,4900,5100,5500,6200,6700,6900,8000,8100,8200,8500,8700,9800,9900,10000,10100,10500,11200,11700,11800,11900,13000,13100,13200,13500,13700,14800,14900,15000,15100,15500,16200,16700,16800,16900,18000,18200,18700,20000};
    _paFrame_NextEvent = new DWORD[45];
    for (int i = 0; i < 45; i++) {
        _paFrame_NextEvent[i] = dw[i];
    }
    orderActorToFactory(11077100, EnemyAstraea, "Astraea_1");
    orderActorToFactory(110971900, EnemyAstraea, "Astraea_2");
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
    if (_frame_of_life == _paFrame_NextEvent[_iCnt_Event]) {
        switch (_frame_of_life) {
            case 1:
                break;
            case 100:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11077100);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = -300000;
                }
                break;
            case 1700:
                orderActorToFactory(111173700, EnemyAstraea, "Astraea_3");
                break;
            case 1900:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110971900);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = -100000;
                }
                break;
            case 3100:
                orderActorToFactory(110775100, EnemyAstraea, "Astraea_4");
                break;
            case 3500:
                orderActorToFactory(111375500, EnemyAstraea, "Astraea_5");
                break;
            case 3700:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111173700);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = 100000;
                }
                break;
            case 4900:
                orderActorToFactory(110976900, EnemyAstraea, "Astraea_6");
                break;
            case 5100:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110775100);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = -300000;
                }
                break;
            case 5500:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111375500);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = 300000;
                }
                break;
            case 6200:
                orderActorToFactory(111678200, EnemyAstraea, "Astraea_7");
                break;
            case 6700:
                orderActorToFactory(111178700, EnemyAstraea, "Astraea_8");
                break;
            case 6900:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110976900);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = -100000;
                }
                break;
            case 8000:
                orderActorToFactory(1118710000, EnemyAstraea, "Astraea_9");
                break;
            case 8100:
                orderActorToFactory(1107710100, EnemyAstraea, "Astraea_10");
                break;
            case 8200:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111678200);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 900000;
                pActor->_Z = 200000;
                pActor->_Y = -250000;
                }
                break;
            case 8500:
                orderActorToFactory(1113710500, EnemyAstraea, "Astraea_11");
                break;
            case 8700:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111178700);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = 100000;
                }
                break;
            case 9800:
                orderActorToFactory(1120711800, EnemyAstraea, "Astraea_12");
                break;
            case 9900:
                orderActorToFactory(1109711900, EnemyAstraea, "Astraea_13");
                break;
            case 10000:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118710000);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 900000;
                pActor->_Z = 200000;
                pActor->_Y = -50000;
                }
                break;
            case 10100:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1107710100);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = -300000;
                }
                break;
            case 10500:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113710500);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = 300000;
                }
                break;
            case 11200:
                orderActorToFactory(1116713200, EnemyAstraea, "Astraea_14");
                break;
            case 11700:
                orderActorToFactory(1111713700, EnemyAstraea, "Astraea_15");
                break;
            case 11800:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120711800);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 900000;
                pActor->_Z = 200000;
                pActor->_Y = 150000;
                }
                break;
            case 11900:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109711900);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = -100000;
                }
                break;
            case 13000:
                orderActorToFactory(1118715000, EnemyAstraea, "Astraea_16");
                break;
            case 13100:
                orderActorToFactory(1107715100, EnemyAstraea, "Astraea_17");
                break;
            case 13200:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116713200);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 900000;
                pActor->_Z = 200000;
                pActor->_Y = -250000;
                }
                break;
            case 13500:
                orderActorToFactory(1113715500, EnemyAstraea, "Astraea_18");
                break;
            case 13700:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111713700);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = 100000;
                }
                break;
            case 14800:
                orderActorToFactory(1120716800, EnemyAstraea, "Astraea_19");
                break;
            case 14900:
                orderActorToFactory(1109716900, EnemyAstraea, "Astraea_20");
                break;
            case 15000:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118715000);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 900000;
                pActor->_Z = 200000;
                pActor->_Y = -50000;
                }
                break;
            case 15100:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1107715100);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = -300000;
                }
                break;
            case 15500:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113715500);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = 300000;
                }
                break;
            case 16200:
                orderActorToFactory(1116718200, EnemyAstraea, "Astraea_21");
                break;
            case 16700:
                orderActorToFactory(1111718700, EnemyAstraea, "Astraea_22");
                break;
            case 16800:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120716800);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 900000;
                pActor->_Z = 200000;
                pActor->_Y = 150000;
                }
                break;
            case 16900:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109716900);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = -100000;
                }
                break;
            case 18000:
                orderActorToFactory(1118720000, EnemyAstraea, "Astraea_23");
                break;
            case 18200:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116718200);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 900000;
                pActor->_Z = 200000;
                pActor->_Y = -250000;
                }
                break;
            case 18700:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111718700);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 800000;
                pActor->_Z = -200000;
                pActor->_Y = 100000;
                }
                break;
            case 20000:
                {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118720000);
                getLordActor()->accept(KIND_ENEMY_BODY, pActor);
                pActor->_X = 900000;
                pActor->_Z = 200000;
                pActor->_Y = -50000;
                }
                break;
            default :
                break;
        }
        _iCnt_Event++;
    }
    // gen02 end

    if (_frame_of_life== 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (_frame_of_life== 1) {
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
