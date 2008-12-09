#include "stdafx.h"

FormationCeres002::FormationCeres002(string prm_name, string prm_model) : FormationActor(prm_name) {
	_class_name = "FormationCeres002";

	_pRotEnemyMeshShots001 = NEW RotationActor("FmtCeres002_RotEnemyMeshS001");
	EnemyMeshShot001* pEnemyMeshShot;
	for (int i = 0; i < 80; i++) { //�X�g�b�N256��
		pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshS"+GgafUtil::itos(i), "myvic");
		pEnemyMeshShot->stopImmediately(); //�ŏ���\��
		_pRotEnemyMeshShots001 -> addSubLast(pEnemyMeshShot);
	}

	for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
		_pEnemyCeres[i] = NEW EnemyCeres("Ceres01", prm_model);
		_pEnemyCeres[i] -> stopImmediately();
		_pEnemyCeres[i] -> _Y_turn = -1*(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2) + (i * ((GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT)/NUM_CERES_FORMATION002)) ;
		_pEnemyCeres[i] -> _iBeginVelocity = 5000;
		_pEnemyCeres[i] -> _Z = -1500000;
		_pEnemyCeres[i] -> _pRotEnemyMeshShots001 = this->_pRotEnemyMeshShots001;
		addSubLast(_pEnemyCeres[i] );
	}
	//�ꎞ�ޔ�
	addSubLast(this->_pRotEnemyMeshShots001);
}

void FormationCeres002::initialize() {
	//�{���̏ꏊ��
	getLordActor()->accept(KIND_ENEMY_SHOT_GU, (GgafMainActor*)_pRotEnemyMeshShots001->tear());
	//�o���\��
	for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
		_pEnemyCeres[i] -> playAfter(i*80+1);
	}
}

void FormationCeres002::processJudgement() {
	if (getSubFirst() == NULL) {
		declareFinishLife();
		_pRotEnemyMeshShots001 -> declareFinishLife(60*5);
	}
}

FormationCeres002::~FormationCeres002() {
}
