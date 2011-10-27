#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

unsigned int GgafDxDrawableActor::_hash_technique_last_draw = 0;

GgafDxDrawableActor::GgafDxDrawableActor(const char* prm_name,
                                           const char* prm_model,
                                           const char* prm_effect,
                                           const char* prm_technique,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) :
  GgafDxGeometricActor(prm_name, prm_pStat, prm_pChecker) {
    _obj_class |= Obj_GgafDxDrawableActor;
    _class_name = "GgafDxDrawableActor";

    //_TRACE_("GgafDxDrawableActor::GgafDxDrawableActor(");
    //_TRACE_("    prm_name="<<prm_name);
    //_TRACE_("    prm_model="<<prm_model);
    //_TRACE_("    prm_effect="<<prm_effect);
    //_TRACE_("    prm_technique="<<prm_technique);
    //_TRACE_(")");

    _hash_technique = GgafUtil::easy_hash(prm_technique);
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _temp_technique = NEW char[51];
    _hash_technique = 0;
    _frame_of_behaving_temp_technique_end = 0;
    _is_temp_technique = false;

    _pNext_TheSameDrawDepthLevel = NULL;
    //モデル取得connectModelManager
    _pModelCon = (GgafDxModelConnection*)GgafDxGod::_pModelManager->connect(prm_model);
    _pModel = (GgafDxModel*)_pModelCon->use();
    //エフェクト取得
    _pEffectCon = (GgafDxEffectConnection*)GgafDxGod::_pEffectManager->connect(prm_effect);
    _pEffect = (GgafDxEffect*)_pEffectCon->use();
    //マテリアルをコピー
    _paMaterial = NEW D3DMATERIAL9[_pModel->_dwNumMaterials];
    for (DWORD i = 0; i < _pModel->_dwNumMaterials; i++){
        _paMaterial[i] = _pModel->_paMaterial_default[i];
    }
    _fAlpha = 1.0f;
    _pFader = NEW GgafDxAlphaFader(this);
    //最大距離頂点
    _radius_bounding_sphere = _pModel->_radius_bounding_sphere;
    _now_drawdepth = 0;
    _specal_drawdepth = -1;
    _zenable = true;
    _zwriteenable = true;
}
//((GgafDxCore::GgafDxModelConnection*)(GgafDxCore::GgafDxGod::_pModelManager->connect(prm_model))


GgafDxDrawableActor::GgafDxDrawableActor(const char* prm_name,
                                           const char* prm_model_id,
                                           const char* prm_model_type,
                                           const char* prm_effect_id,
                                           const char* prm_effect_type,
                                           const char* prm_technique,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) :
  GgafDxGeometricActor(prm_name, prm_pStat, prm_pChecker) {

    _class_name = "GgafDxDrawableActor";
    _hash_technique = GgafUtil::easy_hash(prm_technique);
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _temp_technique = NEW char[51];
    _hash_technique = 0;
    _frame_of_behaving_temp_technique_end = 0;
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
    _pModelCon = (GgafDxModelConnection*)GgafDxGod::_pModelManager->connect(model_name);
    _pModel = (GgafDxModel*)_pModelCon->use();
    //エフェクト取得
    _pEffectCon = (GgafDxEffectConnection*)GgafDxGod::_pEffectManager->connect(effelct_name);
    _pEffect = (GgafDxEffect*)_pEffectCon->use();
    //マテリアルをコピー
    _paMaterial = NEW D3DMATERIAL9[_pModel->_dwNumMaterials];
    for (DWORD i = 0; i < _pModel->_dwNumMaterials; i++){
        _paMaterial[i] = _pModel->_paMaterial_default[i];
    }
    _fAlpha = 1.0f;
    _pFader = NEW GgafDxAlphaFader(this);
    //最大距離頂点
    _radius_bounding_sphere = _pModel->_radius_bounding_sphere;

    DELETEARR_IMPOSSIBLE_NULL(model_name);
    DELETEARR_IMPOSSIBLE_NULL(effelct_name);

    _now_drawdepth = 0;
    _specal_drawdepth = -1;
    _zenable = true;
    _zwriteenable = true;
}



void GgafDxDrawableActor::processPreDraw() {
    if (_pModel->_is_init_model == false) {
        onCreateModel(); //モデル作成時の初期処理
        _pModel->_is_init_model = true;
    }

    _pNext_TheSameDrawDepthLevel = NULL;
    //TODO:要検証
    if (isActiveInTheTree()) { //isActiveInTheTree() で判定すると、
        if (_is2DActor) {
//            _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(
//                                (int)((1.0*_Z/LEN_UNIT) * MAX_DRAW_DEPTH_LEVEL),
//                                this
//                             );
            _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(_Z, this); //2Dは_Zはプライオリティに使用。
        } else {
            if (isOutOfView() || _fAlpha <= 0.0f || ((GgafDxScene*)getPlatformScene())->_pAlphaCurtain->_alpha <= 0.0f) {
                //描画しないので登録なし
            } else {
                //＜メモ＞
                //初期カメラ位置 _cameraZ_org = -47.6701、表示範囲奥行き  _zf は _dep=20のとき、_zf = -_cameraZ_org*(_dep+1); とした場合の例。。
                //「参照：GgafDxCamera::GgafDxCamera()」
                //表示範囲(奥行き:_zf)の距離は初期カメラの引き位置距離の21倍で約 1000(1001.0721) になる（これが _zf = -_cameraZ_org*20.0 の意味）
                //さて MAX_DRAW_DEPTH_LEVEL (現在1000)とどのように対応させるか
                //本ライブラリはDIRECTX座標の1は原点付近ので画面上約10px相当という計算を行っている。よって
                //次の文は約10px間隔相当の奥からの段階レンダリングの設定となる
                //
                //  GgafDxUniverse::setDrawDepthLevel(-1.0*_fDist_VpPlnFront, this);
                //   (※_fDist_VpPlnFrontは視錐台手前面からオブジェクトまでの距離の負数)
                //
                //これは、1000 段階の深度判定となる。
                //また、
                //
                //  GgafDxUniverse::setDrawDepthLevel(-1.0*_fDist_VpPlnFront*10.0, this);
                //
                //これは1px間隔相当で約 10000 段階となる。
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
                //   7975036 <DEBUG> GgafDxCamera::GgafDxCamera 画面アスペクト：1.33333
                //   7975036 <DEBUG> GgafDxCamera::GgafDxCamera FovX=1.39626 FovY=1.12341
                //   7975036 <DEBUG> GgafDxCamera::GgafDxCamera カメラの位置(0,0,-47.6701)
                //   7975036 <DEBUG> GgafDxCamera::GgafDxCamera 範囲 [0.01 ~ 1001.07]
                //
                // 1001.07 つまり約10000px相当の奥行きを描画
                if (_specal_drawdepth < 0) { //特別な描画深度指定無し

                    float dep = -_fDist_VpPlnFront; //オブジェクトの視点からの距離(DIRECTX距離)
                    static float roughly_dep_point1 = (P_CAM->_zf * 0.3); //荒くなるポイント１(カメラ可視奥行の 3/10 の地点)(約 300 DIRECTX距離)
                    static float roughly_dep_point2 = (P_CAM->_zf * 0.6); //荒くなるポイント２(カメラ可視奥行の 6/10 の地点)(約 600 DIRECTX距離)

                    if (dep <= roughly_dep_point1) { //depが ～ roughly_dep_point1 までの距離のオブジェクトは

                        _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(dep*0.5, this); //DirectXの距離1の0.5倍、DirectXの距離2が深さ1。よって20px間隔
                        // MAX_DRAW_DEPTH_LEVEL の 0 ～ (int)roughly_dep_point1 までココで当てはめられることになる
                        // 上記の例では 1001.07 * 0.3 = 300 より、DIRECTX距離 0～300 に対し 300*0.5 = 150 であるので
                        // MAX_DRAW_DEPTH_LEVEL = 0 ～ 150 が割り当てられる
                    } else if (dep <= roughly_dep_point2) {
                        //dep が roughly_dep_point1(300 DIRECTX距離) ～ roughly_dep_point2(600 DIRECTX距離) までの距離のオブジェクトは
                        int offset_DRAW_DEPTH_LEVEL = roughly_dep_point1*0.5; //段階レベルオフセット = 150

                        _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(offset_DRAW_DEPTH_LEVEL + ((dep - roughly_dep_point1) * 0.2), this);  //DirectXの距離1の0.2倍。つまりDirectXの距離5が深さ1。よって50px間隔で段階レンダ
                        // (dep - roughly_dep_point1) * 0.2 の dep が roughly_dep_point2 の場合
                        // (600 - 300) * 0.2 =  60、となるのでDIRECTX距離 300～600 に対して MAX_DRAW_DEPTH_LEVEL の 150～210 がここで当てはめられる
                    } else {
                        //dep が roughly_dep_point2(600) ～ の距離のオブジェクトは
                        //上の offset_DRAW_DEPTH_LEVEL + (dep - roughly_dep_point1) * 0.2) の dep に roughly_dep_point2を代入した値がオフセットである
                        int offset_DRAW_DEPTH_LEVEL = (roughly_dep_point1*0.5) + ((roughly_dep_point2 - roughly_dep_point1) * 0.2);

                        _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(offset_DRAW_DEPTH_LEVEL  + ((dep - roughly_dep_point2) * 0.01), this); //0.01倍。つまりDirectXの距離100が深さ1。よって1000px間隔で段階レンダ
                    }
//                    if (GgafDxInput::isBeingPressedKey(DIK_I)) {
//                        _TRACE_("setDep ["<<_now_drawdepth<<"]:dep="<<dep<<" roughly_dep_point1="<<roughly_dep_point1<<" roughly_dep_point2="<<roughly_dep_point2<<" name="<<this->getName());
//                    }
                } else {
                    //特別な描画深度指定有り
                    if (GgafDxUniverse::_apAlphaActorList_DrawDepthLevel[_specal_drawdepth] == NULL) {
                        //そのprm_draw_depth_levelで最初のアクターの場合
                        this->_pNext_TheSameDrawDepthLevel = NULL;
                        GgafDxUniverse:: _apAlphaActorList_DrawDepthLevel[_specal_drawdepth] = this;
                    } else {
                        //前に追加
                        GgafDxDrawableActor* pActorTmp = GgafDxUniverse::_apAlphaActorList_DrawDepthLevel[_specal_drawdepth];
                        this->_pNext_TheSameDrawDepthLevel = pActorTmp;
                        GgafDxUniverse::_apAlphaActorList_DrawDepthLevel[_specal_drawdepth] = this;
                    }
                    _now_drawdepth = _specal_drawdepth;
//                    if (GgafDxInput::isBeingPressedKey(DIK_I)) {
//                        _TRACE_("_specal_drawdepth ["<<_now_drawdepth<<"]: name="<<this->getName());
//                    }
                }

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


#ifdef MY_DEBUG

void GgafDxDrawableActor::processAfterDraw() {
    //当たり判定領域表示
    if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        drawHitArea();
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDxGod::_d3dfillmode);
    }
}

#else

void GgafDxDrawableActor::processAfterDraw() {}

#endif



void GgafDxDrawableActor::setMaterialColor(float r, float g, float b) {
    for (DWORD i = 0; i < _pModel->_dwNumMaterials; i++) {
        _paMaterial[i].Ambient.r = r;
        _paMaterial[i].Diffuse.r = r;
        _paMaterial[i].Ambient.g = g;
        _paMaterial[i].Diffuse.g = g;
        _paMaterial[i].Ambient.b = b;
        _paMaterial[i].Diffuse.b = b;
    }
}

void GgafDxDrawableActor::resetMaterialColor() {
    for (DWORD i = 0; i < _pModel->_dwNumMaterials; i++) {
        _paMaterial[i].Ambient.r = _pModel->_paMaterial_default[i].Ambient.r;
        _paMaterial[i].Diffuse.r = _pModel->_paMaterial_default[i].Diffuse.r;
        _paMaterial[i].Ambient.g = _pModel->_paMaterial_default[i].Ambient.g;
        _paMaterial[i].Diffuse.g = _pModel->_paMaterial_default[i].Diffuse.g;
        _paMaterial[i].Ambient.b = _pModel->_paMaterial_default[i].Ambient.b;
        _paMaterial[i].Diffuse.b = _pModel->_paMaterial_default[i].Diffuse.b;
    }
}


GgafDxDrawableActor::~GgafDxDrawableActor() {
    DELETE_IMPOSSIBLE_NULL(_pFader);
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    DELETEARR_IMPOSSIBLE_NULL(_temp_technique);
    DELETEARR_IMPOSSIBLE_NULL(_paMaterial);

    _pEffectCon->close();
    _pModelCon->close();
}
