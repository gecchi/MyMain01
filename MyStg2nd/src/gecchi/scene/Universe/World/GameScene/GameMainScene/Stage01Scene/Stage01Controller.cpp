#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01Controller::Stage01Controller(const char* prm_name) : DefaultScene(prm_name) {
    _pBgmPerformer->useBgm(3);
    _pBgmPerformer->set(0, "VIRTUAL_ON_06");
    _pBgmPerformer->set(1, "PLANETES");
    _pBgmPerformer->set(2, "VIRTUAL_ON_11");
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen01 start
	frame f[] = {1,3,200,2000,2200,4000,4200,6000};
	_paFrame_NextEvent = new frame[8];
	for (int i = 0; i < 8; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderSceneToFactory(110273, Stage01_01, "Stage01_01");
    // gen01 end
}

void Stage01Controller::initialize() {
    _pBgmPerformer->play(0, DSBVOLUME_MIN, true);
    _pBgmPerformer->fadein(0, 420);
}

void Stage01Controller::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 3:
				{
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(110273);
				addSubLast(pScene);
				}
				break;
			case 200:
				orderSceneToFactory(110372000, Stage01_02, "Stage01_02");
				break;
			case 2000:
				{
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(110372000);
				addSubLast(pScene);
				}
				break;
			case 2200:
				orderSceneToFactory(110474000, Stage01_03, "Stage01_03");
				break;
			case 4000:
				{
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(110474000);
				addSubLast(pScene);
				}
				break;
			case 4200:
				orderSceneToFactory(110576000, Stage01_Climax, "Stage01_Climax");
				break;
			case 6000:
				{
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(110576000);
				addSubLast(pScene);
				}
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 8-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

    if (getBehaveingFrame() == 2) {

        _TRACE_("Stage01Controller::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01Controller::processFinal() {
}

void Stage01Controller::catchEvent(UINT32 prm_no) {
	if (prm_no == STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01Controller::catchEvent() STG01_01_WAS_BROKEN");
        //BGM０番フェードアウト
        _pBgmPerformer->fadeout_stop(0, 420);
        //BGM１番フェードイン
        _pBgmPerformer->play(1, DSBVOLUME_MIN, true);
        _pBgmPerformer->fadein(1, 420);
    } else if (prm_no == STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01Controller::catchEvent() STG01_02_WAS_BROKEN");
    } else if (prm_no == STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01Controller::catchEvent() STG01_03_WAS_BROKEN");
        //BGM１番フェードアウト
        _pBgmPerformer->fadeout_stop(1, 420);
        //BGM２番フェードイン
        _pBgmPerformer->play(2, DSBVOLUME_MIN, true);
        _pBgmPerformer->fadein(2, 420);
    } else if (prm_no == STG01_BOSS_WAS_BROKEN) {
        //BGM１番フェードアウト
        _pBgmPerformer->fadeout_stop(2, 420);
        _TRACE_("Stage01Controller::catchEvent() STG01_BOSS_WAS_BROKENキャッチしたよ。STAGE_PROG_ENDにします");
        getParent()->setProgress(STAGE_PROG_END); //ステージエンドを親シーンに伝える
    } else {
    }
}

Stage01Controller::~Stage01Controller() {

}
