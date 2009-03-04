#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <vector>
using namespace std;
//#include "GgafCommonHeader.h"
#include "ToolBox\IOModel_X.h"
#define DEBUG
//DECLARE_TRACE;
//TBuff* TBuff::_Instance = 0;


struct VERTEXX {
    float x, y, z; // ���_���W
    float nx, ny, nz; // �@��
    DWORD color; // ���_�̐F
    float tu, tv; // �e�N�X�`�����W
};

struct VTXINFO {
    UINT indexVertice;
    float r;
    Frm::Vector vn;
};

float getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2) {
    _TRACE_("v0=("<<v0.data[0]<<"."<<v0.data[1]<<","<<v0.data[2]<<")");
    _TRACE_("v1=("<<v1.data[0]<<"."<<v1.data[1]<<","<<v1.data[2]<<")");
    _TRACE_("v2=("<<v2.data[0]<<"."<<v2.data[1]<<","<<v2.data[2]<<")");
    Frm::Vector V0(v0.data[0], v0.data[1], v0.data[2]);
    Frm::Vector V1(v1.data[0], v1.data[1], v1.data[2]);
    Frm::Vector V2(v2.data[0], v2.data[1], v2.data[2]);
    Frm::Vector V = V2 - V1;
    Frm::Vector W = V0 - V1;
    //�x�N�g�� a b �̐����p�����߂�

//    V=(vx,vy,vz)=(bx-ax,by-ay,bz-az)
//    W=(wx,wy,wz)=(cx-ax,cy-ay,cz-az)
//    �ƂȂ�܂��B
//
//    �����V�AW�x�N�g�����Ȃ��p����
//    cos��=(V�AW�x�N�g���̓��ρj���iV�̑傫���j���iW�̑傫���j
//        =(vx*wx+vy*wy+vz*wz)
//         �����[�g(vx^2+vy^2+vz^2)�����[�g(wx^2+wy^2+wz^2)

    _TRACE_("V=("<<V.x<<"."<<V.y<<","<<V.z<<")");
    _TRACE_("W=("<<W.x<<"."<<W.y<<","<<W.z<<")");
    float DOT = V.Dot(W);
    _TRACE_("DOT="<<DOT);
    float LV = V.Abs();
    _TRACE_("LV="<<LV);
    float LW = W.Abs();
    _TRACE_("LW="<<LW);

    float cosV1 = DOT / LV / LW;
    if (cosV1 == 0) {
        return (float)3.14159265358979/2;
    } else {
        return cosV1;
    }

}

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
        //�ݒ�
        VERTEXX* paVtxBuffer_org = NEW VERTEXX[nVertices];

        for (int i = 0; i < nVertices; i++) {
            paVtxBuffer_org[i].x = (*mesh)->_Vertices[i].data[0];
            paVtxBuffer_org[i].y = (*mesh)->_Vertices[i].data[1];
            paVtxBuffer_org[i].z = (*mesh)->_Vertices[i].data[2];
            paVtxBuffer_org[i].nx = 0.0f;
            paVtxBuffer_org[i].ny = 0.0f;
            paVtxBuffer_org[i].nz = 0.0f;
            paVtxBuffer_org[i].color = D3DCOLOR_ARGB(255,255,255,255);
            paVtxBuffer_org[i].tu = 0.0f;
            paVtxBuffer_org[i].tv = 0.0f;
        }

        std::vector<VTXINFO> v_vtxInfo;


        unsigned short indexVertices[3];
        unsigned short indexNormals[3];
        float nx, ny, nz;
        for (int i = 0; i < nFaces; i++) {
            for (int j = 0; j < 3; j++) {
                indexVertices[j] = (*mesh)->_Faces[i].data[j];       //
                indexNormals[j] = (*mesh)->_FaceNormals[i].data[j];
            }

            VTXINFO vtxinfo0;
            vtxinfo0.indexVertice = indexVertices[0];
            vtxinfo0.r = getRadv1_v0v1v2(
                           (*mesh)->_Vertices[indexVertices[2]],
                           (*mesh)->_Vertices[indexVertices[0]],
                           (*mesh)->_Vertices[indexVertices[1]]
                        );
            vtxinfo0.vn.x = (*mesh)->_Normals[indexNormals[0]].x;
            vtxinfo0.vn.y = (*mesh)->_Normals[indexNormals[0]].y;
            vtxinfo0.vn.z = (*mesh)->_Normals[indexNormals[0]].z;
            v_vtxInfo.push_back(vtxinfo0);






            VTXINFO vtxinfo1;
            vtxinfo1.indexVertice = indexVertices[1];
            vtxinfo1.r = getRadv1_v0v1v2(
                           (*mesh)->_Vertices[indexVertices[0]],
                           (*mesh)->_Vertices[indexVertices[1]],
                           (*mesh)->_Vertices[indexVertices[2]]
                        );
            vtxinfo1.vn.x = (*mesh)->_Normals[indexNormals[1]].x;
            vtxinfo1.vn.y = (*mesh)->_Normals[indexNormals[1]].y;
            vtxinfo1.vn.z = (*mesh)->_Normals[indexNormals[1]].z;
            v_vtxInfo.push_back(vtxinfo1);

            VTXINFO vtxinfo2;
            vtxinfo2.indexVertice = indexVertices[2];
            vtxinfo2.r = getRadv1_v0v1v2(
                           (*mesh)->_Vertices[indexVertices[1]],
                           (*mesh)->_Vertices[indexVertices[2]],
                           (*mesh)->_Vertices[indexVertices[0]]
                        );
            vtxinfo2.vn.x = (*mesh)->_Normals[indexNormals[1]].x;
            vtxinfo2.vn.y = (*mesh)->_Normals[indexNormals[1]].y;
            vtxinfo2.vn.z = (*mesh)->_Normals[indexNormals[1]].z;
            v_vtxInfo.push_back(vtxinfo2);

            _TRACE_("iv0_iv1_iv2="<<vtxinfo0.indexVertice<<"��"<<vtxinfo1.indexVertice<<"��"<<vtxinfo2.indexVertice);
            _TRACE_("v0v1v2=("<<vtxinfo0.vn.x<<","<<vtxinfo0.vn.y<<","<<vtxinfo0.vn.z<<") ("<<vtxinfo1.vn.x<<","<<vtxinfo1.vn.y<<","<<vtxinfo1.vn.z<<") ("<<vtxinfo2.vn.x<<","<<vtxinfo2.vn.y<<","<<vtxinfo2.vn.z<<")");
            _TRACE_("R201="<<vtxinfo0.r);
            _TRACE_("R012="<<vtxinfo1.r);
            _TRACE_("R120="<<vtxinfo2.r);

//            for (int j = 0; j < 3; j++) {
//
//
//
//
//
//                nx = (*mesh)->_Normals[indexNormals[j]].x;
//                ny = (*mesh)->_Normals[indexNormals[j]].y;
//                nz = (*mesh)->_Normals[indexNormals[j]].z;
//                _TRACE_("i="<<i<<"/j="<<j<<"/indexNormals[j]="<<indexNormals[j]);
//                //���Z�����ω�����i�P�ʃx�N�g���ł͂Ȃ��Ȃ��Ă��܂�
//                paVtxBuffer_org[indexVertices[j]].nx += nx;
//                paVtxBuffer_org[indexVertices[j]].ny += ny;
//                paVtxBuffer_org[indexVertices[j]].nz += nz;
//
//
//                _TRACE_("i="<<i<<"/j="<<j<<"/indexVertices[j]="<<indexVertices[j]);
//                _TRACE_("nx="<<nx<<" paVtxBuffer_org["<<indexVertices[j]<<"].nx="<<paVtxBuffer_org[indexVertices[j]].nx);
//                _TRACE_("ny="<<ny<<" paVtxBuffer_org["<<indexVertices[j]<<"].ny="<<paVtxBuffer_org[indexVertices[j]].ny);
//                _TRACE_("nz="<<nz<<" paVtxBuffer_org["<<indexVertices[j]<<"].nz="<<paVtxBuffer_org[indexVertices[j]].nz);
//            }
//
        }

        for (UINT i = 0; i < v_vtxInfo.size(); i++) {
            _TRACE_("["<<i<<"]= vindex="<<v_vtxInfo[i].indexVertice<<":"<<v_vtxInfo[i].r<<"("<< v_vtxInfo[i].vn.x << "\t, " << v_vtxInfo[i].vn.y << "\t, " << v_vtxInfo[i].vn.z << ")");
        }

        for (UINT i = 0; i < nVertices; i++) {
            float radSum_Vtx = 0;
            for (UINT j = 0; j < v_vtxInfo.size(); j++) {
                if (v_vtxInfo[j].indexVertice == i) {
                    radSum_Vtx += v_vtxInfo[j].r;
                }
            }
            for (UINT j = 0; j < v_vtxInfo.size(); j++) {
                if (v_vtxInfo[j].indexVertice == i) {
                    float rate = v_vtxInfo[j].r / radSum_Vtx;
                    paVtxBuffer_org[i].nx += v_vtxInfo[j].vn.x * rate;
                    paVtxBuffer_org[i].ny += v_vtxInfo[j].vn.y * rate;
                    paVtxBuffer_org[i].nz += v_vtxInfo[j].vn.z * rate;
                }
            }
        }

        _TRACE_("�@�����K���O�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[");
        for (int i = 0; i < nVertices; i++) {
            _TRACE_("["<<i<<"]=" << paVtxBuffer_org[i].x << "\t, " << paVtxBuffer_org[i].y << "\t, " << paVtxBuffer_org[i].z << "\t, " << paVtxBuffer_org[i].nx << "\t, " << paVtxBuffer_org[i].ny << "\t, " << paVtxBuffer_org[i].nz << "\t, " << paVtxBuffer_org[i].tu << "\t, " << paVtxBuffer_org[i].tv);
        }


        D3DXVECTOR3 vec;
        for (int i = 0; i < nVertices; i++) {
            vec.x = paVtxBuffer_org[i].nx;
            vec.y = paVtxBuffer_org[i].ny;
            vec.z = paVtxBuffer_org[i].nz;
            if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
                continue;
            } else {
                D3DXVec3Normalize( &vec, &vec);
                paVtxBuffer_org[i].nx = vec.x;
                paVtxBuffer_org[i].ny = vec.y;
                paVtxBuffer_org[i].nz = vec.z;
            }
        }

//       for (UINT i = 0; i < nVertices; i++) {
//            if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
//                paVtxBuffer_org[i].nx = 0;
//                paVtxBuffer_org[i].ny = 0;
//                paVtxBuffer_org[i].nz = 0;
//            } else {
//                D3DXVec3Normalize( &vec, &vec);
//                paVtxBuffer_org[i].nx = vec.x;
//                paVtxBuffer_org[i].ny = vec.y;
//                paVtxBuffer_org[i].nz = vec.z;
//            }
//       }


        _TRACE_("�@�����K����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[");
        for (int i = 0; i < nVertices; i++) {
            _TRACE_("["<<i<<"]=" << paVtxBuffer_org[i].x << "\t, " << paVtxBuffer_org[i].y << "\t, " << paVtxBuffer_org[i].z << "\t, " << paVtxBuffer_org[i].nx << "\t, " << paVtxBuffer_org[i].ny << "\t, " << paVtxBuffer_org[i].nz << "\t, " << paVtxBuffer_org[i].tu << "\t, " << paVtxBuffer_org[i].tv);
        }


        delete[] paVtxBuffer_org;
        meshno++;
    }
















//    Frm::Mesh* pMesh = CurrentModel->_Meshes.front();

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





