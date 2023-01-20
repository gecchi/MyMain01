#include "jp/ggaf/dx/model/RegularPolygonBoardModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/actor/RegularPolygonBoardActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/RegularPolygonBoardEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;

DWORD RegularPolygonBoardModel::FVF = (D3DFVF_XYZ | D3DFVF_TEX1);

RegularPolygonBoardModel::RegularPolygonBoardModel(const char* prm_model_id) :
    Model(prm_model_id), IPlaneModel() {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_RegularPolygonBoardModel | Obj_GgafDx_IPlaneModel;
    _paVertexBuffer_data = nullptr;
    _paVertexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _angle_num = 3;
    _drawing_order = 0;
    _x_center = 16;
    _y_center = 16;
    _u_center = 0.5;
    _v_center = 0.5;
    _max_draw_set_num = 1;
}

HRESULT RegularPolygonBoardModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("RegularPolygonBoardModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;
    //対象Actor
    const RegularPolygonBoardActor* const pTargetActor = (RegularPolygonBoardActor*)prm_pActor_target;
    //対象RegularPolygonBoardActorのエフェクトラッパ
    RegularPolygonBoardEffect* const pRegularPolygonBoardEffect = (RegularPolygonBoardEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pRegularPolygonBoardEffect->_pID3DXEffect;
    //今回描画のUV
    float u,v;
    pTargetActor->_pUvFlipper->getUV(u,v);
    HRESULT hr;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _paVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(RegularPolygonBoardModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_x_center, _x_center);
        checkDxException(hr, D3D_OK, "SetFloat(_h_x_center) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_y_center, _y_center);
        checkDxException(hr, D3D_OK, "SetFloat(_h_y_center) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_u_center, _u_center);
        checkDxException(hr, D3D_OK, "SetFloat(_h_u_center) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_v_center, _v_center);
        checkDxException(hr, D3D_OK, "SetFloat(_h_v_center) に失敗しました。");
    }
    hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) に失敗しました。");
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pRegularPolygonBoardEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pRegularPolygonBoardEffect->_effect_name);
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pRegularPolygonBoardEffect->_begin) {
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pRegularPolygonBoardEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pRegularPolygonBoardEffect->_effect_name<<"("<<pRegularPolygonBoardEffect<<")");
    pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, pTargetActor->_draw_fan_num);
#ifdef MY_DEBUG
        GgafCore::Caretaker::_num_draw++;
#endif
    //前回描画モデル保持
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pRegularPolygonBoardEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void RegularPolygonBoardModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVertexBuffer_data == nullptr) {
        _papTextureConnection = nullptr;
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        std::string model_def_file = std::string(_model_id) + ".rsprx";
        std::string model_def_filepath = Model::getModelDefineFilePath(model_def_file);
        if (model_def_filepath == "") {
            throwCriticalException("RegularPolygonBoardModel::restore() "+model_def_file+" が見つかりません");
        }
        ModelManager::RegPolySpriteXFileFmt xdata;
        pModelManager->obtainRegPolySpriteModelInfo(&xdata, model_def_filepath);

        _angle_num = xdata.FanNum;
        _drawing_order = xdata.IsCW;
        _model_width_px  = xdata.Width;
        _model_height_px = xdata.Height;
        _row_texture_split = xdata.TextureSplitRows;
        _col_texture_split = xdata.TextureSplitCols;
        _pa_texture_filenames = NEW std::string[1];
        _pa_texture_filenames[0] = std::string(xdata.TextureFile);
        _matBaseTransformMatrix = xdata.BaseTransformMatrix;

        _paVertexBuffer_data = NEW RegularPolygonBoardModel::VERTEX[_angle_num+2];
        _size_vertices = sizeof(RegularPolygonBoardModel::VERTEX)*(_angle_num+2);
        _size_vertex_unit = sizeof(RegularPolygonBoardModel::VERTEX);
        float model_width = _model_width_px;
        float model_height = _model_height_px;
        float tu_rate = 1.0 / _col_texture_split;
        float tv_rate = 1.0 / _row_texture_split;
        _u_center = tu_rate * 0.5;
        _v_center = tv_rate * 0.5;
        _x_center =  model_width * 0.5;
        _y_center =  model_height * 0.5;
        //中心
        _paVertexBuffer_data[0].x = _x_center;
        _paVertexBuffer_data[0].y = _y_center;
        _paVertexBuffer_data[0].z = 0.0f;
        _paVertexBuffer_data[0].tu = _u_center;
        _paVertexBuffer_data[0].tv = _v_center;

        if (_drawing_order == 0) {        //反計回り
            for (int ang = 0; ang < _angle_num; ang++) {
                double rad = (PI2 * ang) / _angle_num;
                _paVertexBuffer_data[ang+1].x = _paVertexBuffer_data[0].x + (cos(rad) * model_width  * 0.5);
                _paVertexBuffer_data[ang+1].y = _paVertexBuffer_data[0].y - (sin(rad) * model_height * 0.5);
                _paVertexBuffer_data[ang+1].z = 0.0f;
                _paVertexBuffer_data[ang+1].tu = _paVertexBuffer_data[0].tu + (cos(rad) * tu_rate * 0.5);
                _paVertexBuffer_data[ang+1].tv = _paVertexBuffer_data[0].tv - (sin(rad) * tv_rate * 0.5);
            }
            _paVertexBuffer_data[_angle_num+1] = _paVertexBuffer_data[1];
        } else {
            //時計回り
            for (int ang = 0; ang < _angle_num; ang++) {
                double rad = PI2 - ((PI2 * ang) / _angle_num);
                _paVertexBuffer_data[ang+1].x = _paVertexBuffer_data[0].x + (cos(rad) * model_width  * 0.5);
                _paVertexBuffer_data[ang+1].y = _paVertexBuffer_data[0].y - (sin(rad) * model_height * 0.5);
                _paVertexBuffer_data[ang+1].z = 0.0f;
                _paVertexBuffer_data[ang+1].tu = _paVertexBuffer_data[0].tu + (cos(rad) * tu_rate * 0.5);
                _paVertexBuffer_data[ang+1].tv = _paVertexBuffer_data[0].tv - (sin(rad) * tv_rate * 0.5);
            }
            _paVertexBuffer_data[_angle_num+1] = _paVertexBuffer_data[1];
        }
        transformPosVtx(_paVertexBuffer_data, _size_vertex_unit, _angle_num+2);

        _num_materials = 1;
        D3DMATERIAL9* paMaterial;
        paMaterial = NEW D3DMATERIAL9[_num_materials];
        for ( DWORD i = 0; i < _num_materials; i++) {
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


    //バッファ作成
    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                RegularPolygonBoardModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_paVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_id));
        //頂点バッファ作成
        //頂点情報をビデオカード頂点バッファへロード
        void *paVertexBuffer;
        hr = _paVertexBuffer->Lock(0, _size_vertices, (void**)&paVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_id);

        memcpy(paVertexBuffer, _paVertexBuffer_data, _size_vertices); //paVertexBuffer ← _paVertexBuffer_data
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

void RegularPolygonBoardModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    GGAF_RELEASE(_paVertexBuffer);
    //テクスチャを解放
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

void RegularPolygonBoardModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

RegularPolygonBoardModel::~RegularPolygonBoardModel() {
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    GGAF_DELETEARR(_paVertexBuffer_data);
}
