/////////////////////////////////////////////////////////
// Frm_Mesh.h
//
//
/////////////////////////////////////////////////////////

#ifndef FRM_MESH_H
#define FRM_MESH_H
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/dx/util/XFile/framework/frm_types.h"
#include "jp/ggaf/dx/util/XFile/framework/frm_3Dmath.h"
//#include "framework\frm_Quaternion.h"
#include "jp/ggaf/dx/util/XFile/framework/frm_Material.h"

//#define DEBUG
//#include "jp/ggaf/dx/util/XFile/ToolBox/Mytrace.h"

#include <list>
#include <vector>

namespace Frm {

class Mesh;

class Bone {
public:
    Bone(void) :
        _nVertices(0), _Vertices(0), _Weights(0) {
        _MatrixPos.Identity();
        _SkinOffset.Identity();
        _MeshName = ""; //add tsuge
        _Name = "";     //add tsuge
    }
    ~Bone(void);
    Bone* IsName(std::string &BoneName);
    void UpdateIndices(uint16_t pIndex);

    Matrix _MatrixPos, _SkinOffset;
    uint32_t _nVertices;
    uint16_t* _Vertices;
    float* _Weights;
    std::string _MeshName;
    std::string _Name;
    std::list<Bone*> _Bones;
};

struct Subset {
    uint16_t Size;
    Face* Faces;
};

class Mesh {
public:
    Mesh(void) :
        _nVertices(0), _FirstVertex(0), _Vertices(0),
        _nTextureCoords(0), _FirstTextureCoord(0), _TextureCoords(0),
        _nFaces(0),  _FirstFace(0), _Faces(0),
        _nNormals(0), _FirstNormal(0), _Normals(0),
        _nFaceNormals(0), _FaceNormals(0),
        _nMaterials(0), _FirstMaterial(0), _FaceMaterials(0) {
    }
    ~Mesh(void);
    Mesh* IsName(std::string &MeshName) {
        if (strcmp(_Name.c_str(), MeshName.c_str()) == 0)
            return this;
        return 0;
    }
    void UpdateIndices(void);
    void CreateSubsets(void);
    //Vertices
    uint16_t _nVertices, _FirstVertex;
    Vertex* _Vertices;
    //Texture Coords for each vertex
    uint16_t _nTextureCoords, _FirstTextureCoord;
    TCoord* _TextureCoords;
    //Faces
    uint32_t _nFaces, _FirstFace;
    Face* _Faces;
    //Subset of a mesh: there is one subset for each material used
    std::list<Subset*> _Subsets;
    //Normals
    uint16_t _nNormals, _FirstNormal;
    vector<float>* _Normals;
    uint16_t _nFaceNormals;
    Face* _FaceNormals;   //add tsuge
    //Material index for each face
    uint16_t _nMaterials, _FirstMaterial;
    uint16_t* _FaceMaterials;
    //list of Materials for that Mesh
    std::list<Material*> _Materials;
    std::string _Name;
};

typedef struct {
    uint32_t Time;
    Frm::Quaternion Rotation;
} RotateKey;

typedef struct {
    uint32_t Time;
    Frm::Vertex Translation;
} PositionKey;

typedef struct {
    uint32_t Time;
    Frm::Vector Scale;
} ScaleKey;

typedef struct {
    uint32_t Time;
    Frm::Matrix Matrix;
} MatrixKey;

class Animation {
public:
    ~Animation(void);
    Animation* Get(void) {
        return this;
    }
    Animation* IsName(std::string &pText) {
        if (strcmp(_BoneName.c_str(), pText.c_str()) == 0)
            return this;
        return 0;
    }

    std::string _BoneName;
    std::vector<ScaleKey*> _Scalings;
    std::vector<RotateKey*> _Rotations;
    std::vector<PositionKey*> _Translations;
    std::vector<MatrixKey*> _Matrices;
};

class AnimationSet {
public:
    ~AnimationSet(void);
    AnimationSet* IsName(std::string &pText) {
        if (strcmp(_Name.c_str(), pText.c_str()) == 0)
            return this;
        return 0;
    }
    Animation* FindAnimation(std::string &pText);
    std::string _Name;
    std::list<Animation*> _Animations;
    uint32_t _MaxKey; //Maximum time key for the full animation set
};

class Model3D {
public:
    Model3D(void) :
        _Skeletton(0) {
    }
    ~Model3D(void);
    Mesh* IsMeshName(std::string &pText);
    void ConcatenateMeshes(void);
    AnimationSet* FindAnimationSet(std::string &pText);
    Bone* _Skeletton;
    std::list<Mesh*> _Meshes;
    std::list<AnimationSet*> _AnimationSets;

    //add tsuge begin
    std::list<Frm::Bone*> _toplevel_Skelettons;
    //add tsuge end

private:
    void UpdateBoneIndices(Bone* &pBone);
};

}

#endif
