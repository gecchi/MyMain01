#include "SplineLineManager.h"

#include "jp/gecchi/VioletVreath/manager/SplineLineConnection.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SplineLineManager::SplineLineManager(const char* prm_manager_name) :
    GgafResourceManager<GgafLib::SplineLine> (prm_manager_name) {
}

SplineLine* SplineLineManager::processCreateResource(char* prm_idstr, void* prm_pConnector) {
    SplineLine* pResource = nullptr;

    if (strcmp("Spl_001", prm_idstr) == 0) {
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
        pResource = NEW SplineLine(p, 17, 0.2);//粒度 0.2
    }

    if (strcmp("Spl_00201_", prm_idstr) == 0) {
        //後方から
        double p[][3] = { //           X  ,                       Y ,                         Z
           { MyShip::lim_x_behaind_ - 500000.0 ,                      0.0 ,  MyShip::lim_z_left_ * 0.8 },
           {                          3000000 , MyShip::lim_y_top_ * 0.2 ,                        0.0 },
           {                          3000000 , MyShip::lim_y_top_ * 0.5 , MyShip::lim_z_right_ * 0.3 },
           {                          3000000 , MyShip::lim_y_top_ * 1.0 ,                        0.0 },
           {                          3000000 ,                      0.0 ,                        0.0 }
        };
        pResource = NEW SplineLine(p, 5, 0.2); //粒度 0.2
    }

    if (strcmp("Spl_00202_", prm_idstr) == 0) {
        //後方から
        double p[][3] = { //           X  ,                          Y ,                         Z
           { MyShip::lim_x_behaind_ - 500000.0 ,                         0.0 , MyShip::lim_z_right_ * 0.8 },
           { MyShip::lim_x_front_ * 1.5        , MyShip::lim_y_bottom_ * 0.2 ,                        0.0 },
           { MyShip::lim_x_front_ * 2.5        , MyShip::lim_y_bottom_ * 0.5 ,  MyShip::lim_z_left_ * 0.3 },
           { MyShip::lim_x_front_ * 2.2        , MyShip::lim_y_bottom_ * 1.0 ,                        0.0 },
           { MyShip::lim_x_front_ * 2.0        ,                         0.0 ,                        0.0 }
        };
        pResource = NEW SplineLine(p, 5, 0.2); //粒度 0.2
    }

    if (strcmp("Spl_HAN", prm_idstr) == 0) {
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
                          { 1050000 ,     0.0 ,     0.0 },
                          { 1000000 ,     0.0 ,     0.0 },
                          { 950000  ,     0.0 ,     0.0 },
                          {     0.0 ,     0.0 ,     0.0 }
        };
        pResource = NEW SplineLine(p, 21, 0.2); //粒度 0.2
    }

    if (strcmp("Spl_Allas01", prm_idstr) == 0) {
        double p[][3] = { //     X  ,       Y ,       Z
                          { -1.724577 ,  0.000000 ,  0.000000 },
                          { -0.964337 , -0.088378 , -0.344892 },
                          { -0.501305 , -0.055518 , -0.298879 },
                          { -0.179336 , -0.031628 , -0.240141 },
                          {  0.123544 , -0.016126 , -0.165195 },
                          {  0.362343 ,  0.000000 ,  0.000000 },
                          {  0.545634 ,  0.038709 ,  0.176104 },
                          {  0.704048 ,  0.173192 ,  0.372772 },
                          {  0.864812 ,  0.444651 ,  0.516556 },
                          {  1.055714 ,  0.626849 ,  0.569336 },
                          {  1.246407 ,  0.655359 ,  0.547772 },
                          {  1.365876 ,  0.590994 ,  0.453279 },
                          {  1.388259 ,  0.465998 ,  0.332581 },
                          {  1.362117 ,  0.328636 ,  0.211183 },
                          {  1.242692 ,  0.226675 ,  0.087900 },
                          {  1.064405 ,  0.202917 ,  0.000000 },
                          {  0.920421 ,  0.202917 ,  0.000000 }
        };
        for (int i = 0; i < 17; i++) {
            //X
            p[i][0] = p[i][0] * MyShip::lim_x_front_;
            //Y
            p[i][1] = p[i][1] * MyShip::lim_y_top_;
            //Z
            p[i][2] = p[i][2] * MyShip::lim_z_left_;

        }
        pResource = NEW SplineLine(p, 17, 0.2); //粒度 0.2
    }
    if (pResource == nullptr) {
        throwGgafCriticalException("SplineLineManager::processCreateResource("<<prm_idstr<<") 想定外のIDです。SplineLineが作成できません。");
    }
    return pResource;
}

GgafResourceConnection<GgafLib::SplineLine>* SplineLineManager::processCreateConnection(char* prm_idstr, SplineLine* prm_pResource) {
    _TRACE3_(" SplineLineManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    SplineLineConnection* pConne = NEW SplineLineConnection(prm_idstr, prm_pResource);
    _TRACE3_(" SplineLineManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConne;
}

