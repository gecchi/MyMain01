#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _TRACE_("World::World");

    //�y�߂��z
    //������Actor��Scene��NEW���͂��Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
}

void World::initialize() {
        _TRACE_("World::initialize()");
    GameScene* pGameScene = NEW GameScene("Game");
    addSubLast(pGameScene);
#ifdef OREDEBUG
    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "B/moji");
    getLordActor()->accept(KIND_EFFECT, pDispFpsActor);
#endif
_TRACE_("GgafDx9Universe::_pCamera="<<GgafDx9Universe::_pCamera);

}



void World::processBehavior() {
    VB::update(); //���͏��X�V


    //TODO:�~�߂Ă�frame�͐i�ށQ�H
    if (VB::isPushedDown(VB_PAUSE)) {
        if (getSubFirst()->isBehaving()) {
            _TRACE_("PAUSE!");
            getSubFirst()->pause();     //�ꎞ��~
        } else {
            _TRACE_("UNPAUSE!");
            getSubFirst()->unpause();   //�ꎞ��~����
        }
    }

    //�T�u�V�[�����ꎞ��~���Ă���΁A�J��������ł���B
    if ( getSubFirst()->isBehaving() ) {
        //�X���[
    } else {
        GgafDx9Universe::_pCamera->_pMover->_move_angle_rz_target_flg = true;
        GgafDx9Universe::_pCamera->_pMover->_move_angle_ry_target_flg = true;

        if (GgafDx9Input::isBeingPressedKey(DIK_SPACE)) {
            if (GgafDx9Input::isBeingPressedKey(DIK_T)) {
                GgafDx9Universe::_pCamera->_Y += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_G)) {
                GgafDx9Universe::_pCamera->_Y -= 2000;
            } else {

            }

            if (GgafDx9Input::isBeingPressedKey(DIK_H)) {
                GgafDx9Universe::_pCamera->_X += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_F)) {
                GgafDx9Universe::_pCamera->_X -= 2000;
            } else {
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_U)) {
                GgafDx9Universe::_pCamera->_Z += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_J)) {
                GgafDx9Universe::_pCamera->_Z -= 2000;
            } else {
            }

        } else {
            if (GgafDx9Input::isBeingPressedKey(DIK_T)) {
                GgafDx9Universe::_pCamera->_pMover->addRzMoveAngle(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_G)) {
                GgafDx9Universe::_pCamera->_pMover->addRzMoveAngle(-2000);
            } else {
                GgafDx9Universe::_pCamera->_pMover->addRzMoveAngle(0);
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_H)) {
                GgafDx9Universe::_pCamera->_pMover->addRyMoveAngle(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_F)) {
                GgafDx9Universe::_pCamera->_pMover->addRyMoveAngle(-2000);
            } else {
                GgafDx9Universe::_pCamera->_pMover->addRyMoveAngle(0);
            }
            if (GgafDx9Input::isBeingPressedKey(DIK_U)) {
                GgafDx9Universe::_pCamera->_pMover->setMoveVelocity(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_J)) {
                GgafDx9Universe::_pCamera->_pMover->setMoveVelocity(-2000);
            } else {
                GgafDx9Universe::_pCamera->_pMover->setMoveVelocity(0);
            }
        }
    }

    //�J�������������ݒ�
    GgafDx9Universe::_pCamera->setGaze (
               GgafDx9Universe::_pCamera->_X + (GgafDx9Universe::_pCamera->_pMover->_vX * LEN_UNIT * PX_UNIT),
               GgafDx9Universe::_pCamera->_Y + (GgafDx9Universe::_pCamera->_pMover->_vY * LEN_UNIT * PX_UNIT),
               GgafDx9Universe::_pCamera->_Z + (GgafDx9Universe::_pCamera->_pMover->_vZ * LEN_UNIT * PX_UNIT)
              );
    if ( getSubFirst()->isBehaving() ) {
        //�X���[
    } else {
        if (GgafDx9Input::isBeingPressedKey(DIK_O)) {
            GgafDx9Universe::_pCamera->_pMover->setMoveAngle(0,0,0);
        }
    }

}

void World::processJudgement() {
}

World::~World() {
}
