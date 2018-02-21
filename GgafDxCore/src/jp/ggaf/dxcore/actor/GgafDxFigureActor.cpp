#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/core/util/GgafRgb.h"
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
#include "jp/ggaf/dxcore/GgafDxConfig.h"

using namespace GgafCore;
using namespace GgafDxCore;

hashval GgafDxFigureActor::_hash_technique_last_draw = 0;

GgafDxFigureActor::GgafDxFigureActor(const char* prm_name,
                                     const char* prm_model,
                                     const char* prm_effect,
                                     const char* prm_technique,
                                     GgafStatus* prm_pStat,
                                     GgafDxChecker* prm_pChecker) :

                                         GgafDxGeometricActor(prm_name,
                                                              prm_pStat,
                                                              prm_pChecker),
_pModelCon(
    (GgafDxModelConnection*)(
        GgafDxGod::_pModelManager->connect(
            std::string(prm_model).c_str(), this
        )
    )
),
_pModel((GgafDxModel*)_pModelCon->peek()),
_pEffectCon(
    (GgafDxEffectConnection*)(
        GgafDxGod::_pEffectManager->connect(
            std::string(prm_effect).c_str(), this
        )
    )
),
_pEffect((GgafDxEffect*)_pEffectCon->peek()),
_pAlphaFader(nullptr)
{
    _obj_class |= Obj_GgafDxFigureActor;
    _class_name = "GgafDxFigureActor";
    _technique = NEW char[256];
    GgafDxFigureActor::changeEffectTechnique(prm_technique);
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
    //最大距離頂点
    _now_drawdepth = 0;
    _specal_render_depth_index = -1;
    _zenable = true;
    _zwriteenable = true;
}

GgafDxFigureActor::GgafDxFigureActor(const char* prm_name,
                                     const char* prm_model_id,
                                     const char* prm_model_type,
                                     const char* prm_effect_id,
                                     const char* prm_effect_type,
                                     const char* prm_technique,
                                     GgafStatus* prm_pStat,
                                     GgafDxChecker* prm_pChecker) :

                                         GgafDxGeometricActor(prm_name,
                                                              prm_pStat,
                                                              prm_pChecker),
_pModelCon(
    (GgafDxModelConnection*)(
        GgafDxGod::_pModelManager->connect(
            (std::string(prm_model_type) + "/" + std::string(prm_model_id)).c_str(), this
        )
    )
),
_pModel((GgafDxModel*)_pModelCon->peek()),
_pEffectCon(
    (GgafDxEffectConnection*)(
        GgafDxGod::_pEffectManager->connect(
            (std::string(prm_effect_type) + "/" + std::string(prm_effect_id)).c_str(), this
        )
    )
),
_pEffect((GgafDxEffect*)_pEffectCon->peek()),
_pAlphaFader(nullptr)
{
    _class_name = "GgafDxFigureActor";

    _technique = NEW char[256];
    GgafDxFigureActor::changeEffectTechnique(prm_technique);
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
    _now_drawdepth = 0;
    _specal_render_depth_index = -1;
    _zenable = true;
    _zwriteenable = true;
}

GgafDxAlphaFader* GgafDxFigureActor::getAlphaFader() {
    return _pAlphaFader ? _pAlphaFader : _pAlphaFader = NEW GgafDxAlphaFader(this);
}

void GgafDxFigureActor::processPreDraw() {
    GgafDxSpacetime* pSpacetime = pGOD->getSpacetime();
    GgafScene* pPlatformScene = getMySceneMediator()->getPlatformScene();
#ifdef MY_DEBUG
    if (pPlatformScene->instanceOf(Obj_GgafDxScene)) {
        //OK
    } else {
        throwGgafCriticalException("name="<<getName()<<"を描画登録しようとしましたが、所属シーンが name="<<getName()<<"->getPlatformScene()["<<(pPlatformScene->getName())<<"]が、GgafDxScene に変換不可です。this="<<NODE_INFO<<" \n"
                "getPlatformScene()->_obj_class="<<pPlatformScene->_obj_class<< " Obj_GgafDxScene="<<Obj_GgafDxScene<<" \n"
                "(getPlatformScene()->_obj_class & Obj_GgafDxScene)="<<((pPlatformScene->_obj_class) & Obj_GgafDxScene) <<" ==?? Obj_GgafDxScene("<<Obj_GgafDxScene<<")");
    }
#endif
    if (_pModel->_is_init_model == false) {
        onCreateModel(); //モデル作成時の初期処理
        _pModel->_is_init_model = true;
    }
    _pNextRenderActor = nullptr;
    if (isActiveInTheTree()) {
        GgafGod::_num_active_actor++;
        if (_alpha > 0.0f &&  ((GgafDxScene*)pPlatformScene)->_scene_alpha > 0.0f) { //isActiveInTheTree() で判定すると、
            if (_is_2D) {
                _now_drawdepth = pSpacetime->registerFigureActor2D(this);
            } else {
                _now_drawdepth = pSpacetime->registerFigureActor3D(this);
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


void GgafDxFigureActor::processAfterDraw() {
#ifdef MY_DEBUG
//    //各所属シーンのαカーテンを設定する。
//    getEffect()->setAlphaMaster(((GgafDxScene*)getPlatformScene())->_scene_alpha);
//    _TRACE_("this="<<getName()<<" PlathoneScene="<<((GgafDxScene*)getPlatformScene())->getName()<<" _scene_alpha="<<((GgafDxScene*)getPlatformScene())->_scene_alpha);
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
void GgafDxFigureActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paMaterial[0].Ambient.a = _alpha;
    _paMaterial[0].Diffuse.a = _alpha;
}

void GgafDxFigureActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paMaterial[0].Ambient.a = _alpha;
    _paMaterial[0].Diffuse.a = _alpha;
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
    std::string technique = std::string(_pEffect->getName()) + "_" + std::string(prm_technique);
#ifdef MY_DEBUG
    if (technique.length() > 255) {
        throwGgafCriticalException("テクニック名が長すぎます。prm_technique="<<prm_technique<<" technique="<<technique);
    }
#endif
    _hash_technique = UTIL::easy_hash(technique.c_str());
    strcpy(_technique, prm_technique);
}

void GgafDxFigureActor::changeEffectTechniqueMoment(const char* prm_technique, frame prm_frame) {
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

void GgafDxFigureActor::effectFlush(frame prm_frame) {
    changeEffectTechniqueMoment("Flush", prm_frame); //フラッシュ
}

void GgafDxFigureActor::effectBlendOne(frame prm_frame) {
    changeEffectTechniqueMoment("DestBlendOne", prm_frame);
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

GgafDxFigureActor::~GgafDxFigureActor() {
    GGAF_DELETEARR(_technique);
    GGAF_DELETEARR(_temp_technique);
    GGAF_DELETEARR(_paMaterial);
    GGAF_DELETE_NULLABLE(_pAlphaFader);
    _pEffectCon->close();
    _pModelCon->close();
}
