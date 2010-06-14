#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Spline3DManager::Spline3DManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Core::GgafDx9Spline3D> (prm_manager_name) {
}

GgafDx9Spline3D* Spline3DManager::processCreateResource(char* prm_idstr) {
    GgafDx9Spline3D* pResource = NULL;

    if (GgafUtil::strcmp_ascii("SpCon_001", prm_idstr) == 0) {
        double p[][3] = { //        X ,        Y ,       Z
                          { -1024000 ,  -300000 ,  680000 },
                          {  -800000 ,   300000 ,  480000 },
                          {  -200000 ,  -300000 ,  200000 },
                          {   200000 ,   300000 ,  100000 },
                          {   400000 ,        0 ,       0 },
                          {   300000 ,        0 ,       0 },
                          {   200000 ,   200000 ,       0 },
                          {   100000 ,        0 ,  200000 },
                          {        0 ,  -200000 ,       0 },
                          {  -100000 ,        0 , -200000 },
                          {   300000 ,        0 ,       0 },
                          {        0 ,   300000 ,       0 },
                          {        0 ,        0 ,  300000 },
                          {  -300000 ,        0 ,       0 },
                          {        0 ,  -300000 ,       0 },
                          {        0 ,        0 , -300000 },
                          {  -800000 ,        0 ,       0 }
                        };
        pResource = NEW GgafDx9Spline3D(p, 17, 0.2);//粒度 0.2
    }

    if (GgafUtil::strcmp_ascii("SpCon_002_01", prm_idstr) == 0) {
        //後方から
        double p[][3] = { //           X  ,                       Y ,                         Z
           { MyShip::_lim_behaind - 500000 ,                    0.0 ,  MyShip::_lim_zleft * 0.8 },
           {                       3000000 , MyShip::_lim_top * 0.2 ,                       0.0 },
           {                       3000000 , MyShip::_lim_top * 0.5 , MyShip::_lim_zright * 0.3 },
           {                       3000000 , MyShip::_lim_top * 1.0 ,                       0.0 },
           {                       3000000 ,                    0.0 ,                       0.0 }
        };
        pResource = NEW GgafDx9Spline3D(p, 5, 0.2); //粒度 0.2
    }

    if (GgafUtil::strcmp_ascii("SpCon_002_02", prm_idstr) == 0) {
        //後方から
        double p[][3] = { //           X  ,                          Y ,                         Z
           { MyShip::_lim_behaind - 500000 ,                       0.0 , MyShip::_lim_zright * 0.8 },
           {      MyShip::_lim_front * 1.5 , MyShip::_lim_bottom * 0.2 ,                       0.0 },
           {      MyShip::_lim_front * 2.5 , MyShip::_lim_bottom * 0.5 ,  MyShip::_lim_zleft * 0.3 },
           {      MyShip::_lim_front * 2.2 , MyShip::_lim_bottom * 1.0 ,                       0.0 },
           {      MyShip::_lim_front * 2.0 ,                       0.0 ,                       0.0 }
        };
        pResource = NEW GgafDx9Spline3D(p, 5, 0.2); //粒度 0.2
    }

    if (GgafUtil::strcmp_ascii("SpCon_HAN", prm_idstr) == 0) {
        double p[][3] = { //     X  ,       Y ,       Z
                          {  200000 ,     0.0 ,     0.0 },
                          {  250000 ,  200000 ,     0.0 },
                          {  300000 ,     0.0 ,  200000 },
                          {  350000 , -200000 ,     0.0 },
                          {  400000 ,     0.0 , -200000 },
                          {  450000 ,  200000 ,     0.0 },
                          {  500000 ,     0.0 ,  200000 },
                          {  550000 , -200000 ,     0.0 },
                          {  600000 ,     0.0 , -200000 },
                          {  750000 ,  200000 ,     0.0 },
                          {  800000 ,     0.0 ,  200000 },
                          {  850000 , -200000 ,     0.0 },
                          {  900000 ,     0.0 , -200000 },
                          {  950000 ,  200000 ,     0.0 },
                          { 1000000 ,     0.0 ,  200000 },
                          { 1050000 , -200000 ,     0.0 },
                          { 1200000 ,     0.0 , -200000 },
                          {     0.0 ,     0.0 ,     0.0 }
        };
        pResource = NEW GgafDx9Spline3D(p, 18, 0.2); //粒度 0.2
    }

    if (GgafUtil::strcmp_ascii("SpCon_Pallas01", prm_idstr) == 0) {
        double p[][3] = { //     X  ,       Y ,       Z
                          { -0.574751 , -0.589108 , 0.000000 },
                          { -0.360991 , -0.478461 , 0.137702 },
                          { -0.175143 , -0.370334 , 0.250448 },
                          {  0.021891 , -0.209944 , 0.320181 },
                          {  0.283607 ,  0.024359 , 0.336248 },
                          {  0.422801 ,  0.153113 , 0.336248 },
                          {  0.540611 ,  0.274529 , 0.336248 },
                          {  0.575960 ,  0.390467 , 0.336248 },
                          {  0.544272 ,  0.488121 , 0.336248 },
                          {  0.486184 ,  0.546011 , 0.336248 },
                          {  0.385394 ,  0.561057 , 0.336248 },
                          {  0.287790 ,  0.510965 , 0.336248 },
                          {  0.254406 ,  0.417164 , 0.336248 },
                          {  0.267014 ,  0.316299 , 0.336248 },
                          {  0.344287 ,  0.239935 , 0.336248 },
                          {  0.492799 ,  0.157079 , 0.336248 },
                          {  0.680964 ,  0.136068 , 0.300000 },
                          {  0.829921 ,  0.138288 , 0.244407 },
                          {  0.924608 ,  0.114603 , 0.189449 },
                          {  0.956161 ,  0.063537 , 0.106763 },
                          {  0.927760 ,  0.024959 , 0.051877 },
                          {  0.842761 ,  0.000000 , 0.007250 },
                          {  0.750565 ,  0.000000 , 0.000000 },
                          {  0.597851 ,  0.000000 , 0.000000 }
        };
        for (int i = 0; i < 24; i++) {
            //X
            p[i][0] = p[i][0] * MyShip::_lim_front*1.4;
            //Y
            p[i][1] = p[i][1] * MyShip::_lim_top;
            //Z
            p[i][2] = p[i][2] * MyShip::_lim_zleft;

        }
        pResource = NEW GgafDx9Spline3D(p, 24, 0.2); //粒度 0.2
    }

    return pResource;
}

//MyShip::_lim_top     = GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*5*LEN_UNIT / 2;      //上下は画面高さの大体５画面分
//MyShip::_lim_bottom  = -(GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*5*LEN_UNIT / 2);
//MyShip::_lim_front   = GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*4*LEN_UNIT / 2 ;    //前後は画面幅の大体４画面分
//MyShip::_lim_behaind = -(GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*0.5*LEN_UNIT / 2 );
//MyShip::_lim_zleft   = GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*5*LEN_UNIT / 2;       //奥手前は画面幅の大体５画面分
//MyShip::_lim_zright  = -(GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*5*LEN_UNIT / 2);
//GgafDx9Universe::_X_goneLeft   = GgafDx9Camera::_X_ScreenLeft - 3000*LEN_UNIT; //最大3000pxのオブジェクトまで想定
//GgafDx9Universe::_X_goneRight  = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Y_goneTop    = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Y_goneBottom = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Z_goneFar   = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
//GgafDx9Universe::_Z_goneNear  = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);

GgafResourceConnection<GgafDx9Core::GgafDx9Spline3D>* Spline3DManager::processCreateConnection(char* prm_idstr, GgafDx9Spline3D* prm_pResource) {
    TRACE3(" Spline3DManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    Spline3DConnection* pConnection = NEW Spline3DConnection(prm_idstr, prm_pResource);
    TRACE3(" Spline3DManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
