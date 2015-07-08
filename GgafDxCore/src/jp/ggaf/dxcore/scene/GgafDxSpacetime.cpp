#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

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

#include "jp/ggaf/core/util/GgafUtil.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxFigureActor* GgafDxSpacetime::_pActor_draw_active = nullptr;
std::string GgafDxSpacetime::_seqkey_se_delay = "_SE_D_";

GgafDxSpacetime::SeArray::SeArray() {
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

void GgafDxSpacetime::SeArray::add(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency, GgafDxGeometricActor* prm_pActor) {
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
        _TRACE_("GgafDxSpacetime::SeArray::add() SE�����Ԃ�Ė�������܂����B"<<
                "������="<<prm_pActor->getName()<<"("<<prm_pActor<<") SE="<<prm_pSe->_wave_key<<"("<<prm_pSe->_wave_file_name<<")");
    }
#endif
}

void GgafDxSpacetime::SeArray::play(int index) {
    _apSe[index]->play(_volume[index], _pan[index], _rate_frequency[index]);
    _apSe[index]->_pActor_last_played = _apActor[index];
    _apActor[index] = nullptr;
    _apSe[index] = nullptr;
}

GgafDxSpacetime::GgafDxSpacetime(const char* prm_name, GgafDxCamera* prm_pCamera) : GgafSpacetime(prm_name),
_x_bound_left  (-DX_C(prm_pCamera->getZFar())), //�J�����̎ʂ��͈́�Spacetime�͈̔�
_x_bound_right (+DX_C(prm_pCamera->getZFar())),
_y_bound_bottom(-DX_C(prm_pCamera->getZFar())),
_y_bound_top   (+DX_C(prm_pCamera->getZFar())),
_z_bound_near  (-DX_C(prm_pCamera->getZFar())),
_z_bound_far   (+DX_C(prm_pCamera->getZFar()))
{
    _obj_class |= Obj_GgafDxSpacetime;
    _class_name = "GgafDxSpacetime";

    _TRACE_("Spacetime Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");

//TODO:�t�H�O����
//    _colFog.r = 0.0;
//    _colFog.g = 0.0;
//    _colFog.b = 0.0;
//    _colFog.a = 1.0;
    _papFirstActor_in_render_depth = NEW GgafDxFigureActor*[ALL_RENDER_DEPTH_LEVELS_NUM];
    _papLastActor_in_render_depth = NEW GgafDxFigureActor*[ALL_RENDER_DEPTH_LEVELS_NUM];
    for (int i = 0; i < ALL_RENDER_DEPTH_LEVELS_NUM; i++) {
        _papFirstActor_in_render_depth[i] = nullptr;
        _papLastActor_in_render_depth[i] = nullptr;
    }
    //��ɃJ������NEW���Ă����Ȃ��Ƃ����Ȃ��B
    _pCamera = prm_pCamera;
    GgafDxUtil::_pCam = prm_pCamera;

    bringDirector()->addSubGroup(_pCamera);

    _pRing_pSeArray = NEW GgafLinkedListRing<SeArray>();
    for (int i = 0; i < PROPERTY::MAX_SE_DELAY; i++) { //GGAF_END_DELAY�͍ő����x��t���[�������A����SE�̒x���̍ō��t���[�����Ƃ��Ă��g��
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }
    _pRing_pSeArray->indexedValue();

    GgafRepeatSeq::create(_seqkey_se_delay, 0, 8); //�Y��SE�Đ��t���[��



    //���ۂ̐[�x�ƁA�`��̒i�K�����_�����O�̐[�x�v�f�̊֌W
    //��ʂɋ߂��ꍇ�ׂ͍��i�K�����_�����O���邪
    //���ɂȂ�΂Ȃ�قǂ��񂾂�A�o�E�g�Ȓi�K�ɂ��Ă���

    // y = sin(x^(e/pi))
    // 0 <= x <= (pi^(pi/e)) / (2^(pi/e))
    //                               �� y=1�Őڂ���ӏ�
    _TRACE_("------------");
    const double e = 2.7182818284590452354;
    const double period = pow(PI, (PI/e)) / pow(2,(PI/e));

    _dep_resolution = prm_pCamera->getZFar() * PROPERTY::RENDER_DEPTH_STAGE_RATIO;  //�i�K�����_�l���͈�
    pixcoord px_dep_resolution = DX_PX(_dep_resolution);
    _paDep2Lv = NEW int[px_dep_resolution+1];

    for (int z = 0; z <= px_dep_resolution; z++) {
        double ang = RCNV(0, px_dep_resolution, z, 0, period);
        _paDep2Lv[z] = (int) ( sin( pow(ang, e/PI) ) * (REGULAR_RENDER_DEPTH_LEVELS_NUM-1) );
        _TRACE_(z <<"\t"<<_paDep2Lv[z]);
    }

}

void GgafDxSpacetime::registerSe(GgafDxSe* prm_pSe,
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

void GgafDxSpacetime::processSettlementBehavior() {
    GgafSpacetime::processSettlementBehavior();
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

void GgafDxSpacetime::draw() {
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
    for (int i = ALL_RENDER_DEPTH_LEVELS_NUM - 1; i >= 0; i--) { //������
        pDrawActor = _papFirstActor_in_render_depth[i];
        if (pDrawActor) {
            while (pDrawActor) {
                GgafDxSpacetime::_pActor_draw_active = pDrawActor;
#ifdef MY_DEBUG
                if (pDrawActor->getPlatformScene()->instanceOf(Obj_GgafDxScene)) {
                    //OK
                } else {
                    throwGgafCriticalException("GgafDxSpacetime::draw() err2. �`��A�N�^�[�̏����V�[�� _pActor_draw_active["<<(pDrawActor->getName())<<"->getPlatformScene()["<<(pDrawActor->getPlatformScene()->getName())<<"]���AGgafDxScene �ɕϊ��s�ł��Bthis="<<getName()<<" \n"<<
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

                pDrawActor = GgafDxSpacetime::_pActor_draw_active->_pNextActor_in_render_depth_level;
                //set�n�`��̏ꍇ�́ApDrawActor->processDraw() �������ŁA
                //GgafDxSpacetime::_pActor_draw_active ���Aset�n�̍ŏI�`��A�N�^�[�ɍX�V����Ă���B
                //_pNextActor_in_render_depth_level �ŕ\������΂���邱�Ƃ͂Ȃ��B
            }
            _papFirstActor_in_render_depth[i] = nullptr; //����̂��߂Ƀ��Z�b�g
            _papLastActor_in_render_depth[i] = nullptr;
        }
    }

    //�Ō��EndPass
    HRESULT hr;
    if (GgafDxEffectManager::_pEffect_active) {

        _TRACE4_("EndPass("<<GgafDxEffectManager::_pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<GgafDxEffectManager::_pEffect_active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_active<<")");
        hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxSpacetime::processDraw() EndPass() �Ɏ��s���܂����B");
        hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "GgafDxSpacetime::processDraw() End() �Ɏ��s���܂����B");
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
int GgafDxSpacetime::setDrawDepthLevel2D(GgafDxFigureActor* prm_pActor) {
    int render_depth_level;
    int specal_drawdepth = prm_pActor->_specal_drawdepth;
    if (specal_drawdepth < 0) {
        //������ 2D�œ��ʂȕ`��[�x�w�薳�� ������
        render_depth_level = EX_RENDER_DEPTH_LEVELS_FRONT_NUM + prm_pActor->_z; //_z�l���v���C�I���e�B���`��[�x�B
        //��������J�b�g
        if (render_depth_level > EX_RENDER_DEPTH_LEVELS_FRONT_NUM + REGULAR_RENDER_DEPTH_LEVELS_NUM - 1) {
            render_depth_level = EX_RENDER_DEPTH_LEVELS_FRONT_NUM + REGULAR_RENDER_DEPTH_LEVELS_NUM - 1;
        } else if (render_depth_level < EX_RENDER_DEPTH_LEVELS_FRONT_NUM) {
            render_depth_level = EX_RENDER_DEPTH_LEVELS_FRONT_NUM;
        }
        if (_papFirstActor_in_render_depth[render_depth_level] == nullptr) {
            //2D�ł���prm_render_depth_level�ōŏ��̃A�N�^�[�̏ꍇ
            prm_pActor->_pNextActor_in_render_depth_level = nullptr;
            _papFirstActor_in_render_depth[render_depth_level] = prm_pActor;
            _papLastActor_in_render_depth[render_depth_level] = prm_pActor;
        } else {
            //2D�œ���[�x��2D�̏ꍇ�A�A�����X�g�̂��K�ɒǉ����Ă���
            //�܂�A�Ō�� addSubLast() ����΂���قǁA�`�揇����ɂȂ�A�v���C�I���e�B���������Ȃ�B
            GgafDxFigureActor* pActorTmp = _papLastActor_in_render_depth[render_depth_level];
            pActorTmp->_pNextActor_in_render_depth_level = prm_pActor;
            prm_pActor->_pNextActor_in_render_depth_level = nullptr;
            _papLastActor_in_render_depth[render_depth_level] = prm_pActor;
        }
    } else {
        //������ 2D�œ��ʂȕ`��[�x�w��L�� ������
        render_depth_level = specal_drawdepth;
        if (_papFirstActor_in_render_depth[render_depth_level] == nullptr) {
            //����prm_render_depth_level�ōŏ��̃A�N�^�[�̏ꍇ
            prm_pActor->_pNextActor_in_render_depth_level = nullptr;
            _papFirstActor_in_render_depth[render_depth_level] = prm_pActor;
            _papLastActor_in_render_depth[render_depth_level] = prm_pActor;
        } else {
            //��O�ɒǉ�
            GgafDxFigureActor* pActorTmp = _papFirstActor_in_render_depth[render_depth_level];
            prm_pActor->_pNextActor_in_render_depth_level = pActorTmp;
            _papFirstActor_in_render_depth[render_depth_level] = prm_pActor;
        }
    }
    return render_depth_level;
}

int GgafDxSpacetime::setDrawDepthLevel3D(GgafDxFigureActor* prm_pActor) {
    int render_depth_level;
    int specal_drawdepth = prm_pActor->_specal_drawdepth;
    //�������RD�̏ꍇ
    if (prm_pActor->isOutOfView()) {
        //�`�悵�Ȃ��̂œo�^�Ȃ�
        render_depth_level = -1;
    } else {

        if (specal_drawdepth < 0) { //���ʂȕ`��[�x�w�薳��
            //������ 3D�œ��ʂȕ`��[�x�w�薳�� ������
            dxcoord dep = -prm_pActor->_dest_from_vppln_front; //�I�u�W�F�N�g�̎��_����̋���(DIRECTX����)
            if (dep < 0.0) {
                render_depth_level = EX_RENDER_DEPTH_LEVELS_FRONT_NUM;
            } else if (0.0 <= dep && dep < _dep_resolution) {
                render_depth_level = EX_RENDER_DEPTH_LEVELS_FRONT_NUM + _paDep2Lv[DX_PX(dep)];
            } else {
                render_depth_level = EX_RENDER_DEPTH_LEVELS_FRONT_NUM + REGULAR_RENDER_DEPTH_LEVELS_NUM - 1;
            }
            if (_papFirstActor_in_render_depth[render_depth_level] == nullptr) {
                //����prm_render_depth_level�ōŏ��̃A�N�^�[�̏ꍇ
                prm_pActor->_pNextActor_in_render_depth_level = nullptr;
                _papFirstActor_in_render_depth[render_depth_level] = prm_pActor;
                _papLastActor_in_render_depth[render_depth_level] = prm_pActor;
            } else {
                //����[�x��3D�̏ꍇ�A�O�ɒǉ��ƁA���K�ɒǉ������݂ɍs���B
                //���̂���Ȃ��Ƃ����邩�Ƃ����ƁAZ�o�b�t�@�L��̃e�N�X�`���ɓ���������I�u�W�F�N�g��A�������I�u�W�F�N�g�����������ꍇ�A
                //����[�x�Ȃ̂ŁA�v���C�I���e�B�i�`�揇�j�ɂ���ē����Ȃ������������Ă��܂��B
                //�����`�揇�𖈃t���[���ω������邱�ƂŁA���ݕ\���ł�������኱�̂��܂������s���B
                //TODO:(�ۑ�)�Q�A�R�̃I�u�W�F�N�g�̌����͏ꍇ�͌����ڂɂ����e�ł��邪�A��������ł܂�Ɩ{���Ƀ`���`������B
                if ((_frame_of_behaving & 1) == 1) { //�
                    //�O�ɒǉ�
                    GgafDxFigureActor* pActorTmp = _papFirstActor_in_render_depth[render_depth_level];
                    prm_pActor->_pNextActor_in_render_depth_level = pActorTmp;
                    _papFirstActor_in_render_depth[render_depth_level] = prm_pActor;
                } else {
                    //���K�ɒǉ�
                    GgafDxFigureActor* pActorTmp = _papLastActor_in_render_depth[render_depth_level];
                    pActorTmp->_pNextActor_in_render_depth_level = prm_pActor;
                    prm_pActor->_pNextActor_in_render_depth_level = nullptr;
                    _papLastActor_in_render_depth[render_depth_level] = prm_pActor;
                }
            }

        } else {
            //������ 3D�œ��ʂȕ`��[�x�w��L��
            render_depth_level = specal_drawdepth;
            if (_papFirstActor_in_render_depth[render_depth_level] == nullptr) {
                //����prm_render_depth_level�ōŏ��̃A�N�^�[�̏ꍇ
                prm_pActor->_pNextActor_in_render_depth_level = nullptr;
                _papFirstActor_in_render_depth[render_depth_level] = prm_pActor;
                _papLastActor_in_render_depth[render_depth_level] = prm_pActor;
            } else {
                //�O�ɒǉ�
                GgafDxFigureActor* pActorTmp = _papFirstActor_in_render_depth[render_depth_level];
                prm_pActor->_pNextActor_in_render_depth_level = pActorTmp;
                _papFirstActor_in_render_depth[render_depth_level] = prm_pActor;
            }
        }
    }
    return render_depth_level;
}


GgafDxSpacetime::~GgafDxSpacetime() {
    GGAF_DELETE(_pRing_pSeArray);
    GGAF_DELETEARR(_paDep2Lv);

    GGAF_DELETEARR(_papFirstActor_in_render_depth);
    GGAF_DELETEARR(_papLastActor_in_render_depth);


}
