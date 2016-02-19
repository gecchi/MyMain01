#include "jp/ggaf/dxcore/model/GgafDxMassMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMeshEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

//DWORD GgafDxMassMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer = nullptr;

GgafDxMassMeshModel::GgafDxMassMeshModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxMassMeshModel::GgafDxMassMeshModel(" << _model_name << ")");
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;
    // prm_model_name �ɂ� "xxxxxx" or "8/xxxxx" ���A�n���Ă���B
    // �����`��Z�b�g����8�Ƃ����Ӗ��ł��B
    // ���[�t�^�[�Q�b�g�����Ⴄ���f���́A�ʃ��f���Ƃ��������ɂ��邽�߁A���f�����ɐ��l���c�������ȁB
    // ���f�������瓯���`��Z�b�g���w�肪����Ύ��o���B�������8
    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
    if (names.size() > 2) {
        throwGgafCriticalException("GgafDxMassMeshModel::GgafDxMassMeshModel "<<
                "prm_model_name �ɂ� \"xxxxxx\" or \"8/xxxxx\" �`�����w�肵�Ă��������B \n"<<
                "���ۂ̈����́Aprm_idstr="<<prm_model_name);
    }
    if (names.size() == 2) {
        _set_num = STOI(names[0]);
        if (_set_num > MAX_INSTACE) {
            _TRACE_("GgafDxMassMeshModel("<<prm_model_name<<") �̓����`��Z�b�g���I�[�o�[�B�ő��"<<MAX_INSTACE<<"�Z�b�g���ł�������ȏオ�ݒ肳��Ă��܂��B�Ӑ}���Ă��܂����H _set_num="<<_set_num<<"�B");
        }
    } else {
        _TRACE_("GgafDxMassMeshModel("<<prm_model_name<<") �̃Z�b�g���ȗ��̂��߁A�W���̍ő��"<<MAX_INSTACE<<"�Z�b�g���ݒ肳��܂��B");
        _set_num = MAX_INSTACE;
    }
    _pVertexBuffer_model = nullptr;
    _pVertexBuffer_instacedata = nullptr;
    _pIndexBuffer = nullptr;
    _pIDirect3DVertexDeclaration9 = nullptr;
    _paVtxBuffer_org_model = nullptr;
    _paIdxBuffer_org = nullptr;
    _size_vertex_unit_instacedata = 0;
    _size_vertex_unit_model = 0;
    _size_vertices_model = 0;
    _nVertices = 0;
    _nFaces= 0;

    _obj_model |= Obj_GgafDxMassMeshModel;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̃����o�[��������
    //void GgafDxModelManager::restoreMassMeshModel(GgafDxMassMeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
    _TRACE_("GgafDxMassMeshModel::GgafDxMassMeshModel(" << _model_name << ") End");
}

void GgafDxMassMeshModel::restore() {
    _TRACE3_("GgafDxMassMeshModel::restore() " << _model_name << " start");
//    GgafDxGod::_pModelManager->restoreMassMeshModel(this);

   /////////////////////////////////////////////////////////////////
    _TRACE3_("GgafDxModelManager::restoreMassMeshModel(" << _model_name << ")");
    std::string xfile_name; //�ǂݍ���X�t�@�C����
    //"12/Eres" or "8/Celes" or "Celes" ���� "Celes" ������Ƃ肾���ăt���p�X���擾
    //TODO:���l�R���ȏ�̎��͂���
    if (*(_model_name + 1) == '/') {
        xfile_name = GgafDxModelManager::getMeshFileName(std::string(_model_name + 2));
    } else if (*(_model_name + 2) == '/') {
        xfile_name = GgafDxModelManager::getMeshFileName(std::string(_model_name + 3));
    } else {
        xfile_name = GgafDxModelManager::getMeshFileName(std::string(_model_name));
    }
    if (xfile_name == "") {
         throwGgafCriticalException("GgafDxModelManager::restoreMassMeshModel ���b�V���t�@�C��(*.x)��������܂���Bmodel_name="<<(_model_name));
    }

    HRESULT hr;
    //�������ޒ��_�o�b�t�@�f�[�^�쐬
    ToolBox::IO_Model_X iox;

    Frm::Model3D* model_pModel3D = nullptr;
    Frm::Mesh* model_pMeshesFront = nullptr;

//    GgafDxMassMeshModel::INDEXPARAM** model_papaIndexParam = nullptr;
//    GgafDxMassMeshModel::VERTEX* unit_paVtxBuffer_org = nullptr;
    GgafDxMassMeshModel::VERTEX_model* model_paVtxBuffer_org_model = nullptr;
//    WORD* unit_paIdxBuffer_org = nullptr;
    WORD* model_paIdxBuffer_org = nullptr;
    D3DMATERIAL9* model_paMaterial = nullptr;
    GgafDxTextureConnection** model_papTextureConnection = nullptr;

    int nVertices = 0;
    int nTextureCoords = 0;
    int nFaces = 0;
//    int nFaceNormals = 0;

    if (_pModel3D == nullptr) {
        model_pModel3D = NEW Frm::Model3D();

        bool r = iox.Load(xfile_name, model_pModel3D);
        if (r == false) {
            throwGgafCriticalException("[GgafDxModelManager::restoreMassMeshModel] X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<xfile_name);
        }

        //���b�V������������O�ɁA�����m�ۂ��Ă���
        int nMesh = (int)model_pModel3D->_Meshes.size();
        uint16_t* paNumVertices = NEW uint16_t[nMesh];
        int index_Mesh = 0;
        for (std::list<Frm::Mesh*>::iterator iteMeshes = model_pModel3D->_Meshes.begin();
                iteMeshes != model_pModel3D->_Meshes.end(); iteMeshes++) {
            paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
            index_Mesh++;
        }
        model_pModel3D->ConcatenateMeshes(); //���b�V�����q����

        model_pMeshesFront = model_pModel3D->_Meshes.front();
        nVertices = model_pMeshesFront->_nVertices;
        nTextureCoords = model_pMeshesFront->_nTextureCoords;
        nFaces = model_pMeshesFront->_nFaces;
//        nFaceNormals = model_pMeshesFront->_nFaceNormals;
        model_paVtxBuffer_org_model = NEW GgafDxMassMeshModel::VERTEX_model[nVertices];

        if (nVertices > 65535) {
            throwGgafCriticalException("[GgafDxModelManager::restoreMassMeshModel] ���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<getName()<<"  nVertices:"<<nVertices);
        }

        _nVertices = nVertices;
        _nFaces = nFaces;
        _size_vertex_unit_model = sizeof(GgafDxMassMeshModel::VERTEX_model);
        _size_vertices_model = sizeof(GgafDxMassMeshModel::VERTEX_model) * nVertices;
        _size_vertex_unit_instacedata = sizeof(GgafDxMassMeshModel::VERTEX_instancedata);

        //�@���ȊO�ݒ�
        FLOAT model_bounding_sphere_radius;
        for (int i = 0; i < nVertices; i++) {
            model_paVtxBuffer_org_model[i].x = model_pMeshesFront->_Vertices[i].data[0];
            model_paVtxBuffer_org_model[i].y = model_pMeshesFront->_Vertices[i].data[1];
            model_paVtxBuffer_org_model[i].z = model_pMeshesFront->_Vertices[i].data[2];
            model_paVtxBuffer_org_model[i].nx = 0.0f;
            model_paVtxBuffer_org_model[i].ny = 0.0f;
            model_paVtxBuffer_org_model[i].nz = 0.0f;
            model_paVtxBuffer_org_model[i].color = D3DCOLOR_ARGB(255,255,255,255); //���_�J���[�͍��̏��g���Ă��Ȃ�
            if (i < nTextureCoords) {
                model_paVtxBuffer_org_model[i].tu = model_pMeshesFront->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
                model_paVtxBuffer_org_model[i].tv = model_pMeshesFront->_TextureCoords[i].data[1];
            } else {
                model_paVtxBuffer_org_model[i].tu = 0;
                model_paVtxBuffer_org_model[i].tv = 0;
            }

            //����
            model_bounding_sphere_radius = (FLOAT)(sqrt(model_paVtxBuffer_org_model[i].x * model_paVtxBuffer_org_model[i].x +
                                                        model_paVtxBuffer_org_model[i].y * model_paVtxBuffer_org_model[i].y +
                                                        model_paVtxBuffer_org_model[i].z * model_paVtxBuffer_org_model[i].z));
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        if (nVertices < nTextureCoords) {
            _TRACE_("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            _TRACE_("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfile_name);
        }
        //�@���ݒ��FrameTransformMatrix�K�p
        prepareVtx((void*)model_paVtxBuffer_org_model, _size_vertex_unit_model,
                                        model_pModel3D, paNumVertices);
        GGAF_DELETE(paNumVertices);

        //�C���f�b�N�X�o�b�t�@�\�z
        model_paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            model_paIdxBuffer_org[i*3 + 0] = model_pMeshesFront->_Faces[i].data[0];
            model_paIdxBuffer_org[i*3 + 1] = model_pMeshesFront->_Faces[i].data[1];
            model_paIdxBuffer_org[i*3 + 2] = model_pMeshesFront->_Faces[i].data[2];
        }

        //���_�o�b�t�@�쐬
        if (_pIDirect3DVertexDeclaration9 == nullptr) {
            D3DVERTEXELEMENT9* paVtxelem = NEW D3DVERTEXELEMENT9[10];
            // Stream = 0 ---->
            WORD  st0_offset_next = 0;
            //float x, y, z;    // :POSITION0 ���_���W
            paVtxelem[0].Stream = 0;
            paVtxelem[0].Offset = st0_offset_next;
            paVtxelem[0].Type   = D3DDECLTYPE_FLOAT3;
            paVtxelem[0].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[0].Usage  = D3DDECLUSAGE_POSITION;
            paVtxelem[0].UsageIndex = 0;
            st0_offset_next += sizeof(float)*3;
            //float nx, ny, nz; // :NORMAL0 �@��
            paVtxelem[1].Stream = 0;
            paVtxelem[1].Offset = st0_offset_next;
            paVtxelem[1].Type   = D3DDECLTYPE_FLOAT3;
            paVtxelem[1].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[1].Usage  = D3DDECLUSAGE_NORMAL;
            paVtxelem[1].UsageIndex = 0;
            st0_offset_next += sizeof(float)*3;
            //DWORD color;     // : COLOR0  ���_�J���[
            paVtxelem[2].Stream = 0;
            paVtxelem[2].Offset = st0_offset_next;
            paVtxelem[2].Type   = D3DDECLTYPE_D3DCOLOR;
            paVtxelem[2].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[2].Usage  = D3DDECLUSAGE_COLOR;
            paVtxelem[2].UsageIndex = 0;
            st0_offset_next += sizeof(DWORD);
            //float tu, tv;    // : TEXCOORD0  �e�N�X�`�����W
            paVtxelem[3].Stream = 0;
            paVtxelem[3].Offset = st0_offset_next;
            paVtxelem[3].Type   = D3DDECLTYPE_FLOAT2;
            paVtxelem[3].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[3].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[3].UsageIndex = 0;
            st0_offset_next += sizeof(float)*2;
            // <---- Stream = 0

            // Stream = 1 ---->
            WORD st1_offset_next = 0;
            //float _11, _12, _13, _14;   // : TEXCOORD1  World�ϊ��s��A�P�s��
            paVtxelem[4].Stream = 1;
            paVtxelem[4].Offset = st1_offset_next;
            paVtxelem[4].Type   = D3DDECLTYPE_FLOAT4;
            paVtxelem[4].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[4].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[4].UsageIndex = 1;
            st1_offset_next += sizeof(float)*4;
            //float _21, _22, _23, _24;  // : TEXCOORD2  World�ϊ��s��A�Q�s��
            paVtxelem[5].Stream = 1;
            paVtxelem[5].Offset = st1_offset_next;
            paVtxelem[5].Type   = D3DDECLTYPE_FLOAT4;
            paVtxelem[5].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[5].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[5].UsageIndex = 2;
            st1_offset_next += sizeof(float)*4;
            //float _31, _32, _33, _34;  // : TEXCOORD3  World�ϊ��s��A�R�s��
            paVtxelem[6].Stream = 1;
            paVtxelem[6].Offset = st1_offset_next;
            paVtxelem[6].Type   = D3DDECLTYPE_FLOAT4;
            paVtxelem[6].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[6].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[6].UsageIndex = 3;
            st1_offset_next += sizeof(float)*4;
            //float _41, _42, _43, _44;  // : TEXCOORD4  World�ϊ��s��A�S�s��
            paVtxelem[7].Stream = 1;
            paVtxelem[7].Offset = st1_offset_next;
            paVtxelem[7].Type   = D3DDECLTYPE_FLOAT4;
            paVtxelem[7].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[7].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[7].UsageIndex = 4;
            st1_offset_next += sizeof(float)*4;
            //float r, g, b, a;        // : TEXCOORD5  �}�e���A���J���[
            paVtxelem[8].Stream = 1;
            paVtxelem[8].Offset = st1_offset_next;
            paVtxelem[8].Type   = D3DDECLTYPE_FLOAT4;
            paVtxelem[8].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[8].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[8].UsageIndex = 5;
            st1_offset_next += sizeof(float)*4;
            // <---- Stream = 1
            //D3DDECL_END()
            paVtxelem[9].Stream = 0xFF;
            paVtxelem[9].Offset = 0;
            paVtxelem[9].Type = D3DDECLTYPE_UNUSED;
            paVtxelem[9].Method = 0;
            paVtxelem[9].Usage = 0;
            paVtxelem[9].UsageIndex = 0;
            hr = GgafDxGod::_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(_pIDirect3DVertexDeclaration9) );
            checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] GgafDxGod::_pID3DDevice9->CreateVertexDeclaration ���s model="<<(_model_name));
            //�X�g���[�����擾        hr = m_pDecl->GetDeclaration( m_pElement, &m_numElements);
            GGAF_DELETEARR(paVtxelem);
        }

    }

    //���_�o�b�t�@�쐬(���f��)
    if (_pVertexBuffer_model == nullptr) {
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices_model,
                D3DUSAGE_WRITEONLY,
                0,
                D3DPOOL_DEFAULT,
                &(_pVertexBuffer_model),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));
        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = _pVertexBuffer_model->Lock(
                                      0,
                                      _size_vertices_model,
                                      (void**)&pVertexBuffer,
                                      0
                                    );
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
        memcpy(
          pVertexBuffer,
          model_paVtxBuffer_org_model,
          _size_vertices_model
        );
        _pVertexBuffer_model->Unlock();
    }

    //���_�o�b�t�@�쐬(�C���X�^���X)
    if (_pVertexBuffer_instacedata == nullptr) {
        int size_instancedata = _size_vertex_unit_instacedata * _set_num;//�ő哯���`�搔�m��
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                size_instancedata,
                D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,  //���񏑂��������D3DUSAGE_DYNAMIC
                0,
                D3DPOOL_DEFAULT,
                &(_pVertexBuffer_instacedata),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] _pID3DDevice9->CreateVertexBuffer2 ���s model="<<(_model_name));
        void *pVertexBuffer_instacedata;
        hr = _pVertexBuffer_instacedata->Lock(
                                      0,
                                      size_instancedata,
                                      (void**)&pVertexBuffer_instacedata,
                                      0
                                    );
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s2 model="<<_model_name);
        ZeroMemory(pVertexBuffer_instacedata, size_instancedata);
        hr = _pVertexBuffer_instacedata->Unlock();
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] ���_�A�����b�N�擾�Ɏ��s2 model="<<_model_name);
    }

    //�C���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (_pIndexBuffer == nullptr) {
        nFaces = model_pMeshesFront->_nFaces;
        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_name));

        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          model_paIdxBuffer_org,
          sizeof(WORD) * nFaces * 3
        );
        _pIndexBuffer->Unlock();
    }


    //�}�e���A���ݒ�
    int model_nMaterials = 0;
    setMaterial(model_pMeshesFront,
                &model_nMaterials, &model_paMaterial, &model_papTextureConnection);

    //���f���ɕێ�������
    _pModel3D = model_pModel3D;
    _pMeshesFront = model_pMeshesFront;
    _paIdxBuffer_org = model_paIdxBuffer_org;
    _paVtxBuffer_org_model = model_paVtxBuffer_org_model;
//    _papaIndexParam = model_papaIndexParam;
    _paMaterial_default = model_paMaterial;
    _papTextureConnection = model_papTextureConnection;
    _num_materials = model_nMaterials;
    _TRACE3_("GgafDxMassMeshModel::restore() " << _model_name << " end");
}

//�`��
HRESULT GgafDxMassMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxMassMeshModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_("GgafDxMassMeshModel::draw() "<<_model_name<<" �̕`��Z�b�g���I�[�o�[�B_set_num="<<_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //�ΏۃA�N�^�[
    const GgafDxMassMeshActor* const pTargetActor = (GgafDxMassMeshActor*)prm_pActor_target;
    //�Ώ�MassMeshActor�̃G�t�F�N�g���b�p
    GgafDxMassMeshEffect* const pMassMeshEffect = (GgafDxMassMeshEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMassMeshEffect->_pID3DXEffect;

    HRESULT hr;

    //���_�o�b�t�@(�C���X�^���X�f�[�^)��������
    UINT update_vertex_instacedata_size = _size_vertex_unit_instacedata * prm_draw_set_num;
    void* pVertexBuffer_instacedata;
    hr = _pVertexBuffer_instacedata->Lock(
                                  0,
                                  update_vertex_instacedata_size,
                                  (void**)&pVertexBuffer_instacedata,
                                  D3DLOCK_DISCARD
                                );
    checkDxException(hr, D3D_OK, "[GgafDxMassMeshModel::draw] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
    memcpy(
      pVertexBuffer_instacedata,
      _aInstancedata,
      update_vertex_instacedata_size
    );
    _pVertexBuffer_instacedata->Unlock();

    //���f���������ł��A�Z�b�g���������Ȃ�Β��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̐ݒ�̓X�L�b�v�ł���
    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
    checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSourceFreq 0 �Ɏ��s���܂����Bprm_draw_set_num="<<prm_draw_set_num);

    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSourceFreq 1 �Ɏ��s���܂����B");
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        hr = pDevice->SetVertexDeclaration(_pIDirect3DVertexDeclaration9); //���_�t�H�[�}�b�g
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetVertexDeclaration �Ɏ��s���܂����B");
        hr = pDevice->SetStreamSource(0, _pVertexBuffer_model      , 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSource 0 �Ɏ��s���܂����B");
        hr = pDevice->SetStreamSource(1, _pVertexBuffer_instacedata, 0, _size_vertex_unit_instacedata);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSource 1 �Ɏ��s���܂����B");
        hr = pDevice->SetIndices(_pIndexBuffer);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetIndices �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) �Ɏ��s���܂����B");
        if (_papTextureConnection[0]) {
            pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("GgafDxMassMeshModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(PROPERTY::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
            //������΃e�N�X�`������
            pDevice->SetTexture(0, nullptr);
        }
    }
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (pEffect_active != pMassMeshEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
        if (pEffect_active) {
            _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() EndPass() �Ɏ��s���܂����B");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwGgafCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxMassMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name<<"("<<pMassMeshEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pMassMeshEffect->_begin) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassMeshEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name);

    hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                  0,
                                  0,
                                  _nVertices,
                                  0,
                                  _nFaces);
    //checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() DrawIndexedPrimitive()  pass=1 �Ɏ��s���܂����B");
    if (_num_pass >= 2) { //�Q�p�X�ڈȍ~������
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() �P�p�X�� EndPass() �Ɏ��s���܂����B");
        for (UINT i = 1; i < _num_pass; i++) {
            hr = pID3DXEffect->BeginPass(i);
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() "<<i+1<<"�p�X�� BeginPass("<<i<<") �Ɏ��s���܂����B");
            hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                          0,
                                          0,
                                          _nVertices,
                                          0,
                                          _nFaces);
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() DrawIndexedPrimitive()  pass="<<(i+1)<<" �Ɏ��s���܂����B");
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() "<<i+1<<"�p�X�� EndPass() �Ɏ��s���܂����B");
        }
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() �P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
    }

//    pDevice->SetStreamSourceFreq( 0, 1 );
//    pDevice->SetStreamSourceFreq( 1, 1 );

    GgafGod::_num_drawing++;
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMassMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}


void GgafDxMassMeshModel::onDeviceLost() {
    _TRACE3_("GgafDxMassMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxMassMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMassMeshModel::release() {
    _TRACE3_("GgafDxMassMeshModel::release() " << _model_name << " start");

    //�e�N�X�`�������
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //�e�N�X�`���̔z��
    GGAF_RELEASE(_pVertexBuffer_instacedata);
    GGAF_RELEASE(_pVertexBuffer_model);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_RELEASE(_pIDirect3DVertexDeclaration9);

    GGAF_DELETEARR(_paVtxBuffer_org_model);
    GGAF_DELETEARR(_paIdxBuffer_org);

    GGAF_DELETE(_pModel3D);
    //_pMeshesFront �� _pModel3D ��DELETE���Ă���̂ł���K�v�͖���
    _pMeshesFront = nullptr;

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);

    _TRACE3_("GgafDxMassMeshModel::release() " << _model_name << " end");

}
GgafDxMassMeshModel::~GgafDxMassMeshModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

