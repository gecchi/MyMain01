#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;



SceneProgress::SceneProgress(DefaultScene* prm_pScene, int prm_num_progress)  : GgafProgress(&(prm_pScene->_frame_of_behaving), prm_num_progress) {
    _pScene = prm_pScene;
}
void SceneProgress::affectSubScene(progress prm_FirstProgress, progress prm_EndProgress, const char* prm_FirstSubSceneName) {
    affectSubScene(prm_FirstProgress, prm_EndProgress, (DefaultScene*)(_pScene->getSubByName(prm_FirstSubSceneName)));
}
void SceneProgress::affectSubScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstSubScene) {
    DefaultScene* pSub = prm_pFirstSubScene;
    int num_progress = _pScene->_pProg->_num_progress;
    int num = 1;
    for (progress prog = prm_FirstProgress; prog <= prm_EndProgress; prog++, num++) {
        _mapProg2Scene[prog] = pSub;
        if (pSub->isLast() && prog < prm_EndProgress) {
            throwGgafCriticalException("SceneProgress::SceneProgress _pScene("<<_pScene->getName()<<")��"<<
                                       "�T�u�V�[��("<<prm_pFirstSubScene->getName()<<")���琔���ẴT�u�V�[���̐�������܂���(�T�u�V�[����������܂���)�B\n"<<
                                       "�i���ԍ����� "<<prm_FirstProgress<<"�`"<<prm_EndProgress<<" �� "<<(prm_EndProgress-prm_FirstProgress)<<" �ɑ΂��A\n"<<
                                       "�T�u�V�[������ "<<prm_pFirstSubScene->getName()<<"�`"<<pSub->getName()<<" �� "<<num<<"�ł����B");
        }
        pSub = (DefaultScene*)(pSub->getNext());

    }
    //    _mapSubScene[GAMESCENE_PROG_PRE_TITLE] = NEW GamePreTitleScene("PreGameTitle");
    //    _mapSubScene[GAMESCENE_PROG_TITLE]     = NEW GameTitleScene("GameTitle");
    //    _mapSubScene[GAMESCENE_PROG_DEMO]      = NEW GameDemoScene("GameDemo");
    //    _mapSubScene[GAMESCENE_PROG_BEGINNING] = NEW GameBeginningScene("GameBeginning");
    //    _mapSubScene[GAMESCENE_PROG_MAIN]      = NEW GameMainScene("GameMain");
    //    _mapSubScene[GAMESCENE_PROG_ENDING]    = NEW GameEndingScene("GameEnding");
    //    _mapSubScene[GAMESCENE_PROG_GAME_OVER] = NEW GameOverScene("GameOver");
}

void SceneProgress::changeWithFlippingSubScene(progress prm_progress) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->inactivate();
    } else {
        _TRACE_("���x����SceneProgress::changeWithFlippingSubScene �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[���̂��ߖ������܂����Bget()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeinSceneTree(0);
    } else {
        _TRACE_("���x����SceneProgress::changeWithFlippingSubScene �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[�����ߖ������܂����Bprm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithCrossfadingSubScene(progress prm_progress, frame prm_fade_frames) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->fadeoutSceneTree(prm_fade_frames);
        _mapProg2Scene[get()]->inactivateDelay(prm_fade_frames);
    } else {
        _TRACE_("���x����SceneProgress::changeWithFlippingSubScene �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[���̂��ߖ������܂����Bget()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeoutSceneTree(0);
        _mapProg2Scene[prm_progress]->fadeinSceneTree(prm_fade_frames);
    } else {
        _TRACE_("���x����SceneProgress::changeWithFlippingSubScene �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[�����ߖ������܂����Bprm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithOverlappingSubScene(progress prm_progress, frame prm_fade_frames) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->inactivateDelay(prm_fade_frames);
    } else {
        _TRACE_("���x����SceneProgress::changeWithOverlappingSubScene �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[���̂��ߖ������܂����Bget()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
    } else {
        _TRACE_("���x����SceneProgress::changeWithOverlappingSubScene �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[�����ߖ������܂����Bprm_progress="<<prm_progress);
    }
    change(prm_progress);
}



DefaultScene* SceneProgress::getSubScene() {
    return (_mapProg2Scene[get()]);
}
SceneProgress::~SceneProgress() {
}
