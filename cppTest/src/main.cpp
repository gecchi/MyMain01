// 固定アニメーションテストサンプルプログラム


#include "ToolBox\IOModel_X.h"



    ToolBox::IO_Model_X IOX;
    Frm::Model3D MyModel;
    Frm::Model3D* CurrentModel;

int main(int argc,char *argv[]) {
    //START_TRACE; //readies the debug file


    std::string temp = "cube4.x";



    bool Running = false;
    CurrentModel = &MyModel;
    Running = IOX.Load(temp, CurrentModel);

    return 0;
}
