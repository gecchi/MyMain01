#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01WalledScene::Stage01WalledScene(const char* prm_name) : WalledScene(prm_name) {
    _class_name = "Stage01WalledScene";

    //壁ブロックディスパッチャー生成
    float scale_r = 5.0f; //壁ブロックの元モデルからの拡大率
    WallActor* pWallActor;
    GgafActorDispatcher* pDispatcher_Wall = NEW GgafActorDispatcher("Dp_Wall");
    for (int i = 0; i < 1000; i++) {
        pWallActor = NEW Wall001("GroundBox");
        pWallActor->setScaleRate(scale_r);
        pWallActor->inactivateTreeImmediately();
        pDispatcher_Wall->addSubLast(pWallActor);
    }

    //シーンセクション生成
    WalledSectionScene* apSection[] = {
      NEW Stage01WalledSection001("gbs", this, "scene4_wall_0.dat"),
      NEW Stage01WalledSection001("gbs", this, "scene4_wall_1.dat"),
      NEW Stage01WalledSection001("gbs", this, "scene4_wall_2.dat"),
      NEW Stage01WalledSection001("gbs", this, "scene4_wall_3.dat"),
      NEW Stage01WalledSection001("gbs", this, "scene4_wall_4.dat"),
    };

    //構築
    buildWalledScene(
        400000*scale_r, 100000*scale_r, 100000*scale_r,
        (WalledSectionScene**)&apSection, 5,
        pDispatcher_Wall
    );

    //初期スクロールスピード
    setScroolSpeed(10000);

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,100};
    _paFrame_NextEvent = new frame[2];
    for (int i = 0; i < 2; i++) {
        _paFrame_NextEvent[i] = f[i];
    }
    orderActorToFactory(20000000, FormationThalia, "FormationThalia_1");
    // gen01 end
}


void Stage01WalledScene::initialize() {
}



void Stage01WalledScene::onActive() {
    WalledScene::onActive();
}

void Stage01WalledScene::processBehavior() {
    WalledScene::processBehavior();


    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
    if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
        switch (getActivePartFrame()) {
            case 1: {
                break;
            }
            case 100: {
                FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(20000000);
                getLordActor()->addSubGroup(pF);
                break;
            }
            default :
                break;
        }
        _iCnt_Event = (_iCnt_Event < 2-1 ? _iCnt_Event+1 : _iCnt_Event);
    }
    // gen02 end
}

void Stage01WalledScene::processFinal() {
}

Stage01WalledScene::~Stage01WalledScene() {

}
