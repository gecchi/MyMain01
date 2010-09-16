#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyOptionTorpedoController::MyOptionTorpedoController(const char* prm_name, MyOptionLockonController* prm_pLockonController)
                                                                                  : GgafDummyActor(prm_name) {
    _class_name = "MyOptionTorpedoController";
    _length_TorpedoChip = 5;
    _papLaserChipDispatcher = NEW LaserChipDispatcher*[MyOption::_max_lockon_num];
    _pa_all_employed = NEW bool[MyOption::_max_lockon_num];
    _papMyTorpedoChip_Head = NEW MyTorpedoChip*[MyOption::_max_lockon_num];
    for (int i = 0; i < MyOption::_max_lockon_num; i++) {
        _pa_all_employed[i] = false;
        _papLaserChipDispatcher[i] = NEW LaserChipDispatcher("DP");
        _papLaserChipDispatcher[i]->config(_length_TorpedoChip, 10, NULL);


        for (int j = 0; j < _length_TorpedoChip; j++) {
            stringstream name;
            name <<  "Torpedo["<<i<<"]["<<j<<"]";
            MyTorpedoChip* pChip = NEW MyTorpedoChip(name.str().c_str());
            if (j == 0) {
                //ŽÀŽ¿‚Ìæ“ªH

            }
            pChip->inactivateImmediately();
            _papLaserChipDispatcher[i]->addSubLast(pChip);
        }
        addSubGroup(_papLaserChipDispatcher[i]);
    }
    _firing_num = 0;
    _in_firing = false;
    _pLockonController = prm_pLockonController;

}

void MyOptionTorpedoController::initialize() {
}

void MyOptionTorpedoController::processBehavior() {
    if (_in_firing) {
        _in_firing = false;
        for (int i = 0; i < _firing_num; i++) {
            if (_pa_all_employed[i]) {
                //”­ŽËŒã
                if (_papLaserChipDispatcher[i]->_num_chip_active > 0) {
                    _in_firing = true;
                }
            } else {
                //”­ŽË’†
                MyTorpedoChip* pTorpedoChip = (MyTorpedoChip*)_papLaserChipDispatcher[i]->employ();
                if (pTorpedoChip != NULL) {
                    pTorpedoChip->setGeometry(pMYSHIP);
                    pTorpedoChip->_pMover->setMvAng(((MyOption*)getParent()));
                    pTorpedoChip->activate();
                    if (pTorpedoChip->_pChip_front &&  pTorpedoChip->_pChip_front->_pChip_front == NULL) {
                        _papMyTorpedoChip_Head[i] = pTorpedoChip;
                    }
                    _in_firing = true;
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
        _firing_num = _pLockonController->_pRingTarget->length();
        if (_firing_num == 0) {
            //_firing_num = 1;
        } else {
            for (int i = 0; i < _firing_num; i++) {
                MyTorpedoChip* pHead = (MyTorpedoChip*)_papLaserChipDispatcher[i]->getSubFirst();
                pHead->_pTarget = _pLockonController->_pRingTarget->getNext(i);
            }
            _in_firing = true;
        }
    }
}


MyOptionTorpedoController::~MyOptionTorpedoController() {
}
