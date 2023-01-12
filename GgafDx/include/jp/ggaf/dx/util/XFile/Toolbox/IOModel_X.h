/////////////////////////////////////////////////////////
// IOModel_X.h
// load/save X file descriptions
//
/////////////////////////////////////////////////////////

#ifndef IOMODEL_X
#define IOMODEL_X
#include "GgafDxCommonHeader.h"
//#define DEBUG

//#include "jp/ggaf/dx/util/XFile/ToolBox/MyTrace.h"
#include "jp/ggaf/dx/util/XFile/framework/frm_IO.h"
//#include <GL\freeglut.h>
#include "jp/ggaf/dx/util/XFile/framework/Frm_Mesh.h"
#include "jp/ggaf/dx/util/XFile/ToolBox/XFileStructs.h"

namespace ToolBox {

class IO_Model_X: Frm::IO<Frm::Model3D*> {
public:
    IO_Model_X(void) { // : _LoadSkeletton(0) { //tsuge add
        _Type = IO_3DX;
        token_next = 0; //add tsuge
    }
    bool Load(std::string pFilename, Frm::Model3D* pT);
//    bool Save(std::string pFilename, Frm::Model3D* &pT);
//    bool Load(std::string pFilename, std::vector<Frm::Model3D*> &pVT) {
//        return false;
//    }
//    bool Save(std::string pFilename, std::vector<Frm::Model3D*> &pVT) {
//        return false;
//    }

private:
    std::ifstream fin;
//    Frm::Bone* _LoadSkeletton;
    std::list<Frm::Bone*> _load_toplevel_Skelettons;
    Frm::Mesh* _LoadMesh;
    Frm::AnimationSet* _LoadAnimationSet;
    Frm::Model3D* _Object;
    std::string active_load_filename;
    //Utilities
    int16_t ProcessBlock(void);
    int16_t BlockID(std::string &pText);
    void AvoidTemplate(void);
    void Find(uint8_t pChar);
    //Unique X struct ID in case no name are found
    //Uses the Windows function GetTickCount
    char* SetUID(char pType);
    //structure used by the previous function to quickly
    //convert a 32 bit number to a non-significant text.
    union {
        uint32_t Integer[2]; //mod tsuge
        //char Text[5];
        char Text[8+2]; //mod tsuge
    } _X_UID;

    /** Xファイル読み込み時の次のトークン予約 */
    uint8_t token_next; //add tsuge

    //X File struct processing
    uint32_t _MaxKey; //Max animation key for a loaded animation set
    void ProcessFrameTransformMatrix(Frm::Bone* &pB);
    void ProcessBone(Frm::Bone* pBone, int dep);
    void ProcessMesh(int dep);
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
