#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyOptionTorpedoController::MyOptionTorpedoController(const char* prm_name, MyOption* prm_pMyOption)
                                                                                  : GgafDummyActor(prm_name) {
    _class_name = "MyOptionTorpedoController";
    _length_TorpedoChip = 10;
    _papLaserChipDispatcher = NEW LaserChipDispatcher*[MyOption::_max_lockon_num];
    _pa_all_employed = NEW bool[MyOption::_max_lockon_num];
    _papMyTorpedoChip_Head = NEW MyTorpedoChip*[MyOption::_max_lockon_num];
    for (int i = 0; i < MyOption::_max_lockon_num; i++) {
        _pa_all_employed[i] = false;
        _papLaserChipDispatcher[i] = NEW LaserChipDispatcher("DP");
        _papLaserChipDispatcher[i]->config(_length_TorpedoChip, 0, NULL);


        for (int j = 0; j < _length_TorpedoChip; j++) {
            stringstream name;
            name <<  "Torpedo["<<i<<"]["<<j<<"]";
            MyTorpedoChip* pChip = NEW MyTorpedoChip(name.str().c_str());
            if (j == 0) {
                //実質の先頭？

            }
            pChip->inactivateImmediately();
            _papLaserChipDispatcher[i]->addSubLast(pChip);
        }
        addSubGroup(_papLaserChipDispatcher[i]);
    }
    _firing_num = 0;
    _in_firing = false;
    _pMyOption = prm_pMyOption;

}

void MyOptionTorpedoController::initialize() {
}

void MyOptionTorpedoController::processBehavior() {
    if (_in_firing) {
        _in_firing = false;
        for (int i = 0; i < _firing_num; i++) {
            if (_pa_all_employed[i]) {
                //発射後
                if (_papLaserChipDispatcher[i]->_num_chip_active > 0) {
                    _in_firing = true;
                }
            } else {
                //発射中
                _in_firing = true;
                MyTorpedoChip* pTorpedoChip = (MyTorpedoChip*)_papLaserChipDispatcher[i]->employ();
                if (pTorpedoChip) {
                    pTorpedoChip->setGeometry(pMYSHIP);
                    pTorpedoChip->activate();
                    if (pTorpedoChip->_pChip_front &&  pTorpedoChip->_pChip_front->_pChip_front == NULL) {
                        _papMyTorpedoChip_Head[i] = pTorpedoChip;
                    }
                } else {
                    _pa_all_employed[i] = true;
                }
            }
        }
    }
}

void MyOptionTorpedoController::processJudgement() {
}

void MyOptionTorpedoController::fire() {
    if (!_in_firing) {
        _in_firing = true;
        int target_num = _pMyOption->_pLockonController->_pRingTarget->length();
        _firing_num = MyOption::_max_lockon_num; //target_num == 0 ? MyOption::_max_lockon_num : target_num;
        angle angBegin = ANGLE90;
        angle angRenge  = ANGLE360 / _pMyOption->_pMyOptionParent->_now_option_num;
        angle angFireCenter = angBegin + (ANGLE360*(_pMyOption->_no-1) / _pMyOption->_pMyOptionParent->_now_option_num);
        angle out_rz,out_ry,out_dz,out_dy;
        angle* pa_angWay = NEW angle[ _firing_num+2];
        GgafDx9Util::getWayAngle2D(angFireCenter, _firing_num+1, angRenge / _firing_num, pa_angWay);
        for (int i = 0; i < _firing_num; i++) { //両端の方向は不要
            _pa_all_employed[i] = false; //リセット
            MyTorpedoChip* pHead = (MyTorpedoChip*)_papLaserChipDispatcher[i]->getSubFirst();
            if (target_num == 0) {
                pHead->_pTarget = NULL;
            } else {
                pHead->_pTarget = _pMyOption->_pLockonController->_pRingTarget->getNext(i);
            }

            pHead->_pMover->setRzRyMvAng(0, 0);
            pHead->_pMover->getRzRyMvAngDistance(TURN_CLOSE_TO,
                                                 pa_angWay[i], ANGLE90,
                                                 out_dz, out_dy,
                                                 out_rz, out_ry
                                                );
            pHead->_pMover->setRzRyMvAng(out_rz, out_ry);
        }
        delete[] pa_angWay;
    }
}


MyOptionTorpedoController::~MyOptionTorpedoController() {
}
