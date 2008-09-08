#include "stdafx.h"


Stage03Scene::Stage03Scene(string prm_name) : DefaultScene(prm_name) {
}

void Stage03Scene::initialize() {

}

void Stage03Scene::processBehavior() {
	//DWORD frame = _dwFrame;

	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen start
	// gen end
}

void Stage03Scene::processFinal() {

	if (_dwFrame == 1) {
		_TRACE_("Stage03Scene::Finally 私はいきなり自分停止。GameMainSceneが解除してくれるまで待つす");
		this->declareStop(); //GameMainSceneが解除してくれる
	}
}

Stage03Scene::~Stage03Scene() {
}
