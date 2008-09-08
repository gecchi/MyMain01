#include "stdafx.h"


Stage02Scene::Stage02Scene(string prm_name) : DefaultScene(prm_name) {
}

void Stage02Scene::initialize() {

}

void Stage02Scene::processBehavior() {

	//DWORD frame = _dwFrame;
	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen start
	// gen end
}

void Stage02Scene::processFinal() {

	if (_dwFrame == 1) {
		_TRACE_("Stage02Scene::Finally 私はいきなり自分停止。GameMainSceneが解除してくれるまで待つす");
		this->declareStop(); //GameMainSceneが解除してくれる
	}
}


Stage02Scene::~Stage02Scene() {
}
