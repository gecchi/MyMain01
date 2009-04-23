#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

LaserChipRotationActor::LaserChipRotationActor(const char* prm_name, LaserChip* prm_pChip_subFirst) : RotationActor(prm_name) {
    _class_name = "LaserChipRotationActor";
    _num_continual_obtain_count = 0;
    _num_chip_active = 0;
    _is_tear_laser = false;
    _num_chip_max = prm_pChip_subFirst->getNumSub();
    addSubLast(pChip);


//    LaserChip* pChip;
//    for (int i = 0; i < _num_chip_max; i++) { //レーザーストック
//        Sleep(2); //工場に気を使う。
//        stringstream name;
//        name <<  "MYS_LaserChip" << i;
//        string name2 = name.str();
//        pChip = NEW LaserChip(name2.c_str(), this);
//        pChip->inactivateImmediately();
//        addSubLast(pChip);
//    }
//    Sleep(1);
    _pChip_prev_obtain = NULL;
    _lifeframe_prev_obtain = 0;
    _pSeCon_Laser = (GgafDx9SeConnection*)GgafDx9Sound::_pSeManager->getConnection("laser001");
}
void LaserChipRotationActor::processBehavior() {
}

void LaserChipRotationActor::processFinal() {
}

LaserChip* LaserChipRotationActor::obtain() {
    if ((_is_tear_laser && _num_chip_max - _num_chip_active < _num_chip_max/4) || _num_continual_obtain_count > _num_chip_max) {
        _is_tear_laser = true;
        _pChip_prev_obtain = NULL;
        _lifeframe_prev_obtain = 0;
        _num_continual_obtain_count = 0;
        return NULL;
    } else {
        LaserChip* pChip = (LaserChip*)RotationActor::obtain();
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

LaserChipRotationActor::~LaserChipRotationActor() {
    _pSeCon_Laser->close();
}
