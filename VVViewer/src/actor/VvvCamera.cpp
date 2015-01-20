#include "VvvCamera.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "actor/VvvCameraViewPoint.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

#include "jp/ggaf/dxcore/util/GgafDxDirectionUtil.h"

#include "VvvCameraUpVector.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvCamera::VvvCamera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "VvvCamera";
    pAxsMver_ = NEW GgafDxAxesMover(this);

    vcv_face_ = 0;
    vcv_face_prev_ = vcv_face_;


    for (int i = 0; i < 3*3*3; i++) {
        for (int j = 0; j < 3*3*3; j++) {
            relation_up_vec_[i][j] = GgafDxDirectionUtil::FACE_XXX;
        }
    }
    relation_up_by_vec_ =  (int (*)[3*3*3])(&(relation_up_vec_[13][13])); //13 は 3*3*3=27 の真ん中の要素、_relation_up_vec[-13～13][-13～13]でアクセスする為

    relation_up_by_vec_[TN( 1, 0, 0)][TN( 1,-1,-1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN( 1, 0, 0)][TN( 1,-1, 0)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 1, 0, 0)][TN( 1,-1, 1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 0,-1)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 0, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 0, 1)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 1,-1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 1, 0)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 1, 1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN( 1, 0, 0)][TN(-1,-1,-1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN( 1, 0, 0)][TN(-1,-1, 0)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 1, 0, 0)][TN(-1,-1, 1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 0,-1)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 0, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 0, 1)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 1,-1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 1, 0)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 1, 1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN(-1,-1,-1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN(-1,-1, 0)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN(-1, 0, 0)][TN(-1,-1, 1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 0,-1)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 0, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 0, 1)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 1,-1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 1, 0)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 1, 1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN( 1,-1,-1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN( 1,-1, 0)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN(-1, 0, 0)][TN( 1,-1, 1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 0,-1)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 0, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 0, 1)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 1,-1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 1, 0)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 1, 1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN(-1, 1,-1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN(-1, 1, 0)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 0, 1, 0)][TN(-1, 1, 1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 0, 1,-1)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 0, 1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 0, 1, 1)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 1, 1,-1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 1, 1, 0)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 1, 1, 1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN(-1,-1,-1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN(-1,-1, 0)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN( 0, 1, 0)][TN(-1,-1, 1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 0,-1,-1)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 0,-1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 0,-1, 1)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 1,-1,-1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 1,-1, 0)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 0, 1, 0)][TN( 1,-1, 1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN(-1,-1,-1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN(-1,-1, 0)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 0,-1, 0)][TN(-1,-1, 1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 0,-1,-1)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 0,-1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 0,-1, 1)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 1,-1,-1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 1,-1, 0)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 1,-1, 1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN(-1, 1,-1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN(-1, 1, 0)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN( 0,-1, 0)][TN(-1, 1, 1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 0, 1,-1)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 0, 1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 0, 1, 1)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 1, 1,-1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 1, 1, 0)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 0,-1, 0)][TN( 1, 1, 1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN(-1,-1, 1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 0, 1)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 1, 1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 0,-1, 1)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 0, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 1, 1)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 1,-1, 1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 0, 1)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 1, 1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN(-1,-1,-1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 0,-1)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 1,-1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 0,-1,-1)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 0,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 1,-1)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 1,-1,-1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 0,-1)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 1,-1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN(-1,-1,-1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 0,-1)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 1,-1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 0,-1,-1)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 0,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 1,-1)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 1,-1,-1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 0,-1)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 1,-1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN(-1,-1, 1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 0, 1)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 1, 1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 0,-1, 1)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 0, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 1, 1)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 1,-1, 1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 0, 1)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 1, 1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 0, 1,-1)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 0, 1, 0)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 0, 1, 1)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 0,-1)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 0, 0)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 0, 1)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 1,-1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 1, 1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN(-1,-1,-1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN(-1,-1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1, 1, 0)][TN(-1,-1, 1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN(-1, 0,-1)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN(-1, 0, 0)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN( 1, 1, 0)][TN(-1, 0, 1)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 0,-1,-1)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 0,-1, 0)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1, 1, 0)][TN( 0,-1, 1)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN(-1,-1,-1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN(-1,-1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1,-1, 0)][TN(-1,-1, 1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN(-1, 0,-1)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN(-1, 0, 0)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN(-1,-1, 0)][TN(-1, 0, 1)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 0,-1,-1)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 0,-1, 0)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 0,-1, 1)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 0, 1,-1)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 0, 1, 0)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 0, 1, 1)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 0,-1)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 0, 0)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 0, 1)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 1,-1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 1, 1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 0,-1, 1)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 0, 1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 1, 1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 1,-1, 0)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 0, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 1, 0)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 1,-1, 1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 0, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 1, 1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 1, 0, 1)][TN(-1,-1,-1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 0,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 1,-1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN( 1, 0, 1)][TN(-1,-1, 0)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 0, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 1, 0)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 0,-1,-1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 0,-1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 1,-1)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN(-1, 0,-1)][TN(-1,-1,-1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 0,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 1,-1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN(-1, 0,-1)][TN(-1,-1, 0)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 0, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 1, 0)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 0,-1,-1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 0,-1)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 1,-1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 0,-1, 1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 0, 1)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 1, 1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 1,-1, 0)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 0, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 1, 0)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 1,-1, 1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 0, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 1, 1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 0, 1)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 0, 1)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 0, 1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 1, 0)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 1, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 1, 0)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 1, 1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 1, 1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN( 0, 1, 1)][TN(-1,-1,-1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 0,-1,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 1,-1,-1)] = TN( 1, 1, 1);
    relation_up_by_vec_[TN( 0, 1, 1)][TN(-1,-1, 0)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 0,-1, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 1,-1, 0)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 0,-1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 0,-1)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 0,-1)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 0,-1,-1)][TN(-1,-1,-1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 0,-1,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 1,-1,-1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN( 0,-1,-1)][TN(-1,-1, 0)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 0,-1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 1,-1, 0)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 0,-1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 0,-1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 0,-1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 0, 1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 0, 1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 0, 1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 1, 0)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 1, 0)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 1, 1)] = TN(-1,-1,-1);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 1, 1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 0, 1,-1)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 0, 1, 0)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 0, 1, 1)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 0,-1)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 0, 0)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 0, 1)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 1,-1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 1, 1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 1,-1,-1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 1,-1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 1,-1, 1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 1, 0,-1)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 1, 0, 0)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 1, 0, 1)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 0,-1,-1)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 0,-1, 0)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1, 1, 0)][TN( 0,-1, 1)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 1, 0,-1)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 1, 0, 0)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 1, 0, 1)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 0,-1,-1)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 0,-1, 0)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 0,-1, 1)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 1,-1,-1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 1,-1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 1,-1, 1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 1,-1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 1, 0)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 1, 1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 0, 1,-1)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 0, 1, 0)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1,-1, 0)][TN( 0, 1, 1)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 0,-1)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 0, 0)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 0, 1)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 0,-1, 1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 0, 1)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 1, 1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN(-1, 0, 1)][TN(-1,-1, 0)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 0, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 1, 0)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN(-1, 0, 1)][TN(-1,-1, 1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 0, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 1, 1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 1,-1,-1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 0,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 1,-1)] = TN(-1, 1, 1);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 1,-1, 0)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 0, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 1, 0)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 0,-1,-1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 0,-1)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 1,-1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 1,-1, 0)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 0, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 1, 0)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 0,-1,-1)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 0,-1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 1,-1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 1,-1,-1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 0,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 1,-1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN( 1, 0,-1)][TN(-1,-1, 1)] = TN( 1,-1,-1);
    relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 0, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 1, 1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 0,-1, 1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 0, 1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 1, 1)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 1, 0,-1)][TN(-1,-1, 0)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 0, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 1, 0)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 0, 1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 0, 1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 0, 1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN( 0,-1, 1)][TN(-1,-1, 0)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 0,-1, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 1,-1, 0)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN( 0,-1, 1)][TN(-1,-1, 1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 0,-1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 1,-1, 1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 1,-1)] = TN(-1,-1, 1);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 1,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 1,-1)] = TN( 1,-1, 1);
    relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 1, 0)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 1, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 1, 0)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 0,-1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 0,-1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 0,-1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 1, 0)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 1, 0)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 0,-1)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 0,-1)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 0,-1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 1,-1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 1,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 1,-1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN( 0, 1,-1)][TN(-1,-1, 1)] = TN(-1, 1,-1);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 0,-1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 1,-1, 1)] = TN( 1, 1,-1);
    relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 0, 1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 0, 1)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 0, 1)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 0, 1,-1)][TN(-1,-1, 0)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 0,-1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN( 0, 1,-1)][TN( 1,-1, 0)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 1, 1, 1)][TN( 0, 0, 1)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 1, 1, 1)][TN( 0, 1, 0)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 1, 1, 1)][TN( 0, 1, 1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 0, 0)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 0, 1)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 1, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1, 1, 1)][TN( 0,-1, 0)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 1, 1, 1)][TN( 0,-1,-1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1, 1, 1)][TN(-1, 0, 0)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN( 1, 1, 1)][TN(-1, 0,-1)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN( 1, 1, 1)][TN(-1,-1, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN( 1, 1, 1)][TN(-1,-1,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1,-1,-1)][TN( 0, 0,-1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN(-1,-1,-1)][TN( 0,-1,-1)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1,-1,-1)][TN(-1, 0, 0)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN(-1,-1,-1)][TN(-1, 0,-1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN(-1,-1,-1)][TN(-1,-1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN(-1,-1,-1)][TN(-1,-1,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1,-1,-1)][TN( 0, 0, 1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN(-1,-1,-1)][TN( 0, 1, 0)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 0, 0)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 0, 1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 0,-1)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 1, 0)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 1,-1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1, 1,-1)][TN( 1, 0,-1)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN( 1, 1,-1)][TN( 1, 1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN( 1, 1,-1)][TN( 1, 1,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 0, 1)] = TN( 1, 1, 0);
    relation_up_by_vec_[TN( 1, 1,-1)][TN( 0,-1, 0)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 1, 1,-1)][TN( 0,-1, 1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1, 1,-1)][TN(-1, 0, 0)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN( 1, 1,-1)][TN(-1,-1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN( 1, 1,-1)][TN(-1,-1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 0, 1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN(-1,-1, 1)][TN( 0,-1, 0)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN(-1,-1, 1)][TN( 0,-1, 1)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1,-1, 1)][TN(-1, 0, 0)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN(-1,-1, 1)][TN(-1, 0, 1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN(-1,-1, 1)][TN(-1,-1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 0,-1)] = TN(-1,-1, 0);
    relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 1, 0)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 1,-1)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 0, 0)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 0,-1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 1, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 1,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 0, 1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 1,-1, 1)][TN( 0,-1, 0)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 1,-1, 1)][TN( 0,-1, 1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1,-1, 1)][TN( 1, 0, 0)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN( 1,-1, 1)][TN( 1, 0, 1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN( 1,-1, 1)][TN( 1,-1, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN( 1,-1, 1)][TN( 1,-1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 0,-1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 1, 0)] = TN( 1, 0, 1);
    relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 1,-1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 0, 0)] = TN( 0,-1, 1);
    relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 0,-1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 1, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 1,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 0,-1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 1, 0)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 1,-1)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 0, 0)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 0,-1)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 1,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 0, 1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN(-1, 1,-1)][TN( 0,-1, 0)] = TN(-1, 0,-1);
    relation_up_by_vec_[TN(-1, 1,-1)][TN( 0,-1, 1)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1, 1,-1)][TN( 1, 0, 0)] = TN( 0, 1,-1);
    relation_up_by_vec_[TN(-1, 1,-1)][TN( 1, 0, 1)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN(-1, 1,-1)][TN( 1,-1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN(-1, 1,-1)][TN( 1,-1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 0,-1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 1,-1,-1)][TN( 0,-1, 0)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 1,-1,-1)][TN( 0,-1,-1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1,-1,-1)][TN( 1, 0, 0)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN( 1,-1,-1)][TN( 1, 0,-1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN( 1,-1,-1)][TN( 1,-1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN( 1,-1,-1)][TN( 1,-1,-1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 0, 1)] = TN( 1,-1, 0);
    relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 1, 0)] = TN( 1, 0,-1);
    relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 1, 1)] = TN( 1, 0, 0);
    relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 0, 0)] = TN( 0,-1,-1);
    relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 0, 1)] = TN( 0,-1, 0);
    relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 1, 0)] = TN( 0, 0,-1);
    relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 0, 1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 1, 0)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 1, 1)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 0, 0)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 0, 1)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 1, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 1, 1)] = TN( 0, 0, 0);
    relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 0,-1)] = TN(-1, 1, 0);
    relation_up_by_vec_[TN(-1, 1, 1)][TN( 0,-1, 0)] = TN(-1, 0, 1);
    relation_up_by_vec_[TN(-1, 1, 1)][TN( 0,-1,-1)] = TN(-1, 0, 0);
    relation_up_by_vec_[TN(-1, 1, 1)][TN( 1, 0, 0)] = TN( 0, 1, 1);
    relation_up_by_vec_[TN(-1, 1, 1)][TN( 1, 0,-1)] = TN( 0, 1, 0);
    relation_up_by_vec_[TN(-1, 1, 1)][TN( 1,-1, 0)] = TN( 0, 0, 1);
    relation_up_by_vec_[TN(-1, 1, 1)][TN( 1,-1,-1)] = TN( 0, 0, 0);

    auto_up_wait_frames = 0;
}

GgafDxCameraViewPoint* VvvCamera::createCameraViewPoint() {
    VvvCameraViewPoint* pVP = NEW VvvCameraViewPoint("VvvCameraViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}

GgafDxCameraUpVector* VvvCamera::createCameraUpVector() {
    VvvCameraUpVector* pUp = NEW VvvCameraUpVector("VvvCameraUpVector");
    return (GgafDxCameraUpVector*)pUp;
}

void VvvCamera::initialize() {
    DefaultCamera::initialize();
}

void VvvCamera::processBehavior() {
    VvvCameraViewPoint* pVP = (VvvCameraViewPoint*)getCameraViewPoint();
    VvvCameraUpVector* pUpV = (VvvCameraUpVector*)getCameraUpVector();

    pAxsMver_->behave();
    getKuroko()->behave();

    vcv_face_ = getCamToVpFaceNo();

    if (auto_up_wait_frames == 0) {
        if (vcv_face_ != vcv_face_prev_) { //カメラ→視点ベクトルの面番号が変化したらUPを１回考慮

            int up_face_wk = pUpV->up_face_; //デバッグ用

            int up_hx1, up_hy1, up_hz1;
            GgafDxDirectionUtil::cnvFaceNo2Sgn(pUpV->up_face_, up_hx1, up_hy1, up_hz1);

            int up_face_next = relation_up_by_vec_[pUpV->up_face_][vcv_face_];
            if (up_face_next == GgafDxDirectionUtil::FACE_XXX) {
                //FACE_XXXは、UPは動く必要なし
            } else {
                if (up_face_next == GgafDxDirectionUtil::FACE_ZZZ) {
                    //カメラ→視点ベクトルの面番号が、UPの面番号と同じか真裏になった。
                    //その場合は、カメラ→視点ベクトルの一つ前の面番号を採用してUPの場所を求める。
                    int up_face_next_other = relation_up_by_vec_[pUpV->up_face_][vcv_face_prev_];
                    if (up_face_next_other == GgafDxDirectionUtil::FACE_XXX) {
                        //FACE_XXXは、UPは動く必要なし
                    } else {
                        if (up_face_next_other == GgafDxDirectionUtil::FACE_ZZZ) {
                            //カメラ→視点ベクトルの面番号が真裏へ一気に動いたことになる。
                            //お手上げ。UPはどこに行けばよいか不定。したがってUPはそのまま。
                        } else {
                            pUpV->setFaceNo(up_face_next_other);
                        }
                    }
                } else {
                    //カメラ→視点ベクトル面番号が、UPベクトル面番号に隣接したので、
                    //その隣接面の反対側の隣接面の方角へUPベクトルを逃す。
                    //或いは、カメラ→視点ベクトル面番号が、UPベクトル面番号から直角以上の角度で遠ざかるので、
                    //UPベクトルを近寄らせる。
                    pUpV->setFaceNo(up_face_next);
                }
            }


            int eye_hx1, eye_hy1, eye_hz1;
            GgafDxDirectionUtil::cnvFaceNo2Sgn(vcv_face_prev_, eye_hx1, eye_hy1, eye_hz1);
            int eye_hx2, eye_hy2, eye_hz2;
            GgafDxDirectionUtil::cnvFaceNo2Sgn(vcv_face_, eye_hx2, eye_hy2, eye_hz2);
            int up_hx_1, up_hy_1, up_hz_1;
            GgafDxDirectionUtil::cnvFaceNo2Sgn(up_face_wk, up_hx_1, up_hy_1, up_hz_1);
            int up_hx2, up_hy2, up_hz2;
            GgafDxDirectionUtil::cnvFaceNo2Sgn(pUpV->up_face_, up_hx2, up_hy2, up_hz2);
            _TRACE_("EYE["<<vcv_face_prev_<<"]("<<eye_hx1<<","<< eye_hy1<<","<<eye_hz1<<") → ["<<vcv_face_<<"]("<<eye_hx2<<","<< eye_hy2<<","<<eye_hz2<<")");
            _TRACE_(" → UP["<<up_face_wk<<"]("<<up_hx_1<<","<< up_hy_1<<","<<up_hz_1<<") → ["<<pUpV->up_face_<<"]("<<up_hx2<<","<< up_hy2<<","<<up_hz2<<")");
        }
    } else {
        auto_up_wait_frames--;
    }

    DefaultCamera::processBehavior();

    vcv_face_prev_ = vcv_face_;
}

void VvvCamera::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    //_TRACE_(" VvvCamera::slideMvTo("<<tx<<","<<ty<<","<<tz<<",t="<<t<<")");
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.4, 0, true);
}
void VvvCamera::slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}
int VvvCamera::getCamToVpFaceNo() {
    float vcv_x, vcv_y, vcv_z;
    VvvCameraViewPoint* pVP = (VvvCameraViewPoint*)getCameraViewPoint();
    UTIL::getNormalizeVector (
            pVP->_x - _x,
            pVP->_y - _y,
            pVP->_z - _z,
            vcv_x, vcv_y, vcv_z  );
    return GgafDxDirectionUtil::cnvVec2FaceNo(vcv_x, vcv_y, vcv_z);
}

VvvCamera::~VvvCamera() {
    GGAF_DELETE(pAxsMver_);
}
