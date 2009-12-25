#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01Scene::Stage01Scene(const char* prm_name) : StageScene(prm_name) {
    _pStage01Main = NEW Stage01MainScene("Stage01Main");
    _pStage01Main->inactivate();
    addSubLast(_pStage01Main);
    Sleep(2);
    _pBackGround01 = NEW BackGround01("BACKGOROUND01", "");
    _pBackGround01->inactivateTree();
    getLordActor()->addSubGroup(KIND_EFFECT, _pBackGround01);
    _pBackGroundStar =  NEW BackGroundStar("BackGroundStarP");
    _pBackGroundStar->inactivateTree();
    getLordActor()->addSubGroup(KIND_EFFECT, _pBackGroundStar);
    _angCamZX_prev = 0;
    _angCamXY_prev = 0;

    _pBgmCon_st1 = (GgafDx9BgmConnection*)GgafDx9Sound::_pBgmManager->connect("VIRTUAL_ON_11");
    //GameMainScene���������Ă����
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::initialize() {
    _angCamZX_prev = GgafDx9Util::getAngle2D(-(pCAM->_pVecCamLookatPoint->x - pCAM->_pVecCamFromPoint->x),
                                                     -(pCAM->_pVecCamLookatPoint->z - pCAM->_pVecCamFromPoint->z)
                                                    );
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::processBehavior() {


    if (getProgress() == STAGE01_PROG_INIT) {
        setProgress(STAGE01_PROG_BEGIN);
    }
    if (onChangeProgressAt(STAGE01_PROG_BEGIN)) {

        _pBgmCon_st1->view()->play(true);
        _dwFrame_Begin = 0;
    } else if (getProgress() == GAMEDEMO_PROG_BEGIN) {
        //�^�C�g���������[�v
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 120) { //�X�e�[�W�P�J�n�I
            _pBackGround01->activateTree();
            _pBackGroundStar->activateTree();
            _pStage01Main->activate();
            setProgress(STAGE01_PROG_PLAY);
        }
    } else if (getProgress() == STAGE01_PROG_PLAY) {
        angle angCamXZ = GgafDx9Util::getAngle2D(
                             pCAM->_X - pCAM->_pViewPoint->_X,
                             pCAM->_Z - pCAM->_pViewPoint->_Z
                         );
        angle angCamXY = GgafDx9Util::getAngle2D(
                             pCAM->_X - pCAM->_pViewPoint->_X,
                             pCAM->_Y - pCAM->_pViewPoint->_Y
                         );
        _pBackGround01->_inc_x = GgafDx9Util::getDiffAngle(_angCamZX_prev, angCamXZ) * (1.0*GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH)/(ANGLE90*0.5));
        _pBackGround01->_inc_y = GgafDx9Util::getDiffAngle(_angCamXY_prev, angCamXY) * (1.0*GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT)/(ANGLE90*0.5));
        //* (1.0*GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH)/ANGLE90 �� 90�x�J�������񂷂Ɣw�i���P�T����v�Z(1��ʕ������j�B
        //���ۂɂ�2��ʂقǔw�i�͓����Ǝv���̂Ł~0.5
        _angCamZX_prev = angCamXZ;
        _angCamXY_prev = angCamXY;

        if (pWORLD->_pos_camera == CAM_POS_RIGHT) {
            _pBackGround01->_x -= 0.1; //�w�i�X�N���[��
        } else if (pWORLD->_pos_camera == CAM_POS_LEFT) {
            _pBackGround01->_x += 0.1;
        } else if (pWORLD->_pos_camera == CAM_POS_TOP) {
            _pBackGround01->_y += 0.1;
        } else if (pWORLD->_pos_camera == CAM_POS_BOTTOM) {
            _pBackGround01->_y -= 0.1;
        }


    }



}

void Stage01Scene::processJudgement() {
}

void Stage01Scene::processFinal() {

}

Stage01Scene::~Stage01Scene() {
    _pBgmCon_st1->close();
}
