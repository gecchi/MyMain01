#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

//int FormationJuno::_X_FormationWhole = 0;
//int FormationJuno::_incX = -2000;

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
            int prm_frame_app_interval) : FormationActor(prm_name) {
    _class_name = "FormationJuno";
    _pDispatcherCon = (DispatcherConnection*)(pGOD->_pDispatcherManager->connect("DpCon_Shot004")); //Juno‚Ì’e

    _pRndGen = CmRandomNumberGenerator::getInstance();
    _pRndGen->changeSeed(pMYSHIP->_Z);

    _X1_app = prm_X1_app;
    _Y1_app = prm_Y1_app;
    _Z1_app = prm_Z1_app;
    _X2_app = prm_X2_app;
    _Y2_app = prm_Y2_app;
    _Z2_app = prm_Z2_app;

    _X = prm_X;
    _Y = prm_Y;
    _Z = prm_Z;
    _pMover->setMvVelo(prm_veloMv_App);
    _pMover->setRzRyMvAng(prm_angRzMv_AppBox, prm_angRyMv_AppBox);
    float vX_AppBox, vY_AppBox, vZ_AppBox;
    GgafDx9Util::getNormalizeVectorZY(prm_angRzMv_AppBox, prm_angRyMv_AppBox,
                                      vX_AppBox, vY_AppBox, vZ_AppBox);

    _frame_app_interval = prm_frame_app_interval;

    _pDispatcher_EnemyJuno = NEW GgafActorDispatcher("RotEnemyJuno");
    for (int i = 0; i < prm_nJunoStock; i++) {
        EnemyJuno* pEnemyJuno = NEW EnemyJuno("Juno01");
        pEnemyJuno->setDispatcher_Shot(_pDispatcherCon->view()); //’eÝ’è
        pEnemyJuno->_pMover->relateRzRyFaceAngToMvAng(true);
        pEnemyJuno->_pMover->setMvVelo(prm_veloMv_Juno);
        pEnemyJuno->_pMover->setRzRyMvAng(prm_angRzMv_JunoMv, prm_angRyMv_JunoMv);
        pEnemyJuno->_pMover->setVxMvVelo(vX_AppBox*prm_veloMv_App);
        pEnemyJuno->_pMover->setVyMvVelo(vY_AppBox*prm_veloMv_App);
        pEnemyJuno->_pMover->setVzMvVelo(vZ_AppBox*prm_veloMv_App);
        pEnemyJuno->inactivateTreeImmediately();
        _pDispatcher_EnemyJuno->addSubLast(pEnemyJuno);
    }
    addSubGroup(_pDispatcher_EnemyJuno);
}

void FormationJuno::initialize() {
}

void FormationJuno::processBehavior() {
    if (getPartFrame() % _frame_app_interval == 0) {
        EnemyJuno* pEnemyJuno = (EnemyJuno*)_pDispatcher_EnemyJuno->employ();
        if (pEnemyJuno != NULL) {
            pEnemyJuno->_X = (_pRndGen->genrand_int32() % (_X2_app-_X1_app)) + _X1_app + _X;
            pEnemyJuno->_Y = (_pRndGen->genrand_int32() % (_Y2_app-_Y1_app)) + _Y1_app + _Y;
            pEnemyJuno->_Z = (_pRndGen->genrand_int32() % (_Z2_app-_Z1_app)) + _Z1_app + _Z;
            pEnemyJuno->activate();
        }
    }
    _pMover->behave();
}

FormationJuno::~FormationJuno() {
    _pDispatcherCon->close();
}
