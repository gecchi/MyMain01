#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01MainScene::Stage01MainScene(const char* prm_name) : DefaultScene(prm_name) {

    _pDispatcher = NEW GgafActorDispatcher("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 100; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivateTreeImmediately(); //�ŏ���\��
        _pDispatcher->addSubLast(pEnemyMeshShot);
    }
    getLordActor()->addSubGroup(KIND_ENEMY_SHOT_CHOKI, _pDispatcher);

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�V�[��Creater.xls�v���J���āA��������s���B
    // gen01 start
	DWORD dw[] = {17002,20002};
	_paFrame_NextEvent = new DWORD[2];
	for (int i = 0; i < 2; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // �ȉ��� gen02 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // gen02 start
	if (getPartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getPartFrame()) {
			case 17002:
				orderActorToFactory(1138620002, EnemyMetis, "Metis_1");
				break;
			case 20002:
				getLordActor()->addSubGroup(obtainActorFromFactory(1138620002));
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 2-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

    if (getBehaveingFrame() == 2) {

        _TRACE_("Stage01MainScene::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
        // ���ʃV�[����z���Ɉړ�
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (getBehaveingFrame() == 1) {
    //		_TRACE_("Stage01MainScene::processFinally ���͂����Ȃ��~���܂��BGameMainScene���������Ă����͂��[");
    //		this->inactivateTree(); //GameMainScene���������Ă����
    //	}
}

Stage01MainScene::~Stage01MainScene() {
    //NEW����processBehavior�܂ł̊Ԃɋ����I�����ꂽ�ꍇ�A
    //_pDispatcher�͂ǂ̃c���[�ɂ��������Ă��Ȃ��B
    if (_pDispatcher->getParent() == NULL) {
        _TRACE_("_pDispatcher���������̂��ߓƎ�delete");
        DELETE_IMPOSSIBLE_NULL(_pDispatcher);
    }
}
