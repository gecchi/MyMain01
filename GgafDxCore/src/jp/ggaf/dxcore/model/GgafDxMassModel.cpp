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
    _TRACE3_("GgafDxMassModel::GgafDxMassModel(" << _model_name << ")");
    _set_num = 0;
    _pVertexBuffer_model = nullptr;
    _pVertexBuffer_instacedata = nullptr;
    _pIndexBuffer = nullptr;
    _pVertexDeclaration = nullptr;
    _size_vertex_unit_instacedata = 0;
    _size_vertex_unit_model = 0;
    _size_vertices_model = 0;
    _nVertices = 0;
    _nFaces= 0;
    _pFunc_getVertexInstaceData = nullptr;
    _pInstancedata = nullptr;
    _obj_model |= Obj_GgafDxMassModel;
    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̃����o�[��������
    //void GgafDxMassModel::restore(GgafDxMassModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
    _TRACE_("GgafDxMassModel::GgafDxMassModel(" << _model_name << ") End");
}

void GgafDxMassModel::createVertexElements() {
    HRESULT hr;
    //�f�o�C�X�ɒ��_�t�H�[�}�b�g�o�^
    //���̃����o���ݒ肷��
    //_size_vertex_unit_instacedata
    //_pInstancedata
    //_pVertexDeclaration
    if (_pVertexDeclaration == nullptr) {
#ifdef MY_DEBUG
        if (!_pFunc_getVertexModel) {
            throwGgafCriticalException("GgafDxMassModel::createVertexElements() _pFunc_getVertexModel ���`���Ă��������B���f�����_��񂪕K�v�ł��B");
        }
        if (!_pFunc_getVertexInstaceData) {
            throwGgafCriticalException("GgafDxMassModel::createVertexElements() _pFunc_getVertexInstaceData ���`���Ă��������B�C���X�^���X�f�[�^��񂪕K�v�ł��B");
        }
#endif
        VertexModelInfo model_info;
        (*_pFunc_getVertexModel)(&model_info); //�R�[���o�b�N
        int model_element_num = model_info.element_num;

        VertexInstaceDataInfo instace_info;
        (*_pFunc_getVertexInstaceData)(&instace_info); //�R�[���o�b�N
        _size_vertex_unit_instacedata = instace_info.size_vertex_unit_instacedata;
        _pInstancedata =  instace_info.pInstancedata;
        int instace_data_element_num = instace_info.element_num;

        int elem_num = model_element_num + instace_data_element_num + 1; //+1 = D3DDECL_END()
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

        D3DVERTEXELEMENT9* paVtxInstaceDataElem = instace_info.paElement;
        for (int j = 0; j < instace_data_element_num; j++) {
            paVtxelem[model_element_num+j].Stream = paVtxInstaceDataElem[j].Stream;
            paVtxelem[model_element_num+j].Offset = paVtxInstaceDataElem[j].Offset;
            paVtxelem[model_element_num+j].Type   = paVtxInstaceDataElem[j].Type;
            paVtxelem[model_element_num+j].Method = paVtxInstaceDataElem[j].Method;
            paVtxelem[model_element_num+j].Usage  = paVtxInstaceDataElem[j].Usage;
            paVtxelem[model_element_num+j].UsageIndex = paVtxInstaceDataElem[j].UsageIndex;
        }

        //D3DDECL_END()
        paVtxelem[elem_num-1].Stream = 0xFF;
        paVtxelem[elem_num-1].Offset = 0;
        paVtxelem[elem_num-1].Type = D3DDECLTYPE_UNUSED;
        paVtxelem[elem_num-1].Method = 0;
        paVtxelem[elem_num-1].Usage = 0;
        paVtxelem[elem_num-1].UsageIndex = 0;

        hr = GgafDxGod::_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(_pVertexDeclaration) );
        checkDxException(hr, D3D_OK, "GgafDxMassModel::restore() GgafDxGod::_pID3DDevice9->CreateVertexDeclaration ���s model="<<(_model_name));
        GGAF_DELETEARR(paVtxelem);
    }
    //�f�o�C�X�ɒ��_�o�b�t�@�쐬(�C���X�^���X�f�[�^)
    int size_instancedata = _size_vertex_unit_instacedata * _set_num;//�ő哯���`�搔�m��
    hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
            size_instancedata,
            D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,  //���񏑂��������D3DUSAGE_DYNAMIC
            0,
            D3DPOOL_DEFAULT,
            &(_pVertexBuffer_instacedata),
            nullptr);
    checkDxException(hr, D3D_OK, "GgafDxMassModel::restore() _pID3DDevice9->CreateVertexBuffer2 ���s model="<<_model_name);
    void *pDeviceMemory;
    hr = _pVertexBuffer_instacedata->Lock(0, size_instancedata, (void**)&pDeviceMemory, 0);
    checkDxException(hr, D3D_OK, "GgafDxMassModel::restore() ���_�o�b�t�@�̃��b�N�擾�Ɏ��s2 model="<<_model_name);
    ZeroMemory(pDeviceMemory, size_instancedata);
    hr = _pVertexBuffer_instacedata->Unlock();
    checkDxException(hr, D3D_OK, "GgafDxMassModel::restore() ���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s2 model="<<_model_name);
}

void GgafDxMassModel::onDeviceLost() {
    _TRACE3_("GgafDxMassModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxMassModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMassModel::release() {
    _TRACE3_("GgafDxMassModel::release() " << _model_name << " start");
    //�e�N�X�`�������
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    GGAF_RELEASE(_pVertexBuffer_instacedata);
    GGAF_RELEASE(_pVertexBuffer_model);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_RELEASE(_pVertexDeclaration);
    _TRACE3_("GgafDxMassModel::release() " << _model_name << " end");
}

GgafDxMassModel::~GgafDxMassModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

