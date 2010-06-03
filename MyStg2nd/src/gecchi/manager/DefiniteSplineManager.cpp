#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DefiniteSplineManager::DefiniteSplineManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Core::GgafDx9Spline3D> (prm_manager_name) {
}

GgafDx9Spline3D* DefiniteSplineManager::processCreateResource(char* prm_idstr) {
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
        pResource = NEW GgafDx9Spline3D(p, 17, 0.2);//���x 0.2
    }

    if (GgafUtil::strcmp_ascii("SpCon_002_01", prm_idstr) == 0) {
        //�������
        double p[][3] = { //           X  ,                       Y ,                         Z
           { MyShip::_lim_behaind - 500000 ,                    0.0 ,  MyShip::_lim_zleft * 0.8 },
           {      3000000 , MyShip::_lim_top * 0.2 ,                       0.0 },
           {      3000000 , MyShip::_lim_top * 0.5 , MyShip::_lim_zright * 0.3 },
           {      3000000 , MyShip::_lim_top * 1.0 ,                       0.0 },
           {      3000000 ,                    0.0 ,                       0.0 }
        };
        pResource = NEW GgafDx9Spline3D(p, 5, 0.2); //���x 0.2
    }

    if (GgafUtil::strcmp_ascii("SpCon_002_02", prm_idstr) == 0) {
        //�������
        double p[][3] = { //           X  ,                          Y ,                         Z
           { MyShip::_lim_behaind - 500000 ,                       0.0 , MyShip::_lim_zright * 0.8 },
           {      MyShip::_lim_front * 1.5 , MyShip::_lim_bottom * 0.2 ,                       0.0 },
           {      MyShip::_lim_front * 2.5 , MyShip::_lim_bottom * 0.5 ,  MyShip::_lim_zleft * 0.3 },
           {      MyShip::_lim_front * 2.2 , MyShip::_lim_bottom * 1.0 ,                       0.0 },
           {      MyShip::_lim_front * 2.0 ,                       0.0 ,                       0.0 }
        };
        pResource = NEW GgafDx9Spline3D(p, 5, 0.2); //���x 0.2
    }

    if (GgafUtil::strcmp_ascii("SpCon_HAN", prm_idstr) == 0) {
        //�������
        double p[][3] = { //           X  ,                          Y ,                         Z
           {  200000 , 0.0     , 0.0 },
           {  250000 , 200000  , 0.0 },
           {  300000 , 0.0     , 200000 },
           {  350000 , -200000 , 0.0 },
           {  400000 , 0.0     , -200000 },
           {  450000 , 200000  , 0.0 },
           {  500000 , 0.0     , 200000 },
           {  550000 , -200000 , 0.0 },
           {  600000 , 0.0     , -200000 },
           {  750000 , 200000  , 0.0 },
           {  800000 , 0.0     , 200000 },
           {  850000 , -200000 , 0.0 },
           {  900000 , 0.0     , -200000 },
           {  950000 , 200000  , 0.0 },
           {  1000000 , 0.0     , 200000 },
           {  1050000 , -200000 , 0.0 },
           {  1200000 , 0.0     , -200000 },
           {  0.0 , 0.0 , 0.0 }
        };
        pResource = NEW GgafDx9Spline3D(p, 18, 0.2); //���x 0.2
    }


    return pResource;
}

GgafResourceConnection<GgafDx9Core::GgafDx9Spline3D>* DefiniteSplineManager::processCreateConnection(char* prm_idstr, GgafDx9Spline3D* prm_pResource) {
    TRACE3(" DefiniteSplineManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    DefiniteSplineConnection* pConnection = NEW DefiniteSplineConnection(prm_idstr, prm_pResource);
    TRACE3(" DefiniteSplineManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConnection;
}