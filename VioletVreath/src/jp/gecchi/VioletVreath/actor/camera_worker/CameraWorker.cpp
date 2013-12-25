#include "stdafx.h"
#include "CameraWorker.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/actor/ViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverHelperA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperB.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CameraWorker::CameraWorker(const char* prm_name) : GgafMainActor(prm_name, nullptr) {
    _class_name = "CameraWorker";
    t_x_VP_ =  0;
    t_y_VP_ =  0;
    t_z_VP_ =  0;
    t_x_CAM_ =  0;
    t_y_CAM_ =  0;
    t_z_CAM_ =  0;
    frame_of_behaving_since_onSwitch_ = 0;
    pCam_ = nullptr;
    pVp_ = nullptr;
    t_cam_up_face_ = 2;

    //���ӁFCamera�͂܂���������Ă��Ȃ����߂�����P_CAM�͎g�p�s��
}

void CameraWorker::initialize() {
    pCam_ = P_CAM;
    pVp_ = (ViewPoint*)(pCam_->getViewPoint());
    t_x_VP_ = pVp_->_x;
    t_y_VP_ = pVp_->_y;
    t_z_VP_ = pVp_->_z;
    t_x_CAM_ = pCam_->_x;
    t_y_CAM_ = pCam_->_y;
    t_z_CAM_ = pCam_->_z;
    t_cam_up_face_ = pCam_->up_face_;
}
void CameraWorker::onActive() {
    //���݂̃^�[�Q�b�g���ă^�[�Q�b�g
    slideMvCamTo(t_x_CAM_, t_y_CAM_, t_z_CAM_, 60);
    slideMvVpTo(t_x_VP_, t_y_VP_, t_z_VP_, 60);
}

void CameraWorker::onSwitchCameraWork() {
    //frame_of_behaving_since_onSwitch_ = 0; �� Universe::switchCameraWork() ���s���B
}

void CameraWorker::onUndoCameraWork() {
}

void CameraWorker::onSwitchToOtherCameraWork() {
}

void CameraWorker::onCameBackFromOtherCameraWork() {
}

void CameraWorker::processBehavior() {
    behaveAutoCamUp();
}

void CameraWorker::slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvCamTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}
void CameraWorker::slideMvVpTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvVpTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}
void CameraWorker::slideMvCamTo(coord tx, coord ty, coord tz, frame t) {
    t_x_CAM_ = tx;
    t_y_CAM_ = ty;
    t_z_CAM_ = tz;
    pCam_->slideMvTo(tx, ty, tz, t);
}
void CameraWorker::slideMvVpTo(coord tx, coord ty, coord tz, frame t) {
    t_x_VP_ = tx;
    t_y_VP_ = ty;
    t_z_VP_ = tz;
    pVp_->slideMvTo(tx, ty, tz, t);
}
void CameraWorker::behaveAutoCamUp() {
#ifdef MY_DEBUG
    int bk_up_face_ = pCam_->up_face_;
#endif
    if (pCam_->vcv_face_ != pCam_->vcv_face_prev_) {
        GgafDxAxesMoverHelperA* hlprA = pCam_->pAxsMver_->hlprA();
        int fx = hlprA->_smthVxMv._prm._flg ? hlprA->_smthVxMv._prm._target_frames : 10;
        int fy = hlprA->_smthVyMv._prm._flg ? hlprA->_smthVyMv._prm._target_frames : 10;
        int fz = hlprA->_smthVzMv._prm._flg ? hlprA->_smthVzMv._prm._target_frames : 10;
        frame up_frames = (frame)(MAX3(fx,fy,fz) / 2) ; //�����̃t���[�����Ԃ�UP�ύX������������
        if (pCam_->vcv_face_ == pCam_->up_face_) {
            //����UP(up_face_)�̖ʂɃJ���������_�x�N�g��(vcv_face_)���˂��h����ꍇ
            //�ȑO�̃J���������_(vcv_face_prev_) �̐^���̖ʂ�UP���ړ�
            pCam_->slideUpCamTo(7 - pCam_->vcv_face_prev_, up_frames);
        } else if (pCam_->vcv_face_ == 7 - pCam_->up_face_) {  //up_face_�̗���
             //����UP(up_face_)�̖ʂ̐^���ɃJ���������_�x�N�g��(vcv_face_)���˂��h����ꍇ
             //�ȑO�̃J���������_(vcv_face_prev_) �̖ʂ�UP�ɕύX
            pCam_->slideUpCamTo(pCam_->vcv_face_prev_, up_frames);
        } else {
            //�ω����Ȃ�
            pCam_->slideUpCamTo(pCam_->up_face_, up_frames);
        }
        _TRACE_("CameraWorker::behaveAutoCamUp() up_frames="<<up_frames<<" vcv="<<pCam_->vcv_face_prev_<<"��"<<pCam_->vcv_face_<<" up_face_="<<bk_up_face_<<"��"<<pCam_->up_face_<<"");
    }
//    _TRACE_("cam=("<<_x<<","<<_y<<","<<_z<<") vp=("<< pVP->_x <<","<< pVP->_y <<","<< pVP->_z <<")  UP=("<< pUp_->_x <<","<< pUp_->_y <<","<< pUp_->_z <<") CAM_UP=("<< _pVecCamUp->x <<","<< _pVecCamUp->y <<","<< _pVecCamUp->z <<")");
//    _TRACE_("vcv="<<vcv_face_prev_<<"��"<<vcv_face_<<" up_face_="<<bk_up_face_<<"��"<<up_face_<<"");
}
CameraWorker::~CameraWorker() {

}
