#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


int GgafDx9ModelManager::_id_max = 0;
int GgafDx9ModelManager::_id_lastdraw = -1;
GgafDx9ModelManager::GgafDx9ModelManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Model> (prm_manager_name) {

    //�e�N�X�`���}�l�W���[
    _pTextureManager = NEW GgafDx9TextureManager("GgafDx9TextureManager");
    //�|���S����`�t�@�C���Ǎ���
    DirectXFileCreate( &_pIDirectXFile );
    char* paChar_SpriteModelineTemplate = GgafUtil::getFileText(GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + "ggaf_spritemodel_define.x");
    if (paChar_SpriteModelineTemplate == NULL) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] �X�v���C�g���Ǎ��݃e���v���[�g\""<<GGAFDX9_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_spritemodel_define.x\" ���J���܂���B");
    }
    HRESULT hr = _pIDirectXFile->RegisterTemplates(paChar_SpriteModelineTemplate, (DWORD)(strlen(paChar_SpriteModelineTemplate)));
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] RegisterTemplates�Ɏ��s���܂����B\""<<GGAFDX9_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_spritemodel_define.x\"���m�F���ĉ������B");
    }
    DELETE_IMPOSSIBLE_NULL(paChar_SpriteModelineTemplate);
}

GgafDx9Model* GgafDx9ModelManager::processCreateResource(char* prm_idstr) {
    //�U�蕪��
    char model_type = *prm_idstr; //���ꕶ��
    char* model_name = prm_idstr + 2; //�R�����ڈȍ~
    GgafDx9Model* model;
    switch (model_type) {
        case 'M':
            //MeshModel
            model = createMeshModel(model_name, D3DXMESH_SYSTEMMEM);
            break;
        case 'm':
            //DynaMeshModel
            model = createMeshModel(model_name, D3DXMESH_DYNAMIC);
            break;
        case 'X':
            //PrimitiveModel
            model = createPrimitiveModel(model_name);
            break;
        case 'S':
            //SpriteModel
            model = createSpriteModel(model_name);
            break;
        case 'P':
            //PlateModel
            model = createPlateModel(model_name);
            break;
        case 'C':
            //cubeModel
            model = createMeshModel("cube", D3DXMESH_SYSTEMMEM);
            break;
        case 'Q':
            //SquareModel
            model = createSquareModel(model_name);
            break;
        default:
            TRACE("GgafDx9ModelManager::processCreateResource("<<prm_idstr<<") ����Ȏ�ʂ͂���܂���");
            throwGgafCriticalException("GgafDx9ModelManager::processCreateResource("<<prm_idstr<<") ����ȃ��f����ʂ͒m��܂���");
            model = NULL;
            break;
    }
    return model;
}

GgafDx9MeshModel* GgafDx9ModelManager::createMeshModel(char* prm_model_name, DWORD prm_dwOptions) {
    GgafDx9MeshModel* pMeshModel_New = NEW GgafDx9MeshModel(prm_model_name, prm_dwOptions);
    restoreMeshModel(pMeshModel_New);
    return pMeshModel_New;
}

GgafDx9SpriteModel* GgafDx9ModelManager::createSpriteModel(char* prm_model_name) {

    GgafDx9SpriteModel* pSpriteModel_New = NEW GgafDx9SpriteModel(prm_model_name);
    restoreSpriteModel(pSpriteModel_New);
    return pSpriteModel_New;
}

GgafDx9PlateModel* GgafDx9ModelManager::createPlateModel(char* prm_model_name) {
    GgafDx9PlateModel* pPlateModel_New = NEW GgafDx9PlateModel(prm_model_name);
    restorePlateModel(pPlateModel_New);
    return pPlateModel_New;
}

GgafDx9SquareModel* GgafDx9ModelManager::createSquareModel(char* prm_model_name) {
    GgafDx9SquareModel* pSquareModel_New = NEW GgafDx9SquareModel(prm_model_name);
    restoreSquareModel(pSquareModel_New);
    return pSquareModel_New;
}

GgafDx9PrimitiveModel* GgafDx9ModelManager::createPrimitiveModel(char* prm_model_name) {
    GgafDx9PrimitiveModel* pPrimitiveModel_New = NEW GgafDx9PrimitiveModel(prm_model_name);
    restorePrimitiveModel(pPrimitiveModel_New);
    return pPrimitiveModel_New;
}


void GgafDx9ModelManager::restorePrimitiveModel(GgafDx9PrimitiveModel* prm_pPrimModel) {
    _TRACE_("GgafDx9ModelManager::restorePrimitiveModel(" << prm_pPrimModel->_model_name << ")");
    //�P�j���_�o�b�t�@�A�C���f�b�N�X���_�o�b�t�@ ���쐬
    //�Q�jX�t�@�C������A�Ǝ��Ɏ��̏���ǂݍ��݁A���_�o�b�t�@�A�C���f�b�N�X���_�o�b�t�@ �ɗ������ށB
    //�R�j�Q�j���s�Ȃ��ߒ��ŁA������ GgafDx9PrimitiveModel �Ɏ��̃����o���쐬�B
    //�@�@�@�@�E���_�o�b�t�@�̎ʂ�
    //�@�@�@�@�E�C���f�b�N�X���_�o�b�t�@�̎ʂ�
    //�@�@�@�@�E�}�e���A���z��(�v�f�����}�e���A����)
    //�@�@�@�@�E�e�N�X�`���z��(�v�f�����}�e���A����)
    //�@�@�@�@�EDrawIndexedPrimitive�p�����z��(�v�f�����}�e���A�����X�g���ω�������)
    //�����Ӂ�
    string xfile_name = GGAFDX9_PROPERTY(DIR_MESH_MODEL) + string(prm_pPrimModel->_model_name) + ".x";
    HRESULT hr;
//    LPDIRECT3DVERTEXBUFFER9 pIDirect3DVertexBuffer9;
//    LPDIRECT3DINDEXBUFFER9 pIDirect3DIndexBuffer9;
//    D3DMATERIAL9* paD3DMaterial9;

    //�������ޒ��_�o�b�t�@�f�[�^�쐬
    ToolBox::IO_Model_X iox;

    Frm::Model3D* pModel3D = NULL;
    Frm::Mesh* pMeshesFront = NULL;

    GgafDx9PrimitiveModel::INDEXPARAM* paIndexParam = NULL;
    GgafDx9PrimitiveModel::VERTEX* paVtxBuffer_org = NULL;
    WORD* paIdxBuffer_org = NULL;
    D3DMATERIAL9* paD3DMaterial9 = NULL;
    GgafDx9TextureConnection** papTextureCon = NULL;

    if (prm_pPrimModel->_pModel3D == NULL) {
        //_TRACE_("CreateModel");
        pModel3D = NEW Frm::Model3D();

        bool r = iox.Load(xfile_name, pModel3D);
        if (r == false) {
            throwGgafCriticalException("[GgafDx9ModelManager::restorePrimitiveModel] X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<xfile_name);
        }
        pModel3D->ConcatenateMeshes();
        pMeshesFront = pModel3D->_Meshes.front();

        int nVertices = pMeshesFront->_nVertices;
        int nFaces = pMeshesFront->_nFaces;

        paVtxBuffer_org = NEW GgafDx9PrimitiveModel::VERTEX[nVertices];
        prm_pPrimModel->_size_vertecs = sizeof(GgafDx9PrimitiveModel::VERTEX) * nVertices;
        prm_pPrimModel->_size_vertec_unit = sizeof(GgafDx9PrimitiveModel::VERTEX);

        //�@���ȊO�ݒ�
        for (int i = 0; i < nVertices; i++) {
            Sleep(1);
            paVtxBuffer_org[i].x = pMeshesFront->_Vertices[i].data[0];
            paVtxBuffer_org[i].y = pMeshesFront->_Vertices[i].data[1];
            paVtxBuffer_org[i].z = pMeshesFront->_Vertices[i].data[2];
            paVtxBuffer_org[i].nx = 0.0f;
            paVtxBuffer_org[i].ny = 0.0f;
            paVtxBuffer_org[i].nz = 0.0f;
            paVtxBuffer_org[i].color = D3DCOLOR_ARGB(255,255,255,255);
            paVtxBuffer_org[i].tu = pMeshesFront->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
            paVtxBuffer_org[i].tv = pMeshesFront->_TextureCoords[i].data[1];
        }

        int nTextureCoords = pMeshesFront->_nTextureCoords;
        if (nVertices < nTextureCoords) {
            _TRACE_("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            _TRACE_("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfile_name);
        }

        //�@���ݒ�
        //���L���_�̖@���̕��ω������݂�I
        //�y2009/03/04�̔]�݂��ɂ��A�C�f�B�A�z
        //���L���_�ɁA�ʂ����������ʂɏW�������ꍇ�A�P���ɕ��ω��i���Z���Ċ���j����Ɩ@���͕΂��Ă��܂��B
        //�����ŁA�@���̉e���x�����i���j���A���̖@�����������钸�_�̐����p�̑傫���Ō��߂�悤�ɂ����B
        //�@���̉e���x���� �� ���̖@�����������钸�_�̐����p �^ ���̒��_�ɂԂ牺����Sface�̐����p���v
        //�Ƃ����B�Ō�ɐ��K������B

        float* paRad = NEW float[nFaces*3]; //�������q�ŏ�����

        float* paRadSum_Vtx = NEW float[nVertices];
        for (int i = 0; i < nVertices; i++) {
            paRadSum_Vtx[i] = 0;
        }
        std::fill_n(paRadSum_Vtx, nVertices, 0);
        static unsigned short indexVertices_per_Face[3];
        static unsigned short indexNormals_per_Face[3];
        for (int i = 0; i < nFaces; i++) {
            Sleep(1);
            for (int j = 0; j < 3; j++) {
                indexVertices_per_Face[j] = pMeshesFront->_Faces[i].data[j];       //�ʂɑ΂��钸�_�C���f�b�N�X�R��(A,B,C�Ƃ���)
                indexNormals_per_Face[j] = pMeshesFront->_FaceNormals[i].data[j];  //�ʂɑ΂���@���C���f�b�N�X�R��
            }

            //���_�C���f�b�N�X A �̊p(��CAB)�����߂āA�z��ɕێ�
            paRad[i*3+0] = getRadv1_v0v1v2(
                             pMeshesFront->_Vertices[indexVertices_per_Face[2]],
                             pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                             pMeshesFront->_Vertices[indexVertices_per_Face[1]]
                           );
            //A �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[0]] += paRad[i*3+0];

            //���_�C���f�b�N�X B �̊p(��ABC)�����߂āA�z��ɕێ�
            paRad[i*3+1] = getRadv1_v0v1v2(
                             pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                             pMeshesFront->_Vertices[indexVertices_per_Face[1]],
                             pMeshesFront->_Vertices[indexVertices_per_Face[2]]
                           );
            //B �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[1]] += paRad[i*3+1];

            //���_�C���f�b�N�X C �̊p(��ACB)�����߂āA�z��ɕێ�
            paRad[i*3+2] = getRadv1_v0v1v2(
                             pMeshesFront->_Vertices[indexVertices_per_Face[1]],
                             pMeshesFront->_Vertices[indexVertices_per_Face[2]],
                             pMeshesFront->_Vertices[indexVertices_per_Face[0]]
                           );
            //C �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[2]] += paRad[i*3+2];
        }

        static float rate; //�@���x�N�g���Ɋ|���闦�B���̖@���x�N�g���̉e���̋����B���̖@���̏o�Ă��钸�_�̐����p�̗��B
        for (int i = 0; i < nFaces; i++) {
            Sleep(1);
            for (int j = 0; j < 3; j++) {
                indexVertices_per_Face[j] = pMeshesFront->_Faces[i].data[j];       //�ʂɑ΂��钸�_�C���f�b�N�X�R��
                indexNormals_per_Face[j] = pMeshesFront->_FaceNormals[i].data[j];  //�ʂɑ΂���@���C���f�b�N�X�R��
            }
            rate = (paRad[i*3+0] / paRadSum_Vtx[indexVertices_per_Face[0]]);
            paVtxBuffer_org[indexVertices_per_Face[0]].nx += (pMeshesFront->_Normals[indexNormals_per_Face[0]].x * rate);
            paVtxBuffer_org[indexVertices_per_Face[0]].ny += (pMeshesFront->_Normals[indexNormals_per_Face[0]].y * rate);
            paVtxBuffer_org[indexVertices_per_Face[0]].nz += (pMeshesFront->_Normals[indexNormals_per_Face[0]].z * rate);
            rate = (paRad[i*3+1] / paRadSum_Vtx[indexVertices_per_Face[1]]);
            paVtxBuffer_org[indexVertices_per_Face[1]].nx += (pMeshesFront->_Normals[indexNormals_per_Face[1]].x * rate);
            paVtxBuffer_org[indexVertices_per_Face[1]].ny += (pMeshesFront->_Normals[indexNormals_per_Face[1]].y * rate);
            paVtxBuffer_org[indexVertices_per_Face[1]].nz += (pMeshesFront->_Normals[indexNormals_per_Face[1]].z * rate);
            rate = (paRad[i*3+2] / paRadSum_Vtx[indexVertices_per_Face[2]]);
            paVtxBuffer_org[indexVertices_per_Face[2]].nx += (pMeshesFront->_Normals[indexNormals_per_Face[2]].x * rate);
            paVtxBuffer_org[indexVertices_per_Face[2]].ny += (pMeshesFront->_Normals[indexNormals_per_Face[2]].y * rate);
            paVtxBuffer_org[indexVertices_per_Face[2]].nz += (pMeshesFront->_Normals[indexNormals_per_Face[2]].z * rate);
        }

        //�Ō�ɖ@�����K�����Đݒ�
        static D3DXVECTOR3 vec;
        for (int i = 0; i < nVertices; i++) {
            Sleep(1);
            vec.x = paVtxBuffer_org[i].nx;
            vec.y = paVtxBuffer_org[i].ny;
            vec.z = paVtxBuffer_org[i].nz;
            if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
                paVtxBuffer_org[i].nx = 0;
                paVtxBuffer_org[i].ny = 0;
                paVtxBuffer_org[i].nz = 0;
            } else {
                D3DXVec3Normalize( &vec, &vec);
                paVtxBuffer_org[i].nx = vec.x;
                paVtxBuffer_org[i].ny = vec.y;
                paVtxBuffer_org[i].nz = vec.z;
            }
        }
        _TRACE_("�@�����K����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[");
        for (int i = 0; i < nVertices; i++) {
            _TRACE_("["<<i<<"]=" << paVtxBuffer_org[i].x << "\t, " << paVtxBuffer_org[i].y << "\t, " << paVtxBuffer_org[i].z << "\t, " << paVtxBuffer_org[i].nx << "\t, " << paVtxBuffer_org[i].ny << "\t, " << paVtxBuffer_org[i].nz << "\t, " << paVtxBuffer_org[i].tu << "\t, " << paVtxBuffer_org[i].tv);
        }
        _TRACE_("�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[");
        //�C���f�b�N�X�o�b�t�@�o�^
        //paIdxBuffer_org = NEW WORD[nFaces*3];
        paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            Sleep(1);
            paIdxBuffer_org[i*3 + 0] = pMeshesFront->_Faces[i].data[0];
            paIdxBuffer_org[i*3 + 1] = pMeshesFront->_Faces[i].data[1];
            paIdxBuffer_org[i*3 + 2] = pMeshesFront->_Faces[i].data[2];
        }

        //�}�e���A�����X�g
//        UINT aMaterialsGrp = UINT[nFaces];
//        for (int i = 0; i < nFaces; i++) {
//            aMaterialsGrp[i] =  pMeshesFront->_FaceMaterials[i];
//        }

        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        GgafDx9PrimitiveModel::INDEXPARAM* paParam = NEW GgafDx9PrimitiveModel::INDEXPARAM[nFaces];

        int prev_materialno = -1;
        int materialno = 0;
        int paramno = 0;
        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;
        UINT max_num_vertices = 0;
        UINT min_num_vertices = INT_MAX;

        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < nFaces; faceNoCnt++) {
            Sleep(1);
            materialno = pMeshesFront->_FaceMaterials[faceNoCnt];
            if (prev_materialno != materialno) {
                //_TRACE_("BREAK! paramno="<<paramno);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                paParam[paramno].MaterialNo = materialno;
                paParam[paramno].BaseVertexIndex = 0;
                paParam[paramno].MinIndex = INT_MAX; //����u���C�N���ɐݒ�A�ςȒl�ɂ��Ƃ�
                paParam[paramno].NumVertices = INT_MAX; //����u���C�N���ɐݒ�
                paParam[paramno].StartIndex = faceNoCnt*3;
                paParam[paramno].PrimitiveCount = INT_MAX; //����u���C�N���ɐݒ�

                if (faceNoCnt > 0) {
                    _TRACE_("BREAK�őO�ݒ�P paramno="<<paramno);
                    paParam[paramno-1].MinIndex = min_num_vertices;
                    paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                    //���Z�b�g
                    max_num_vertices = 0;
                    min_num_vertices = INT_MAX;
                }
                paramno++;
            }

            //_TRACE_("faceNoCnt="<<faceNoCnt<<"/max_num_vertices="<<max_num_vertices<<"/_paIdxBuffer_org[faceNoCnt*3 + 0]="<<paIdxBuffer_org[faceNoCnt*3 + 0]);
            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 0]) {
               // _TRACE_("YES!1");
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 0];
            }
            //_TRACE_("faceNoCnt="<<faceNoCnt<<"/max_num_vertices="<<max_num_vertices<<"/_paIdxBuffer_org[faceNoCnt*3 + 1]="<<paIdxBuffer_org[faceNoCnt*3 + 1]);

            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 1]) {
               // _TRACE_("YES!2");
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 1];
            }
            //_TRACE_("faceNoCnt="<<faceNoCnt<<"/max_num_vertices="<<max_num_vertices<<"/_paIdxBuffer_org[faceNoCnt*3 + 2]="<<paIdxBuffer_org[faceNoCnt*3 + 2]);

            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 2]) {
                //_TRACE_("YES!3");
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 2];
            }

            //_TRACE_("faceNoCnt="<<faceNoCnt<<"/min_num_vertices="<<min_num_vertices<<"/_paIdxBuffer_org[faceNoCnt*3 + 0]="<<paIdxBuffer_org[faceNoCnt*3 + 0]);
            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 0]) {
                //_TRACE_("YES!4");
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 0];
            }
            //_TRACE_("faceNoCnt="<<faceNoCnt<<"/min_num_vertices="<<min_num_vertices<<"/_paIdxBuffer_org[faceNoCnt*3 + 1]="<<paIdxBuffer_org[faceNoCnt*3 + 1]);

            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 1]) {
                //_TRACE_("YES!5");
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 1];
            }
            //_TRACE_("faceNoCnt="<<faceNoCnt<<"/min_num_vertices="<<min_num_vertices<<"/_paIdxBuffer_org[faceNoCnt*3 + 2]="<<paIdxBuffer_org[faceNoCnt*3 + 2]);

            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 2]) {
                _TRACE_("YES!6");
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 2];
            }

            prev_materialno = materialno;
        }
        if (nFaces > 0) {
            //_TRACE_("BREAK�őO�ݒ�Ō� paramno="<<paramno);
            //_TRACE_("faceNoCnt="<<faceNoCnt<<"/min_num_vertices="<<min_num_vertices<<"/max_num_vertices="<<max_num_vertices);

            paParam[paramno-1].MinIndex = min_num_vertices;
            paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }

        paIndexParam = NEW GgafDx9PrimitiveModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            paIndexParam[i].MaterialNo = paParam[i].MaterialNo;
            paIndexParam[i].BaseVertexIndex = paParam[i].BaseVertexIndex;
            paIndexParam[i].MinIndex = paParam[i].MinIndex;
            paIndexParam[i].NumVertices = paParam[i].NumVertices;
            paIndexParam[i].StartIndex = paParam[i].StartIndex;
            paIndexParam[i].PrimitiveCount = paParam[i].PrimitiveCount;
        }
        prm_pPrimModel->_nMaterialListGrp = paramno;
        delete[] paRad;
        delete[] paRadSum_Vtx;
		delete[] paParam;
    }
//    int nVertices = pMeshesFront->_nVertices;
//    _TRACE_("nVertices="<<nVertices);
//    _TRACE_("prm_pPrimModel->_size_vertecs="<<prm_pPrimModel->_size_vertecs);
//    _TRACE_("prm_pPrimModel->_size_vertec_unit="<<prm_pPrimModel->_size_vertec_unit);
//    for (int i = 0; i < nVertices; i++) {
//        _TRACE_("["<<i<<"]=" << paVtxBuffer_org[i].x << "\t, " << paVtxBuffer_org[i].y << "\t, " << paVtxBuffer_org[i].z << "\t, " << paVtxBuffer_org[i].nx << "\t, " << paVtxBuffer_org[i].ny << "\t, " << paVtxBuffer_org[i].nz << "\t, " << paVtxBuffer_org[i].tu << "\t, " << paVtxBuffer_org[i].tv);
//    }
//    int nFaces = pMeshesFront->_nFaces;
//    _TRACE_("<INDEXBUFFER>nFaces="<<nFaces);
//    for (int i = 0; i < nFaces*3; i++) {
//        _TRACE_(paIdxBuffer_org[i]);
//    }
//
//    _TRACE_("�p�����[�^ prm_pPrimModel->_nMaterialListGrp="<<prm_pPrimModel->_nMaterialListGrp);
//    for (int i = 0; i < prm_pPrimModel->_nMaterialListGrp; i++) {
//        _TRACE_("["<<i<<"]MaterialNo="<<paIndexParam[i].MaterialNo);
//        _TRACE_("["<<i<<"]BaseVertexIndex="<<paIndexParam[i].BaseVertexIndex);
//        _TRACE_("["<<i<<"]MinIndex="<<paIndexParam[i].MinIndex);
//        _TRACE_("["<<i<<"]NumVertices="<<paIndexParam[i].NumVertices);
//        _TRACE_("["<<i<<"]StartIndex="<<paIndexParam[i].StartIndex);
//        _TRACE_("["<<i<<"]PrimitiveCount="<<paIndexParam[i].PrimitiveCount);
//        _TRACE_("------------------------------------------------------------");
//    }
//


    if (prm_pPrimModel->_pIDirect3DVertexBuffer9 == NULL) {

        //���_�o�b�t�@�쐬
        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pPrimModel->_size_vertecs,
                D3DUSAGE_WRITEONLY,
                GgafDx9PrimitiveModel::FVF,
                D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
                &(prm_pPrimModel->_pIDirect3DVertexBuffer9),
                NULL);
        whetherGgafDx9CriticalException(hr, D3D_OK, "[GgafDx9ModelManager::restorePrimitiveModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pPrimModel->_model_name));
        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = prm_pPrimModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pPrimModel->_size_vertecs, (void**)&pVertexBuffer, 0);
        whetherGgafDx9CriticalException(hr, D3D_OK, "[GgafDx9ModelManager::restorePrimitiveModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pPrimModel->_model_name);
        memcpy(pVertexBuffer, paVtxBuffer_org, prm_pPrimModel->_size_vertecs); //pVertexBuffer �� paVertex
        prm_pPrimModel->_pIDirect3DVertexBuffer9->Unlock();
    }


    //�������ރC���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (prm_pPrimModel->_pIDirect3DIndexBuffer9 == NULL) {
        int nFaces = pMeshesFront->_nFaces;

        hr = GgafDx9God::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_MANAGED,
                                &(prm_pPrimModel->_pIDirect3DIndexBuffer9),
                                NULL);
        whetherGgafDx9CriticalException(hr, D3D_OK, "[GgafDx9ModelManager::restorePrimitiveModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pPrimModel->_model_name));
        void* pIndexBuffer;
        prm_pPrimModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , paIdxBuffer_org , sizeof(WORD) * nFaces * 3);
        prm_pPrimModel->_pIDirect3DIndexBuffer9->Unlock();
    }


    int nMaterials = pMeshesFront->_nMaterials;
    prm_pPrimModel->_dwNumMaterials = nMaterials;

    //paD3DMaterial9 = NEW D3DMATERIAL9[nMaterials];
    paD3DMaterial9 = NEW D3DMATERIAL9[nMaterials];
    //paIndexParam = NEW GgafDx9PrimitiveModel::INDEXPARAM[nMaterials];
    papTextureCon = NEW GgafDx9TextureConnection*[nMaterials];

    char* texture_filename;
    int n = 0;
    for (list<Frm::Material*>::iterator material = pMeshesFront->_Materials.begin(); material != pMeshesFront->_Materials.end(); material++) {
        Sleep(1);
        paD3DMaterial9[n].Diffuse.r = (*material)->_FaceColor.data[0];
        paD3DMaterial9[n].Diffuse.g = (*material)->_FaceColor.data[1];
        paD3DMaterial9[n].Diffuse.b = (*material)->_FaceColor.data[2];
        paD3DMaterial9[n].Diffuse.a = (*material)->_FaceColor.data[3];

        paD3DMaterial9[n].Ambient.r = (*material)->_FaceColor.data[0];
        paD3DMaterial9[n].Ambient.g = (*material)->_FaceColor.data[1];
        paD3DMaterial9[n].Ambient.b = (*material)->_FaceColor.data[2];
        paD3DMaterial9[n].Ambient.a = (*material)->_FaceColor.data[3];

        paD3DMaterial9[n].Specular.r = (*material)->_SpecularColor.data[0];
        paD3DMaterial9[n].Specular.g = (*material)->_SpecularColor.data[1];
        paD3DMaterial9[n].Specular.b = (*material)->_SpecularColor.data[2];
        paD3DMaterial9[n].Specular.a = 1.000000;
        paD3DMaterial9[n].Power =  (*material)->_power;

        paD3DMaterial9[n].Emissive.r = (*material)->_EmissiveColor.data[0];
        paD3DMaterial9[n].Emissive.g = (*material)->_EmissiveColor.data[1];
        paD3DMaterial9[n].Emissive.b = (*material)->_EmissiveColor.data[2];
        paD3DMaterial9[n].Emissive.a = 1.000000;

        texture_filename = (char*)((*material)->_TextureName.c_str());
        if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
            papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
        } else {
            //�e�N�X�`������
            papTextureCon[n] = NULL;
        }
        n++;
    }

    if (nMaterials != n) {
        _TRACE_("�}�e���A���������������ł��BnMaterials="<<nMaterials<<"/n="<<n);
    }

    //���f���ɕێ�������
    prm_pPrimModel->_pModel3D = pModel3D;
    prm_pPrimModel->_pMeshesFront = pMeshesFront;

    prm_pPrimModel->_paIdxBuffer_org = paIdxBuffer_org;
    prm_pPrimModel->_paVtxBuffer_org = paVtxBuffer_org;
    prm_pPrimModel->_paIndexParam = paIndexParam;
    prm_pPrimModel->_paD3DMaterial9_default = paD3DMaterial9;
    prm_pPrimModel->_papTextureCon = papTextureCon;




}

void GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshModel* prm_pMeshModel) {
    TRACE("GgafDx9ModelManager::restoreMeshModel(" << prm_pMeshModel->_model_name << ")");
    //X�t�@�C���̃��[�h���ĕK�v�ȓ��e��GgafDx9MeshModel�����o�ɐݒ肵�C���X�^���X�Ƃ��Ċ�����������
    //�ȉ��� string xfile_name �܂ł�GgafDx9MeshModel�����o�ݒ�̂��߂̎󂯎��ϐ��B
    LPD3DXMESH pID3DXMesh; //���b�V��(ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�j
    D3DMATERIAL9* paD3DMaterial9; //�}�e���A��(D3DXMATERIAL�\���̂̔z��̐擪�v�f���w���|�C���^�j
    GgafDx9TextureConnection** papTextureCon; //�e�N�X�`���z��(IDirect3DTexture9�C���^�[�t�F�C�X�ւ̃|�C���^��ێ�����I�u�W�F�N�g�j
    DWORD dwNumMaterials;
    string xfile_name = GGAFDX9_PROPERTY(DIR_MESH_MODEL) + string(prm_pMeshModel->_model_name) + ".x";

    LPD3DXBUFFER pID3DXBuffer; //�󂯎��p�o�b�t�@�i�}�e���A���p�j
    HRESULT hr;
    //X�t�@�C���̃t�@�C�����[�h
    hr = D3DXLoadMeshFromX(
           xfile_name.c_str(),         //[in]  LPCTSTR pFilename
           prm_pMeshModel->_dwOptions, //[in]  DWORD Options  D3DXMESH_SYSTEMMEM D3DXMESH_VB_DYNAMIC
           GgafDx9God::_pID3DDevice9,  //[in]  LPDIRECT3DDEVICE9 pDevice
           NULL,                       //[out] LPD3DXBUFFER* ppAdjacency
           &pID3DXBuffer,              //[out] LPD3DXBUFFER* ppMaterials
           NULL,                       //[out] LPD3DXBUFFER* ppEffectInstances
           &dwNumMaterials,            //[out] DWORD* pNumMaterials
           &pID3DXMesh                 //[out] LPD3DXMESH* pMesh
         );
    whetherGgafDx9CriticalException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMeshModel] D3DXLoadMeshFromX�ɂ�郍�[�h�����s�B�Ώ�="<<xfile_name);

    //TODO ���b�V����Optimize�������I
    //    !   ���b�V���̖ʋy�ђ��_�̏��Ԃ�ύX���C�œK���������b�V���I�u�W�F�N�g���擾����B
    //        call XOptimize(lpMesh,D3DXMESHOPT_ATTRSORT,NULL,NULL,NULL,NULL,LOC(lpMeshOpt),iRes)

    //�}�e���A�������o��
    D3DXMATERIAL* paD3DMaterial9_tmp = (D3DXMATERIAL*)(pID3DXBuffer->GetBufferPointer());
    //��2008/02/02 �̔]�݂���
    // ����Ă��邱�ƃ���
    // GetBufferPointer()�Ŏ擾�ł��� D3DXMATERIAL�\���̔z��̃����o��MatD3D (D3DMATERIAL9�\����) ���~�����B
    //�i��GgafDx9MeshModel�̃����o�[�����ɂ��������߁j�B pID3DXBuffer_tmp �̕��͂������Ɖ��(Release())���悤�Ƃ����B
    // ������������ D3DXMATERIAL�\���̔z����ǂ���������悤���A�����ɂ͏����Ȃ���������񂪁c�i�����Ńn�}��G�j�B
    // �����ł������Ȃ��̂ŁApaD3DMaterial9_tmp �̍\���̂𕨗��R�s�[�����ĕۑ����邱�Ƃɂ��܂���`�A���`���`���܂��傤�B
    paD3DMaterial9 = NEW D3DMATERIAL9[dwNumMaterials];
    for( DWORD i = 0; i < dwNumMaterials; i++){
        paD3DMaterial9[i] = paD3DMaterial9_tmp[i].MatD3D;
    }

    //�}�e���A����Diffuse���˂�Ambient���˂ɃR�s�[����
    //���R�FAmbient���C�g���g�p�����������B���̂��߂ɂ͓��RAmbient���˒l���}�e���A���ɐݒ肵�Ȃ���΂����Ȃ���
    //x�t�@�C���iMatD3D�j�ɂ�Diffuse���˒l�����ݒ肳��Ă��Ȃ��A������Diffuse���˂̒l��
    //Ambient���˒l���p���邱�Ƃɂ���B�Ƃ肠�����B
    //TODO:�{���ɂ���ł����̂��H
    for( DWORD i = 0; i < dwNumMaterials; i++) {
        paD3DMaterial9[i].Ambient = paD3DMaterial9[i].Diffuse;
    }

    //�e�N�X�`�������o��
    papTextureCon = NEW GgafDx9TextureConnection*[dwNumMaterials];
    char* texture_filename;
    for( DWORD i = 0; i < dwNumMaterials; i++) {
        texture_filename = paD3DMaterial9_tmp[i].pTextureFilename;
        if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
            papTextureCon[i] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
        } else {
            //�e�N�X�`������
            papTextureCon[i] = NULL;
        }
    }
    RELEASE_IMPOSSIBLE_NULL(pID3DXBuffer);//�e�N�X�`���t�@�C�����͂�������Ȃ��̂Ńo�b�t�@���

    //X�t�@�C���ɖ@�����Ȃ��ꍇ�A�@����ݒ�B
    if(pID3DXMesh->GetFVF() != (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)) {
        LPD3DXMESH pID3DXMesh_tmp = NULL;
        hr = pID3DXMesh->CloneMeshFVF(
                           pID3DXMesh->GetOptions(),             // [in]  DWORD Options,
                           D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1, // [in]  DWORD FVF,
                           GgafDx9God::_pID3DDevice9,            // [in]  LPDIRECT3DDEVICE9 pDevice,
                           &pID3DXMesh_tmp                       // [out] LPD3DXMESH *ppCloneMesh
                         );
        whetherGgafDx9CriticalException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMeshModel]  pID3DXMesh->CloneMeshFVF()���s�B�Ώ�="<<xfile_name);
        D3DXComputeNormals(pID3DXMesh_tmp, NULL); //�@���v�Z
        RELEASE_IMPOSSIBLE_NULL(pID3DXMesh);
        pID3DXMesh = pID3DXMesh_tmp;
    }

    //���b�V���A�}�e���A���A�e�N�X�`���̎Q�ƁA�}�e���A���������f���I�u�W�F�N�g�ɕێ�������
    prm_pMeshModel->_pID3DXMesh = pID3DXMesh;
    prm_pMeshModel->_paD3DMaterial9_default = paD3DMaterial9;
    prm_pMeshModel->_papTextureCon = papTextureCon;
    prm_pMeshModel->_dwNumMaterials = dwNumMaterials;
}

void GgafDx9ModelManager::restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel) {
    TRACE("GgafDx9ModelManager::restoreSpriteModel(" << prm_pSpriteModel->_model_name << ")");

    prm_pSpriteModel->_pTextureCon = NULL;
    prm_pSpriteModel->_paRectUV = NULL;

    prm_pSpriteModel->_pD3DMaterial9_default = NEW D3DMATERIAL9;
    ZeroMemory(prm_pSpriteModel->_pD3DMaterial9_default, sizeof(D3DMATERIAL9) );
    prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.r = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.g = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.b = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.a = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Ambient.r = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Ambient.g = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Ambient.b = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Ambient.a = 1.0f;

    HRESULT hr;
    string xfile_name = GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pSpriteModel->_model_name) + ".x";

    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)

    IDirectXFileEnumObject* pIDirectXFileEnumObject;
    IDirectXFileData* pIDirectXFileData;
    hr = _pIDirectXFile->CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
    whetherGgafDx9CriticalException(hr, DXFILE_OK, "[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<"��CreateEnumObject�Ɏ��s���܂����B");

    //TODO
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

    char** ppaChar_TextureFile;
    float* pFloat_Size_SpriteModelWidth;
    float* pFloat_Size_SpriteModelHeight;
    int* pInt_RowNum_TextureSplit;
    int* pInt_ColNum_TextureSplit;

    // 1�Z�b�g�����Ǎ���
    hr = pIDirectXFileEnumObject->GetNextDataObject(&pIDirectXFileData);
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<" �̓Ǎ��݂Ɏ��s���܂����B���ږ�����������");
    }
    const GUID *pGuid;
    pIDirectXFileData->GetType( &pGuid );
    //if( *pGuid == PersonID_GUID ) {
    if(true) {
        DWORD Size;
        // PersonID�e���v���[�g�f�[�^���擾
        pIDirectXFileData->GetData("TextureFile"     , &Size, (void**)&ppaChar_TextureFile);
        pIDirectXFileData->GetData("Width"           , &Size, (void**)&pFloat_Size_SpriteModelWidth);
        pIDirectXFileData->GetData("Height"          , &Size, (void**)&pFloat_Size_SpriteModelHeight);
        pIDirectXFileData->GetData("TextureSplitRows", &Size, (void**)&pInt_RowNum_TextureSplit);
        pIDirectXFileData->GetData("TextureSplitCols", &Size, (void**)&pInt_ColNum_TextureSplit);
        prm_pSpriteModel->_fSize_SpriteModelWidthPx = *pFloat_Size_SpriteModelWidth;
        prm_pSpriteModel->_fSize_SpriteModelHeightPx = *pFloat_Size_SpriteModelHeight;
        prm_pSpriteModel->_row_texture_split = *pInt_RowNum_TextureSplit;
        prm_pSpriteModel->_col_texture_split = *pInt_ColNum_TextureSplit;
    } else {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<" ��GUID����v���܂���B");
    }

    //�e�N�X�`���擾�����f���ɕێ�������
    //string texture_filename = GGAFDX9_PROPERTY(DIR_TEXTURE_MODEL) + string(*ppaChar_TextureFile);
    GgafDx9TextureConnection* pTextureCon = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);
    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    prm_pSpriteModel->_pTextureCon = pTextureCon;

    GgafDx9SpriteModel::VERTEX* paVertex = NEW GgafDx9SpriteModel::VERTEX[4];
    prm_pSpriteModel->_size_vertecs = sizeof(GgafDx9SpriteModel::VERTEX)*4;
    prm_pSpriteModel->_size_vertec_unit = sizeof(GgafDx9SpriteModel::VERTEX);

    //���_�z��������f���ɕێ�������
    paVertex[0].x = *pFloat_Size_SpriteModelWidth / -2 / PX_UNIT;
    paVertex[0].y = *pFloat_Size_SpriteModelHeight / 2 / PX_UNIT;
    paVertex[0].z = 0.0f;
    paVertex[0].nx = 0.0f;
    paVertex[0].ny = 0.0f;
    paVertex[0].nz = -1.0f;
    paVertex[0].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[0].tu = 0.0f;
    paVertex[0].tv = 0.0f;

    paVertex[1].x = *pFloat_Size_SpriteModelWidth / 2 / PX_UNIT;
    paVertex[1].y = *pFloat_Size_SpriteModelHeight / 2 / PX_UNIT;
    paVertex[1].z = 0.0f;
    paVertex[1].nx = 0.0f;
    paVertex[1].ny = 0.0f;
    paVertex[1].nz = -1.0f;
    paVertex[1].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[1].tu = 1.0f;
    paVertex[1].tv = 0.0f;

    paVertex[2].x = *pFloat_Size_SpriteModelWidth / -2 / PX_UNIT;
    paVertex[2].y = *pFloat_Size_SpriteModelHeight / -2 / PX_UNIT;
    paVertex[2].z = 0.0f;
    paVertex[2].nx = 0.0f;
    paVertex[2].ny = 0.0f;
    paVertex[2].nz = -1.0f;
    paVertex[2].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[2].tu = 0.0f;
    paVertex[2].tv = 1.0f;

    paVertex[3].x = *pFloat_Size_SpriteModelWidth / 2 / PX_UNIT;
    paVertex[3].y = *pFloat_Size_SpriteModelHeight / -2 / PX_UNIT;
    paVertex[3].z = 0.0f;
    paVertex[3].nx = 0.0f;
    paVertex[3].ny = 0.0f;
    paVertex[3].nz = -1.0f;
    paVertex[3].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[3].tu = 1.0f;
    paVertex[3].tv = 1.0f;

    //�o�b�t�@�쐬
    if (prm_pSpriteModel->_pIDirect3DVertexBuffer9 == NULL) {

        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pSpriteModel->_size_vertecs,
                D3DUSAGE_WRITEONLY,
                GgafDx9SpriteModel::FVF,
                D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
                &(prm_pSpriteModel->_pIDirect3DVertexBuffer9),
                NULL);
        whetherGgafDx9CriticalException(hr, D3D_OK, "[GgafDx9ModelManager::restoreSpriteModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pSpriteModel->_model_name));
    }
    //���_�o�b�t�@�쐬
    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = prm_pSpriteModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pSpriteModel->_size_vertecs, (void**)&pVertexBuffer, 0);
    whetherGgafDx9CriticalException(hr, D3D_OK, "[GgafDx9ModelManager::restoreSpriteModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pSpriteModel->_model_name);

    memcpy(pVertexBuffer, paVertex, prm_pSpriteModel->_size_vertecs); //pVertexBuffer �� paVertex
    prm_pSpriteModel->_pIDirect3DVertexBuffer9->Unlock();

    //�S�p�^�[����UV���̔z��쐬�����f���ɕێ�������
    int pattnum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
    GgafDx9RectUV* paRectUV = NEW GgafDx9RectUV[pattnum];
    for (int row = 0; row < *pInt_RowNum_TextureSplit; row++) {
        for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
            int pattno_ani = row*(*pInt_ColNum_TextureSplit)+col;
            paRectUV[pattno_ani]._aUV[0].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
            paRectUV[pattno_ani]._aUV[0].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

            paRectUV[pattno_ani]._aUV[1].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
            paRectUV[pattno_ani]._aUV[1].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

            paRectUV[pattno_ani]._aUV[2].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
            paRectUV[pattno_ani]._aUV[2].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));

            paRectUV[pattno_ani]._aUV[3].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
            paRectUV[pattno_ani]._aUV[3].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));
        }
    }
    prm_pSpriteModel->_paRectUV = paRectUV;
    prm_pSpriteModel->_pattno_ani_Max=pattnum-1;

    //��n��
    DELETEARR_IMPOSSIBLE_NULL(paVertex);
    RELEASE_SAFETY(pIDirectXFileData);
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}

void GgafDx9ModelManager::restorePlateModel(GgafDx9PlateModel* prm_pPlateModel) {
    TRACE("GgafDx9ModelManager::restorePlateModel(" << prm_pPlateModel->_model_name << ")");

    HRESULT hr;
    string xfile_name = GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pPlateModel->_model_name) + ".x";

    //	prm_pPlateModel->_pD3DMaterial9 = NEW D3DMATERIAL9;
    //	ZeroMemory( prm_pPlateModel->_pD3DMaterial9, sizeof(D3DMATERIAL9) );
    //	prm_pPlateModel->_pD3DMaterial9->Diffuse.r = 1.0f;
    //	prm_pPlateModel->_pD3DMaterial9->Diffuse.g = 1.0f;
    //	prm_pPlateModel->_pD3DMaterial9->Diffuse.b = 1.0f;
    //	prm_pPlateModel->_pD3DMaterial9->Diffuse.a = 0.2f;
    //	prm_pPlateModel->_pD3DMaterial9->Ambient = prm_pPlateModel->_pD3DMaterial9->Diffuse;
    IDirectXFileEnumObject* pIDirectXFileEnumObject;
    IDirectXFileData* pIDirectXFileData;
    hr = _pIDirectXFile->CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
    if (hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restorePlateModel] "<<xfile_name<<"��CreateEnumObject�Ɏ��s���܂����B");
    }

    //TODO
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

    char** ppaChar_TextureFile;
    float* pFloat_Size_PlateModelWidth;
    float* pFloat_Size_PlateModelHeight;
    int* pInt_RowNum_TextureSplit;
    int* pInt_ColNum_TextureSplit;

    // 1�Z�b�g�����Ǎ���
    hr = pIDirectXFileEnumObject->GetNextDataObject(&pIDirectXFileData);
    if (hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restorePlateModel] "<<xfile_name<<"�̓Ǎ��݂Ɏ��s���܂����B���ږ�����������");
    }

    const GUID *pGuid;
    pIDirectXFileData->GetType(&pGuid);
    //if( *pGuid == PersonID_GUID ) {

    if (true) {
        DWORD Size;
        // PersonID�e���v���[�g�f�[�^���擾
        pIDirectXFileData->GetData("TextureFile"     , &Size, (void**)&ppaChar_TextureFile);
        pIDirectXFileData->GetData("Width"           , &Size, (void**)&pFloat_Size_PlateModelWidth);
        pIDirectXFileData->GetData("Height"          , &Size, (void**)&pFloat_Size_PlateModelHeight);
        pIDirectXFileData->GetData("TextureSplitRows", &Size, (void**)&pInt_RowNum_TextureSplit);
        pIDirectXFileData->GetData("TextureSplitCols", &Size, (void**)&pInt_ColNum_TextureSplit);
        //�f�[�^�̓R�s�[���Ȃ���΂����܂���B
        prm_pPlateModel->_fSize_PlateModelWidth  = *pFloat_Size_PlateModelWidth;
        prm_pPlateModel->_fSize_PlateModelHeight = *pFloat_Size_PlateModelHeight;
        prm_pPlateModel->_row_texture_split = *pInt_RowNum_TextureSplit;
        prm_pPlateModel->_col_texture_split = *pInt_ColNum_TextureSplit;
    } else {
        throwGgafCriticalException("[GgafDx9ModelManager::restorePlateModel] "<<xfile_name<<"��GUID����v���܂���B");
    }

    //���_�z��������f���ɕێ�������
    //string texture_filename = GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + string(*ppaChar_TextureFile);
    GgafDx9TextureConnection* pTextureCon = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);

    prm_pPlateModel->_pTextureCon = pTextureCon;

    // �e�N�X�`���[�̃T�C�Y���擾
    /*
     D3DSURFACE_DESC d3dsurface_desc;
     pIDirect3DTexture9->GetLevelDesc(0, &d3dsurface_desc);
     UINT ulTextureWidth  = d3dsurface_desc.Width;  //���i�e�N�Z���j
     UINT ulTextureHeight = d3dsurface_desc.Height; //�e�N�X�`�������i�s�N�Z���j
     */

    //�S�p�^�[����UV�������W�����߂ĕێ�
    int pattnum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
    GgafDx9RectUV* paRectUV = NEW GgafDx9RectUV[pattnum];
	for (int row = 0; row < *pInt_RowNum_TextureSplit; row++){
        for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
            int pattno = row*(*pInt_ColNum_TextureSplit)+col;

            paRectUV[pattno]._aUV[0].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
            paRectUV[pattno]._aUV[0].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

            paRectUV[pattno]._aUV[1].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
            paRectUV[pattno]._aUV[1].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

            paRectUV[pattno]._aUV[2].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
            paRectUV[pattno]._aUV[2].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));

            paRectUV[pattno]._aUV[3].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
            paRectUV[pattno]._aUV[3].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));
        }
    }
    prm_pPlateModel->_paRectUV = paRectUV;
    prm_pPlateModel->_pattno_max=pattnum-1;

    //��n��
    RELEASE_SAFETY(pIDirectXFileData);
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}

void GgafDx9ModelManager::restoreSquareModel(GgafDx9SquareModel* prm_pSquareModel) {
    TRACE("GgafDx9ModelManager::restoreSquareModel(" << prm_pSquareModel->_model_name << ")");

    //���_�����ݒ肵�����B
    prm_pSquareModel->_pD3DMaterial9 = NEW D3DMATERIAL9;
    ZeroMemory(prm_pSquareModel->_pD3DMaterial9, sizeof(D3DMATERIAL9) );
    prm_pSquareModel    ->_pD3DMaterial9->Diffuse.r = prm_pSquareModel->_pD3DMaterial9->Ambient.r = 1.0f;
    prm_pSquareModel->_pD3DMaterial9->Diffuse.g = prm_pSquareModel->_pD3DMaterial9->Ambient.g = 0.0f;
    prm_pSquareModel->_pD3DMaterial9->Diffuse.b = prm_pSquareModel->_pD3DMaterial9->Ambient.b = 0.0f;
    prm_pSquareModel->_pD3DMaterial9->Diffuse.a = prm_pSquareModel->_pD3DMaterial9->Ambient.a = 1.0f;

    GgafDx9SquareModel::VERTEX* paVertex = NEW GgafDx9SquareModel::VERTEX[12];
    prm_pSquareModel->_size_vertecs = sizeof(GgafDx9SquareModel::VERTEX)*4;
    prm_pSquareModel->_size_vertec_unit = sizeof(GgafDx9SquareModel::VERTEX);
    paVertex[0].color = D3DCOLOR_ARGB(255,255,0,0);
    paVertex[1].color = D3DCOLOR_ARGB(255,255,0,0);
    paVertex[2].color = D3DCOLOR_ARGB(255,255,0,0);
    paVertex[3].color = D3DCOLOR_ARGB(255,255,0,0);

    //���_�z��������f���ɕێ�������
    paVertex[0].x = -0.5/PX_UNIT;
    paVertex[0].y = 0.5/PX_UNIT;
    paVertex[0].z = 0.0f;
    paVertex[0].nx = 0.0f;
    paVertex[0].ny = 0.0f;
    paVertex[0].nz = -1.0f;
    paVertex[0].color = D3DCOLOR_ARGB(255,255,0,0);

    paVertex[1].x = 0.5/PX_UNIT;
    paVertex[1].y = 0.5/PX_UNIT;
    paVertex[1].z = 0.0f;
    paVertex[1].nx = 0.0f;
    paVertex[1].ny = 0.0f;
    paVertex[1].nz = -1.0f;
    paVertex[1].color = D3DCOLOR_ARGB(255,255,0,0);

    paVertex[2].x = -0.5/PX_UNIT;
    paVertex[2].y = -0.5/PX_UNIT;
    paVertex[2].z = 0.0f;
    paVertex[2].nx = 0.0f;
    paVertex[2].ny = 0.0f;
    paVertex[2].nz = -1.0f;
    paVertex[2].color = D3DCOLOR_ARGB(255,255,0,0);

    paVertex[3].x = 0.5/PX_UNIT;
    paVertex[3].y = -0.5/PX_UNIT;
    paVertex[3].z = 0.0f;
    paVertex[3].nx = 0.0f;
    paVertex[3].ny = 0.0f;
    paVertex[3].nz = -1.0f;
    paVertex[3].color = D3DCOLOR_ARGB(255,255,0,0);

    HRESULT hr;
    //���_�o�b�t�@�쐬
    if (prm_pSquareModel->_pIDirect3DVertexBuffer9 == NULL) {
        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                                          prm_pSquareModel->_size_vertecs,
                                          D3DUSAGE_WRITEONLY,
                                          GgafDx9SquareModel::FVF,
                                          D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
                                          &(prm_pSquareModel->_pIDirect3DVertexBuffer9),
                                          NULL
                                        );
        whetherGgafDx9CriticalException(hr, D3D_OK, "[GgafDx9SquareModelManager::restoreSquareModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<prm_pSquareModel->_model_name);
    }

    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = prm_pSquareModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pSquareModel->_size_vertecs, (void**)&pVertexBuffer, 0);
    whetherGgafDx9CriticalException(hr, D3D_OK, "[GgafDx9SquareModelManager::restoreSquareModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pSquareModel->_model_name);
    memcpy(pVertexBuffer, paVertex, prm_pSquareModel->_size_vertecs);
    prm_pSquareModel->_pIDirect3DVertexBuffer9->Unlock();

    //��n��
    DELETEARR_IMPOSSIBLE_NULL(paVertex);
}

GgafResourceConnection<GgafDx9Model>* GgafDx9ModelManager::processCreateConnection(char* prm_idstr, GgafDx9Model* prm_pResource) {
    TRACE(" GgafDx9ModelManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    GgafDx9ModelConnection* p = NEW GgafDx9ModelConnection(prm_idstr, prm_pResource);
    TRACE(" GgafDx9ModelManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return p;
}

GgafDx9ModelManager::~GgafDx9ModelManager() {
    TRACE("GgafDx9ModelManager::~GgafDx9ModelManager() start-->");
    RELEASE_IMPOSSIBLE_NULL(_pIDirectXFile);
    _pTextureManager->dump();
    DELETE_IMPOSSIBLE_NULL(_pTextureManager);
    TRACE("GgafDx9ModelManager::releaseAll() ���邯�ǂ��A�����ł͊��ɉ����J��������̂��Ȃ��͂��ł�");
    releaseAll();
    TRACE("GgafDx9ModelManager::~GgafDx9ModelManager() end<--");

}

void GgafDx9ModelManager::restoreAll() {
    TRACE("GgafDx9ModelManager::restoreAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pTop;
    TRACE("restoreAll pCurrent="<<pCurrent);
    while (pCurrent != NULL) {
        pCurrent->view()->restore();
        pCurrent = pCurrent->_pNext;
    }
    TRACE("GgafDx9ModelManager::restoreAll() end<--");
}

void GgafDx9ModelManager::onDeviceLostAll() {
    TRACE("GgafDx9ModelManager::onDeviceLostAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pTop;
    TRACE("onDeviceLostAll pCurrent="<<pCurrent);
    while (pCurrent != NULL) {
        pCurrent->view()->onDeviceLost();
        pCurrent = pCurrent->_pNext;
    }
    TRACE("GgafDx9ModelManager::onDeviceLostAll() end<--");
}

void GgafDx9ModelManager::releaseAll() {
    TRACE("GgafDx9ModelManager::releaseAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pTop;
    while (pCurrent != NULL) {
        pCurrent->view()->release();
        pCurrent = pCurrent->_pNext;
    }
    TRACE("GgafDx9ModelManager::releaseAll() end<--");
}

float GgafDx9ModelManager::getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2) {
    //_TRACE_("v0=("<<v0.data[0]<<"."<<v0.data[1]<<","<<v0.data[2]<<")");
    //_TRACE_("v1=("<<v1.data[0]<<"."<<v1.data[1]<<","<<v1.data[2]<<")");
    //_TRACE_("v2=("<<v2.data[0]<<"."<<v2.data[1]<<","<<v2.data[2]<<")");
    static Frm::Vector V0;
    static Frm::Vector V1;
    static Frm::Vector V2;
    V0.x = v0.data[0]; V0.y = v0.data[1]; V0.z = v0.data[2];
    V1.x = v1.data[0]; V1.y = v1.data[1]; V1.z = v1.data[2];
    V2.x = v2.data[0]; V2.y = v2.data[1]; V2.z = v2.data[2];
    static Frm::Vector V;
    V = V2 - V1;
    static Frm::Vector W;
    W = V0 - V1;
    //�x�N�g�� V W �̐����p�����߂�
    //    V=(vx,vy,vz)=(bx-ax,by-ay,bz-az)
    //    W=(wx,wy,wz)=(cx-ax,cy-ay,cz-az)
    //    �ƂȂ�܂��B
    //
    //    �����V�AW�x�N�g�����Ȃ��p����
    //    cos��=(V�AW�x�N�g���̓��ρj���iV�̑傫���j���iW�̑傫���j
    //        =(vx*wx+vy*wy+vz*wz)
    //         �����[�g(vx^2+vy^2+vz^2)�����[�g(wx^2+wy^2+wz^2)
    static float DOT, LV, LW, cosV1;
    //_TRACE_("V=("<<V.x<<"."<<V.y<<","<<V.z<<")");
    //_TRACE_("W=("<<W.x<<"."<<W.y<<","<<W.z<<")");
    DOT = V.Dot(W);
    //_TRACE_("DOT="<<DOT);
    LV = V.Abs();
    //_TRACE_("LV="<<LV);
    LW = W.Abs();
    //_TRACE_("LW="<<LW);

    cosV1 = DOT / LV / LW;
    if (cosV1 == 0) {
        return (float)PI/2;
    } else {
        return cosV1;
    }

}


