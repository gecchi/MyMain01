#include "jp/ggaf/lib/util/ScenePhase.h"

#include "jp/ggaf/lib/scene/DefaultScene.h"

using namespace GgafLib;

ScenePhase::ScenePhase(DefaultScene* prm_pScene)  : GgafCore::Phase(&(prm_pScene->_frame_of_behaving)) {
    _pScene = prm_pScene;
    _phase_next_promise = 0;
    _count_next_promise = 0;
}

void ScenePhase::relateChildScene(phase prm_FirstProgress, phase prm_EndProgress, const char* prm_FirstChildSceneName) {
    relateChildScene(prm_FirstProgress, prm_EndProgress, (DefaultScene*)(_pScene->getChildByName(prm_FirstChildSceneName)));
}

void ScenePhase::relateChildScene(phase prm_FirstProgress, phase prm_EndProgress, DefaultScene* prm_pFirstChildScene) {
    DefaultScene* pChild = prm_pFirstChildScene;
    int num = 1;
    _TRACE_(FUNC_NAME<<" �V�[��("<<_pScene->getName()<<")�́AScenePhase�̐i���ԍ��Ǝq�V�[�����֘A�t���đ��삵�܂��B�Ή��͈ȉ��̒ʂ�B");
    for (phase prog = prm_FirstProgress; prog <= prm_EndProgress; prog++, num++) {
        _mapPhase2Scene[prog] = pChild;
        if (pChild->isLast() && prog < prm_EndProgress) {
            throwCriticalException("_pScene("<<_pScene->getName()<<")��"
                                       "�q�V�[��("<<prm_pFirstChildScene->getName()<<")���琔���Ă̎q�V�[���̐�������܂���(�q�V�[����������܂���)�B\n"
                                       "�i���ԍ����� "<<prm_FirstProgress<<"�`"<<prm_EndProgress<<" �� "<<(prm_EndProgress-prm_FirstProgress)<<" �ɑ΂��A\n"
                                       "�q�V�[������ "<<prm_pFirstChildScene->getName()<<"�`"<<pChild->getName()<<" �� "<<num<<"�ł����B");
        }
        _TRACE_("   �i���ԍ�:"<<prog<<" ==> �V�[��:"<<pChild->getName()<<"");
        pChild = (DefaultScene*)(pChild->getNext());
    }
}

void ScenePhase::changeWithSceneFadein(phase prm_phase, frame prm_fade_in ) {
    _TRACE_("ScenePhase::changeWithSceneFadein("<<prm_phase<<","<<prm_fade_in<<")  �i���V�[��:"<<get()<<"->"<<prm_phase<<" ");
    if (_mapPhase2Scene.find(prm_phase) == _mapPhase2Scene.end()) {
                _TRACE_("�y�x���zScenePhase::changeWithSceneFadein �V�[��("<<_pScene->getName()<<")�ŁA"
            "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�i��(prm_phase="<<prm_phase<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[prm_phase]->reset();
        _mapPhase2Scene[prm_phase]->activate();
        _mapPhase2Scene[prm_phase]->fadeinScene(prm_fade_in);
    }
    change(prm_phase);
}

void ScenePhase::changeWithSceneFlipping(phase prm_phase) {
    _TRACE_("ScenePhase::changeWithSceneFlipping("<<prm_phase<<")  �i���V�[��:"<<get()<<"->"<<prm_phase<<" ");

    if (_mapPhase2Scene.find(get()) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneFlipping �V�[��("<<_pScene->getName()<<")�ŁA"
            "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��i��(get()="<<get()<<")�������ׁAinactivate() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[get()]->fadeoutBgmTree(0);
        _mapPhase2Scene[get()]->inactivate();
    }
    if (_mapPhase2Scene.find(prm_phase) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneFlipping �V�[��("<<_pScene->getName()<<")�ŁA"
            "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�i��(prm_phase="<<prm_phase<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[prm_phase]->reset();
        _mapPhase2Scene[prm_phase]->activate();
        _mapPhase2Scene[prm_phase]->fadeinScene(0);
    }
    change(prm_phase);
}

void ScenePhase::changeWithSceneCrossfading(phase prm_phase, frame prm_cross_fade_frames) {
    _TRACE_("ScenePhase::changeWithSceneCrossfading("<<prm_phase<<","<<prm_cross_fade_frames<<")  �i���V�[��:"<<get()<<"->"<<prm_phase<<" ");
    if (_mapPhase2Scene.find(get()) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneCrossfading �V�[��("<<_pScene->getName()<<")�ŁA"
            "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��i��(get()="<<get()<<")�������ׁAinactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[get()]->fadeoutSceneWithBgmTree(prm_cross_fade_frames);
        _mapPhase2Scene[get()]->inactivateDelay(prm_cross_fade_frames); //�t�F�[�h������A�񊈓���
    }
    if (_mapPhase2Scene.find(prm_phase) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneCrossfading �V�[��("<<_pScene->getName()<<")�ŁA"
            "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�i��(prm_phase="<<prm_phase<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[prm_phase]->reset();
        _mapPhase2Scene[prm_phase]->activate();
        _mapPhase2Scene[prm_phase]->fadeoutSceneWithBgmTree(0);
        _mapPhase2Scene[prm_phase]->fadeinScene(prm_cross_fade_frames);
    }
    change(prm_phase);
}

void ScenePhase::changeWithSceneFadeoutFadein(phase prm_phase, frame prm_fade_out, frame prm_fade_in) {
    _TRACE_("ScenePhase::changeWithSceneFadeoutFadein("<<prm_phase<<","<<prm_fade_out<<","<<prm_fade_in<<")  �i���V�[��:"<<get()<<"->"<<prm_phase<<" ");
    if (_mapPhase2Scene.find(get()) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneFadeoutFadein �V�[��("<<_pScene->getName()<<")�ŁA"
            "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��i��(get()="<<get()<<")�������ׁAinactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[get()]->fadeoutSceneWithBgmTree(prm_fade_out);
        _mapPhase2Scene[get()]->inactivateDelay(prm_fade_out);
    }
    if (_mapPhase2Scene.find(prm_phase) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneFadeoutFadein �V�[��("<<_pScene->getName()<<")�ŁA"
            "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�i��(prm_phase="<<prm_phase<<") �������ׁAactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[prm_phase]->reset();
        _mapPhase2Scene[prm_phase]->activateDelay(prm_fade_out);   //�����\��
        _mapPhase2Scene[prm_phase]->fadeoutSceneWithBgmTree(0);    //
        _mapPhase2Scene[prm_phase]->fadeinScene(prm_fade_in);  //activateDelay �Ȃ̂ŁAprm_fade_out �t���[����Ƀt�F�[�h�C������B
    }
    changeDelay(prm_phase, prm_fade_out); //�i���ύX�\��
}

void ScenePhase::changeWithSceneOverlapping(phase prm_phase, frame prm_overlapping_frames) {
    _TRACE_("ScenePhase::changeWithSceneOverlapping("<<prm_phase<<","<<prm_overlapping_frames<<")  �i���V�[��:"<<get()<<"->"<<prm_phase<<" ");
    if (_mapPhase2Scene.find(get()) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneOverlapping �V�[��("<<_pScene->getName()<<")�ŁA"
            "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڌ��i��(get()="<<get()<<")�������ׁAinactivateDelay() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[get()]->inactivateDelay(prm_overlapping_frames);
    }
    if (_mapPhase2Scene.find(prm_phase) == _mapPhase2Scene.end()) {
        _TRACE_("�y�x���zScenePhase::changeWithSceneOverlapping �V�[��("<<_pScene->getName()<<")�ŁA"
            "�q�V�[���Ɗ֘A�t������Ă��Ȃ��J�ڐ�i��(prm_phase="<<prm_phase<<") �������ׁAactivate() ���ł��܂���ł����B");
    } else {
        _mapPhase2Scene[prm_phase]->reset();
        _mapPhase2Scene[prm_phase]->activate();
    }
    change(prm_phase);
}


DefaultScene* ScenePhase::getGazedScene() {
    if (_mapPhase2Scene.find(get()) == _mapPhase2Scene.end()) {
        return nullptr;
    } else {
        return (_mapPhase2Scene[get()]);
    }
}

DefaultScene* ScenePhase::getScene(phase prm_phase) {
    if (_mapPhase2Scene.find(prm_phase) == _mapPhase2Scene.end()) {
        return nullptr;
    } else {
        return (_mapPhase2Scene[prm_phase]);
    }
}

void ScenePhase::change(phase prm_phase) {
    if (_count_next_promise > 0) {
        //�J�ڐ�\�񂪂��łɂ������ꍇ�Ƃ肯��
        //�J�ڐ�\�񂪁A�����change�Ɠ����J�ڐ�Ȃ炢����
        //�قȂ�ꍇ�́A�O��̃V�[���̊����\����������B
        if (prm_phase == _phase_next_promise) {
            //�J�ڐ�V�[���������A
            //_phase+1 �̃V�[���� ��activate()�ŁA����activateDelay()���㏑������̂�OK
        } else {
            //_phase_next_promise�� activateDelay() ���������B
            if (_mapPhase2Scene.find(_phase_next_promise) == _mapPhase2Scene.end()) {
                _TRACE_("�y���zScenePhase::change("<<prm_phase<<")  �V�[��("<<_pScene->getName()<<")�ŁA"
                    "�J�ڐ�\��i��(_phase_next_promise="<<_phase_next_promise<<")�����݂��܂������A�q�V�[���Ɗ֘A�t������Ă��Ȃ����߁A"
                    "�����\����������̑[�u�͍s���܂���B");
            } else {
                _TRACE_("�y���zScenePhase::change("<<prm_phase<<")  �V�[��("<<_pScene->getName()<<")�ŁA"
                    "�J�ڐ�\��i��(_phase_next_promise="<<_phase_next_promise<<")�����݂��A�֘A�V�[��("<<(_mapPhase2Scene[_phase_next_promise]->getName())<<")���A"
                    "���� activateDelay() ����Ă��܂��B�������A�{ change() ��D�悵�A�V�[��("<<(_mapPhase2Scene[_phase_next_promise]->getName())<<"�� activateDelay() ���������܂����B");
                _mapPhase2Scene[_phase_next_promise]->_frame_of_life_when_activation = 0;
            }
        }
        _phase_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Phase::change(prm_phase);
}

void ScenePhase::changeNothing() {
    if (_count_next_promise > 0) {
        //�J�ڐ�\�񂪂��łɂ������ꍇ�Ƃ肯��
        //_phase_next_promise�� activateDelay() ���������B
        if (_mapPhase2Scene.find(_phase_next_promise) == _mapPhase2Scene.end()) {
            _TRACE_("�y���zScenePhase::changeNothing() �V�[��("<<_pScene->getName()<<")�ŁA"
                "�J�ڐ�\��i��(_phase_next_promise="<<_phase_next_promise<<")�����݂��܂������A�q�V�[���Ɗ֘A�t������Ă��Ȃ����߁A"
                "�����\����������̑[�u�͍s���܂���B");
        } else {
            _TRACE_("�y���zScenePhase::changeNothing()  �V�[��("<<_pScene->getName()<<")�ŁA"
                "�J�ڐ�\��i��(_phase_next_promise="<<_phase_next_promise<<")�����݂��A�֘A�V�[��("<<(_mapPhase2Scene[_phase_next_promise]->getName())<<")���A"
                "���� activateDelay() ����Ă��܂��B�������A�{ changeNothing() ��D�悵�A�V�[��("<<(_mapPhase2Scene[_phase_next_promise]->getName())<<"�� activateDelay() ���������܂����B");
            _mapPhase2Scene[_phase_next_promise]->_frame_of_life_when_activation = 0;
        }
        _phase_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Phase::changeNothing();
}

void ScenePhase::changeNext() {
    if (_count_next_promise > 0) {
        //�J�ڐ�\�񂪂��łɂ������ꍇ�Ƃ肯��
        //�J�ڐ�\�񂪁A�����change�Ɠ����Ȃ炢����
        //�قȂ�ꍇ�́A�V�[���̊����\����������B
        if (_phase+1 == _phase_next_promise) {
            //�J�ڐ�V�[���������A
            //_phase+1 �̃V�[���� ��activate()�ŁA����activateDelay()���㏑������̂�OK
        } else {
            //_phase_next_promise�� activateDelay() ���������B
            if (_mapPhase2Scene.find(_phase_next_promise) == _mapPhase2Scene.end()) {
                _TRACE_("�y���zScenePhase::changeNext() _phase+1="<<(_phase+1)<<" �V�[��("<<_pScene->getName()<<")�ŁA"
                "�J�ڐ�\��i��(_phase_next_promise="<<_phase_next_promise<<")�����݂��܂������A�q�V�[���Ɗ֘A�t������Ă��Ȃ����߁A"
                "�����\����������̑[�u�͍s���܂���B");
            } else {
                _TRACE_("�y���zScenePhase::changeNext() _phase+1="<<(_phase+1)<<" �V�[��("<<_pScene->getName()<<")�ŁA"
                "�J�ڐ�\��i��(_phase_next_promise="<<_phase_next_promise<<")�����݂��A�֘A�V�[��("<<(_mapPhase2Scene[_phase_next_promise]->getName())<<")���A"
                "���� activateDelay() ����Ă��܂��B�������A�{ changeNext() ��D�悵�A�V�[��("<<(_mapPhase2Scene[_phase_next_promise]->getName())<<"�� activateDelay() ���������܂����B");
                _mapPhase2Scene[_phase_next_promise]->_frame_of_life_when_activation = 0;
            }
        }
        _phase_next_promise = 0;
        _count_next_promise = 0;
    }
    GgafCore::Phase::changeNext();
}

void ScenePhase::changeDelay(phase prm_phase, frame prm_delay) {
    _phase_next_promise = prm_phase;
    _count_next_promise = (*_p_frame_counter) + prm_delay;
}

void ScenePhase::update() {
    if (_count_next_promise > 0) {
        if ((*_p_frame_counter) == _count_next_promise) {
            change(_phase_next_promise);
            _phase_next_promise = 0;
            _count_next_promise = 0;
        }
    }
    GgafCore::Phase::update();
}

ScenePhase::~ScenePhase() {
}
