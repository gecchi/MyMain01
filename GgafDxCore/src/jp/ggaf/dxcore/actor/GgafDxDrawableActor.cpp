#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

hashval GgafDxDrawableActor::_hash_technique_last_draw = 0;

GgafDxDrawableActor::GgafDxDrawableActor(const char* prm_name,
                                         const char* prm_model,
                                         const char* prm_effect,
                                         const char* prm_technique,
                                         GgafStatus* prm_pStat,
                                         GgafDxChecker* prm_pChecker) :
  GgafDxGeometricActor(prm_name, prm_pStat, prm_pChecker) {
    _obj_class |= Obj_GgafDxDrawableActor;
    _class_name = "GgafDxDrawableActor";

    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _hash_technique = 0;

    _temp_technique = NEW char[51];
    _hash_temp_technique = 0;

    _frame_of_behaving_temp_technique_end = 0;
    _is_temp_technique = false;
    _pNext_TheSameDrawDepthLevel = nullptr;
    //モデル取得connectModelManager
    _pModelCon = (GgafDxModelConnection*)GgafDxGod::_pModelManager->connect(prm_model);
    _pModel = (GgafDxModel*)_pModelCon->fetch();
    //エフェクト取得
    _pEffectCon = (GgafDxEffectConnection*)GgafDxGod::_pEffectManager->connect(prm_effect);
    _pEffect = (GgafDxEffect*)_pEffectCon->fetch();
    //マテリアルをコピー
    _paMaterial = NEW D3DMATERIAL9[_pModel->_num_materials];
    for (DWORD i = 0; i < _pModel->_num_materials; i++){
        _paMaterial[i] = _pModel->_paMaterial_default[i];
    }
    _alpha = 1.0f;
    _pFader = NEW GgafDxAlphaFader(this);
    //最大距離頂点
    _bounding_sphere_radius = _pModel->_bounding_sphere_radius;
    _now_drawdepth = 0;
    _specal_drawdepth = -1;
    _zenable = true;
    _zwriteenable = true;
    _hash_technique = UTIL::easy_hash(prm_technique) + UTIL::easy_hash(_pModel->getName());
}

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

    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _hash_technique = 0;

    _temp_technique = NEW char[51];
    _hash_temp_technique = 0;

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

    _pNext_TheSameDrawDepthLevel = nullptr;
    //モデル取得
    _pModelCon = (GgafDxModelConnection*)GgafDxGod::_pModelManager->connect(model_name);
    _pModel = (GgafDxModel*)_pModelCon->fetch();
    //エフェクト取得
    _pEffectCon = (GgafDxEffectConnection*)GgafDxGod::_pEffectManager->connect(effelct_name);
    _pEffect = (GgafDxEffect*)_pEffectCon->fetch();
    //マテリアルをコピー
    _paMaterial = NEW D3DMATERIAL9[_pModel->_num_materials];
    for (DWORD i = 0; i < _pModel->_num_materials; i++){
        _paMaterial[i] = _pModel->_paMaterial_default[i];
    }
    _alpha = 1.0f;
    _pFader = NEW GgafDxAlphaFader(this);
    //最大距離頂点
    _bounding_sphere_radius = _pModel->_bounding_sphere_radius;

    DELETEARR_IMPOSSIBLE_NULL(model_name);
    DELETEARR_IMPOSSIBLE_NULL(effelct_name);

    _now_drawdepth = 0;
    _specal_drawdepth = -1;
    _zenable = true;
    _zwriteenable = true;
    _hash_technique = UTIL::easy_hash(prm_technique) + UTIL::easy_hash(_pModel->getName());
}



void GgafDxDrawableActor::processPreDraw() {
    if (_pModel->_is_init_model == false) {
        onCreateModel(); //モデル作成時の初期処理
        _pModel->_is_init_model = true;
    }

    _pNext_TheSameDrawDepthLevel = nullptr;
    //TODO:要検証
    if (isActiveInTheTree()) { //isActiveInTheTree() で判定すると、
        if (_is2DActor) {
//            _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(
//                                (int)((1.0*_Z/LEN_UNIT) * MAX_DRAW_DEPTH_LEVEL),
//                                this
//                             );
            if (_alpha <= 0.0f || ((GgafDxScene*)getPlatformScene())->_master_alpha <= 0.0f) {
                //描画しないので登録なし
            } else {
                _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(_Z, this); //2Dは_Zはプライオリティに使用。
            }
        } else {
            if (isOutOfView() || _alpha <= 0.0f || ((GgafDxScene*)getPlatformScene())->_pAlphaCurtain->_alpha <= 0.0f) {
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
                //  GgafDxUniverse::setDrawDepthLevel(-1.0*_dest_from_vppln_front, this);
                //   (※_dest_from_vppln_frontは視錐台手前面からオブジェクトまでの距離の負数)
                //
                //これは、1000 段階の深度判定となる。
                //また、
                //
                //  GgafDxUniverse::setDrawDepthLevel(-1.0*_dest_from_vppln_front*10.0, this);
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
                dxcoord dep = -_dest_from_vppln_front; //オブジェクトの視点からの距離(DIRECTX距離)

                static const double dep_rate_point1 = 0.3;                                //荒くなるポイント１の割合(カメラ可視奥行の 3/10 の地点)
                static const double dep_rate_point2 = 0.6;                                //荒くなるポイント２の割合(カメラ可視奥行の 6/10 の地点)
                static const dxcoord roughly_dep_point1 = (P_CAM->_zf * dep_rate_point1); //荒くなるポイント１距離
                static const dxcoord roughly_dep_point2 = (P_CAM->_zf * dep_rate_point2); //荒くなるポイント２距離
                static const double dep_level_rate_cam_to_point1 = 0.5;                   //視点～荒くなるポイント１までの、深度レベルを求めるために距離に乗ずる割合。
                static const double dep_level_rate_point1_to_point2 = 0.2;                //荒くなるポイント１～ポイント２間の、深度レベルを求めるために距離に乗ずる割合。
                static const double dep_level_rate_point2_to_far_away = 0.01;             //荒くなるポイント２～最遠の、深度レベルを求めるために距離に乗ずる割合。
                static const int roughly_dep_point1_DRAW_DEPTH_LEVEL = roughly_dep_point1*dep_level_rate_cam_to_point1;    //荒くなるポイント１深度レベル
                static const int roughly_dep_point2_DRAW_DEPTH_LEVEL = roughly_dep_point1_DRAW_DEPTH_LEVEL +
                               ((roughly_dep_point2 - roughly_dep_point1) * dep_level_rate_point1_to_point2);        //荒くなるポイント２深度レベル

                if (_specal_drawdepth < 0) { //特別な描画深度指定無し
                    if (dep <= roughly_dep_point1) {         //depが 視点 ～ r荒くなるポイント１ までの距離のオブジェクト
                        _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(
                                             dep*dep_level_rate_cam_to_point1,
                                             this); //DirectXの距離1の0.5倍、DirectXの距離2が深さ1。よって約20px間隔
                    } else if (dep <= roughly_dep_point2) {  //depが 荒くなるポイント１～ポイント２間
                        _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(
                                             roughly_dep_point1_DRAW_DEPTH_LEVEL +
                                               ((dep - roughly_dep_point1) * dep_level_rate_point1_to_point2),
                                             this);  //DirectXの距離1の0.2倍。つまりDirectXの距離5が深さ1。よって50px間隔で段階レンダ
                    } else {                                 //depが ポイント２以降
                        _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(
                                             roughly_dep_point2_DRAW_DEPTH_LEVEL +
                                               ((dep - roughly_dep_point2) * dep_level_rate_point2_to_far_away),
                                             this); //0.01倍。つまりDirectXの距離100が深さ1。よって1000px間隔で段階レンダ
                    }
                } else {
                    //特別な描画深度指定有り
                    if (GgafDxUniverse::_apAlphaActorFirstList_DrawDepthLevel[_specal_drawdepth] == nullptr) {
                        //そのprm_draw_depth_levelで最初のアクターの場合
                        this->_pNext_TheSameDrawDepthLevel = nullptr;
                        GgafDxUniverse::_apAlphaActorFirstList_DrawDepthLevel[_specal_drawdepth] = this;
                        GgafDxUniverse::_apAlphaActorLastList_DrawDepthLevel[_specal_drawdepth] = this;
                    } else {
                        //前に追加
                        GgafDxDrawableActor* pActorTmp = GgafDxUniverse::_apAlphaActorFirstList_DrawDepthLevel[_specal_drawdepth];
                        this->_pNext_TheSameDrawDepthLevel = pActorTmp;
                        GgafDxUniverse::_apAlphaActorFirstList_DrawDepthLevel[_specal_drawdepth] = this;
                    }
                    _now_drawdepth = _specal_drawdepth;
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


void GgafDxDrawableActor::processAfterDraw() {
#ifdef MY_DEBUG
    //当たり判定領域表示
    if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        drawHitArea();
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDxGod::_d3dfillmode);
    }
#endif
}

void GgafDxDrawableActor::setMaterialColor(float r, float g, float b) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.r = r;
        _paMaterial[i].Diffuse.r = r;
        _paMaterial[i].Ambient.g = g;
        _paMaterial[i].Diffuse.g = g;
        _paMaterial[i].Ambient.b = b;
        _paMaterial[i].Diffuse.b = b;
    }
}

void GgafDxDrawableActor::resetMaterialColor() {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.r = _pModel->_paMaterial_default[i].Ambient.r;
        _paMaterial[i].Diffuse.r = _pModel->_paMaterial_default[i].Diffuse.r;
        _paMaterial[i].Ambient.g = _pModel->_paMaterial_default[i].Ambient.g;
        _paMaterial[i].Diffuse.g = _pModel->_paMaterial_default[i].Diffuse.g;
        _paMaterial[i].Ambient.b = _pModel->_paMaterial_default[i].Ambient.b;
        _paMaterial[i].Diffuse.b = _pModel->_paMaterial_default[i].Diffuse.b;
    }
}

void GgafDxDrawableActor::setSpecialDrawDepth(int prm_drawdepth) {
    if (prm_drawdepth > MAX_DRAW_DEPTH_LEVEL) {
        _specal_drawdepth = MAX_DRAW_DEPTH_LEVEL;
    } else {
        _specal_drawdepth = prm_drawdepth;
    }
}

void GgafDxDrawableActor::changeEffectTechnique(const char* prm_technique) {
    _hash_technique = UTIL::easy_hash(prm_technique) + UTIL::easy_hash(_pModel->getName());
    strcpy(_technique, prm_technique);
}
void GgafDxDrawableActor::changeEffectTechniqueInterim(const char* prm_technique, frame prm_frame) {
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

void GgafDxDrawableActor::effectFlush(frame prm_frame) {
    changeEffectTechniqueInterim("Flush", prm_frame); //フラッシュ
}

void GgafDxDrawableActor::effectBlendOne(frame prm_frame) {
    changeEffectTechniqueInterim("DestBlendOne", prm_frame);
}

void GgafDxDrawableActor::effectDefault() {
    if (_is_temp_technique) {
        _hash_technique = _hash_temp_technique;
        strcpy(_technique, _temp_technique);
        _is_temp_technique = false;
        _hash_temp_technique = 0;
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
