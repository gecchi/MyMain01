/////////////////////////////////////////////////////////
// IOModel_X.h
// load/save X file descriptions
//
/////////////////////////////////////////////////////////

#ifndef IOMODEL_X
#define IOMODEL_X

//#define DEBUG


#include "../Toolbox/MyTrace.h"

#include "../framework/frm_IO.h"
//#include <GL\freeglut.h>
#include "../framework/Frm_Mesh.h"
#include "../ToolBox/XFileStructs.h"

namespace ToolBox {

class IO_Model_X: Frm::IO<Frm::Model3D*> {
public:
    IO_Model_X(void) :
        _LoadSkeletton(0) { //tsuge add
        _Type = IO_3DX;
        token_next = 0; //add tsuge
    }
    bool Load(std::string pFilename, Frm::Model3D* &pT);
    bool Save(std::string pFilename, Frm::Model3D* &pT);
    bool Load(std::string pFilename, std::vector<Frm::Model3D*> &pVT) {
        return false;
    }
    bool Save(std::string pFilename, std::vector<Frm::Model3D*> &pVT) {
        return false;
    }

private:
    ifstream fin;
    Frm::Bone* _LoadSkeletton;
    Frm::Mesh* _LoadMesh;
    Frm::AnimationSet* _LoadAnimationSet;
    Frm::Model3D* _Object;
    std::string active_load_filename;
    //Utilities
    int16 ProcessBlock(void);
    int16 BlockID(std::string &pText);
    void AvoidTemplate(void);
    void Find(uchar pChar);
    //Unique X struct ID in case no name are found
    //Uses the Windows function GetTickCount
    char* SetUID(char pType);
    //structure used by the previous function to quickly
    //convert a 32 bit number to a non-significant text.
    union {
        uint32 Integer[2]; //mod tsuge
        //char Text[5];
        char Text[8+2]; //mod tsuge
    } _X_UID;

    /** X�t�@�C���ǂݍ��ݎ��̎��̃g�[�N���\�� */
    uchar token_next; //add tsuge

    //X File struct processing
    uint32 _MaxKey; //Max animation key for a loaded animation set
    void ProcessFrameTransformMatrix(Frm::Bone* &pB);
    void ProcessBone(Frm::Bone* pBone);
    void ProcessMesh(void);
    void ProcessMeshTextureCoords(void);
    void ProcessMeshMaterials(void);
    void ProcessMeshNormals(void);
    void ProcessMaterial(void);
    void ProcessSkinWeights(void);
    void ProcessAnimationSets(void);
    void ProcessAnimations(Frm::AnimationSet* &pAS);
    void ProcessAnimationKeys(Frm::Animation* &pA);
    void MapMeshToBones(Frm::Bone* &pBone);

};

}
#endif