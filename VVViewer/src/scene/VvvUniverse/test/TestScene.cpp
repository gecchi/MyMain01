
#include <actor/test/VecEyeActor.h>
#include <actor/test/VecUpActor.h>
#include <GgafCommonHeader.h>
#include <jp/ggaf/core/actor/GgafSceneDirector.h>
#include <jp/ggaf/lib/util/RhombicuboctahedronUtil.h>
#include <jp/ggaf/lib/util/StgUtil.h>
#include <scene/VvvUniverse/test/TestScene.h>
#include <iostream>

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

#define TN(X,Y,Z) (((3*3)*((X)+1)) + (3*((Y)+1)) + ((Z)+1))

TestScene::TestScene(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    _pVecUpActor = NEW VecUpActor("VecUp");
    getSceneDirector()->addSubGroup(_pVecUpActor);
    _pVecEyeActor = NEW VecEyeActor("VecEyeActor");
    getSceneDirector()->addSubGroup(_pVecEyeActor);
}

void TestScene::initialize() {
}

void TestScene::processBehavior() {
    int eye_face_no = TN(_pVecEyeActor->_hx, _pVecEyeActor->_hy, _pVecEyeActor->_hz);
    int up_face_no = TN(_pVecUpActor->_hx, _pVecUpActor->_hy, _pVecUpActor->_hz);
    _TRACE_("UP("<<_pVecUpActor->_hx<<","<< _pVecUpActor->_hy<<","<<_pVecUpActor->_hz<<")  EYE("<<_pVecEyeActor->_hx<<","<< _pVecEyeActor->_hy<<","<<_pVecEyeActor->_hz<<")");

    int up_face_no_next = RhombicuboctahedronUtil::relation_up_vec[up_face_no][eye_face_no];
    if (up_face_no_next != up_face_no) {

        int hx, hy, hz;
        RhombicuboctahedronUtil::cnvFaceNo2Sgn(up_face_no_next, hx, hy, hz);
        _pVecUpActor->_hx = hx;
        _pVecUpActor->_hy = hy;
        _pVecUpActor->_hz = hz;
        _TRACE_(" UPìÆÇ©Ç»ÇØÇÍÇŒÅ®Åi"<<hx<<","<<hy<<","<<hz<<")");
    }

}

TestScene::~TestScene() {
}
