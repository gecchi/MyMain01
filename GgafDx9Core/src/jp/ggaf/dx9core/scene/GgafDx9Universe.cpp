#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9DrawableActor* GgafDx9Universe::_apAlphaActorList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL];
GgafDx9DrawableActor* GgafDx9Universe::_pActors_DrawMaxDrawDepth = NULL;
GgafDx9DrawableActor* GgafDx9Universe::_pActor_DrawActive = NULL;
GgafDx9Camera* GgafDx9Universe::_pCamera = NULL;

int GgafDx9Universe::_X_goneLeft   = 0;
int GgafDx9Universe::_X_goneRight  = 0;
int GgafDx9Universe::_Y_goneTop    = 0;
int GgafDx9Universe::_Y_goneBottom = 0;
int GgafDx9Universe::_Z_goneFar   = 0;
int GgafDx9Universe::_Z_goneNear  = 0;

GgafDx9Universe::GgafDx9Universe(const char* prm_name) : GgafUniverse(prm_name) {
    _class_name = "GgafDx9Universe";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
        _apAlphaActorList_DrawDepthLevel[i] = NULL;
    }
    //��ɃJ������NEW���Ă����Ȃ��Ƃ����Ȃ��B
    _pCamera = NEW GgafDx9Camera("CAMERA", PI * 80.0f / 180.0f, GGAFDX9_PROPERTY(GAME_SPACE_DEPTH));    //FovX����p80�x�A�[���~15.0
    getLordActor()->addSubGroup(_pCamera);
    _pActor_DrawActive = NULL;

    //�J�����̎ʂ�������Ɨ]�T���������͈́B
    _X_goneLeft   = GgafDx9Camera::_X_ScreenLeft * 4;
    _X_goneRight  = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Y_goneTop    = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Y_goneBottom = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Z_goneFar   = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Z_goneNear  = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _TRACE_("Gone=X ("<<_X_goneLeft<<" ~ "<<_X_goneRight<<") Y("<<_Y_goneBottom<<" ~ "<<_Y_goneTop<<") Z("<<_Z_goneFar<<" ~ "<<_Z_goneNear<<")");

    _pRing_pSeArray = NEW GgafLinkedListRing<SeArray>();
    for (int i = 0; i < GGAF_SAYONARA_DELAY; i++) { //GGAF_SAYONARA_DELAY = 180
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }

}

void GgafDx9Universe::registSe(GgafDx9Se* prm_pSe, DWORD prm_delay) {
    _pRing_pSeArray->getNext(prm_delay+1)->add(prm_pSe);
}

void GgafDx9Universe::processPreJudgement() {
    GgafUniverse::processPreJudgement();
    //SE��炷
    SeArray* pSeArray = _pRing_pSeArray->next(); //��i�߂�SE�z��擾
    if (pSeArray->_p > 0) {
        for (int p = 0; p > pSeArray->_p; p++) {
            pSeArray->_apSe[p]->play(DSBPAN_CENTER, DSBPAN_CENTER);
        }
        pSeArray->_p = 0; //���Z�b�g
    }
}

void GgafDx9Universe::draw() {
    GgafDx9ModelConnection* pModelCon = GgafDx9God::_pModelManager->getFirstConnection();
    while (pModelCon != NULL) {
        pModelCon->view()->_pTextureBlinker->behave();
        pModelCon = (GgafDx9ModelConnection*)(pModelCon->getNext());
    }


    //�i�K�����_�����O�s�v�i�Ő[�����A�w�i�A�őP�ʂ̕������j�̕`��B
    //��TODO:�{���͎�O����`��̂ق��������ǂ��B���A���̓��œK��
    _pActor_DrawActive = _pActors_DrawMaxDrawDepth;
    while (_pActor_DrawActive != NULL && _pActor_DrawActive->_is_active_flg && _pActor_DrawActive->_can_live_flg) {
        if (_pActor_DrawActive->_fAlpha < 1.0) {
            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //�������v�f����Ƃ������ƂŃJ�����O���ꎞOFF
            //�A���A�i�K�����_�����O�s�v�ł���ɂ�������炸�A�������\���́A�O�オ���܂��\������Ȃ��̂Ŕ�����ׂ��B
        }
        _pActor_DrawActive->processDraw();
        if (_pActor_DrawActive->_fAlpha < 1.0) {
            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  //�J�����O�L��ɖ߂�
        }
        _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
    }
    _pActors_DrawMaxDrawDepth = NULL; //����̂��߂Ƀ��Z�b�g

    //�i�K�����_�����O���K�v�ȃI�u�W�F�N�g��`��
    //float tmpAlpah;
    //int alphapoint = MAX_DRAW_DEPTH_LEVEL/4*3;
    for (int i = MAX_DRAW_DEPTH_LEVEL - 1; i >= 0; i--) {
        _pActor_DrawActive = _apAlphaActorList_DrawDepthLevel[i];
        while (_pActor_DrawActive != NULL && _pActor_DrawActive->_is_active_flg && _pActor_DrawActive->_can_live_flg) {
            if (_pActor_DrawActive->_fAlpha < 1.0) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //�������v�f����Ƃ������ƂŃJ�����O���ꎞOFF
            }
            //TODO:���͈Â�
//            if (alphapoint < i) {
//                tmpAlpah = _pActor_DrawActive->getAlpha();
//                _pActor_DrawActive->addAlpha((1.0/(MAX_DRAW_DEPTH_LEVEL - alphapoint))*i - 3.0);
//            }
            _pActor_DrawActive->processDraw();
//            if (alphapoint < i) {
//                _pActor_DrawActive->setAlpha(tmpAlpah);
//            }
            if (_pActor_DrawActive->_fAlpha < 1.0) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  //�J�����O�L��ɖ߂�
            }
            _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
        _apAlphaActorList_DrawDepthLevel[i] = NULL; //����̂��߂Ƀ��Z�b�g
    }

    //�Ō��EndPass
    HRESULT hr;
    if (GgafDx9EffectManager::_pEffect_Active != NULL) {
        TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDx9Universe::processDraw() EndPass() �Ɏ��s���܂����B");
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "GgafDx9Universe::processDraw() End() �Ɏ��s���܂����B");
        GgafDx9EffectManager::_pEffect_Active = NULL;
        GgafDx9ModelManager::_pModelLastDraw = NULL;
        GgafDx9DrawableActor::_hash_technique_last_draw = 0;
    }
}

//void GgafDx9Universe::setDrawDepthMaxLevel(GgafDx9DrawableActor* prm_pActor) {
//    static GgafDx9DrawableActor* pActorTmp;
//    if (_pActors_DrawMaxDrawDepth == NULL) {
//        //�ŏ��̃A�N�^�[�̏ꍇ
//        prm_pActor->_pNext_TheSameDrawDepthLevel = NULL;
//        _pActors_DrawMaxDrawDepth = prm_pActor;
//        return;
//    } else {
//        //���ɃA�N�^�[�o�^�ς݂������ꍇ
//        pActorTmp = _pActors_DrawMaxDrawDepth;
//        prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
//        _pActors_DrawMaxDrawDepth = prm_pActor;
//        return;
//    }
//}
int GgafDx9Universe::setDrawDepthLevel(int prm_draw_depth_level, GgafDx9DrawableActor* prm_pActor) {
    int draw_depth_level;
    static GgafDx9DrawableActor* pActorTmp;
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
        //�ł܂�Ȃ��悤�ɁA���K����ǉ�(�L���[)�A�����́A�O�ɐςݏグ(�X�^�b�N)���A�t���[������Č��݂ɍs���B
        //���̂Ȃ�΁A�e�N�X�`���ɔ����������݂���Z�o�b�t�@�L��̔������I�u�W�F�N�g�����������ꍇ�A
        //����[�x�Ȃ̂ŁA�`�揇�ɂ���Ă͓����Ȃ������������A�������ȕ\���ƂȂ�B������������ݕ\���Ŏ኱�̂��܂������s���B
        if ((GgafGod::_pGod->_pUniverse->_frame_of_behaving & 1) == 1) {
            //���K�ɒǉ�
            pActorTmp = _apAlphaActorList_DrawDepthLevel[draw_depth_level];
            prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
            _apAlphaActorList_DrawDepthLevel[draw_depth_level] = prm_pActor;
        } else {
            //�O�ɒǉ�
            pActorTmp = _apAlphaActorList_DrawDepthLevel[draw_depth_level];
            while(pActorTmp->_pNext_TheSameDrawDepthLevel != NULL) {
                pActorTmp = pActorTmp->_pNext_TheSameDrawDepthLevel;
            }
            pActorTmp->_pNext_TheSameDrawDepthLevel = prm_pActor;
            prm_pActor->_pNext_TheSameDrawDepthLevel = NULL;
        }
    }
    return draw_depth_level;

}


GgafDx9Universe::~GgafDx9Universe() {

    DELETE_IMPOSSIBLE_NULL(_pRing_pSeArray);
}
