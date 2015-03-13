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
    float scale_r = 2.0f;        //今回壁ブロックの拡大率（ここで設定可能）
    //****************************

    //壁ブロック(直方体)デポジトリ生成
    WallAABActor* pWallAABActor;
    GgafActorDepository* pDepo_wall = NEW GgafActorDepository("Dp_WallAAB");
    for (int i = 0; i < 2000; i++) {
        std::string name = "Wall001_"+XTOS(i);
        pWallAABActor = NEW Wall001(name.c_str());
        pWallAABActor->setScaleR(scale_r);
        pDepo_wall->put(pWallAABActor);
    }
    bringDirector()->addSubGroup(pDepo_wall);

    //壁ブロック(プリズム)デポジトリ生成
    WallAAPrismActor* pWallAAPrismActor;
    GgafActorDepository* pDepo_prism = NEW GgafActorDepository("Dp_WallAAPrism");
    for (int i = 0; i < 100; i++) {
        std::string name = "Wall001Prism_"+XTOS(i);
        pWallAAPrismActor = NEW Wall001Prism(name.c_str());
        pWallAAPrismActor->setScaleR(scale_r);
        pDepo_prism->put(pWallAAPrismActor);
    }
    bringDirector()->addSubGroup(pDepo_prism);

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
        GgafDxUniverse::_x_gone_right,
        (WalledSectionScene**)&apSection, 4,
        pDepo_wall ,pDepo_prism
    );

    //初期スクロールスピード
    setScrollSpeed(PX_C(15));

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {400,700,1000,1300,1600,1900,2200,2500,2800,3100,3400,3700,4000,4300,4600,4900,5200,5500,5800,6100,6400,6700,7000,7300,7600,7900,8200,8500,8800,9100,9400,9700,10000};
	_paFrame_NextEvent = new frame[33];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 33;
    // gen01 end
}

void Stage01WalledScene::initialize() {
    WalledScene::initialize(); //重要。壁デポジトリの所属シーンを配下に
}

void Stage01WalledScene::onActive() {
    P_COMMON_SCENE->setScrollingFunction(_pFuncScrolling);
    P_COMMON_SCENE->setScrollSpeed(getScrollSpeed());
    _TRACE_("Stage01WalledScene::onActive()  CommonScene にもスクロールを設定します。");
    //P_COMMON_SCENE->dump();
    WalledScene::onActive();
}

void Stage01WalledScene::processBehavior() {
    WalledScene::processBehavior();

    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 400: {
				orderActorToFactory(50000000, EnemyErmione, "EnemyErmione-1");
				break;
			}
			case 700: {
				orderActorToFactory(50000001, EnemyErmione, "EnemyErmione-2");
				break;
			}
			case 1000: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000000);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000002, EnemyErmione, "EnemyErmione-3");
				break;
			}
			case 1300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000001);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000003, EnemyErmione, "EnemyErmione-4");
				break;
			}
			case 1600: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000002);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000004, EnemyErmione, "EnemyErmione-5");
				break;
			}
			case 1900: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000003);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000005, EnemyErmione, "EnemyErmione-6");
				break;
			}
			case 2200: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000004);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000006, EnemyErmione, "EnemyErmione-7");
				break;
			}
			case 2500: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000005);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000007, EnemyErmione, "EnemyErmione-8");
				break;
			}
			case 2800: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000006);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000008, EnemyErmione, "EnemyErmione-9");
				break;
			}
			case 3100: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000007);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000009, EnemyErmione, "EnemyErmione-10");
				break;
			}
			case 3400: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000008);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000010, EnemyErmione, "EnemyErmione-11");
				break;
			}
			case 3700: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000009);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000011, EnemyErmione, "EnemyErmione-12");
				break;
			}
			case 4000: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000010);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000012, EnemyErmione, "EnemyErmione-13");
				break;
			}
			case 4300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000011);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000013, EnemyErmione, "EnemyErmione-14");
				break;
			}
			case 4600: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000012);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000014, EnemyErmione, "EnemyErmione-15");
				break;
			}
			case 4900: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000013);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000015, EnemyErmione, "EnemyErmione-16");
				break;
			}
			case 5200: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000014);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000016, EnemyErmione, "EnemyErmione-17");
				break;
			}
			case 5500: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000015);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000017, EnemyErmione, "EnemyErmione-18");
				break;
			}
			case 5800: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000016);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000018, EnemyErmione, "EnemyErmione-19");
				break;
			}
			case 6100: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000017);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000019, EnemyErmione, "EnemyErmione-20");
				break;
			}
			case 6400: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000018);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000020, EnemyErmione, "EnemyErmione-21");
				break;
			}
			case 6700: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000019);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000021, EnemyErmione, "EnemyErmione-22");
				break;
			}
			case 7000: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000020);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000022, EnemyErmione, "EnemyErmione-23");
				break;
			}
			case 7300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000021);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000023, EnemyErmione, "EnemyErmione-24");
				break;
			}
			case 7600: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000022);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000024, EnemyErmione, "EnemyErmione-25");
				break;
			}
			case 7900: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000023);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000025, EnemyErmione, "EnemyErmione-26");
				break;
			}
			case 8200: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000024);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000026, EnemyErmione, "EnemyErmione-27");
				break;
			}
			case 8500: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000025);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000027, EnemyErmione, "EnemyErmione-28");
				break;
			}
			case 8800: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000026);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000028, EnemyErmione, "EnemyErmione-29");
				break;
			}
			case 9100: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000027);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000029, EnemyErmione, "EnemyErmione-30");
				break;
			}
			case 9400: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000028);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				orderActorToFactory(50000030, EnemyErmione, "EnemyErmione-31");
				break;
			}
			case 9700: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000029);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				break;
			}
			case 10000: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(50000030);
				bringDirector()->addSubGroup(pE);
				pE->position(PX_C(5000),0,0);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 33-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


}

void Stage01WalledScene::onFinishedAllSection() {
    _TRACE_(" Stage01WalledScene::onFinishedAllSection()  CommonScene のスクロールを解除します。");
    P_COMMON_SCENE->setScrollingFunction(nullptr);
    P_COMMON_SCENE->setScrollSpeed(0);
    throwEventUpperTree(EVENT_STG01_WALLED_WAS_BROKEN);
}

Stage01WalledScene::~Stage01WalledScene() {

}
