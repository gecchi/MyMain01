#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectConnection.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/scene/GgafDxScene.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxAlphaCurtain.h"
#include "jp/ggaf/core/util/GgafRgb.h"

#include "jp/ggaf/dxcore/GgafDxProperties.h"
using namespace GgafCore;
using namespace GgafDxCore;

hashval GgafDxFigureActor::_hash_technique_last_draw = 0;

GgafDxFigureActor::GgafDxFigureActor(const char* prm_name,
                                     const char* prm_model,
                                     const char* prm_effect,
                                     const char* prm_technique,
                                     GgafStatus* prm_pStat,
                                     GgafDxChecker* prm_pChecker) :
  GgafDxGeometricActor(prm_name, prm_pStat, prm_pChecker),
_pModelCon((GgafDxModelConnection*)GgafDxGod::_pModelManager->connect(
                  std::string(prm_model).c_str(),
                  this)),
_pModel((GgafDxModel*)_pModelCon->peek()),
_pEffectCon((GgafDxEffectConnection*)GgafDxGod::_pEffectManager->connect(
                  std::string(prm_effect).c_str(),
                  this)),
_pEffect((GgafDxEffect*)_pEffectCon->peek()) {

    _obj_class |= Obj_GgafDxFigureActor;
    _class_name = "GgafDxFigureActor";

    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _hash_technique = 0;

    _temp_technique = NEW char[51];
    _hash_temp_technique = 0;

    _frame_of_behaving_temp_technique_end = 0;
    _is_temp_technique = false;
    _pNextActor_in_render_depth = nullptr;
//    //モデル取得connectModelManager
//    _pModelCon = (GgafDxModelConnection*)GgafDxGod::_pModelManager->connect(prm_model, this);
//    _pModel = (GgafDxModel*)_pModelCon->peek();
//    //エフェクト取得
//    _pEffectCon = (GgafDxEffectConnection*)GgafDxGod::_pEffectManager->connect(prm_effect, this);
//    _pEffect = (GgafDxEffect*)_pEffectCon->peek();
    //マテリアルをコピー
    _paMaterial = NEW D3DMATERIAL9[_pModel->_num_materials];
    for (DWORD i = 0; i < _pModel->_num_materials; i++){
        _paMaterial[i] = _pModel->_paMaterial_default[i];
    }
    _alpha = 1.0f;
    //最大距離頂点
    _now_drawdepth = 0;
    _specal_render_depth_index = -1;
    _zenable = true;
    _zwriteenable = true;
    _hash_technique = UTIL::easy_hash(prm_technique) + UTIL::easy_hash(_pModel->getName());
}

GgafDxFigureActor::GgafDxFigureActor(const char* prm_name,
                                     const char* prm_model_id,
                                     const char* prm_model_type,
                                     const char* prm_effect_id,
                                     const char* prm_effect_type,
                                     const char* prm_technique,
                                     GgafStatus* prm_pStat,
                                     GgafDxChecker* prm_pChecker) :
  GgafDxGeometricActor(prm_name, prm_pStat, prm_pChecker),
_pModelCon((GgafDxModelConnection*)GgafDxGod::_pModelManager->connect(
                    (std::string(prm_model_type) + std::string("/") + std::string(prm_model_id)).c_str(),
                    this)),
_pModel((GgafDxModel*)_pModelCon->peek()),
_pEffectCon((GgafDxEffectConnection*)GgafDxGod::_pEffectManager->connect(
                    (std::string(prm_effect_type) + std::string("/") + std::string(prm_effect_id)).c_str(),
                    this)),
_pEffect((GgafDxEffect*)_pEffectCon->peek())
          {

    _class_name = "GgafDxFigureActor";

    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _hash_technique = 0;

    _temp_technique = NEW char[51];
    _hash_temp_technique = 0;

    _frame_of_behaving_temp_technique_end = 0;
    _is_temp_technique = false;

//    char* model_name = NEW char[51];
//    model_name[0] = '\0';
//    strcat(model_name, prm_model_type);
//    strcat(model_name, "/");
//    strcat(model_name, prm_model_id);
//    // prm_model_id   = "Eres"
//    // prm_model_type = "X"
//    // の場合、model_name として
//    // model_name     = "X/Eres"
//    // という文字列を作成。
//
//    char* effelct_name = NEW char[51];
//    effelct_name[0] = '\0';
//    strcat(effelct_name, prm_effect_type);
//    strcat(effelct_name, "/");
//    strcat(effelct_name, prm_effect_id);
//    // prm_effect_id   = "DefaultMeshEffect"
//    // prm_effect_type = "X"
//    // の場合、effelct_name として
//    // effelct_name     = "X/DefaultMeshEffect"
//    // という文字列を作成。

    _pNextActor_in_render_depth = nullptr;

    //マテリアルをコピー
    _paMaterial = NEW D3DMATERIAL9[_pModel->_num_materials];
    for (DWORD i = 0; i < _pModel->_num_materials; i++){
        _paMaterial[i] = _pModel->_paMaterial_default[i];
    }
    _alpha = 1.0f;

//    GGAF_DELETEARR(model_name);
//    GGAF_DELETEARR(effelct_name);

    _now_drawdepth = 0;
    _specal_render_depth_index = -1;
    _zenable = true;
    _zwriteenable = true;
    _hash_technique = UTIL::easy_hash(prm_technique) + UTIL::easy_hash(_pModel->getName());
}

void GgafDxFigureActor::processPreDraw() {
    GgafDxSpacetime* pSpacetime = P_GOD->getSpacetime();
#ifdef MY_DEBUG
    if (getPlatformScene()->instanceOf(Obj_GgafDxScene)) {
        //OK
    } else {
        throwGgafCriticalException("GgafDxFigureActor::processPreDraw() name="<<getName()<<"を描画登録しようとしましたが、所属シーンが name="<<getName()<<"->getPlatformScene()["<<(getPlatformScene()->getName())<<"]が、GgafDxScene に変換不可です。this="<<NODE_INFO<<" \n"<<
                "getPlatformScene()->_obj_class="<<getPlatformScene()->_obj_class<< " Obj_GgafDxScene="<<Obj_GgafDxScene<<" \n"<<
                "(getPlatformScene()->_obj_class & Obj_GgafDxScene)="<<((getPlatformScene()->_obj_class) & Obj_GgafDxScene) <<" ==?? Obj_GgafDxScene("<<Obj_GgafDxScene<<")");
    }
#endif
    if (_pModel->_is_init_model == false) {
        onCreateModel(); //モデル作成時の初期処理
        _pModel->_is_init_model = true;
    }
    _pNextActor_in_render_depth = nullptr;
    if (_alpha > 0.0f && isActiveInTheTree() && ((GgafDxScene*)getPlatformScene())->_master_alpha > 0.0f) { //isActiveInTheTree() で判定すると、
        if (_is_2D) {
            _now_drawdepth = pSpacetime->registerFigureActor2D(this);
        } else {
            _now_drawdepth = pSpacetime->registerFigureActor3D(this);
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


void GgafDxFigureActor::processAfterDraw() {
#ifdef MY_DEBUG
    //当たり判定領域表示
    if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        drawHitArea();
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDxGod::_d3dfillmode);
    }
#endif
}

void GgafDxFigureActor::setMaterialColor(float r, float g, float b) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.r = r;
        _paMaterial[i].Diffuse.r = r;
        _paMaterial[i].Ambient.g = g;
        _paMaterial[i].Diffuse.g = g;
        _paMaterial[i].Ambient.b = b;
        _paMaterial[i].Diffuse.b = b;
    }
}

void GgafDxFigureActor::setMaterialRed(float r) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.r = r;
        _paMaterial[i].Diffuse.r = r;
    }
}
void GgafDxFigureActor::setMaterialGreen(float g) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.g = g;
        _paMaterial[i].Diffuse.g = g;
    }
}
void GgafDxFigureActor::setMaterialBlue(float b) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.b = b;
        _paMaterial[i].Diffuse.b = b;
    }
}

float GgafDxFigureActor::getMaterialRed() {
    return _paMaterial[0].Diffuse.r;
}
float GgafDxFigureActor::getMaterialGreen() {
    return _paMaterial[0].Diffuse.g;
}
float GgafDxFigureActor::getMaterialBlue() {
    return _paMaterial[0].Diffuse.b;
}

void GgafDxFigureActor::setMaterialColor(const GgafCore::GgafRgb* prm_rgb) {
    setMaterialColor(prm_rgb->_r, prm_rgb->_g, prm_rgb->_b);
}

void GgafDxFigureActor::resetMaterialColor() {
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

void GgafDxFigureActor::setSpecialRenderDepthIndex(int prm_drawdepth) {
    if (prm_drawdepth < 0) {
        _specal_render_depth_index = 0;
    } else if (prm_drawdepth > ALL_RENDER_DEPTH_INDEXS_NUM-1) {
        _specal_render_depth_index = ALL_RENDER_DEPTH_INDEXS_NUM-1;
    } else {
        _specal_render_depth_index = prm_drawdepth;
    }
}
void GgafDxFigureActor::resetSpecialRenderDepthIndex() {
    _specal_render_depth_index = -1;
}
void GgafDxFigureActor::changeEffectTechnique(const char* prm_technique) {
    _hash_technique = UTIL::easy_hash(prm_technique) + UTIL::easy_hash(_pModel->getName());
    strcpy(_technique, prm_technique);
}

void GgafDxFigureActor::changeEffectTechniqueInterim(const char* prm_technique, frame prm_frame) {
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
        _hash_technique = UTIL::easy_hash(prm_technique) + UTIL::easy_hash(_pModel->getName());
        strcpy(_technique, prm_technique);
        _is_temp_technique = true;
    }
}

void GgafDxFigureActor::effectFlush(frame prm_frame) {
    changeEffectTechniqueInterim("Flush", prm_frame); //フラッシュ
}

void GgafDxFigureActor::effectBlendOne(frame prm_frame) {
    changeEffectTechniqueInterim("DestBlendOne", prm_frame);
}

void GgafDxFigureActor::effectDefault() {
    if (_is_temp_technique) {
        _hash_technique = _hash_temp_technique;
        strcpy(_technique, _temp_technique);
        _is_temp_technique = false;
        _hash_temp_technique = 0;
    }
}
int GgafDxFigureActor::isOutOfView() {
    if (_offscreen_kind == -1) {
        const dxcoord bound = getModel()->_bounding_sphere_radius * _rate_of_bounding_sphere_radius*2.0f;//掛ける2は境界球を大きくして、画面境界のチラツキを抑える
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_front < bound) {
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
GgafDxFigureActor::~GgafDxFigureActor() {
    GGAF_DELETEARR(_technique);
    GGAF_DELETEARR(_temp_technique);
    GGAF_DELETEARR(_paMaterial);
    _pEffectCon->close();
    _pModelCon->close();
}
