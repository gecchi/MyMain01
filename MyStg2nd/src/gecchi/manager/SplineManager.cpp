#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

SplineManager::SplineManager(const char* prm_manager_name) :
    GgafResourceManager<SplineSource> (prm_manager_name) {
}

SplineSource* SplineManager::processCreateResource(char* prm_idstr, void* prm_p) {

    SplineSource* pResource = NEW SplineSource(prm_idstr);

//
//    GgafDx9SplineProgram* pResource = NULL;
//    GgafDx9GeometricActor* pActor = (GgafDx9GeometricActor*)prm_p;
//
//
//    string data_filename = STG_PROPERTY(DIR_SPLINE_DATA) + string(prm_idstr) + ".spl";
//    ifstream ifs(data_filename.c_str());
//    if (ifs.fail()) {
//        throwGgafCriticalException("SplineManager::processCreateResource "<<prm_idstr<<" が開けません");
//    }
//
//    string line;
//    double p[1000][3];
//    double accuracy = 0.0;
//    frame spent_frame = 0;
//    angvelo angveloRzRyMv = 0;
//    string classname;
//    int n = 0;
//    while( getline(ifs,line) ) {
//        if ( line.size() == 0 ) continue;
//        if ( line.c_str()[0] == '#' ) continue;
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
//        } else if ( line == "[POINT]") {
//
//            while( getline(ifs,line) ) {
//                if ( line.size() == 0 ) break;
//                if ( line.c_str()[0] == '#' ) continue;
//                istringstream iss(line);
//                iss >> p[n][0];
//                iss >> p[n][1];
//                iss >> p[n][2];
//                n++;
//            }
//        }
//        for (int i = 0; i < n; i++) {
//            //X
//            p[i][0] = p[i][0] * MyShip::_lim_front;
//            //Y
//            p[i][1] = p[i][1] * MyShip::_lim_top;
//            //Z
//            p[i][2] = p[i][2] * MyShip::_lim_zleft;
//
//        }
//
//        if ( classname == "GgafDx9FixedFrameSplineProgram") {
//            pResource = NEW GgafDx9FixedFrameSplineProgram(pActor, p, n, accuracy, spent_frame, angveloRzRyMv);
//            _TRACE_("pResource = NEW GgafDx9FixedFrameSplineProgram("<<pActor->getName()<<", p, "<<n<<", "<<accuracy<<", "<<spent_frame<<", "<<angveloRzRyMv<<");");
//        } else if ( classname == "GgafDx9FixedVelocitySplineProgram") {
//            pResource = NEW GgafDx9FixedVelocitySplineProgram(pActor, p, n, accuracy, angveloRzRyMv);
//            _TRACE_("pResource = NEW GgafDx9FixedVelocitySplineProgram("<<pActor->getName()<<", p, "<<n<<", "<<accuracy<<", "<<angveloRzRyMv<<");");
//        }
//
//        for (int i = 0; i < n; i++) {
//            cout << "X,Y,Z ["<<i<<"]="<<p[i][0]<<","<<p[i][1]<<","<<p[i][2] <<  endl;
//        }
//    }
////
////
////
////
////
////    if (GgafUtil::strcmp_ascii("SpCon_Pallas01", prm_idstr) == 0) {
////        string data_filename = STG_PROPERTY(DIR_SCENE_DATA) + string(prm_idstr) + ".spl";
////        ifstream ifs(data_filename.c_str());
////        if (ifs.fail()) {
////            throwGgafCriticalException("SplineManager::processCreateResource "<<prm_idstr<<" が開けません");
////        }
////
////        string line;
////        double point[1000][3];
////        int bp = 0;
////        while( getline(ifs,line) ) {
////
////            if ( line == "[Vertecs]") {
////                while( getline(ifs,line) ) {
////                    if ( line.size() == 0 )  { break; }
////                    iss >> point[bp][0];
////                    iss >> point[bp][1];
////                    iss >> point[bp][2];
////                }
////            } else if (line == "[Class]") {
////
////            }
////            iss >> name;
////            iss >> x;
////            iss >> y;
////
////
////        }
////
////
////
////        ifs >> _loop_num;
////
////
////        ifs >> _area_len >>
////               _area_height >>
////               _area_width;
////        if (ifs.fail()) {
////            throwGgafCriticalException("WalledSectionScene::WalledSectionScene "<<prm_data_filename<<" フォーマットエラーその１");
////        }
////        int r_data;
////        _paWallInfoLen = NEW int[_area_len];
////        for (int i = 0; i < _area_len; i++) {
////            ifs >> r_data;
////            _paWallInfoLen[i] = r_data;
////            if (ifs.fail()) {
////                throwGgafCriticalException("WalledSectionScene::WalledSectionScene "<<prm_data_filename<<" フォーマットエラーその２ i="<<i<<" _area_len="<<_area_len);
////            }
////        }
////
////        _papaWallInfo = NEW WallInfo*[_area_len];
////        for (int i = 0; i < _area_len; i++) {
////            _TRACE_("WalledSectionScene read..."<<i);
////            _papaWallInfo[i] = NEW WallInfo[_paWallInfoLen[i]];
////            for (int j = 0; j < _paWallInfoLen[i]; j++) {
////                ifs >> _papaWallInfo[i][j]._Y >>
////                       _papaWallInfo[i][j]._Z >>
////                       _papaWallInfo[i][j]._wall_draw_face >>
////                       _papaWallInfo[i][j]._aColliBoxStretch[0] >>
////                       _papaWallInfo[i][j]._aColliBoxStretch[1] >>
////                       _papaWallInfo[i][j]._aColliBoxStretch[2] >>
////                       _papaWallInfo[i][j]._aColliBoxStretch[3] >>
////                       _papaWallInfo[i][j]._aColliBoxStretch[4] >>
////                       _papaWallInfo[i][j]._aColliBoxStretch[5];
////                if (ifs.fail()) {
////                    throwGgafCriticalException("WalledSectionScene::WalledSectionScene "<<prm_data_filename<<" フォーマットエラーその３ i="<<i<<"/j="<<j<<"/_area_len="<<_area_len<<"/_paWallInfoLen[i]="<<_paWallInfoLen[i]);
////                }
////            }
////
////        }
////        ifs.close();
////
////
////
////
////
////
////
////
////
////
////        double p[][3] = { //     X  ,       Y ,       Z
////                          { -1.724577 ,  0.000000 ,  0.000000 },
////                          { -0.964337 , -0.088378 , -0.344892 },
////                          { -0.501305 , -0.055518 , -0.298879 },
////                          { -0.179336 , -0.031628 , -0.240141 },
////                          {  0.123544 , -0.016126 , -0.165195 },
////                          {  0.362343 ,  0.000000 ,  0.000000 },
////                          {  0.545634 ,  0.038709 ,  0.176104 },
////                          {  0.704048 ,  0.173192 ,  0.372772 },
////                          {  0.864812 ,  0.444651 ,  0.516556 },
////                          {  1.055714 ,  0.626849 ,  0.569336 },
////                          {  1.246407 ,  0.655359 ,  0.547772 },
////                          {  1.365876 ,  0.590994 ,  0.453279 },
////                          {  1.388259 ,  0.465998 ,  0.332581 },
////                          {  1.362117 ,  0.328636 ,  0.211183 },
////                          {  1.242692 ,  0.226675 ,  0.087900 },
////                          {  1.064405 ,  0.202917 ,  0.000000 },
////                          {  0.920421 ,  0.202917 ,  0.000000 }
////        };
////        for (int i = 0; i < 17; i++) {
////            //X
////            p[i][0] = p[i][0] * MyShip::_lim_front;
////            //Y
////            p[i][1] = p[i][1] * MyShip::_lim_top;
////            //Z
////            p[i][2] = p[i][2] * MyShip::_lim_zleft;
////
////        }
////        pResource = NEW GgafDx9SplineProgram(NULL); //粒度 0.2
////    }

    return pResource;
}

//MyShip::_lim_top     = GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT)*5*LEN_UNIT / 2;      //上下は画面高さの大体５画面分
//MyShip::_lim_bottom  = -(GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT)*5*LEN_UNIT / 2);
//MyShip::_lim_front   = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)*4*LEN_UNIT / 2 ;    //前後は画面幅の大体４画面分
//MyShip::_lim_behaind = -(GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)*0.5*LEN_UNIT / 2 );
//MyShip::_lim_zleft   = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)*5*LEN_UNIT / 2;       //奥手前は画面幅の大体５画面分
//MyShip::_lim_zright  = -(GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)*5*LEN_UNIT / 2);
//GgafDx9Universe::_X_goneLeft   = GgafDx9Camera::_X_ScreenLeft - 3000*LEN_UNIT; //最大3000pxのオブジェクトまで想定
//GgafDx9Universe::_X_goneRight  = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Y_goneTop    = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Y_goneBottom = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Z_goneFar   = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Z_goneNear  = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);

GgafResourceConnection<SplineSource>* SplineManager::processCreateConnection(char* prm_idstr, SplineSource* prm_pResource) {
    TRACE3(" SplineManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    SplineConnection* pConnection = NEW SplineConnection(prm_idstr, prm_pResource);
    TRACE3(" SplineManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
