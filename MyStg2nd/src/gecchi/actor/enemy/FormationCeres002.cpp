#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationCeres002::FormationCeres002(char* prm_name, char* prm_model) : FormationActor(prm_name) {
	_class_name = "FormationCeres002";

	_pRotEnemyMeshShots001 = NEW RotationActor("FmtCeres002_RotEnemyMeshS001");
	EnemyMeshShot001* pEnemyMeshShot;
	for (int i = 0; i < 30; i++) { //�e�X�g�b�N
		Sleep(1);
		pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot", "M/BDAMA");
		pEnemyMeshShot->stopImmediately(); //�ŏ���\��
		_pRotEnemyMeshShots001->addSubLast(pEnemyMeshShot);
	}

	for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
		Sleep(1);
		_pEnemyCeres[i] = NEW EnemyCeres("Ceres01", prm_model, _pRotEnemyMeshShots001);
		_pEnemyCeres[i]->stopAloneImmediately();
		_pEnemyCeres[i]->_Y_turn = -1*(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2) + (i * ((GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT)/NUM_CERES_FORMATION002)) ;
		_pEnemyCeres[i]->_iBeginVelocity = 5000;
		_pEnemyCeres[i]->_Z = -1500000;
		addSubLast(_pEnemyCeres[i] );
	}

	//�ꎞ�ޔ�
	addSubLast(this->_pRotEnemyMeshShots001);
}

void FormationCeres002::initialize() {
	//�o���\��
	for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
		_pEnemyCeres[i]->playAfter(i*80+1);
	}
}

void FormationCeres002::processJudgement() {
	if (getSubFirst() == NULL) {
		farewell();
		_pRotEnemyMeshShots001->farewell(60*5);
	}
}

FormationCeres002::~FormationCeres002() {
}
