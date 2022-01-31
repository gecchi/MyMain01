#include "jp/ggaf/dx/model/MassMorphMeshModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/MassMorphMeshActor.h"
#include "jp/ggaf/dx/effect/MassMorphMeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/texture/Texture.h"

using namespace GgafDx;

MassMorphMeshModel::MassMorphMeshModel(const char* prm_model_id) : MassModel(prm_model_id) {
    _obj_model |= Obj_GgafDx_MassMorphMeshModel;
    _paVtxBuffer_data_model = nullptr;
    _paIndexBuffer_data = nullptr;
    _paVertexBuffer_model_morph = nullptr;
    _papaVtxBuffer_data_morph_model = nullptr;
    _size_vertices_morph_model = 0;
    _size_vertex_unit_morph_model = 0;
    _morph_target_num = 0;
    _max_draw_set_num = GGAFDXMASS_MAX_INSTANCE_NUM;
    registerCallback_VertexModelInfo(MassMorphMeshModel::createVertexModel); //���_���C�A�E�g���쐬�R�[���o�b�N�֐�
}

void MassMorphMeshModel::createVertexModel(void* prm, MassModel::VertexModelInfo* out_info) {
    MassMorphMeshModel* pModel = (MassMorphMeshModel*)prm;
    int morph_target_num =  pModel->_morph_target_num;
    int element_num = 4+(2*morph_target_num);
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
    st0_offset_next += sizeof(float)*2;
    //���[�t�^�[�Q�b�g���b�V�������_�t�H�[�}�b�g
    int s = 1;
    int POSITION_idx = 1;
    int NORMAL_idx = 1;
    int n = 4;
    for (int i = 1; i <= morph_target_num; i++) {
        //float x, y, z; // ���_���W   POSITION1 �` POSITIONX
        out_info->paElement[n].Stream = s;
        out_info->paElement[n].Offset = 0;
        out_info->paElement[n].Type   = D3DDECLTYPE_FLOAT3;
        out_info->paElement[n].Method = D3DDECLMETHOD_DEFAULT;
        out_info->paElement[n].Usage  = D3DDECLUSAGE_POSITION;
        out_info->paElement[n].UsageIndex = POSITION_idx;    POSITION_idx++;
        n++;
        //float nx, ny, nz; // �@��    NORMAL1 �` NORMALX
        out_info->paElement[n].Stream = s;
        out_info->paElement[n].Offset = sizeof(float)*3;
        out_info->paElement[n].Type   = D3DDECLTYPE_FLOAT3;
        out_info->paElement[n].Method = D3DDECLMETHOD_DEFAULT;
        out_info->paElement[n].Usage  = D3DDECLUSAGE_NORMAL;
        out_info->paElement[n].UsageIndex = NORMAL_idx;       NORMAL_idx++;
        n++;

        s++;
    }
    out_info->element_num = element_num; //D3DVERTEXELEMENT9 �\���̂̔z��v�f��;
}

void MassMorphMeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVtxBuffer_data_model == nullptr) {
        ModelManager* pModelManager = pGOD->_pModelManager;
        ModelManager::MeshXFileFmt xdata;
        std::string model_def_file = std::string(_model_id) + ".meshx";
        std::string model_def_filepath = Model::getModelDefineFilePath(model_def_file);
        pModelManager->obtainMeshModelInfo(&xdata, model_def_filepath);
        _matBaseTransformMatrix = xdata.BaseTransformMatrix;
        _draw_set_num = xdata.DrawSetNum;
        if (_draw_set_num == 0 || _draw_set_num > _max_draw_set_num) {
            _TRACE_("MassMorphMeshModel::restore() "<<_model_id<<" �̓����`��Z�b�g���́A�ő�� "<<_max_draw_set_num<<" �ɍĒ�`����܂����B���R�F_draw_set_num="<<_draw_set_num);
            _draw_set_num = _max_draw_set_num;
        } else {
            _TRACE_("MassMorphMeshModel::restore() "<<_model_id<<" �̓����`��Z�b�g���� "<<_draw_set_num<<" �ł��B");
        }

        _morph_target_num = xdata.XFileNum - 1;
        int morph_target_num = _morph_target_num;
        std::string* paXfilepath = NEW std::string[morph_target_num+1];
        for (int i = 0; i < morph_target_num+1; i++) {
            paXfilepath[i] = Model::getXFilePath(xdata.XFileNames[i]);
        }
        //�������ޒ��_�o�b�t�@�f�[�^�쐬
        ToolBox::IO_Model_X iox;
        Frm::Model3D** papModel3D = NEW Frm::Model3D*[_morph_target_num+1];
        Frm::Mesh** papMeshesFront = NEW Frm::Mesh*[_morph_target_num+1];
        _papaVtxBuffer_data_morph_model = NEW MassMorphMeshModel::VERTEX_model_morph*[_morph_target_num];

        for (int pattern = 0; pattern < _morph_target_num+1; pattern++) {
            papModel3D[pattern] = NEW Frm::Model3D();
            bool r = iox.Load(paXfilepath[pattern], papModel3D[pattern]);
            if (r == false) {
                throwCriticalException("X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<paXfilepath[pattern]);
            }
            //���b�V������������O�ɁA�����m�ۂ��Ă���
            int nMesh = (int)papModel3D[pattern]->_Meshes.size();
            uint16_t* paNumVertices = NEW uint16_t[nMesh];
            int index_Mesh = 0;
            for (std::list<Frm::Mesh*>::iterator iteMeshes = papModel3D[pattern]->_Meshes.begin();
                    iteMeshes != papModel3D[pattern]->_Meshes.end(); iteMeshes++) {
                paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
                index_Mesh++;
            }
            papModel3D[pattern]->ConcatenateMeshes(); //���b�V�����q����
            papMeshesFront[pattern] = papModel3D[pattern]->_Meshes.front();
            _nVertices = papMeshesFront[pattern]->_nVertices;
            uint16_t nTextureCoords = papMeshesFront[pattern]->_nTextureCoords;
            _nFaces = papMeshesFront[pattern]->_nFaces;
    //            nFaceNormals = papMeshesFront[pattern]->_nFaceNormals;
            if (_nVertices > 65535) {
                throwCriticalException("���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<getName()<<"  _nVertices:"<<_nVertices);
            }

            if (pattern == 0) {
                //�v���C�}�����b�V��
                _paVtxBuffer_data_model = NEW MassMorphMeshModel::VERTEX_model_primary[_nVertices];
                _size_vertex_unit_model = sizeof(MassMorphMeshModel::VERTEX_model_primary);
                _size_vertices_model = sizeof(MassMorphMeshModel::VERTEX_model_primary) * _nVertices;
                //�@���ȊO�ݒ�
                for (UINT i = 0; i < _nVertices; i++) {
                    _paVtxBuffer_data_model[i].x = papMeshesFront[pattern]->_Vertices[i].data[0];
                    _paVtxBuffer_data_model[i].y = papMeshesFront[pattern]->_Vertices[i].data[1];
                    _paVtxBuffer_data_model[i].z = papMeshesFront[pattern]->_Vertices[i].data[2];
                    _paVtxBuffer_data_model[i].nx = 0.0f;
                    _paVtxBuffer_data_model[i].ny = 0.0f;
                    _paVtxBuffer_data_model[i].nz = 0.0f;
                    _paVtxBuffer_data_model[i].color = D3DCOLOR_ARGB(255,255,255,255);
                    if (i < nTextureCoords) {
                        _paVtxBuffer_data_model[i].tu = papMeshesFront[pattern]->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
                        _paVtxBuffer_data_model[i].tv = papMeshesFront[pattern]->_TextureCoords[i].data[1];
                    } else {
                        _paVtxBuffer_data_model[i].tu = 0.0f;
                        _paVtxBuffer_data_model[i].tv = 0.0f;
                    }

                }
            } else {
                //���[�t�^�[�Q�b�g���b�V��
                _papaVtxBuffer_data_morph_model[pattern-1] = NEW MassMorphMeshModel::VERTEX_model_morph[_nVertices];
                _size_vertex_unit_morph_model = sizeof(MassMorphMeshModel::VERTEX_model_morph);
                _size_vertices_morph_model = sizeof(MassMorphMeshModel::VERTEX_model_morph) * _nVertices;
                //�@���ȊO�ݒ�
                for (UINT i = 0; i < _nVertices; i++) {
                    _papaVtxBuffer_data_morph_model[pattern-1][i].x = papMeshesFront[pattern]->_Vertices[i].data[0];
                    _papaVtxBuffer_data_morph_model[pattern-1][i].y = papMeshesFront[pattern]->_Vertices[i].data[1];
                    _papaVtxBuffer_data_morph_model[pattern-1][i].z = papMeshesFront[pattern]->_Vertices[i].data[2];
                    _papaVtxBuffer_data_morph_model[pattern-1][i].nx = 0.0f;
                    _papaVtxBuffer_data_morph_model[pattern-1][i].ny = 0.0f;
                    _papaVtxBuffer_data_morph_model[pattern-1][i].nz = 0.0f;
                }
            }

            if (_nVertices < nTextureCoords) {
                _TRACE_("nTextureCoords="<<nTextureCoords<<"/_nVertices="<<_nVertices);
                _TRACE_("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<paXfilepath[pattern]);
            }

            //�@���ݒ��FrameTransformMatrix�K�p
            if (pattern == 0) { //�v���C�}�����b�V��
                prepareVtx((void*)_paVtxBuffer_data_model, _size_vertex_unit_model,
                           papModel3D[pattern], paNumVertices);
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
            } else {            //�^�[�Q�b�g���b�V��
                prepareVtx((void*)(_papaVtxBuffer_data_morph_model[pattern-1]), _size_vertex_unit_morph_model,
                           papModel3D[pattern], paNumVertices);
            }
            GGAF_DELETE(paNumVertices);
        }   // �v���C�}�������[�t�^�[�Q�b�g���[�vEND... for (int pattern = 0; pattern < _morph_target_num+1; pattern++)

        //�C���f�b�N�X�o�b�t�@�擾
        _paIndexBuffer_data = NEW WORD[_nFaces*3];
        for (UINT i = 0; i < _nFaces; i++) {
            _paIndexBuffer_data[i*3 + 0] = papMeshesFront[0]->_Faces[i].data[0];
            _paIndexBuffer_data[i*3 + 1] = papMeshesFront[0]->_Faces[i].data[1];
            _paIndexBuffer_data[i*3 + 2] = papMeshesFront[0]->_Faces[i].data[2];
        }
        //�}�e���A���ݒ�
        setMaterial(papMeshesFront[0]);

        //��Еt��
        for (int pattern = 0; pattern <= _morph_target_num; pattern++) {
            if (papModel3D) {
                Frm::Model3D* p = papModel3D[pattern];
                GGAF_DELETE(p);
            }
        }
        GGAF_DELETEARR(paXfilepath);
        GGAF_DELETEARR(papMeshesFront);
        GGAF_DELETEARR(papModel3D);
    }
    //���_�o�b�t�@�쐬
    if (_paVertexBuffer_model == nullptr) {
        HRESULT hr;
        //�f�o�C�X�ɒ��_�o�b�t�@�쐬(���f��)
        _paVertexBuffer_model_morph = NEW LPDIRECT3DVERTEXBUFFER9[_morph_target_num];
        for (int pattern = 0; pattern < _morph_target_num+1; pattern++) {
            if (pattern == 0) {
                //�v���C�}�����_�o�b�t�@
                hr = God::_pID3DDevice9->CreateVertexBuffer(
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
            } else {
                //���[�t�^�[�Q�b�g���_�o�b�t�@
                hr = God::_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_morph_model,
                        D3DUSAGE_WRITEONLY,
                        0,
                        D3DPOOL_DEFAULT,
                        &(_paVertexBuffer_model_morph[pattern-1]),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s�i���[�t:"<<pattern-1<<"�j model="<<(_model_id));
                //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
                void* pDeviceMemory = 0;
                hr = _paVertexBuffer_model_morph[pattern-1]->Lock(0, _size_vertices_morph_model, (void**)&pDeviceMemory, 0);
                checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s�i���[�t:"<<pattern-1<<"�j model="<<_model_id);
                memcpy(pDeviceMemory, _papaVtxBuffer_data_morph_model[pattern-1], _size_vertices_morph_model); //paVertexBuffer �� paVertex
                hr = _paVertexBuffer_model_morph[pattern-1]->Unlock();
                checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s�i���[�t:"<<pattern-1<<"�j model="<<_model_id);
            }
        }
    }


    //�C���f�b�N�X�o�b�t�@�f�[�^�쐬�i�v���C�}���A���[�t�^�[�Q�b�g���ɓ����j
    if (_paIndexBuffer == nullptr) {
        HRESULT hr;
        hr = God::_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * _nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_paIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_id));
        void* pDeviceMemory = 0;
        _paIndexBuffer->Lock(0,0,(void**)&pDeviceMemory,0);
        memcpy(pDeviceMemory , _paIndexBuffer_data , sizeof(WORD) * _nFaces * 3);
        _paIndexBuffer->Unlock();
    }

    if (_papTextureConnection == nullptr) {
        ModelManager* pModelManager = pGOD->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }
    MassModel::restore(); //��ʂ��Ăяo��
    _TRACE3_("_model_id=" << _model_id << " end");
}

HRESULT MassMorphMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
//    if (_paVertexBuffer_instancedata == nullptr) {
//        createVertexElements(); //�f�o�C�X���X�g���A���ɌĂяo�����
//    }
#ifdef MY_DEBUG
    if (prm_draw_set_num > _draw_set_num) {
        throwCriticalException(FUNC_NAME<<" "<<_model_id<<" �̕`��Z�b�g���I�[�o�[�B_draw_set_num="<<_draw_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* pDevice = God::_pID3DDevice9;
    //�ΏۃA�N�^�[
    const MassMorphMeshActor* const pTargetActor = (MassMorphMeshActor*)prm_pActor_target;
    //�ΏۃA�N�^�[�̃G�t�F�N�g���b�p
    MassMorphMeshEffect* const pMassMorphMeshEffect = (MassMorphMeshEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMassMorphMeshEffect->_pID3DXEffect;

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
    //���_�o�b�t�@�ݒ�
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq(_morph_target_num+1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq "<<_morph_target_num+1<<" D3DSTREAMSOURCE_INSTANCEDATA �Ɏ��s���܂����B");
        hr = pDevice->SetVertexDeclaration(_pVertexDeclaration); //���_�t�H�[�}�b�g
        checkDxException(hr, D3D_OK, "SetVertexDeclaration �Ɏ��s���܂����B");
        hr = pDevice->SetStreamSource(0, _paVertexBuffer_model, 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "SetStreamSource 0 �Ɏ��s���܂����B");
        for (int i = 1; i <= _morph_target_num; i++) {
            hr = pDevice->SetStreamSource(i, _paVertexBuffer_model_morph[i-1], 0, _size_vertex_unit_morph_model);
            checkDxException(hr, D3D_OK, "SetStreamSource "<<i<<" �Ɏ��s���܂����B");
        }
        hr = pDevice->SetStreamSource(_morph_target_num+1, _paVertexBuffer_instancedata, 0, _size_vertex_unit_instancedata);
        checkDxException(hr, D3D_OK, "SetStreamSource "<<_morph_target_num+1<<" �Ɏ��s���܂����B");
        //�C���f�b�N�X�o�b�t�@�ݒ�
        pDevice->SetIndices(_paIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) �Ɏ��s���܂����B");
        if (_papTextureConnection[0]) {
            pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("MassMeshModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(CONFIG::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
            //������΃e�N�X�`������
            pDevice->SetTexture(0, nullptr);
        }
    }
    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
    checkDxException(hr, D3D_OK, "SetStreamSourceFreq 0 �Ɏ��s���܂����BD3DSTREAMSOURCE_INDEXEDDATA prm_draw_set_num="<<prm_draw_set_num);
    for (int i = 1; i <= _morph_target_num; i++) {
        hr = pDevice->SetStreamSourceFreq( i, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq "<<i<<" �Ɏ��s���܂����BD3DSTREAMSOURCE_INDEXEDDATA prm_draw_set_num="<<prm_draw_set_num);
    }


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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassMorphMeshEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");


        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassMorphMeshEffect->_effect_name<<"("<<pMassMorphMeshEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        //���[�t�^�[�Q�b�g�̐��ɂ�� pass ��؂�ւ��Ă���
        //�v���}�����b�V���̂�                             = pass0
        //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���P�� = pass1
        //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���Q�� = pass2
        //�ȉ��ő�X�܂�
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pMassMorphMeshEffect->_begin) {
            throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassMorphMeshEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }

    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassMorphMeshEffect->_effect_name);
    hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                       0,
                                       0,
                                       _nVertices,
                                       0,
                                       _nFaces);
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
        GgafCore::God::_num_drawing++;
#endif
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pMassMorphMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void MassMorphMeshModel::resetStreamSourceFreq() {
    God::_pID3DDevice9->SetStreamSourceFreq( 0, 1 );
    for (int i = 1; i <= _morph_target_num; i++) {
        God::_pID3DDevice9->SetStreamSourceFreq( i, 1 );
    }
    God::_pID3DDevice9->SetStreamSourceFreq( _morph_target_num+1, 1 );
}

void MassMorphMeshModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MassMorphMeshModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    for (int pattern = 1; pattern <= _morph_target_num; pattern++) {
        GGAF_RELEASE(_paVertexBuffer_model_morph[pattern-1]);
    }
    GGAF_DELETEARR(_paVertexBuffer_model_morph);
    _TRACE3_("_model_id=" << _model_id << " end");
    MassModel::release();
}

MassMorphMeshModel::~MassMorphMeshModel() {
    for (int pattern = 1; pattern <= _morph_target_num; pattern++) {
        GGAF_DELETEARR(_papaVtxBuffer_data_morph_model[pattern-1]);
    }
    GGAF_DELETEARR(_papaVtxBuffer_data_morph_model);
    GGAF_DELETEARR(_paVtxBuffer_data_model);
    GGAF_DELETEARR(_paIndexBuffer_data);
}

