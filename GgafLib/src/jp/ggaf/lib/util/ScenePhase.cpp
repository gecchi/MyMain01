#include "jp/ggaf/lib/util/ScenePhase.h"

#include "jp/ggaf/lib/scene/DefaultScene.h"

using namespace GgafLib;

ScenePhase::ScenePhase(DefaultScene* prm_pScene)  : GgafCore::Phase(&(prm_pScene->_frame_of_behaving)) {
    _pScene = prm_pScene;
    _phase_no_next_promise = 0;
    _count_next_promise = 0;
}

void ScenePhase::relateChildScene(int prm_FirstPhase, int prm_EndPhase, const char* prm_FirstChildSceneName) {
    relateChildScene(prm_FirstPhase, prm_EndPhase, (DefaultScene*)(_pScene->getChildByName(prm_FirstChildSceneName)));
}

void ScenePhase::relateChildScene(int prm_FirstPhase, int prm_EndPhase, DefaultScene* prm_pFirstChildScene) {
    DefaultScene* pChild = prm_pFirstChildScene;
    int num = 1;
    _TRACE_(FUNC_NAME<<" �V�[��("<<_pScene->getName()<<")�́AScenePhase�̃t�F�[�Y�ԍ��Ǝq�V�[�����֘A�t���đ��삵�܂��B�Ή��͈ȉ��̒ʂ�B");
    for (int phs = prm_FirstPhase; phs <= prm_EndPhase; phs++, num++) {
        _mapPhase2Scene[phs] = pChild;
        if (pChild->isLast() && phs < prm_EndPhase) {
            throwCriticalException("_pScene("<<_pScene->getName()<<")��"
                                   "�q�V�[��("<<prm_pFirstChildScene->getName()<<")���琔���Ă̎q�V�[���̐�������܂���(�q�V�[����������܂���)�B\n"
                                   "�t�F�[�Y�ԍ����� "<<prm_FirstPhase<<"�`"<<prm_EndPhase<<" �� "<<(prm_EndPhase-prm_FirstPhase)<<" �ɑ΂��A\n"
                                   "�q�V�[������ "<<prm_pFirstChildScene->getName()<<"�`"<<pChild->getName()<<" �� "<<num<<"�ł����B");
        }
        _TRACE_("   �t�F�[�Y�ԍ�:"<<phs<<" ==> �V�[��:"<<pChild->getName()<<"");
        pChild = (DefaultScene*)(pChild->getNext());
    }
}

void ScenePhase::changeWithSceneFadein(int prm_phase_no, frame prm_fade_in ) {
    _TRACE_("ScenePhase::changeWithSceneFadein("<<prm_phase_no<<","<<prm_fade_in<<")  �V�[���t�F�[�Y:"<<getCurrent()<<"->"<<prm_phase_no<<" ");
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneFadein �V�[��("<<_pScene->getName()<<")�ŁA"
                "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�t�F�[�Y(prm_phase_no="<<prm_phase_no<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[prm_phase_no]->reset();
        _mapPhase2Scene[prm_phase_no]->activate();
        _mapPhase2Scene[prm_phase_no]->fadeinScene(prm_fade_in);
    }
    change(prm_phase_no);
}

void ScenePhase::changeWithSceneFlipping(int prm_phase_no) {
    _TRACE_("ScenePhase::changeWithSceneFlipping("<<prm_phase_no<<")  �V�[���t�F�[�Y:"<<getCurrent()<<"->"<<prm_phase_no<<" ");

    if (_mapPhase2Scene.find(getCurrent()) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneFlipping �V�[��("<<_pScene->getName()<<")�ŁA"
                "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��t�F�[�Y(get()="<<getCurrent()<<")�������ׁAinactivate() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[getCurrent()]->fadeoutBgmTree(0);
        _mapPhase2Scene[getCurrent()]->inactivate();
    }
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneFlipping �V�[��("<<_pScene->getName()<<")�ŁA"
                "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�t�F�[�Y(prm_phase_no="<<prm_phase_no<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[prm_phase_no]->reset();
        _mapPhase2Scene[prm_phase_no]->activate();
        _mapPhase2Scene[prm_phase_no]->fadeinScene(0);
    }
    change(prm_phase_no);
}

void ScenePhase::changeWithSceneCrossfading(int prm_phase_no, frame prm_cross_fade_frames) {
    _TRACE_("ScenePhase::changeWithSceneCrossfading("<<prm_phase_no<<","<<prm_cross_fade_frames<<")  �V�[���t�F�[�Y:"<<getCurrent()<<"->"<<prm_phase_no<<" ");
    if (_mapPhase2Scene.find(getCurrent()) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneCrossfading �V�[��("<<_pScene->getName()<<")�ŁA"
                "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��t�F�[�Y(get()="<<getCurrent()<<")�������ׁAinactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[getCurrent()]->fadeoutSceneWithBgmTree(prm_cross_fade_frames);
        _mapPhase2Scene[getCurrent()]->inactivateDelay(prm_cross_fade_frames); //�t�F�[�h������A�񊈓���
    }
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneCrossfading �V�[��("<<_pScene->getName()<<")�ŁA"
                "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�t�F�[�Y(prm_phase_no="<<prm_phase_no<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[prm_phase_no]->reset();
        _mapPhase2Scene[prm_phase_no]->activate();
        _mapPhase2Scene[prm_phase_no]->fadeoutSceneWithBgmTree(0);
        _mapPhase2Scene[prm_phase_no]->fadeinScene(prm_cross_fade_frames);
    }
    change(prm_phase_no);
}

void ScenePhase::changeWithSceneFadeoutFadein(int prm_phase_no, frame prm_fade_out, frame prm_fade_in) {
    _TRACE_("ScenePhase::changeWithSceneFadeoutFadein("<<prm_phase_no<<","<<prm_fade_out<<","<<prm_fade_in<<")  �V�[���t�F�[�Y:"<<getCurrent()<<"->"<<prm_phase_no<<" ");
    if (_mapPhase2Scene.find(getCurrent()) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneFadeoutFadein �V�[��("<<_pScene->getName()<<")�ŁA"
                "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��t�F�[�Y(get()="<<getCurrent()<<")�������ׁAinactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[getCurrent()]->fadeoutSceneWithBgmTree(prm_fade_out);
        _mapPhase2Scene[getCurrent()]->inactivateDelay(prm_fade_out);
    }
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneFadeoutFadein �V�[��("<<_pScene->getName()<<")�ŁA"
                "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�t�F�[�Y(prm_phase_no="<<prm_phase_no<<") �������ׁAactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[prm_phase_no]->reset();
        _mapPhase2Scene[prm_phase_no]->activateDelay(prm_fade_out);   //�����\��
        _mapPhase2Scene[prm_phase_no]->fadeoutSceneWithBgmTree(0);    //
        _mapPhase2Scene[prm_phase_no]->fadeinScene(prm_fade_in);  //activateDelay �Ȃ̂ŁAprm_fade_out �t���[����Ƀt�F�[�h�C������B
    }
    changeDelay(prm_phase_no, prm_fade_out); //�t�F�[�Y�ύX�\��
}

void ScenePhase::changeWithSceneOverlapping(int prm_phase_no, frame prm_overlapping_frames) {
    _TRACE_("ScenePhase::changeWithSceneOverlapping("<<prm_phase_no<<","<<prm_overlapping_frames<<")  �V�[���t�F�[�Y:"<<getCurrent()<<"->"<<prm_phase_no<<" ");
    if (_mapPhase2Scene.find(getCurrent()) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneOverlapping �V�[��("<<_pScene->getName()<<")�ŁA"
                "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��t�F�[�Y(get()="<<getCurrent()<<")�������ׁAinactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[getCurrent()]->inactivateDelay(prm_overlapping_frames);
    }
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneOverlapping �V�[��("<<_pScene->getName()<<")�ŁA"
                "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�t�F�[�Y(prm_phase_no="<<prm_phase_no<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[prm_phase_no]->reset();
        _mapPhase2Scene[prm_phase_no]->activate();
    }
    change(prm_phase_no);
}


DefaultScene* ScenePhase::getGazedScene() {
    if (_mapPhase2Scene.find(getCurrent()) == _mapPhase2Scene.end()) {
        return nullptr;
    } else {
        return (_mapPhase2Scene[getCurrent()]);
    }
}

DefaultScene* ScenePhase::getRelationScene(int prm_phase_no) {
    if (_mapPhase2Scene.find(prm_phase_no) == _mapPhase2Scene.end()) {
        return nullptr;
    } else {
        return (_mapPhase2Scene[prm_phase_no]);
    }
}

void ScenePhase::change(int prm_phase_no) {
    if (_count_next_promise > 0) {
        //�J�ڐ�\�񂪂��łɂ������ꍇ�Ƃ肯��
        //�J�ڐ�\�񂪁A�����change�Ɠ����J�ڐ�Ȃ炢����
        //�قȂ�ꍇ�́A�O��̃V�[���̊����\����������B
        if (prm_phase_no == _phase_no_next_promise) {
            //�J�ڐ�V�[���������A
            //_phase_no+1 �̃V�[���� ��activate()�ŁA����activateDelay()���㏑������̂�OK
        } else {
            //_phase_no_next_promise�� activateDelay() ���������B
            if (_mapPhase2Scene.find(_phase_no_next_promise) == _mapPhase2Scene.end()) {
                _TRACE_("�y���zScenePhase::change("<<prm_phase_no<<")  �V�[��("<<_pScene->getName()<<")�ŁA"
                        "�J�ڐ�\��t�F�[�Y(_phase_no_next_promise="<<_phase_no_next_promise<<")�����݂��܂������A�q�V�[���Ɗ֘A�t������Ă��Ȃ����߁A"
                        "�����\����������̑[�u�͍s���܂���B");
            } else {
                _TRACE_("�y���zScenePhase::change("<<prm_phase_no<<")  �V�[��("<<_pScene->getName()<<")�ŁA"
                        "�J�ڐ�\��t�F�[�Y(_phase_no_next_promise="<<_phase_no_next_promise<<")�����݂��A�֘A�V�[��("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<")���A"
                        "���� activateDelay() ����Ă��܂��B�������A�{ change() ��D�悵�A�V�[��("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<"�� activateDelay() ���������܂����B");
                _mapPhase2Scene[_phase_no_next_promise]->_frame_of_life_when_activation = 0;
            }
        }
        _phase_no_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Phase::change(prm_phase_no);
}

void ScenePhase::changeNothing() {
    if (_count_next_promise > 0) {
        //�J�ڐ�\�񂪂��łɂ������ꍇ�Ƃ肯��
        //_phase_no_next_promise�� activateDelay() ���������B
        if (_mapPhase2Scene.find(_phase_no_next_promise) == _mapPhase2Scene.end()) {
            _TRACE_("�y���zScenePhase::changeNothing() �V�[��("<<_pScene->getName()<<")�ŁA"
                    "�J�ڐ�\��t�F�[�Y(_phase_no_next_promise="<<_phase_no_next_promise<<")�����݂��܂������A�q�V�[���Ɗ֘A�t������Ă��Ȃ����߁A"
                    "�����\����������̑[�u�͍s���܂���B");
        } else {
            _TRACE_("�y���zScenePhase::changeNothing()  �V�[��("<<_pScene->getName()<<")�ŁA"
                    "�J�ڐ�\��t�F�[�Y(_phase_no_next_promise="<<_phase_no_next_promise<<")�����݂��A�֘A�V�[��("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<")���A"
                    "���� activateDelay() ����Ă��܂��B�������A�{ changeNothing() ��D�悵�A�V�[��("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<"�� activateDelay() ���������܂����B");
            _mapPhase2Scene[_phase_no_next_promise]->_frame_of_life_when_activation = 0;
        }
        _phase_no_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Phase::changeNothing();
}

void ScenePhase::changeNext() {
    if (_count_next_promise > 0) {
        //�J�ڐ�\�񂪂��łɂ������ꍇ�Ƃ肯��
        //�J�ڐ�\�񂪁A�����change�Ɠ����Ȃ炢����
        //�قȂ�ꍇ�́A�V�[���̊����\����������B
        if (_phase_no+1 == _phase_no_next_promise) {
            //�J�ڐ�V�[���������A
            //_phase_no+1 �̃V�[���� ��activate()�ŁA����activateDelay()���㏑������̂�OK
        } else {
            //_phase_no_next_promise�� activateDelay() ���������B
            if (_mapPhase2Scene.find(_phase_no_next_promise) == _mapPhase2Scene.end()) {
                _TRACE_("�y���zScenePhase::changeNext() _phase_no+1="<<(_phase_no+1)<<" �V�[��("<<_pScene->getName()<<")�ŁA"
                        "�J�ڐ�\��t�F�[�Y(_phase_no_next_promise="<<_phase_no_next_promise<<")�����݂��܂������A�q�V�[���Ɗ֘A�t������Ă��Ȃ����߁A"
                        "�����\����������̑[�u�͍s���܂���B");
            } else {
                _TRACE_("�y���zScenePhase::changeNext() _phase_no+1="<<(_phase_no+1)<<" �V�[��("<<_pScene->getName()<<")�ŁA"
                        "�J�ڐ�\��t�F�[�Y(_phase_no_next_promise="<<_phase_no_next_promise<<")�����݂��A�֘A�V�[��("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<")���A"
                        "���� activateDelay() ����Ă��܂��B�������A�{ changeNext() ��D�悵�A�V�[��("<<(_mapPhase2Scene[_phase_no_next_promise]->getName())<<"�� activateDelay() ���������܂����B");
                _mapPhase2Scene[_phase_no_next_promise]->_frame_of_life_when_activation = 0;
            }
        }
        _phase_no_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Phase::changeNext();
}

void ScenePhase::changeDelay(int prm_phase_no, frame prm_delay) {
    _phase_no_next_promise = prm_phase_no;
    _count_next_promise = (*_p_frame_counter) + prm_delay;
}

void ScenePhase::update() {
    if (_count_next_promise > 0) {
        if ((*_p_frame_counter) == _count_next_promise) {
            change(_phase_no_next_promise);
            _phase_no_next_promise = 0;
            _count_next_promise = 0;
        }
    }
    GgafCore::Phase::update();
}

ScenePhase::~ScenePhase() {
}
