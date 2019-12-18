#include "jp/ggaf/dx/model/SpriteSetModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/actor/SpriteSetActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/SpriteSetEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"

using namespace GgafDx;

DWORD SpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_TEX1);
SpriteSetModel::SpriteSetModel(const char* prm_model_name) : Model(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, ",");
    if (names.size() > 2) {
        throwCriticalException("prm_model_name には \"xxxxxx\" or \"8,xxxxx\" 形式を指定してください。 \n"
                "実際の引数は、prm_idstr="<<prm_model_name);
    }
    if (names.size() == 2) {
        _set_num = STOI(names[0]);
        if (_set_num > 18) {
            _TRACE_("SpriteSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大の18セットですがそれ以上のセット数です。意図していますか？ _set_num="<<_set_num<<"。");
        }
    } else {
        _TRACE_("SpriteSetModel("<<prm_model_name<<") の同時描画セット数省略。最大の18セットが設定されます。");
        _set_num = 18;
    }
    _pVertexBuffer_data = nullptr;
    _pIndexBuffer_data = nullptr;

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _paIndexParam = nullptr;
    _obj_model |= Obj_GgafDx_SpriteSetModel;
}

HRESULT SpriteSetModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("SpriteSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        throwCriticalException(_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    //対象Actor
    const SpriteSetActor* const pTargetActor = (SpriteSetActor*)prm_pActor_target;
    //対象SpriteSetActorのエフェクトラッパ
    SpriteSetEffect* const pSpriteSetEffect = (SpriteSetEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pSpriteSetEffect->_pID3DXEffect;

    HRESULT hr;
    //モデルが同じならば頂点バッファ等、の設定はスキップできる
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(SpriteSetModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }
    Effect* pEffect_active = EffectManager::_pEffect_active;
    if (FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
        if (pEffect_active) {
            _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "End() に失敗しました。");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
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
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
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
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pSpriteSetEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
    return D3D_OK;
}

void SpriteSetModel::restore() {
    _TRACE3_("_model_name="<<_model_name);
    if (_pVertexBuffer_data == nullptr) {
        if (4*_set_num > 65535) {
            throwCriticalException("頂点が 65535を超えたかもしれません。\n対象Model："<<getName()<<"  nVertices:4  セット数:"<<(_set_num));
        }
        if ( 2 * 3 * _set_num > 65535) {
            throwCriticalException("頂点インデックスが 65535を超えたかもしれません。\n対象Model："<<getName()<<"  nFaces:2(*3)  セット数:"<<(_set_num));
        }
        ModelManager* pModelManager = pGOD->_pModelManager;
        _papTextureConnection = nullptr;

        HRESULT hr;
    //    //スプライト情報読込みテンプレートの登録(初回実行時のみ)
    //    ID3DXFileEnumObject* pID3DXFileEnumObject;
    //    ID3DXFileData* pID3DXFileData;
        std::string xfile_name; //読み込むスプライト定義ファイル名（Xファイル形式）
        //"12,Bomb" or "8,Bomb" or "Bomb" から "Bomb" だけ取とりだしてフルパス名取得
        if (*(_model_name + 1) == ',') {
            xfile_name = ModelManager::getSpriteFileName(std::string(_model_name + 2), "sprx");
        } else if (*(_model_name + 2) == ',') {
            xfile_name = ModelManager::getSpriteFileName(std::string(_model_name + 3), "sprx");
        } else {
            xfile_name = ModelManager::getSpriteFileName(std::string(_model_name), "sprx");
        }
        ModelManager::SpriteXFileFmt xdata;
        pModelManager->obtainSpriteInfo(&xdata, xfile_name);
        _model_width_px  = xdata.width;
        _model_height_px = xdata.height;
        _row_texture_split = xdata.row_texture_split;
        _col_texture_split = xdata.col_texture_split;
        _pa_texture_filenames = NEW std::string[1];
        _pa_texture_filenames[0] = std::string(xdata.texture_file);
        //バッファ作成
        _size_vertices = sizeof(SpriteSetModel::VERTEX)*4;
        _size_vertex_unit = sizeof(SpriteSetModel::VERTEX);

        _pVertexBuffer_data = NEW SpriteSetModel::VERTEX[4 * _set_num];

        double du = 0.0;
        double dv = 0.0;
        //頂点配列情報をモデルに保持させる
        //UVは左上の１つ分（アニメパターン０）をデフォルトで設定する。
        //シェーダーが描画時にアニメパターン番号をみてUV座標をずらす仕様としよっと。
        //x,y の ÷2 とは、モデル中心をローカル座標の原点中心としたいため
        for (int i = 0; i < _set_num; i++) {
            //左上
            _pVertexBuffer_data[i*4 + 0].x = PX_DX(xdata.width)  / -2.0;
            _pVertexBuffer_data[i*4 + 0].y = PX_DX(xdata.height) /  2.0;
            _pVertexBuffer_data[i*4 + 0].z = 0.0f;
            _pVertexBuffer_data[i*4 + 0].nx = 0.0f;
            _pVertexBuffer_data[i*4 + 0].ny = 0.0f;
            _pVertexBuffer_data[i*4 + 0].nz = -1.0f;
            _pVertexBuffer_data[i*4 + 0].tu = (float)du;
            _pVertexBuffer_data[i*4 + 0].tv = (float)dv;
            _pVertexBuffer_data[i*4 + 0].index = (float)i;
            //右上
            _pVertexBuffer_data[i*4 + 1].x = PX_DX(xdata.width)  / 2.0;
            _pVertexBuffer_data[i*4 + 1].y = PX_DX(xdata.height) / 2.0;
            _pVertexBuffer_data[i*4 + 1].z = 0.0f;
            _pVertexBuffer_data[i*4 + 1].nx = 0.0f;
            _pVertexBuffer_data[i*4 + 1].ny = 0.0f;
            _pVertexBuffer_data[i*4 + 1].nz = -1.0f;
            _pVertexBuffer_data[i*4 + 1].tu = (float)((1.0 / xdata.col_texture_split) - du);
            _pVertexBuffer_data[i*4 + 1].tv = (float)dv;
            _pVertexBuffer_data[i*4 + 1].index = (float)i;
            //左下
            _pVertexBuffer_data[i*4 + 2].x = PX_DX(xdata.width)  / -2.0;
            _pVertexBuffer_data[i*4 + 2].y = PX_DX(xdata.height) / -2.0;
            _pVertexBuffer_data[i*4 + 2].z = 0.0f;
            _pVertexBuffer_data[i*4 + 2].nx = 0.0f;
            _pVertexBuffer_data[i*4 + 2].ny = 0.0f;
            _pVertexBuffer_data[i*4 + 2].nz = -1.0f;
            _pVertexBuffer_data[i*4 + 2].tu = (float)du;
            _pVertexBuffer_data[i*4 + 2].tv = (float)((1.0 / xdata.row_texture_split) - dv);
            _pVertexBuffer_data[i*4 + 2].index = (float)i;
            //右下
            _pVertexBuffer_data[i*4 + 3].x = PX_DX(xdata.width)  /  2.0;
            _pVertexBuffer_data[i*4 + 3].y = PX_DX(xdata.height) / -2.0;
            _pVertexBuffer_data[i*4 + 3].z = 0.0f;
            _pVertexBuffer_data[i*4 + 3].nx = 0.0f;
            _pVertexBuffer_data[i*4 + 3].ny = 0.0f;
            _pVertexBuffer_data[i*4 + 3].nz = -1.0f;
            _pVertexBuffer_data[i*4 + 3].tu = (float)((1.0 / xdata.col_texture_split) - du);
            _pVertexBuffer_data[i*4 + 3].tv = (float)((1.0 / xdata.row_texture_split) - dv);
            _pVertexBuffer_data[i*4 + 3].index = (float)i;

        }

        //距離
        FLOAT model_bounding_sphere_radius = (FLOAT)(sqrt(_pVertexBuffer_data[0].x * _pVertexBuffer_data[0].x +
                                                          _pVertexBuffer_data[0].y * _pVertexBuffer_data[0].y +
                                                          _pVertexBuffer_data[0].z * _pVertexBuffer_data[0].z));
        _bounding_sphere_radius = model_bounding_sphere_radius;
        //インデックスバッファデータ
        int nVertices = 4;
        int nFaces = 2;
        WORD* unit_paIdxBuffer = NEW WORD[(nFaces*3)];
        unit_paIdxBuffer[0] = 0;
        unit_paIdxBuffer[1] = 1;
        unit_paIdxBuffer[2] = 2;
        unit_paIdxBuffer[3] = 1;
        unit_paIdxBuffer[4] = 3;
        unit_paIdxBuffer[5] = 2;
        _pIndexBuffer_data = NEW WORD[(nFaces*3) * _set_num];
        for (int i = 0; i < _set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                _pIndexBuffer_data[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer[j*3 + 0] + (nVertices*i);
                _pIndexBuffer_data[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer[j*3 + 1] + (nVertices*i);
                _pIndexBuffer_data[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer[j*3 + 2] + (nVertices*i);
            }
        }
        GGAF_DELETEARR(unit_paIdxBuffer);


        //描画時パラメーター
        SpriteSetModel::INDEXPARAM* paIndexParam = NEW SpriteSetModel::INDEXPARAM[_set_num];
        for (int i = 0; i < _set_num; i++) {
            paIndexParam[i].MaterialNo = 0;
            paIndexParam[i].BaseVertexIndex = 0;
            paIndexParam[i].MinIndex = 0;
            paIndexParam[i].NumVertices = nVertices*(i+1);
            paIndexParam[i].StartIndex = 0;
            paIndexParam[i].PrimitiveCount = nFaces*(i+1);
        }
        _paIndexParam = paIndexParam;

        _num_materials = 1;
        D3DMATERIAL9* paMaterial = NEW D3DMATERIAL9[_num_materials];
        for ( DWORD i = 0; i < _num_materials; i++) {
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
    }
    if (_pVertexBuffer == nullptr) {
        HRESULT hr;
        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices * _set_num,
                D3DUSAGE_WRITEONLY,
                SpriteSetModel::FVF,
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
            _pVertexBuffer_data,
            _size_vertices* _set_num
        ); //pVertexBuffer ← _pVertexBuffer_data
        _pVertexBuffer->Unlock();

    }

    //インデックスバッファ作成
    if (_pIndexBuffer == nullptr) {
        HRESULT hr;
        int nVertices = 4;
        int nFaces = 2;
        hr = God::_pID3DDevice9->CreateIndexBuffer(
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
          _pIndexBuffer_data,
          sizeof(WORD) * nFaces * 3 * _set_num
        );
        _pIndexBuffer->Unlock();
    }

    if (_papTextureConnection == nullptr) {
        //テクスチャ取得しモデルに保持させる
        ModelManager* pModelManager = pGOD->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[1];
        _papTextureConnection[0] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
    }

    _TRACE3_("_model_name=" << _model_name << " end");
}

void SpriteSetModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void SpriteSetModel::release() {
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

    _TRACE3_("_model_name=" << _model_name << " end");
}

SpriteSetModel::~SpriteSetModel() {
    GGAF_DELETEARR(_pVertexBuffer_data);
    GGAF_DELETEARR(_pIndexBuffer_data);
    GGAF_DELETEARR(_paIndexParam);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
}

