#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyLaserChipRotationActor::MyLaserChipRotationActor(const char* prm_name) : RotationActor(prm_name) {
    _class_name = "MyLaserChipRotationActor";
    _iNumActiveChip = 0;
    _pHeadChip = NULL;
    _mode = 0;
    MyLaserChip2* pChip;
    for (int i = 0; i < 32; i++) { //レーザーストック
        Sleep(1);
        pChip = NEW MyLaserChip2("MYS_MyLaserChip2", "m/laserchip9");
        pChip->inactImmediately();
        addSubLast(pChip);
    }
    Sleep(1);
    _pSeCon_Laser = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->getConnection("laser001");
}
void MyLaserChipRotationActor::processBehavior() {
}

void MyLaserChipRotationActor::processFinal() {
    if (_pHeadChip == NULL) {
        if (_mode == 1 && _iNumActiveChip == 0) {
            _mode = 0;
        }
    } else {
        if ( _pHeadChip->_switchedToInact) {
            _mode = 1;
            _pHeadChip = NULL;
        } else {

        }
    }
}

GgafMainActor* MyLaserChipRotationActor::obtain() {
    if (_mode == 1) {
        return NULL;
    } else {
        if (_iNumActiveChip >= 32) {
            return NULL;
        } else {
            MyLaserChip2* pChip = (MyLaserChip2*)RotationActor::obtain();
            if (pChip == NULL) {
                _TRACE_("おかしいですぜ兄貴MyLaserChipRotationActor::obtain() _iNumActiveChip="<<_iNumActiveChip<<"/_mode="<<_mode);
                return NULL;
            } else {
                _iNumActiveChip++;
            }
            if (_iNumActiveChip == 1) {
                //先頭のチップ
                _pSeCon_Laser->take()->play();
                _pHeadChip = pChip;
            }
            return pChip;
        }
    }
}


MyLaserChipRotationActor::~MyLaserChipRotationActor() {
    _pSeCon_Laser->close();
}
