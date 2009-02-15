// 固定アニメーションテストサンプルプログラム

#include <iostream>
using namespace std;

#include "ToolBox\IOModel_X.h"
#define DEBUG

DECLARE_TRACE;

ToolBox::IO_Model_X IOX;
Frm::Model3D MyModel;
Frm::Model3D* CurrentModel;

int main(int argc, char *argv[]) {
    START_TRACE; //readies the debug file

    std::string temp = "MYCUBE001_no.X";
    cout << "temp=" << temp << endl;
    bool Running = false;
    CurrentModel = &MyModel;
    Running = IOX.Load(temp, CurrentModel);
    MyModel.ConcatenateMeshes();
    for (std::list<Frm::Mesh*>::iterator i = MyModel._Meshes.begin(); i != MyModel._Meshes.end(); i++) {
        for (std::list<Frm::Material*>::iterator j = (*i)->_Materials.begin(); j != (*i)->_Materials.end(); j++) {
            temp = (*j)->_TextureName;
            cout << "temp2=" << temp << endl;
            //(*j)->_TextID = SampleScreen.SetTextureID(temp);
        }
    }

    Frm::Mesh* _Mesh = CurrentModel->_Meshes.front();


//    Frm::Vertex* _SkinnedVertices;
//    Frm::Model3D* _Model;
//    Frm::AnimationSet* _cAnimationSet;

    END_TRACE;
    return 0;
}
