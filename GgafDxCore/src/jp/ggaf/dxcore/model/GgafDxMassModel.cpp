#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassModel::GgafDxMassModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _set_num = 0;
    _pVertexBuffer_model = nullptr;
    _pVertexBuffer_instancedata = nullptr;
    _pIndexBuffer = nullptr;
    _pVertexDeclaration = nullptr;
    _size_vertex_unit_instancedata = 0;
    _size_vertex_unit_model = 0;
    _size_vertices_model = 0;
    _nVertices = 0;
    _nFaces= 0;
    _pFunc_getVertexInstanceData = nullptr;
    _pFunc_getVertexModel = nullptr;
    _pInstancedata = nullptr;
    _obj_model |= Obj_GgafDxMassModel;
}

void GgafDxMassModel::createVertexElements() {
    HRESULT hr;
    //デバイスに頂点フォーマット登録
    //次のメンバも設定する
    //_size_vertex_unit_instancedata
    //_pInstancedata
    //_pVertexDeclaration
    if (_pVertexDeclaration == nullptr) {
#ifdef MY_DEBUG
        if (!_pFunc_getVertexModel) {
            throwGgafCriticalException("_pFunc_getVertexModel を定義してください。モデル頂点情報が必要です。");
        }
        if (!_pFunc_getVertexInstanceData) {
            throwGgafCriticalException("_pFunc_getVertexInstanceData を定義してください。インスタンスデータ情報が必要です。");
        }
#endif
        VertexModelInfo model_info;
        (*_pFunc_getVertexModel)(this, &model_info); //コールバック
        int model_element_num = model_info.element_num;

        VertexInstanceDataInfo instance_info;
        (*_pFunc_getVertexInstanceData)(this, &instance_info); //コールバック
        _size_vertex_unit_instancedata = instance_info.size_vertex_unit_instancedata;
        _pInstancedata = instance_info.pInstancedata;
        int instance_data_element_num = instance_info.element_num;

        int elem_num = model_element_num + instance_data_element_num + 1; //+1 = D3DDECL_END()
        D3DVERTEXELEMENT9* paVtxelem = NEW D3DVERTEXELEMENT9[elem_num];

        D3DVERTEXELEMENT9* paVtxModel = model_info.paElement;
        for (int i = 0; i < model_element_num; i++) {
            paVtxelem[i].Stream = paVtxModel[i].Stream;
            paVtxelem[i].Offset = paVtxModel[i].Offset;
            paVtxelem[i].Type   = paVtxModel[i].Type;
            paVtxelem[i].Method = paVtxModel[i].Method;
            paVtxelem[i].Usage  = paVtxModel[i].Usage;
            paVtxelem[i].UsageIndex = paVtxModel[i].UsageIndex;
        }

        D3DVERTEXELEMENT9* paVtxInstanceDataElem = instance_info.paElement;
        for (int j = 0; j < instance_data_element_num; j++) {
            paVtxelem[model_element_num+j].Stream = paVtxInstanceDataElem[j].Stream;
            paVtxelem[model_element_num+j].Offset = paVtxInstanceDataElem[j].Offset;
            paVtxelem[model_element_num+j].Type   = paVtxInstanceDataElem[j].Type;
            paVtxelem[model_element_num+j].Method = paVtxInstanceDataElem[j].Method;
            paVtxelem[model_element_num+j].Usage  = paVtxInstanceDataElem[j].Usage;
            paVtxelem[model_element_num+j].UsageIndex = paVtxInstanceDataElem[j].UsageIndex;
        }

        //D3DDECL_END()
        paVtxelem[elem_num-1].Stream = 0xFF;
        paVtxelem[elem_num-1].Offset = 0;
        paVtxelem[elem_num-1].Type = D3DDECLTYPE_UNUSED;
        paVtxelem[elem_num-1].Method = 0;
        paVtxelem[elem_num-1].Usage = 0;
        paVtxelem[elem_num-1].UsageIndex = 0;

        hr = GgafDxGod::_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(_pVertexDeclaration) );
        checkDxException(hr, D3D_OK, "GgafDxGod::_pID3DDevice9->CreateVertexDeclaration 失敗 model="<<(_model_name));
        GGAF_DELETEARR(paVtxelem);
    }
    //デバイスに頂点バッファ作成(インスタンスデータ)
    int size_instancedata = _size_vertex_unit_instancedata * _set_num;//最大同時描画数確保
    hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
            size_instancedata,
            D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,  //毎回書き換える為D3DUSAGE_DYNAMIC
            0,
            D3DPOOL_DEFAULT,
            &(_pVertexBuffer_instancedata),
            nullptr);
    checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer2 失敗 model="<<_model_name);
//    void* pDeviceMemory = 0;
//    hr = _pVertexBuffer_instancedata->Lock(0, size_instancedata, (void**)&pDeviceMemory, 0);
//    checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗2 model="<<_model_name);
//    ZeroMemory(pDeviceMemory, size_instancedata);
//    hr = _pVertexBuffer_instancedata->Unlock();
//    checkDxException(hr, D3D_OK, "頂点バッファのアンロック取得に失敗2 model="<<_model_name);
}

void GgafDxMassModel::resetStreamSourceFreq() {
    GgafDxGod::_pID3DDevice9->SetStreamSourceFreq( 0, 1 );
    GgafDxGod::_pID3DDevice9->SetStreamSourceFreq( 1, 1 );
}

void GgafDxMassModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxMassModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    //テクスチャを解放
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    GGAF_RELEASE(_pVertexBuffer_instancedata);
    GGAF_RELEASE(_pVertexBuffer_model);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_RELEASE(_pVertexDeclaration);
    _TRACE3_("_model_name=" << _model_name << " end");
}

GgafDxMassModel::~GgafDxMassModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

