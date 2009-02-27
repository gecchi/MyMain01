#include <iostream>
using namespace std;
//#include "GgafCommonHeader.h"
#include "ToolBox\IOModel_X.h"
#define DEBUG
//DECLARE_TRACE;
//TBuff* TBuff::_Instance = 0;

int main(int argc, char *argv[]) {
//    TBuff* _Buff;


    ToolBox::IO_Model_X IOX;
    Frm::Model3D MyModel;
    Frm::Model3D* CurrentModel;


    //START_TRACE; //readies the debug file
//    _Buff = TBuff::GetInstance();
//    GetCurrentDirectoryA(512, _Buff->_TraceName);
//    memcpy(&_Buff->_TraceName[strlen(_Buff->_TraceName)], "\\Debug\\Trace.txt\0", 17);
//    ToolBox::RemTrace();




    //std::string temp = "MYCUBE001_no.X";
    std::string temp = "ebi2.X";
    cout << "temp=" << temp << endl;
    bool Running = false;
    CurrentModel = &MyModel;
    Running = IOX.Load(temp, CurrentModel);
    MyModel.ConcatenateMeshes();

    int meshno = 0;
    for (std::list<Frm::Mesh*>::iterator mesh = MyModel._Meshes.begin(); mesh != MyModel._Meshes.end(); mesh++) {
        cout << "----------- Mesh�ԍ�["<< meshno <<"] ---------------" << endl;

        //���_
        int  nVertices = (*mesh)->_nVertices;
        cout <<  "���_���F" << nVertices << endl;
        for (int i = 0; i < nVertices; i++) {
            cout <<  "���_�ԍ�["<<i<<"] = (" << (*mesh)->_Vertices[i].data[0] << ", " <<
                                               (*mesh)->_Vertices[i].data[1] << ", " <<
                                               (*mesh)->_Vertices[i].data[2] << ")" << endl;
        }
        //���_�C���f�b�N�X�o�b�t�@
        int  nFaces = (*mesh)->_nFaces;
        cout <<  "���_�C���f�b�N�X��(�ʂ̐�) �F" << nFaces << endl;
        for (int i = 0; i < nFaces; i++) {
            cout <<  "��["<<i<<"]�̒��_�ԍ� = " << (*mesh)->_Faces[i].data[0] << " -> " <<
                                                 (*mesh)->_Faces[i].data[1] << " -> " <<
                                                 (*mesh)->_Faces[i].data[2] << endl;
        }
        //�@��
        int  normals_num = (*mesh)->_nNormals;
        cout <<  "�@�����F" << normals_num << endl;
        for (int i = 0; i < normals_num; i++) {
            cout << "�@���ԍ�["<<i<<"] = (" << (*mesh)->_Normals[i].x << ", " <<
                                              (*mesh)->_Normals[i].y << ", " <<
                                              (*mesh)->_Normals[i].z << ")" << endl;
        }
        //�@���C���f�b�N�X
        cout <<  "�@���C���f�b�N�X��(���ʂ̐�)�F" << nFaces << endl;
        for (int i = 0; i < nFaces; i++) {
            cout <<  "��["<<i<<"]�̖@���ԍ� = " << (*mesh)->_FaceNormals[i].data[0] << ", " <<
                                                 (*mesh)->_FaceNormals[i].data[1] << ", " <<
                                                 (*mesh)->_FaceNormals[i].data[2] << "" << endl;
        }

        //UV
        int  nTextureCoords = (*mesh)->_nTextureCoords;
        cout <<  "UV���F" << nTextureCoords << endl;
        for (int i = 0; i < nTextureCoords; i++) {
            cout <<  "UV["<<i<<"] = (" << (*mesh)->_TextureCoords[i].data[0] << ", " <<
                                          (*mesh)->_TextureCoords[i].data[1] << ")" << endl;
        }

        //�܂Ă肠��
        int  nMaterials = (*mesh)->_nMaterials;
        cout <<  "�}�e���A����ސ� �F" << nMaterials << endl;
        for (int i = 0; i <nFaces; i++) {
            cout << "��["<<i<<"]�̃}�e���A���ԍ� = " << (*mesh)->_FaceMaterials[i] << endl;
        }
        int materialno = 0;
        for (std::list<Frm::Material*>::iterator material = (*mesh)->_Materials.begin(); material != (*mesh)->_Materials.end(); material++) {
            cout << "    --- �}�e���A���ԍ�["<<materialno<<"]�̒�` --->" << endl;
            cout << "    ��`�� = "<< (*material)->_Name << endl;
            cout << "    FaceColor(R,G,B,A) = (" << (*material)->_FaceColor.data[0] << ", " <<
                                                    (*material)->_FaceColor.data[1] << ", " <<
                                                    (*material)->_FaceColor.data[2] << ", " <<
                                                    (*material)->_FaceColor.data[3] << ")" << endl;
            cout << "    power = " << (*material)->_power << endl;
            cout << "    SpecularColor(R,G,B) = (" << (*material)->_SpecularColor.data[0] << ", " <<
                                                      (*material)->_SpecularColor.data[1] << ", " <<
                                                      (*material)->_SpecularColor.data[2] << ")" << endl;
            cout << "    EmissiveColor(R,G,B) = (" << (*material)->_EmissiveColor.data[0] << ", " <<
                                                      (*material)->_EmissiveColor.data[1] << ", " <<
                                                      (*material)->_EmissiveColor.data[2] << ")" << endl;
            cout << "    TextID = " << (*material)->_TextID << endl;
            cout << "    �e�N�X�`���t�@�C�� = " << (*material)->_TextureName << endl;
            cout << "    <-------------------------------------------" << endl;
            materialno++;
        }
        meshno++;
    }

    Frm::Mesh* pMesh = CurrentModel->_Meshes.front();

    //���_
//    int  nVertices = pMesh->_nVertices;
//    cout <<  "���_���F" << nVertices << endl;
//    for (int i = 0; i < nVertices; i++) {
//        cout <<  "���_�ԍ�["<<i<<"] = " << pMesh->_Vertices[i].data[0] <<"," << pMesh->_Vertices[i].data[1] << "," << pMesh->_Vertices[i].data[2] << endl;
//    }
//    //���_�o�b�t�@
//    int  nFaces = pMesh->_nFaces;
//    cout <<  "���_�C���f�b�N�X��(�ʂ̐�) �F" << nFaces << endl;
//    for (int i = 0; i < nFaces; i++) {
//        cout <<  "��["<<i<<"]�̒��_�ԍ� = " << pMesh->_Faces[i].data[0] <<"," << pMesh->_Faces[i].data[1] << "," << pMesh->_Faces[i].data[2] << endl;
//    }
//    //�@��
//    int  normals_num = pMesh->_nNormals;
//    cout <<  "�@�����F" << normals_num << endl;
//    for (int i = 0; i < normals_num; i++) {
//        cout << "�@���ԍ�["<<i<<"] = " << pMesh->_Normals[i].x <<"," << pMesh->_Normals[i].y << "," << pMesh->_Normals[i].z << endl;
//    }
//    //�@���C���f�b�N�X
//    cout <<  "�@���C���f�b�N�X��(���ʂ̐�)�F" << nFaces << endl;
//    for (int i = 0; i < nFaces; i++) {
//        cout <<  "��["<<i<<"]�̖@���ԍ�; " << pMesh->_FaceNormals[i].data[0] <<"," << pMesh->_FaceNormals[i].data[1] << "," << pMesh->_FaceNormals[i].data[2] << endl;
//    }
//
//    //�܂Ă肠��
//    int  nMaterials = pMesh->_nMaterials;
//    cout <<  "�}�e���A����ސ� �F" << nFaces << endl;
//    for (int i = 0; i <nFacess; i++) {
//        cout <<  "��["<<i<<"]�̃}�e���A���ԍ� = " << pMesh->_FaceMaterials[i] << endl;
//    }
//
//    for (std::list<Frm::Mesh*>::iterator i = _Meshes.begin(); i != _Meshes.end(); i++) {
//        cout <<  "--- �}�e���A���ԍ�["<<i<<"]�̒�` ---" << endl;
//        for (std::list<Frm::Material*>::iterator j = (*i)->_Materials.begin(); j != (*i)->_Materials.end(); j++) {
//
//            temp = (*j)->_TextureName;
//            cout << "temp2=" << temp << endl;
//            //(*j)->_TextID = SampleScreen.SetTextureID(temp);
//        }
//    }
//


//    Frm::Vertex* _SkinnedVertices;
//    Frm::Model3D* _Model;
//    Frm::AnimationSet* _cAnimationSet;

    //END_TRACE;
//    delete _Buff;
    return 0;
}
