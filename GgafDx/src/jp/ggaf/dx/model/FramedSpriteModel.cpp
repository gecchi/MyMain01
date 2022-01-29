#include "jp/ggaf/dx/model/FramedSpriteModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/actor/FramedSpriteActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/FramedSpriteEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;

DWORD FramedSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1);

FramedSpriteModel::FramedSpriteModel(const char* prm_model_id) : Model(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_model |= Obj_GgafDx_FramedSpriteModel;
    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _model_frame_width_px = 32.0f;
    _model_frame_height_px = 32.0f;
    _row_frame_texture_split = 1;
    _col_frame_texture_split = 1;
    _paVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _paVertexBuffer_data = nullptr;
    _pIndexBuffer_data = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _nVertices = 4;
    _max_draw_set_num = 1;
}

HRESULT FramedSpriteModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    _TRACE4_("FramedSpriteModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    //対象Actor
    const FramedSpriteActor* const pTargetActor = (FramedSpriteActor*)prm_pActor_target;
    //対象FramedSpriteActorのエフェクトラッパ
    FramedSpriteEffect* const pFramedSpriteEffect = (FramedSpriteEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pFramedSpriteEffect->_pID3DXEffect;

    //今回描画のUV
    float u,v;
    pTargetActor->_pUvFlipper->getUV(u,v);
    HRESULT hr;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _paVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(FramedSpriteModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }
    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) に失敗しました。");
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pFramedSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pFramedSpriteEffect->_effect_name<<"("<<pFramedSpriteEffect<<")");
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pFramedSpriteEffect->_begin) {
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pFramedSpriteEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pFramedSpriteEffect->_effect_name);
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    if (_num_pass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");

        for (UINT pass = 1; pass < _num_pass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, pass+1<<"パス目 BeginPass("<<pass<<") に失敗しました。");
            pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
        }

        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "１パス目 BeginPass(0) に失敗しました。");
    }

    //前回描画モデル保持
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pFramedSpriteEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
    return D3D_OK;
}

void FramedSpriteModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVertexBuffer_data == nullptr) {
        _draw_set_num = 9;
        _papTextureConnection = nullptr;
        ModelManager* pModelManager = pGOD->_pModelManager;

        std::string model_def_file = std::string(_model_id) + ".fsprx";
        std::string model_def_filepath = Model::getModelDefineFilePath(model_def_file);
        ModelManager::FramedSpriteXFileFmt xdata;
        pModelManager->obtainFramedSpriteModelInfo(&xdata, model_def_filepath);
        _model_width_px  = xdata.Width;
        _model_height_px = xdata.Height;
        _row_texture_split = xdata.TextureSplitRows;
        _col_texture_split = xdata.TextureSplitCols;
        _model_frame_width_px  = xdata.FrameWidth;
        _model_frame_height_px = xdata.FrameHeight;
        _row_frame_texture_split = xdata.FrameTextureSplitRows;
        _col_frame_texture_split = xdata.FrameTextureSplitCols;
        _pa_texture_filenames = NEW std::string[2];
        _pa_texture_filenames[0] = std::string(xdata.TextureFile);
        _pa_texture_filenames[1] = std::string(xdata.FrameTextureFile);

        _size_vertices = sizeof(FramedSpriteModel::VERTEX)*4;
        _size_vertex_unit = sizeof(FramedSpriteModel::VERTEX);
        _paVertexBuffer_data = NEW FramedSpriteModel::VERTEX[4 * _draw_set_num];
        //    ┌─┬─┬─┐
        //    │０│１│２│
        //    ├─┼─┼─┤
        //    │３│４│５│
        //    ├─┼─┼─┤
        //    │６│７│８│
        //    └─┴─┴─┘
        //1pxあたりのuvの大きさを求める
        for (int i = 0; i < _draw_set_num; i++) {
            if (i == 4) {
                //中心
                //左上
                _paVertexBuffer_data[i*4 + 0].x = PX_DX(xdata.Width)  / -2.0;
                _paVertexBuffer_data[i*4 + 0].y = PX_DX(xdata.Height) /  2.0;
                _paVertexBuffer_data[i*4 + 0].z = 0.0f;
                _paVertexBuffer_data[i*4 + 0].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 0].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 0].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 0].index = (float)i;
                _paVertexBuffer_data[i*4 + 0].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 0].tu = 0.0f;
                _paVertexBuffer_data[i*4 + 0].tv = 0.0f;
                //右上
                _paVertexBuffer_data[i*4 + 1].x = PX_DX(xdata.Width)  /  2.0;
                _paVertexBuffer_data[i*4 + 1].y = PX_DX(xdata.Height) /  2.0;
                _paVertexBuffer_data[i*4 + 1].z = 0.0f;
                _paVertexBuffer_data[i*4 + 1].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 1].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 1].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 1].index = (float)i;
                _paVertexBuffer_data[i*4 + 1].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 1].tu = (float)(1.0 / xdata.TextureSplitCols);
                _paVertexBuffer_data[i*4 + 1].tv = 0.0f;
                //左下
                _paVertexBuffer_data[i*4 + 2].x = PX_DX(xdata.Width)  / -2.0;
                _paVertexBuffer_data[i*4 + 2].y = PX_DX(xdata.Height) / -2.0;
                _paVertexBuffer_data[i*4 + 2].z = 0.0f;
                _paVertexBuffer_data[i*4 + 2].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 2].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 2].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 2].index = (float)i;
                _paVertexBuffer_data[i*4 + 2].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 2].tu = 0.0f;
                _paVertexBuffer_data[i*4 + 2].tv = (float)(1.0 / xdata.TextureSplitRows);
                //右下
                _paVertexBuffer_data[i*4 + 3].x = PX_DX(xdata.Width)  /  2.0;
                _paVertexBuffer_data[i*4 + 3].y = PX_DX(xdata.Height) / -2.0;
                _paVertexBuffer_data[i*4 + 3].z = 0.0f;
                _paVertexBuffer_data[i*4 + 3].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 3].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 3].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 3].index = (float)i;
                _paVertexBuffer_data[i*4 + 3].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 3].tu = (float)(1.0 / xdata.TextureSplitCols);
                _paVertexBuffer_data[i*4 + 3].tv = (float)(1.0 / xdata.TextureSplitRows);

            } else if (i == 0 || i == 2 || i == 6 || i == 8 ) {
                //４角
                //左上
                _paVertexBuffer_data[i*4 + 0].x = PX_DX(xdata.FrameWidth)  / -2.0;
                _paVertexBuffer_data[i*4 + 0].y = PX_DX(xdata.FrameHeight) /  2.0;
                _paVertexBuffer_data[i*4 + 0].z = 0.0f;
                _paVertexBuffer_data[i*4 + 0].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 0].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 0].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 0].index = (float)i;
                _paVertexBuffer_data[i*4 + 0].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 0].tu = 0.0f;
                _paVertexBuffer_data[i*4 + 0].tv = 0.0f;
                //右上
                _paVertexBuffer_data[i*4 + 1].x = PX_DX(xdata.FrameWidth)  /  2.0;
                _paVertexBuffer_data[i*4 + 1].y = PX_DX(xdata.FrameHeight) /  2.0;
                _paVertexBuffer_data[i*4 + 1].z = 0.0f;
                _paVertexBuffer_data[i*4 + 1].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 1].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 1].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 1].index = (float)i;
                _paVertexBuffer_data[i*4 + 1].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 1].tu = (float)(1.0 / xdata.TextureSplitCols);
                _paVertexBuffer_data[i*4 + 1].tv = 0.0f;
                //左下
                _paVertexBuffer_data[i*4 + 2].x = PX_DX(xdata.FrameWidth)  / -2.0;
                _paVertexBuffer_data[i*4 + 2].y = PX_DX(xdata.FrameHeight) / -2.0;
                _paVertexBuffer_data[i*4 + 2].z = 0.0f;
                _paVertexBuffer_data[i*4 + 2].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 2].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 2].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 2].index = (float)i;
                _paVertexBuffer_data[i*4 + 2].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 2].tu = 0.0f;
                _paVertexBuffer_data[i*4 + 2].tv = (float)(1.0 / xdata.TextureSplitRows);
                //右下
                _paVertexBuffer_data[i*4 + 3].x = PX_DX(xdata.FrameWidth)  /  2.0;
                _paVertexBuffer_data[i*4 + 3].y = PX_DX(xdata.FrameHeight) / -2.0;
                _paVertexBuffer_data[i*4 + 3].z = 0.0f;
                _paVertexBuffer_data[i*4 + 3].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 3].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 3].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 3].index = (float)i;
                _paVertexBuffer_data[i*4 + 3].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 3].tu = (float)(1.0 / xdata.TextureSplitCols);
                _paVertexBuffer_data[i*4 + 3].tv = (float)(1.0 / xdata.TextureSplitRows);

            } else if (i == 1 || i == 7) {
                //縦の真ん中
                //左上
                _paVertexBuffer_data[i*4 + 0].x = PX_DX(xdata.Width)  / -2.0;
                _paVertexBuffer_data[i*4 + 0].y = PX_DX(xdata.FrameHeight) /  2.0;
                _paVertexBuffer_data[i*4 + 0].z = 0.0f;
                _paVertexBuffer_data[i*4 + 0].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 0].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 0].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 0].index = (float)i;
                _paVertexBuffer_data[i*4 + 0].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 0].tu = 0.0f;
                _paVertexBuffer_data[i*4 + 0].tv = 0.0f;
                //右上
                _paVertexBuffer_data[i*4 + 1].x = PX_DX(xdata.Width)  /  2.0;
                _paVertexBuffer_data[i*4 + 1].y = PX_DX(xdata.FrameHeight) /  2.0;
                _paVertexBuffer_data[i*4 + 1].z = 0.0f;
                _paVertexBuffer_data[i*4 + 1].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 1].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 1].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 1].index = (float)i;
                _paVertexBuffer_data[i*4 + 1].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 1].tu = (float)(1.0 / xdata.TextureSplitCols);
                _paVertexBuffer_data[i*4 + 1].tv = 0.0f;
                //左下
                _paVertexBuffer_data[i*4 + 2].x = PX_DX(xdata.Width)  / -2.0;
                _paVertexBuffer_data[i*4 + 2].y = PX_DX(xdata.FrameHeight) / -2.0;
                _paVertexBuffer_data[i*4 + 2].z = 0.0f;
                _paVertexBuffer_data[i*4 + 2].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 2].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 2].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 2].index = (float)i;
                _paVertexBuffer_data[i*4 + 2].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 2].tu = 0.0f;
                _paVertexBuffer_data[i*4 + 2].tv = (float)(1.0 / xdata.TextureSplitRows);
                //右下
                _paVertexBuffer_data[i*4 + 3].x = PX_DX(xdata.Width)  /  2.0;
                _paVertexBuffer_data[i*4 + 3].y = PX_DX(xdata.FrameHeight) / -2.0;
                _paVertexBuffer_data[i*4 + 3].z = 0.0f;
                _paVertexBuffer_data[i*4 + 3].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 3].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 3].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 3].index = (float)i;
                _paVertexBuffer_data[i*4 + 3].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 3].tu = (float)(1.0 / xdata.TextureSplitCols);
                _paVertexBuffer_data[i*4 + 3].tv = (float)(1.0 / xdata.TextureSplitRows);

            } else if (i == 3 || i == 5) {
                //横の真ん中
                //左上
                _paVertexBuffer_data[i*4 + 0].x = PX_DX(xdata.FrameWidth)  / -2.0;
                _paVertexBuffer_data[i*4 + 0].y = PX_DX(xdata.Height) /  2.0;
                _paVertexBuffer_data[i*4 + 0].z = 0.0f;
                _paVertexBuffer_data[i*4 + 0].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 0].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 0].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 0].index = (float)i;
                _paVertexBuffer_data[i*4 + 0].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 0].tu = 0.0f;
                _paVertexBuffer_data[i*4 + 0].tv = 0.0f;
                //右上
                _paVertexBuffer_data[i*4 + 1].x = PX_DX(xdata.FrameWidth)  /  2.0;
                _paVertexBuffer_data[i*4 + 1].y = PX_DX(xdata.Height) /  2.0;
                _paVertexBuffer_data[i*4 + 1].z = 0.0f;
                _paVertexBuffer_data[i*4 + 1].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 1].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 1].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 1].index = (float)i;
                _paVertexBuffer_data[i*4 + 1].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 1].tu = (float)(1.0 / xdata.TextureSplitCols);
                _paVertexBuffer_data[i*4 + 1].tv = 0.0f;
                //左下
                _paVertexBuffer_data[i*4 + 2].x = PX_DX(xdata.FrameWidth)  / -2.0;
                _paVertexBuffer_data[i*4 + 2].y = PX_DX(xdata.Height) / -2.0;
                _paVertexBuffer_data[i*4 + 2].z = 0.0f;
                _paVertexBuffer_data[i*4 + 2].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 2].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 2].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 2].index = (float)i;
                _paVertexBuffer_data[i*4 + 2].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 2].tu = 0.0f;
                _paVertexBuffer_data[i*4 + 2].tv = (float)(1.0 / xdata.TextureSplitRows);
                //右下
                _paVertexBuffer_data[i*4 + 3].x = PX_DX(xdata.FrameWidth)  /  2.0;
                _paVertexBuffer_data[i*4 + 3].y = PX_DX(xdata.Height) / -2.0;
                _paVertexBuffer_data[i*4 + 3].z = 0.0f;
                _paVertexBuffer_data[i*4 + 3].nx = 0.0f;
                _paVertexBuffer_data[i*4 + 3].ny = 0.0f;
                _paVertexBuffer_data[i*4 + 3].nz = -1.0f;
                _paVertexBuffer_data[i*4 + 3].index = (float)i;
                _paVertexBuffer_data[i*4 + 3].color = D3DCOLOR_ARGB(255,255,255,255);
                _paVertexBuffer_data[i*4 + 3].tu = (float)(1.0 / xdata.TextureSplitCols);
                _paVertexBuffer_data[i*4 + 3].tv = (float)(1.0 / xdata.TextureSplitRows);
            }
        }

        transformPosVtx(_paVertexBuffer_data, _size_vertex_unit, _nVertices);
        //距離
        FLOAT l0 = (FLOAT)(sqrt(_paVertexBuffer_data[0].x * _paVertexBuffer_data[0].x +
                          _paVertexBuffer_data[0].y * _paVertexBuffer_data[0].y +
                          _paVertexBuffer_data[0].z * _paVertexBuffer_data[0].z));
        FLOAT l4 = (FLOAT)(sqrt(_paVertexBuffer_data[4].x * _paVertexBuffer_data[4].x +
                          _paVertexBuffer_data[4].y * _paVertexBuffer_data[4].y +
                          _paVertexBuffer_data[4].z * _paVertexBuffer_data[4].z));
        FLOAT l8 = (FLOAT)(sqrt(_paVertexBuffer_data[8].x * _paVertexBuffer_data[8].x +
                          _paVertexBuffer_data[8].y * _paVertexBuffer_data[8].y +
                          _paVertexBuffer_data[8].z * _paVertexBuffer_data[8].z));
        _bounding_sphere_radius = l0 + l4 + l8;

        int nVertices = 4;
        int nFaces = 2;
        WORD* unit_paIdxBuffer = NEW WORD[(nFaces*3)];
        unit_paIdxBuffer[0] = 0;
        unit_paIdxBuffer[1] = 1;
        unit_paIdxBuffer[2] = 2;
        unit_paIdxBuffer[3] = 1;
        unit_paIdxBuffer[4] = 3;
        unit_paIdxBuffer[5] = 2;
        _pIndexBuffer_data = NEW WORD[(nFaces*3) * _draw_set_num];
        for (int i = 0; i < _draw_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                _pIndexBuffer_data[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer[j*3 + 0] + (nVertices*i);
                _pIndexBuffer_data[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer[j*3 + 1] + (nVertices*i);
                _pIndexBuffer_data[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer[j*3 + 2] + (nVertices*i);
            }
        }
        GGAF_DELETEARR(unit_paIdxBuffer);

        _num_materials = 1;
         D3DMATERIAL9* paMaterial;
         paMaterial = NEW D3DMATERIAL9[_num_materials];
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

        //描画時パラメーター
        _indexParam.MaterialNo = 0;
        _indexParam.BaseVertexIndex = 0;
        _indexParam.MinIndex = 0;
        _indexParam.NumVertices = nVertices*_draw_set_num;
        _indexParam.StartIndex = 0;
        _indexParam.PrimitiveCount = nFaces*_draw_set_num;


    } // if (_paVertexBuffer_data == nullptr) {


    //バッファ作成
    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                FramedSpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_paVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_id));
        //頂点バッファ作成
        //頂点情報をビデオカード頂点バッファへロード
        void *pVertexBuffer;
        hr = _paVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_id);
        memcpy(pVertexBuffer, _paVertexBuffer_data, _size_vertices); //paVertexBuffer ← _paVertexBuffer_data
        _paVertexBuffer->Unlock();
    }


    _TRACE3_("_model_id=" << _model_id << " end");
}

void FramedSpriteModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void FramedSpriteModel::release() {
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

FramedSpriteModel::~FramedSpriteModel() {
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    GGAF_DELETEARR(_paVertexBuffer_data);
}

