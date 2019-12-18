#include "jp/ggaf/dx/model/BoardSetModel.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/effect/BoardSetEffect.h"
#include "jp/ggaf/dx/actor/BoardSetActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/texture/Texture.h"

#include "jp/ggaf/dx/manager/TextureManager.h"

#include "jp/ggaf/dx/model/MassModel.h"

using namespace GgafDx;

DWORD BoardSetModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_TEX1);
BoardSetModel::BoardSetModel(const char* prm_model_name) : Model(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _paVertexBuffer_data = nullptr;
    _pIndexBuffer_data = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _paIndexParam = nullptr;
    _obj_model |= Obj_GgafDx_BoardSetModel;

    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, ",");
    if (names.size() > 2) {
        throwCriticalException("prm_model_name には \"xxxxxx\" or \"8,xxxxx\" 形式を指定してください。 \n"
                                   "実際の引数は、prm_idstr="<<prm_model_name);
    }
    if (names.size() == 2) {
        _set_num = STOI(names[0]);
        if (_set_num > 28) {
            _TRACE_("BoardSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大の28がセットですが、それ以上のセット数です。意図していますか？_set_num="<<_set_num);
        }
    } else {
        _TRACE_("BoardSetModel("<<prm_model_name<<") の同時描画セット数省略のため、最大の28がセットされます。");
        _set_num = 28;
    }
}

HRESULT BoardSetModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("BoardSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        throwCriticalException(FUNC_NAME<<" "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    //対象Actor
    const BoardSetActor* const pTargetActor = (BoardSetActor*)prm_pActor_target;
    //対象BoardSetActorのエフェクトラッパ
    BoardSetEffect* const pBoardSetEffect = (BoardSetEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pBoardSetEffect->_pID3DXEffect;

    HRESULT hr;
    //モデルが同じならば頂点バッファ等、の設定はスキップできる
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(BoardSetModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_threshold, _blink_threshold);
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name<<"("<<pBoardSetEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pBoardSetEffect->_begin) {
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pBoardSetEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
    const INDEXPARAM& idxparam = _paIndexParam[prm_draw_set_num-1];
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                  idxparam.BaseVertexIndex,
                                  idxparam.MinIndex,
                                  idxparam.NumVertices,
                                  idxparam.StartIndex,
                                  idxparam.PrimitiveCount);

    //前回描画モデル保持
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pBoardSetEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
    return D3D_OK;
}

void BoardSetModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    if (_paVertexBuffer_data == nullptr) {
        if (4*_set_num > 65535) {
            throwCriticalException("頂点が 65535を超えたかもしれません。\n対象Model："<<getName()<<"  nVertices:4  セット数:"<<(_set_num));
        }

        _papTextureConnection = nullptr;
        ModelManager* pModelManager = pGOD->_pModelManager;
        std::string xfile_name; //読み込むスプライト定義ファイル名（Xファイル形式）
        //"12,Moji" or "8,Moji" or "Moji" から "Moji" だけ取とりだしてフルパス名取得。
        //TODO:数値3桁("123,Moji"とか)が来たら困る。
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

        //テクスチャ取得しモデルに保持させる
        _pa_texture_filenames = NEW std::string[1];
        _pa_texture_filenames[0] = std::string(xdata.texture_file);

        _size_vertices = sizeof(BoardSetModel::VERTEX)*4;
        _size_vertex_unit = sizeof(BoardSetModel::VERTEX);
        _paVertexBuffer_data = NEW BoardSetModel::VERTEX[4 * _set_num];

        //1pxあたりのuvの大きさを求める
//        float tex_width  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
//        float tex_height = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)
        double du = 0.0; //1.0 / tex_width  / 100000.0; //テクスチャの幅1pxの10000分の1px
        double dv = 0.0; //1.0 / tex_height / 100000.0; //テクスチャの高さ1pxの10000分の1px
        for (int i = 0; i < _set_num; i++) {
            //左上
            _paVertexBuffer_data[i*4 + 0].x = 0.0f;
            _paVertexBuffer_data[i*4 + 0].y = 0.0f;
            _paVertexBuffer_data[i*4 + 0].z = 0.0f;
            _paVertexBuffer_data[i*4 + 0].tu = (float)du;
            _paVertexBuffer_data[i*4 + 0].tv = (float)dv;
            _paVertexBuffer_data[i*4 + 0].index = (float)i;
            //右上
            _paVertexBuffer_data[i*4 + 1].x = xdata.width;
            _paVertexBuffer_data[i*4 + 1].y = 0.0f;
            _paVertexBuffer_data[i*4 + 1].z = 0.0f;
            _paVertexBuffer_data[i*4 + 1].tu = (float)((1.0 / xdata.col_texture_split) - du);
            _paVertexBuffer_data[i*4 + 1].tv = (float)dv;
            _paVertexBuffer_data[i*4 + 1].index = (float)i;
            //左下
            _paVertexBuffer_data[i*4 + 2].x = 0.0f;
            _paVertexBuffer_data[i*4 + 2].y = xdata.height;
            _paVertexBuffer_data[i*4 + 2].z = 0.0f;
            _paVertexBuffer_data[i*4 + 2].tu = (float)du;
            _paVertexBuffer_data[i*4 + 2].tv = (float)((1.0 / xdata.row_texture_split) - dv);
            _paVertexBuffer_data[i*4 + 2].index = (float)i;
            //右下
            _paVertexBuffer_data[i*4 + 3].x = xdata.width;
            _paVertexBuffer_data[i*4 + 3].y = xdata.height;
            _paVertexBuffer_data[i*4 + 3].z = 0.0f;
            _paVertexBuffer_data[i*4 + 3].tu = (float)((1.0 / xdata.col_texture_split) - du);
            _paVertexBuffer_data[i*4 + 3].tv = (float)((1.0 / xdata.row_texture_split) - dv);
            _paVertexBuffer_data[i*4 + 3].index = (float)i;
        }

        //描画時パラメーター
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

        BoardSetModel::INDEXPARAM* paIndexParam = NEW BoardSetModel::INDEXPARAM[_set_num];
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
        //バッファ作成
        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices * _set_num,
                D3DUSAGE_WRITEONLY,
                BoardSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));
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
          _paVertexBuffer_data,
          _size_vertices * _set_num
        ); //pVertexBuffer ← _paVertexBuffer_data
        _pVertexBuffer->Unlock();

    }


    //インデックスバッファ作成
    if (_pIndexBuffer == nullptr) {
        HRESULT hr;
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
        ModelManager* pModelManager = pGOD->_pModelManager;
        //テクスチャ取得しモデルに保持させる
        _papTextureConnection = NEW TextureConnection*[1];
        _papTextureConnection[0] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
    }

}

void BoardSetModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void BoardSetModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);
    //テクスチャを解放
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    //TODO:親クラスメンバをDELETEするのはややきたないか

    _TRACE3_("_model_name=" << _model_name << " end");
}

BoardSetModel::~BoardSetModel() {

    GGAF_DELETEARR(_paVertexBuffer_data);
    GGAF_DELETEARR(_pIndexBuffer_data);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    GGAF_DELETEARR(_paIndexParam);
    //release();
    //はModelConnection::processReleaseResource(Model* prm_pResource) で呼び出される
}

