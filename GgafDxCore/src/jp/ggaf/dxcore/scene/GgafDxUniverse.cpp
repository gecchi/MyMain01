#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxDrawableActor* GgafDxUniverse::_apAlphaActorFirstList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL+1];
GgafDxDrawableActor* GgafDxUniverse::_apAlphaActorLastList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL+1];
//GgafDxDrawableActor* GgafDxUniverse::_pActors_DrawMaxDrawDepth = nullptr;
GgafDxDrawableActor* GgafDxUniverse::_pActor_DrawActive = nullptr;
std::string GgafDxUniverse::_seqkey_se_delay = "_SE_D_";

coord GgafDxUniverse::_X_goneLeft   = 0;
coord GgafDxUniverse::_X_goneRight  = 0;
coord GgafDxUniverse::_Y_goneTop    = 0;
coord GgafDxUniverse::_Y_goneBottom = 0;
coord GgafDxUniverse::_Z_goneFar   = 0;
coord GgafDxUniverse::_Z_goneNear  = 0;


GgafDxUniverse::SeArray::SeArray() {
    _p = 0;
    for (int i = 0; i < MAX_SE_AT_ONCE; i++) {
        _apSe[i] = nullptr;
    }
}

void GgafDxUniverse::SeArray::add(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency) {
    if (_p < MAX_SE_AT_ONCE) {
        _apSe[_p] = prm_pSe;
        _rate_frequency[_p] = prm_rate_frequency;
        _volume[_p] = prm_volume;
        _pan[_p] = prm_pan;
        _p++;
    }
}

void GgafDxUniverse::SeArray::play(int index) {
    _apSe[index]->play(_volume[index], _pan[index], _rate_frequency[index]);
    _apSe[index] = nullptr;
}

GgafDxUniverse::GgafDxUniverse(const char* prm_name, GgafDxCamera* prm_pCamera) : GgafUniverse(prm_name) {
    _obj_class |= Obj_GgafDxUniverse;
    _class_name = "GgafDxUniverse";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL+1; i++) {
        _apAlphaActorFirstList_DrawDepthLevel[i] = nullptr;
        _apAlphaActorLastList_DrawDepthLevel[i] = nullptr;
    }
    //��ɃJ������NEW���Ă����Ȃ��Ƃ����Ȃ��B
    _pCamera = prm_pCamera;


    getDirector()->addSubGroup(_pCamera);
    _pActor_DrawActive = nullptr;

    //�J�����̎ʂ��͈́B
    coord F = DX_C(_pCamera->_zf);
    _X_goneRight  = +F;
    _X_goneLeft   = -F;
    _Y_goneTop    = +F;
    _Y_goneBottom = -F;
    _Z_goneFar    = +F;
    _Z_goneNear   = -F;
    _TRACE_("Gone=X ("<<_X_goneLeft<<" ~ "<<_X_goneRight<<") Y("<<_Y_goneBottom<<" ~ "<<_Y_goneTop<<") Z("<<_Z_goneFar<<" ~ "<<_Z_goneNear<<")");

    _pRing_pSeArray = NEW GgafLinkedListRing<SeArray>();
    for (int i = 0; i < MAX_SE_DELAY; i++) { //GGAF_SAYONARA_DELAY�͍ő����x��t���[�������A����SE�̒x���̍ō��t���[�����Ƃ��Ă��g��
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }
    GgafRepeatSeq::create(_seqkey_se_delay, 0, 8); //�Y��SE�Đ��t���[��
}

void GgafDxUniverse::registSe(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency, int prm_delay ) {
//    int bpm = GgafDxBgmPerformer::_active_bgm_bpm;
    //�Y���t���[�����v�Z
    //1���Ԃ�60*60=3600�t���[��
    //4�������^�C�~���O�� 3600/_bpm
    //8�������^�C�~���O�� 3600/(_bpm*2) = 1800/_bpm
    //16�������^�C�~���O�� 3600/(_bpm*4) = 900/_bpm
    //0�t���[������BGM�������Ƃ��āA���݂̃t���[����f�Ƃ���ƁA���ߖ�����16�������^�C�~���O��
    //F = f%(900/_bpm)
    //F = 0�̏ꍇ�A�������� f
    //F != 0 �̏ꍇ {f/(900/_bpm)�̏� * (900/_bpm)} + (900/_bpm) �����ߖ�����16�������^�C�~���O
    //TODO:���߂Ă����̂ɃC���x�[�_�[�G�N�X�g���[���ɐ��������Ă��܂����I�I�{���V�v�f���~�����B�I�I




    //SE�̖�^�C�~���O�� 0�`8�t���[�������炵�ăo��������

    _pRing_pSeArray->getNext(prm_delay+1+(GgafRepeatSeq::nextVal(_seqkey_se_delay)))->add(prm_pSe, prm_volume, prm_pan, prm_rate_frequency);
    //_pRing_pSeArray->getNext(prm_delay+1)->add(prm_pSe, prm_volume, prm_pan, prm_rate_frequency);
}

void GgafDxUniverse::processSettlementBehavior() {

    GgafUniverse::processSettlementBehavior();
    //SE��炷
    SeArray* pSeArray = _pRing_pSeArray->next(); //��i�߂�SE�z��擾
    if (pSeArray->_p > 0) {
        for (int p = 0; p < pSeArray->_p; p++) {
            pSeArray->play(p);
        }
        pSeArray->_p = 0; //���Z�b�g
    }

    GgafRepeatSeq::setMax(_seqkey_se_delay); //����nextVal��0��Ԃ���
}

void GgafDxUniverse::draw() {
    GgafDxModelConnection* pModelCon = GgafDxGod::_pModelManager->getFirstConnection();
    while (pModelCon) {
        pModelCon->fetch()->_pTextureBlinker->behave();
        pModelCon = (GgafDxModelConnection*)(pModelCon->getNext());
    }

    //������EffectManager�ŉ񂵂�Vew�ϊ������������ݒ肷��悤�ɂ���
    GgafDxGod::_pEffectManager->setParamPerFrameAll();

    //�i�K�����_�����O�`��
    GgafDxScene* pScene;
    for (int i = MAX_DRAW_DEPTH_LEVEL; i >= 0; i--) {
        _pActor_DrawActive = _apAlphaActorFirstList_DrawDepthLevel[i];
        while (_pActor_DrawActive) {
#ifdef MY_DEBUG
            if (_pActor_DrawActive->getPlatformScene()->instanceOf(Obj_GgafDxScene)) {
                //OK
            } else {
                throwGgafCriticalException("GgafDxUniverse::draw() err2. _pActor_DrawActive["<<(_pActor_DrawActive->getName())<<"->getPlatformScene()["<<(_pActor_DrawActive->getPlatformScene()->getName())<<"]���AGgafDxScene �ɕϊ��s�ł��Bthis="<<getName());
            }
#endif
            //�e�����V�[���̃��J�[�e����ݒ肷��B
            pScene = (GgafDxScene*)_pActor_DrawActive->getPlatformScene();
            _pActor_DrawActive->_pEffect->_pID3DXEffect->SetFloat(
                    _pActor_DrawActive->_pEffect->_h_alpha_master, pScene->_master_alpha);

            //�������v�f����̏ꍇ�J�����O���ꎞOFF
            if (_pActor_DrawActive->_alpha < 1.0f) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
            }
            //Z�o�b�t�@���l�������ݒ�
            if (!_pActor_DrawActive->_zenable) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
            }
            // Z�o�b�t�@�������ݕs�ݒ�
            if (!_pActor_DrawActive->_zwriteenable) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
            }

            _pActor_DrawActive->processDraw(); //�`��I�I�I

            //�J�����O�L��ɖ߂�
            if (_pActor_DrawActive->_alpha < 1.0f) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
            }
            //Z�o�b�t�@���l�������ݒ�
            if (!_pActor_DrawActive->_zenable) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
            }
            // Z�o�b�t�@�������ݕs�ݒ�
            if (!_pActor_DrawActive->_zwriteenable) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
            }

            _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
        _apAlphaActorFirstList_DrawDepthLevel[i] = nullptr; //����̂��߂Ƀ��Z�b�g
        _apAlphaActorLastList_DrawDepthLevel[i] = nullptr;
    }

    //�Ō��EndPass
    HRESULT hr;
    if (GgafDxEffectManager::_pEffect_Active) {

        TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
        hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxUniverse::processDraw() EndPass() �Ɏ��s���܂����B");
        hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "GgafDxUniverse::processDraw() End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
        if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
            throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            GgafDxEffectManager::_pEffect_Active->_begin = false;
        }
#endif
        GgafDxEffectManager::_pEffect_Active = nullptr;
        GgafDxModelManager::_pModelLastDraw = nullptr;
        GgafDxDrawableActor::_hash_technique_last_draw = 0;
    }

}

int GgafDxUniverse::setDrawDepthLevel(int prm_draw_depth_level, GgafDxDrawableActor* prm_pActor) {
    int draw_depth_level;
    GgafDxDrawableActor* pActorTmp;
    //��������J�b�g
    if (prm_draw_depth_level > MAX_DRAW_DEPTH_LEVEL - 4) {
        draw_depth_level = MAX_DRAW_DEPTH_LEVEL - 4;
    } else if (prm_draw_depth_level < 1) {
        draw_depth_level = 1;
    } else {
        draw_depth_level = prm_draw_depth_level;
    }

    if (_apAlphaActorFirstList_DrawDepthLevel[draw_depth_level] == nullptr) {
        //����prm_draw_depth_level�ōŏ��̃A�N�^�[�̏ꍇ
        prm_pActor->_pNext_TheSameDrawDepthLevel = nullptr;
        _apAlphaActorFirstList_DrawDepthLevel[draw_depth_level] = prm_pActor;
        _apAlphaActorLastList_DrawDepthLevel[draw_depth_level] = prm_pActor;
    } else {
        if (prm_pActor->_is2DActor) {
            //�O�ɒǉ�
            pActorTmp = _apAlphaActorFirstList_DrawDepthLevel[draw_depth_level];
            prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
            _apAlphaActorFirstList_DrawDepthLevel[draw_depth_level] = prm_pActor;
        } else {
            //����prm_draw_depth_level�Ŋ��ɃA�N�^�[�o�^�ς݂������ꍇ
            //�\�������Œ�ɂȂ�Ȃ��悤�ɁA���K����ǉ�(�L���[)�A�����́A�O�ɐςݏグ(�X�^�b�N)���A�t���[������Č��݂ɍs���B
            //���̂���Ȃ��Ƃ����邩�Ƃ����ƁAZ�o�b�t�@�L��̃e�N�X�`���ɓ���������I�u�W�F�N�g��A�������I�u�W�F�N�g�����������ꍇ�A
            //����[�x�Ȃ̂ŁA�v���C�I���e�B�i�`�揇�j�ɂ���ē����Ȃ������������Ă��܂��B
            //�����`�揇�𖈃t���[���ω������邱�ƂŁA���ݕ\���ł�������኱�̂��܂������s���B
            //TODO:(�ۑ�)�Q�A�R�̃I�u�W�F�N�g�̌����͏ꍇ�͌����ڂɂ����e�ł��邪�A��������ł܂�Ɩ{���Ƀ`���`������B

            if ((GgafGod::_pGod->_pUniverse->_frame_of_behaving & 1) == 1) {
                //�O�ɒǉ�
                pActorTmp = _apAlphaActorFirstList_DrawDepthLevel[draw_depth_level];
                prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
                _apAlphaActorFirstList_DrawDepthLevel[draw_depth_level] = prm_pActor;
            } else {
                //���K�ɒǉ�
                pActorTmp = _apAlphaActorLastList_DrawDepthLevel[draw_depth_level];
                pActorTmp->_pNext_TheSameDrawDepthLevel = prm_pActor;
                prm_pActor->_pNext_TheSameDrawDepthLevel = nullptr;
                _apAlphaActorLastList_DrawDepthLevel[draw_depth_level] = prm_pActor;
            }
        }
    }
    return draw_depth_level;

}


GgafDxUniverse::~GgafDxUniverse() {
    DELETE_IMPOSSIBLE_NULL(_pRing_pSeArray);
}
