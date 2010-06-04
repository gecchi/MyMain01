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
    _actor_class |= Obj_GgafDx9DrawableActor;
    _class_name = "GgafDx9DrawableActor";

    //_TRACE_("GgafDx9DrawableActor::GgafDx9DrawableActor(");
    //_TRACE_("    prm_name="<<prm_name);
    //_TRACE_("    prm_model="<<prm_model);
    //_TRACE_("    prm_effect="<<prm_effect);
    //_TRACE_("    prm_technique="<<prm_technique);
    //_TRACE_(")");

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
                //＜メモ＞
                //初期カメラ位置 _cameraZ_org = -47.6701、表示範囲奥行きは、_zf = -_cameraZ_org*20.0; とした場合の例。
                //「参照：GgafDx9Camera::GgafDx9Camera()」
                //表示範囲(奥行き:_zf)の距離は初期カメラの引き位置距離の10倍で約 571.0 になる（これが _zf = -_cameraZ_org*10.0 の意味）
                //さて MAX_DRAW_DEPTH_LEVEL (現在1000)とどのように対応させるか
                //本ライブラリはDIRECTX座標の1は原点付近ので画面上約10px相当という計算を行っている。よって
                //次の文は約10px間隔相当の奥からの段階レンダリングの設定となる
                //
                //  GgafDx9Universe::setDrawDepthLevel(-1.0*_fDist_VpPlnFront, this);
                //   (※_fDist_VpPlnFrontは視錐台手前面からオブジェクトまでの距離の負数)
                //
                //これは、571 段階の深度判定となる。
                //また、
                //
                //  GgafDx9Universe::setDrawDepthLevel(-1.0*_fDist_VpPlnFront*10.0, this);
                //
                //これは1px間隔相当で約 5710 段階となるが、MAX_DRAW_DEPTH_LEVELが1000ならば
                //4710～5710段階目は全て最深のとして同一深度で扱われてしまう。
                //MAX_DRAW_DEPTH_LEVELを増やせば問題ないが、600段階ぐらいが研究の末パフォーマンス的にちょうどよさげである。
                //なんとか600段階ぐらいで対応段階レンダリングしようと考えた。
                //
                //はるか遠いオブジェクト達を細かい段階描画してもあまり報われないと考えた。
                //カメラに近いほど精密に、遠いほどアバウトに段階レンダリングしたいと考えた。
                //
                //  <o   |-+-+-+-+-+-+-+-+-+-+-+-+-+--+---+----+-----+------+------+-------+-----
                //              ------> 奥         ^            ------> 奥                        ^
                // カメラ                   アバウト間隔開始深度                                 最深部
                //
                //上図のようなイメージ段階的に荒くしていこう！
                //【参考】
                //   7975036 <DEBUG> GgafDx9Camera::GgafDx9Camera 画面アスペクト：1.33333
                //   7975036 <DEBUG> GgafDx9Camera::GgafDx9Camera FovX=1.39626 FovY=1.12341
                //   7975036 <DEBUG> GgafDx9Camera::GgafDx9Camera カメラの位置(0,0,-47.6701)
                //   7975036 <DEBUG> GgafDx9Camera::GgafDx9Camera 範囲 [0.01 ~ 1001.07]
                //
                // 1001.07 つまり約10000px相当の奥行きを描画

                float dep = -_fDist_VpPlnFront; //オブジェクトの視点からの距離(DIRECTX距離)
                static float roughly_dep_point1 = ((pCAM->_zf) * (5.0/10.0)); //荒くなるポイント１(カメラ可視奥行の 5/10 の地点)( 500.535 DIRECTX距離)
                static float roughly_dep_point2 = ((pCAM->_zf) * (8.0/10.0)); //荒くなるポイント２(カメラ可視奥行の 8/10 の地点)( 800.856 DIRECTX距離)

                if (dep <= roughly_dep_point1) { //depが ～ roughly_dep_point1 までの距離のオブジェクトは

                    _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(dep, this); //DirectXの距離1が深さ1。よって10px間隔
                    // MAX_DRAW_DEPTH_LEVEL の 0 ～ (int)roughly_dep_point1 までココで当てはめられることになる
                    // 上記の例では 1001.07 * (5.0/10.0) = 500.535
                    // MAX_DRAW_DEPTH_LEVEL = 0 ～ 500 が使用される
//                    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//                        _TRACE_(GgafGod::_pGod->_godframe<<"\t"<<getName()<<"\t"<<dep<<"\t"<<_now_drawdepth<<"\t1\tinfo\tOffset=0\t"<<pCAM->_zf<<"\t"<<roughly_dep_point1<<"\t"<<roughly_dep_point2<<"\t");
//                    }
                } else if (dep <= roughly_dep_point2) {
                    //dep が roughly_dep_point1(500.535) ～ roughly_dep_point2(800.856) までの距離のオブジェクトは
                    int offset_DRAW_DEPTH_LEVEL = roughly_dep_point1; //オフセット

                    _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(offset_DRAW_DEPTH_LEVEL + ((dep - roughly_dep_point1) * 0.2), this);  //0.2倍。つまりDirectXの距離5が深さ1。よって50px間隔で段階レンダ
                    // (dep - roughly_dep_point1) * 0.2 の dep が roughly_dep_point2 の場合
                    // (800.856 - 500.535) * 0.2 =  550.5885 となるので
                    // MAX_DRAW_DEPTH_LEVEL の 500 ～  550 がここで当てはめられる
//                    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//                        _TRACE_(GgafGod::_pGod->_godframe<<"\t"<<getName()<<"\t"<<dep<<"\t"<<_now_drawdepth<<"\t2\tinfo\tOffset="<<offset_DRAW_DEPTH_LEVEL<<"\t"<<pCAM->_zf<<"\t"<<roughly_dep_point1<<"\t"<<roughly_dep_point2<<"\t");
//                    }
                } else {
                    //dep が roughly_dep_point2(800.856) ～ までの距離のオブジェクトは
                    //上の offset_DRAW_DEPTH_LEVEL + (dep - roughly_dep_point1) * 0.2) の dep に roughly_dep_point2を代入した値がオフセットである
                    int offset_DRAW_DEPTH_LEVEL = roughly_dep_point1 + ((roughly_dep_point2 - roughly_dep_point1) * 0.2);

                    _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(offset_DRAW_DEPTH_LEVEL  + ((dep - roughly_dep_point2) * 0.04), this); //0.04倍。つまりDirectXの距離25が深さ1。よって250px間隔で段階レンダ
//                    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//                        _TRACE_(GgafGod::_pGod->_godframe<<"\t"<<getName()<<"\t"<<dep<<"\t"<<_now_drawdepth<<"\t3\tinfo\tOffset="<<offset_DRAW_DEPTH_LEVEL<<"\t"<<pCAM->_zf<<"\t"<<roughly_dep_point1<<"\t"<<roughly_dep_point2<<"\t");
//                    }
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


GgafDx9DrawableActor::~GgafDx9DrawableActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    DELETEARR_IMPOSSIBLE_NULL(_technique_temp);
    _pGgafDx9ModelCon->close();
    _pGgafDx9EffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
