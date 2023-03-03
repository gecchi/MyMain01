#include "jp/ggaf/dx/model/PointSpriteModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/actor/PointSpriteActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/PointSpriteEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;

DWORD PointSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1);

PointSpriteModel::PointSpriteModel(const char* prm_model_id) : Model(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_PointSpriteModel;
    _paVertexBuffer = nullptr;
    _paVtxBuffer_data = nullptr;
    _vertices_num = 0;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _square_size_px = 0.0f;
    _texture_size_px = 0.0f;
    _texture_split_rowcol = 1;
    _inv_texture_split_rowcol = 1.0f / _texture_split_rowcol;
    _max_draw_set_num = 1;
}

HRESULT PointSpriteModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;
    _TRACE4_("PointSpriteModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());

    //対象Actor
    const PointSpriteActor* const pTargetActor = (PointSpriteActor*)prm_pActor_target;
    //対象PointSpriteActorのエフェクトラッパ
    PointSpriteEffect* const pPointSpriteEffect = (PointSpriteEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pPointSpriteEffect->_pID3DXEffect;

    //今回描画のUV
    HRESULT hr;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _paVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(PointSpriteModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_hTexSize, _texture_size_px);
        checkDxException(hr, D3D_OK, "SetFloat(_hTexSize) に失敗しました。");
        hr = pID3DXEffect->SetInt(pPointSpriteEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hTextureSplitRowcol) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_hInvTextureSplitRowcol, _inv_texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hInvTextureSplitRowcol) に失敗しました。");
        hr = pID3DXEffect->SetValue(pPointSpriteEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pPointSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pPointSpriteEffect->_effect_name<<"("<<pPointSpriteEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pPointSpriteEffect->_begin) {
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pPointSpriteEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pPointSpriteEffect->_effect_name);
    pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _vertices_num);
#ifdef MY_DEBUG
    GgafCore::Caretaker::_num_draw++;
#endif
    //前回描画モデル保持
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pPointSpriteEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void PointSpriteModel::restore() {
    _TRACE3_("_model_id="<<_model_id);
    _papTextureConnection = nullptr;

    if (_paVtxBuffer_data == nullptr) {

        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::ModelXFileFmt xdata;
        obtainMetaModelInfo(&xdata);
        std::string psprx_filepath = Model::getPointSpriteXFilePath(xdata.XFileNames[0]);
        ModelManager::PointSpriteXFileFmt xdata_pspr;
        pModelManager->obtainPointSpriteModelInfo(&xdata_pspr, psprx_filepath);
        if (_draw_set_num != 1) {
            _TRACE_("PointSpriteModel::restore() 本モデルの "<<_model_id<<" の同時描画セット数は 1 に上書きされました。（_draw_set_num="<<_draw_set_num<<" は無視されました。）");
            _draw_set_num = 1;
        }
        //退避
        float square_size_px = xdata_pspr.SquareSize;
        int texture_split_rowcol = xdata_pspr.TextureSplitRowCol;
        int vertices_num = xdata_pspr.VerticesNum;
        _TRACE3_("vertices_num="<<vertices_num);
        UINT size_vertices = sizeof(PointSpriteModel::VERTEX)*vertices_num;
        UINT size_vertex_unit = sizeof(PointSpriteModel::VERTEX);

        _pa_texture_filenames = NEW std::string[1];
        _pa_texture_filenames[0] = std::string(xdata_pspr.TextureFile);
        if (_papTextureConnection == nullptr) {
            //テクスチャ取得しモデルに保持させる
            _papTextureConnection = NEW TextureConnection*[1];
            _papTextureConnection[0] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str() , this));
        }
        Texture* pTex = _papTextureConnection[0]->peek();
        float tex_width  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
        float tex_height = (float)(pTex->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)幅と同じになる
        if ((int)(tex_width*100000) != (int)(tex_height*100000)) {
            throwCriticalException("ポイントスプライト用テクスチャ["<<pTex->getName()<<"]("<<tex_width<<"x"<<tex_height<<")は、正方形である必要があります。");
        }

        //頂点バッファ作成
        PointSpriteModel::VERTEX* paVtxBuffer_data = NEW PointSpriteModel::VERTEX[vertices_num];

        for (int i = 0; i < vertices_num; i++) {
            paVtxBuffer_data[i].x = xdata_pspr.paD3DVECTOR_Vertices[i].x;
            paVtxBuffer_data[i].y = xdata_pspr.paD3DVECTOR_Vertices[i].y;
            paVtxBuffer_data[i].z = xdata_pspr.paD3DVECTOR_Vertices[i].z;
            paVtxBuffer_data[i].psize = (square_size_px*texture_split_rowcol / tex_width) * xdata_pspr.paFLOAT_InitScale[i]; //PSIZEにはピクセルサイズではなく倍率を埋め込む。
                                                                                                    //シェーダーで拡大縮小ピクセルを計算
            paVtxBuffer_data[i].color = D3DCOLOR_COLORVALUE(xdata_pspr.paD3DVECTOR_VertexColors[i].r,
                                                            xdata_pspr.paD3DVECTOR_VertexColors[i].g,
                                                            xdata_pspr.paD3DVECTOR_VertexColors[i].b,
                                                            xdata_pspr.paD3DVECTOR_VertexColors[i].a );
            paVtxBuffer_data[i].tu = (float)(xdata_pspr.paInt_InitUvPtnNo[i]);
            paVtxBuffer_data[i].tv = 0;


        }
        transformPosVtx(paVtxBuffer_data, size_vertex_unit, vertices_num);

        //距離
        FLOAT bounding_sphere_radius = 0;
        float dis;
        for (int i = 0; i < vertices_num; i++) {
            dis = (FLOAT)(sqrt(paVtxBuffer_data[i].x * paVtxBuffer_data[i].x +
                               paVtxBuffer_data[i].y * paVtxBuffer_data[i].y +
                               paVtxBuffer_data[i].z * paVtxBuffer_data[i].z  )
                           + (((square_size_px/PX_UNIT) * 1.41421356 ) / 2.0)
                         );

             if (bounding_sphere_radius < dis) {
                 bounding_sphere_radius = dis;
             }
        }
        D3DMATERIAL9*   paMaterial = nullptr;
        paMaterial = NEW D3DMATERIAL9[1];
        paMaterial[0].Diffuse.r = 1.0f;
        paMaterial[0].Diffuse.g = 1.0f;
        paMaterial[0].Diffuse.b = 1.0f;
        paMaterial[0].Diffuse.a = 1.0f;

        //モデルに保持させる
        _paMaterial_default     = paMaterial;
        _num_materials          = 1;
        _square_size_px         = square_size_px;
        _texture_size_px        = tex_width;
        _texture_split_rowcol   = texture_split_rowcol;
        _vertices_num           = vertices_num;
        _size_vertices          = size_vertices;
        _size_vertex_unit       = size_vertex_unit;
        _paVtxBuffer_data        = paVtxBuffer_data;
        _bounding_sphere_radius = bounding_sphere_radius;
        _inv_texture_split_rowcol = 1.0f / _texture_split_rowcol;
    }

    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        //頂点バッファ作成
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                PointSpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT D3DPOOL_MANAGED
                &(_paVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_id));

        //バッファへ作成済み頂点データを流し込む
        void *paVertexBuffer;
        hr = _paVertexBuffer->Lock(0, _size_vertices, (void**)&paVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_id);
        memcpy(paVertexBuffer, _paVtxBuffer_data, _size_vertices); //paVertexBuffer ← paVertex
        _paVertexBuffer->Unlock();
    }

    if (_papTextureConnection == nullptr) {
        //テクスチャ取得しモデルに保持させる
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[1];
        _papTextureConnection[0] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
    }
    _TRACE3_("_model_id=" << _model_id << " end");
}

void PointSpriteModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void PointSpriteModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    GGAF_RELEASE(_paVertexBuffer);
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);

    _TRACE3_("_model_id=" << _model_id << " end");
}

PointSpriteModel::~PointSpriteModel() {
    GGAF_DELETEARR(_paVtxBuffer_data);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
}

