#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Spline3DManager::Spline3DManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Core::GgafDx9Spline3D> (prm_manager_name) {
}

GgafDx9Spline3D* Spline3DManager::processCreateResource(char* prm_idstr, void* prm_p) {
    GgafDx9Spline3D* pResource = NULL;



    string data_filename = STG_PROPERTY(DIR_SPLINE_DATA) + string(prm_idstr) + ".spl";
    ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("SplineProgramManager::processCreateResource "<<prm_idstr<<" ���J���܂���");
    }

    string line;
    double p[1000][3];
    double accuracy = 0.0;
//    frame spent_frame = 0;
//    angvelo angveloRzRyMv = 0;
//    string classname;
    int n = 0;
    while( getline(ifs,line) ) {
        if ( line.size() == 0 ) continue;
        if ( line.c_str()[0] == '#' ) continue;
//        if ( line == "[CLASS]") {
//            getline(ifs,line);
//            istringstream iss(line);
//            iss >> classname;
//            if ( classname == "GgafDx9FixedFrameSplineProgram") {
//                iss >> accuracy;
//                iss >> spent_frame;
//                iss >> angveloRzRyMv;
//            } else if ( classname == "GgafDx9FixedVelocitySplineProgram") {
//                iss >> accuracy;
//                iss >> angveloRzRyMv;
//            }
//        } else
        if ( line == "[POINT]") {
            while( getline(ifs,line) ) {
                if ( line.size() == 0 ) break;
                if ( line.c_str()[0] == '#' ) continue;
                istringstream iss(line);
                iss >> p[n][0];
                iss >> p[n][1];
                iss >> p[n][2];
                n++;
            }
        } else if ( line == "[ACCURACY]") {
            while( getline(ifs,line) ) {
                if ( line.size() == 0 ) break;
                if ( line.c_str()[0] == '#' ) continue;
                istringstream iss(line);
                iss >> accuracy;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        //X
        p[i][0] = p[i][0] * MyShip::_lim_front;
        //Y
        p[i][1] = p[i][1] * MyShip::_lim_top;
        //Z
        p[i][2] = p[i][2] * MyShip::_lim_zleft;

    }
//
//        if ( classname == "GgafDx9FixedFrameSplineProgram") {
//            pResource = NEW GgafDx9FixedFrameSplineProgram(pActor, p, n, accuracy, spent_frame, angveloRzRyMv);
//            _TRACE_("pResource = NEW GgafDx9FixedFrameSplineProgram("<<pActor->getName()<<", p, "<<n<<", "<<accuracy<<", "<<spent_frame<<", "<<angveloRzRyMv<<");");
//        } else if ( classname == "GgafDx9FixedVelocitySplineProgram") {
//            pResource = NEW GgafDx9FixedVelocitySplineProgram(pActor, p, n, accuracy, angveloRzRyMv);
//            _TRACE_("pResource = NEW GgafDx9FixedVelocitySplineProgram("<<pActor->getName()<<", p, "<<n<<", "<<accuracy<<", "<<angveloRzRyMv<<");");
//        }

    for (int i = 0; i < n; i++) {
        cout << "X,Y,Z ["<<i<<"]="<<p[i][0]<<","<<p[i][1]<<","<<p[i][2] <<  endl;
    }

    pResource = NEW GgafDx9Spline3D(p, n, accuracy);//���x 0.2


//    if (GgafUtil::strcmp_ascii("SpCon_001", prm_idstr) == 0) {
//        double p[][3] = { //        X ,        Y ,       Z
//                          { -1024000 ,  -300000 ,  680000 },
//                          {  -800000 ,   300000 ,  480000 },
//                          {  -200000 ,  -300000 ,  200000 },
//                          {   200000 ,   300000 ,  100000 },
//                          {   400000 ,        0 ,       0 },
//                          {   300000 ,        0 ,       0 },
//                          {   200000 ,   200000 ,       0 },
//                          {   100000 ,        0 ,  200000 },
//                          {        0 ,  -200000 ,       0 },
//                          {  -100000 ,        0 , -200000 },
//                          {   300000 ,        0 ,       0 },
//                          {        0 ,   300000 ,       0 },
//                          {        0 ,        0 ,  300000 },
//                          {  -300000 ,        0 ,       0 },
//                          {        0 ,  -300000 ,       0 },
//                          {        0 ,        0 , -300000 },
//                          {  -800000 ,        0 ,       0 }
//                        };
//        pResource = NEW GgafDx9Spline3D(p, 17, 0.2);//���x 0.2
//    }
//
//    if (GgafUtil::strcmp_ascii("SpCon_002_01", prm_idstr) == 0) {
//        //�������
//        double p[][3] = { //           X  ,                       Y ,                         Z
//           { MyShip::_lim_behaind - 500000.0 ,                    0.0 ,  MyShip::_lim_zleft * 0.8 },
//           {                       3000000 , MyShip::_lim_top * 0.2 ,                       0.0 },
//           {                       3000000 , MyShip::_lim_top * 0.5 , MyShip::_lim_zright * 0.3 },
//           {                       3000000 , MyShip::_lim_top * 1.0 ,                       0.0 },
//           {                       3000000 ,                    0.0 ,                       0.0 }
//        };
//        pResource = NEW GgafDx9Spline3D(p, 5, 0.2); //���x 0.2
//    }
//
//    if (GgafUtil::strcmp_ascii("SpCon_002_02", prm_idstr) == 0) {
//        //�������
//        double p[][3] = { //           X  ,                          Y ,                         Z
//           { MyShip::_lim_behaind - 500000.0 ,                       0.0 , MyShip::_lim_zright * 0.8 },
//           {      MyShip::_lim_front * 1.5 , MyShip::_lim_bottom * 0.2 ,                       0.0 },
//           {      MyShip::_lim_front * 2.5 , MyShip::_lim_bottom * 0.5 ,  MyShip::_lim_zleft * 0.3 },
//           {      MyShip::_lim_front * 2.2 , MyShip::_lim_bottom * 1.0 ,                       0.0 },
//           {      MyShip::_lim_front * 2.0 ,                       0.0 ,                       0.0 }
//        };
//        pResource = NEW GgafDx9Spline3D(p, 5, 0.2); //���x 0.2
//    }
//
//    if (GgafUtil::strcmp_ascii("SpCon_HAN", prm_idstr) == 0) {
//        double p[][3] = { //     X  ,       Y ,       Z
//                          {  200000 ,     0.0 ,     0.0 },
//                          {  250000 ,  200000 ,     0.0 },
//                          {  300000 ,     0.0 ,  200000 },
//                          {  350000 , -200000 ,     0.0 },
//                          {  400000 ,     0.0 , -200000 },
//                          {  450000 ,  200000 ,     0.0 },
//                          {  500000 ,     0.0 ,  200000 },
//                          {  550000 , -200000 ,     0.0 },
//                          {  600000 ,     0.0 , -200000 },
//                          {  750000 ,  200000 ,     0.0 },
//                          {  800000 ,     0.0 ,  200000 },
//                          {  850000 , -200000 ,     0.0 },
//                          {  900000 ,     0.0 , -200000 },
//                          {  950000 ,  200000 ,     0.0 },
//                          { 1000000 ,     0.0 ,  200000 },
//                          { 1050000 , -200000 ,     0.0 },
//                          { 1200000 ,     0.0 , -200000 },
//                          {     0.0 ,     0.0 ,     0.0 }
//        };
//        pResource = NEW GgafDx9Spline3D(p, 18, 0.2); //���x 0.2
//    }
//
//    if (GgafUtil::strcmp_ascii("SpCon_Pallas01", prm_idstr) == 0) {
//        double p[][3] = { //     X  ,       Y ,       Z
//                          { -1.724577 ,  0.000000 ,  0.000000 },
//                          { -0.964337 , -0.088378 , -0.344892 },
//                          { -0.501305 , -0.055518 , -0.298879 },
//                          { -0.179336 , -0.031628 , -0.240141 },
//                          {  0.123544 , -0.016126 , -0.165195 },
//                          {  0.362343 ,  0.000000 ,  0.000000 },
//                          {  0.545634 ,  0.038709 ,  0.176104 },
//                          {  0.704048 ,  0.173192 ,  0.372772 },
//                          {  0.864812 ,  0.444651 ,  0.516556 },
//                          {  1.055714 ,  0.626849 ,  0.569336 },
//                          {  1.246407 ,  0.655359 ,  0.547772 },
//                          {  1.365876 ,  0.590994 ,  0.453279 },
//                          {  1.388259 ,  0.465998 ,  0.332581 },
//                          {  1.362117 ,  0.328636 ,  0.211183 },
//                          {  1.242692 ,  0.226675 ,  0.087900 },
//                          {  1.064405 ,  0.202917 ,  0.000000 },
//                          {  0.920421 ,  0.202917 ,  0.000000 }
//        };
//        for (int i = 0; i < 17; i++) {
//            //X
//            p[i][0] = p[i][0] * MyShip::_lim_front;
//            //Y
//            p[i][1] = p[i][1] * MyShip::_lim_top;
//            //Z
//            p[i][2] = p[i][2] * MyShip::_lim_zleft;
//
//        }
//        pResource = NEW GgafDx9Spline3D(p, 17, 0.2); //���x 0.2
//    }

    return pResource;
}

//MyShip::_lim_top     = GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT)*5*LEN_UNIT / 2;      //�㉺�͉�ʍ����̑�̂T��ʕ�
//MyShip::_lim_bottom  = -(GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT)*5*LEN_UNIT / 2);
//MyShip::_lim_front   = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)*4*LEN_UNIT / 2 ;    //�O��͉�ʕ��̑�̂S��ʕ�
//MyShip::_lim_behaind = -(GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)*0.5*LEN_UNIT / 2 );
//MyShip::_lim_zleft   = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)*5*LEN_UNIT / 2;       //����O�͉�ʕ��̑�̂T��ʕ�
//MyShip::_lim_zright  = -(GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)*5*LEN_UNIT / 2);
//GgafDx9Universe::_X_goneLeft   = GgafDx9Camera::_X_ScreenLeft - 3000*LEN_UNIT; //�ő�3000px�̃I�u�W�F�N�g�܂őz��
//GgafDx9Universe::_X_goneRight  = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Y_goneTop    = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Y_goneBottom = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Z_goneFar   = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Z_goneNear  = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);

GgafResourceConnection<GgafDx9Core::GgafDx9Spline3D>* Spline3DManager::processCreateConnection(char* prm_idstr, GgafDx9Spline3D* prm_pResource) {
    TRACE3(" Spline3DManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    Spline3DConnection* pConnection = NEW Spline3DConnection(prm_idstr, prm_pResource);
    TRACE3(" Spline3DManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConnection;
}

