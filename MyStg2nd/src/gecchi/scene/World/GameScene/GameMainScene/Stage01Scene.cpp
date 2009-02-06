#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01Scene::Stage01Scene(const char* prm_name) : StageScene(prm_name) {
	_pStage01Main = NEW Stage01MainScene("Stage01Main");
	_pStage01Main->refrainAlone();
    addSubLast(_pStage01Main);

	_pBackGround01 = NEW BackGround01Plate("BACKGOROUND01", "");
	_pBackGround01->refrain();
    getLordActor()->accept(KIND_EFFECT, _pBackGround01);

    _pBgmLead_st1 = (GgafDx9BgmLead*)GgafDx9Sound::_pBgmManager->lead("JM5");
    //GameMainSceneが解除してくれる
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::initialize() {
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::processBehavior() {
    if (getProgress() == STAGE01_PROG_INIT) {
    	setProgress(STAGE01_PROG_BEGIN);
    }
    if (isChangeProgress(STAGE01_PROG_BEGIN)) {
    	_pBackGround01->act();
    	_pBgmLead_st1->getResource()->play(false);
        _dwFrame_Begin = 0;
    } else if (getProgress() == GAMEDEMO_PROG_BEGIN) {
        //タイトル活動ループ
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 120) {
        	_pStage01Main->actAlone();
            setProgress(STAGE01_PROG_PLAY);
        }
    }

}

void Stage01Scene::processJudgement() {
    //当たり判定処理実行
    //詳細は ACTOR.xls の hantei シート
    if (_dwFrame >= 2) {
        executeBumpChkHeadActors(KIND_CHIKEI, KIND_MY | KIND_MY_SHOT_GU | KIND_MY_SHOT_CHOKI | KIND_MY_SHOT_NOMAL
                | KIND_ENEMY_SHOT_GU | KIND_ENEMY_SHOT_CHOKI | KIND_ENEMY_SHOT_NOMAL | KIND_OTHER);
        executeBumpChkHeadActors(KIND_ENEMY | KIND_ENEMY_SHOT_GU | KIND_ENEMY_SHOT_CHOKI | KIND_ENEMY_SHOT_PA
                | KIND_ENEMY_SHOT_NOMAL | KIND_OTHER, KIND_MY | KIND_MY_SHOT_GU | KIND_MY_SHOT_CHOKI | KIND_MY_SHOT_PA
                | KIND_MY_SHOT_NOMAL);
        executeBumpChkHeadActors(KIND_OTHER, KIND_ENEMY | KIND_ENEMY_SHOT_GU | KIND_ENEMY_SHOT_CHOKI
                | KIND_ENEMY_SHOT_PA | KIND_ENEMY_SHOT_NOMAL | KIND_OTHER);
        executeBumpChkHeadActors(KIND_MY_SHOT_CHOKI | KIND_MY_SHOT_NOMAL, KIND_ENEMY_SHOT_GU);
        executeBumpChkHeadActors(KIND_MY_SHOT_CHOKI, KIND_MY_SHOT_GU);
    }
}

void Stage01Scene::processFinal() {

}

Stage01Scene::~Stage01Scene() {
    RELEASE_IMPOSSIBLE_NULL(_pBgmLead_st1);
}
