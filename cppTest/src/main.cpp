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
        cout << "----------- Mesh番号["<< meshno <<"] ---------------" << endl;

        //頂点
        int  nVertices = (*mesh)->_nVertices;
        cout <<  "頂点数：" << nVertices << endl;
        for (int i = 0; i < nVertices; i++) {
            cout <<  "頂点番号["<<i<<"] = (" << (*mesh)->_Vertices[i].data[0] << ", " <<
                                               (*mesh)->_Vertices[i].data[1] << ", " <<
                                               (*mesh)->_Vertices[i].data[2] << ")" << endl;
        }
        //頂点インデックスバッファ
        int  nFaces = (*mesh)->_nFaces;
        cout <<  "頂点インデックス数(面の数) ：" << nFaces << endl;
        for (int i = 0; i < nFaces; i++) {
            cout <<  "面["<<i<<"]の頂点番号 = " << (*mesh)->_Faces[i].data[0] << " -> " <<
                                                 (*mesh)->_Faces[i].data[1] << " -> " <<
                                                 (*mesh)->_Faces[i].data[2] << endl;
        }
        //法線
        int  normals_num = (*mesh)->_nNormals;
        cout <<  "法線数：" << normals_num << endl;
        for (int i = 0; i < normals_num; i++) {
            cout << "法線番号["<<i<<"] = (" << (*mesh)->_Normals[i].x << ", " <<
                                              (*mesh)->_Normals[i].y << ", " <<
                                              (*mesh)->_Normals[i].z << ")" << endl;
        }
        //法線インデックス
        cout <<  "法線インデックス数(＝面の数)：" << nFaces << endl;
        for (int i = 0; i < nFaces; i++) {
            cout <<  "面["<<i<<"]の法線番号 = " << (*mesh)->_FaceNormals[i].data[0] << ", " <<
                                                 (*mesh)->_FaceNormals[i].data[1] << ", " <<
                                                 (*mesh)->_FaceNormals[i].data[2] << "" << endl;
        }

        //UV
        int  nTextureCoords = (*mesh)->_nTextureCoords;
        cout <<  "UV数：" << nTextureCoords << endl;
        for (int i = 0; i < nTextureCoords; i++) {
            cout <<  "UV["<<i<<"] = (" << (*mesh)->_TextureCoords[i].data[0] << ", " <<
                                          (*mesh)->_TextureCoords[i].data[1] << ")" << endl;
        }

        //まてりある
        int  nMaterials = (*mesh)->_nMaterials;
        cout <<  "マテリアル種類数 ：" << nMaterials << endl;
        for (int i = 0; i <nFaces; i++) {
            cout << "面["<<i<<"]のマテリアル番号 = " << (*mesh)->_FaceMaterials[i] << endl;
        }
        int materialno = 0;
        for (std::list<Frm::Material*>::iterator material = (*mesh)->_Materials.begin(); material != (*mesh)->_Materials.end(); material++) {
            cout << "    --- マテリアル番号["<<materialno<<"]の定義 --->" << endl;
            cout << "    定義名 = "<< (*material)->_Name << endl;
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
            cout << "    テクスチャファイル = " << (*material)->_TextureName << endl;
            cout << "    <-------------------------------------------" << endl;
            materialno++;
        }
        meshno++;
    }

    Frm::Mesh* pMesh = CurrentModel->_Meshes.front();

    //頂点
//    int  nVertices = pMesh->_nVertices;
//    cout <<  "頂点数：" << nVertices << endl;
//    for (int i = 0; i < nVertices; i++) {
//        cout <<  "頂点番号["<<i<<"] = " << pMesh->_Vertices[i].data[0] <<"," << pMesh->_Vertices[i].data[1] << "," << pMesh->_Vertices[i].data[2] << endl;
//    }
//    //頂点バッファ
//    int  nFaces = pMesh->_nFaces;
//    cout <<  "頂点インデックス数(面の数) ：" << nFaces << endl;
//    for (int i = 0; i < nFaces; i++) {
//        cout <<  "面["<<i<<"]の頂点番号 = " << pMesh->_Faces[i].data[0] <<"," << pMesh->_Faces[i].data[1] << "," << pMesh->_Faces[i].data[2] << endl;
//    }
//    //法線
//    int  normals_num = pMesh->_nNormals;
//    cout <<  "法線数：" << normals_num << endl;
//    for (int i = 0; i < normals_num; i++) {
//        cout << "法線番号["<<i<<"] = " << pMesh->_Normals[i].x <<"," << pMesh->_Normals[i].y << "," << pMesh->_Normals[i].z << endl;
//    }
//    //法線インデックス
//    cout <<  "法線インデックス数(＝面の数)：" << nFaces << endl;
//    for (int i = 0; i < nFaces; i++) {
//        cout <<  "面["<<i<<"]の法線番号; " << pMesh->_FaceNormals[i].data[0] <<"," << pMesh->_FaceNormals[i].data[1] << "," << pMesh->_FaceNormals[i].data[2] << endl;
//    }
//
//    //まてりある
//    int  nMaterials = pMesh->_nMaterials;
//    cout <<  "マテリアル種類数 ：" << nFaces << endl;
//    for (int i = 0; i <nFacess; i++) {
//        cout <<  "面["<<i<<"]のマテリアル番号 = " << pMesh->_FaceMaterials[i] << endl;
//    }
//
//    for (std::list<Frm::Mesh*>::iterator i = _Meshes.begin(); i != _Meshes.end(); i++) {
//        cout <<  "--- マテリアル番号["<<i<<"]の定義 ---" << endl;
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
