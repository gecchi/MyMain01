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
    GgafActorDepository* pDepo_wall = NEW GgafActorDepository("Dp_WallAAB");
    for (int i = 0; i < 1000; i++) {
        std::string name = "Wall001_"+XTOS(i);
        pWallAABActor = NEW Wall001(name.c_str());
        pWallAABActor->setScaleR(scale_r);
        pDepo_wall->put(pWallAABActor);
        Sleep(1);
    }
    P_COMMON_SCENE->getSceneDirector()->addSubGroup(pDepo_wall);
    //getSceneDirector()->addSubGroup(pDepo_wall); は P_UNIVERSE 配下になってしまう

    //壁ブロック(プリズム)デポジトリ生成
    WallAAPrismActor* pWallAAPrismActor;
    GgafActorDepository* pDepo_prism = NEW GgafActorDepository("Dp_WallAAPrism");
    for (int i = 0; i < 100; i++) {
        std::string name = "Wall001Prism_"+XTOS(i);
        pWallAAPrismActor = NEW Wall001Prism(name.c_str());
        pWallAAPrismActor->setScaleR(scale_r);
        pDepo_prism->put(pWallAAPrismActor);
        Sleep(1);
    }
    P_COMMON_SCENE->getSceneDirector()->addSubGroup(pDepo_prism);

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
    setScrollSpeed(PX_C(5));

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {100};
	_paFrame_NextEvent = new frame[1];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 1;
    // gen01 end
}

void Stage01WalledScene::initialize() {
    WalledScene::initialize(); //重要。壁デポジトリの所属シーンを配下に
}

void Stage01WalledScene::onActive() {
    P_COMMON_SCENE->setScrollingFunction(_pFuncScrolling);
    P_COMMON_SCENE->setScrollSpeed(getScrollSpeed());
    _DTRACE_("Stage01WalledScene::onActive()  CommonScene にもスクロールを設定します。");
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
			case 100: {
				// WalledScene は終わったよイベント通知不要
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 1-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


}

void Stage01WalledScene::onFinishedAllSection() {
    _DTRACE_(" Stage01WalledScene::onFinishedAllSection()  CommonScene のスクロールを解除します。");
    P_COMMON_SCENE->setScrollingFunction(nullptr);
    P_COMMON_SCENE->setScrollSpeed(0);
    throwEventUpperTree(EVENT_STG01_WALLED_WAS_BROKEN);
}

Stage01WalledScene::~Stage01WalledScene() {

}
