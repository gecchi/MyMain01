#include "jp/ggaf/dx/model/MassMeshModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/MassMeshActor.h"
#include "jp/ggaf/dx/effect/MassMeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;

MassMeshModel::MassMeshModel(const char* prm_model_id) : MassModel(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_MassMeshModel;
    _paVtxBuffer_data_model = nullptr;
    _paIndexBuffer_data = nullptr;
    registerCallback_VertexModelInfo(MassMeshModel::createVertexModel); //���_���C�A�E�g���쐬�R�[���o�b�N�֐�
    _max_draw_set_num = GGAFDXMASS_MAX_INSTANCE_NUM;
    _TRACE_("MassMeshModel::MassMeshModel(" << _model_id << ") End");
}

void MassMeshModel::createVertexModel(void* prm, MassModel::VertexModelInfo* out_info) {
    int element_num = 4;
    out_info->paElement = NEW D3DVERTEXELEMENT9[element_num];
    WORD  st0_offset_next = 0;
    //float x, y, z;    // :POSITION0 ���_���W
    out_info->paElement[0].Stream = 0;
    out_info->paElement[0].Offset = st0_offset_next;
    out_info->paElement[0].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[0].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[0].Usage  = D3DDECLUSAGE_POSITION;
    out_info->paElement[0].UsageIndex = 0;
    st0_offset_next += sizeof(float)*3;
    //float nx, ny, nz; // :NORMAL0 �@��
    out_info->paElement[1].Stream = 0;
    out_info->paElement[1].Offset = st0_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_NORMAL;
    out_info->paElement[1].UsageIndex = 0;
    st0_offset_next += sizeof(float)*3;
    //DWORD color;     // : COLOR0  ���_�J���[
    out_info->paElement[2].Stream = 0;
    out_info->paElement[2].Offset = st0_offset_next;
    out_info->paElement[2].Type   = D3DDECLTYPE_D3DCOLOR;
    out_info->paElement[2].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[2].Usage  = D3DDECLUSAGE_COLOR;
    out_info->paElement[2].UsageIndex = 0;
    st0_offset_next += sizeof(DWORD);
    //float tu, tv;    // : TEXCOORD0  �e�N�X�`�����W
    out_info->paElement[3].Stream = 0;
    out_info->paElement[3].Offset = st0_offset_next;
    out_info->paElement[3].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[3].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[3].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[3].UsageIndex = 0;
    //st0_offset_next += sizeof(float)*2;

    out_info->element_num = element_num;
}

void MassMeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVtxBuffer_data_model == nullptr) {
        HRESULT hr;
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::MeshXFileFmt xdata;
        std::string model_def_file = std::string(_model_id) + ".meshx";
        std::string model_def_filepath = Model::getModelDefineFilePath(model_def_file);
        pModelManager->obtainMeshModelInfo(&xdata, model_def_filepath);
        _matBaseTransformMatrix = xdata.BaseTransformMatrix;
        _draw_set_num = xdata.DrawSetNum;
        if (_draw_set_num == 0 || _draw_set_num > _max_draw_set_num) {
            _TRACE_("MassMeshModel::restore() "<<_model_id<<" �̓����`��Z�b�g���́A�ő�� "<<_max_draw_set_num<<" �ɍĒ�`����܂����B���R�F_draw_set_num="<<_draw_set_num);
            _draw_set_num = _max_draw_set_num;
        } else {
            _TRACE_("MassMeshModel::restore() "<<_model_id<<" �̓����`��Z�b�g���� "<<_draw_set_num<<" �ł��B");
        }

        std::string xfilepath = Model::getXFilePath(xdata.XFileNames[0]);
        //�������ޒ��_�o�b�t�@�f�[�^�쐬
        ToolBox::IO_Model_X iox;
        Frm::Model3D* pModel3D = NEW Frm::Model3D();
        bool r = iox.Load(xfilepath, pModel3D);
        if (r == false) {
            throwCriticalException("X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<xfilepath);
        }

        //���b�V������������O�ɁA�����m�ۂ��Ă���
        int nMesh = (int)pModel3D->_Meshes.size();
        uint16_t* paNumVertices = NEW uint16_t[nMesh];
        int index_Mesh = 0;
        for (std::list<Frm::Mesh*>::iterator iteMeshes = pModel3D->_Meshes.begin();
                iteMeshes != pModel3D->_Meshes.end(); iteMeshes++) {
            paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
            index_Mesh++;
        }
        pModel3D->ConcatenateMeshes(); //���b�V�����q����

        Frm::Mesh* pMeshesFront = pModel3D->_Meshes.front();
        _nVertices = pMeshesFront->_nVertices;
        _nFaces = pMeshesFront->_nFaces;
        if (_nVertices > 65535) {
            throwCriticalException("���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<getName()<<"  _nVertices:"<<_nVertices);
        }
        UINT nTextureCoords = pMeshesFront->_nTextureCoords;
//        nFaceNormals = pMeshesFront->_nFaceNormals;
        _paVtxBuffer_data_model = NEW MassMeshModel::VERTEX_model[_nVertices];
        _size_vertex_unit_model = sizeof(MassMeshModel::VERTEX_model);
        _size_vertices_model = sizeof(MassMeshModel::VERTEX_model) * _nVertices;
        //�@���ȊO�ݒ�
        for (UINT i = 0; i < _nVertices; i++) {
            _paVtxBuffer_data_model[i].x = pMeshesFront->_Vertices[i].data[0];
            _paVtxBuffer_data_model[i].y = pMeshesFront->_Vertices[i].data[1];
            _paVtxBuffer_data_model[i].z = pMeshesFront->_Vertices[i].data[2];
            _paVtxBuffer_data_model[i].nx = 0.0f;
            _paVtxBuffer_data_model[i].ny = 0.0f;
            _paVtxBuffer_data_model[i].nz = 0.0f;
            _paVtxBuffer_data_model[i].color = D3DCOLOR_ARGB(255,255,255,255); //���_�J���[�͍��̏��g���Ă��Ȃ�
            if (i < nTextureCoords) {
                _paVtxBuffer_data_model[i].tu = pMeshesFront->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
                _paVtxBuffer_data_model[i].tv = pMeshesFront->_TextureCoords[i].data[1];
            } else {
                _paVtxBuffer_data_model[i].tu = 0;
                _paVtxBuffer_data_model[i].tv = 0;
            }
        }

        if (_nVertices < nTextureCoords) {
            _TRACE_("nTextureCoords="<<nTextureCoords<<"/_nVertices="<<_nVertices);
            _TRACE_("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfilepath);
        }
        //�@���ݒ��FrameTransformMatrix�K�p
        prepareVtx((void*)_paVtxBuffer_data_model, _size_vertex_unit_model,
                   pModel3D, paNumVertices);
        GGAF_DELETE(paNumVertices);

        //����
        FLOAT model_bounding_sphere_radius;
        for (UINT i = 0; i < _nVertices; i++) {
            model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data_model[i].x * _paVtxBuffer_data_model[i].x +
                                                        _paVtxBuffer_data_model[i].y * _paVtxBuffer_data_model[i].y +
                                                        _paVtxBuffer_data_model[i].z * _paVtxBuffer_data_model[i].z));
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        //�C���f�b�N�X�o�b�t�@�\�z
        _paIndexBuffer_data = NEW WORD[_nFaces*3];
        for (UINT i = 0; i < _nFaces; i++) {
            _paIndexBuffer_data[i*3 + 0] = pMeshesFront->_Faces[i].data[0];
            _paIndexBuffer_data[i*3 + 1] = pMeshesFront->_Faces[i].data[1];
            _paIndexBuffer_data[i*3 + 2] = pMeshesFront->_Faces[i].data[2];
        }
        //�}�e���A���ݒ�
        setMaterial(pMeshesFront);
        GGAF_DELETE(pModel3D);
    }

    //�f�o�C�X�ɒ��_�o�b�t�@�쐬(���f��)
    if (_paVertexBuffer_model == nullptr) {
        HRESULT hr;
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices_model,
                D3DUSAGE_WRITEONLY,
                0,
                D3DPOOL_DEFAULT,
                &(_paVertexBuffer_model),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_id));
        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void* pDeviceMemory = 0;
        hr = _paVertexBuffer_model->Lock(0, _size_vertices_model, (void**)&pDeviceMemory, 0);
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_id);
        memcpy(pDeviceMemory, _paVtxBuffer_data_model, _size_vertices_model);
        hr = _paVertexBuffer_model->Unlock();
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s model="<<_model_id);
    }

    //�f�o�C�X�ɃC���f�b�N�X�o�b�t�@�쐬
    if (_paIndexBuffer == nullptr) {
        HRESULT hr;
        hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * _nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_paIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<_model_id);
        void* pDeviceMemory = 0;
        hr = _paIndexBuffer->Lock(0, 0, (void**)&pDeviceMemory,0);
        checkDxException(hr, D3D_OK, "�C���f�b�N�X�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_id);
        memcpy(pDeviceMemory, _paIndexBuffer_data, sizeof(WORD)*_nFaces*3);
        hr = _paIndexBuffer->Unlock();
        checkDxException(hr, D3D_OK, "�C���f�b�N�X�o�b�t�@�̃A�����b�N�擾�Ɏ��s model="<<_model_id);
    }

    //�f�o�C�X�Ƀe�N�X�`���쐬
    if (_papTextureConnection == nullptr) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }

    MassModel::restore(); //��ʂ��Ăяo��
    _TRACE3_("_model_id=" << _model_id << " end");
}

HRESULT MassMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("MassMeshModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
//    if (_paVertexBuffer_instancedata == nullptr) {
//        createVertexElements(); //�f�o�C�X���X�g���A���ɌĂяo�����
//    }
#ifdef MY_DEBUG
    if (prm_draw_set_num > _draw_set_num) {
        throwCriticalException(FUNC_NAME<<" "<<_model_id<<" �̕`��Z�b�g���I�[�o�[�B_draw_set_num="<<_draw_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* pDevice = pCARETAKER->_pID3DDevice9;
    //�ΏۃA�N�^�[
    const MassMeshActor* pTargetActor = (MassMeshActor*)prm_pActor_target;
    //�Ώ�MassMeshActor�̃G�t�F�N�g���b�p
    MassMeshEffect* pMassMeshEffect = (MassMeshEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMassMeshEffect->_pID3DXEffect;

    HRESULT hr;
    //���_�o�b�t�@(�C���X�^���X�f�[�^)��������
    UINT update_vertex_instancedata_size = _size_vertex_unit_instancedata * prm_draw_set_num;
    void* pInstancedata = prm_pPrm ? prm_pPrm : this->_pInstancedata; //prm_pPrm �͗Վ��̃e���|�����C���X�^���X�f�[�^
    void* pDeviceMemory = 0;
    hr = _paVertexBuffer_instancedata->Lock(0, update_vertex_instancedata_size, (void**)&pDeviceMemory, D3DLOCK_DISCARD);
    checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_id);
    memcpy(pDeviceMemory, pInstancedata, update_vertex_instancedata_size);
    hr = _paVertexBuffer_instancedata->Unlock();
    checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s model="<<_model_id);

    //���f���������Ȃ�Β��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̐ݒ�̓X�L�b�v�ł���
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq 1 �Ɏ��s���܂����B");
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        hr = pDevice->SetVertexDeclaration(_pVertexDeclaration); //���_�t�H�[�}�b�g
        checkDxException(hr, D3D_OK, "SetVertexDeclaration �Ɏ��s���܂����B");
        hr = pDevice->SetStreamSource(0, _paVertexBuffer_model      , 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "SetStreamSource 0 �Ɏ��s���܂����B");
        hr = pDevice->SetStreamSource(1, _paVertexBuffer_instancedata, 0, _size_vertex_unit_instancedata);
        checkDxException(hr, D3D_OK, "SetStreamSource 1 �Ɏ��s���܂����B");
        hr = pDevice->SetIndices(_paIndexBuffer);
        checkDxException(hr, D3D_OK, "SetIndices �Ɏ��s���܂����B");

        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) �Ɏ��s���܂����B");
        if (_papTextureConnection[0]) {
            hr = pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("MassMeshModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(CONFIG::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
            //������΃e�N�X�`������
            hr = pDevice->SetTexture(0, nullptr);
        }
        checkDxException(hr, D3D_OK, "SetTexture �Ɏ��s���܂���");
    }
    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
    checkDxException(hr, D3D_OK, "SetStreamSourceFreq 0 �Ɏ��s���܂����Bprm_draw_set_num="<<prm_draw_set_num);

    Effect* pEffect_active = EffectManager::_pEffect_active;
    if (FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
        if (pEffect_active) {
            _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassMeshEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassMeshEffect->_effect_name<<"("<<pMassMeshEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pMassMeshEffect->_begin) {
            throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassMeshEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassMeshEffect->_effect_name);

    hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                       0,
                                       0,
                                       _nVertices,
                                       0,
                                       _nFaces);
    //checkDxException(hr, D3D_OK, " pass=1 �Ɏ��s���܂����B");
    if (_num_pass >= 2) { //�Q�p�X�ڈȍ~������
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
        for (UINT i = 1; i < _num_pass; i++) {
            hr = pID3DXEffect->BeginPass(i);
            checkDxException(hr, D3D_OK, i+1<<"�p�X�� BeginPass("<<i<<") �Ɏ��s���܂����B");
            hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                               0,
                                               0,
                                               _nVertices,
                                               0,
                                               _nFaces);
            checkDxException(hr, D3D_OK, " pass="<<(i+1)<<" �Ɏ��s���܂����B");
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
        }
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "�P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
    }
#ifdef MY_DEBUG
        GgafCore::Caretaker::_num_drawing++;
#endif
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pMassMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

MassMeshModel::~MassMeshModel() {
    GGAF_DELETEARR(_paVtxBuffer_data_model);
    GGAF_DELETEARR(_paIndexBuffer_data);
}

