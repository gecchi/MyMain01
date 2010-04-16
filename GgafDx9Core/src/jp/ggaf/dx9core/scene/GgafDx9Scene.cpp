#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Scene::GgafDx9Scene(const char* prm_name) : GgafMainScene(prm_name) {
    _papBgmCon = NEW GgafDx9BgmConnection*[MAX_BGM_PER_ACTOR];
    for (int i = 0; i < MAX_BGM_PER_ACTOR; i++) {
        _papBgmCon[i] = NULL;
    }
}
void GgafDx9Scene::fadeinBgm(int prm_id, int prm_frame) {
    _papBgmCon[prm_id]->view()->fade(prm_frame, DSBVOLUME_MAX);
}
void GgafDx9Scene::fadeoutBgm(int prm_id, int prm_frame) {
    _papBgmCon[prm_id]->view()->fade(prm_frame, DSBVOLUME_MIN);
}
void GgafDx9Scene::prepareBgm(int prm_id, const char* prm_bgm_name, int prm_cannel) {
    if (prm_id < 0 || prm_id >= MAX_BGM_PER_ACTOR) {
        throwGgafCriticalException("GgafDx9GeometricActor::prepareBGM() IDが範囲外です。0~"<<(MAX_BGM_PER_ACTOR-1)<<"でお願いします。prm_id="<<prm_id);
    }
    char idstr[129];
    sprintf(idstr, "%d/%s", prm_cannel, prm_bgm_name);
    _papBgmCon[prm_id] = (GgafDx9BgmConnection*)GgafDx9Sound::_pBgmManager->connect(idstr);
}

void GgafDx9Scene::playBgm(int prm_id,  int prm_volume, bool prm_is_loop) {
    if (prm_id < 0 || prm_id >= MAX_BGM_PER_ACTOR) {
        throwGgafCriticalException("GgafDx9GeometricActor::playSe() IDが範囲外です。0~"<<(MAX_BGM_PER_ACTOR-1)<<"でお願いします。prm_id="<<prm_id);
    }
    GgafDx9Universe* pUniverse = (GgafDx9Universe*)(GgafGod::_pGod->_pUniverse);
    _papBgmCon[prm_id]->view()->setVolume(prm_volume);
    _papBgmCon[prm_id]->view()->play(prm_is_loop);
}
void GgafDx9Scene::processPreJudgement() {
    for (int i = 0; i < MAX_BGM_PER_ACTOR; i++) {
        if (_papBgmCon[i]) {
            _papBgmCon[i]->view()->behave();
        }
    }

}
GgafDx9Scene::~GgafDx9Scene() {
    for (int i = 0; i < MAX_BGM_PER_ACTOR; i++) {
        if (_papBgmCon[i]) {
            _papBgmCon[i]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papBgmCon);
}
