/////////////////////////////////////////////////////////
// Frm_Mesh.cpp
//
//
/////////////////////////////////////////////////////////

#include "jp/ggaf/dx/util/XFile/framework/Frm_mesh.h"
#include "jp/ggaf/dx/util/Util.h"
#include <d3dx9math.h>

using namespace Frm;

Bone::~Bone(void) {
    if (_Vertices != 0)
        delete[] _Vertices;
    if (_Weights != 0)
        delete[] _Weights;
    while (!_Bones.empty()) {
        delete _Bones.back();
        _Bones.pop_back();
    }
}

Bone* Bone::IsName(std::string &BoneName) {
    if (strcmp(_Name.c_str(), BoneName.c_str()) == 0)
        return this;

    if (_Bones.empty())
        return 0;

    for (std::list<Bone*>::iterator i = _Bones.begin(); i != _Bones.end(); i++)
        if ((*i)->IsName(BoneName) != 0)
            return (*i)->IsName(BoneName);
    return 0;
}

void Bone::UpdateIndices(uint32_t pIndex) {
    for (uint32_t i = 0; i < _nVertices; i++)
        _Vertices[i] += pIndex;
}

Mesh::~Mesh(void) {
    if (_Vertices != 0)
        delete[] _Vertices;
    if (_Faces != 0)
        delete[] _Faces;
    if (_Normals != 0)
        delete[] _Normals;
    if (_TextureCoords != 0)
        delete[] _TextureCoords;
    while (!_Materials.empty()) {
        delete _Materials.back();
        _Materials.pop_back();
    }
    if (_FaceMaterials != 0)
        delete[] _FaceMaterials;
    while (!_Subsets.empty()) {
        delete[] _Subsets.back()->Faces;
        delete _Subsets.back();
        _Subsets.pop_back();
    }
    //add tsuge begin
    if (_FaceNormals != 0) {
        delete[] _FaceNormals;
    }
    //sdd tsuge end
}

void Mesh::UpdateIndices(void) {
    if (!_FaceMaterials) {
        _FaceMaterials = NEW uint32_t[_nFaces];
        for (uint32_t i = 0; i < _nFaces; i++) {
            _FaceMaterials[i] = 0;
        }
    }
    for (uint32_t i = 0; i < _nFaces; i++) {
        _Faces[i].data[0] += _FirstVertex;
        _Faces[i].data[1] += _FirstVertex;
        _Faces[i].data[2] += _FirstVertex;

        _FaceMaterials[i] += _FirstMaterial;
    }

    if (_nNormals != 0)
        for (uint32_t i = 0; i < _nFaces; i++) {
            _FaceNormals[i].data[0] += _FirstNormal;
            _FaceNormals[i].data[1] += _FirstNormal;
            _FaceNormals[i].data[2] += _FirstNormal;
        }
}

void Mesh::CreateSubsets(void) {
    uint32_t FaceCount;
    Subset* MeshSubset;

    //For each material
    for (uint32_t i = 0; i < _Materials.size(); i++) {
        //We count the number of faces using this material
        FaceCount = 0;
        for (uint32_t j = 0; j < _nFaces; j++)
            if (_FaceMaterials[j] == i)
                ++FaceCount;
        //We initialise the mesh subset
        MeshSubset = NEW Subset;
        MeshSubset->Size = FaceCount;
        MeshSubset->Faces = NEW Face[FaceCount];
        int k = 0;
        //We fill in the Mesh subset
        for (uint32_t j = 0; j < _nFaces; j++)
            if (_FaceMaterials[j] == i)
                MeshSubset->Faces[k++] = _Faces[j];
        //And we add that subset to the list
        _Subsets.push_back(MeshSubset);
    }
}

/*************************************************
 NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW*/

Animation::~Animation(void) {
    while (!_Scalings.empty()) {
        delete _Scalings.back();
        _Scalings.pop_back();
    }
    while (!_Rotations.empty()) {
        delete _Rotations.back();
        _Rotations.pop_back();
    }
    while (!_Translations.empty()) {
        delete _Translations.back();
        _Translations.pop_back();
    }
    while (!_Matrices.empty()) {
        delete _Matrices.back();
        _Matrices.pop_back();
    }
}

AnimationSet::~AnimationSet(void) {
    while (!_Animations.empty()) {
        delete _Animations.back();
        _Animations.pop_back();
    }
}

Animation* AnimationSet::FindAnimation(std::string &pText) {
    for (std::list<Animation*>::iterator i = _Animations.begin(); i
            != _Animations.end(); i++)
        if ((*i)->IsName(pText) != 0)
            return (*i)->IsName(pText);
    return 0;
}

/*************************************************/

Model3D::~Model3D(void) {
    //tsuge modify begin

    //if (_Skeletton != 0)
    //    delete _Skeletton;

    //_toplevel_Skelettonsのリスト解放するので、上の
    //delete は不要になった。
    while (!_toplevel_Skelettons.empty()) {
        delete _toplevel_Skelettons.back();
        _toplevel_Skelettons.pop_back();
    }
    //tsuge modify end

    while (!_Meshes.empty()) {
        delete _Meshes.back();
        _Meshes.pop_back();
    }
    while (!_AnimationSets.empty()) {
        delete _AnimationSets.back();
        _AnimationSets.pop_back();
    }
}

Mesh* Model3D::IsMeshName(std::string &pText) {
    for (std::list<Mesh*>::iterator i = _Meshes.begin(); i != _Meshes.end(); i++)
        if ((*i)->IsName(pText) != 0)
            return (*i)->IsName(pText);
    return 0;
}

void Model3D::ConcatenateMeshes(void) {
    //We only concatenate when there are at least two meshes
    //if (_Meshes.size() < 2)
    //    return;

    _TRACE_("Concatenating "<<(_Meshes.size())<<" Meshes ...");

    Mesh* ConcatMesh = NEW Mesh;
    Mesh* LastMesh = _Meshes.back();

    ConcatMesh->_Name = "ConcatMesh";

    //We create the NEW mesh.
    //We get the dimensions of the NEW mesh
    ConcatMesh->_nVertices = LastMesh->_FirstVertex + LastMesh->_nVertices;
    ConcatMesh->_nFaces = LastMesh->_FirstFace + LastMesh->_nFaces;
    ConcatMesh->_nTextureCoords = LastMesh->_FirstTextureCoord + LastMesh->_nTextureCoords;
    ConcatMesh->_nNormals = LastMesh->_FirstNormal + LastMesh->_nNormals;
    //add tsuge begin
    ConcatMesh->_nMaterials = LastMesh->_FirstMaterial + LastMesh->_nMaterials;
    ConcatMesh->_nFaceNormals = LastMesh->_nFaceNormals + LastMesh->_nFaceNormals;
    //addtsuge end


    //Here we have a control:
    //Texture coordinates must be as numerous as Vertices or there must be none
    //Normal vectors must be as numerous as Vertices or there must be none
    if ((ConcatMesh->_nTextureCoords < ConcatMesh->_nVertices) && (ConcatMesh->_nTextureCoords != 0)) {
        ConcatMesh->_nTextureCoords = ConcatMesh->_nVertices;
    }
    if ((ConcatMesh->_nNormals < ConcatMesh->_nVertices) && (ConcatMesh->_nNormals != 0)) {
        ConcatMesh->_nNormals = ConcatMesh->_nVertices;
    }

    _TRACE_("Final number of Vertices:"<< ConcatMesh->_nVertices);
    _TRACE_("Final number of Faces:"<< ConcatMesh->_nFaces);
    _TRACE_("Final number of TextureCoords:"<< ConcatMesh->_nTextureCoords);
    _TRACE_("Final number of Normals:"<< ConcatMesh->_nNormals);
    _TRACE_("Final number of Materials:"<< ConcatMesh->_nMaterials);


    //add tsuge
    for (std::list<Frm::Bone*>::iterator iteBone = _toplevel_Skelettons.begin(); iteBone != _toplevel_Skelettons.end(); iteBone++) {
        Matrix mat;
        mat.Identity();
        UpdateVertex((*iteBone), mat);
    }

    //We create all the arrays:
    // - Vertices and Faces
    // - Material indices per face
    // - Texture Coords
    // - Normal vectors and Face Allocation of Normal vectors
    ConcatMesh->_Vertices = NEW Frm::Vertex[ConcatMesh->_nVertices];
    memset(ConcatMesh->_Vertices, 0, ConcatMesh->_nVertices
            * sizeof(Frm::Vertex));
    ConcatMesh->_Faces = NEW Frm::Face[ConcatMesh->_nFaces];
    memset(ConcatMesh->_Faces, 0, ConcatMesh->_nFaces * sizeof(Frm::Face));
    ConcatMesh->_FaceMaterials = NEW uint32_t[ConcatMesh->_nFaces];
    memset(ConcatMesh->_FaceMaterials, 0, ConcatMesh->_nFaces * sizeof(uint32_t));
    if (ConcatMesh->_nTextureCoords != 0) {
        ConcatMesh->_TextureCoords
                = NEW Frm::TCoord[ConcatMesh->_nTextureCoords];
        memset(ConcatMesh->_TextureCoords, 0, ConcatMesh->_nTextureCoords
                * sizeof(Frm::TCoord));
    }
    if (ConcatMesh->_nNormals != 0) {
        ConcatMesh->_Normals = NEW Frm::vector<float>[ConcatMesh->_nNormals];
        ConcatMesh->_FaceNormals = NEW Frm::Face[ConcatMesh->_nFaces];
        memset(ConcatMesh->_Normals, 0, ConcatMesh->_nNormals
                * sizeof(Frm::vector<float>));
        memset(ConcatMesh->_FaceNormals, 0, ConcatMesh->_nFaces
                * sizeof(Frm::Face));
    }

    //We fill up the arrays with each array from the _Meshes container
    for (std::list<Mesh*>::iterator i = _Meshes.begin(); i != _Meshes.end(); i++) {
        (*i)->UpdateIndices();
        memcpy(&(ConcatMesh->_Vertices[(*i)->_FirstVertex]), (*i)->_Vertices, (*i)->_nVertices * sizeof(Frm::Vertex));

        memcpy(&(ConcatMesh->_Faces[(*i)->_FirstFace]), (*i)->_Faces,
                (*i)->_nFaces * sizeof(Frm::Face));
        memcpy(&(ConcatMesh->_FaceMaterials[(*i)->_FirstFace]),
                (*i)->_FaceMaterials, (*i)->_nFaces * sizeof(uint32_t));
        if ((*i)->_nTextureCoords != 0)
            memcpy(&(ConcatMesh->_TextureCoords[(*i)->_FirstTextureCoord]),
                    (*i)->_TextureCoords, (*i)->_nTextureCoords
                            * sizeof(Frm::TCoord));
        if ((*i)->_nNormals != 0) {
            memcpy(&(ConcatMesh->_Normals[(*i)->_FirstNormal]), (*i)->_Normals,
                    (*i)->_nNormals * sizeof(Frm::vector<float>));
            memcpy(&(ConcatMesh->_FaceNormals[(*i)->_FirstFace]),
                    (*i)->_FaceNormals, (*i)->_nFaces * sizeof(Frm::Face));
        }
        while (!(*i)->_Materials.empty()) {
            ConcatMesh->_Materials.push_back((*i)->_Materials.front());
            (*i)->_Materials.pop_front();
        }
    }




    ////////////////////////////////////////////////////////////
    //OK. We now process the bone hierarchy to update the
    //skinning indices

    _TRACE_("Adapting the Bone hierarchy ...");
//    if (_Skeletton != 0)
//        UpdateBoneIndices(_Skeletton);

    for (std::list<Frm::Bone*>::iterator iteBone = _toplevel_Skelettons.begin(); iteBone != _toplevel_Skelettons.end(); iteBone++) {
        UpdateBoneIndices(*iteBone);
    }
    //TODO: ここは複数。_toplevel_Skelettonsでまわす？
    _TRACE_("Bone hierarchy adapted.");

    //We eventually delete all the previous meshes
    while (!_Meshes.empty()) {
        delete _Meshes.back();
        _Meshes.pop_back();
    }

    //and push the NEW concatenated one
    _Meshes.push_back(ConcatMesh);

    //We create the subsets
    ConcatMesh->CreateSubsets();

    _TRACE_("All meshes are concatenated.");
}

void Model3D::UpdateBoneIndices(Bone* &pBone) {
    Mesh* BoneMesh = IsMeshName(pBone->_MeshName);
    if (BoneMesh != 0) {
        pBone->UpdateIndices(BoneMesh->_FirstVertex);
    }
    pBone->_MeshName = "ConcatMesh";
    if (!pBone->_Bones.empty()) {
        for (std::list<Bone*>::iterator i = pBone->_Bones.begin(); i != pBone->_Bones.end(); i++) {
            UpdateBoneIndices(*i);
        }
    }
}

//tsuge add
void Model3D::UpdateVertex(Bone* &pBone, Matrix& prm_MatrixPos) {
    //_TRACE_("UpdateVertex pBone:_MeshName="<<(pBone->_MeshName)<<"");
    //_TRACE_("UpdateVertex pBone:_Name="<<(pBone->_Name)<<"");
    Matrix mat(prm_MatrixPos);
    mat = ( pBone->_MatrixPos * mat);
    Mesh* pBoneMesh = IsMeshName(pBone->_MeshName);
    if (pBoneMesh != 0) {
        int nVertices = pBoneMesh->_nVertices; //頂点数
        int nNormals = pBoneMesh->_nNormals; //法線数
        //頂点変換
        for (int i = 0; i < nVertices; i++) {
            Vertex* pV = &(pBoneMesh->_Vertices[i]);
            Vertex v = mat * (*pV);
            //_TRACE_("Vbefore ["<<i<<"]"<<(pV->data[0])<<","<<(pV->data[1])<<","<<(pV->data[2]));
            pV->data[0] = v.data[0];
            pV->data[1] = v.data[1];
            pV->data[2] = v.data[2];
            //_TRACE_("Vafter  ["<<i<<"]"<<(pV->data[0])<<","<<(pV->data[1])<<","<<(pV->data[2]))
        }
        //法線変換
        Matrix mat_normals(mat);
        //平行移動成分除去
        mat_normals.data[12] = 0.0f;
        mat_normals.data[13] = 0.0f;
        mat_normals.data[14] = 0.0f;

        for (int i = 0; i < nNormals; i++) {
            //_TRACE_("Nbefore ["<<i<<"]"<<(pBoneMesh->_Normals[i].x)<<","<<(pBoneMesh->_Normals[i].y)<<","<<(pBoneMesh->_Normals[i].z));
            vector<float> vecNormal( mat_normals * (pBoneMesh->_Normals[i]));
            //正規化
            double t = 1.0 / sqrt(vecNormal.x * vecNormal.x + vecNormal.y * vecNormal.y + vecNormal.z * vecNormal.z);
            //vecNormal.Normalize();
            pBoneMesh->_Normals[i].x = vecNormal.x * t;
            pBoneMesh->_Normals[i].y = vecNormal.y * t;
            pBoneMesh->_Normals[i].z = vecNormal.z * t;
            //_TRACE_("Nafter ["<<i<<"]"<<(pBoneMesh->_Normals[i].x)<<","<<(pBoneMesh->_Normals[i].y)<<","<<(pBoneMesh->_Normals[i].z));
        }
    }
    if (!pBone->_Bones.empty()) {
        for (std::list<Bone*>::iterator iteBone = pBone->_Bones.begin(); iteBone != pBone->_Bones.end(); iteBone++) {
            UpdateVertex(*iteBone, mat);
        }
    }
}
/*************************************************
 NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW*/

AnimationSet* Model3D::FindAnimationSet(std::string &pText) {
    for (std::list<AnimationSet*>::iterator i = _AnimationSets.begin(); i
            != _AnimationSets.end(); i++)
        if ((*i)->IsName(pText) != 0)
            return (*i)->IsName(pText);
    return 0;
}
/*************************************************/

