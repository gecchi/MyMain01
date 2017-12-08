#include "jp/ggaf/dxcore/model/GgafDxPointSpriteModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxPointSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDxPointSpriteModel::GgafDxPointSpriteModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _pVertexBuffer = nullptr;
    _paVtxBuffer_data = nullptr;
    _vertices_num = 0;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _square_size_px = 0.0f;
    _texture_size_px = 0.0f;
    _texture_split_rowcol = 1;
    _obj_model |= Obj_GgafDxPointSpriteModel;
}

HRESULT GgafDxPointSpriteModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    _TRACE4_("GgafDxPointSpriteModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());

    //対象Actor
    const GgafDxPointSpriteActor* const pTargetActor = (GgafDxPointSpriteActor*)prm_pActor_target;
    //対象PointSpriteActorのエフェクトラッパ
    GgafDxPointSpriteEffect* const pPointSpriteEffect = (GgafDxPointSpriteEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pPointSpriteEffect->_pID3DXEffect;

    //今回描画のUV
    HRESULT hr;
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxPointSpriteModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_hTexSize, _texture_size_px);
        checkDxException(hr, D3D_OK, "SetFloat(_hTexSize) に失敗しました。");
        hr = pID3DXEffect->SetInt(pPointSpriteEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hTextureSplitRowcol) に失敗しました。");
        hr = pID3DXEffect->SetValue(pPointSpriteEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name<<"("<<pPointSpriteEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pPointSpriteEffect->_begin) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pPointSpriteEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
    pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _vertices_num);

    //前回描画モデル保持
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pPointSpriteEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif
    return D3D_OK;
}

void GgafDxPointSpriteModel::restore() {
    _TRACE3_("_model_name="<<_model_name);
    _papTextureConnection = nullptr;
    HRESULT hr;
    std::string xfile_name = GgafDxModelManager::getPointSpriteFileName(_model_name);
    GgafDxModelManager::PointSpriteXFileFmt pointsprite_info;
    GgafDxModelManager::obtainPointSpriteInfo(&pointsprite_info, xfile_name);
    //退避
    float square_size_px = pointsprite_info.SquareSize;
    int texture_split_rowcol = pointsprite_info.TextureSplitRowCol;
    int vertices_num = pointsprite_info.VerticesNum;
    _TRACE3_("vertices_num="<<vertices_num);
    UINT size_vertices = sizeof(GgafDxPointSpriteModel::VERTEX)*vertices_num;
    UINT size_vertex_unit = sizeof(GgafDxPointSpriteModel::VERTEX);

    //テクスチャ取得しモデルに保持させる
    GgafDxTextureConnection** papTextureConnection = NEW GgafDxTextureConnection*[1];
    papTextureConnection[0] = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(pointsprite_info.TextureFile , this));
    GgafDxTexture* pTex = papTextureConnection[0]->peek();

    float tex_width  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
    float tex_height = (float)(pTex->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)幅と同じになる
    if ((int)(tex_width*100000) != (int)(tex_height*100000)) {
        throwGgafCriticalException("ポイントスプライト用テクスチャ["<<pTex->getName()<<"]("<<tex_width<<"x"<<tex_height<<")は、正方形である必要があります。");
    }
    FLOAT bounding_sphere_radius = 0;

    //頂点バッファ作成
    GgafDxPointSpriteModel::VERTEX* paVtxBuffer_data = NEW GgafDxPointSpriteModel::VERTEX[vertices_num];

    float dis;
    for (int i = 0; i < vertices_num; i++) {
        paVtxBuffer_data[i].x = pointsprite_info.paD3DVECTOR_Vertices[i].x;
        paVtxBuffer_data[i].y = pointsprite_info.paD3DVECTOR_Vertices[i].y;
        paVtxBuffer_data[i].z = pointsprite_info.paD3DVECTOR_Vertices[i].z;
        paVtxBuffer_data[i].psize = (square_size_px*texture_split_rowcol / tex_width) * pointsprite_info.paFLOAT_InitScale[i]; //PSIZEにはピクセルサイズではなく倍率を埋め込む。
                                                                                                //シェーダーで拡大縮小ピクセルを計算
        paVtxBuffer_data[i].color = D3DCOLOR_COLORVALUE(pointsprite_info.paD3DVECTOR_VertexColors[i].r,
                                                        pointsprite_info.paD3DVECTOR_VertexColors[i].g,
                                                        pointsprite_info.paD3DVECTOR_VertexColors[i].b,
                                                        pointsprite_info.paD3DVECTOR_VertexColors[i].a );
        paVtxBuffer_data[i].tu = (float)(pointsprite_info.paInt_InitUvPtnNo[i]);
        paVtxBuffer_data[i].tv = 0;

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
    if (_pVertexBuffer == nullptr) {

        //頂点バッファ作成
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDxPointSpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT D3DPOOL_MANAGED
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));

        //バッファへ作成済み頂点データを流し込む
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(0, size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_name);
        memcpy(pVertexBuffer, paVtxBuffer_data, size_vertices); //pVertexBuffer ← paVertex
        _pVertexBuffer->Unlock();
    }

    paMaterial = NEW D3DMATERIAL9[1];
    paMaterial[0].Diffuse.r = 1.0f;
    paMaterial[0].Diffuse.g = 1.0f;
    paMaterial[0].Diffuse.b = 1.0f;
    paMaterial[0].Diffuse.a = 1.0f;

    //モデルに保持させる
    _paMaterial_default     = paMaterial;
    _papTextureConnection   = papTextureConnection;
    _num_materials          = 1;
    _square_size_px         = square_size_px;
    _texture_size_px        = tex_width;
    _texture_split_rowcol   = texture_split_rowcol;
    _vertices_num           = vertices_num;
    _size_vertices          = size_vertices;
    _size_vertex_unit       = size_vertex_unit;
    _paVtxBuffer_data        = paVtxBuffer_data;
    _bounding_sphere_radius = bounding_sphere_radius;
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxPointSpriteModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxPointSpriteModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_DELETEARR(_paVtxBuffer_data);
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

GgafDxPointSpriteModel::~GgafDxPointSpriteModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

