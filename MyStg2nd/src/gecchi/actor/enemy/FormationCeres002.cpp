#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationCeres002::FormationCeres002(const char* prm_name) : FormationActor(prm_name) {
    _class_name = "FormationCeres002";

    _pRotEnemyMeshShots001 = NEW RotationActor("FmtCeres002_RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 30; i++) { //弾ストック
                Sleep(1);
                pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
                pEnemyMeshShot->inactivateTreeImmediately(); //最初非表示
                _pRotEnemyMeshShots001->addSubLast(pEnemyMeshShot);
            }
            for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
                Sleep(1);
                _pEnemyCeres[i] = NEW EnemyCeres("Ceres01");
                _pEnemyCeres[i]->inactivateImmediately();
                _pEnemyCeres[i]->_Y_turn = -1*(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2) + (i * ((GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT)/NUM_CERES_FORMATION002));
                _pEnemyCeres[i]->_veloBegin = 5000;
                _pEnemyCeres[i]->_Z = -1500000;
                addSubLast(_pEnemyCeres[i] );
            }

            //一時退避
            addSubLast(this->_pRotEnemyMeshShots001);
        }

void FormationCeres002::initialize() {
    //出現予約
    for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
        _pEnemyCeres[i]->activateAfter(i * 80 + 1);
    }
}

void FormationCeres002::processJudgement() {
    if (getSubFirst() == NULL) {
        arigatou_sayounara();
        _pRotEnemyMeshShots001->arigatou_sayounara(60 * 5);
    }
}

FormationCeres002::~FormationCeres002() {
}
