#include "jp/ggaf/dx/actor/FigureActor.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/util/Rgb.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/ModelConnection.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/EffectConnection.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/scene/Scene.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/scene/supporter/AlphaCurtain.h"
#include "jp/ggaf/dx/actor/supporter/Colorist.h"
#include "jp/ggaf/dx/Config.h"


using namespace GgafDx;

hashval FigureActor::_hash_technique_last_draw = 0;

FigureActor::FigureActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect,
                         const char* prm_technique,
                         Checker* prm_pChecker) :

                             GeometricActor(prm_name,
                                            prm_pChecker),
_pModelCon(
    (ModelConnection*)(
        pCARETAKER->_pModelManager->connect(prm_model, this)
    )
),
_pModel((Model*)_pModelCon->peek()),
_pEffectCon(
    (EffectConnection*)(
        pCARETAKER->_pEffectManager->connect(prm_effect, this)
    )
),
_pEffect((Effect*)_pEffectCon->peek()),
_pAlphaFader(nullptr),
_pColorist(nullptr)
{
    _obj_class |= Obj_GgafDx_FigureActor;
    _class_name = "FigureActor";
    _technique = NEW char[256];
    FigureActor::changeEffectTechnique(prm_technique);
    _temp_technique = NEW char[256];
    _hash_temp_technique = 0;
    _frame_of_behaving_temp_technique_end = 0;
    _is_temp_technique = false;
    _pNextRenderActor = nullptr;
    //�}�e���A�����R�s�[
    _paMaterial = NEW D3DMATERIAL9[_pModel->_num_materials];
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i] = _pModel->_paMaterial_default[i];
    }
    _alpha = 1.0f;
    //�ő勗�����_
    _now_drawdepth = 0;
    _specal_render_depth_index = -1;
    _zenable = true;
    _zwriteenable = true;
    if (_pModelCon->chkFirstConnectionIs(this) ) {
        _is_first_model_connector = true;
    } else {
        _is_first_model_connector = false;
    }
    if (_pEffectCon->chkFirstConnectionIs(this) ) {
        _is_first_effect_connector = true;
    } else {
        _is_first_effect_connector = false;
    }
    _cull_enable = true;
    _cull_mode_default = D3DCULL_CCW;
    _cull_mode = _cull_mode_default;
}

FigureActor::FigureActor(const char* prm_name,
                         const char* prm_model,
                         const char prm_model_type,
                         const char* prm_effect_id,
                         const char prm_effect_type,
                         const char* prm_technique,
                         Checker* prm_pChecker) :

                             GeometricActor(prm_name,
                                            prm_pChecker),
_pModelCon(
    (ModelConnection*)(
        pCARETAKER->_pModelManager->connect(
            (std::string(1, prm_model_type) + "," + std::string(prm_model)).c_str(), this
        )
    )
),
_pModel((Model*)_pModelCon->peek()),
_pEffectCon(
    (EffectConnection*)(
        pCARETAKER->_pEffectManager->connect(
            (std::string(1, prm_effect_type) + "," + std::string(prm_effect_id)).c_str(), this
        )
    )
),
_pEffect((Effect*)_pEffectCon->peek()),
_pAlphaFader(nullptr),
_pColorist(nullptr)
{
    _class_name = "FigureActor";

    _technique = NEW char[256];
    FigureActor::changeEffectTechnique(prm_technique);
    _temp_technique = NEW char[256];
    _hash_temp_technique = 0;
    _frame_of_behaving_temp_technique_end = 0;
    _is_temp_technique = false;
    _pNextRenderActor = nullptr;

    //�}�e���A�����R�s�[
    _paMaterial = NEW D3DMATERIAL9[_pModel->_num_materials];
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i] = _pModel->_paMaterial_default[i];
    }
    _alpha = 1.0f;
    _cull_enable = true;
    _cull_mode_default = D3DCULL_CCW;
    _cull_mode = _cull_mode_default;
    _now_drawdepth = 0;
    _specal_render_depth_index = -1;
    _zenable = true;
    _zwriteenable = true;
    if (_pModelCon->chkFirstConnectionIs(this) ) {
        _is_first_model_connector = true;
    } else {
        _is_first_model_connector = false;
    }
    if (_pEffectCon->chkFirstConnectionIs(this) ) {
        _is_first_effect_connector = true;
    } else {
        _is_first_effect_connector = false;
    }
}

AlphaFader* FigureActor::getAlphaFader() {
    return _pAlphaFader ? _pAlphaFader : _pAlphaFader = NEW AlphaFader(this);
}

Colorist* FigureActor::getColorist() {
    return _pColorist ? _pColorist : _pColorist = NEW Colorist(this);
}

void FigureActor::processPreDraw() {
    Spacetime* pSpacetime = pCARETAKER->getSpacetime();
    GgafCore::Scene* pPlatformScene = getSceneMediator()->getPlatformScene();
#ifdef MY_DEBUG
    if (pPlatformScene->instanceOf(Obj_GgafDx_Scene)) {
        //OK
    } else {
        throwCriticalException("name="<<getName()<<"��`��o�^���悤�Ƃ��܂������A�����V�[���� name="<<getName()<<"->getPlatformScene()["<<(pPlatformScene->getName())<<"]���AGgafDx::Scene �ɕϊ��s�ł��Bthis="<<NODE_INFO<<" \n"
                "getPlatformScene()->_obj_class="<<pPlatformScene->_obj_class<< " Obj_GgafDx_Scene="<<Obj_GgafDx_Scene<<" \n"
                "(getPlatformScene()->_obj_class & Obj_GgafDx_Scene)="<<((pPlatformScene->_obj_class) & Obj_GgafDx_Scene) <<" ==?? Obj_GgafDx_Scene("<<Obj_GgafDx_Scene<<")");
    }
#endif
    if (_pModel->_is_init_model == false) {
        onCreateModel(); //���f���쐬���̏�������
        _pModel->_is_init_model = true;
    }
    _pNextRenderActor = nullptr;
    if (isActiveInTheTree()) {
        GgafCore::Caretaker::_num_active_actor++;
        if (_alpha > 0.0f &&  ((GgafDx::Scene*)pPlatformScene)->_scene_alpha > 0.0f) { //isActiveInTheTree() �Ŕ��肷�邱��
            _now_drawdepth = _is_2D ? pSpacetime->registerFigureActor2D(this) : pSpacetime->registerFigureActor3D(this);
        }
    }

    //�ꎞ�e�N�j�b�N���ԃ`�F�b�N
    if (_is_temp_technique) {
        if (_frame_of_behaving_temp_technique_end <= _frame_of_behaving) {
            //�ꎞ�e�N�j�b�N���Ԗ����B���ɖ߂�
            _hash_technique = _hash_temp_technique;
            strcpy(_technique, _temp_technique);
            _is_temp_technique = false;
            //����̓_���B�z��̈悪�ǂ����ɂ������߁B_temp_technique = "";
            _hash_temp_technique = 0;
        }
    }
}

void FigureActor::setMaterialColor(float r, float g, float b) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.r = r;
        _paMaterial[i].Diffuse.r = r;
        _paMaterial[i].Ambient.g = g;
        _paMaterial[i].Diffuse.g = g;
        _paMaterial[i].Ambient.b = b;
        _paMaterial[i].Diffuse.b = b;
    }
}

void FigureActor::setMaterialRed(float r) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.r = r;
        _paMaterial[i].Diffuse.r = r;
    }
}
void FigureActor::setMaterialGreen(float g) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.g = g;
        _paMaterial[i].Diffuse.g = g;
    }
}
void FigureActor::setMaterialBlue(float b) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.b = b;
        _paMaterial[i].Diffuse.b = b;
    }
}

float FigureActor::getMaterialRed() {
    return _paMaterial[0].Diffuse.r;
}
float FigureActor::getMaterialGreen() {
    return _paMaterial[0].Diffuse.g;
}
float FigureActor::getMaterialBlue() {
    return _paMaterial[0].Diffuse.b;
}

void FigureActor::setMaterialColor(const GgafCore::Rgb* prm_rgb) {
    setMaterialColor(prm_rgb->_r, prm_rgb->_g, prm_rgb->_b);
}

void FigureActor::resetMaterialColor() {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        D3DMATERIAL9* p = &(_pModel->_paMaterial_default[i]);
        _paMaterial[i].Ambient.r = p->Ambient.r;
        _paMaterial[i].Diffuse.r = p->Diffuse.r;
        _paMaterial[i].Ambient.g = p->Ambient.g;
        _paMaterial[i].Diffuse.g = p->Diffuse.g;
        _paMaterial[i].Ambient.b = p->Ambient.b;
        _paMaterial[i].Diffuse.b = p->Diffuse.b;
    }
}
void FigureActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //���ݒ�A���݃}�e���A����Diffuse�ȊO�֌W�Ȃ�
    _paMaterial[0].Ambient.a = _alpha;
    _paMaterial[0].Diffuse.a = _alpha;
}

void FigureActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //���ݒ�A���݃}�e���A����Diffuse�ȊO�֌W�Ȃ�
    _paMaterial[0].Ambient.a = _alpha;
    _paMaterial[0].Diffuse.a = _alpha;
}
void FigureActor::setSpecialRenderDepthIndex(int prm_drawdepth) {
    if (prm_drawdepth < 0) {
        _specal_render_depth_index = 0;
    } else if (prm_drawdepth > ALL_RENDER_DEPTH_INDEXS_NUM-1) {
        _specal_render_depth_index = ALL_RENDER_DEPTH_INDEXS_NUM-1;
    } else {
        _specal_render_depth_index = prm_drawdepth;
    }
}
void FigureActor::resetSpecialRenderDepthIndex() {
    _specal_render_depth_index = -1;
}

void FigureActor::changeEffectTechnique(const char* prm_technique) {
    std::string technique = std::string(_pEffect->getName()) + "_" + std::string(prm_technique);
#ifdef MY_DEBUG
    if (technique.length() > 255) {
        throwCriticalException("�e�N�j�b�N�����������܂��Bprm_technique="<<prm_technique<<" technique="<<technique);
    }
#endif
    _hash_technique = UTIL::easy_hash(technique.c_str());
    strcpy(_technique, prm_technique);
}

void FigureActor::changeEffectTechniqueMoment(const char* prm_technique, frame prm_frame) {
    if (_is_temp_technique == false) { //���łɈꎞ�e�N�j�b�N�g�p���͖���
        //���X�̃e�N�j�b�N��ޔ�
        _hash_temp_technique = _hash_technique;
        strcpy(_temp_technique, _technique);
        //�e�N�j�b�N�ύX
        if (prm_frame == MAX_FRAME) {
            _frame_of_behaving_temp_technique_end = MAX_FRAME;
        } else {
            _frame_of_behaving_temp_technique_end = _frame_of_behaving + prm_frame; //�ύX�����t���[��
        }
        changeEffectTechnique(prm_technique);
        _is_temp_technique = true;
    }
}

void FigureActor::effectFlush(frame prm_frame) {
    changeEffectTechniqueMoment("Flush", prm_frame); //�t���b�V��
}

void FigureActor::effectBlendOne(frame prm_frame) {
    changeEffectTechniqueMoment("DestBlendOne", prm_frame);
}

void FigureActor::effectDefault() {
    if (_is_temp_technique) {
        _hash_technique = _hash_temp_technique;
        strcpy(_technique, _temp_technique);
        _is_temp_technique = false;
        _hash_temp_technique = 0;
    }
}
int FigureActor::isOutOfView() {
    if (_offscreen_kind == -1) {
        const dxcoord bound = getModel()->_bounding_sphere_radius * _rate_of_bounding_sphere_radius*2.0f;//�|����2�͋��E����傫�����āA��ʋ��E�̃`���c�L��}����
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_infront < bound) {
                            if (_dest_from_vppln_back < bound) {
                                //Viewport�͈͓�
                                _offscreen_kind = 0;
                            } else {
                                //�����ʂ�艜�Ŕ͈͊O
                                _offscreen_kind = 6;
                            }
                        } else {
                            //��O���ʂ���O�Ŕ͈͊O
                            _offscreen_kind = 5;
                        }
                    } else {
                        //�E���ʂ��E�Ŕ͈͊O
                        _offscreen_kind = 4;
                    }
                } else {
                    //�����ʂ�荶�Ŕ͈͊O
                    _offscreen_kind = 3;
                }
            } else {
                //�����ʂ�艺�Ŕ͈͊O
                _offscreen_kind = 2;
            }
        } else {
            //�㕽�ʂ���Ŕ͈͊O
            _offscreen_kind = 1;
        }
    }
    return _offscreen_kind;
}

FigureActor::~FigureActor() {
    GGAF_DELETEARR(_technique);
    GGAF_DELETEARR(_temp_technique);
    GGAF_DELETEARR(_paMaterial);
    GGAF_DELETE_NULLABLE(_pAlphaFader);
    GGAF_DELETE_NULLABLE(_pColorist);
    _pEffectCon->close();
    _pModelCon->close();
}
