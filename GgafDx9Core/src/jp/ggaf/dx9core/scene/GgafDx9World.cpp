#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafActor* GgafDx9World::_apAlphaActorList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL];
GgafActor* GgafDx9World::_pActors_DrawMaxDrawDepth = NULL;
GgafDx9Camera* GgafDx9World::_pCamera = NULL;

GgafDx9World::GgafDx9World(const char* prm_name) : GgafWorld(prm_name) {
    _class_name = "GgafDx9World";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
        _apAlphaActorList_DrawDepthLevel[i] = NULL;
    }
    _pCamera = NEW GgafDx9Camera("CAMERA");
    getLordActor()->accept(_pCamera);
}

void GgafDx9World::drawMain() {
    static GgafActor* pActor;

    //�s�����A�N�^�[�ȂǁA�i�K�����_�����O���s�v�ȃI�u�W�F�N�g��`��
    //��TODO�F�{���͎�O����`��̂ق��������ǂ����A�Ƃ肠��������ŁB
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //���i�����v���j���ɃJ�����O �捶����W�n
    pActor = _pActors_DrawMaxDrawDepth;
    while (pActor != NULL) {
        pActor->processDrawMain();
        pActor = pActor->_pNext_TheSameDrawDepthLevel;
    }
    _pActors_DrawMaxDrawDepth = NULL; //����̂��߂Ƀ��Z�b�g

    //��������ȂǁA�i�K�����_�����O���K�v�ȃI�u�W�F�N�g��`��
    //��TODO�FVIEW�̒���������������Z���Ɍ����Ă�����ۂ����Ƃ��O��BZ���ł����[�x�𑪂��Ă܂���B
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //�J�����O���Ȃ�
    for (int i = MAX_DRAW_DEPTH_LEVEL - 1; i >= 0; i--) {
        pActor = _apAlphaActorList_DrawDepthLevel[i];
        while (pActor != NULL) {
            pActor->processDrawMain();
            pActor = pActor->_pNext_TheSameDrawDepthLevel;
        }
        _apAlphaActorList_DrawDepthLevel[i] = NULL; //����̂��߂Ƀ��Z�b�g
    }
}

void GgafDx9World::setDrawDepthMaxLevel(GgafActor* prm_pActor) {
    static GgafActor* pActorTmp;
    if (_pActors_DrawMaxDrawDepth == NULL) {
        //�ŏ��̃A�N�^�[�̏ꍇ
        prm_pActor->_pNext_TheSameDrawDepthLevel = NULL;
        _pActors_DrawMaxDrawDepth = prm_pActor;
        return;
    } else {
        //���ɃA�N�^�[�o�^�ς݂������ꍇ
        pActorTmp = _pActors_DrawMaxDrawDepth;
        prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
        _pActors_DrawMaxDrawDepth = prm_pActor;
        return;
    }
}
void GgafDx9World::setDrawDepthLevel(int prm_draw_depth_level, GgafActor* prm_pActor) {
    static int draw_depth_level;
    static GgafActor* pActorTmp;
    //��������J�b�g
    if (prm_draw_depth_level > MAX_DRAW_DEPTH_LEVEL - 1) {
        draw_depth_level = MAX_DRAW_DEPTH_LEVEL - 1;
    } else if (prm_draw_depth_level < 0) {
        draw_depth_level = 0;
    } else {
        draw_depth_level = prm_draw_depth_level;
    }

    if (_apAlphaActorList_DrawDepthLevel[draw_depth_level] == NULL) {
        //����prm_draw_depth_level�ōŏ��̃A�N�^�[�̏ꍇ
        prm_pActor->_pNext_TheSameDrawDepthLevel = NULL;
        _apAlphaActorList_DrawDepthLevel[draw_depth_level] = prm_pActor;
    } else {
        //����prm_draw_depth_level�Ŋ��ɃA�N�^�[�o�^�ς݂������ꍇ
        pActorTmp = _apAlphaActorList_DrawDepthLevel[draw_depth_level];
        prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
        _apAlphaActorList_DrawDepthLevel[draw_depth_level] = prm_pActor;
    }
}

GgafDx9World::~GgafDx9World() {
//�s�p
//    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
//        if (_apAlphaActorList_DrawDepthLevel[i] != NULL) {
//            DELETE_IMPOSSIBLE_NULL(_apAlphaActorList_DrawDepthLevel[i]);
//        }
//    }
}
