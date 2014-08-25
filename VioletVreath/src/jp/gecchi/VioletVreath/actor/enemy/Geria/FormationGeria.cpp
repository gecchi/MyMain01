#include "FormationGeria.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/EnemyGeria.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

//int FormationGeria::X_FormationWhole_ = 0;
//int FormationGeria::incX_ = -2000;

FormationGeria::FormationGeria(
            const char* prm_name,
            int prm_X1_app, int prm_Y1_app, int prm_Z1_app,
            int prm_X2_app, int prm_Y2_app, int prm_Z2_app,
            int prm_x, int prm_y, int prm_z,
            velo prm_velo_mv_App,
            angle prm_ang_rz_mv_AppBox, angle prm_ang_ry_mv_AppBox,
            velo prm_velo_mv_Geria,
            angle prm_ang_rz_mv_GeriaMv, angle prm_ang_ry_mv_GeriaMv,
            int prm_nGeriaStock,
            int prm_frame_app_interval) : DefaultGeometricActor(prm_name, nullptr) {
    _class_name = "FormationGeria";
    pAxsMver_ = NEW GgafDxAxesMover(this);

    X1_app_ = prm_X1_app;
    Y1_app_ = prm_Y1_app;
    Z1_app_ = prm_Z1_app;
    X2_app_ = prm_X2_app;
    Y2_app_ = prm_Y2_app;
    Z2_app_ = prm_Z2_app;

    _x = prm_x;
    _y = prm_y;
    _z = prm_z;
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvVelo(prm_velo_mv_App);
    pKuroko->setRzRyMvAng(prm_ang_rz_mv_AppBox, prm_ang_ry_mv_AppBox);
    float vX_AppBox, vY_AppBox, vZ_AppBox;
    UTIL::convRzRyToVector(prm_ang_rz_mv_AppBox, prm_ang_ry_mv_AppBox,
                           vX_AppBox, vY_AppBox, vZ_AppBox);

    frame_app_interval_ = prm_frame_app_interval;

    pDepo_ = NEW GgafActorDepository("RotEnemyGeria");
    for (int i = 0; i < prm_nGeriaStock; i++) {
        std::string name = "Geria"+XTOS(i);
        EnemyGeria* pEnemyGeria = NEW EnemyGeria(name.c_str());
        pEnemyGeria->getKuroko()->relateFaceByMvAng(true);
        pEnemyGeria->getKuroko()->setMvVelo(prm_velo_mv_Geria);
        pEnemyGeria->getKuroko()->setRzRyMvAng(prm_ang_rz_mv_GeriaMv, prm_ang_ry_mv_GeriaMv);
        pEnemyGeria->pAxsMver_->setVxyzMvVelo(vX_AppBox*prm_velo_mv_App,
                                              vY_AppBox*prm_velo_mv_App,
                                              vZ_AppBox*prm_velo_mv_App );
        pDepo_->put(pEnemyGeria);
    }
    addSubGroup(pDepo_);
}

void FormationGeria::initialize() {
}

void FormationGeria::processBehavior() {
    if (getActiveFrame() % frame_app_interval_ == 0) {
        EnemyGeria* pEnemyGeria = (EnemyGeria*)pDepo_->dispatch();
        if (pEnemyGeria) {
            pEnemyGeria->_x = RND(X1_app_, X2_app_) + _x;
            pEnemyGeria->_y = RND(Y1_app_, Y2_app_) + _y;
            pEnemyGeria->_z = RND(Z1_app_, Z2_app_) + _z;
        }
    }
    getKuroko()->behave();
    pAxsMver_->behave();
}

FormationGeria::~FormationGeria() {
    GGAF_DELETE(pAxsMver_);
}
