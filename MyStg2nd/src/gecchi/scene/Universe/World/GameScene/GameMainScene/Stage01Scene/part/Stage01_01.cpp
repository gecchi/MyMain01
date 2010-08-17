#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�V�[��Creater.xls�v���J���āA��������s�����Ɓi�������m�ۂ̂��߁j�B
    // gen01 start
    frame f[] = {1,100,500};
    _paFrame_NextEvent = new frame[3];
    for (int i = 0; i < 3; i++) {
        _paFrame_NextEvent[i] = f[i];
    }
    orderActorToFactory(21027100, FormationPallas001a, "F001a_Pallas_1");
    orderActorToFactory(21037500, FormationPallas001b, "F001b_Pallas_2");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // �ȉ��� gen02 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�V�[��Creater.xls�v���J���āA��������s�����Ɓi�������m�ۂ̂��߁j�B
    // gen02 start
    if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
        switch (getActivePartFrame()) {
            case 1:
                break;
            case 100 ... 102:
                {
                FormationPallas001a* pFormationActor = (FormationPallas001a*)obtainActorFromFactory(21027100);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            case 500:
                {
                FormationPallas001b* pFormationActor = (FormationPallas001b*)obtainActorFromFactory(21037500);
                getLordActor()->addSubGroup(pFormationActor);
                }
                break;
            default :
                break;
        }
        _iCnt_Event = (_iCnt_Event < 3-1 ? _iCnt_Event+1 : _iCnt_Event);
    }
    // gen02 end

}

void Stage01_01::processFinal() {
}

Stage01_01::~Stage01_01() {

}
