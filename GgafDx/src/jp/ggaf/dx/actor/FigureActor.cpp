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

//FigureActor::FigureActor(const char* prm_name,
//                         const char* prm_model,
//                         const char* prm_effect,
//                         const char* prm_technique,
//                         CollisionChecker* prm_pChecker) :
//
//                             GeometricActor(prm_name,
//                                            prm_pChecker),
//_pModelCon(
//    (ModelConnection*)(
//        pCARETAKER->_pModelManager->connect(prm_model, this)
//    )
//),
//_pModel((Model*)_pModelCon->peek()),
//_pEffectCon(
//    (EffectConnection*)(
//        pCARETAKER->_pEffectManager->connect(prm_effect, this)
//    )
//),
//_pEffect((Effect*)_pEffectCon->peek()),
//_pAlphaFader(nullptr),
//_pColorist(nullptr)
//{
//    _obj_class |= Obj_GgafDx_FigureActor;
//    _class_name = "FigureActor";
//    _technique = NEW char[256];
//    FigureActor::changeEffectTechnique(prm_technique);
//    _temp_technique = NEW char[256];
//    _hash_temp_technique = 0;
//    _frame_of_behaving_temp_technique_end = 0;
//    _is_temp_technique = false;
//    _pNextRenderActor = nullptr;
//    //マテリアルをコピー
//    _paMaterial = NEW D3DMATERIAL9[_pModel->_num_materials];
//    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
//        _paMaterial[i] = _pModel->_paMaterial_default[i];
//    }
//    _alpha = 1.0f;
//    //最大距離頂点
//    _now_drawdepth = 0;
//    _specal_render_depth_index = -1;
//    _zenable = true;
//    _zwriteenable = true;
////    if (_pModelCon->chkFirstConnectionIs(this) ) {
////        _is_first_model_connector = true;
////    } else {
////        _is_first_model_connector = false;
////    }
////    if (_pEffectCon->chkFirstConnectionIs(this) ) {
////        _is_first_effect_connector = true;
////    } else {
////        _is_first_effect_connector = false;
////    }
//    _cull_enable = true;
//    _cull_mode_default = D3DCULL_CCW;
//    _cull_mode = _cull_mode_default;
//
//    _lstModelCon.push_back(_pModelCon);
//    _lstModel.push_back(_pModel);
//}

FigureActor::FigureActor(const char* prm_name,
                         const char* prm_model,
                         const char prm_model_type,
                         const char* prm_effect_id,
                         const char prm_effect_type,
                         const char* prm_technique,
                         CollisionChecker* prm_pChecker) :

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
    _obj_class |= Obj_GgafDx_FigureActor;
    _class_name = "FigureActor";
    _technique = NEW char[256];
    FigureActor::changeEffectTechnique(prm_technique);
    _temp_technique = NEW char[256];
    _hash_temp_technique = 0;
    _frame_of_behaving_temp_technique_end = 0;
    _is_temp_technique = false;
    _pNextRenderActor = nullptr;

    //マテリアルをコピー
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
//    if (_pModelCon->chkFirstConnectionIs(this) ) {
//        _is_first_model_connector = true;
//    } else {
//        _is_first_model_connector = false;
//    }
//    if (_pEffectCon->chkFirstConnectionIs(this) ) {
//        _is_first_effect_connector = true;
//    } else {
//        _is_first_effect_connector = false;
//    }
    _lstModelCon.push_back(_pModelCon);
    _lstModel.push_back(_pModel);

    _mapModel[std::string(prm_model)] = 0;
}

void FigureActor::addModel(const char* prm_model) {
    std::string model = std::string(prm_model);
#ifdef MY_DEBUG
    if (_mapModel.find(model) != _mapModel.end()) {
        throwCriticalException("FigureActor::addModel() アクター "<<getName()<<" に、既に追加済みモデルです。 model="<<model<<"。");
    }
#endif
   std::string model_id = std::string(1, _pModel->_model_type) + "," + std::string(prm_model);
   ModelConnection* pModelCon =  (ModelConnection*)pCARETAKER->_pModelManager->connect(model_id.c_str(), this);
   Model* pModel = ((Model*)pModelCon->peek());
   _lstModelCon.push_back(pModelCon);
   _lstModel.push_back(pModel);
   _mapModel[model] = (int)(_lstModel.size()-1);
}

void FigureActor::changeModelByIndex(int prm_model_index) {
#ifdef MY_DEBUG
    if (_lstModel.size() < prm_model_index+1) {
        throwCriticalException("要素数が不正。prm_model_index="<<prm_model_index);
    }
#endif
    _pModel = _lstModel.at(prm_model_index);
    _pModelCon = _lstModelCon.at(prm_model_index);
}

void FigureActor::changeModel(const char* prm_model) {
    std::string model = std::string(prm_model);
    if (_mapModel.find(model) == _mapModel.end()) {
        _TRACE_("FigureActor::changeModel() アクター "<<getName()<<" に、紐づいていないモデル model="<<model<<" のため追加します。");
        addModel(prm_model);
    }
    int model_index = _mapModel[model];
    changeModelByIndex(model_index);
}

void FigureActor::changeDefaultModel() {
    changeModelByIndex(0);
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
        throwCriticalException("name="<<getName()<<"を描画登録しようとしましたが、所属シーンが name="<<getName()<<"->getPlatformScene()["<<(pPlatformScene->getName())<<"]が、GgafDx::Scene に変換不可です。this="<<NODE_INFO<<" \n"
                "getPlatformScene()->_obj_class="<<pPlatformScene->_obj_class<< " Obj_GgafDx_Scene="<<Obj_GgafDx_Scene<<" \n"
                "(getPlatformScene()->_obj_class & Obj_GgafDx_Scene)="<<((pPlatformScene->_obj_class) & Obj_GgafDx_Scene) <<" ==?? Obj_GgafDx_Scene("<<Obj_GgafDx_Scene<<")");
    }
#endif
    if (_pModel->_is_init_model == false) {
        onCreateModel(); //モデル作成時の初期処理
        _pModel->_is_init_model = true;
    }
    _pNextRenderActor = nullptr;
    if (isActiveInTheTree()) {
        GgafCore::Caretaker::_num_active_actors++;
        if (!isOutOfView()) {
            if (_alpha > 0.0f &&  ((GgafDx::Scene*)pPlatformScene)->_scene_alpha > 0.0f) { //isActiveInTheTree() で判定すること
                //レンダリング対象として登録
                _now_drawdepth = pSpacetime->registerDrawActor(this);
#ifdef MY_DEBUG
                GgafCore::Caretaker::_num_draw_actors++;
#endif
            }
        }

    }

    //一時テクニック期間チェック
    if (_is_temp_technique) {
        if (_frame_of_behaving_temp_technique_end <= _frame_of_behaving) {
            //一時テクニック期間満了。元に戻す
            _hash_technique = _hash_temp_technique;
            strcpy(_technique, _temp_technique);
            _is_temp_technique = false;
            //これはダメ。配列領域がどこかにいくため。_temp_technique = "";
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
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paMaterial[0].Ambient.a = _alpha;
    _paMaterial[0].Diffuse.a = _alpha;
}

void FigureActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
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

void FigureActor::setSpecialRenderDepthNear(int prm_near_index) {
    // 0, 1, 2, 3, … 10 で指定
    //0(最前面の中でも最も手前) ～ 10(最前面の中でも最も背面)
    if (prm_near_index < 0) {
            throwCriticalException("setSpecialRenderDepthNear() 不正な深度指定です（0,1,2,3,4… で指定してください） prm_near_index="<<prm_near_index);
    } else if (prm_near_index > CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_NEAR-1) {
        setSpecialRenderDepthIndex(CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_NEAR-1);
    } else {
        setSpecialRenderDepthIndex(prm_near_index);
    }
}

void FigureActor::setSpecialRenderDepthFar(int prm_far_index) {
    //0,-1,-2,-3, … -10
    //0(最背面の中でも最も背面) ～ -10(最背面の中でも最も手前)
    if (prm_far_index > 0) {
        throwCriticalException("setSpecialRenderDepthFar() 不正な深度指定です（0,-1,-2,-3,-4… で指定してください） prm_far_index="<<prm_far_index);
    } else if (-prm_far_index > CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_FAR-1) {
        setSpecialRenderDepthIndex(CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_FAR + CONFIG::RENDER_DEPTH_INDEXS_NUM);
    } else {
        setSpecialRenderDepthIndex(ALL_RENDER_DEPTH_INDEXS_NUM-1 + prm_far_index);
    }
}

void FigureActor::resetSpecialRenderDepthIndex() {
    _specal_render_depth_index = -1;
}

void FigureActor::changeEffectTechnique(const char* prm_technique) {
    std::string technique = std::string(_pEffect->getName()) + "_" + std::string(prm_technique);
#ifdef MY_DEBUG
    if (technique.length() > 255) {
        throwCriticalException("テクニック名が長すぎます。prm_technique="<<prm_technique<<" technique="<<technique);
    }
#endif
    _hash_technique = UTIL::easy_hash(technique.c_str());
    strcpy(_technique, prm_technique);
}

void FigureActor::changeEffectTechniqueMoment(const char* prm_technique, frame prm_frame) {
    if (_is_temp_technique == false) { //すでに一時テクニック使用時は無視
        //元々のテクニックを退避
        _hash_temp_technique = _hash_technique;
        strcpy(_temp_technique, _technique);
        //テクニック変更
        if (prm_frame == MAX_FRAME) {
            _frame_of_behaving_temp_technique_end = MAX_FRAME;
        } else {
            _frame_of_behaving_temp_technique_end = _frame_of_behaving + prm_frame; //変更満期フレーム
        }
        changeEffectTechnique(prm_technique);
        _is_temp_technique = true;
    }
}

void FigureActor::effectFlush(frame prm_frame) {
    changeEffectTechniqueMoment("Flush", prm_frame); //フラッシュ
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
        const dxcoord bound = getModel()->_bounding_sphere_radius * _rate_of_bounding_sphere_radius*2.0f;//掛ける2は境界球を大きくして、画面境界のチラツキを抑える
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_infront < bound) {
                            if (_dest_from_vppln_back < bound) {
                                //Viewport範囲内
                                _offscreen_kind = 0;
                            } else {
                                //奥平面より奥で範囲外
                                _offscreen_kind = 6;
                            }
                        } else {
                            //手前平面より手前で範囲外
                            _offscreen_kind = 5;
                        }
                    } else {
                        //右平面より右で範囲外
                        _offscreen_kind = 4;
                    }
                } else {
                    //左平面より左で範囲外
                    _offscreen_kind = 3;
                }
            } else {
                //下平面より下で範囲外
                _offscreen_kind = 2;
            }
        } else {
            //上平面より上で範囲外
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
    for (int i = 0; i < _lstModelCon.size(); i++) {
        ModelConnection* pModelCon = _lstModelCon.at(i);
        pModelCon->close();
    }
    _pModelCon = nullptr;
}
