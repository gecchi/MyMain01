#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;



SceneProgress::SceneProgress(DefaultScene* prm_pScene, int prm_num_progress)  : GgafProgress(&(prm_pScene->_frame_of_behaving), prm_num_progress) {
    _pScene = prm_pScene;
}
void SceneProgress::relatSubScene(progress prm_FirstProgress, progress prm_EndProgress, const char* prm_FirstSubSceneName) {
    relatSubScene(prm_FirstProgress, prm_EndProgress, (DefaultScene*)(_pScene->getSubByName(prm_FirstSubSceneName)));
}
void SceneProgress::relatSubScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstSubScene) {
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
}

void SceneProgress::changeWithScene(progress prm_progress) {
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeinSceneTree(0);
    } else {
        _TRACE_("���x����SceneProgress::changeScene �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[�����ߖ������܂����Bprm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneFlipping(progress prm_progress) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->inactivate();
    } else {
        _TRACE_("���x����SceneProgress::changeWithSceneFlipping �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[���̂��ߖ������܂����Bget()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeinSceneTree(0);
    } else {
        _TRACE_("���x����SceneProgress::changeWithSceneFlipping �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[�����ߖ������܂����Bprm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneCrossfading(progress prm_progress, frame prm_fade_frames) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->fadeoutSceneWithBgmTree(prm_fade_frames);
        _mapProg2Scene[get()]->inactivateDelay(prm_fade_frames);
    } else {
        _TRACE_("���x����SceneProgress::changeWithSceneCrossfading �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[���̂��ߖ������܂����Bget()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeoutSceneWithBgmTree(0);
        _mapProg2Scene[prm_progress]->fadeinSceneTree(prm_fade_frames);
    } else {
        _TRACE_("���x����SceneProgress::changeWithSceneCrossfading �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[�����ߖ������܂����Bprm_progress="<<prm_progress);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneFadeoutFadin(progress prm_progress, frame prm_fade_frames) {
}

void SceneProgress::changeWithSceneOverlapping(progress prm_progress, frame prm_frames) {
    if (_mapProg2Scene[get()]) {
        _mapProg2Scene[get()]->inactivateDelay(prm_frames);
    } else {
        _TRACE_("���x����SceneProgress::changeWithSceneOverlapping �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[���̂��ߖ������܂����Bget()="<<get());
    }
    if (_mapProg2Scene[prm_progress]) {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
    } else {
        _TRACE_("���x����SceneProgress::changeWithSceneOverlapping �V�[��("<<_pScene->getName()<<")�ɖ��G���g���[�̐i���V�[�����ߖ������܂����Bprm_progress="<<prm_progress);
    }
    change(prm_progress);
}



DefaultScene* SceneProgress::getGazedScene() {
    return (_mapProg2Scene[get()]);
}

DefaultScene* SceneProgress::getScene(progress prm_progress) {
    return (_mapProg2Scene[prm_progress]);
}

SceneProgress::~SceneProgress() {
}
