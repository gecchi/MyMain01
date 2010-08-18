#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01Controller::Stage01Controller(const char* prm_name) : DefaultScene(prm_name) {

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�V�[��Creater.xls�v���J���āA��������s�����Ɓi�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,3,2000,3000,5000,6000};
	_paFrame_NextEvent = new frame[6];
	for (int i = 0; i < 6; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderSceneToFactory(110273, Stage01_01, "Stage01_01");
    // gen01 end
}

void Stage01Controller::initialize() {

}

void Stage01Controller::processBehavior() {
    // �ȉ��� gen02 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�V�[��Creater.xls�v���J���āA��������s�����Ɓi�������m�ۂ̂��߁j�B
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 3:
				{
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(110273);
				addSubLast(pScene);
				}
				break;
			case 2000:
				orderSceneToFactory(110375000, Stage01_02, "Stage01_02");
				break;
			case 3000:
				orderSceneToFactory(110476000, Stage01_03, "Stage01_03");
				break;
			case 5000:
				{
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(110375000);
				addSubLast(pScene);
				}
				break;
			case 6000:
				{
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(110476000);
				addSubLast(pScene);
				}
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 6-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

    if (getBehaveingFrame() == 2) {

        _TRACE_("Stage01Controller::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
        // ���ʃV�[����z���Ɉړ�
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01Controller::processFinal() {
}

Stage01Controller::~Stage01Controller() {

}