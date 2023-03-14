#include "jp/ggaf/dx/model/PointSpriteSetModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/PointSpriteSetActor.h"
#include "jp/ggaf/dx/effect/PointSpriteSetEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"

#define POINTSPRITESETMODEL_MAX_DARW_SET_NUM 15

using namespace GgafDx;

DWORD PointSpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer = nullptr;

PointSpriteSetModel::PointSpriteSetModel(const char* prm_model_id) : Model(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_PointSpriteSetModel;
    _paVertexBuffer = nullptr;
    _paVtxBuffer_data = nullptr;
    _square_size_px = 0.0f;
    _texture_size_px = 0.0f;
    _texture_split_rowcol = 1;
    _inv_texture_split_rowcol = 1.0f / _texture_split_rowcol;
    _size_vertices = 0;
    _size_vertex_unit= 0;
    _nVertices = 0;
    _max_draw_set_num = POINTSPRITESETMODEL_MAX_DARW_SET_NUM;
}

HRESULT PointSpriteSetModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("PointSpriteSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _draw_set_num) {
        _TRACE_(FUNC_NAME<<" "<<_model_id<<" の描画セット数オーバー。_draw_set_num="<<_draw_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* pDevice = pCARETAKER->_pID3DDevice9;
    //対象アクター
    const PointSpriteSetActor* pTargetActor = (PointSpriteSetActor*)prm_pActor_target;
    //対象PointSpriteSetActorのエフェクトラッパ
    PointSpriteSetEffect* pPointSpriteSetEffect = (PointSpriteSetEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pPointSpriteSetEffect->_pID3DXEffect;

    HRESULT hr;
    //モデルが同じでかつ、セット数も同じならば頂点バッファ、インデックスバッファの設定はスキップできる
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //頂点バッファとインデックスバッファを設定
        pDevice->SetStreamSource(0, _paVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(PointSpriteSetModel::FVF);
        if (_papTextureConnection[0]) {
            hr = pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("PointSpriteSetModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(CONFIG::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
            //無ければテクスチャ無し
            hr = pDevice->SetTexture(0, nullptr);
        }
        pDevice->SetIndices(nullptr);

        hr = pID3DXEffect->SetFloat(pPointSpriteSetEffect->_hTexSize, _texture_size_px);
        checkDxException(hr, D3D_OK, "SetFloat(_hTexSize) に失敗しました。");
        hr = pID3DXEffect->SetInt(pPointSpriteSetEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hTextureSplitRowcol) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pPointSpriteSetEffect->_hInvTextureSplitRowcol, _inv_texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hInvTextureSplitRowcol) に失敗しました。");
    }

    Effect* pEffect_active = EffectManager::_pEffect_active;
    if (FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pPointSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pPointSpriteSetEffect->_effect_name<<"("<<pPointSpriteSetEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pPointSpriteSetEffect->_begin) {
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pPointSpriteSetEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pPointSpriteSetEffect->_effect_name);
    hr = pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _nVertices*prm_draw_set_num);
    checkDxException(hr, D3D_OK, " pass=1 に失敗しました。");
#ifdef MY_DEBUG
        GgafCore::Caretaker::_num_draw++;
#endif
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pPointSpriteSetEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void PointSpriteSetModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVtxBuffer_data == nullptr) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::ModelXFileFmt xdata;
        obtainMetaModelInfo(&xdata);
        std::string psprx_filepath = Model::getPointSpriteXFilePath(xdata.XFileNames[0]);
        ModelManager::PointSpriteXFileFmt xdata_pspr;
        pModelManager->obtainPointSpriteModelInfo(&xdata_pspr, psprx_filepath);
        //マテリアル定義が１つも無いので、描画のために無理やり１つマテリアルを作成。
//        _num_materials = 1; ////setMaterial();で実行済み
        setMaterial();
//        _pa_texture_filenames = NEW std::string[1]; ////setMaterial();で実行済み
        _pa_texture_filenames[0] = std::string(xdata_pspr.TextureFile);
        //デバイスにテクスチャ作成 (下にも同じ処理があるが、下はデバイスロスト時実行)
        //頂点バッファのpsizeの算出に、テクスチャの長さが必要なため、ここで一旦求めている
        if (_papTextureConnection == nullptr) {
            _papTextureConnection = NEW TextureConnection*[1];
            _papTextureConnection[0] =
                (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
        }

        Texture* pTex = _papTextureConnection[0]->peek();
        float tex_width  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
        float tex_height = (float)(pTex->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)幅と同じになる
        if ((int)(tex_width*100000) != (int)(tex_height*100000)) {
            throwCriticalException("ポイントスプライト用テクスチャ["<<pTex->getName()<<"]("<<tex_width<<"x"<<tex_height<<")は、正方形である必要があります。");
        }
        _texture_size_px = tex_width;
        _square_size_px = xdata_pspr.SquareSize;
        _texture_split_rowcol = xdata_pspr.TextureSplitRowCol;
        _inv_texture_split_rowcol = 1.0f / _texture_split_rowcol;
        _nVertices = xdata_pspr.VerticesNum;
        _draw_set_num = xdata_pspr.DrawSetNum;
        if (_draw_set_num == 0 || _draw_set_num > _max_draw_set_num) {
            _TRACE_("PointSpriteSetModel::restore() "<<_model_id<<" の同時描画セット数は、最大の "<<_max_draw_set_num<<" に再定義されました。理由：_draw_set_num="<<_draw_set_num);
            _draw_set_num = _max_draw_set_num;
        } else {
            _TRACE_("PointSpriteSetModel::restore() "<<_model_id<<" の同時描画セット数は "<<_draw_set_num<<" です。");
        }

//        if (_nVertices*_draw_set_num > 65535) {
//            throwCriticalException("PointSpriteSetModel::restore() 頂点インデックスが 65535 を超えたかもしれません。\n対象Model："<<getName()<<"  _nVertices*_draw_set_num:"<<_nVertices*_draw_set_num);
//        }
//        _nFaces = 0; //_nFacesは使用しない
        _paVtxBuffer_data = NEW PointSpriteSetModel::VERTEX[_nVertices*_draw_set_num];
        _size_vertex_unit = sizeof(PointSpriteSetModel::VERTEX);
        _size_vertices = sizeof(PointSpriteSetModel::VERTEX) * _nVertices*_draw_set_num;

        for (UINT i = 0; i < _nVertices; i++) {
            _paVtxBuffer_data[i].x = xdata_pspr.paD3DVECTOR_Vertices[i].x;
            _paVtxBuffer_data[i].y = xdata_pspr.paD3DVECTOR_Vertices[i].y;
            _paVtxBuffer_data[i].z = xdata_pspr.paD3DVECTOR_Vertices[i].z;

            _paVtxBuffer_data[i].psize = (_square_size_px*_texture_split_rowcol / _texture_size_px) * xdata_pspr.paFLOAT_InitScale[i]; //PSIZEにはピクセルサイズではなく倍率を埋め込む。
            //シェーダーで拡大縮小ピクセルを計算
            _paVtxBuffer_data[i].color = D3DCOLOR_COLORVALUE(xdata_pspr.paD3DVECTOR_VertexColors[i].r,
                                                             xdata_pspr.paD3DVECTOR_VertexColors[i].g,
                                                             xdata_pspr.paD3DVECTOR_VertexColors[i].b,
                                                             xdata_pspr.paD3DVECTOR_VertexColors[i].a );
            _paVtxBuffer_data[i].ini_ptn_no = (float)(xdata_pspr.paInt_InitUvPtnNo[i]); //頂点スプライトのUVパターン番号
            _paVtxBuffer_data[i].index = 0; //頂点番号（むりやり埋め込み）
        }
        transformPosVtx(_paVtxBuffer_data, _size_vertex_unit, _nVertices);

        //距離
        FLOAT model_bounding_sphere_radius;
        for (UINT i = 0; i < _nVertices; i++) {
            model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data[i].x * _paVtxBuffer_data[i].x +
                                                        _paVtxBuffer_data[i].y * _paVtxBuffer_data[i].y +
                                                        _paVtxBuffer_data[i].z * _paVtxBuffer_data[i].z  )
                                                   + (((_square_size_px/PX_UNIT) * 1.41421356 ) / 2.0)
                                                 );
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }
        //set分繰り返し挿入
        for (int n = 1; n < _draw_set_num; n++) {
            int os = n*_nVertices;
            for (UINT i = 0; i < _nVertices; i++) {
                _paVtxBuffer_data[os+i].x = _paVtxBuffer_data[i].x;
                _paVtxBuffer_data[os+i].y = _paVtxBuffer_data[i].y;
                _paVtxBuffer_data[os+i].z = _paVtxBuffer_data[i].z;
                _paVtxBuffer_data[os+i].psize = _paVtxBuffer_data[i].psize;
                _paVtxBuffer_data[os+i].color = _paVtxBuffer_data[i].color;
                _paVtxBuffer_data[os+i].ini_ptn_no = _paVtxBuffer_data[i].ini_ptn_no;
                _paVtxBuffer_data[os+i].index = n; //頂点番号（むりやり埋め込み）
            }
        }

        transformPosVtx(_paVtxBuffer_data, _size_vertex_unit, _nVertices*_draw_set_num);

    }

    //デバイスに頂点バッファ作成(モデル)
    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        //頂点バッファ作成
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS,
                PointSpriteSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT D3DPOOL_MANAGED
                &(_paVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_id));
        //バッファへ作成済み頂点データを流し込む
        void* pDeviceMemory = 0;
        hr = _paVertexBuffer->Lock(0, _size_vertices, (void**)&pDeviceMemory, 0);
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_id);
        memcpy(pDeviceMemory, _paVtxBuffer_data, _size_vertices);
        hr = _paVertexBuffer->Unlock();
        checkDxException(hr, D3D_OK, "頂点バッファのアンロック取得に失敗 model="<<_model_id);
    }

    //デバイスにテクスチャ作成
    if (_papTextureConnection == nullptr) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[1];
        _papTextureConnection[0] =
            (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
    }

//    //インデックスバッファは使わない
//    _paIndexBuffer = nullptr;

    _TRACE3_("_model_id=" << _model_id << " end");
}

void PointSpriteSetModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void PointSpriteSetModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");

    //テクスチャを解放
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //テクスチャの配列
    GGAF_RELEASE(_paVertexBuffer);
    _TRACE3_("_model_id=" << _model_id << " end");

}
PointSpriteSetModel::~PointSpriteSetModel() {
    GGAF_DELETEARR(_paVtxBuffer_data);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
}

