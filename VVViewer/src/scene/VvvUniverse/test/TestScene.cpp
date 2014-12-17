
#include <actor/test/VecEyeActor.h>
#include <actor/test/VecUpActor.h>
#include <GgafCommonHeader.h>
#include <jp/ggaf/core/actor/GgafSceneDirector.h>
#include <jp/ggaf/lib/util/DirectionUtil.h>
#include <jp/ggaf/lib/util/StgUtil.h>
#include <scene/VvvUniverse/test/TestScene.h>
#include <iostream>

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;


TestScene::TestScene(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    _pVecUpActor = NEW VecUpActor("VecUp");
    getSceneDirector()->addSubGroup(_pVecUpActor);
    _pVecEyeActor = NEW VecEyeActor("VecEyeActor");
    getSceneDirector()->addSubGroup(_pVecEyeActor);
}

void TestScene::initialize() {
}

void TestScene::processBehavior() {
    float eye_vx,eye_vy,eye_vz;
    UTIL::convRzRyToVector(_pVecEyeActor->_rz, _pVecEyeActor->_ry, eye_vx,eye_vy,eye_vz);
    int eye_face_no = DirectionUtil::cnvVec2FaceNo(eye_vx,eye_vy,eye_vz);
    int eye_hx, eye_hy, eye_hz;
    DirectionUtil::cnvFaceNo2Sgn(eye_face_no, eye_hx, eye_hy, eye_hz);

    int up_hx, up_hy, up_hz;
    DirectionUtil::cnvFaceNo2Sgn(_pVecUpActor->up_face_no_, up_hx, up_hy, up_hz);

    _TRACE_("UP["<<_pVecUpActor->up_face_no_<<"]("<<up_hx<<","<< up_hy<<","<<up_hz<<")  EYE["<<eye_face_no<<"]("<<eye_hx<<","<< eye_hy<<","<<eye_hz<<")");

    int up_face_no_next = DirectionUtil::_relation_up_by_vec[_pVecUpActor->up_face_no_][eye_face_no];
    if (up_face_no_next != DirectionUtil::FACE_XXX && up_face_no_next != _pVecUpActor->up_face_no_) {
        int hx, hy, hz;
        DirectionUtil::cnvFaceNo2Sgn(up_face_no_next, hx, hy, hz);
        _pVecUpActor->up_face_no_ = up_face_no_next;
        _TRACE_(" UPìÆÇ©Ç»ÇØÇÍÇŒÅ®["<<up_face_no_next<<"]Åi"<<hx<<","<<hy<<","<<hz<<")");
    }

}

TestScene::~TestScene() {
}
