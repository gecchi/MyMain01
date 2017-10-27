#include "jp/ggaf/lib/util/SceneProgress.h"

#include "jp/ggaf/lib/scene/DefaultScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SceneProgress::SceneProgress(DefaultScene* prm_pScene, int prm_num_progress)  : GgafProgress(&(prm_pScene->_frame_of_behaving), prm_num_progress) {
    _pScene = prm_pScene;
    _progress_next_promise = 0;
    _count_next_promise = 0;
}

void SceneProgress::relateSubScene(progress prm_FirstProgress, progress prm_EndProgress, const char* prm_FirstSubSceneName) {
    relateSubScene(prm_FirstProgress, prm_EndProgress, (DefaultScene*)(_pScene->getSubByName(prm_FirstSubSceneName)));
}

void SceneProgress::relateSubScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstSubScene) {
    DefaultScene* pSub = prm_pFirstSubScene;
    int num = 1;
    _TRACE_(FUNC_NAME<<" �V�[��("<<_pScene->getName()<<")�́ASceneProgress�̐i���ԍ��ƃT�u�V�[�����֘A�t���đ��삵�܂��B�Ή��͈ȉ��̒ʂ�B");
    for (progress prog = prm_FirstProgress; prog <= prm_EndProgress; prog++, num++) {
        _mapProg2Scene[prog] = pSub;
        if (pSub->isLast() && prog < prm_EndProgress) {
            throwGgafCriticalException("_pScene("<<_pScene->getName()<<")��"
                                       "�T�u�V�[��("<<prm_pFirstSubScene->getName()<<")���琔���ẴT�u�V�[���̐�������܂���(�T�u�V�[����������܂���)�B\n"
                                       "�i���ԍ����� "<<prm_FirstProgress<<"�`"<<prm_EndProgress<<" �� "<<(prm_EndProgress-prm_FirstProgress)<<" �ɑ΂��A\n"
                                       "�T�u�V�[������ "<<prm_pFirstSubScene->getName()<<"�`"<<pSub->getName()<<" �� "<<num<<"�ł����B");
        }
        _TRACE_("   �i���ԍ�:"<<prog<<" ==> �V�[��:"<<pSub->getName()<<"");
        pSub = (DefaultScene*)(pSub->getNext());
    }
}

void SceneProgress::changeWithScene(progress prm_progress) {
    _TRACE_("SceneProgress::changeWithScene("<<prm_progress<<")  �i���V�[��:"<<get()<<"->"<<prm_progress<<" ");
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
                _TRACE_("���x����SceneProgress::changeWithScene �V�[��("<<_pScene->getName()<<")�ŁA"
            "�T�u�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�i��(prm_progress="<<prm_progress<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeinSceneTree(0);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneFlipping(progress prm_progress) {
    _TRACE_("SceneProgress::changeWithSceneFlipping("<<prm_progress<<")  �i���V�[��:"<<get()<<"->"<<prm_progress<<" ");

    if (_mapProg2Scene.find(get()) == _mapProg2Scene.end()) {
        _TRACE_("���x����SceneProgress::changeWithSceneFlipping �V�[��("<<_pScene->getName()<<")�ŁA"
            "�T�u�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��i��(get()="<<get()<<")�������ׁAinactivate() ���ł��܂���ł����B");
    } else {
        _mapProg2Scene[get()]->inactivate();
    }
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
        _TRACE_("���x����SceneProgress::changeWithSceneFlipping �V�[��("<<_pScene->getName()<<")�ŁA"
            "�T�u�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�i��(prm_progress="<<prm_progress<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeinSceneTree(0);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneCrossfading(progress prm_progress, frame prm_cross_fade_frames) {
    _TRACE_("SceneProgress::changeWithSceneCrossfading("<<prm_progress<<","<<prm_cross_fade_frames<<")  �i���V�[��:"<<get()<<"->"<<prm_progress<<" ");
    if (_mapProg2Scene.find(get()) == _mapProg2Scene.end()) {
        _TRACE_("���x����SceneProgress::changeWithSceneCrossfading �V�[��("<<_pScene->getName()<<")�ŁA"
            "�T�u�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��i��(get()="<<get()<<")�������ׁAinactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapProg2Scene[get()]->fadeoutSceneWithBgmTree(prm_cross_fade_frames);
        _mapProg2Scene[get()]->inactivateDelay(prm_cross_fade_frames); //�t�F�[�h������A�񊈓���
    }
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
        _TRACE_("���x����SceneProgress::changeWithSceneCrossfading �V�[��("<<_pScene->getName()<<")�ŁA"
            "�T�u�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�i��(prm_progress="<<prm_progress<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
        _mapProg2Scene[prm_progress]->fadeoutSceneWithBgmTree(0);
        _mapProg2Scene[prm_progress]->fadeinSceneTree(prm_cross_fade_frames);
    }
    change(prm_progress);
}

void SceneProgress::changeWithSceneFadeoutFadein(progress prm_progress, frame prm_fade_out, frame prm_fade_in) {
    _TRACE_("SceneProgress::changeWithSceneFadeoutFadein("<<prm_progress<<","<<prm_fade_out<<","<<prm_fade_in<<")  �i���V�[��:"<<get()<<"->"<<prm_progress<<" ");
    if (_mapProg2Scene.find(get()) == _mapProg2Scene.end()) {
        _TRACE_("���x����SceneProgress::changeWithSceneFadeoutFadein �V�[��("<<_pScene->getName()<<")�ŁA"
            "�T�u�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��i��(get()="<<get()<<")�������ׁAinactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapProg2Scene[get()]->fadeoutSceneWithBgmTree(prm_fade_out);
        _mapProg2Scene[get()]->inactivateDelay(prm_fade_out);
    }
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
        _TRACE_("���x����SceneProgress::changeWithSceneFadeoutFadein �V�[��("<<_pScene->getName()<<")�ŁA"
            "�T�u�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�i��(prm_progress="<<prm_progress<<") �������ׁAactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activateDelay(prm_fade_out);   //�����\��
        _mapProg2Scene[prm_progress]->fadeoutSceneWithBgmTree(0);    //
        _mapProg2Scene[prm_progress]->fadeinSceneTree(prm_fade_in);  //activateDelay �Ȃ̂ŁAprm_fade_out �t���[����Ƀt�F�[�h�C������B
    }
    changeDelay(prm_progress, prm_fade_out); //�i���ύX�\��
}

void SceneProgress::changeWithSceneOverlapping(progress prm_progress, frame prm_overlapping_frames) {
    _TRACE_("SceneProgress::changeWithSceneOverlapping("<<prm_progress<<","<<prm_overlapping_frames<<")  �i���V�[��:"<<get()<<"->"<<prm_progress<<" ");
    if (_mapProg2Scene.find(get()) == _mapProg2Scene.end()) {
        _TRACE_("���x����SceneProgress::changeWithSceneOverlapping �V�[��("<<_pScene->getName()<<")�ŁA"
            "�T�u�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��i��(get()="<<get()<<")�������ׁAinactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapProg2Scene[get()]->inactivateDelay(prm_overlapping_frames);
    }
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
        _TRACE_("���x����SceneProgress::changeWithSceneOverlapping �V�[��("<<_pScene->getName()<<")�ŁA"
            "�T�u�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�i��(prm_progress="<<prm_progress<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapProg2Scene[prm_progress]->reset();
        _mapProg2Scene[prm_progress]->activate();
    }
    change(prm_progress);
}


DefaultScene* SceneProgress::getGazedScene() {
    if (_mapProg2Scene.find(get()) == _mapProg2Scene.end()) {
        return nullptr;
    } else {
        return (_mapProg2Scene[get()]);
    }
}

DefaultScene* SceneProgress::getScene(progress prm_progress) {
    if (_mapProg2Scene.find(prm_progress) == _mapProg2Scene.end()) {
        return nullptr;
    } else {
        return (_mapProg2Scene[prm_progress]);
    }
}

void SceneProgress::change(progress prm_progress) {
    if (_count_next_promise > 0) {
        //�J�ڐ�\�񂪂��łɂ������ꍇ�Ƃ肯��
        //�J�ڐ�\�񂪁A�����change�Ɠ����J�ڐ�Ȃ炢����
        //�قȂ�ꍇ�́A�O��̃V�[���̊����\����������B
        if (prm_progress == _progress_next_promise) {
            //�J�ڐ�V�[���������A
            //_progress+1 �̃V�[���� ��activate()�ŁA����activateDelay()���㏑������̂�OK
        } else {
            //_progress_next_promise�� activateDelay() ���������B
            if (_mapProg2Scene.find(_progress_next_promise) == _mapProg2Scene.end()) {
                _TRACE_("�����SceneProgress::change("<<prm_progress<<")  �V�[��("<<_pScene->getName()<<")�ŁA"
                    "�J�ڐ�\��i��(_progress_next_promise="<<_progress_next_promise<<")�����݂��܂������A�T�u�V�[���Ɗ֘A�t������Ă��Ȃ����߁A"
                    "�����\����������̑[�u�͍s���܂���B");
            } else {
                _TRACE_("�����SceneProgress::change("<<prm_progress<<")  �V�[��("<<_pScene->getName()<<")�ŁA"
                    "�J�ڐ�\��i��(_progress_next_promise="<<_progress_next_promise<<")�����݂��A�֘A�V�[��("<<(_mapProg2Scene[_progress_next_promise]->getName())<<")���A"
                    "���� activateDelay() ����Ă��܂��B�������A�{ change() ��D�悵�A�V�[��("<<(_mapProg2Scene[_progress_next_promise]->getName())<<"�� activateDelay() ���������܂����B");
                _mapProg2Scene[_progress_next_promise]->_frame_of_life_when_activation = 0;
            }
        }
        _progress_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafProgress::change(prm_progress);
}

void SceneProgress::changeNothing() {
    if (_count_next_promise > 0) {
        //�J�ڐ�\�񂪂��łɂ������ꍇ�Ƃ肯��
        //_progress_next_promise�� activateDelay() ���������B
        if (_mapProg2Scene.find(_progress_next_promise) == _mapProg2Scene.end()) {
            _TRACE_("�����SceneProgress::changeNothing() �V�[��("<<_pScene->getName()<<")�ŁA"
                "�J�ڐ�\��i��(_progress_next_promise="<<_progress_next_promise<<")�����݂��܂������A�T�u�V�[���Ɗ֘A�t������Ă��Ȃ����߁A"
                "�����\����������̑[�u�͍s���܂���B");
        } else {
            _TRACE_("�����SceneProgress::changeNothing()  �V�[��("<<_pScene->getName()<<")�ŁA"
                "�J�ڐ�\��i��(_progress_next_promise="<<_progress_next_promise<<")�����݂��A�֘A�V�[��("<<(_mapProg2Scene[_progress_next_promise]->getName())<<")���A"
                "���� activateDelay() ����Ă��܂��B�������A�{ changeNothing() ��D�悵�A�V�[��("<<(_mapProg2Scene[_progress_next_promise]->getName())<<"�� activateDelay() ���������܂����B");
            _mapProg2Scene[_progress_next_promise]->_frame_of_life_when_activation = 0;
        }
        _progress_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafProgress::changeNothing();
}

void SceneProgress::changeNext() {
    if (_count_next_promise > 0) {
        //�J�ڐ�\�񂪂��łɂ������ꍇ�Ƃ肯��
        //�J�ڐ�\�񂪁A�����change�Ɠ����Ȃ炢����
        //�قȂ�ꍇ�́A�V�[���̊����\����������B
        if (_progress+1 == _progress_next_promise) {
            //�J�ڐ�V�[���������A
            //_progress+1 �̃V�[���� ��activate()�ŁA����activateDelay()���㏑������̂�OK
        } else {
            //_progress_next_promise�� activateDelay() ���������B
            if (_mapProg2Scene.find(_progress_next_promise) == _mapProg2Scene.end()) {
                _TRACE_("�����SceneProgress::changeNext() _progress+1="<<(_progress+1)<<" �V�[��("<<_pScene->getName()<<")�ŁA"
                "�J�ڐ�\��i��(_progress_next_promise="<<_progress_next_promise<<")�����݂��܂������A�T�u�V�[���Ɗ֘A�t������Ă��Ȃ����߁A"
                "�����\����������̑[�u�͍s���܂���B");
            } else {
                _TRACE_("�����SceneProgress::changeNext() _progress+1="<<(_progress+1)<<" �V�[��("<<_pScene->getName()<<")�ŁA"
                "�J�ڐ�\��i��(_progress_next_promise="<<_progress_next_promise<<")�����݂��A�֘A�V�[��("<<(_mapProg2Scene[_progress_next_promise]->getName())<<")���A"
                "���� activateDelay() ����Ă��܂��B�������A�{ changeNext() ��D�悵�A�V�[��("<<(_mapProg2Scene[_progress_next_promise]->getName())<<"�� activateDelay() ���������܂����B");
                _mapProg2Scene[_progress_next_promise]->_frame_of_life_when_activation = 0;
            }
        }
        _progress_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafProgress::changeNext();
}

void SceneProgress::changeDelay(progress prm_progress, frame prm_delay) {
    _progress_next_promise = prm_progress;
    _count_next_promise = (*_p_frame_counter) + prm_delay;
}

void SceneProgress::update() {
    if (_count_next_promise > 0) {
        if ((*_p_frame_counter) == _count_next_promise) {
            change(_progress_next_promise);
            _progress_next_promise = 0;
            _count_next_promise = 0;
        }
    }
    GgafProgress::update();
}

SceneProgress::~SceneProgress() {
}
