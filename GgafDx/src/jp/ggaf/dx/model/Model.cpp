#include "jp/ggaf/dx/model/Model.h"

#include <Shlwapi.h>
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MeshModel.h"
#include "jp/ggaf/dx/model/PointSpriteModel.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/dx/texture/Texture.h"

using namespace GgafDx;

Model::Model(const char* prm_model_id) : GgafCore::Object(),
_pTexBlinker(new TextureBlinker(this)) {
    _TRACE3_("_model_id=" << prm_model_id << " _id=" << _id);
    int len = (int)strlen(prm_model_id);
    _model_id = NEW char[len+1];
    strcpy(_model_id, prm_model_id);
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
    _draw_set_num = 1;
    _max_draw_set_num = 1;//デフォルト最大同描画数１
    _specular = 0.0f;
    _specular_power = 0.0f;
    _num_pass = 1;
    D3DXMatrixIdentity(&_matBaseTransformMatrix);
    _TRACE3_("_model_id="<<_model_id<<" _id="<<_id);
}

//void Model::setMaterialTexture(int prm_material_no, const char* prm_texture) {
//    TextureManager* pModelTextureManager = ModelManager::_pModelTextureManager;
//    TextureConnection* pTexCon = (TextureConnection*)pModelTextureManager->connect(prm_texture, this);
//    _papTextureConnection[prm_material_no]->close();
//    _papTextureConnection[prm_material_no] = pTexCon;
//}

//TextureConnection* Model::setMaterialTexture(int prm_material_no, TextureConnection* prm_pTexCon) {
//    if (prm_material_no > _num_materials) {
//        throwCriticalException("マテリアルINDEXが範囲外です。_model_id="<<_model_id<<" _num_materials="<<_num_materials<<" prm_material_no="<<prm_material_no)
//    } else {
//        TextureConnection* r = _papTextureConnection[prm_material_no];
//        _papTextureConnection[prm_material_no] = prm_pTexCon;
//        return r;
//    }
//}
//void Model::swapTopTextureOrder(const char* prm_texture0) {
//    int idx = -1;
//    for (DWORD i = 0; i < _num_materials; i++) {
//        if (strcmp(_papTextureConnection[i]->peek()->getName(), prm_texture0) == 0) {
//            if (i == 0) {
//                return; //swap不要すでにTop
//            } else {
//                idx = i;
//                break;
//            }
//        }
//    }
//    if (idx < 0) {
//        throwCriticalException("指定テクスチャは見つかりません。prm_texture0="<<prm_texture0);
//    }
//    TextureConnection* top = _papTextureConnection[idx];
//    for (int i = _num_materials-1; i >= 1; i--) {
//        if (i <= idx) {
//            _papTextureConnection[i] = _papTextureConnection[i-1];
//        }
//    }
//    _papTextureConnection[0] = top;
//}
void Model::transformPosVtx(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit, int prm_vtx_num) {
    byte* paVtxBuffer = (byte*)prm_paVtxBuffer;
    VERTEX_POS* pVtx;
    for (int i = 0; i < prm_vtx_num; i++) {
        D3DXVECTOR3 vecVertex;
        pVtx = (VERTEX_POS*)(paVtxBuffer + (prm_size_of_vtx_unit*i)); //頂点データの頭だし
        vecVertex.x = pVtx->x;
        vecVertex.y = pVtx->y;
        vecVertex.z = pVtx->z;
        D3DXVec3TransformCoord(&vecVertex, &vecVertex, &_matBaseTransformMatrix);
    }
}

void Model::transformPosNomalVtx(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit, int prm_vtx_num) {
    byte* paVtxBuffer = (byte*)prm_paVtxBuffer;
    Model::VERTEX_POS_NOMAL* pVtx;

    for (int i = 0; i < prm_vtx_num; i++) {
        D3DXVECTOR3 vecVertex;
        D3DXVECTOR3 vecNormal;
        pVtx = (Model::VERTEX_POS_NOMAL*)(paVtxBuffer + (prm_size_of_vtx_unit*i)); //頂点データの頭だし
        vecVertex.x = pVtx->x;
        vecVertex.y = pVtx->y;
        vecVertex.z = pVtx->z;
        D3DXVec3TransformCoord(&vecVertex, &vecVertex, &_matBaseTransformMatrix);
        vecNormal.x = pVtx->nx;
        vecNormal.y = pVtx->ny;
        vecNormal.z = pVtx->nz;
        D3DXVec3TransformNormal(&vecNormal, &vecNormal, &_matBaseTransformMatrix);
        pVtx->x = vecVertex.x;
        pVtx->y = vecVertex.y;
        pVtx->z = vecVertex.z;
        pVtx->nx = vecNormal.x;
        pVtx->ny = vecNormal.y;
        pVtx->nz = vecNormal.z;

        ///MeshModelの場合だけ///////////////////
        if (_obj_class & Obj_GgafDx_MeshModel) {
            D3DXVECTOR3 vecTangent;
            D3DXVECTOR3 vecBinormal;
            //MeshModelの場合
            MeshModel::VERTEX* pVtx_ex = (MeshModel::VERTEX*)pVtx;
            vecTangent.x = pVtx_ex->tan_x;
            vecTangent.y = pVtx_ex->tan_y;
            vecTangent.z = pVtx_ex->tan_z;
            D3DXVec3TransformNormal(&vecTangent, &vecTangent, &_matBaseTransformMatrix);
            vecBinormal.x = pVtx_ex->bin_x;
            vecBinormal.y = pVtx_ex->bin_y;
            vecBinormal.z = pVtx_ex->bin_z;
            D3DXVec3TransformNormal(&vecBinormal, &vecBinormal, &_matBaseTransformMatrix);

            pVtx_ex->tan_x = vecTangent.x;
            pVtx_ex->tan_y = vecTangent.y;
            pVtx_ex->tan_z = vecTangent.z;
            pVtx_ex->bin_x = vecBinormal.x;
            pVtx_ex->bin_y = vecBinormal.y;
            pVtx_ex->bin_z = vecBinormal.z;
        }
        /////////////////////////////////////////////
    }

    D3DXVECTOR3 vec;
    for (int i = 0; i < prm_vtx_num; i++) {
        pVtx = (Model::VERTEX_POS_NOMAL*)(paVtxBuffer + (prm_size_of_vtx_unit*i));
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

        ///MeshModelの場合だけ///////////////////
        if (_obj_class & Obj_GgafDx_MeshModel) {
            MeshModel::VERTEX* pVtx_ex = (MeshModel::VERTEX*)pVtx;
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
}

void Model::prepareVtx(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit,
                       Frm::Model3D* model_pModel3D,
                       uint32_t* paNumVertices) {
    //＜前提＞
    //prm_paVtxBuffer には x,y,z,tu,tv は設定済み
    Frm::Mesh* model_pMeshesFront = model_pModel3D->_Meshes.front();
    int nVertices = model_pMeshesFront->_nVertices; //メッシュ連結後の総頂点数
    int nFaces = model_pMeshesFront->_nFaces;       //メッシュ連結後の総面数
    int nFaceNormals = model_pMeshesFront->_nFaceNormals; //メッシュ連結後の総法線数
    //法線設定。
    //共有頂点の法線は平均化を試みる！
    //【2009/03/04の脳みそによるアイディア】
    //共有頂点に、面が同じような方面に集中した場合、単純に加算して面数で割る平均化をすると法線は偏ってしまう。
    //そこで、共有頂点法線への影響度割合（率）を、その面法線が所属する面の頂点角の大きさで決めるようにした。
    //法線の影響度割合 ＝ その法線が所属する頂点の成す角 ／ その頂点にぶら下がる全faceの成す角合計
    //とした。最後に正規化する。
    byte* paVtxBuffer = (byte*)prm_paVtxBuffer;
    float* paRad = NEW float[nFaces*3];
    float* paRadSum_Vtx = NEW float[nVertices];
    for (int v = 0; v < nVertices; v++) {
        paRadSum_Vtx[v] = 0;
    }
    std::fill_n(paRadSum_Vtx, nVertices, 0);
    DWORD indexVertices_per_Face[3];
    DWORD indexNormals_per_Face[3];
    for (int face_index = 0; face_index < nFaces; face_index++) {
        for (int v = 0; v < 3; v++) {
            //面に対する頂点インデックス３つ(A,B,Cとする)
            indexVertices_per_Face[v] = model_pMeshesFront->_Faces[face_index].data[v];
            //面に対する法線インデックス３つ
            if (nFaceNormals > face_index) {
                indexNormals_per_Face[v] = model_pMeshesFront->_FaceNormals[face_index].data[v];
            } else {
                //法線が無い場合
                indexNormals_per_Face[v] = (DWORD)0;
            }
        }

        //頂点インデックス A の角(∠CAB)を求めて、配列に保持
        paRad[face_index*3+0] = Model::getRadv1_v0v1v2(
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[2]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[1]]
                       );
        //A の頂点インデックス番号に紐つけて、角を加算
        paRadSum_Vtx[indexVertices_per_Face[0]] += paRad[face_index*3+0];

        //頂点インデックス B の角(∠ABC)を求めて、配列に保持
        paRad[face_index*3+1] = Model::getRadv1_v0v1v2(
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[1]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[2]]
                       );
        //B の頂点インデックス番号に紐つけて、角を加算
        paRadSum_Vtx[indexVertices_per_Face[1]] += paRad[face_index*3+1];

        //頂点インデックス C の角(∠ACB)を求めて、配列に保持
        paRad[face_index*3+2] = (float)(2*PI - (paRad[face_index*3+0] + paRad[face_index*3+1]));
        //C の頂点インデックス番号に紐つけて、角を加算
        paRadSum_Vtx[indexVertices_per_Face[2]] += paRad[face_index*3+2];
    }

    float rate; //その法線の出ている頂点の成す角の率。つまり法線ベクトルに掛ける率。その法線ベクトルの影響の強さ。
    Model::VERTEX_POS_NOMAL* pVtx;
    D3DXVECTOR3 p[3];
    D3DXVECTOR2 uv[3];
    D3DXVECTOR3 outTangent;
    D3DXVECTOR3 outBinormal;
    for (int face_index = 0; face_index < nFaces; face_index++) { //全ポリゴン数ループ
        //ポリゴン（三角面）の頂点インデックスを３つ格納
        for (int v = 0; v < 3; v++) {
            indexVertices_per_Face[v] = model_pMeshesFront->_Faces[face_index].data[v];
            if (nFaceNormals > face_index) {
                indexNormals_per_Face[v] = model_pMeshesFront->_FaceNormals[face_index].data[v];
            } else {
                //法線が無い場合
                indexNormals_per_Face[v] = (DWORD)0;
            }
        }
        if (nFaceNormals > face_index) {
            for (int v = 0; v < 3; v++) {
                rate = (paRad[face_index*3+v] / paRadSum_Vtx[indexVertices_per_Face[v]]);
                pVtx = (Model::VERTEX_POS_NOMAL*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
                pVtx->nx += (model_pMeshesFront->_Normals[indexNormals_per_Face[v]].x * rate);
                pVtx->ny += (model_pMeshesFront->_Normals[indexNormals_per_Face[v]].y * rate);
                pVtx->nz += (model_pMeshesFront->_Normals[indexNormals_per_Face[v]].z * rate);
            }
        } else {
            //法線が無い場合、法線を計算して作りだす。

            //面に対する頂点インデックス３つ
            int indexVertices1 = model_pMeshesFront->_Faces[face_index].data[0];
            int indexVertices2 = model_pMeshesFront->_Faces[face_index].data[1];
            int indexVertices3 = model_pMeshesFront->_Faces[face_index].data[2];
            //面の頂点３つ
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
            // 3 つの点から平面を作成
            D3DXPlaneFromPoints(&Plane, &v1, &v2, &v3);
            //正規化した平面(法線)を算出
            D3DXPlaneNormalize(&Plane, &Plane);
            for (int v = 0; v < 3; v++) {
                rate = (paRad[face_index*3+v] / paRadSum_Vtx[indexVertices_per_Face[v]]);
                pVtx = (Model::VERTEX_POS_NOMAL*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
                pVtx->nx += (Plane.a * rate);
                pVtx->ny += (Plane.b * rate);
                pVtx->nz += (Plane.c * rate);
            }
        }

        ///Obj_GgafDx_MeshModelの場合だけ//////////////////////////////////////////
        if (_obj_class & Obj_GgafDx_MeshModel) {
            //何を血迷ったか、バンプマップの為U軸 接ベクトル（Tangent）及び V軸 従法線（Binormal）の平均を計算
            //頂点バッファに、Tangent Binormal 埋め込み有りの場合
            for (int v = 0; v < 3; v++) { //p[3] と uv[3] にパラメータセット
                pVtx = (Model::VERTEX_POS_NOMAL*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
                p[v].x = pVtx->x;
                p[v].y = pVtx->y;
                p[v].z = pVtx->z;
                MeshModel::VERTEX* pVtx_ex = (MeshModel::VERTEX*)pVtx;
                uv[v].x = pVtx_ex->tu;
                uv[v].y = pVtx_ex->tv;
            }
            //計算
            Model::calcTangentAndBinormal(
                    &p[0], &uv[0],
                    &p[1], &uv[1],
                    &p[2], &uv[2],
                    &outTangent, &outBinormal); //面に対する U軸（Tangent）及びV軸（Binormal）
            //結果を頂点バッファに書き込み（平均も考慮）
            for (int v = 0; v < 3; v++) {
                //MeshModelの場合
                MeshModel::VERTEX* pVtx_ex = (MeshModel::VERTEX*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
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

    //XファイルのFrameTransformMatrix(0フレーム目の初期化アニメーション)を考慮
    int n = 0;
    int nVertices_begin = 0;
    int nVertices_end = 0;
    for (std::list<Frm::Bone*>::iterator iteBone = model_pModel3D->_toplevel_Skelettons.begin() ;
            iteBone != model_pModel3D->_toplevel_Skelettons.end(); iteBone++) {

        _TRACE_("ModelManager : (*iteBone)->_Name="<<((*iteBone)->_Name));

        if ((*iteBone)) {
            D3DXMATRIX FrameTransformMatrix;
            D3DXMatrixIdentity(&FrameTransformMatrix);
            Frm::Matrix* pMatPos = &((*iteBone)->_MatrixPos);
            if (pMatPos == 0 || pMatPos== nullptr || pMatPos->isIdentity()) {
                //FrameTransformMatrix は単位行列
                _TRACE_("ModelManager : FrameTransformMatrix is Identity");
            } else {
                _TRACE_("ModelManager : Execute FrameTransform!");
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
            }

            D3DXMatrixMultiply(&FrameTransformMatrix, &FrameTransformMatrix, &_matBaseTransformMatrix);
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
                pVtx = (Model::VERTEX_POS_NOMAL*)(paVtxBuffer + (prm_size_of_vtx_unit*i));
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

                ///MeshModelの場合だけ///////////////////
                if (_obj_class & Obj_GgafDx_MeshModel) {
                    //MeshModelの場合
                    MeshModel::VERTEX* pVtx_ex = (MeshModel::VERTEX*)pVtx;
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
        n++;
    }
    //最後に法線正規化して設定
    D3DXVECTOR3 vec;
    for (int i = 0; i < nVertices; i++) {
        pVtx = (Model::VERTEX_POS_NOMAL*)(paVtxBuffer + (prm_size_of_vtx_unit*i));
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

        ///MeshModelの場合だけ///////////////////
        if (_obj_class & Obj_GgafDx_MeshModel) {
            MeshModel::VERTEX* pVtx_ex = (MeshModel::VERTEX*)pVtx;
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

void Model::calcTangentAndBinormal(
        D3DXVECTOR3* p0, D3DXVECTOR2* uv0,
        D3DXVECTOR3* p1, D3DXVECTOR2* uv1,
        D3DXVECTOR3* p2, D3DXVECTOR2* uv2,
        D3DXVECTOR3* outTangent, D3DXVECTOR3* outBinormal) {
    // 5次元→3次元頂点に
    D3DXVECTOR3 CP0[3] =
            { D3DXVECTOR3(p0->x, uv0->x, uv0->y), D3DXVECTOR3(p0->y, uv0->x, uv0->y), D3DXVECTOR3(p0->z, uv0->x, uv0->y), };
    D3DXVECTOR3 CP1[3] =
            { D3DXVECTOR3(p1->x, uv1->x, uv1->y), D3DXVECTOR3(p1->y, uv1->x, uv1->y), D3DXVECTOR3(p1->z, uv1->x, uv1->y), };
    D3DXVECTOR3 CP2[3] =
            { D3DXVECTOR3(p2->x, uv2->x, uv2->y), D3DXVECTOR3(p2->y, uv2->x, uv2->y), D3DXVECTOR3(p2->z, uv2->x, uv2->y), };

    // 平面パラメータからUV軸座標算出
    float U[3], V[3];
    static double lim = FLT_MAX/100.0;
    for (int i = 0; i < 3; ++i) {
        D3DXVECTOR3 V1 = CP1[i] - CP0[i];
        D3DXVECTOR3 V2 = CP2[i] - CP1[i];
        D3DXVECTOR3 VABC;
        D3DXVec3Cross(&VABC, &V1, &V2);

        if (ZEROf_EQ(VABC.x)) {
            // やばいす！
            // ポリゴンかUV上のポリゴンが縮退してます！
            //_TRACE_("【警告】 Model::calcTangentAndBinormal ポリゴンかUV上のポリゴンが縮退してます！");
            U[i] = -SGN(VABC.y) * lim;
            V[i] = -SGN(VABC.z) * lim;
        } else {
            U[i] = -VABC.y / VABC.x;
            V[i] = -VABC.z / VABC.x;
        }
    }

    memcpy(outTangent, U, sizeof(float) * 3);
    memcpy(outBinormal, V, sizeof(float) * 3);

    // 正規化します
    D3DXVec3Normalize(outTangent, outTangent);
    D3DXVec3Normalize(outBinormal, outBinormal);
}

//マルペケ
//http://marupeke296.com/DXPS_No12_CalcTangentVectorSpace.html
//U軸とV軸を求める関数
// 3頂点とUV値から指定座標でのU軸（Tangent）及びV軸（Binormal）を算出
// p0, p1, p2    : ローカル空間での頂点座標（ポリゴン描画順にすること）
// uv0, uv1, uv2 : 各頂点のUV座標
// outTangent    : U軸（Tangent）出力
// outBinormal   : V軸（Binormal）出力


float Model::getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2) {
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
    //ベクトル V W の成す角を求める
    //    V=(vx,vy,vz)=(bx-ax,by-ay,bz-az)
    //    W=(wx,wy,wz)=(cx-ax,cy-ay,cz-az)
    //    とするとV、Wベクトルがなす角は
    //    cosα=(V、Wベクトルの内積）÷（Vの大きさ）÷（Wの大きさ）
    //        =(vx*wx+vy*wy+vz*wz)
    //         ÷ルート(vx^2+vy^2+vz^2)÷ルート(wx^2+wy^2+wz^2)
    float DOT, LV, LW, cosV1;
    //_TRACE3_("V=("<<V.x<<"."<<V.y<<","<<V.z<<")");
    //_TRACE3_("W=("<<W.x<<"."<<W.y<<","<<W.z<<")");
    DOT = V.Dot(W);
    LV = V.Abs();
    LW = W.Abs();
    cosV1 = DOT / LV / LW;
    return acos(cosV1);
}


void Model::setMaterial(Frm::Mesh* in_pMeshesFront) {
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
                   _pa_texture_filenames[n] = CONFIG::WHITE_TEXTURE;
                }
                n++;
            }
        } else {
            //マテリアル定義が１つも無いので、描画のために無理やり１つマテリアルを作成。
            _num_materials = 1;
            _paMaterial_default  = NEW D3DMATERIAL9[1];
            _pa_texture_filenames = NEW std::string[1];
            setDefaultMaterial(&(_paMaterial_default[0]));
            _pa_texture_filenames[0] = CONFIG::WHITE_TEXTURE;
        }
    }

}
void Model::setDefaultMaterial(D3DMATERIAL9* pMateria) {
    pMateria->Diffuse.r = 1.0f;
    pMateria->Diffuse.g = 1.0f;
    pMateria->Diffuse.b = 1.0f;
    pMateria->Diffuse.a = 1.0f;
    pMateria->Ambient.r = 1.0f;
    pMateria->Ambient.g = 1.0f;
    pMateria->Ambient.b = 1.0f;
    pMateria->Ambient.a = 1.0f;
    pMateria->Specular.r = 1.0f;
    pMateria->Specular.g = 1.0f;
    pMateria->Specular.b = 1.0f;
    pMateria->Specular.a = 1.0f;
    pMateria->Power = 0.0f;
    pMateria->Emissive.r = 1.0f;
    pMateria->Emissive.g = 1.0f;
    pMateria->Emissive.b = 1.0f;
    pMateria->Emissive.a = 1.0f;
}

std::string Model::getXFilePath(std::string prm_xfile) {
    std::string xfile_path2 = CONFIG::DIR_MESH[2] + "/" + prm_xfile;
    UTIL::strReplace(xfile_path2, "//", "/");
    if (PathFileExists(xfile_path2.c_str()) ) {
        _TRACE_("Model::getXFilePath() xfile_path2="<<xfile_path2);
        return xfile_path2; //カレントに存在すればそれを優先
    } else {
        std::string xfile_path1 = CONFIG::DIR_MESH[1] + "/" + prm_xfile;
        UTIL::strReplace(xfile_path1, "//", "/");
        _TRACE_("Model::getXFilePath() xfile_path1="<<xfile_path1);
        if (PathFileExists(xfile_path1.c_str()) ) {
            return xfile_path1; //ユーザースキンに存在すればそれを優先
        } else {
            std::string xfile_path0 = CONFIG::DIR_MESH[0] + "/" + prm_xfile;
            UTIL::strReplace(xfile_path0, "//", "/");
            _TRACE_("Model::getXFilePath() xfile_path0="<<xfile_path0);
            if (PathFileExists(xfile_path0.c_str()) ) {
                return xfile_path0;
            } else {
                throwCriticalException("Model::getXFilePath() Xファイルが以下から見つかりません。prm_xfile="<<prm_xfile<<"\n"<<
                        "xfile_path2="<<xfile_path2<<"\n"
                        "xfile_path1="<<xfile_path1<<"\n"
                        "xfile_path0="<<xfile_path0<<"\n"
                        );
            }
        }
    }
}

std::string Model::getModelDefineFilePath(std::string prm_model_name) {
    std::string model_define_path2 = CONFIG::DIR_MODEL[2] + "/" + prm_model_name;
    UTIL::strReplace(model_define_path2, "//", "/");
    if (PathFileExists(model_define_path2.c_str()) ) {
        _TRACE_("Model::getModelDefineFilePath() model_define_path2.c_str()="<<model_define_path2.c_str());
        return model_define_path2;
    } else {
        std::string model_define_path1 = CONFIG::DIR_MODEL[1] + "/" +  prm_model_name;
        UTIL::strReplace(model_define_path1, "//", "/");
        if (PathFileExists(model_define_path1.c_str()) ) {
            _TRACE_("Model::getModelDefineFilePath() model_define_path1.c_str()="<<model_define_path1.c_str());
            return model_define_path1; //ユーザースキンに存在すればそれを優先
        } else {
            std::string model_define_path0 = CONFIG::DIR_MODEL[0] + "/" +  prm_model_name;
            UTIL::strReplace(model_define_path0, "//", "/");
            if (PathFileExists(model_define_path0.c_str()) ) {
                _TRACE_("Model::getModelDefineFilePath() model_define_path3.c_str()="<<model_define_path0.c_str());
                return model_define_path0;
            } else {
                _TRACE_("Model::getModelDefineFilePath() モデル定義ファイルが以下から見つかりません。prm_model_name="<<prm_model_name<<"\n"<<
                        "model_define_path2="<<model_define_path2<<"\n"
                        "model_define_path1="<<model_define_path1<<"\n"
                        "model_define_path0="<<model_define_path0<<"\n"
                        );
                return "";
            }
        }
    }
}

Model::~Model() {
    _TRACE4_("Model::~Model("<<_model_id<<") Adr:"<<this);
    GGAF_DELETEARR_NULLABLE(_model_id);
    GGAF_DELETEARR_NULLABLE(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    delete _pTexBlinker;
}

