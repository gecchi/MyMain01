#include "jp/ggaf/dxcore/model/GgafDxMassMorphMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMorphMeshEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassMorphMeshActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassMorphMeshModel::GgafDxMassMorphMeshModel(const char* prm_model_name) : GgafDxMassModel(prm_model_name) {
    _paVtxBuffer_data_model = nullptr;
    _paIndexBuffer_data = nullptr;

    _pVertexBuffer_model_morph = nullptr;
    _papaVtxBuffer_data_morph_model = nullptr;
    _size_vertices_morph_model = 0;
    _size_vertex_unit_morph_model = 0;

    _obj_model |= Obj_GgafDxMassMorphMeshModel;


    registerCallback_VertexModelInfo(GgafDxMassMorphMeshModel::createVertexModel); //���_���C�A�E�g���쐬�R�[���o�b�N�֐�

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreMassMorphMeshModel(GgafDxMassMorphMeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
    _TRACE_("GgafDxMassMorphMeshModel::GgafDxMassMorphMeshModel(" << _model_name << ") End");
}

void GgafDxMassMorphMeshModel::createVertexModel(void* prm, GgafDxMassModel::VertexModelInfo* out_info) {
    GgafDxMassMorphMeshModel* pModel = (GgafDxMassMorphMeshModel*)prm;
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

void GgafDxMassMorphMeshModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");

    if (!_paVtxBuffer_data_model) {
        // _model_name �ɂ� "8/xxx_4" or "xxx_4" �Ƃ��������񂪓n���Ă���B (/��_�͋�؂蕶��)
        // 8   �F�����`��Z�b�g��(�ȗ��� GGAFDXMASS_MAX_INSTACE_NUM)
        // xxx �F���f����
        // 4   �F���[�t�^�[�Q�b�g��
        std::vector<std::string> names = UTIL::split(std::string(_model_name), "/");
        std::string xname = "";
        if (names.size() == 1) {
            _TRACE_(FUNC_NAME<<" "<<_model_name<<" �̍ő哯���`��I�u�W�F�N�g���́A�f�t�H���g��"<<GGAFDXMASS_MAX_INSTACE_NUM<<" ���ݒ肳��܂����B");
            _set_num = GGAFDXMASS_MAX_INSTACE_NUM;
            xname = names[0];
        } else if (names.size() == 2) {
            _set_num = STOI(names[0]);  // "8/xxx_4" �� 8 ������
            xname = names[1];            // "8/xxx_4" �� xxx_4 ������
        } else {
            throwGgafCriticalException("_model_name �ɂ� \"8/xxx_4\" or \"xxx_4\" �`�����w�肵�Ă��������B \n"<<
                    "���ۂ́A_model_name="<<_model_name<<" �ł����B");
        }
        if (_set_num < 1 || _set_num > GGAFDXMASS_MAX_INSTACE_NUM) {
            throwGgafCriticalException(_model_name<<"�̍ő哯���`��I�u�W�F�N�g�����s���B�͈͂� 1�`"<<GGAFDXMASS_MAX_INSTACE_NUM<<"�Z�b�g�ł��B_set_num="<<_set_num);
        }

        std::string::size_type pos = xname.find_last_of('_');
        if (pos == std::string::npos) {
            throwGgafCriticalException("_model_name �ɂ� \"8/xxx_4\" or \"xxx_4\" �`�����w�肵�Ă��������B \n"<<
                    "���ۂ́A_model_name="<<_model_name<<" �ł����B(2)");
        }
        std::string str_model = xname.substr(0, pos);  // "8/xxx_4" �� xxx ������
        std::string str_t_num = xname.substr(pos + 1); // "8/xxx_4" �� 4 ������
        _morph_target_num = STOI(str_t_num);

        std::string* xfile_names = NEW std::string[_morph_target_num+1];

        for(int i = 0; i < _morph_target_num+1; i++) {
            xfile_names[i] = GgafDxModelManager::getMeshFileName(str_model + "_" + XTOS(i));
        }
        HRESULT hr;
        D3DMATERIAL9*                         paMaterial = nullptr;

        GgafDxTextureConnection** model_papTextureConnection = nullptr;

        //�������ޒ��_�o�b�t�@�f�[�^�쐬
        ToolBox::IO_Model_X iox;
        Frm::Model3D** papModel3D = NEW Frm::Model3D*[_morph_target_num+1];
        Frm::Mesh** papMeshesFront = NEW Frm::Mesh*[_morph_target_num+1];
        _papaVtxBuffer_data_morph_model = NEW GgafDxMassMorphMeshModel::VERTEX_model_morph*[_morph_target_num];

        for (int pattern = 0; pattern < _morph_target_num+1; pattern++) {
            papModel3D[pattern] = NEW Frm::Model3D();
            bool r = iox.Load(xfile_names[pattern], papModel3D[pattern]);
            if (r == false) {
                throwGgafCriticalException("X�t�@�C���̓Ǎ��ݎ��s�B2/ �Ƃ��Y��Ă܂��񂩁H �Ώ�="<<xfile_names[pattern]);
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
                throwGgafCriticalException("���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<getName()<<"  _nVertices:"<<_nVertices);
            }

            if (pattern == 0) {
                //�v���C�}�����b�V��
                _paVtxBuffer_data_model = NEW VERTEX_model_primary[_nVertices];
                _size_vertex_unit_model = sizeof(VERTEX_model_primary);
                _size_vertices_model = sizeof(VERTEX_model_primary) * _nVertices;
                //�@���ȊO�ݒ�
                FLOAT model_bounding_sphere_radius;
                for (int i = 0; i < _nVertices; i++) {
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

                    //����
                    model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data_model[i].x * _paVtxBuffer_data_model[i].x +
                                                                _paVtxBuffer_data_model[i].y * _paVtxBuffer_data_model[i].y +
                                                                _paVtxBuffer_data_model[i].z * _paVtxBuffer_data_model[i].z));
                    if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                        _bounding_sphere_radius = model_bounding_sphere_radius;
                    }
                }
            } else {
                //���[�t�^�[�Q�b�g���b�V��
                _papaVtxBuffer_data_morph_model[pattern-1] = NEW VERTEX_model_morph[_nVertices];
                _size_vertex_unit_morph_model = sizeof(VERTEX_model_morph);
                _size_vertices_morph_model = sizeof(VERTEX_model_morph) * _nVertices;
                //�@���ȊO�ݒ�
                for (int i = 0; i < _nVertices; i++) {
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
                _TRACE_("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfile_names[pattern]);
            }

            //�@���ݒ��FrameTransformMatrix�K�p
            if (pattern == 0) { //�v���C�}�����b�V��
                prepareVtx((void*)_paVtxBuffer_data_model, _size_vertex_unit_model,
                           papModel3D[pattern], paNumVertices);
            } else {            //�^�[�Q�b�g���b�V��
                prepareVtx((void*)(_papaVtxBuffer_data_morph_model[pattern-1]), _size_vertex_unit_morph_model,
                           papModel3D[pattern], paNumVertices);
            }
            GGAF_DELETE(paNumVertices);
        }   // �v���C�}�������[�t�^�[�Q�b�g���[�vEND... for (int pattern = 0; pattern < _morph_target_num+1; pattern++)

        //�C���f�b�N�X�o�b�t�@�擾
        _paIndexBuffer_data = NEW WORD[_nFaces*3];
        for (int i = 0; i < _nFaces; i++) {
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
        GGAF_DELETEARR(xfile_names);
        GGAF_DELETEARR(papMeshesFront);
        GGAF_DELETEARR(papModel3D);
    }



    //���_�o�b�t�@�쐬
    HRESULT hr;
    if (_pVertexBuffer_model == nullptr) {
        //�f�o�C�X�ɒ��_�o�b�t�@�쐬(���f��)
        _pVertexBuffer_model_morph = NEW LPDIRECT3DVERTEXBUFFER9[_morph_target_num];
        for (int pattern = 0; pattern < _morph_target_num+1; pattern++) {
            if (pattern == 0) {
                //�v���C�}�����_�o�b�t�@
                hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_model,
                        D3DUSAGE_WRITEONLY,
                        0,
                        D3DPOOL_DEFAULT,
                        &(_pVertexBuffer_model),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));
                //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
                void *pDeviceMemory;
                hr = _pVertexBuffer_model->Lock(0, _size_vertices_model, (void**)&pDeviceMemory, 0);
                checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
                memcpy(pDeviceMemory, _paVtxBuffer_data_model, _size_vertices_model);
                hr = _pVertexBuffer_model->Unlock();
                checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s model="<<_model_name);
            } else {
                //���[�t�^�[�Q�b�g���_�o�b�t�@
                hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_morph_model,
                        D3DUSAGE_WRITEONLY,
                        0,
                        D3DPOOL_DEFAULT,
                        &(_pVertexBuffer_model_morph[pattern-1]),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s�i���[�t:"<<pattern-1<<"�j model="<<(_model_name));
                //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
                void *pDeviceMemory;
                hr = _pVertexBuffer_model_morph[pattern-1]->Lock(0, _size_vertices_morph_model, (void**)&pDeviceMemory, 0);
                checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s�i���[�t:"<<pattern-1<<"�j model="<<_model_name);
                memcpy(pDeviceMemory, _papaVtxBuffer_data_morph_model[pattern-1], _size_vertices_morph_model); //pVertexBuffer �� paVertex
                hr = _pVertexBuffer_model_morph[pattern-1]->Unlock();
                checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s�i���[�t:"<<pattern-1<<"�j model="<<_model_name);
            }
        }
    }


    //�C���f�b�N�X�o�b�t�@�f�[�^�쐬�i�v���C�}���A���[�t�^�[�Q�b�g���ɓ����j
    if (_pIndexBuffer == nullptr) {
        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * _nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_name));
        void* pDeviceMemory;
        _pIndexBuffer->Lock(0,0,(void**)&pDeviceMemory,0);
        memcpy(pDeviceMemory , _paIndexBuffer_data , sizeof(WORD) * _nFaces * 3);
        _pIndexBuffer->Unlock();
    }

    if (!_papTextureConnection) {
        _papTextureConnection = NEW GgafDxTextureConnection*[_num_materials];
        for (int n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }
    _TRACE3_("_model_name=" << _model_name << " end");
}

HRESULT GgafDxMassMorphMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    if (_pVertexBuffer_instacedata == nullptr) {
        createVertexElements(); //�f�o�C�X���X�g���A���ɌĂяo�����
    }
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        throwGgafCriticalException(FUNC_NAME<<" "<<_model_name<<" �̕`��Z�b�g���I�[�o�[�B_set_num="<<_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    //�ΏۃA�N�^�[
    const GgafDxMassMorphMeshActor* const pTargetActor = (GgafDxMassMorphMeshActor*)prm_pActor_target;
    //�ΏۃA�N�^�[�̃G�t�F�N�g���b�p
    GgafDxMassMorphMeshEffect* const pMassMorphMeshEffect = (GgafDxMassMorphMeshEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMassMorphMeshEffect->_pID3DXEffect;

    HRESULT hr;

    //���_�o�b�t�@(�C���X�^���X�f�[�^)��������
    UINT update_vertex_instacedata_size = _size_vertex_unit_instacedata * prm_draw_set_num;
    void* pInstancedata = prm_pPrm ? prm_pPrm : this->_pInstancedata; //prm_pPrm �͗Վ��̃e���|�����C���X�^���X�f�[�^
    void* pDeviceMemory;
    hr = _pVertexBuffer_instacedata->Lock(0, update_vertex_instacedata_size, (void**)&pDeviceMemory, D3DLOCK_DISCARD);
    checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
    memcpy(pDeviceMemory, pInstancedata, update_vertex_instacedata_size);
    hr = _pVertexBuffer_instacedata->Unlock();
    checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s model="<<_model_name);

    //���f���������Ȃ�Β��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̐ݒ�̓X�L�b�v�ł���
    //���_�o�b�t�@�ݒ�
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq(_morph_target_num+1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq "<<_morph_target_num+1<<" D3DSTREAMSOURCE_INSTANCEDATA �Ɏ��s���܂����B");
        hr = pDevice->SetVertexDeclaration(_pVertexDeclaration); //���_�t�H�[�}�b�g
        checkDxException(hr, D3D_OK, "SetVertexDeclaration �Ɏ��s���܂����B");
        hr = pDevice->SetStreamSource(0, _pVertexBuffer_model, 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "SetStreamSource 0 �Ɏ��s���܂����B");
        for (int i = 1; i <= _morph_target_num; i++) {
            hr = pDevice->SetStreamSource(i, _pVertexBuffer_model_morph[i-1], 0, _size_vertex_unit_morph_model);
            checkDxException(hr, D3D_OK, "SetStreamSource "<<i<<" �Ɏ��s���܂����B");
        }
        hr = pDevice->SetStreamSource(_morph_target_num+1, _pVertexBuffer_instacedata, 0, _size_vertex_unit_instacedata);
        checkDxException(hr, D3D_OK, "SetStreamSource "<<_morph_target_num+1<<" �Ɏ��s���܂����B");
        //�C���f�b�N�X�o�b�t�@�ݒ�
        pDevice->SetIndices(_pIndexBuffer);

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
            _TRACE_("GgafDxMassMeshModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(PROPERTY::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
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


    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
        if (pEffect_active) {
           _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwGgafCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMorphMeshEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");


        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMorphMeshEffect->_effect_name<<"("<<pMassMorphMeshEffect<<")");
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
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassMorphMeshEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }

    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMorphMeshEffect->_effect_name);
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
    ++GgafGod::_num_drawing;
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMassMorphMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxMassMorphMeshModel::resetStreamSourceFreq() {
    GgafDxGod::_pID3DDevice9->SetStreamSourceFreq( 0, 1 );
    for (int i = 1; i <= _morph_target_num; i++) {
        GgafDxGod::_pID3DDevice9->SetStreamSourceFreq( i, 1 );
    }
    GgafDxGod::_pID3DDevice9->SetStreamSourceFreq( _morph_target_num+1, 1 );
}

void GgafDxMassMorphMeshModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxMassMorphMeshModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    for (int pattern = 1; pattern <= _morph_target_num; pattern++) {
        GGAF_RELEASE(_pVertexBuffer_model_morph[pattern-1]);
    }
    GGAF_DELETEARR(_pVertexBuffer_model_morph);
    _TRACE3_("_model_name=" << _model_name << " end");
    GgafDxMassModel::release();
}

GgafDxMassMorphMeshModel::~GgafDxMassMorphMeshModel() {
    for (int pattern = 1; pattern <= _morph_target_num; pattern++) {
        GGAF_DELETEARR(_papaVtxBuffer_data_morph_model[pattern-1]);
    }
    GGAF_DELETEARR(_papaVtxBuffer_data_morph_model);
    GGAF_DELETEARR(_paVtxBuffer_data_model);
    GGAF_DELETEARR(_paIndexBuffer_data);
}

