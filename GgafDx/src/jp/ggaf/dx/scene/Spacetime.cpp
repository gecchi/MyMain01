#include "jp/ggaf/dx/scene/Spacetime.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/util/LinkedListRing.hpp"
#include "jp/ggaf/core/util/RepeatSeq.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelConnection.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/dx/scene/Scene.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/dx/sound/Se.h"
#include "jp/ggaf/dx/util/Util.h"

#include "jp/ggaf/dx/model/MassModel.h"

using namespace GgafDx;

FigureActor* Spacetime::_pActor_draw_active = nullptr;
int Spacetime::render_depth_index_active = 0;
std::string Spacetime::_seqkey_se_delay = "_SE_D_";

Spacetime::SeArray::SeArray() {
#ifdef MY_DEBUG
    if (CONFIG::MAX_SE_AT_ONCE > 64) {
        throwCriticalException("�v���p�e�B�l MAX_SE_AT_ONCE ���A���(64)�𒴂��Ă��܂��B�v���p�e�B�t�@�C�����m�F���Ă��������BCONFIG::MAX_SE_AT_ONCE="<<CONFIG::MAX_SE_AT_ONCE);
    }
#endif
    _p = 0;
    for (int i = 0; i < CONFIG::MAX_SE_AT_ONCE; i++) {
        _apSe[i] = nullptr;
        _apActor[i] = nullptr;
    }
}

void Spacetime::SeArray::add(Se* prm_pSe, int prm_volume, float prm_pan, float prm_frequency_rate, bool prm_can_looping, GeometricActor* prm_pActor) {
    if (_p < CONFIG::MAX_SE_AT_ONCE) {
        _apSe[_p] = prm_pSe;
        _frequency_rate[_p] = prm_frequency_rate;
        _volume[_p] = prm_volume;
        _pan[_p] = prm_pan;
        _can_looping[_p] = prm_can_looping;
        _apActor[_p] = prm_pActor;
        _p++;
    }
#ifdef MY_DEBUG
    else {
        _TRACE_("SE�����Ԃ�Ė�������܂����B"
                "������="<<prm_pActor->getName()<<"("<<prm_pActor<<") SE="<<prm_pSe->_wave_key<<"("<<prm_pSe->_wave_file_name<<")");
    }
#endif
}

void Spacetime::SeArray::play(int index) {
    _apSe[index]->setVolume(_volume[index] );
    _apSe[index]->setPan(_pan[index]);
    _apSe[index]->setFrequencyRate(_frequency_rate[index]);
    _apSe[index]->play(_can_looping[index]);
    _apSe[index]->_pActor_last_played = _apActor[index];
    _apActor[index] = nullptr;
    _apSe[index] = nullptr;
}

Spacetime::Spacetime(const char* prm_name, Camera* prm_pCamera) : GgafCore::Spacetime(prm_name),
_x_bound_left  (-DX_C(prm_pCamera->getZFar())), //�J�����̎ʂ��͈́�Spacetime�͈̔�
_x_bound_right (+DX_C(prm_pCamera->getZFar())),
_y_bound_bottom(-DX_C(prm_pCamera->getZFar())),
_y_bound_top   (+DX_C(prm_pCamera->getZFar())),
_z_bound_near  (-DX_C(prm_pCamera->getZFar())),
_z_bound_far   (+DX_C(prm_pCamera->getZFar()))
{
    _obj_class |= Obj_GgafDx_Spacetime;
    _class_name = "Spacetime";

    _TRACE_("Spacetime Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");

//TODO:�t�H�O����
//    _colFog.r = 0.0;
//    _colFog.g = 0.0;
//    _colFog.b = 0.0;
//    _colFog.a = 1.0;
    _papFirstActor_in_render_depth = NEW FigureActor*[ALL_RENDER_DEPTH_INDEXS_NUM];
    _papLastActor_in_render_depth = NEW FigureActor*[ALL_RENDER_DEPTH_INDEXS_NUM];
    for (int i = 0; i < ALL_RENDER_DEPTH_INDEXS_NUM; i++) {
        _papFirstActor_in_render_depth[i] = nullptr;
        _papLastActor_in_render_depth[i] = nullptr;
    }
    //��ɃJ������NEW���Ă����Ȃ��Ƃ����Ȃ��B
    _pCamera = prm_pCamera;
    Util::_pCam = prm_pCamera;

    bringSceneMediator()->appendGroupChild(_pCamera);

    _pRing_pSeArray = NEW GgafCore::LinkedListRing<SeArray>();
    for (int i = 0; i < CONFIG::SE_DELAY_MAX_DEPTH; i++) { //GGAF_END_DELAY�͍ő����x��t���[�������A����SE�̒x���̍ō��t���[�����Ƃ��Ă��g��
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }
    _pRing_pSeArray->createIndex();

    GgafCore::RepeatSeq::create(_seqkey_se_delay, 0, 8); //�Y��SE�Đ��t���[��

    //���ۂ̐[�x�ƁA�`��̒i�K�����_�����O�̐[�x�v�f�̊֌W
    //��ʂɋ߂��ꍇ�ׂ͍��i�K�����_�����O���邪
    //���ɂȂ�΂Ȃ�قǂ��񂾂�A�o�E�g�Ȓi�K�ɂ��Ă���

    // y = sin(x^(e/pi))
    // 0 <= x <= (pi^(pi/e)) / (2^(pi/e))
    //                               �� y=1�Őڂ���ӏ�
    static const double e = 2.7182818284590452354;
    static const double period = pow(PI, (PI/e)) / pow(2,(PI/e));

    _dep_resolution = prm_pCamera->getZFar() * CONFIG::RENDER_DEPTH_STAGE_RATIO;  //�i�K�����_�l���͈�
    pixcoord px_dep_resolution = DX_PX(_dep_resolution);
    _paDep2Lv = NEW int[px_dep_resolution+1];

    _paDep2Lv[0] = 0;
    for (int z = 1; z <= px_dep_resolution; z++) {
        double ang = RCNV(0, px_dep_resolution, z, 0, period);
        _paDep2Lv[z] = (int) ( sin( pow(ang, e/PI) ) * (REGULAR_RENDER_DEPTH_INDEXS_NUM-1) );
    }
    //�n�}�������ƃ���
    //pow(x,y)��
    //double ang = RCNV(0, px_dep_resolution, z, 0, period); �� z = 0 �̏ꍇ ang = -0; �ɂȂ�
    //GCC�̏ꍇ�͒ꂪ���Ɖ��߂����̂��A pow(ang, e/PI) = -1.#IND �ƂȂ��Ă��܂��������ɂ�肠��B
    //VC�� 0 �ɂȂ����B
    //pow���g���Ƃ��͋C�����悤�B

    _TRACE_("�ʏ�̒i�K�����_�����O�[�x���F"<<REGULAR_RENDER_DEPTH_INDEXS_NUM);
    _TRACE_("�ʏ�̒i�K�����_�����O�����͈́F"<<DX_C(prm_pCamera->getZFar())<<" * "<<CONFIG::RENDER_DEPTH_STAGE_RATIO <<
                                             " = "<< DX_C(_dep_resolution)   );
    _TRACE_("�J��������̋���  0 ~ "<<DX_C(_dep_resolution)<< " ��Actor�́A �[�x���l������ĉ����̃I�u�W�F�N�g���珇�Ƀ����_�����O���s���܂��B");
    _TRACE_(DX_C(_dep_resolution)<<" ��艓���I�u�W�F�N�g�͑S�ē���[�x�Ƃ��čŏ��Ƀ����_�����O����܂��B");
}

void Spacetime::registerSe(Se* prm_pSe,
                           int prm_volume,
                           float prm_pan,
                           float prm_frequency_rate,
                           int prm_delay,
                           bool prm_can_looping,
                           GeometricActor* prm_pActor) {
//    int bpm = BgmConductor::_active_bgm_bpm;
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
    int delay = prm_delay+1+(GgafCore::RepeatSeq::nextVal(_seqkey_se_delay));
    if (delay > CONFIG::SE_DELAY_MAX_DEPTH-1) {
        delay = CONFIG::SE_DELAY_MAX_DEPTH-1;
    }
    _pRing_pSeArray->getNext(delay)->add(prm_pSe, prm_volume, prm_pan, prm_frequency_rate, prm_can_looping, prm_pActor);
}

void Spacetime::processSettlementBehavior() {
    GgafCore::Spacetime::processSettlementBehavior();
    //SE��炷
    SeArray* pSeArray = _pRing_pSeArray->next(); //��i�߂�SE�z��擾
    if (pSeArray->_p > 0) {
        int se_p = pSeArray->_p;
        for (int p = 0; p < se_p; p++) {
            pSeArray->play(p);
        }
        pSeArray->_p = 0; //���Z�b�g
    }
    GgafCore::RepeatSeq::setMin(_seqkey_se_delay); //����nextVal��0��Ԃ���
}

void Spacetime::draw() {
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;

    //�����ŁA�S Model �ɑ΂���TextureBlinker�̏�Ԃ�i�s������
    ModelConnection* pModelCon = pGOD->_pModelManager->getFirstConnection();
    while (pModelCon) {
        pModelCon->peek()->_pTexBlinker->behave();
        pModelCon = (ModelConnection*)(pModelCon->getNext());
    }

    //�����ŁA�S Effect �ɑ΂���Vew�ϊ��s���ݒ肷��悤�ɂ���
    pGOD->_pEffectManager->setParamPerFrameAll();

    //�i�K�����_�����O�`��
    //�`�揇�A�N�^�[���X�g���\�z
    FigureActor* pDrawLastActor_in_render_depth = nullptr;
    FigureActor* pDrawNextActor_in_render_depth = nullptr;
    FigureActor* pDrawActor = nullptr; //���X�g�̐擪�A�N�^�[������
    for (int i = ALL_RENDER_DEPTH_INDEXS_NUM - 1; i >= 0; i--) { //������
        pDrawLastActor_in_render_depth = _papLastActor_in_render_depth[i];
        if (pDrawLastActor_in_render_depth) {
            if (!pDrawActor) {
                pDrawActor = _papFirstActor_in_render_depth[i];  //��ԍŏ��ɕ\������A�N�^�[
            }
            _papFirstActor_in_render_depth[i] = nullptr;   //����̂��߂Ƀ��Z�b�g
            _papLastActor_in_render_depth[i]  = nullptr;   //����̂��߂Ƀ��Z�b�g
            for (i-- ; i >= 0; i--) {
                pDrawNextActor_in_render_depth = _papFirstActor_in_render_depth[i];
                if (pDrawNextActor_in_render_depth) {
                    pDrawLastActor_in_render_depth->_pNextRenderActor = pDrawNextActor_in_render_depth;
                    i++;
                    break;
                }
            }
        }
    }

    while (pDrawActor) {
        Spacetime::_pActor_draw_active = pDrawActor;
        GgafCore::Scene* pPlatformScene = pDrawActor->getSceneMediator()->getPlatformScene();

#ifdef MY_DEBUG
        if (pPlatformScene->instanceOf(Obj_GgafDx_Scene)) {
            //OK
        } else {
            throwCriticalException("err2. �`��A�N�^�[�̏����V�[�� _pActor_draw_active["<<(pDrawActor->getName())<<"->getPlatformScene()["<<(pPlatformScene->getName())<<"]���AScene �ɕϊ��s�ł��Bthis="<<getName()<<" \n"
                    "pDrawActor->getPlatformScene()->_obj_class="<<pPlatformScene->_obj_class<< " Obj_GgafDx_Scene="<<Obj_GgafDx_Scene<<" \n"
                    "(pDrawActor->getPlatformScene()->_obj_class & Obj_GgafDx_Scene)="<<((pPlatformScene->_obj_class) & Obj_GgafDx_Scene) <<" ==?? Obj_GgafDx_Scene("<<Obj_GgafDx_Scene<<")");
        }
#endif
        //�e�����V�[���̃��J�[�e����ݒ肷��B
        pDrawActor->getEffect()->setAlphaMaster(
                                    ((GgafDx::Scene*)pPlatformScene)->_scene_alpha_from_top
                                 );
        //�f�t�H���g
        //SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        //SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
        //SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
        //�̏ꍇ�́A��� SetRenderState �������Ȃ��E�E�E
        if (pDrawActor->_cull_mode == D3DCULL_CCW) {
            if (pDrawActor->_zenable) {
                if (pDrawActor->_zwriteenable) {
                    pDrawActor->processDraw(); //�f�t�H���g��
                } else {
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                }
            } else {
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
                if (pDrawActor->_zwriteenable) {
                    pDrawActor->processDraw();
                } else {
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                }
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
            }
        } else {
            pDevice->SetRenderState(D3DRS_CULLMODE, pDrawActor->_cull_mode);
            if (pDrawActor->_zenable) {
                if (pDrawActor->_zwriteenable) {
                    pDrawActor->processDraw();
                } else {
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                }
            } else {
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
                if (pDrawActor->_zwriteenable) {
                    pDrawActor->processDraw();
                } else {
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                }
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
            }
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        }

        pDrawActor = Spacetime::_pActor_draw_active->_pNextRenderActor;
        //set�n�`��̏ꍇ�́ApDrawActor->processDraw() �������ŁA
        //Spacetime::_pActor_draw_active ���Aset�n�̍ŏI�`��A�N�^�[�ɍX�V����Ă���B
        //_pNextRenderActor �ŕ\������΂���邱�Ƃ͂Ȃ��B
    }

    //�Ō��EndPass
    HRESULT hr;
    Effect* pEffect_active = EffectManager::_pEffect_active;
    if (pEffect_active) {
        _TRACE4_("�Ō�� EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
        hr = pEffect_active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
        hr = pEffect_active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "End()�Ɏ��s���܂����B");
#ifdef MY_DEBUG
        if (pEffect_active->_begin == false) {
            throwCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
        } else {
            pEffect_active->_begin = false;
        }
#endif
        Model* pModelLastDraw = ModelManager::_pModelLastDraw;
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        EffectManager::_pEffect_active = nullptr;
        ModelManager::_pModelLastDraw = nullptr;
        FigureActor::_hash_technique_last_draw = 0;
    }
}

int Spacetime::registerFigureActor2D(FigureActor* prm_pActor) {
    int render_depth_index;
    int specal_render_depth_index = prm_pActor->_specal_render_depth_index;
    if (specal_render_depth_index < 0) {
        //������ 2D�œ��ʂȕ`��[�x�w�薳�� ������
        render_depth_index = EX_RENDER_DEPTH_INDEXS_FRONT_NUM + prm_pActor->_z; //_z�l���v���C�I���e�B���`��[�x�B
        //��������J�b�g
        if (render_depth_index > RENDER_DEPTH_INDEX_BACK) {
            render_depth_index = RENDER_DEPTH_INDEX_BACK;
        } else if (render_depth_index < RENDER_DEPTH_INDEX_FRONT) {
            render_depth_index = RENDER_DEPTH_INDEX_FRONT;
        }
        if (_papFirstActor_in_render_depth[render_depth_index] == nullptr) {
            //2D�ł���prm_render_depth_index�ōŏ��̃A�N�^�[�̏ꍇ
            prm_pActor->_pNextRenderActor = nullptr;
            _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
            _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
        } else {
            //2D�œ���[�x��2D�̏ꍇ�A�A�����X�g�̂��K�ɒǉ����Ă���
            //�܂�A�Ō�� appendChild() ����΂���قǁA�`�揇����ɂȂ�A�v���C�I���e�B���������Ȃ�B
            FigureActor* pActorTmp = _papLastActor_in_render_depth[render_depth_index];
            pActorTmp->_pNextRenderActor = prm_pActor;
            prm_pActor->_pNextRenderActor = nullptr;
            _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
        }
    } else {
        //������ 2D�œ��ʂȕ`��[�x�w��L�� ������
        render_depth_index = specal_render_depth_index;
        if (_papFirstActor_in_render_depth[render_depth_index] == nullptr) {
            //����prm_render_depth_index�ōŏ��̃A�N�^�[�̏ꍇ
            prm_pActor->_pNextRenderActor = nullptr;
            _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
            _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
        } else {
            //��O�ɒǉ�
            FigureActor* pActorTmp = _papFirstActor_in_render_depth[render_depth_index];
            prm_pActor->_pNextRenderActor = pActorTmp;
            _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
        }
    }
    return render_depth_index;
}

int Spacetime::registerFigureActor3D(FigureActor* prm_pActor) {
    int render_depth_index;
    int specal_render_depth_index = prm_pActor->_specal_render_depth_index;
    //�������RD�̏ꍇ
    if (prm_pActor->isOutOfView()) {
        //�`�悵�Ȃ��̂œo�^�Ȃ�
        render_depth_index = -1;
    } else {

        if (specal_render_depth_index < 0) { //���ʂȕ`��[�x�w�薳��
            //������ 3D�œ��ʂȕ`��[�x�w�薳�� ������
            dxcoord dep = -prm_pActor->_dest_from_vppln_infront; //�I�u�W�F�N�g�̎��_����̋���(DIRECTX����)
            if (dep < 0.0) {
                render_depth_index = RENDER_DEPTH_INDEX_FRONT;
            } else if (0.0 <= dep && dep < _dep_resolution) {
                render_depth_index = RENDER_DEPTH_INDEX_FRONT + _paDep2Lv[DX_PX(dep)];
            } else {
                render_depth_index = RENDER_DEPTH_INDEX_BACK;
            }
            if (_papFirstActor_in_render_depth[render_depth_index] == nullptr) {
                //����prm_render_depth_index�ōŏ��̃A�N�^�[�̏ꍇ
                prm_pActor->_pNextRenderActor = nullptr;
                _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
                _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
            } else {
                if (!prm_pActor->_zwriteenable) {
                    //Z�l���������ܖ����I�u�W�F�N�g�͂��K�ɒǉ��B
                    //�[�x�̐[�����ɕ\���͍s���邪�B
                    //����̐[�x�́u�O�v�ɒǉ�   �� ���̐[�x�Ŏn�߂ɕ`�悳���
                    //����̐[�x�́u���K�v�ɒǉ� �� ���̐[�x�Ō�ɕ`�悳���
                    //�ƂȂ��Ă��邱�Ƃɒ��ӁB
                    //Z�l���������ނ̃A�N�^�[�͎n�߂̕��ɕ`�悷��ق����������Ȃ��`�Ǝv���āB
                    //���[�U�[�����Y��ɕ`�悳���\���������B
                    FigureActor* pActorTmp = _papLastActor_in_render_depth[render_depth_index];
                    pActorTmp->_pNextRenderActor = prm_pActor;
                    prm_pActor->_pNextRenderActor = nullptr;
                    _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
                } else {
                    //����[�x��3D�̏ꍇ�A�O�ɒǉ��ƁA���K�ɒǉ������݂ɍs���B
                    //���̂���Ȃ��Ƃ����邩�Ƃ����ƁAZ�o�b�t�@�L��̃I�u�W�F�N�g�ɔ������I�u�W�F�N�g�ƌ��������ꍇ�A
                    //����[�x�Ȃ̂ŁA�v���C�I���e�B�i�`�揇�j�ɂ���ē����Ȃ������������Ă��܂��B
                    //�����`�揇�𖈃t���[���ω������邱�ƂŁA���ݕ\���ł�������኱�̂��܂������s���B
                    //TODO:(�ۑ�)�Q�A�R�̃I�u�W�F�N�g�̌����͏ꍇ�͌����ڂɂ����e�ł��邪�A��������ł܂�Ɩ{���Ƀ`���`������B
                    if ((_frame_of_behaving & 1) == 1) { //�
                        //�O�ɒǉ�
                        FigureActor* pActorTmp = _papFirstActor_in_render_depth[render_depth_index];
                        prm_pActor->_pNextRenderActor = pActorTmp;
                        _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
                    } else {
                        //���K�ɒǉ�
                        FigureActor* pActorTmp = _papLastActor_in_render_depth[render_depth_index];
                        pActorTmp->_pNextRenderActor = prm_pActor;
                        prm_pActor->_pNextRenderActor = nullptr;
                        _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
                    }
                }
            }

        } else {
            //������ 3D�œ��ʂȕ`��[�x�w��L��
            render_depth_index = specal_render_depth_index;
            if (_papFirstActor_in_render_depth[render_depth_index] == nullptr) {
                //����prm_render_depth_index�ōŏ��̃A�N�^�[�̏ꍇ
                prm_pActor->_pNextRenderActor = nullptr;
                _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
                _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
            } else {
                //�O�ɒǉ�
                FigureActor* pActorTmp = _papFirstActor_in_render_depth[render_depth_index];
                prm_pActor->_pNextRenderActor = pActorTmp;
                _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
            }
        }
    }
    return render_depth_index;
}

Spacetime::~Spacetime() {
    GGAF_DELETE(_pRing_pSeArray);
    GGAF_DELETEARR(_paDep2Lv);
    GGAF_DELETEARR(_papFirstActor_in_render_depth);
    GGAF_DELETEARR(_papLastActor_in_render_depth);
}