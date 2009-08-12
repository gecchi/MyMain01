#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
GgafDx9DrawableActor::GgafDx9DrawableActor(const char* prm_name,
                                           const char* prm_model,
                                           const char* prm_effect,
                                           const char* prm_technique,
                                           GgafDx9Checker* prm_pChecker) :
  GgafDx9GeometricActor(prm_name, prm_pChecker) {

//_TRACE_("GgafDx9DrawableActor::GgafDx9DrawableActor(");
//_TRACE_("    prm_name="<<prm_name);
//_TRACE_("    prm_model="<<prm_model);
//_TRACE_("    prm_effect="<<prm_effect);
//_TRACE_("    prm_technique="<<prm_technique);
//_TRACE_(")");

    _class_name = "GgafDx9DrawableActor";
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);

    _pNext_TheSameDrawDepthLevel = NULL;
    //モデル取得
    _pGgafDx9ModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pGgafDx9Model = (GgafDx9Model*)_pGgafDx9ModelCon->view();
    //エフェクト取得
    _pGgafDx9EffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pGgafDx9Effect = (GgafDx9Effect*)_pGgafDx9EffectCon->view();
    //マテリアルをコピー
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pGgafDx9Model->_dwNumMaterials];
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pGgafDx9Model->_paD3DMaterial9_default[i];
    }
    _fAlpha = 1.0f;
    //最大距離頂点
    _max_radius = _pGgafDx9Model->_max_radius;

}


GgafDx9DrawableActor::GgafDx9DrawableActor(const char* prm_name,
                                           const char* prm_model_id,
                                           const char* prm_model_type,
                                           const char* prm_effect_id,
                                           const char* prm_effect_type,
                                           const char* prm_technique,
                                           GgafDx9Checker* prm_pChecker) :
  GgafDx9GeometricActor(prm_name, prm_pChecker) {

//_TRACE_("GgafDx9DrawableActor::GgafDx9DrawableActor(");
//_TRACE_("    prm_name="<<prm_name);
//_TRACE_("    prm_model_id="<<prm_model_id);
//_TRACE_("    prm_model_type="<<prm_model_type);
//_TRACE_("    prm_effect_id="<<prm_effect_id);
//_TRACE_("    prm_effect_type="<<prm_effect_type);
//_TRACE_("    prm_technique="<<prm_technique);
//_TRACE_(")");

    _class_name = "GgafDx9DrawableActor";
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);

    char* model_name = NEW char[51];
    model_name[0] = '\0';
    strcat(model_name, prm_model_type);
    strcat(model_name, "/");
    strcat(model_name, prm_model_id);
    char* effelct_name = NEW char[51];
    effelct_name[0] = '\0';
    strcat(effelct_name, prm_effect_type);
    strcat(effelct_name, "/");
    strcat(effelct_name, prm_effect_id);
    // prm_model_id   = "Celes"
    // prm_model_type = "X"
    // の場合、model_name として
    // model_name     = "X/Celes"
    // という文字列を作成。

    _pNext_TheSameDrawDepthLevel = NULL;
    //モデル取得
    _pGgafDx9ModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(model_name);
    _pGgafDx9Model = (GgafDx9Model*)_pGgafDx9ModelCon->view();
    //エフェクト取得
    _pGgafDx9EffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(effelct_name);
    _pGgafDx9Effect = (GgafDx9Effect*)_pGgafDx9EffectCon->view();
    //マテリアルをコピー
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pGgafDx9Model->_dwNumMaterials];
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pGgafDx9Model->_paD3DMaterial9_default[i];
    }
    _fAlpha = 1.0f;


    DELETEARR_IMPOSSIBLE_NULL(model_name);
    DELETEARR_IMPOSSIBLE_NULL(effelct_name);

}



void GgafDx9DrawableActor::processDrawPrior() {
    _pNext_TheSameDrawDepthLevel = NULL;
    //TODO:要検証
    if (_is_active_flg && _can_live_flg) {
        if (getAlpha() < 1.0) {
            if (_isTransformed) {
                GgafDx9Universe::setDrawDepthLevel(
                                    (int)(_z * MAX_DRAW_DEPTH_LEVEL),
                                    this
                                 );
            } else {

                //GgafDx9Universe::setDrawDepthLevel(_fDistance_plnFront*-1*PX_UNIT, this);
                //↑これで1px間隔段階レンダリング
                //GgafDx9Universe::setDrawDepthLevel(_fDistance_plnFront*-1, this);
                //↑ということはこれで10px間隔段階レンダリング
                //今は20px間隔段階レンダリング
                GgafDx9Universe::setDrawDepthLevel((_fDistance_plnFront)/-2, this);
            }
        } else {
            //不透明の場合は初めに描画するように設定。
            //レンダリング時最遠から描画するので、深度レベルはMAX
            GgafDx9Universe::setDrawDepthMaxLevel(this);
        }
    }
}




GgafDx9DrawableActor::~GgafDx9DrawableActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pGgafDx9ModelCon->close();
    _pGgafDx9EffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
