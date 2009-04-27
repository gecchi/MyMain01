#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01MainScene::Stage01MainScene(const char* prm_name) : DefaultScene(prm_name) {

    _pRot = NEW RotationActor("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 100; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivateTreeImmediately(); //�ŏ���\��
        _pRot->addSubLast(pEnemyMeshShot);
    }
    getLordActor()->accept(KIND_ENEMY, _pRot);

	// �ȉ��� gen01 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
	// gen01 start
	DWORD dw[] = {1,10};
	_paFrame_NextEvent = new DWORD[2];
	for (int i = 0; i < 2; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105610, EnemyAstraea, "Astraea_1");
	// gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // �ȉ��� gen02 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // gen02 start
	if (_lifeframe == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_lifeframe) {
			case 1:
				break;
			case 10:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610));
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
    // gen02 end

    if (_lifeframe== 2) {

        _TRACE_("Stage01MainScene::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
        // ���ʃV�[����z���Ɉړ�
        addSubLast(GameGlobal::_pSceneCommon->breakAwayFromTree());

    }

}

void Stage01MainScene::processFinal() {
    //	if (_lifeframe== 1) {
    //		_TRACE_("Stage01MainScene::processFinally ���͂����Ȃ��~���܂��BGameMainScene���������Ă����͂��[");
    //		this->inactivateTree(); //GameMainScene���������Ă����
    //	}
}

Stage01MainScene::~Stage01MainScene() {
    //NEW����processBehavior�܂ł̊Ԃɋ����I�����ꂽ�ꍇ�A
    //_pRot�͂ǂ̃c���[�ɂ��������Ă��Ȃ��B
    if (_pRot->getParent() == NULL) {
        _TRACE_("_pRot���������̂��ߓƎ�delete");
        DELETE_IMPOSSIBLE_NULL(_pRot);
    }
}
