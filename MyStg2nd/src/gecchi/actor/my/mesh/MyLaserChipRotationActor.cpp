#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyLaserChipRotationActor::MyLaserChipRotationActor(const char* prm_name) : RotationActor(prm_name) {
    _class_name = "MyLaserChipRotationActor";
    _num_chip_max = 26;
    _num_continual_obtain_count = 0;
    _num_chip_active = 0;
    _is_tear_laser = false;
    _pHeadChip = NULL;
    MyLaserChip* pChip;
    for (int i = 0; i < _num_chip_max; i++) { //レーザーストック
        Sleep(1);
        stringstream name;
        name <<  "MYS_MyLaserChip" << i;
        string name2 = name.str();
        pChip = NEW MyLaserChip(name2.c_str(), this);
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
}

MyLaserChip* MyLaserChipRotationActor::obtain() {
    if (_is_tear_laser && _num_chip_max - _num_chip_active < _num_chip_max/2) {
        _pChip_prev_obtain = NULL;
        _lifeframe_prev_obtain = 0;
        return NULL;
    } else {
        MyLaserChip* pChip = (MyLaserChip*)RotationActor::obtain();
        if (pChip != NULL) {

            if (_pChip_prev_obtain != NULL) {
                if (_lifeframe_prev_obtain == _pChip_prev_obtain->_lifeframe) { //アクティブになってフレームが加算されるのは１フレーム次であるため
                    //2フレーム連続でobtainの場合連結とみなす
                    _num_continual_obtain_count++;
                    pChip->_pChip_front = _pChip_prev_obtain;
                    _pChip_prev_obtain->_pChip_behind = pChip;
                    _is_tear_laser = false;
                } else {
                    //2フレーム連続でobtain出来てない場合連結は切れてる
                    _num_continual_obtain_count = 0;
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
            _num_continual_obtain_count = 0;
            _is_tear_laser = true;
            _pChip_prev_obtain = NULL;
            _lifeframe_prev_obtain = 0;
            return NULL;
        }
    }

}

MyLaserChipRotationActor::~MyLaserChipRotationActor() {
    _pSeCon_Laser->close();
}
