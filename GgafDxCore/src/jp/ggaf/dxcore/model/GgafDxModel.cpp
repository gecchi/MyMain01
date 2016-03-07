#include "jp/ggaf/dxcore/model/GgafDxModel.h"

#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxModel::GgafDxModel(const char* prm_model_name) : GgafObject(),
_pTexBlinker(new GgafDxTextureBlinker(this)) {
    _TRACE3_("_model_name="<<_model_name<<" _id="<<_id);
    int len = strlen(prm_model_name);
    _model_name = NEW char[len+1];
    strcpy(_model_name, prm_model_name);

    _paMaterial_default = nullptr;
    _num_materials = 0;
    _pa_texture_filenames = nullptr;
    _papTextureConnection = nullptr;
    _default_texture_index = 0;
    _bounding_sphere_radius = 0;
    _power_blink = 1.0f;
    _blink_threshold = 1.000001f;
    _blinker_frames = 0;
    _is_init_model = false;
    _set_num = 1; //�f�t�H���g�ő哯�`�搔�P
    _specular = 0.0f;
    _specular_power = 0.0f;
    _num_pass = 1;
    _obj_model = 0;

    _TRACE3_("_model_name="<<_model_name<<" _id="<<_id);
}

//void GgafDxModel::setMaterialTexture(int prm_material_no, const char* prm_texture) {
//    GgafDxTextureManager* pModelTextureManager = GgafDxModelManager::_pModelTextureManager;
//    GgafDxTextureConnection* pTexCon = (GgafDxTextureConnection*)pModelTextureManager->connect(prm_texture, this);
//    _papTextureConnection[prm_material_no]->close();
//    _papTextureConnection[prm_material_no] = pTexCon;
//}

//GgafDxTextureConnection* GgafDxModel::setMaterialTexture(int prm_material_no, GgafDxTextureConnection* prm_pTexCon) {
//    if (prm_material_no > _num_materials) {
//        throwGgafCriticalException("�}�e���A��INDEX���͈͊O�ł��B_model_name="<<_model_name<<" _num_materials="<<_num_materials<<" prm_material_no="<<prm_material_no)
//    } else {
//        GgafDxTextureConnection* r = _papTextureConnection[prm_material_no];
//        _papTextureConnection[prm_material_no] = prm_pTexCon;
//        return r;
//    }
//}
//void GgafDxModel::swapTopTextureOrder(const char* prm_texture0) {
//    int idx = -1;
//    for (DWORD i = 0; i < _num_materials; i++) {
//        if (strcmp(_papTextureConnection[i]->peek()->getName(), prm_texture0) == 0) {
//            if (i == 0) {
//                return; //swap�s�v���ł�Top
//            } else {
//                idx = i;
//                break;
//            }
//        }
//    }
//    if (idx < 0) {
//        throwGgafCriticalException("�w��e�N�X�`���͌�����܂���Bprm_texture0="<<prm_texture0);
//    }
//    GgafDxTextureConnection* top = _papTextureConnection[idx];
//    for (int i = _num_materials-1; i >= 1; i--) {
//        if (i <= idx) {
//            _papTextureConnection[i] = _papTextureConnection[i-1];
//        }
//    }
//    _papTextureConnection[0] = top;
//}


void GgafDxModel::prepareVtx(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit,
                            Frm::Model3D* model_pModel3D,
                            uint16_t* paNumVertices) {
    //���O��
    //prm_paVtxBuffer �ɂ� x,y,z,tu,tv �͐ݒ�ς�
    Frm::Mesh* model_pMeshesFront = model_pModel3D->_Meshes.front();
    int nVertices = model_pMeshesFront->_nVertices; //���b�V���A����̑����_��
    int nFaces = model_pMeshesFront->_nFaces;       //���b�V���A����̑��ʐ�
    int nFaceNormals = model_pMeshesFront->_nFaceNormals; //���b�V���A����̑��@����
    //�@���ݒ�B
    //���L���_�̖@���͕��ω������݂�I
    //�y2009/03/04�̔]�݂��ɂ��A�C�f�B�A�z
    //���L���_�ɁA�ʂ������悤�ȕ��ʂɏW�������ꍇ�A�P���ɉ��Z���Ėʐ��Ŋ��镽�ω�������Ɩ@���͕΂��Ă��܂��B
    //�����ŁA���L���_�@���ւ̉e���x�����i���j���A���̖ʖ@������������ʂ̒��_�p�̑傫���Ō��߂�悤�ɂ����B
    //�@���̉e���x���� �� ���̖@�����������钸�_�̐����p �^ ���̒��_�ɂԂ牺����Sface�̐����p���v
    //�Ƃ����B�Ō�ɐ��K������B
    byte* paVtxBuffer = (byte*)prm_paVtxBuffer;
    float* paRad = NEW float[nFaces*3];
    float* paRadSum_Vtx = NEW float[nVertices];
    for (int v = 0; v < nVertices; v++) {
        paRadSum_Vtx[v] = 0;
    }
    std::fill_n(paRadSum_Vtx, nVertices, 0);
    unsigned short indexVertices_per_Face[3];
    unsigned short indexNormals_per_Face[3];
    for (int face_index = 0; face_index < nFaces; face_index++) {
        for (int v = 0; v < 3; v++) {
            //�ʂɑ΂��钸�_�C���f�b�N�X�R��(A,B,C�Ƃ���)
            indexVertices_per_Face[v] = model_pMeshesFront->_Faces[face_index].data[v];
            //�ʂɑ΂���@���C���f�b�N�X�R��
            if (nFaceNormals > face_index) {
                indexNormals_per_Face[v] = model_pMeshesFront->_FaceNormals[face_index].data[v];
            } else {
                //�@���������ꍇ
                indexNormals_per_Face[v] = (unsigned short)0;
            }
        }

        //���_�C���f�b�N�X A �̊p(��CAB)�����߂āA�z��ɕێ�
        paRad[face_index*3+0] = GgafDxModel::getRadv1_v0v1v2(
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[2]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[1]]
                       );
        //A �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
        paRadSum_Vtx[indexVertices_per_Face[0]] += paRad[face_index*3+0];

        //���_�C���f�b�N�X B �̊p(��ABC)�����߂āA�z��ɕێ�
        paRad[face_index*3+1] = GgafDxModel::getRadv1_v0v1v2(
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[1]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[2]]
                       );
        //B �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
        paRadSum_Vtx[indexVertices_per_Face[1]] += paRad[face_index*3+1];

        //���_�C���f�b�N�X C �̊p(��ACB)�����߂āA�z��ɕێ�
        paRad[face_index*3+2] = (float)(2*PI - (paRad[face_index*3+0] + paRad[face_index*3+1]));
        //C �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
        paRadSum_Vtx[indexVertices_per_Face[2]] += paRad[face_index*3+2];
    }

    float rate; //���̖@���̏o�Ă��钸�_�̐����p�̗��B�܂�@���x�N�g���Ɋ|���闦�B���̖@���x�N�g���̉e���̋����B
    GgafDxModel::VERTEX_3D_BASE* pVtx;
    D3DXVECTOR3 p[3];
    D3DXVECTOR2 uv[3];
    D3DXVECTOR3 outTangent;
    D3DXVECTOR3 outBinormal;
    for (int face_index = 0; face_index < nFaces; face_index++) { //�S�|���S�������[�v
        //�|���S���i�O�p�ʁj�̒��_�C���f�b�N�X���R�i�[
        for (int v = 0; v < 3; v++) {
            indexVertices_per_Face[v] = model_pMeshesFront->_Faces[face_index].data[v];
            if (nFaceNormals > face_index) {
                indexNormals_per_Face[v] = model_pMeshesFront->_FaceNormals[face_index].data[v];
            } else {
                //�@���������ꍇ
                indexNormals_per_Face[v] = (unsigned short)0;
            }
        }
        if (nFaceNormals > face_index) {
            for (int v = 0; v < 3; v++) {
                rate = (paRad[face_index*3+v] / paRadSum_Vtx[indexVertices_per_Face[v]]);
                pVtx = (GgafDxModel::VERTEX_3D_BASE*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
                pVtx->nx += (model_pMeshesFront->_Normals[indexNormals_per_Face[v]].x * rate);
                pVtx->ny += (model_pMeshesFront->_Normals[indexNormals_per_Face[v]].y * rate);
                pVtx->nz += (model_pMeshesFront->_Normals[indexNormals_per_Face[v]].z * rate);
            }
        } else {
            //�@���������ꍇ�A�@�����v�Z���č�肾���B

            //�ʂɑ΂��钸�_�C���f�b�N�X�R��
            int indexVertices1 = model_pMeshesFront->_Faces[face_index].data[0];
            int indexVertices2 = model_pMeshesFront->_Faces[face_index].data[1];
            int indexVertices3 = model_pMeshesFront->_Faces[face_index].data[2];
            //�ʂ̒��_�R��
            D3DXVECTOR3 v1 = D3DXVECTOR3(
                model_pMeshesFront->_Vertices[indexVertices1].data[0],
                model_pMeshesFront->_Vertices[indexVertices1].data[1],
                model_pMeshesFront->_Vertices[indexVertices1].data[2]
            );
            D3DXVECTOR3 v2 = D3DXVECTOR3(
                model_pMeshesFront->_Vertices[indexVertices2].data[0],
                model_pMeshesFront->_Vertices[indexVertices2].data[1],
                model_pMeshesFront->_Vertices[indexVertices2].data[2]
            );
            D3DXVECTOR3 v3 = D3DXVECTOR3(
                model_pMeshesFront->_Vertices[indexVertices3].data[0],
                model_pMeshesFront->_Vertices[indexVertices3].data[1],
                model_pMeshesFront->_Vertices[indexVertices3].data[2]
            );

            D3DXPLANE Plane;
            // 3 �̓_���畽�ʂ��쐬
            D3DXPlaneFromPoints(&Plane, &v1, &v2, &v3);
            //���K����������(�@��)���Z�o
            D3DXPlaneNormalize(&Plane, &Plane);
            for (int v = 0; v < 3; v++) {
                rate = (paRad[face_index*3+v] / paRadSum_Vtx[indexVertices_per_Face[v]]);
                pVtx = (GgafDxModel::VERTEX_3D_BASE*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
                pVtx->nx += (Plane.a * rate);
                pVtx->ny += (Plane.b * rate);
                pVtx->nz += (Plane.c * rate);
            }
        }

        ///Obj_GgafDxMeshModel�̏ꍇ����//////////////////////////////////////////
        if (_obj_model & Obj_GgafDxMeshModel) {
            //���������������A�o���v�}�b�v�̈�U�� �ڃx�N�g���iTangent�j�y�� V�� �]�@���iBinormal�j�̕��ς��v�Z
            //���_�o�b�t�@�ɁATangent Binormal ���ߍ��ݗL��̏ꍇ
            for (int v = 0; v < 3; v++) { //p[3] �� uv[3] �Ƀp�����[�^�Z�b�g
                pVtx = (GgafDxModel::VERTEX_3D_BASE*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
                p[v].x = pVtx->x;
                p[v].y = pVtx->y;
                p[v].z = pVtx->z;
                GgafDxMeshModel::VERTEX* pVtx_ex = (GgafDxMeshModel::VERTEX*)pVtx;
                uv[v].x = pVtx_ex->tu;
                uv[v].y = pVtx_ex->tv;
            }
            //�v�Z
            GgafDxModel::calcTangentAndBinormal(
                    &p[0], &uv[0],
                    &p[1], &uv[1],
                    &p[2], &uv[2],
                    &outTangent, &outBinormal); //�ʂɑ΂��� U���iTangent�j�y��V���iBinormal�j
            //���ʂ𒸓_�o�b�t�@�ɏ������݁i���ς��l���j
            for (int v = 0; v < 3; v++) {
                //GgafDxMeshModel�̏ꍇ
                GgafDxMeshModel::VERTEX* pVtx_ex = (GgafDxMeshModel::VERTEX*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
                rate = (paRad[face_index*3+v] / paRadSum_Vtx[indexVertices_per_Face[v]]);
                pVtx_ex->tan_x += (outTangent.x  * rate);
                pVtx_ex->tan_y += (outTangent.y  * rate);
                pVtx_ex->tan_z += (outTangent.z  * rate);
                pVtx_ex->bin_x += (outBinormal.x * rate);
                pVtx_ex->bin_y += (outBinormal.y * rate);
                pVtx_ex->bin_z += (outBinormal.z * rate);
            }
        }
    }

    //X�t�@�C����FrameTransformMatrix(0�t���[���ڂ̏������A�j���[�V����)���l��
    int n = 0;
    int nVertices_begin = 0;
    int nVertices_end = 0;
    for (std::list<Frm::Bone*>::iterator iteBone = model_pModel3D->_toplevel_Skelettons.begin() ;
            iteBone != model_pModel3D->_toplevel_Skelettons.end(); iteBone++) {

        _TRACE_("GgafDxModelManager : (*iteBone)->_Name="<<((*iteBone)->_Name));

        if ((*iteBone)) {
            Frm::Matrix* pMatPos = &((*iteBone)->_MatrixPos);
            if (pMatPos == 0 || pMatPos== nullptr || pMatPos->isIdentity()) {
                //FrameTransformMatrix �͒P�ʍs��
                _TRACE_("GgafDxModelManager : FrameTransformMatrix is Identity");
            } else {
                _TRACE_("GgafDxModelManager : Execute FrameTransform!");
                D3DXMATRIX FrameTransformMatrix;
                FrameTransformMatrix._11 = pMatPos->data[0];
                FrameTransformMatrix._12 = pMatPos->data[1];
                FrameTransformMatrix._13 = pMatPos->data[2];
                FrameTransformMatrix._14 = pMatPos->data[3];
                FrameTransformMatrix._21 = pMatPos->data[4];
                FrameTransformMatrix._22 = pMatPos->data[5];
                FrameTransformMatrix._23 = pMatPos->data[6];
                FrameTransformMatrix._24 = pMatPos->data[7];
                FrameTransformMatrix._31 = pMatPos->data[8];
                FrameTransformMatrix._32 = pMatPos->data[9];
                FrameTransformMatrix._33 = pMatPos->data[10];
                FrameTransformMatrix._34 = pMatPos->data[11];
                FrameTransformMatrix._41 = pMatPos->data[12];
                FrameTransformMatrix._42 = pMatPos->data[13];
                FrameTransformMatrix._43 = pMatPos->data[14];
                FrameTransformMatrix._44 = pMatPos->data[15];

                if (n == 0) {
                    nVertices_begin = 0;
                    nVertices_end = paNumVertices[n];
                } else {
                    nVertices_begin += paNumVertices[n-1];
                    nVertices_end += paNumVertices[n];
                }

                D3DXVECTOR3 vecVertex;
                D3DXVECTOR3 vecNormal;
                D3DXVECTOR3 vecTangent;
                D3DXVECTOR3 vecBinormal;
                for (int i = nVertices_begin; i < nVertices_end; i++) {
                    pVtx = (GgafDxModel::VERTEX_3D_BASE*)(paVtxBuffer + (prm_size_of_vtx_unit*i));
                    vecVertex.x = pVtx->x;
                    vecVertex.y = pVtx->y;
                    vecVertex.z = pVtx->z;
                    D3DXVec3TransformCoord(&vecVertex, &vecVertex, &FrameTransformMatrix);
                    vecNormal.x = pVtx->nx;
                    vecNormal.y = pVtx->ny;
                    vecNormal.z = pVtx->nz;
                    D3DXVec3TransformNormal(&vecNormal, &vecNormal, &FrameTransformMatrix);
                    pVtx->x = vecVertex.x;
                    pVtx->y = vecVertex.y;
                    pVtx->z = vecVertex.z;
                    pVtx->nx = vecNormal.x;
                    pVtx->ny = vecNormal.y;
                    pVtx->nz = vecNormal.z;

                    ///GgafDxMeshModel�̏ꍇ����///////////////////
                    if (_obj_model & Obj_GgafDxMeshModel) {
                        //GgafDxMeshModel�̏ꍇ
                        GgafDxMeshModel::VERTEX* pVtx_ex = (GgafDxMeshModel::VERTEX*)pVtx;
                        vecTangent.x = pVtx_ex->tan_x;
                        vecTangent.y = pVtx_ex->tan_y;
                        vecTangent.z = pVtx_ex->tan_z;
                        D3DXVec3TransformNormal(&vecTangent, &vecTangent, &FrameTransformMatrix);
                        vecBinormal.x = pVtx_ex->bin_x;
                        vecBinormal.y = pVtx_ex->bin_y;
                        vecBinormal.z = pVtx_ex->bin_z;
                        D3DXVec3TransformNormal(&vecBinormal, &vecBinormal, &FrameTransformMatrix);

                        pVtx_ex->tan_x = vecTangent.x;
                        pVtx_ex->tan_y = vecTangent.y;
                        pVtx_ex->tan_z = vecTangent.z;
                        pVtx_ex->bin_x = vecBinormal.x;
                        pVtx_ex->bin_y = vecBinormal.y;
                        pVtx_ex->bin_z = vecBinormal.z;
                    }
                    /////////////////////////////////////////////
                }
            }
        }
        n++;
    }
    //�Ō�ɖ@�����K�����Đݒ�
    D3DXVECTOR3 vec;
    for (int i = 0; i < nVertices; i++) {
        pVtx = (GgafDxModel::VERTEX_3D_BASE*)(paVtxBuffer + (prm_size_of_vtx_unit*i));
        vec.x = pVtx->nx;
        vec.y = pVtx->ny;
        vec.z = pVtx->nz;
        if (ZEROf_EQ(vec.x) && ZEROf_EQ(vec.y) && ZEROf_EQ(vec.z)) {
            pVtx->nx = 0;
            pVtx->ny = 0;
            pVtx->nz = 0;
        } else {
            D3DXVec3Normalize( &vec, &vec);
            pVtx->nx = vec.x;
            pVtx->ny = vec.y;
            pVtx->nz = vec.z;
        }

        ///GgafDxMeshModel�̏ꍇ����///////////////////
        if (_obj_model & Obj_GgafDxMeshModel) {
            GgafDxMeshModel::VERTEX* pVtx_ex = (GgafDxMeshModel::VERTEX*)pVtx;
            vec.x = pVtx_ex->tan_x;
            vec.y = pVtx_ex->tan_y;
            vec.z = pVtx_ex->tan_z;
            if (ZEROf_EQ(vec.x) && ZEROf_EQ(vec.y) && ZEROf_EQ(vec.z)) {
                pVtx_ex->tan_x = 0;
                pVtx_ex->tan_y = 0;
                pVtx_ex->tan_z = 0;
            } else {
                D3DXVec3Normalize( &vec, &vec);
                pVtx_ex->tan_x = vec.x;
                pVtx_ex->tan_y = vec.y;
                pVtx_ex->tan_z = vec.z;
            }
            vec.x = pVtx_ex->bin_x;
            vec.y = pVtx_ex->bin_y;
            vec.z = pVtx_ex->bin_z;
            if (ZEROf_EQ(vec.x) && ZEROf_EQ(vec.y) && ZEROf_EQ(vec.z)) {
                pVtx_ex->bin_x = 0;
                pVtx_ex->bin_y = 0;
                pVtx_ex->bin_z = 0;
            } else {
                D3DXVec3Normalize( &vec, &vec);
                pVtx_ex->bin_x = vec.x;
                pVtx_ex->bin_y = vec.y;
                pVtx_ex->bin_z = vec.z;
            }
        }
    }
    delete[] paRad;
    delete[] paRadSum_Vtx;
}

void GgafDxModel::calcTangentAndBinormal(
        D3DXVECTOR3* p0, D3DXVECTOR2* uv0,
        D3DXVECTOR3* p1, D3DXVECTOR2* uv1,
        D3DXVECTOR3* p2, D3DXVECTOR2* uv2,
        D3DXVECTOR3* outTangent, D3DXVECTOR3* outBinormal) {
    // 5������3�������_��
    D3DXVECTOR3 CP0[3] =
            { D3DXVECTOR3(p0->x, uv0->x, uv0->y), D3DXVECTOR3(p0->y, uv0->x, uv0->y), D3DXVECTOR3(p0->z, uv0->x, uv0->y), };
    D3DXVECTOR3 CP1[3] =
            { D3DXVECTOR3(p1->x, uv1->x, uv1->y), D3DXVECTOR3(p1->y, uv1->x, uv1->y), D3DXVECTOR3(p1->z, uv1->x, uv1->y), };
    D3DXVECTOR3 CP2[3] =
            { D3DXVECTOR3(p2->x, uv2->x, uv2->y), D3DXVECTOR3(p2->y, uv2->x, uv2->y), D3DXVECTOR3(p2->z, uv2->x, uv2->y), };

    // ���ʃp�����[�^����UV�����W�Z�o
    float U[3], V[3];
    static double lim = FLT_MAX/100.0;
    for (int i = 0; i < 3; ++i) {
        D3DXVECTOR3 V1 = CP1[i] - CP0[i];
        D3DXVECTOR3 V2 = CP2[i] - CP1[i];
        D3DXVECTOR3 VABC;
        D3DXVec3Cross(&VABC, &V1, &V2);

        if (ZEROf_EQ(VABC.x)) {
            // ��΂����I
            // �|���S����UV��̃|���S�����k�ނ��Ă܂��I
            //_TRACE_("���x���� GgafDxModel::calcTangentAndBinormal �|���S����UV��̃|���S�����k�ނ��Ă܂��I");
            U[i] = -SGN(VABC.y) * lim;
            V[i] = -SGN(VABC.z) * lim;
        } else {
            U[i] = -VABC.y / VABC.x;
            V[i] = -VABC.z / VABC.x;
        }
    }

    memcpy(outTangent, U, sizeof(float) * 3);
    memcpy(outBinormal, V, sizeof(float) * 3);

    // ���K�����܂�
    D3DXVec3Normalize(outTangent, outTangent);
    D3DXVec3Normalize(outBinormal, outBinormal);
}

//�}���y�P
//http://marupeke296.com/DXPS_No12_CalcTangentVectorSpace.html
//U����V�������߂�֐�
// 3���_��UV�l����w����W�ł�U���iTangent�j�y��V���iBinormal�j���Z�o
// p0, p1, p2    : ���[�J����Ԃł̒��_���W�i�|���S���`�揇�ɂ��邱�Ɓj
// uv0, uv1, uv2 : �e���_��UV���W
// outTangent    : U���iTangent�j�o��
// outBinormal   : V���iBinormal�j�o��


float GgafDxModel::getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2) {
    Frm::Vector V0;
    Frm::Vector V1;
    Frm::Vector V2;
    V0.x = v0.data[0]; V0.y = v0.data[1]; V0.z = v0.data[2];
    V1.x = v1.data[0]; V1.y = v1.data[1]; V1.z = v1.data[2];
    V2.x = v2.data[0]; V2.y = v2.data[1]; V2.z = v2.data[2];
    Frm::Vector V;
    V = V2 - V1;
    Frm::Vector W;
    W = V0 - V1;
    //�x�N�g�� V W �̐����p�����߂�
    //    V=(vx,vy,vz)=(bx-ax,by-ay,bz-az)
    //    W=(wx,wy,wz)=(cx-ax,cy-ay,cz-az)
    //    �Ƃ����V�AW�x�N�g�����Ȃ��p��
    //    cos��=(V�AW�x�N�g���̓��ρj���iV�̑傫���j���iW�̑傫���j
    //        =(vx*wx+vy*wy+vz*wz)
    //         �����[�g(vx^2+vy^2+vz^2)�����[�g(wx^2+wy^2+wz^2)
    float DOT, LV, LW, cosV1;
    //_TRACE3_("V=("<<V.x<<"."<<V.y<<","<<V.z<<")");
    //_TRACE3_("W=("<<W.x<<"."<<W.y<<","<<W.z<<")");
    DOT = V.Dot(W);
    LV = V.Abs();
    LW = W.Abs();
    cosV1 = DOT / LV / LW;
    if (ZEROf_EQ(cosV1)) {
        return (float)PI/2;
    } else {
        return cosV1;
    }
}


void GgafDxModel::setMaterial(Frm::Mesh* in_pMeshesFront) {
    if (!_paMaterial_default) {
        _num_materials = 0;
        if (in_pMeshesFront) {
            for (std::list<Frm::Material*>::iterator material = in_pMeshesFront->_Materials.begin();
                    material != in_pMeshesFront->_Materials.end(); material++) {
                _num_materials++;
            }
        }

        if (_num_materials > 0) {
            _paMaterial_default = NEW D3DMATERIAL9[_num_materials];
            _pa_texture_filenames = NEW std::string[_num_materials];
            int n = 0;
            for (std::list<Frm::Material*>::iterator material = in_pMeshesFront->_Materials.begin();
                    material != in_pMeshesFront->_Materials.end(); material++) {
                _paMaterial_default[n].Diffuse.r = (*material)->_FaceColor.data[0];
                _paMaterial_default[n].Diffuse.g = (*material)->_FaceColor.data[1];
                _paMaterial_default[n].Diffuse.b = (*material)->_FaceColor.data[2];
                _paMaterial_default[n].Diffuse.a = (*material)->_FaceColor.data[3];

                _paMaterial_default[n].Ambient.r = (*material)->_FaceColor.data[0];
                _paMaterial_default[n].Ambient.g = (*material)->_FaceColor.data[1];
                _paMaterial_default[n].Ambient.b = (*material)->_FaceColor.data[2];
                _paMaterial_default[n].Ambient.a = (*material)->_FaceColor.data[3];

                _paMaterial_default[n].Specular.r = (*material)->_SpecularColor.data[0];
                _paMaterial_default[n].Specular.g = (*material)->_SpecularColor.data[1];
                _paMaterial_default[n].Specular.b = (*material)->_SpecularColor.data[2];
                _paMaterial_default[n].Specular.a = 1.000000f;
                _paMaterial_default[n].Power =  (*material)->_power;

                _paMaterial_default[n].Emissive.r = (*material)->_EmissiveColor.data[0];
                _paMaterial_default[n].Emissive.g = (*material)->_EmissiveColor.data[1];
                _paMaterial_default[n].Emissive.b = (*material)->_EmissiveColor.data[2];
                _paMaterial_default[n].Emissive.a = 1.000000f;
                _pa_texture_filenames[n] = (*material)->_TextureName;
                if (_pa_texture_filenames[n].size() == 0) {
                   _pa_texture_filenames[n] = PROPERTY::WHITE_TEXTURE;
                }
                n++;
            }
        } else {
            //�}�e���A����`���P�������̂ŁA�`��̂��߂ɖ������P�}�e���A�����쐬�B
            _num_materials = 1;
            _paMaterial_default  = NEW D3DMATERIAL9[1];
            _pa_texture_filenames = NEW std::string[1];

            _paMaterial_default[0].Diffuse.r = 1.0f;
            _paMaterial_default[0].Diffuse.g = 1.0f;
            _paMaterial_default[0].Diffuse.b = 1.0f;
            _paMaterial_default[0].Diffuse.a = 1.0f;

            _paMaterial_default[0].Ambient.r = 1.0f;
            _paMaterial_default[0].Ambient.g = 1.0f;
            _paMaterial_default[0].Ambient.b = 1.0f;
            _paMaterial_default[0].Ambient.a = 1.0f;

            _paMaterial_default[0].Specular.r = 1.0f;
            _paMaterial_default[0].Specular.g = 1.0f;
            _paMaterial_default[0].Specular.b = 1.0f;
            _paMaterial_default[0].Specular.a = 1.0f;
            _paMaterial_default[0].Power = 0.0f;

            _paMaterial_default[0].Emissive.r = 1.0f;
            _paMaterial_default[0].Emissive.g = 1.0f;
            _paMaterial_default[0].Emissive.b = 1.0f;
            _paMaterial_default[0].Emissive.a = 1.0f;
            _pa_texture_filenames[0] = PROPERTY::WHITE_TEXTURE;
        }
    }

}

GgafDxModel::~GgafDxModel() {
    _TRACE_("" << _model_name << " ");
    GGAF_DELETEARR_NULLABLE(_model_name);
    GGAF_DELETEARR_NULLABLE(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    delete _pTexBlinker;
}

