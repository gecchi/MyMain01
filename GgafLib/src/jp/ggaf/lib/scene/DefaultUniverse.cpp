#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/ggaf/lib/GgafLibProperties.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultSpacetime::DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera) : GgafDxSpacetime(prm_name, prm_pCamera) {
    _class_name = "DefaultSpacetime";
    //�����؍쐬
    _TRACE_("�����؍쐬�J�n");
    _pLinearOctree = NEW LinearOctreeForActor(PROPERTY::OCTREE_LEVEL);
    _pLinearOctree->setRootOctant(_x_bound_left  ,_y_bound_bottom, _z_bound_near ,
                                 _x_bound_right ,_y_bound_top   , _z_bound_far   );
    _TRACE_("�����؍쐬�I��");
}

void DefaultSpacetime::processFinal() {
    _pLinearOctree->clearElem();
    //���[�g��ԍX�V
//    _pLinearOctree->setRootOctant(_x_bound_left  ,_y_bound_bottom, _z_bound_near ,
//                                     _x_bound_right ,_y_bound_top   , _z_bound_far   );
}

DefaultSpacetime::~DefaultSpacetime() {
#ifdef MY_DEBUG
    _pLinearOctree->putTree();
    ColliAABActor::release();
    ColliAAPrismActor::release();
    ColliSphereActor::release();
#endif
    GGAF_DELETE(_pLinearOctree);
}
