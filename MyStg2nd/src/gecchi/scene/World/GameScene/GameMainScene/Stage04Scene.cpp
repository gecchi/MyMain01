#include "stdafx.h"


Stage04Scene::Stage04Scene(string prm_name) : DefaultScene(prm_name) {
}

void Stage04Scene::initialize() {

}

void Stage04Scene::processBehavior() {
	//DWORD frame = _dwFrame;

	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen start
	// gen end

}

void Stage04Scene::processFinal() {

	if (_dwFrame == 1) {
		_TRACE_("Stage04Scene::Finally 私はいきなり自分停止。GameMainSceneが解除してくれるまで待つす");
		this->declareStop(); //GameMainSceneが解除してくれる
	}
}

Stage04Scene::~Stage04Scene() {
}
