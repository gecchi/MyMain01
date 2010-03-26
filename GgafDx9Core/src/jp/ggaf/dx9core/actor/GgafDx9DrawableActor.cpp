#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

unsigned int GgafDx9DrawableActor::_hash_technique_last_draw = 0;

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
    _hash_technique = GgafUtil::easy_hash(prm_technique);
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _technique_temp = NEW char[51];
    _hash_technique = 0;
    _frame_temp_technique = 0;
    _is_temp_technique = false;

    _pNext_TheSameDrawDepthLevel = NULL;
    //モデル取得
    _pGgafDx9ModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->connect(prm_model);
    _pGgafDx9Model = (GgafDx9Model*)_pGgafDx9ModelCon->view();
    //エフェクト取得
    _pGgafDx9EffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->connect(prm_effect);
    _pGgafDx9Effect = (GgafDx9Effect*)_pGgafDx9EffectCon->view();
    //マテリアルをコピー
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pGgafDx9Model->_dwNumMaterials];
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pGgafDx9Model->_paD3DMaterial9_default[i];
    }
    _fAlpha = 1.0f;
    //最大距離頂点
    _fBoundingSphereRadius = _pGgafDx9Model->_fBoundingSphereRadius;

    _papSeCon = NEW GgafDx9SeConnection*[10];
    _papSe    = NEW GgafDx9Se*[10];
    for (int i = 0; i < 10; i++) {
        _papSeCon[i] = NULL;
        _papSe[i] = NULL;
    }

    _pSeCon = NULL;
    _pSe = NULL;
    _now_drawdepth = 0;

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
    _hash_technique = GgafUtil::easy_hash(prm_technique);
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _technique_temp = NEW char[51];
    _hash_technique = 0;
    _frame_temp_technique = 0;
    _is_temp_technique = false;

    char* model_name = NEW char[51];
    model_name[0] = '\0';
    strcat(model_name, prm_model_type);
    strcat(model_name, "/");
    strcat(model_name, prm_model_id);
    // prm_model_id   = "Ceres"
    // prm_model_type = "X"
    // の場合、model_name として
    // model_name     = "X/Ceres"
    // という文字列を作成。

    char* effelct_name = NEW char[51];
    effelct_name[0] = '\0';
    strcat(effelct_name, prm_effect_type);
    strcat(effelct_name, "/");
    strcat(effelct_name, prm_effect_id);
    // prm_effect_id   = "DefaultMeshEffect"
    // prm_effect_type = "X"
    // の場合、effelct_name として
    // effelct_name     = "X/DefaultMeshEffect"
    // という文字列を作成。

    _pNext_TheSameDrawDepthLevel = NULL;
    //モデル取得
    _pGgafDx9ModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->connect(model_name);
    _pGgafDx9Model = (GgafDx9Model*)_pGgafDx9ModelCon->view();
    //エフェクト取得
    _pGgafDx9EffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->connect(effelct_name);
    _pGgafDx9Effect = (GgafDx9Effect*)_pGgafDx9EffectCon->view();
    //マテリアルをコピー
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pGgafDx9Model->_dwNumMaterials];
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pGgafDx9Model->_paD3DMaterial9_default[i];
    }
    _fAlpha = 1.0f;

    //最大距離頂点
    _fBoundingSphereRadius = _pGgafDx9Model->_fBoundingSphereRadius;

    DELETEARR_IMPOSSIBLE_NULL(model_name);
    DELETEARR_IMPOSSIBLE_NULL(effelct_name);


    _papSeCon = NEW GgafDx9SeConnection*[10];
    _papSe    = NEW GgafDx9Se*[10];
    for (int i = 0; i < 10; i++) {
        _papSeCon[i] = NULL;
        _papSe[i] = NULL;
    }

    _pSeCon = NULL;
    _pSe = NULL;
    _now_drawdepth = 0;
}



void GgafDx9DrawableActor::processPreDraw() {
    _pNext_TheSameDrawDepthLevel = NULL;
    //TODO:要検証
    if (_is_active_flg && _can_live_flg) {
        if (_isTransformed) {
            _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(
                                (int)(_z * MAX_DRAW_DEPTH_LEVEL),
                                this
                             );
        } else {
            if (isOffscreen()) {
                //描画しないので登録なし
            } else {

                //初期カメラ位置 _cameraZ_org = -57.1259、表示範囲奥行きは、_zf = -_cameraZ_org*10.0; とした場合の例。
                //「参照：GgafDx9Camera::GgafDx9Camera()」
                //表示範囲(奥行き:_zf)までの距離は初期カメラの引き位置距離び10倍で約 571.0 になる
                //さて MAX_DRAW_DEPTH_LEVEL は(現在1000)と対応させるか
                //本ライブラリはDIRECTX座標の1は画面上で約10px相当という計算を行っている。よって
                //次の文は10px間隔相当の奥からの段階レンダリングの設定となる
                //
                //  GgafDx9Universe::setDrawDepthLevel(-1.0*_fDist_VpPlnFront, this);
                //
                //としたばあい、571 段階の深度判定となる。
                //(※_fDist_VpPlnFrontは視錐台手前面からオブジェクトまでの距離の負数)
                //また、
                //
                //  GgafDx9Universe::setDrawDepthLevel(-1.0*_fDist_VpPlnFront*10.0, this);
                //
                //これは1px間隔相当で約 5710 段階となるが、MAX_DRAW_DEPTH_LEVELが1000ならば
                //4710～5710段階目は全て最深のとして同一深度で扱われてしまう。
                //
                //さてここで、はるか遠いオブジェクト達を細かい段階描画しても報われないと思ったため、
                //カメラに近いほど精密に、遠いほどアバウトに段階レンダリングしたいと考えた。
                //
                //  <o   |-+-+-+-+-+-+-+-+-+-+-+-+-+--+---+----+-----+------+------+-------+-----
                //              ------> 奥         ^            ------> 奥                        ^
                // カメラ                   アバウト間隔開始深度                                 最深部
                //
                //上図のようなイメージで設定することとする
                int dep = (int)(-_fDist_VpPlnFront);
                int roughly_dep_point1 = (int)(-(pCAM->_cameraZ_org) * 4.0); //(228)
                int roughly_dep_point2 = (int)(-(pCAM->_cameraZ_org) * 8.0); //(456)
                if (dep <= roughly_dep_point1) {
                    _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(dep, this); //intに丸め込んでる。つまりDirectXの距離1が深さ1。よって10px間隔
                } else if (dep <= roughly_dep_point2) {
                    _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(roughly_dep_point1 + ((dep - roughly_dep_point1) / 3), this);  //3で割る。つまりDirectXの距離2が深さ1。よって20px間隔
                } else {
                    //roughly_dep_point1+((roughly_dep_point2-roughly_dep_point1)/2)=342
                    _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(roughly_dep_point1+((roughly_dep_point2-roughly_dep_point1)/10) + ((dep - roughly_dep_point2) / 6), this);
                }
            }
        }
    }

    //一時テクニック期間チェック
    if (_is_temp_technique) {
        if (_frame_temp_technique <= _frame_of_behaving) {
            //一時テクニック期間満了。元に戻す
            _hash_technique = _hash_technique_temp;
            strcpy(_technique, _technique_temp);
            _is_temp_technique = false;
            //これはダメ。配列領域がどこかにいくため。_technique_temp = "";
            _hash_technique_temp = 0;
        }
    }

}


#ifdef MY_DEBUG

void GgafDx9DrawableActor::processAfterDraw() {
    //当たり判定領域表示
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        drawHitArea();
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void GgafDx9DrawableActor::processAfterDraw() {}

#endif



void GgafDx9DrawableActor::setMaterialColor(float r, float g, float b) {
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.r = r;
        _paD3DMaterial9[i].Diffuse.r = r;
        _paD3DMaterial9[i].Ambient.g = g;
        _paD3DMaterial9[i].Diffuse.g = g;
        _paD3DMaterial9[i].Ambient.b = b;
        _paD3DMaterial9[i].Diffuse.b = b;
    }
}

void GgafDx9DrawableActor::resetMaterialColor() {
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.r = _pGgafDx9Model->_paD3DMaterial9_default[i].Ambient.r;
        _paD3DMaterial9[i].Diffuse.r = _pGgafDx9Model->_paD3DMaterial9_default[i].Diffuse.r;
        _paD3DMaterial9[i].Ambient.g = _pGgafDx9Model->_paD3DMaterial9_default[i].Ambient.g;
        _paD3DMaterial9[i].Diffuse.g = _pGgafDx9Model->_paD3DMaterial9_default[i].Diffuse.g;
        _paD3DMaterial9[i].Ambient.b = _pGgafDx9Model->_paD3DMaterial9_default[i].Ambient.b;
        _paD3DMaterial9[i].Diffuse.b = _pGgafDx9Model->_paD3DMaterial9_default[i].Diffuse.b;
    }
}

void GgafDx9DrawableActor::prepareSe(int prm_id, const char* prm_se_name, int prm_cannel) {
    char idstr[129];
    sprintf(idstr, "%d/%s", prm_cannel, prm_se_name);
    _papSeCon[prm_id] = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->connect(idstr);
    _papSe[prm_id] = _papSeCon[prm_id]->view();
}

void GgafDx9DrawableActor::playSe(int prm_id) {
    _papSe[prm_id]->play();
}


void GgafDx9DrawableActor::prepareSe1(const char* prm_se_name, int prm_cannel) {
    char idstr[129];
    sprintf(idstr, "%d/%s", prm_cannel, prm_se_name);
    _pSeCon = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->connect(idstr);
    _pSe = _pSeCon->view();
}

void GgafDx9DrawableActor::playSe1() {
    _pSe->play();
}

void GgafDx9DrawableActor::prepareSe2(const char* prm_se_name, int prm_cannel) {
    char idstr[129];
    sprintf(idstr, "%d/%s", prm_cannel, prm_se_name);
    _pSeCon2 = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->connect(idstr);
    _pSe2 = _pSeCon2->view();
}

void GgafDx9DrawableActor::playSe2() {
    _pSe2->play();
}

GgafDx9DrawableActor::~GgafDx9DrawableActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    DELETEARR_IMPOSSIBLE_NULL(_technique_temp);
    _pGgafDx9ModelCon->close();
    _pGgafDx9EffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
    if (_pSeCon) {
        _pSeCon->close();
    }
    for (int i = 0; i < 10; i++) {
        if (_papSeCon[i]) {
            _papSeCon[i]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSeCon);
    DELETEARR_IMPOSSIBLE_NULL(_papSe);
}
