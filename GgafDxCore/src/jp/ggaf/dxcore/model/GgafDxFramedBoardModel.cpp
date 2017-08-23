#include "jp/ggaf/dxcore/model/GgafDxFramedBoardModel.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxFramedBoardEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxFramedBoardActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"

#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxFramedBoardModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_TEX1);
GgafDxFramedBoardModel::GgafDxFramedBoardModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _model_frame_width_px = 32.0f;
    _model_frame_height_px = 32.0f;
    _row_frame_texture_split = 1;
    _col_frame_texture_split = 1;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _obj_model |= Obj_GgafDxFramedBoardModel;

//    std::string model_name = std::string(prm_model_name);
//    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
//    if (names.size() > 2) {
//        throwGgafCriticalException("prm_model_name には \"xxxxxx\" or \"8/xxxxx\" 形式を指定してください。 \n"<<
//                                   "実際の引数は、prm_idstr="<<prm_model_name);
//    }
    _set_num = 9;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreFramedBoardModel(GgafDxFramedBoardModel*)
    //で行うようにした。要参照。
}

HRESULT GgafDxFramedBoardModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("GgafDxFramedBoardModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //対象Actor
    const GgafDxFramedBoardActor* const pTargetActor = (GgafDxFramedBoardActor*)prm_pActor_target;
    //対象FramedBoardActorのエフェクトラッパ
    GgafDxFramedBoardEffect* const pFramedBoardEffect = (GgafDxFramedBoardEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pFramedBoardEffect->_pID3DXEffect;

    HRESULT hr;
    //モデルが同じならば頂点バッファ等、の設定はスキップできる
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxFramedBoardModel::FVF);
        pDevice->SetTexture(0, _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetTexture(1, _papTextureConnection[1]->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetIndices(_pIndexBuffer);

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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pFramedBoardEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pFramedBoardEffect->_effect_name<<"("<<pFramedBoardEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pFramedBoardEffect->_begin) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pFramedBoardEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pFramedBoardEffect->_effect_name);
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                    _indexParam.BaseVertexIndex,
                                    _indexParam.MinIndex,
                                    _indexParam.NumVertices,
                                    _indexParam.StartIndex,
                                    _indexParam.PrimitiveCount);

    //前回描画モデル保持
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pFramedBoardEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif

    return D3D_OK;
}

void GgafDxFramedBoardModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    _set_num = 9;
    _papTextureConnection = nullptr;
    HRESULT hr;

    std::string xfile_name = GgafDxModelManager::getSpriteFileName(_model_name);
    GgafDxModelManager::SpriteXFileFmt xdata;
    GgafDxModelManager::obtainSpriteInfo(&xdata, xfile_name);
    _model_width_px  = xdata.width;
    _model_height_px = xdata.height;
    _row_texture_split = xdata.row_texture_split;
    _col_texture_split = xdata.col_texture_split;

    std::string xfile_name_frame = GgafDxModelManager::getSpriteFileName(std::string(_model_name)+"_frame");
    GgafDxModelManager::SpriteXFileFmt xdata_frame;
    GgafDxModelManager::obtainSpriteInfo(&xdata_frame, xfile_name_frame);
    _model_frame_width_px  = xdata_frame.width;
    _model_frame_height_px = xdata_frame.height;
    _row_frame_texture_split = xdata_frame.row_texture_split;
    _col_frame_texture_split = xdata_frame.col_texture_split;



    //テクスチャ取得しモデルに保持させる
    GgafDxTextureConnection* model_pTextureConnection = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(xdata.texture_file, this));
    GgafDxTextureConnection* model_frame_pTextureConnection = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(xdata_frame.texture_file, this));

    //テクスチャの参照を保持させる。
    _papTextureConnection = NEW GgafDxTextureConnection*[2];
    _papTextureConnection[0] = model_pTextureConnection;
    _papTextureConnection[1] = model_frame_pTextureConnection;

    if (_pVertexBuffer == nullptr) {

        _size_vertices = sizeof(GgafDxFramedBoardModel::VERTEX)*4;
        _size_vertex_unit = sizeof(GgafDxFramedBoardModel::VERTEX);
        GgafDxFramedBoardModel::VERTEX* paVertex = NEW GgafDxFramedBoardModel::VERTEX[4 * _set_num];
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
        for (int i = 0; i < _set_num; i++) {
            if (i == 4) {
                //中心
                //左上
                paVertex[i*4 + 0].x = 0.0f;
                paVertex[i*4 + 0].y = 0.0f;
                paVertex[i*4 + 0].z = 0.0f;
                paVertex[i*4 + 0].tu = (float)du;
                paVertex[i*4 + 0].tv = (float)dv;
                paVertex[i*4 + 0].index = (float)i;
                //右上
                paVertex[i*4 + 1].x = xdata.width;
                paVertex[i*4 + 1].y = 0.0f;
                paVertex[i*4 + 1].z = 0.0f;
                paVertex[i*4 + 1].tu = (float)((1.0 / xdata.col_texture_split) - du);
                paVertex[i*4 + 1].tv = (float)dv;
                paVertex[i*4 + 1].index = (float)i;
                //左下
                paVertex[i*4 + 2].x = 0.0f;
                paVertex[i*4 + 2].y = xdata.height;
                paVertex[i*4 + 2].z = 0.0f;
                paVertex[i*4 + 2].tu = (float)du;
                paVertex[i*4 + 2].tv = (float)((1.0 / xdata.row_texture_split) - dv);
                paVertex[i*4 + 2].index = (float)i;
                //右下
                paVertex[i*4 + 3].x = xdata.width;
                paVertex[i*4 + 3].y = xdata.height;
                paVertex[i*4 + 3].z = 0.0f;
                paVertex[i*4 + 3].tu = (float)((1.0 / xdata.col_texture_split) - du);
                paVertex[i*4 + 3].tv = (float)((1.0 / xdata.row_texture_split) - dv);
                paVertex[i*4 + 3].index = (float)i;
            } else if (i == 0 || i == 2 || i == 6 || i == 8 ) {
                //４角
                //左上
                paVertex[i*4 + 0].x = 0.0f;
                paVertex[i*4 + 0].y = 0.0f;
                paVertex[i*4 + 0].z = 0.0f;
                paVertex[i*4 + 0].tu = (float)du;
                paVertex[i*4 + 0].tv = (float)dv;
                paVertex[i*4 + 0].index = (float)i;
                //右上
                paVertex[i*4 + 1].x = xdata_frame.width;
                paVertex[i*4 + 1].y = 0.0f;
                paVertex[i*4 + 1].z = 0.0f;
                paVertex[i*4 + 1].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 1].tv = (float)dv;
                paVertex[i*4 + 1].index = (float)i;
                //左下
                paVertex[i*4 + 2].x = 0.0f;
                paVertex[i*4 + 2].y = xdata_frame.height;
                paVertex[i*4 + 2].z = 0.0f;
                paVertex[i*4 + 2].tu = (float)du;
                paVertex[i*4 + 2].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 2].index = (float)i;
                //右下
                paVertex[i*4 + 3].x = xdata_frame.width;
                paVertex[i*4 + 3].y = xdata_frame.height;
                paVertex[i*4 + 3].z = 0.0f;
                paVertex[i*4 + 3].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 3].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 3].index = (float)i;
            } else if (i == 1 || i == 7) {
                //縦の真ん中
                //左上
                paVertex[i*4 + 0].x = 0.0f;
                paVertex[i*4 + 0].y = 0.0f;
                paVertex[i*4 + 0].z = 0.0f;
                paVertex[i*4 + 0].tu = (float)du;
                paVertex[i*4 + 0].tv = (float)dv;
                paVertex[i*4 + 0].index = (float)i;
                //右上
                paVertex[i*4 + 1].x = xdata.width;
                paVertex[i*4 + 1].y = 0.0f;
                paVertex[i*4 + 1].z = 0.0f;
                paVertex[i*4 + 1].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 1].tv = (float)dv;
                paVertex[i*4 + 1].index = (float)i;
                //左下
                paVertex[i*4 + 2].x = 0.0f;
                paVertex[i*4 + 2].y = xdata_frame.height;
                paVertex[i*4 + 2].z = 0.0f;
                paVertex[i*4 + 2].tu = (float)du;
                paVertex[i*4 + 2].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 2].index = (float)i;
                //右下
                paVertex[i*4 + 3].x = xdata.width;
                paVertex[i*4 + 3].y = xdata_frame.height;
                paVertex[i*4 + 3].z = 0.0f;
                paVertex[i*4 + 3].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 3].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 3].index = (float)i;
            } else if (i == 3 || i == 5) {
                //横の真ん中
                //左上
                paVertex[i*4 + 0].x = 0.0f;
                paVertex[i*4 + 0].y = 0.0f;
                paVertex[i*4 + 0].z = 0.0f;
                paVertex[i*4 + 0].tu = (float)du;
                paVertex[i*4 + 0].tv = (float)dv;
                paVertex[i*4 + 0].index = (float)i;
                //右上
                paVertex[i*4 + 1].x = xdata_frame.width;
                paVertex[i*4 + 1].y = 0.0f;
                paVertex[i*4 + 1].z = 0.0f;
                paVertex[i*4 + 1].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 1].tv = (float)dv;
                paVertex[i*4 + 1].index = (float)i;
                //左下
                paVertex[i*4 + 2].x = 0.0f;
                paVertex[i*4 + 2].y = xdata.height;
                paVertex[i*4 + 2].z = 0.0f;
                paVertex[i*4 + 2].tu = (float)du;
                paVertex[i*4 + 2].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 2].index = (float)i;
                //右下
                paVertex[i*4 + 3].x = xdata_frame.width;
                paVertex[i*4 + 3].y = xdata.height;
                paVertex[i*4 + 3].z = 0.0f;
                paVertex[i*4 + 3].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 3].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 3].index = (float)i;
            }
         }

        //バッファ作成
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices * _set_num,
                D3DUSAGE_WRITEONLY,
                GgafDxFramedBoardModel::FVF,
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
          paVertex,
          _size_vertices * _set_num
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
        _indexParam.MaterialNo = 0;
        _indexParam.BaseVertexIndex = 0;
        _indexParam.MinIndex = 0;
        _indexParam.NumVertices = nVertices*_set_num;
        _indexParam.StartIndex = 0;
        _indexParam.PrimitiveCount = nFaces*_set_num;
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
}

void GgafDxFramedBoardModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxFramedBoardModel::release() {
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
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_name=" << _model_name << " end");
}

GgafDxFramedBoardModel::~GgafDxFramedBoardModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

