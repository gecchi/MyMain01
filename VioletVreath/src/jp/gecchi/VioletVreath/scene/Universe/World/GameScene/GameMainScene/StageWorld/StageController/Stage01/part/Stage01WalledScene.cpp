#include "stdafx.h"
#include "Stage01WalledScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/actor/WallAABActor.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "Stage01WalledSection001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/wall/Wall001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/wall/Wall001Prism.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01WalledScene::Stage01WalledScene(const char* prm_name) : WalledScene(prm_name) {
    _class_name = "Stage01WalledScene";

    //********* 壁情報 ***********
    coord wall_dep    = DX_C(40);  //壁ブロックモデル１個のX軸方向の幅設定（Xファイルにより決まる）
    coord wall_width  = DX_C(10);  //壁ブロックモデル１個のZ軸方向の幅設定（Xファイルにより決まる）
    coord wall_height = DX_C(10);  //壁ブロックモデル１個のY軸方向の幅設定（Xファイルにより決まる）
    float scale_r = 10.0f;        //今回壁ブロックの拡大率（ここで設定可能）
    //****************************

    //壁ブロック(直方体)デポジトリ生成
    WallAABActor* pWallAABActor;
    GgafActorDepository* pDepo_WallAAB = NEW GgafActorDepository("Dp_WallAAB");
    for (int i = 0; i < 1000; i++) {
        std::string name = "Wall001_"+XTOS(i);
        pWallAABActor = NEW Wall001(name.c_str());
        pWallAABActor->setScaleR(scale_r);
        pDepo_WallAAB->addSubLast(pWallAABActor);
        Sleep(1);
    }
    P_COMMON_SCENE->getSceneDirector()->addSubGroup(pDepo_WallAAB);
    //getSceneDirector()->addSubGroup(pDepo_WallAAB); は P_UNIVERSE 配下になってしまう

    //壁ブロック(プリズム)デポジトリ生成
    WallAAPrismActor* pWallAAPrismActor;
    GgafActorDepository* pDepo_WallAAPrism = NEW GgafActorDepository("Dp_WallAAPrism");
    for (int i = 0; i < 100; i++) {
        std::string name = "Wall001Prism_"+XTOS(i);
        pWallAAPrismActor = NEW Wall001Prism(name.c_str());
        pWallAAPrismActor->setScaleR(scale_r);
        pDepo_WallAAPrism->addSubLast(pWallAAPrismActor);
        Sleep(1);
    }
    P_COMMON_SCENE->getSceneDirector()->addSubGroup(pDepo_WallAAPrism);

    //シーンセクション生成
    WalledSectionScene* apSection[] = {
        NEW Stage01WalledSection001("Stage01-001-0", this, "scene4_wall_0.dat"),
        NEW Stage01WalledSection001("Stage01-001-1", this, "scene4_wall_1.dat"),
        NEW Stage01WalledSection001("Stage01-001-2", this, "scene4_wall_2.dat"),
        NEW Stage01WalledSection001("Stage01-001-3", this, "scene4_wall_3.dat"),
    };

    //構築
    buildWalledScene(
        wall_dep*scale_r, wall_width*scale_r, wall_height*scale_r,
        GgafDxUniverse::_X_gone_right,
        (WalledSectionScene**)&apSection, 4,
        pDepo_WallAAB ,pDepo_WallAAPrism
    );

    //初期スクロールスピード
    setScrollSpeed(20000);

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,200,1000,2000,2200,3200,4000,5000,5200,6200,7000,8000,30000};
	_paFrame_NextEvent = new frame[13];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 13;
	orderActorToFactory(20000004, FormationHalia, "FormationHalia-1");
    // gen01 end
}

void Stage01WalledScene::initialize() {
    WalledScene::initialize(); //重要
}

void Stage01WalledScene::onActive() {
    P_COMMON_SCENE->setScrollingFunction(_pFuncScrolling);
    P_COMMON_SCENE->setScrollSpeed(_scroll_speed);
    WalledScene::onActive();
}

void Stage01WalledScene::processBehavior() {
    WalledScene::processBehavior();

    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 200: {
				orderActorToFactory(20000003, FormationUnomia001a, "FormationUnomia001a-2");
				break;
			}
			case 1000: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(20000004);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 2000: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(20000003);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				break;
			}
			case 2200: {
				orderActorToFactory(20000005, FormationHalia, "FormationHalia-3");
				break;
			}
			case 3200: {
				orderActorToFactory(20000000, EnemyEsperia, "EnemyEsperia-4");
				break;
			}
			case 4000: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(20000005);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 5000: {
				EnemyEsperia* p = (EnemyEsperia*)obtainActorFromFactory(20000000);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 5200: {
				orderActorToFactory(20000006, FormationHalia, "FormationHalia-5");
				break;
			}
			case 6200: {
				orderActorToFactory(20000001, EnemyEsperia, "EnemyEsperia-6");
				orderActorToFactory(20000002, VarietyRatislavia002, "VarietyRatislavia002-7");
				break;
			}
			case 7000: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(20000006);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 8000: {
				EnemyEsperia* p = (EnemyEsperia*)obtainActorFromFactory(20000001);
				getSceneDirector()->addSubGroup(p);
				VarietyRatislavia002* pRatislaviaA = (VarietyRatislavia002*)obtainActorFromFactory(20000002);
				getSceneDirector()->addSubGroup(pRatislaviaA);
				break;
			}
			case 30000: {
				// WalledScene は終わったよイベント通知不要
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 13-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


}

void Stage01WalledScene::onFinishedAllSection() {
    P_COMMON_SCENE->setScrollingFunction(nullptr);
    P_COMMON_SCENE->setScrollSpeed(0);
    throwEventUpperTree(EVENT_STG01_WALLED_WAS_BROKEN);
}

Stage01WalledScene::~Stage01WalledScene() {

}
