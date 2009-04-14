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
    MyLaserChip* pChip;
    for (int i = 0; i < 100; i++) { //レーザーストック
        Sleep(1);
        pChip = NEW MyLaserChip("MYS_MyLaserChip1");
        pChip->inactivateTreeNow();
        addSubLast(pChip);
    }
    Sleep(1);
    _pChip_prev_obtain = NULL;
    _lifeframe_prev_obtain = 0;
    _pSeCon_Laser = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->getConnection("laser001");
}
void MyLaserChipRotationActor::processBehavior() {
}

void MyLaserChipRotationActor::processFinal() {
//    if (_pHeadChip == NULL) {
//        if (_mode == 1 && _iNumActiveChip == 0) {
//            _mode = 0;
//        }
//    } else {
//        if ( _pHeadChip->onChangeToInactive()) {
//            _mode = 1;
//            _pHeadChip = NULL;
//        } else {
//
//        }
//    }
}

//MyLaserChip* MyLaserChipRotationActor::obtain() {
//    if (_mode == 1) {
//        return NULL;
//    } else {
//        if (_iNumActiveChip >= 32) {
//            return NULL;
//        } else {
//            MyLaserChip* pChip = (MyLaserChip*)RotationActor::obtain();
//            if (pChip == NULL) {
//                _TRACE_("おかしいですぜ兄貴MyLaserChipRotationActor::obtain() _iNumActiveChip="<<_iNumActiveChip<<"/_mode="<<_mode);
//                return NULL;
//            } else {
//                _iNumActiveChip++;
//            }
//            if (_iNumActiveChip == 1) {
//                //先頭のチップ
//                _pSeCon_Laser->view()->play();
//                _pHeadChip = pChip;
//            }
//            return pChip;
//        }
//    }
//}
MyLaserChip* MyLaserChipRotationActor::obtain() {

    MyLaserChip* pChip = (MyLaserChip*)RotationActor::obtain();
    if (pChip != NULL) {
        if (_pChip_prev_obtain != NULL) {
			//_TRACE_("_lifeframe_prev_obtain="<<_lifeframe_prev_obtain<<" _pChip_prev_obtain->_lifeframe="<<_pChip_prev_obtain->_lifeframe);
            if (_lifeframe_prev_obtain == _pChip_prev_obtain->_lifeframe) { //アクティブになってフレームが加算されるのは１フレーム次であるため
                //2フレーム連続でobtainの場合連結とみなす
                pChip->_pChip_front = _pChip_prev_obtain;
                _pChip_prev_obtain->_pChip_behind = pChip;
            } else {
                //2フレーム連続でobtainの場合連結は切れてる
                pChip->_pChip_front = NULL;
                _pChip_prev_obtain->_pChip_behind = NULL;
            }
        } else {
            pChip->_pChip_front = NULL;
        }
        _pChip_prev_obtain = pChip;
        _lifeframe_prev_obtain = pChip->_lifeframe;
        return pChip;

    } else {
        _pChip_prev_obtain = NULL;
        _lifeframe_prev_obtain = 0;
        return NULL;
    }

}

MyLaserChipRotationActor::~MyLaserChipRotationActor() {
    _pSeCon_Laser->close();
}
