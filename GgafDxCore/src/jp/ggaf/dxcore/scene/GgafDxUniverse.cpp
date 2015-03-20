#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/util/GgafRepeatSeq.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/dxcore/scene/GgafDxScene.h"
#include "jp/ggaf/dxcore/sound/GgafDxSe.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxFigureActor* GgafDxUniverse::_apFirstActor_draw_depth_level[MAX_DRAW_DEPTH_LEVEL+1];
GgafDxFigureActor* GgafDxUniverse::_apLastActor_draw_depth_level[MAX_DRAW_DEPTH_LEVEL+1];
//GgafDxFigureActor* GgafDxUniverse::_pActors_DrawMaxDrawDepth = nullptr;
GgafDxFigureActor* GgafDxUniverse::_pActor_draw_active = nullptr;
std::string GgafDxUniverse::_seqkey_se_delay = "_SE_D_";

coord GgafDxUniverse::_x_gone_left   = 0;
coord GgafDxUniverse::_x_gone_right  = 0;
coord GgafDxUniverse::_y_gone_top    = 0;
coord GgafDxUniverse::_y_gone_bottom = 0;
coord GgafDxUniverse::_z_gone_far   = 0;
coord GgafDxUniverse::_z_gone_near  = 0;


GgafDxUniverse::SeArray::SeArray() {
#ifdef MY_DEBUG
    if (PROPERTY::MAX_SE_AT_ONCE > 64) {
        throwGgafCriticalException("�v���p�e�B�l MAX_SE_AT_ONCE ���A���(64)�𒴂��Ă��܂��B�v���p�e�B�t�@�C�����m�F���Ă��������BPROPERTY::MAX_SE_AT_ONCE="<<PROPERTY::MAX_SE_AT_ONCE);
    }
#endif
    _p = 0;
    for (int i = 0; i < PROPERTY::MAX_SE_AT_ONCE; i++) {
        _apSe[i] = nullptr;
        _apActor[i] = nullptr;
    }
}

void GgafDxUniverse::SeArray::add(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency, GgafDxGeometricActor* prm_pActor) {
    if (_p < PROPERTY::MAX_SE_AT_ONCE) {
        _apSe[_p] = prm_pSe;
        _rate_frequency[_p] = prm_rate_frequency;
        _volume[_p] = prm_volume;
        _pan[_p] = prm_pan;
        _apActor[_p] = prm_pActor;
        _p++;
    }
#ifdef MY_DEBUG
    else {
        _TRACE_("GgafDxUniverse::SeArray::add() SE�����Ԃ�Ė�������܂����B"<<
                "������="<<prm_pActor->getName()<<"("<<prm_pActor<<") SE="<<prm_pSe->_wave_key<<"("<<prm_pSe->_wave_file_name<<")");
    }
#endif
}

void GgafDxUniverse::SeArray::play(int index) {
    _apSe[index]->play(_volume[index], _pan[index], _rate_frequency[index]);
    _apSe[index]->_pActor_last_played = _apActor[index];
    _apActor[index] = nullptr;
    _apSe[index] = nullptr;
}

GgafDxUniverse::GgafDxUniverse(const char* prm_name, GgafDxCamera* prm_pCamera) : GgafUniverse(prm_name) {
    _obj_class |= Obj_GgafDxUniverse;
    _class_name = "GgafDxUniverse";
//TODO:�t�H�O����
//    _colFog.r = 0.0;
//    _colFog.g = 0.0;
//    _colFog.b = 0.0;
//    _colFog.a = 1.0;

    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL+1; i++) {
        _apFirstActor_draw_depth_level[i] = nullptr;
        _apLastActor_draw_depth_level[i] = nullptr;
    }
    //��ɃJ������NEW���Ă����Ȃ��Ƃ����Ȃ��B
    _pCamera = prm_pCamera;
    GgafDxUtil::_pCam = prm_pCamera;

    bringDirector()->addSubGroup(_pCamera);
    _pActor_draw_active = nullptr;

    //�J�����̎ʂ��͈́B
    coord F = DX_C(_pCamera->getZFar());
    _x_gone_right  = +F;
    _x_gone_left   = -F;
    _y_gone_top    = +F;
    _y_gone_bottom = -F;
    _z_gone_far    = +F;
    _z_gone_near   = -F;
    _TRACE_("Gone=X ("<<_x_gone_left<<" ~ "<<_x_gone_right<<") Y("<<_y_gone_bottom<<" ~ "<<_y_gone_top<<") Z("<<_z_gone_near<<" ~ "<<_z_gone_far<<")");

    _pRing_pSeArray = NEW GgafLinkedListRing<SeArray>();
    for (int i = 0; i < PROPERTY::MAX_SE_DELAY; i++) { //GGAF_END_DELAY�͍ő����x��t���[�������A����SE�̒x���̍ō��t���[�����Ƃ��Ă��g��
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }
    _pRing_pSeArray->indexedValue();

    GgafRepeatSeq::create(_seqkey_se_delay, 0, 8); //�Y��SE�Đ��t���[��
}

void GgafDxUniverse::registerSe(GgafDxSe* prm_pSe,
                                int prm_volume,
                                float prm_pan,
                                float prm_rate_frequency,
                                int prm_delay,
                                GgafDxGeometricActor* prm_pActor) {
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
    //TODO:���߂Ă����̂ɃC���x�[�_�[�G�N�X�g���[���ɐ��������Ă��܂���(�Ǝv���Ă�)�I�I�{���V�v�f���~�����B�I�I

    //SE�̖�^�C�~���O�� 0�`8�t���[�������炵�ăo��������
    int delay = prm_delay+1+(GgafRepeatSeq::nextVal(_seqkey_se_delay));
    if (delay > PROPERTY::MAX_SE_DELAY-1) {
        delay = PROPERTY::MAX_SE_DELAY-1;
    }
    _pRing_pSeArray->getNext(delay)->add(prm_pSe, prm_volume, prm_pan, prm_rate_frequency, prm_pActor);
}

void GgafDxUniverse::processSettlementBehavior() {
    GgafUniverse::processSettlementBehavior();
    //SE��炷
    SeArray* pSeArray = _pRing_pSeArray->next(); //��i�߂�SE�z��擾
    if (pSeArray->_p > 0) {
        int se_p = pSeArray->_p;
        for (int p = 0; p < se_p; p++) {
            pSeArray->play(p);
        }
        pSeArray->_p = 0; //���Z�b�g
    }
    GgafRepeatSeq::setMin(_seqkey_se_delay); //����nextVal��0��Ԃ���
}

void GgafDxUniverse::draw() {
    GgafDxModelConnection* pModelCon = GgafDxGod::_pModelManager->getFirstConnection();
    while (pModelCon) {
        pModelCon->peek()->_pTexBlinker->behave();
        pModelCon = (GgafDxModelConnection*)(pModelCon->getNext());
    }

    //������EffectManager�ŉ񂵂�Vew�ϊ������������ݒ肷��悤�ɂ���
    GgafDxGod::_pEffectManager->setParamPerFrameAll();

    //�i�K�����_�����O�`��
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    GgafDxFigureActor* pDrawActor;
    for (int i = MAX_DRAW_DEPTH_LEVEL; i >= 0; i--) {
        pDrawActor = GgafDxUniverse::_apFirstActor_draw_depth_level[i];
        if (pDrawActor) {
            while (pDrawActor) {
                GgafDxUniverse::_pActor_draw_active = pDrawActor;
#ifdef MY_DEBUG
                if (pDrawActor->getPlatformScene()->instanceOf(Obj_GgafDxScene)) {
                    //OK
                } else {
                    throwGgafCriticalException("GgafDxUniverse::draw() err2. �`��A�N�^�[�̏����V�[�� _pActor_draw_active["<<(pDrawActor->getName())<<"->getPlatformScene()["<<(pDrawActor->getPlatformScene()->getName())<<"]���AGgafDxScene �ɕϊ��s�ł��Bthis="<<getName()<<" \n"<<
                            "pDrawActor->getPlatformScene()->_obj_class="<<pDrawActor->getPlatformScene()->_obj_class<< " Obj_GgafDxScene="<<Obj_GgafDxScene<<" \n"<<
                            "(pDrawActor->getPlatformScene()->_obj_class & Obj_GgafDxScene)="<<((pDrawActor->getPlatformScene()->_obj_class) & Obj_GgafDxScene) <<" ==?? Obj_GgafDxScene("<<Obj_GgafDxScene<<")");
                }
#endif
                //�e�����V�[���̃��J�[�e����ݒ肷��B
                pDrawActor->getEffect()->setAlphaMaster(
                                            ((GgafDxScene*)pDrawActor->getPlatformScene())->_master_alpha
                                         );


                //�������v�f����̏ꍇ�J�����O���ꎞOFF
                if (pDrawActor->_alpha < 1.0f) {
                    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
                }
                //Z�o�b�t�@���l�������ݒ�
                if (!pDrawActor->_zenable) {
                    pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
                }
                // Z�o�b�t�@�������ݕs�ݒ�
                if (!pDrawActor->_zwriteenable) {
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
                }

                pDrawActor->processDraw(); //�����ŕ`��B
                //set�̕`�擙�ŁAGgafDxUniverse::_pActor_draw_active ���X�V�����

                //�J�����O�L��ɖ߂�
                if (pDrawActor->_alpha < 1.0f) {
                    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
                }
                //Z�o�b�t�@���l�������ݒ�
                if (!pDrawActor->_zenable) {
                    pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
                }
                // Z�o�b�t�@�������ݕs�ݒ�
                if (!pDrawActor->_zwriteenable) {
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                }

                pDrawActor = GgafDxUniverse::_pActor_draw_active->_pNextActor_in_draw_depth_level;
            }
            GgafDxUniverse::_apFirstActor_draw_depth_level[i] = nullptr; //����̂��߂Ƀ��Z�b�g
            GgafDxUniverse::_apLastActor_draw_depth_level[i] = nullptr;
        }
    }

    //�Ō��EndPass
    HRESULT hr;
    if (GgafDxEffectManager::_pEffect_active) {

        _TRACE4_("EndPass("<<GgafDxEffectManager::_pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<GgafDxEffectManager::_pEffect_active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_active<<")");
        hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxUniverse::processDraw() EndPass() �Ɏ��s���܂����B");
        hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "GgafDxUniverse::processDraw() End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
        if (GgafDxEffectManager::_pEffect_active->_begin == false) {
            throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            GgafDxEffectManager::_pEffect_active->_begin = false;
        }
#endif
        GgafDxEffectManager::_pEffect_active = nullptr;
        GgafDxModelManager::_pModelLastDraw = nullptr;
        GgafDxFigureActor::_hash_technique_last_draw = 0;
    }

}

int GgafDxUniverse::setDrawDepthLevel(int prm_draw_depth_level, GgafDxFigureActor* prm_pActor) {
    int draw_depth_level;
    //��������J�b�g
    if (prm_draw_depth_level > MAX_DRAW_DEPTH_LEVEL - 4) {
        draw_depth_level = MAX_DRAW_DEPTH_LEVEL - 4;
    } else if (prm_draw_depth_level < 1) {
        draw_depth_level = 1;
    } else {
        draw_depth_level = prm_draw_depth_level;
    }

    if (GgafDxUniverse::_apFirstActor_draw_depth_level[draw_depth_level] == nullptr) {
        //����prm_draw_depth_level�ōŏ��̃A�N�^�[�̏ꍇ
        prm_pActor->_pNextActor_in_draw_depth_level = nullptr;
        GgafDxUniverse::_apFirstActor_draw_depth_level[draw_depth_level] = prm_pActor;
        GgafDxUniverse::_apLastActor_draw_depth_level[draw_depth_level] = prm_pActor;
    } else {
        if (prm_pActor->_is_2D) {
            //����[�x��2D�̏ꍇ�A�A�����X�g�̂��K�ɒǉ����Ă���
            //�܂�A�Ō�� addSubLast() ����΂���قǁA�`�揇����ɂȂ�A�v���C�I���e�B�������B
            GgafDxFigureActor* pActorTmp = GgafDxUniverse::_apLastActor_draw_depth_level[draw_depth_level];
            pActorTmp->_pNextActor_in_draw_depth_level = prm_pActor;
            prm_pActor->_pNextActor_in_draw_depth_level = nullptr;
            GgafDxUniverse::_apLastActor_draw_depth_level[draw_depth_level] = prm_pActor;
        } else {
            //����[�x��3D�̏ꍇ�A�O�ɒǉ��ƁA���K�ɒǉ������݂ɍs���B
            //���̂���Ȃ��Ƃ����邩�Ƃ����ƁAZ�o�b�t�@�L��̃e�N�X�`���ɓ���������I�u�W�F�N�g��A�������I�u�W�F�N�g�����������ꍇ�A
            //����[�x�Ȃ̂ŁA�v���C�I���e�B�i�`�揇�j�ɂ���ē����Ȃ������������Ă��܂��B
            //�����`�揇�𖈃t���[���ω������邱�ƂŁA���ݕ\���ł�������኱�̂��܂������s���B
            //TODO:(�ۑ�)�Q�A�R�̃I�u�W�F�N�g�̌����͏ꍇ�͌����ڂɂ����e�ł��邪�A��������ł܂�Ɩ{���Ƀ`���`������B
            if ((GgafGod::_pGod->_pUniverse->_frame_of_behaving & 1) == 1) { //�
                //�O�ɒǉ�
                GgafDxFigureActor* pActorTmp = GgafDxUniverse::_apFirstActor_draw_depth_level[draw_depth_level];
                prm_pActor->_pNextActor_in_draw_depth_level = pActorTmp;
                GgafDxUniverse::_apFirstActor_draw_depth_level[draw_depth_level] = prm_pActor;
            } else {
                //���K�ɒǉ�
                GgafDxFigureActor* pActorTmp = GgafDxUniverse::_apLastActor_draw_depth_level[draw_depth_level];
                pActorTmp->_pNextActor_in_draw_depth_level = prm_pActor;
                prm_pActor->_pNextActor_in_draw_depth_level = nullptr;
                GgafDxUniverse::_apLastActor_draw_depth_level[draw_depth_level] = prm_pActor;
            }
        }
    }
    return draw_depth_level;
}


GgafDxUniverse::~GgafDxUniverse() {
    GGAF_DELETE(_pRing_pSeArray);
}
