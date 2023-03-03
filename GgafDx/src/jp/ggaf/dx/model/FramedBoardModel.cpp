#include "jp/ggaf/dx/model/FramedBoardModel.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/effect/FramedBoardEffect.h"
#include "jp/ggaf/dx/actor/FramedBoardActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"

using namespace GgafDx;

DWORD FramedBoardModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_TEX1);
FramedBoardModel::FramedBoardModel(const char* prm_model_id) : Model(prm_model_id), IPlaneModel() {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_FramedBoardModel | Obj_GgafDx_IPlaneModel;
    _paVertexBuffer_data = nullptr;
    _paIndexBuffer_data = nullptr;
    _model_frame_width_px = 32.0f;
    _model_frame_height_px = 32.0f;
    _row_frame_texture_split = 1;
    _col_frame_texture_split = 1;
    _paVertexBuffer = nullptr;
    _paIndexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _draw_set_num = 9;
    _max_draw_set_num = 9;
}

HRESULT FramedBoardModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("FramedBoardModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;
    //対象Actor
    const FramedBoardActor* const pTargetActor = (FramedBoardActor*)prm_pActor_target;
    //対象FramedBoardActorのエフェクトラッパ
    FramedBoardEffect* const pFramedBoardEffect = (FramedBoardEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pFramedBoardEffect->_pID3DXEffect;

    HRESULT hr;
    //モデルが同じならば頂点バッファ等、の設定はスキップできる
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _paVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(FramedBoardModel::FVF);
        pDevice->SetTexture(0, _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetTexture(1, _papTextureConnection[1]->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetIndices(_paIndexBuffer);

        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");

        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_center_width, _model_width_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_unit_width) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_center_height, _model_height_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_unit_height) に失敗しました。");

        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_frame_width, _model_frame_width_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_unit_width) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_frame_height, _model_frame_height_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_unit_height) に失敗しました。");

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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pFramedBoardEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pFramedBoardEffect->_effect_name<<"("<<pFramedBoardEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pFramedBoardEffect->_begin) {
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pFramedBoardEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pFramedBoardEffect->_effect_name);
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                    _indexParam.BaseVertexIndex,
                                    _indexParam.MinIndex,
                                    _indexParam.NumVertices,
                                    _indexParam.StartIndex,
                                    _indexParam.PrimitiveCount);
#ifdef MY_DEBUG
    GgafCore::Caretaker::_num_draw++;
#endif
    //前回描画モデル保持
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pFramedBoardEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void FramedBoardModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVertexBuffer_data == nullptr) {
        _papTextureConnection = nullptr;
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::ModelXFileFmt xdata;
        obtainMetaModelInfo(&xdata);
        if (_draw_set_num != 9) {
            _TRACE_("FramedBoardModel::restore() 本モデルの "<<_model_id<<" の同時描画セット数は 9 に上書きされました。（_draw_set_num="<<_draw_set_num<<" は無視されました。）");
            _draw_set_num = 9;
        }
        std::string fsprx_filepath = Model::getSpriteXFilePath(xdata.XFileNames[0]);
        ModelManager::FramedSpriteXFileFmt xdata_fspr;
        pModelManager->obtainFramedSpriteModelInfo(&xdata_fspr, fsprx_filepath);

        _model_width_px  = xdata_fspr.Width;
        _model_height_px = xdata_fspr.Height;
        _row_texture_split = xdata_fspr.TextureSplitRows;
        _col_texture_split = xdata_fspr.TextureSplitCols;
        _model_frame_width_px  = xdata_fspr.FrameWidth;
        _model_frame_height_px = xdata_fspr.FrameHeight;
        _row_frame_texture_split = xdata_fspr.FrameTextureSplitRows;
        _col_frame_texture_split = xdata_fspr.FrameTextureSplitCols;
        _pa_texture_filenames = NEW std::string[2];
        _pa_texture_filenames[0] = std::string(xdata_fspr.TextureFile);
        _pa_texture_filenames[1] = std::string(xdata_fspr.FrameTextureFile);

        _size_vertices = sizeof(FramedBoardModel::VERTEX)*4;
        _size_vertex_unit = sizeof(FramedBoardModel::VERTEX);
        _paVertexBuffer_data = NEW FramedBoardModel::VERTEX[4 * _draw_set_num];
        //    ┌─┬─┬─┐
        //    │０│１│２│
        //    ├─┼─┼─┤
        //    │３│４│５│
        //    ├─┼─┼─┤
        //    │６│７│８│
        //    └─┴─┴─┘

        //1pxあたりのuvの大きさを求める
        double du = 0.0;
        double dv = 0.0;
        for (int i = 0; i < _draw_set_num; i++) {
            if (i == 4) {
                //中心
                //左上
                _paVertexBuffer_data[i*4 + 0].x = 0.0f;
                _paVertexBuffer_data[i*4 + 0].y = 0.0f;
                _paVertexBuffer_data[i*4 + 0].z = 0.0f;
                _paVertexBuffer_data[i*4 + 0].tu = (float)du;
                _paVertexBuffer_data[i*4 + 0].tv = (float)dv;
                _paVertexBuffer_data[i*4 + 0].index = (float)i;
                //右上
                _paVertexBuffer_data[i*4 + 1].x = xdata_fspr.Width;
                _paVertexBuffer_data[i*4 + 1].y = 0.0f;
                _paVertexBuffer_data[i*4 + 1].z = 0.0f;
                _paVertexBuffer_data[i*4 + 1].tu = (float)((1.0 / xdata_fspr.TextureSplitCols) - du);
                _paVertexBuffer_data[i*4 + 1].tv = (float)dv;
                _paVertexBuffer_data[i*4 + 1].index = (float)i;
                //左下
                _paVertexBuffer_data[i*4 + 2].x = 0.0f;
                _paVertexBuffer_data[i*4 + 2].y = xdata_fspr.Height;
                _paVertexBuffer_data[i*4 + 2].z = 0.0f;
                _paVertexBuffer_data[i*4 + 2].tu = (float)du;
                _paVertexBuffer_data[i*4 + 2].tv = (float)((1.0 / xdata_fspr.TextureSplitRows) - dv);
                _paVertexBuffer_data[i*4 + 2].index = (float)i;
                //右下
                _paVertexBuffer_data[i*4 + 3].x = xdata_fspr.Width;
                _paVertexBuffer_data[i*4 + 3].y = xdata_fspr.Height;
                _paVertexBuffer_data[i*4 + 3].z = 0.0f;
                _paVertexBuffer_data[i*4 + 3].tu = (float)((1.0 / xdata_fspr.TextureSplitCols) - du);
                _paVertexBuffer_data[i*4 + 3].tv = (float)((1.0 / xdata_fspr.TextureSplitRows) - dv);
                _paVertexBuffer_data[i*4 + 3].index = (float)i;
            } else if (i == 0 || i == 2 || i == 6 || i == 8 ) {
                //４角
                //左上
                _paVertexBuffer_data[i*4 + 0].x = 0.0f;
                _paVertexBuffer_data[i*4 + 0].y = 0.0f;
                _paVertexBuffer_data[i*4 + 0].z = 0.0f;
                _paVertexBuffer_data[i*4 + 0].tu = (float)du;
                _paVertexBuffer_data[i*4 + 0].tv = (float)dv;
                _paVertexBuffer_data[i*4 + 0].index = (float)i;
                //右上
                _paVertexBuffer_data[i*4 + 1].x = xdata_fspr.FrameWidth;
                _paVertexBuffer_data[i*4 + 1].y = 0.0f;
                _paVertexBuffer_data[i*4 + 1].z = 0.0f;
                _paVertexBuffer_data[i*4 + 1].tu = (float)((1.0 / xdata_fspr.FrameTextureSplitCols) - du);
                _paVertexBuffer_data[i*4 + 1].tv = (float)dv;
                _paVertexBuffer_data[i*4 + 1].index = (float)i;
                //左下
                _paVertexBuffer_data[i*4 + 2].x = 0.0f;
                _paVertexBuffer_data[i*4 + 2].y = xdata_fspr.FrameHeight;
                _paVertexBuffer_data[i*4 + 2].z = 0.0f;
                _paVertexBuffer_data[i*4 + 2].tu = (float)du;
                _paVertexBuffer_data[i*4 + 2].tv = (float)((1.0 / xdata_fspr.FrameTextureSplitRows) - dv);
                _paVertexBuffer_data[i*4 + 2].index = (float)i;
                //右下
                _paVertexBuffer_data[i*4 + 3].x = xdata_fspr.FrameWidth;
                _paVertexBuffer_data[i*4 + 3].y = xdata_fspr.FrameHeight;
                _paVertexBuffer_data[i*4 + 3].z = 0.0f;
                _paVertexBuffer_data[i*4 + 3].tu = (float)((1.0 / xdata_fspr.FrameTextureSplitCols) - du);
                _paVertexBuffer_data[i*4 + 3].tv = (float)((1.0 / xdata_fspr.FrameTextureSplitRows) - dv);
                _paVertexBuffer_data[i*4 + 3].index = (float)i;
            } else if (i == 1 || i == 7) {
                //縦の真ん中
                //左上
                _paVertexBuffer_data[i*4 + 0].x = 0.0f;
                _paVertexBuffer_data[i*4 + 0].y = 0.0f;
                _paVertexBuffer_data[i*4 + 0].z = 0.0f;
                _paVertexBuffer_data[i*4 + 0].tu = (float)du;
                _paVertexBuffer_data[i*4 + 0].tv = (float)dv;
                _paVertexBuffer_data[i*4 + 0].index = (float)i;
                //右上
                _paVertexBuffer_data[i*4 + 1].x = xdata_fspr.Width;
                _paVertexBuffer_data[i*4 + 1].y = 0.0f;
                _paVertexBuffer_data[i*4 + 1].z = 0.0f;
                _paVertexBuffer_data[i*4 + 1].tu = (float)((1.0 / xdata_fspr.FrameTextureSplitCols) - du);
                _paVertexBuffer_data[i*4 + 1].tv = (float)dv;
                _paVertexBuffer_data[i*4 + 1].index = (float)i;
                //左下
                _paVertexBuffer_data[i*4 + 2].x = 0.0f;
                _paVertexBuffer_data[i*4 + 2].y = xdata_fspr.FrameHeight;
                _paVertexBuffer_data[i*4 + 2].z = 0.0f;
                _paVertexBuffer_data[i*4 + 2].tu = (float)du;
                _paVertexBuffer_data[i*4 + 2].tv = (float)((1.0 / xdata_fspr.FrameTextureSplitRows) - dv);
                _paVertexBuffer_data[i*4 + 2].index = (float)i;
                //右下
                _paVertexBuffer_data[i*4 + 3].x = xdata_fspr.Width;
                _paVertexBuffer_data[i*4 + 3].y = xdata_fspr.FrameHeight;
                _paVertexBuffer_data[i*4 + 3].z = 0.0f;
                _paVertexBuffer_data[i*4 + 3].tu = (float)((1.0 / xdata_fspr.FrameTextureSplitCols) - du);
                _paVertexBuffer_data[i*4 + 3].tv = (float)((1.0 / xdata_fspr.FrameTextureSplitRows) - dv);
                _paVertexBuffer_data[i*4 + 3].index = (float)i;
            } else if (i == 3 || i == 5) {
                //横の真ん中
                //左上
                _paVertexBuffer_data[i*4 + 0].x = 0.0f;
                _paVertexBuffer_data[i*4 + 0].y = 0.0f;
                _paVertexBuffer_data[i*4 + 0].z = 0.0f;
                _paVertexBuffer_data[i*4 + 0].tu = (float)du;
                _paVertexBuffer_data[i*4 + 0].tv = (float)dv;
                _paVertexBuffer_data[i*4 + 0].index = (float)i;
                //右上
                _paVertexBuffer_data[i*4 + 1].x = xdata_fspr.FrameWidth;
                _paVertexBuffer_data[i*4 + 1].y = 0.0f;
                _paVertexBuffer_data[i*4 + 1].z = 0.0f;
                _paVertexBuffer_data[i*4 + 1].tu = (float)((1.0 / xdata_fspr.FrameTextureSplitCols) - du);
                _paVertexBuffer_data[i*4 + 1].tv = (float)dv;
                _paVertexBuffer_data[i*4 + 1].index = (float)i;
                //左下
                _paVertexBuffer_data[i*4 + 2].x = 0.0f;
                _paVertexBuffer_data[i*4 + 2].y = xdata_fspr.Height;
                _paVertexBuffer_data[i*4 + 2].z = 0.0f;
                _paVertexBuffer_data[i*4 + 2].tu = (float)du;
                _paVertexBuffer_data[i*4 + 2].tv = (float)((1.0 / xdata_fspr.FrameTextureSplitRows) - dv);
                _paVertexBuffer_data[i*4 + 2].index = (float)i;
                //右下
                _paVertexBuffer_data[i*4 + 3].x = xdata_fspr.FrameWidth;
                _paVertexBuffer_data[i*4 + 3].y = xdata_fspr.Height;
                _paVertexBuffer_data[i*4 + 3].z = 0.0f;
                _paVertexBuffer_data[i*4 + 3].tu = (float)((1.0 / xdata_fspr.FrameTextureSplitCols) - du);
                _paVertexBuffer_data[i*4 + 3].tv = (float)((1.0 / xdata_fspr.FrameTextureSplitRows) - dv);
                _paVertexBuffer_data[i*4 + 3].index = (float)i;
            }
        }

        int nVertices = 4;
        int nFaces = 2;
        WORD* unit_paIdxBuffer = NEW WORD[(nFaces*3)];
        unit_paIdxBuffer[0] = 0;
        unit_paIdxBuffer[1] = 1;
        unit_paIdxBuffer[2] = 2;
        unit_paIdxBuffer[3] = 1;
        unit_paIdxBuffer[4] = 3;
        unit_paIdxBuffer[5] = 2;
        _paIndexBuffer_data = NEW WORD[(nFaces*3) * _draw_set_num];
        for (int i = 0; i < _draw_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                _paIndexBuffer_data[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer[j*3 + 0] + (nVertices*i);
                _paIndexBuffer_data[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer[j*3 + 1] + (nVertices*i);
                _paIndexBuffer_data[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer[j*3 + 2] + (nVertices*i);
            }
        }
        GGAF_DELETEARR(unit_paIdxBuffer);

        //描画時パラメーター
        _indexParam.MaterialNo = 0;
        _indexParam.BaseVertexIndex = 0;
        _indexParam.MinIndex = 0;
        _indexParam.NumVertices = nVertices*_draw_set_num;
        _indexParam.StartIndex = 0;
        _indexParam.PrimitiveCount = nFaces*_draw_set_num;


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


    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        //バッファ作成
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices * _draw_set_num,
                D3DUSAGE_WRITEONLY,
                FramedBoardModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_paVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_id));
        //頂点バッファ作成
        //頂点情報をビデオカード頂点バッファへロード
        void* paVertexBuffer;
        hr = _paVertexBuffer->Lock(
                                 0,
                                 _size_vertices * _draw_set_num,
                                 (void**)&paVertexBuffer,
                                 0
                               );
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_id);
        memcpy(
          paVertexBuffer,
          _paVertexBuffer_data,
          _size_vertices * _draw_set_num
        ); //paVertexBuffer ← _paVertexBuffer_data
        _paVertexBuffer->Unlock();

    }


    //インデックスバッファ作成
    if (_paIndexBuffer == nullptr) {
        HRESULT hr;
        int nVertices = 4;
        int nFaces = 2;
        hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * nFaces * 3 * _draw_set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_paIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_id));

        void* paIndexBuffer;
        _paIndexBuffer->Lock(0,0,(void**)&paIndexBuffer,0);
        memcpy(
          paIndexBuffer ,
          _paIndexBuffer_data,
          sizeof(WORD) * nFaces * 3 * _draw_set_num
        );
        _paIndexBuffer->Unlock();
    }

    if (_papTextureConnection == nullptr) {
        //テクスチャ取得しモデルに保持させる
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[2];
        _papTextureConnection[0] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this)); //中身用
        _papTextureConnection[1] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[1].c_str(), this)); //フレーム用
    }
}

void FramedBoardModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void FramedBoardModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    GGAF_RELEASE(_paVertexBuffer);
    GGAF_RELEASE(_paIndexBuffer);
    //テクスチャを解放
    if (_papTextureConnection) {
        _papTextureConnection[0]->close();
        _papTextureConnection[1]->close(); //フレーム
    }
    GGAF_DELETEARR(_papTextureConnection);
    _TRACE3_("_model_id=" << _model_id << " end");
}

FramedBoardModel::~FramedBoardModel() {
    GGAF_DELETEARR(_paVertexBuffer_data);
    GGAF_DELETEARR(_paIndexBuffer_data);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    //release();
    //はModelConnection::processReleaseResource(Model* prm_pResource) で呼び出される
}

