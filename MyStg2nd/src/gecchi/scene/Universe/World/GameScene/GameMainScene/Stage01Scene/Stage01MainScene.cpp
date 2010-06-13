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
	DWORD dw[] = {1,100,600,1100,1600,2100,2600,3100,3600,4100,4600,5100,5600,6100,6600,7100,7600};
	_paFrame_NextEvent = new DWORD[17];
	for (int i = 0; i < 17; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(11027100, FormationPallas001, "F001_Pallas_1");
	orderActorToFactory(11027600, FormationPallas001, "F001_Pallas_2");
	orderActorToFactory(110271100, FormationPallas001, "F001_Pallas_3");
	orderActorToFactory(110271600, FormationPallas001, "F001_Pallas_4");
	orderActorToFactory(110272100, FormationPallas001, "F001_Pallas_5");
	orderActorToFactory(110272600, FormationPallas001, "F001_Pallas_6");
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // �ȉ��� gen02 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // gen02 start
	if (getPartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getPartFrame()) {
			case 1:
				break;
			case 100:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(11027100);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(110273100, FormationPallas001, "F001_Pallas_7");
				break;
			case 600:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(11027600);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(110273600, FormationPallas001, "F001_Pallas_8");
				break;
			case 1100:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110271100);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(110274100, FormationPallas001, "F001_Pallas_9");
				break;
			case 1600:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110271600);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(110274600, FormationPallas001, "F001_Pallas_10");
				break;
			case 2100:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110272100);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(110275100, FormationPallas001, "F001_Pallas_11");
				break;
			case 2600:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110272600);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(110275600, FormationPallas001, "F001_Pallas_12");
				break;
			case 3100:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110273100);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(110276100, FormationPallas001, "F001_Pallas_13");
				break;
			case 3600:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110273600);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(110276600, FormationPallas001, "F001_Pallas_14");
				break;
			case 4100:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110274100);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(110277100, FormationPallas001, "F001_Pallas_15");
				break;
			case 4600:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110274600);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(110277600, FormationPallas001, "F001_Pallas_16");
				break;
			case 5100:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110275100);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 5600:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110275600);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 6100:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110276100);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 6600:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110276600);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 7100:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110277100);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 7600:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110277600);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 17-1 ? _iCnt_Event+1 : _iCnt_Event);
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
