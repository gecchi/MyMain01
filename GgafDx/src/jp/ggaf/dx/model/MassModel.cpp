#include "jp/ggaf/dx/model/MassModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/effect/MassEffect.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/manager/TextureManager.h"


using namespace GgafDx;

MassModel::MassModel(const char* prm_model_id) : Model(prm_model_id) {
    _TRACE3_("_model_id=" << _model_id << " start");
    _draw_set_num = 0;
    _paVertexBuffer_model = nullptr;
    _paVertexBuffer_instancedata = nullptr;
    _paIndexBuffer = nullptr;
    _pVertexDeclaration = nullptr;
    _size_vertex_unit_instancedata = 0;
    _size_vertex_unit_model = 0;
    _size_vertices_model = 0;
    _nVertices = 0;
    _nFaces= 0;
    _pFunc_getVertexInstanceData = nullptr;
    _pFunc_getVertexModel = nullptr;
    _pInstancedata = nullptr;
    _max_draw_set_num = GGAFDXMASS_MAX_INSTANCE_NUM;
    _obj_class |= Obj_GgafDx_MassModel;
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MassModel::createVertexElements() {
    _TRACE3_("_model_id=" << _model_id << " start");
    HRESULT hr;
    //�f�o�C�X�ɒ��_�t�H�[�}�b�g�o�^
    //���̃����o���ݒ肷��
    //_size_vertex_unit_instancedata
    //_pInstancedata
    //_pVertexDeclaration
    if (_pVertexDeclaration == nullptr) {
#ifdef MY_DEBUG
        if (!_pFunc_getVertexModel) {
            throwCriticalException("_pFunc_getVertexModel ���`���Ă��������B���f�����_��񂪕K�v�ł��B");
        }
        if (!_pFunc_getVertexInstanceData) {
            throwCriticalException("_pFunc_getVertexInstanceData ���`���Ă��������B�C���X�^���X�f�[�^��񂪕K�v�ł��B");
        }
#endif
        VertexModelInfo model_info;
        (*_pFunc_getVertexModel)(this, &model_info); //�R�[���o�b�N
        int model_element_num = model_info.element_num;

        VertexInstanceDataInfo instance_info;
        (*_pFunc_getVertexInstanceData)(this, &instance_info); //�R�[���o�b�N
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

        hr = pCARETAKER->_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(_pVertexDeclaration) );
        checkDxException(hr, D3D_OK, "pCARETAKER->_pID3DDevice9->CreateVertexDeclaration ���s model="<<(_model_id));
        GGAF_DELETEARR(paVtxelem);
    }
    //�f�o�C�X�ɒ��_�o�b�t�@�쐬(�C���X�^���X�f�[�^)
    int size_instancedata = _size_vertex_unit_instancedata * _draw_set_num;//�ő哯���`�搔�m��
    hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
            size_instancedata,
            D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,  //���񏑂��������D3DUSAGE_DYNAMIC
            0,
            D3DPOOL_DEFAULT,
            &(_paVertexBuffer_instancedata),
            nullptr);
    checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer2 ���s model="<<_model_id);
//    void* pDeviceMemory = 0;
//    hr = _paVertexBuffer_instancedata->Lock(0, size_instancedata, (void**)&pDeviceMemory, 0);
//    checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s2 model="<<_model_id);
//    ZeroMemory(pDeviceMemory, size_instancedata);
//    hr = _paVertexBuffer_instancedata->Unlock();
//    checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s2 model="<<_model_id);
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MassModel::resetStreamSourceFreq() {
    _TRACE3_("_model_id=" << _model_id << " start");
    pCARETAKER->_pID3DDevice9->SetStreamSourceFreq( 0, 1 );
    pCARETAKER->_pID3DDevice9->SetStreamSourceFreq( 1, 1 );
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MassModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MassModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
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
    GGAF_RELEASE(_paVertexBuffer_instancedata);
    GGAF_RELEASE(_paVertexBuffer_model);
    GGAF_RELEASE(_paIndexBuffer);
    GGAF_RELEASE(_pVertexDeclaration);
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MassModel::restore() {
    _TRACE3_("MassModel::restore() _model_id=" << _model_id << " start");
    if (pCARETAKER->_is_device_lost_flg  && _paVertexBuffer_instancedata == nullptr) {
        createVertexElements(); //�f�o�C�X���X�g���A���ɌĂяo�����
    }
    _TRACE3_("MassModel::restore() _model_id=" << _model_id << " end");
}

MassModel::~MassModel() {
    //release();
    //��ModelConnection::processReleaseResource(Model* prm_pResource) �ŌĂяo�����
}

