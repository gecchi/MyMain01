#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

//int FormationJuno::X_FormationWhole_ = 0;
//int FormationJuno::incX_ = -2000;

FormationJuno::FormationJuno(
            const char* prm_name,
            int prm_X1_app, int prm_Y1_app, int prm_Z1_app,
            int prm_X2_app, int prm_Y2_app, int prm_Z2_app,
            int prm_X, int prm_Y, int prm_Z,
            velo prm_veloMv_App,
            angle prm_angRzMv_AppBox, angle prm_angRyMv_AppBox,
            velo prm_veloMv_Juno,
            angle prm_angRzMv_JunoMv, angle prm_angRyMv_JunoMv,
            int prm_nJunoStock,
            int prm_frame_app_interval) : DefaultGeometricActor(prm_name, NULL) {
    _class_name = "FormationJuno";
    pDepoCon_ = connectDepositoryManager("DpCon_Shot004", NULL); //Juno‚Ì’e

    X1_app_ = prm_X1_app;
    Y1_app_ = prm_Y1_app;
    Z1_app_ = prm_Z1_app;
    X2_app_ = prm_X2_app;
    Y2_app_ = prm_Y2_app;
    Z2_app_ = prm_Z2_app;

    _X = prm_X;
    _Y = prm_Y;
    _Z = prm_Z;
    _pKurokoA->setMvVelo(prm_veloMv_App);
    _pKurokoA->setRzRyMvAng(prm_angRzMv_AppBox, prm_angRyMv_AppBox);
    float vX_AppBox, vY_AppBox, vZ_AppBox;
    GgafDxUtil::getNormalizeVectorZY(prm_angRzMv_AppBox, prm_angRyMv_AppBox,
                                      vX_AppBox, vY_AppBox, vZ_AppBox);

    frame_app_interval_ = prm_frame_app_interval;

    pDepo_EnemyJuno_ = NEW GgafActorDepository("RotEnemyJuno");
    for (int i = 0; i < prm_nJunoStock; i++) {
        std::string name = "Juno"+ITOS(i);
        EnemyJuno* pEnemyJuno = NEW EnemyJuno(name.c_str());
        pEnemyJuno->setDepository_Shot(pDepoCon_->fetch()); //’eÝ’è
        pEnemyJuno->_pKurokoA->relateFaceAngWithMvAng(true);
        pEnemyJuno->_pKurokoA->setMvVelo(prm_veloMv_Juno);
        pEnemyJuno->_pKurokoA->setRzRyMvAng(prm_angRzMv_JunoMv, prm_angRyMv_JunoMv);
        pEnemyJuno->_pKurokoB->setVxMvVelo(vX_AppBox*prm_veloMv_App);
        pEnemyJuno->_pKurokoB->setVyMvVelo(vY_AppBox*prm_veloMv_App);
        pEnemyJuno->_pKurokoB->setVzMvVelo(vZ_AppBox*prm_veloMv_App);
        pEnemyJuno->inactivateTreeImmed();
        pDepo_EnemyJuno_->addSubLast(pEnemyJuno);
    }
    addSubGroup(pDepo_EnemyJuno_);
}

void FormationJuno::initialize() {
}

void FormationJuno::processBehavior() {
    if (getActivePartFrame() % frame_app_interval_ == 0) {
        EnemyJuno* pEnemyJuno = (EnemyJuno*)pDepo_EnemyJuno_->dispatch();
        if (pEnemyJuno) {
            pEnemyJuno->_X = RND(X1_app_, X2_app_) + _X;
            pEnemyJuno->_Y = RND(Y1_app_, Y2_app_) + _Y;
            pEnemyJuno->_Z = RND(Z1_app_, Z2_app_) + _Z;
        }
    }
    _pKurokoA->behave();
    _pKurokoB->behave();
}

FormationJuno::~FormationJuno() {
    pDepoCon_->close();
}
