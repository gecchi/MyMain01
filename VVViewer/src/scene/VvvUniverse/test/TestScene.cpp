
#include <actor/test/VecEyeActor.h>
#include <actor/test/VecUpActor.h>
#include <GgafCommonHeader.h>
#include <jp/ggaf/core/actor/GgafSceneDirector.h>
#include <jp/ggaf/lib/util/StgUtil.h>
#include <scene/VvvUniverse/test/TestScene.h>
#include <iostream>

#include "scene/VvvUniverse.h"

#include "jp/ggaf/dxcore/util/GgafDxDirectionUtil.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;


TestScene::TestScene(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    _pVecUpActor = NEW VecUpActor("VecUp");
    getSceneDirector()->addSubGroup(_pVecUpActor);
    _pVecEyeActor = NEW VecEyeActor("VecEyeActor");
    getSceneDirector()->addSubGroup(_pVecEyeActor);
    eye_face_no_ = 0;
    eye_face_no_prev_ = 0;
}

void TestScene::initialize() {
}

void TestScene::processBehavior() {
    float eye_vx,eye_vy,eye_vz;
    UTIL::convRzRyToVector(_pVecEyeActor->_rz, _pVecEyeActor->_ry, eye_vx,eye_vy,eye_vz);
    eye_face_no_ = GgafDxDirectionUtil::cnvVec2FaceNo(eye_vx,eye_vy,eye_vz);

    if (eye_face_no_ != eye_face_no_prev_) {
//        _TRACE_(" UP�����\���I");
        int eye_hx_prev, eye_hy_prev, eye_hz_prev;
        GgafDxDirectionUtil::cnvFaceNo2Sgn(eye_face_no_prev_, eye_hx_prev, eye_hy_prev, eye_hz_prev);
        int eye_hx, eye_hy, eye_hz;
        GgafDxDirectionUtil::cnvFaceNo2Sgn(eye_face_no_, eye_hx, eye_hy, eye_hz);
//        _TRACE_("EYE["<<eye_face_no_prev_<<"]("<<eye_hx_prev<<","<< eye_hy_prev<<","<<eye_hz_prev<<") �� ["<<eye_face_no_<<"]("<<eye_hx<<","<< eye_hy<<","<<eye_hz<<")");

        int up_hx_now, up_hy_now, up_hz_now;
        GgafDxDirectionUtil::cnvFaceNo2Sgn(_pVecUpActor->up_face_no_, up_hx_now, up_hy_now, up_hz_now);
        int up_face_no_next = P_CAM->relation_up_by_vec_[_pVecUpActor->up_face_no_][eye_face_no_];
        if (up_face_no_next != GgafDxDirectionUtil::FACE_XXX) {
            if (up_face_no_next != GgafDxDirectionUtil::FACE_ZZZ) {
                int up_hx_next, up_hy_next, up_hz_next;
                GgafDxDirectionUtil::cnvFaceNo2Sgn(up_face_no_next, up_hx_next, up_hy_next, up_hz_next);
//                _TRACE_("UP["<<_pVecUpActor->up_face_no_<<"]("<<up_hx_now<<","<< up_hy_now<<","<<up_hz_now<<") �� ["<<up_face_no_next<<"]("<<up_hx_next<<","<< up_hy_next<<","<<up_hz_next<<")");
                _pVecUpActor->up_face_no_ = up_face_no_next; //UP���X�V
            } else {
                //�����Ɖ��̂�UP�Əd�Ȃ������BUP�̔w�ʕ����֍s���Ă��܂����B
                //���̏ꍇ�́A�ړ�����O��EYE�x�N�g�����̗p���Ă݂�B
                int other_up_face_no_next = P_CAM->relation_up_by_vec_[_pVecUpActor->up_face_no_][eye_face_no_prev_];
//                _TRACE_("�����ƁAUP�Əd�Ȃ������BUP�̔w�ʕ����֍s���Ă��܂����̂ŁA�ړ��O�̒��O��EYE�x�N�g����");
//                _TRACE_("EYE["<<eye_face_no_prev_<<"]("<<eye_hx_prev<<","<< eye_hy_prev<<","<<eye_hz_prev<<") �Ŏ���UP���l����");
                if (other_up_face_no_next != GgafDxDirectionUtil::FACE_XXX) {
                    if (other_up_face_no_next != GgafDxDirectionUtil::FACE_ZZZ) {
                        int up_hx_next, up_hy_next, up_hz_next;
                        GgafDxDirectionUtil::cnvFaceNo2Sgn(other_up_face_no_next, up_hx_next, up_hy_next, up_hz_next);
//                        _TRACE_("UP["<<_pVecUpActor->up_face_no_<<"]("<<up_hx_now<<","<< up_hy_now<<","<<up_hz_now<<") �� ["<<other_up_face_no_next<<"]("<<up_hx_next<<","<< up_hy_next<<","<<up_hz_next<<") �ł������Ƃ肠����");
                        _pVecUpActor->up_face_no_ = other_up_face_no_next; //UP���X�V
                    } else {
//                        _TRACE_("���₻��ł��_�����B�P�W�O�x��C�ɓ������H�A�����s���܂���B");
                    }
                } else {
//                    _TRACE_("����A�������� UP["<<_pVecUpActor->up_face_no_<<"]("<<up_hx_now<<","<< up_hy_now<<","<<up_hz_now<<") UP�͂��̂܂ܓ������I");
                }
            }
        } else {
//            _TRACE_("UP["<<_pVecUpActor->up_face_no_<<"]("<<up_hx_now<<","<< up_hy_now<<","<<up_hz_now<<") UP�͂��̂܂ܓ������I");
        }
    }
    eye_face_no_prev_ = eye_face_no_;

}

TestScene::~TestScene() {
}
