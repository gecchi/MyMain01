#include "jp/ggaf/dxcore/model/GgafDxSpriteSetModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/actor/GgafDxSpriteSetActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteSetEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxSpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_TEX1);
GgafDxSpriteSetModel::GgafDxSpriteSetModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
    if (names.size() > 2) {
        throwGgafCriticalException("prm_model_name には \"xxxxxx\" or \"8/xxxxx\" 形式を指定してください。 \n"<<
                "実際の引数は、prm_idstr="<<prm_model_name);
    }
    if (names.size() == 2) {
        _set_num = STOI(names[0]);
        if (_set_num > 18) {
            _TRACE_("GgafDxSpriteSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大の18セットですがそれ以上のセット数です。意図していますか？ _set_num="<<_set_num<<"。");
        }
    } else {
        _TRACE_("GgafDxSpriteSetModel("<<prm_model_name<<") の同時描画セット数省略。最大の18セットが設定されます。");
        _set_num = 18;
    }

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _paIndexParam = nullptr;
    _obj_model |= Obj_GgafDxSpriteSetModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreSpriteSetModel(GgafDxSpriteSetModel*)
    //で行うようにした。要参照。
}

//描画
HRESULT GgafDxSpriteSetModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("GgafDxSpriteSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        throwGgafCriticalException(_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //対象Actor
    const GgafDxSpriteSetActor* const pTargetActor = (GgafDxSpriteSetActor*)prm_pActor_target;
    //対象SpriteSetActorのエフェクトラッパ
    GgafDxSpriteSetEffect* const pSpriteSetEffect = (GgafDxSpriteSetEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pSpriteSetEffect->_pID3DXEffect;

    HRESULT hr;
    //モデルが同じならば頂点バッファ等、の設定はスキップできる
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxSpriteSetModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
        if (pEffect_active) {
            _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "End() に失敗しました。");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwGgafCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name<<"("<<pSpriteSetEffect<<")");
        hr = pID3DXEffect->Begin( &_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pSpriteSetEffect->_begin) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pSpriteSetEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
    const INDEXPARAM& idxparam = _paIndexParam[prm_draw_set_num - 1];
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                  idxparam.BaseVertexIndex,
                                  idxparam.MinIndex,
                                  idxparam.NumVertices,
                                  idxparam.StartIndex,
                                  idxparam.PrimitiveCount);
    if (_num_pass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");

        for (UINT pass = 1; pass < _num_pass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, pass+1<<"パス目 BeginPass("<<pass<<") に失敗しました。");
            pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                          idxparam.BaseVertexIndex,
                                          idxparam.MinIndex,
                                          idxparam.NumVertices,
                                          idxparam.StartIndex,
                                          idxparam.PrimitiveCount);
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
        }

        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "１パス目 BeginPass(0) に失敗しました。");
    }

    //前回描画モデル保持
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pSpriteSetEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif
    return D3D_OK;
}

void GgafDxSpriteSetModel::restore() {
    _TRACE3_("_model_name="<<_model_name);
    if (4*_set_num > 65535) {
        throwGgafCriticalException("頂点が 65535を超えたかもしれません。\n対象Model："<<getName()<<"  nVertices:4  セット数:"<<(_set_num));
    }
    if ( 2 * 3 * _set_num > 65535) {
        throwGgafCriticalException("頂点インデックスが 65535を超えたかもしれません。\n対象Model："<<getName()<<"  nFaces:2(*3)  セット数:"<<(_set_num));
    }

    _papTextureConnection = nullptr;

    HRESULT hr;
//    //スプライト情報読込みテンプレートの登録(初回実行時のみ)
//    ID3DXFileEnumObject* pID3DXFileEnumObject;
//    ID3DXFileData* pID3DXFileData;
    std::string xfile_name; //読み込むスプライト定義ファイル名（Xファイル形式）
    //"12/Bomb" or "8/Bomb" or "Bomb" から "Bomb" だけ取とりだしてフルパス名取得
    if (*(_model_name + 1) == '/') {
        xfile_name = GgafDxModelManager::getSpriteFileName(std::string(_model_name + 2));
    } else if (*(_model_name + 2) == '/') {
        xfile_name = GgafDxModelManager::getSpriteFileName(std::string(_model_name + 3));
    } else {
        xfile_name = GgafDxModelManager::getSpriteFileName(std::string(_model_name));
    }
    GgafDxModelManager::SpriteXFileFmt xdata;
    GgafDxModelManager::obtainSpriteInfo(&xdata, xfile_name);
    _model_width_px  = xdata.width;
    _model_height_px = xdata.height;
    _row_texture_split = xdata.row_texture_split;
    _col_texture_split = xdata.col_texture_split;

    //テクスチャ取得しモデルに保持させる
    GgafDxTextureConnection* model_pTextureConnection = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(xdata.texture_file, this));
    //テクスチャの参照を保持させる。
    _papTextureConnection = NEW GgafDxTextureConnection*[1];
    _papTextureConnection[0] = model_pTextureConnection;
    //バッファ作成
    if (_pVertexBuffer == nullptr) {
        _size_vertices = sizeof(GgafDxSpriteSetModel::VERTEX)*4;
        _size_vertex_unit = sizeof(GgafDxSpriteSetModel::VERTEX);

        GgafDxSpriteSetModel::VERTEX* paVertex = NEW GgafDxSpriteSetModel::VERTEX[4 * _set_num];

        float tex_width  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
        float tex_height = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)
        float du = 1.0f / tex_width  / 100000.0f; //テクスチャの幅1pxの100000分の1px
        float dv = 1.0f / tex_height / 100000.0f; //テクスチャの高さ1pxの100000分の1px
        float rev = 1.0f;//0.99609308; //99609309で割れ
        //頂点配列情報をモデルに保持させる
        //UVは左上の１つ分（アニメパターン０）をデフォルトで設定する。
        //シェーダーが描画時にアニメパターン番号をみてUV座標をずらす仕様としよっと。
        //x,y の ÷2 とは、モデル中心をローカル座標の原点中心としたいため
        for (int i = 0; i < _set_num; i++) {
            //左上
            paVertex[i*4 + 0].x = (PX_DX(xdata.width)  / -2.0)*rev;
            paVertex[i*4 + 0].y = (PX_DX(xdata.height) /  2.0)*rev;
            paVertex[i*4 + 0].z = 0.0f;
            paVertex[i*4 + 0].nx = 0.0f;
            paVertex[i*4 + 0].ny = 0.0f;
            paVertex[i*4 + 0].nz = -1.0f;
            paVertex[i*4 + 0].tu = du;
            paVertex[i*4 + 0].tv = dv;
            paVertex[i*4 + 0].index = (float)i;
            //右上
            paVertex[i*4 + 1].x = (PX_DX(xdata.width)  / 2.0)*rev;
            paVertex[i*4 + 1].y = (PX_DX(xdata.height) / 2.0)*rev;
            paVertex[i*4 + 1].z = 0.0f;
            paVertex[i*4 + 1].nx = 0.0f;
            paVertex[i*4 + 1].ny = 0.0f;
            paVertex[i*4 + 1].nz = -1.0f;
            paVertex[i*4 + 1].tu = (1.0/xdata.col_texture_split) - du;
            paVertex[i*4 + 1].tv = dv;
            paVertex[i*4 + 1].index = (float)i;
            //左下
            paVertex[i*4 + 2].x = (PX_DX(xdata.width)  / -2.0)*rev;
            paVertex[i*4 + 2].y = (PX_DX(xdata.height) / -2.0)*rev;
            paVertex[i*4 + 2].z = 0.0f;
            paVertex[i*4 + 2].nx = 0.0f;
            paVertex[i*4 + 2].ny = 0.0f;
            paVertex[i*4 + 2].nz = -1.0f;
            paVertex[i*4 + 2].tu = du;
            paVertex[i*4 + 2].tv = (1.0/xdata.row_texture_split) - dv;
            paVertex[i*4 + 2].index = (float)i;
            //右下
            paVertex[i*4 + 3].x = (PX_DX(xdata.width)  /  2.0)*rev;
            paVertex[i*4 + 3].y = (PX_DX(xdata.height) / -2.0)*rev;
            paVertex[i*4 + 3].z = 0.0f;
            paVertex[i*4 + 3].nx = 0.0f;
            paVertex[i*4 + 3].ny = 0.0f;
            paVertex[i*4 + 3].nz = -1.0f;
            paVertex[i*4 + 3].tu = (1.0/xdata.col_texture_split) - du;
            paVertex[i*4 + 3].tv = (1.0/xdata.row_texture_split) - dv;
            paVertex[i*4 + 3].index = (float)i;

        }

        //距離
        FLOAT model_bounding_sphere_radius = (FLOAT)(sqrt(paVertex[0].x * paVertex[0].x +
                                                          paVertex[0].y * paVertex[0].y +
                                                          paVertex[0].z * paVertex[0].z));
        _bounding_sphere_radius = model_bounding_sphere_radius;


        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices * _set_num,
                D3DUSAGE_WRITEONLY,
                GgafDxSpriteSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_p1ID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));
        //頂点バッファ作成
        //頂点情報をビデオカード頂点バッファへロード
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(
                               0,
                               _size_vertices * _set_num,
                               (void**)&pVertexBuffer,
                               0
                           );
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_name);

        memcpy(
            pVertexBuffer,
            paVertex,
            _size_vertices* _set_num
        ); //pVertexBuffer ← paVertex
        _pVertexBuffer->Unlock();
        GGAF_DELETEARR(paVertex);
    }

    //インデックスバッファ作成
    if (_pIndexBuffer == nullptr) {
        int nVertices = 4;
        int nFaces = 2;
        WORD* unit_paIdxBuffer = NEW WORD[(nFaces*3)];
        unit_paIdxBuffer[0] = 0;
        unit_paIdxBuffer[1] = 1;
        unit_paIdxBuffer[2] = 2;

        unit_paIdxBuffer[3] = 1;
        unit_paIdxBuffer[4] = 3;
        unit_paIdxBuffer[5] = 2;

        WORD* paIdxBufferSet = NEW WORD[(nFaces*3) * _set_num];
        for (int i = 0; i < _set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer[j*3 + 0] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer[j*3 + 1] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer[j*3 + 2] + (nVertices*i);
            }
        }

        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3 * _set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_name));

        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          paIdxBufferSet,
          sizeof(WORD) * nFaces * 3 * _set_num
        );
        _pIndexBuffer->Unlock();
        GGAF_DELETEARR(unit_paIdxBuffer);
        GGAF_DELETEARR(paIdxBufferSet);

        //描画時パラメーター
        GgafDxSpriteSetModel::INDEXPARAM* paIndexParam = NEW GgafDxSpriteSetModel::INDEXPARAM[_set_num];
        for (int i = 0; i < _set_num; i++) {
            paIndexParam[i].MaterialNo = 0;
            paIndexParam[i].BaseVertexIndex = 0;
            paIndexParam[i].MinIndex = 0;
            paIndexParam[i].NumVertices = nVertices*(i+1);
            paIndexParam[i].StartIndex = 0;
            paIndexParam[i].PrimitiveCount = nFaces*(i+1);
        }
        _paIndexParam = paIndexParam;
    }

    _num_materials = 1;
    D3DMATERIAL9* paMaterial = NEW D3DMATERIAL9[_num_materials];
    for( DWORD i = 0; i < _num_materials; i++){
        //paMaterial[i] = paD3DMaterial9_tmp[i].MatD3D;
        paMaterial[i].Diffuse.r = 1.0f;
        paMaterial[i].Diffuse.g = 1.0f;
        paMaterial[i].Diffuse.b = 1.0f;
        paMaterial[i].Diffuse.a = 1.0f;
        paMaterial[i].Ambient.r = 1.0f;
        paMaterial[i].Ambient.g = 1.0f;
        paMaterial[i].Ambient.b = 1.0f;
        paMaterial[i].Ambient.a = 1.0f;
    }
    _paMaterial_default = paMaterial;
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxSpriteSetModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxSpriteSetModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    GGAF_DELETEARR(_paIndexParam);
    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_name=" << _model_name << " end");
}

GgafDxSpriteSetModel::~GgafDxSpriteSetModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

