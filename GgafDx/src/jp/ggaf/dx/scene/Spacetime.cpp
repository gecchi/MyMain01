#include "jp/ggaf/dx/scene/Spacetime.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/core/util/RepeatSeq.h"
#include "jp/ggaf/core/util/lineartree/LinearOctree.hpp"
#include "jp/ggaf/core/util/lineartree/LinearQuadtree.hpp"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelConnection.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/dx/scene/Scene.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/dx/sound/Se.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/dx/model/MassModel.h"

using namespace GgafDx;

int Spacetime::render_depth_index_active = 0;
std::string Spacetime::_seqkey_se_delay = "_SE_D_";

WorldOctree* Spacetime::_pWorldOctree = nullptr;
WorldOctreeRounder* Spacetime::_pWorldOctreeRounder = nullptr;
WorldQuadtree* Spacetime::_pWorldQuadtree = nullptr;
WorldQuadtreeRounder* Spacetime::_pWorldQuadtreeRounder = nullptr;
ViewQuadtree* Spacetime::_pViewQuadtree = nullptr;
ViewQuadtreeRounder* Spacetime::_pViewQuadtreeRounder = nullptr;

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
_x_bound_left  (-DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())), //�J�����̎ʂ��͈́�Spacetime�͈̔�
_x_bound_right (+DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())),
_y_bound_bottom(-DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())),
_y_bound_top   (+DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())),
_z_bound_near  (-DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())),
_z_bound_far   (+DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())),
_x_bound_left_b   (_x_bound_left    + PX_C(CONFIG::GAME_BUFFER_WIDTH  / 2)),
_x_bound_right_b  (_x_bound_right   + PX_C(CONFIG::GAME_BUFFER_WIDTH  / 2)),
_y_bound_bottom_b (-_y_bound_bottom + PX_C(CONFIG::GAME_BUFFER_HEIGHT / 2)),
_y_bound_top_b    (-_y_bound_top    + PX_C(CONFIG::GAME_BUFFER_HEIGHT / 2))
{
    _obj_class |= Obj_GgafDx_Spacetime;
    _class_name = "Spacetime";

    _TRACE_("Spacetime World  Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");
    _TRACE_("Spacetime Screen Bound = X("<<_x_bound_left_b<<" ~ "<<_x_bound_right_b<<") Y("<<_y_bound_top_b<<" ~ "<<_y_bound_bottom_b<<")");

    _w_r =  1.0 * CONFIG::GAME_BUFFER_WIDTH / CONFIG::RENDER_TARGET_BUFFER_WIDTH;
    _h_r =  1.0 * CONFIG::GAME_BUFFER_HEIGHT / CONFIG::RENDER_TARGET_BUFFER_HEIGHT;

    _primary_buffer_source_left = CONFIG::PRIMARY_VIEW_RENDER_BUFFER_SOURCE_LEFT*_w_r;
    _primary_buffer_source_top = CONFIG::PRIMARY_VIEW_RENDER_BUFFER_SOURCE_TOP*_h_r;
    _primary_buffer_source_width = CONFIG::PRIMARY_VIEW_RENDER_BUFFER_SOURCE_WIDTH*_w_r;
    _primary_buffer_source_height = CONFIG::PRIMARY_VIEW_RENDER_BUFFER_SOURCE_HEIGHT*_h_r;

    _secondary_buffer_source_left = CONFIG::SECONDARY_VIEW_RENDER_BUFFER_SOURCE_LEFT*_w_r;
    _secondary_buffer_source_top = CONFIG::SECONDARY_VIEW_RENDER_BUFFER_SOURCE_TOP*_h_r;
    _secondary_buffer_source_width = CONFIG::SECONDARY_VIEW_RENDER_BUFFER_SOURCE_WIDTH*_w_r;
    _secondary_buffer_source_height = CONFIG::SECONDARY_VIEW_RENDER_BUFFER_SOURCE_HEIGHT*_h_r;

//TODO:�t�H�O����
//    _colFog.r = 0.0;
//    _colFog.g = 0.0;
//    _colFog.b = 0.0;
//    _colFog.a = 1.0;
    _papFirstRenderActor = NEW FigureActor*[ALL_RENDER_DEPTH_INDEXS_NUM];
    _papLastRenderActor = NEW FigureActor*[ALL_RENDER_DEPTH_INDEXS_NUM];
    for (int i = 0; i < ALL_RENDER_DEPTH_INDEXS_NUM; i++) {
        _papFirstRenderActor[i] = nullptr;
        _papLastRenderActor[i] = nullptr;
    }
    //��ɃJ������NEW���Ă����Ȃ��Ƃ����Ȃ��B
    _pCamera = prm_pCamera;
    Util::_pCam = prm_pCamera;

    bringSceneMediator()->appendGroupChild(_pCamera);

    _pRing_pSeArray = NEW GgafCore::RingLinkedList<SeArray>();
    for (int i = 0; i < SeTransmitterForActor::_se_delay_max_depth; i++) { //GGAF_END_DELAY�͍ő����x��t���[�������A����SE�̒x���̍ō��t���[�����Ƃ��Ă��g��
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
        _paDep2Lv[z] = (int) ( sin( pow(ang, e/PI) ) * (CONFIG::RENDER_DEPTH_INDEXS_NUM-1) );
    }
    //�n�}�������ƃ���
    //pow(x,y)��
    //double ang = RCNV(0, px_dep_resolution, z, 0, period); �� z = 0 �̏ꍇ ang = -0; �ɂȂ�
    //GCC�̏ꍇ�͒ꂪ���Ɖ��߂����̂��A pow(ang, e/PI) = -1.#IND �ƂȂ��Ă��܂��������ɂ�肠��B
    //VC�� 0 �ɂȂ����B
    //pow���g���Ƃ��͋C�����悤�B

    _TRACE_("�ʏ�̒i�K�����_�����O�[�x���F"<<CONFIG::RENDER_DEPTH_INDEXS_NUM);
    _TRACE_("�ʏ�̒i�K�����_�����O�����͈́F"<<DX_C(prm_pCamera->getZFar())<<" * "<<CONFIG::RENDER_DEPTH_STAGE_RATIO <<
                                             " = "<< DX_C(_dep_resolution)   );
    _TRACE_("�J��������̋���  0 ~ "<<DX_C(_dep_resolution)<< " ��Actor�́A �[�x���l������ĉ����̃I�u�W�F�N�g���珇�Ƀ����_�����O���s���܂��B");
    _TRACE_(DX_C(_dep_resolution)<<" ��艓���I�u�W�F�N�g�͑S�ē���[�x�Ƃ��čŏ��Ƀ����_�����O����܂��B");

    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        //�l���؍쐬
        _TRACE_("�l���؍쐬�J�n");
        Spacetime::_pWorldQuadtree = NEW WorldQuadtree(CONFIG::WORLD_HIT_CHECK_QUADTREE_LEVEL,
                                                              _x_bound_left  ,_y_bound_bottom,
                                                              _x_bound_right ,_y_bound_top    );
        Spacetime::_pWorldQuadtreeRounder =
                _pWorldQuadtree->createRounder(&GgafCore::Actor::executeHitChk_MeAnd);
        _TRACE_("�l���؍쐬�I��");
    } else {
        //�����؍쐬
        _TRACE_("�����؍쐬�J�n");
        Spacetime::_pWorldOctree = NEW WorldOctree(CONFIG::WORLD_HIT_CHECK_OCTREE_LEVEL,
                                                          _x_bound_left  ,_y_bound_bottom, _z_bound_near ,
                                                          _x_bound_right ,_y_bound_top   , _z_bound_far   );
        Spacetime::_pWorldOctreeRounder =
                _pWorldOctree->createRounder(&GgafCore::Actor::executeHitChk_MeAnd);
        _TRACE_("�����؍쐬�I��");
    }

    //Board�p�l���؍쐬
    _TRACE_("Board�p�l���؍쐬�J�n");
    Spacetime::_pViewQuadtree = NEW ViewQuadtree(CONFIG::VIEW_HIT_CHECK_QUADTREE_LEVEL,
                                                        _x_bound_left_b  ,_y_bound_top_b,
                                                        _x_bound_right_b , _y_bound_bottom_b   );
    Spacetime::_pViewQuadtreeRounder =
            _pViewQuadtree->createRounder(&GgafCore::Actor::executeHitChk_MeAnd);
    _TRACE_("Board�p�l���؍쐬�I��");
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
    if (delay > SeTransmitterForActor::_se_delay_max_depth-1) {
        delay = SeTransmitterForActor::_se_delay_max_depth-1;
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
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;

    //�����ŁA�S Model �ɑ΂���TextureBlinker�̏�Ԃ�i�s������
    ModelConnection* pModelCon = pCARETAKER->_pModelManager->getFirstConnection();
    while (pModelCon) {
        pModelCon->peek()->_pTexBlinker->behave();
        pModelCon = (ModelConnection*)(pModelCon->getNext());
    }

    //�����ŁA�S Effect �ɑ΂���Vew�ϊ��s���ݒ肷��悤�ɂ���
    pCARETAKER->_pEffectManager->setParamPerFrameAll();

    //�i�K�����_�����O�`��
    //�`�揇�A�N�^�[���X�g���\�z
    // �f�[�^�C���[�W
    // �� �� �A�N�^�[
    // [0]�`[3] �� �����_�����O�[�x�i [0]�F��O �` [3]�F���j���S�v�f���́FALL_RENDER_DEPTH_INDEXS_NUM
    //
    // [0] => [ �@ -> �A -> �B -> �C -> �D -> nullptr ]
    // [1] => [ nullptr ]
    // [2] => [ �E -> �F -> nullptr ]
    // [3] => [ �G -> nullptr ]
    //
    // ��}�̂悤�ȏꍇ�A���L�̂悤�ɃA�N�^�[�i�̃|�C���^�j���ݒ肳��Ă���
    //  _papFirstRenderActor[0] = �@     , _papLastRenderActor[0]  = �D
    //  _papFirstRenderActor[1] = nullptr, _papLastRenderActor[1]  = nullptr
    //  _papFirstRenderActor[2] = �E     , _papLastRenderActor[2]  = �F
    //  _papFirstRenderActor[3] = �G     , _papLastRenderActor[3]  = �G
    //  �u->�v �̘A���̓����o�ϐ� _pNextRenderActor �ɂ��P�����A�����X�g
    //�y�`�掞�����z
    // �Ō�� _papLastRenderActor[n] ���A�ЂƂ�O�� _papFirstRenderActor[n-1] �̃A�N�^�[�ɘA������ĕ`��
    // �G -> �E -> �F -> �@ -> �A -> �B -> �C -> �D
#ifdef MY_DEBUG
    if (GgafDx::Input::isPushedDownKey(DIK_R)) {
        _TRACE_("�i�K�����_�����O��� ---->");
        dumpRenderDepthOrder();
        _TRACE_("<---- �i�K�����_�����O���");
    }
#endif
    FigureActor* pDrawLastActor_in_render_depth = nullptr;
    FigureActor* pDrawNextActor_in_render_depth = nullptr;
    FigureActor* pDrawActor = nullptr; //���X�g�̐擪�A�N�^�[������
    for (int i = ALL_RENDER_DEPTH_INDEXS_NUM - 1; i >= 0; i--) { //������
        pDrawLastActor_in_render_depth = _papLastRenderActor[i];
        if (pDrawLastActor_in_render_depth) {
            if (!pDrawActor) {
                pDrawActor = _papFirstRenderActor[i];  //��ԍŏ��ɕ\������A�N�^�[
            }
            _papFirstRenderActor[i] = nullptr;   //����̂��߂Ƀ��Z�b�g
            _papLastRenderActor[i]  = nullptr;   //����̂��߂Ƀ��Z�b�g
            for (i-- ; i >= 0; i--) {
                pDrawNextActor_in_render_depth = _papFirstRenderActor[i];
                if (pDrawNextActor_in_render_depth) {
                    //���̍Ō�̃A�N�^�[���A���߂̎�O�̃A�N�^�[�̐擪�Ƀ����N
                    pDrawLastActor_in_render_depth->_pNextRenderActor = pDrawNextActor_in_render_depth;
                    i++;
                    break;
                }
            }
        }
    }

    while (pDrawActor) {
        GgafCore::Scene* pPlatformScene = pDrawActor->getSceneMediator()->getPlatformScene();

#ifdef MY_DEBUG
        if (pPlatformScene->instanceOf(Obj_GgafDx_Scene)) {
            //OK
        } else {
            throwCriticalException("err2. �`��A�N�^�[�̏����V�[�� pDrawActor["<<(pDrawActor->getName())<<"->getPlatformScene()["<<(pPlatformScene->getName())<<"]���AScene �ɕϊ��s�ł��Bthis="<<getName()<<" \n"
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

        pDrawActor = pDrawActor->_pNextRenderActor;
        //set�n�`��̏ꍇ�́ApDrawActor->processDraw() �������ŁA
        //pDrawActor->_pNextRenderActor ���A�ŏI�`��A�N�^�[�ɍX�V����Ă���B
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
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        EffectManager::_pEffect_active = nullptr;
        ModelManager::_pModelLastDraw = nullptr;
        FigureActor::_hash_technique_last_draw = 0;
    }
}

int Spacetime::registerDrawActor(FigureActor* prm_pActor) {
    int render_depth_index = -1;
    int specal_render_depth_index = prm_pActor->_specal_render_depth_index;
    if (prm_pActor->_is_fix_2D) {
        if (specal_render_depth_index < 0) {
            //������ 2D�œ��ʂȕ`��[�x�w�薳�� ������
            render_depth_index = RENDER_DEPTH_NEAR_INDEX + prm_pActor->_z; //_z�l���v���C�I���e�B���`��[�x�B
            //��������J�b�g
            if (render_depth_index > RENDER_DEPTH_FAR_INDEX) {
                render_depth_index = RENDER_DEPTH_FAR_INDEX;
            } else if (render_depth_index < RENDER_DEPTH_NEAR_INDEX) {
                render_depth_index = RENDER_DEPTH_NEAR_INDEX;
            }
        } else {
            //������ 2D�œ��ʂȕ`��[�x�w��L�� ������
            render_depth_index = specal_render_depth_index + prm_pActor->_z; //_z�l���v���C�I���e�B���`��[�x;
            //�����J�b�g
            if (render_depth_index > ALL_RENDER_DEPTH_INDEXS_NUM-1) {
                render_depth_index = ALL_RENDER_DEPTH_INDEXS_NUM-1;
            }
        }

        if (_papFirstRenderActor[render_depth_index] == nullptr) {
            //2D�ł���prm_render_depth_index�ōŏ��̃A�N�^�[�̏ꍇ
            prm_pActor->_pNextRenderActor = nullptr;
            _papFirstRenderActor[render_depth_index] = prm_pActor;
            _papLastRenderActor[render_depth_index] = prm_pActor;
        } else {
            //2D�œ���[�x��2D�̏ꍇ�A�A�����X�g�̂��K�ɒǉ����Ă���(���̐[�x�Ō�ɕ`�悳���)
            //�܂�A�Ō�� appendChild() ����΂���قǁA�`�揇����ɂȂ�A�v���C�I���e�B���������Ȃ�݌v
            FigureActor* pActorTmp = _papLastRenderActor[render_depth_index];
            pActorTmp->_pNextRenderActor = prm_pActor;
            prm_pActor->_pNextRenderActor = nullptr;
            _papLastRenderActor[render_depth_index] = prm_pActor;
        }

    } else {
        //�������RD�̏ꍇ
        if (specal_render_depth_index < 0) { //���ʂȕ`��[�x�w�薳��
            //������ 3D�œ��ʂȕ`��[�x�w�薳�� ������
            dxcoord dep = -prm_pActor->_dest_from_vppln_infront; //�I�u�W�F�N�g�̎��_����̋���(DIRECTX����)
            if (dep < 0.0) {
                render_depth_index = RENDER_DEPTH_NEAR_INDEX;
            } else if (0.0 <= dep && dep < _dep_resolution) {
                render_depth_index = RENDER_DEPTH_NEAR_INDEX + _paDep2Lv[DX_PX(dep)];
            } else {
                render_depth_index = RENDER_DEPTH_FAR_INDEX;
            }
            if (_papFirstRenderActor[render_depth_index] == nullptr) {
                //����prm_render_depth_index�ōŏ��̃A�N�^�[�̏ꍇ
                prm_pActor->_pNextRenderActor = nullptr;
                _papFirstRenderActor[render_depth_index] = prm_pActor;
                _papLastRenderActor[render_depth_index] = prm_pActor;
            } else {
                if (!prm_pActor->_zwriteenable) {
                    //Z�l���������ܖ����I�u�W�F�N�g�͂��K�ɒǉ��B
                    //�[�x�̐[�����ɕ\���͍s���邪�B
                    //����̐[�x�́u�擪�v�ɒǉ� �� ���̐[�x�Ŏn�߂ɕ`�悳��� => �w�ʂɕ`�悳���
                    //����̐[�x�́u���K�v�ɒǉ� �� ���̐[�x�Ō�ɕ`�悳���   => ��O�ɕ`�悳���
                    //���[�U�[�����Y��ɕ`�悳���\���������B
                    FigureActor* pActorTmp = _papLastRenderActor[render_depth_index];
                    pActorTmp->_pNextRenderActor = prm_pActor;
                    prm_pActor->_pNextRenderActor = nullptr;
                    _papLastRenderActor[render_depth_index] = prm_pActor;
                } else {
                    //Z�l���������ރI�u�W�F�N�g
                    //Z�l���������ރA�N�^�[�͊�{�́u�擪�v�ɒǉ��������B
                    //�����łȂ��ꍇ�́A�w��ɉB���I�u�W�F�N�g�̕`�揈�����ȗ����A�`��������オ�邽�߁B
                    //�������A�������̏ꍇ�́A���R�Ɍ����邽�߂ɂ́A���u���K�v�ɒǉ�����ׂ��Ȃ̂�
                    if (prm_pActor->getAlpha() < 1.0f) {
                        //����[�x�Ŕ������̏ꍇ�A�O�ɒǉ��ƁA���K�ɒǉ������݂ɍs���B
                        //�Ȃ�ł܂�����Ȃ��Ƃ����邩�Ƃ����ƁAZ�o�b�t�@�L��̃I�u�W�F�N�g�ɔ������I�u�W�F�N�g�ƌ��������ꍇ�A
                        //����[�x�Ȃ̂ŁA�v���C�I���e�B�i�`�揇�j�ɂ���ē����Ȃ������������Ă��܂��B
                        //�����`�揇�𖈃t���[���ω������邱�ƂŁA���ݕ\���ł�������኱�̂��܂������s���B
                        //TODO:(�ۑ�)�Q�A�R�̃I�u�W�F�N�g�̌����͏ꍇ�͌����ڂɂ����e�ł��邪�A��������ł܂�Ɩ{���Ƀ`���`������B
                        if ((_frame_of_behaving & 1) == 1) { //�
                            //�O�ɒǉ�
                            FigureActor* pActorTmp = _papFirstRenderActor[render_depth_index];
                            prm_pActor->_pNextRenderActor = pActorTmp;
                            _papFirstRenderActor[render_depth_index] = prm_pActor;
                        } else {
                            //���K�ɒǉ�
                            FigureActor* pActorTmp = _papLastRenderActor[render_depth_index];
                            pActorTmp->_pNextRenderActor = prm_pActor;
                            prm_pActor->_pNextRenderActor = nullptr;
                            _papLastRenderActor[render_depth_index] = prm_pActor;
                        }
                    } else {
                        //�������ł͂Ȃ��ꍇ�A�[�x���{�P���āu�擪�v�ɒǉ��B
                        //CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_FAR > 0 ���ۏ؂���Ă���̂ŁA
                        //_papFirstRenderActor[render_depth_index+1] �͗v�f�I�[�o�[�ɂȂ�Ȃ�
                        render_depth_index++;
                        if (_papFirstRenderActor[render_depth_index] == nullptr) {
                            //����prm_render_depth_index�ōŏ��̃A�N�^�[�̏ꍇ
                            prm_pActor->_pNextRenderActor = nullptr;
                            _papFirstRenderActor[render_depth_index] = prm_pActor;
                            _papLastRenderActor[render_depth_index] = prm_pActor;
                        } else {
                            FigureActor* pActorTmp = _papFirstRenderActor[render_depth_index];
                            prm_pActor->_pNextRenderActor = pActorTmp;
                            _papFirstRenderActor[render_depth_index] = prm_pActor;
                        }
                    }
                }
            }

        } else {
            //������ 3D�œ��ʂȕ`��[�x�w��L��
            render_depth_index = specal_render_depth_index;
            if (_papFirstRenderActor[render_depth_index] == nullptr) {
                //����prm_render_depth_index�ōŏ��̃A�N�^�[�̏ꍇ
                prm_pActor->_pNextRenderActor = nullptr;
                _papFirstRenderActor[render_depth_index] = prm_pActor;
                _papLastRenderActor[render_depth_index] = prm_pActor;
            } else {
                //���K�ɒǉ�
                FigureActor* pActorTmp = _papLastRenderActor[render_depth_index];
                pActorTmp->_pNextRenderActor = prm_pActor;
                prm_pActor->_pNextRenderActor = nullptr;
                _papLastRenderActor[render_depth_index] = prm_pActor;
//                    //�O�ɒǉ�
//                    FigureActor* pActorTmp = _papFirstRenderActor[render_depth_index];
//                    prm_pActor->_pNextRenderActor = pActorTmp;
//                    _papFirstRenderActor[render_depth_index] = prm_pActor;
            }
        }
    }
    return render_depth_index;
}

void Spacetime::cnvViewCoordToWorld(coord prm_view_x, coord prm_view_y, coord prm_depth,
                                    coord& out_world_x, coord& out_world_y, coord& out_world_z) {
    Camera* pCam = getCamera();
    dxcoord target_dep_d = C_DX(prm_depth); //�I�u�W�F�N�g�̋���
    dxcoord zt_rate = RCNV_to_0_1(pCam->_zn, pCam->_zf, target_dep_d);
    D3DXMATRIX matScreen = D3DXMATRIX(
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        C_PX(prm_view_x), C_PX(prm_view_y), 0, 1.0f,  //Near Z=0
        C_PX(prm_view_x), C_PX(prm_view_y), 1, 1.0f   //Far  Z=1
    );
    D3DXMATRIX matWorldCoords = matScreen * pCam->_matInvViewPort_Proj_View;
    //���L���v�Z�œK��
    //    const float near_W = out._34;
    //    const float far_W = out._44;
    //    const float MinZ = pCam->_viewport.MinZ; // = 0
    //    const float MaxZ = pCam->_viewport.MaxZ; // = 1
    //    dxcoord x = RCNV(MinZ, MaxZ, zt_rate, out._31 / near_W, out._41 / far_W);
    //    dxcoord y = RCNV(MinZ, MaxZ, zt_rate, out._32 / near_W, out._42 / far_W);
    //    dxcoord z = RCNV(MinZ, MaxZ, zt_rate, out._33 / near_W, out._43 / far_W);
    const float near_W = matWorldCoords._34;
    const float far_W = matWorldCoords._44;
    const float W = (far_W*near_W);
    const float near_W_zt_rate = (near_W * zt_rate);
    dxcoord x = (near_W_zt_rate*matWorldCoords._41 - ((zt_rate - 1) * (far_W*matWorldCoords._31))) / W;
    dxcoord y = (near_W_zt_rate*matWorldCoords._42 - ((zt_rate - 1) * (far_W*matWorldCoords._32))) / W;
    dxcoord z = (near_W_zt_rate*matWorldCoords._43 - ((zt_rate - 1) * (far_W*matWorldCoords._33))) / W;
    out_world_x = DX_C(x);
    out_world_y = DX_C(y);
    out_world_z = DX_C(z);
}

void Spacetime::cnvWorldCoordToView(coord prm_world_x, coord prm_world_y, coord prm_world_z,
                                    coord& out_view_x, coord& out_view_y) {
    //������ʂ���̋����̊����ŋ��߂�
    const dxcoord fX = C_DX(prm_world_x);
    const dxcoord fY = C_DX(prm_world_y);
    const dxcoord fZ = C_DX(prm_world_z);
    Camera *pCam = getCamera();
    const D3DXPLANE *pPlnTop = &(pCam->_plnTop);
    dxcoord len_top = -(pPlnTop->a*fX + pPlnTop->b*fY + pPlnTop->c*fZ + pPlnTop->d);
    const D3DXPLANE *pPlnBottom = &(pCam->_plnBottom);
    dxcoord len_bottom = -(pPlnBottom->a*fX + pPlnBottom->b*fY + pPlnBottom->c*fZ + pPlnBottom->d);
    const D3DXPLANE *pPlnLeft = &(pCam->_plnLeft);
    dxcoord len_left = -(pPlnLeft->a*fX + pPlnLeft->b*fY + pPlnLeft->c*fZ + pPlnLeft->d);
    const D3DXPLANE *pPlnRight = &(pCam->_plnRight);
    dxcoord len_rigth = -(pPlnRight->a*fX + pPlnRight->b*fY + pPlnRight->c*fZ + pPlnRight->d);
    dxcoord x =  PX_DX(_primary_buffer_source_width ) * (len_left / (len_left+len_rigth ) );
    dxcoord y =  PX_DX(_primary_buffer_source_height) * (len_top  / (len_top +len_bottom) );
    out_view_x = DX_C(x);
    out_view_y = DX_C(y);
}

void Spacetime::executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
#ifdef MY_DEBUG
    if (_is_running_processHitCheck == false) {
        throwCriticalException("executeWorldHitCheck() �́AprocessHitCheck() ���ł������s�ł��܂���B");
    }
#endif
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        Spacetime::_pWorldQuadtreeRounder->executeAll(prm_kind_groupA, prm_kind_groupB);
    } else {
        Spacetime::_pWorldOctreeRounder->executeAll(prm_kind_groupA, prm_kind_groupB);
    }
}

void Spacetime::executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
#ifdef MY_DEBUG
    if (_is_running_processHitCheck == false) {
        throwCriticalException("executeViewHitCheck() �́AprocessHitCheck() ���ł������s�ł��܂���B");
    }
#endif
    Spacetime::_pViewQuadtreeRounder->executeAll(prm_kind_groupA, prm_kind_groupB);
}
void Spacetime::processFinal() {
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        Spacetime::_pWorldQuadtree->clearAllElem();
    } else {
        Spacetime::_pWorldOctree->clearAllElem();
    }
    Spacetime::_pViewQuadtree->clearAllElem();
}
void Spacetime::dumpRenderDepthOrder() {
    for (int i = 0; i < ALL_RENDER_DEPTH_INDEXS_NUM; i++) {
        FigureActor* pDrawActor = _papFirstRenderActor[i];
        if (!pDrawActor) {
            continue;
        }
        if (i < RENDER_DEPTH_NEAR_INDEX) {
            _TRACE_N_("EX_NEAR_DEP["<<i<<"]");
        } else if (RENDER_DEPTH_NEAR_INDEX <= i && i <= RENDER_DEPTH_FAR_INDEX) {
            _TRACE_N_("NORMAL_DEP ["<<i<<"]");
        } else if (i > RENDER_DEPTH_FAR_INDEX) {
            _TRACE_N_("EX_FAR_DEP ["<<i<<"]");
        }
        while(pDrawActor) {
            _TRACE_N_("->["<<pDrawActor->getName()<<"]"<<(pDrawActor->_id)<<"");
            pDrawActor = pDrawActor->_pNextRenderActor;
        }
        _TRACE_N_("\n");
    }
}

Spacetime::~Spacetime() {
    GGAF_DELETE(_pRing_pSeArray);
    GGAF_DELETEARR(_paDep2Lv);
    GGAF_DELETEARR(_papFirstRenderActor);
    GGAF_DELETEARR(_papLastRenderActor);

#ifdef MY_DEBUG
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        _TRACE_("World�l���� -->");
        Spacetime::_pWorldQuadtree->putTree();
        _TRACE_("<--World�l����");
    } else {
        _TRACE_("World������ -->");
        Spacetime::_pWorldOctree->putTree();
        _TRACE_("<--World������");
    }
    _TRACE_("View�l���� -->");
    Spacetime::_pViewQuadtree->putTree();
    _TRACE_("<--View�l����");
#endif
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        GGAF_DELETE(Spacetime::_pWorldQuadtree);
        GGAF_DELETE(Spacetime::_pWorldQuadtreeRounder);
    } else {
        GGAF_DELETE(Spacetime::_pWorldOctree);
        GGAF_DELETE(Spacetime::_pWorldOctreeRounder);
    }
    GGAF_DELETE(Spacetime::_pViewQuadtree);
    GGAF_DELETE(Spacetime::_pViewQuadtreeRounder);
}
