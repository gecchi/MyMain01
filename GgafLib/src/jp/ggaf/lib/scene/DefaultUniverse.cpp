#include "stdafx.h"
#include "jp/ggaf/lib/scene/DefaultUniverse.h"

#include "jp/ggaf/lib/GgafLibProperties.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultUniverse::DefaultUniverse(const char* prm_name, DefaultCamera* prm_pCamera) : GgafDxUniverse(prm_name, prm_pCamera) {
    _class_name = "DefaultUniverse";
    //�W���؍쐬
    _TRACE_("�W���؍쐬�J�n");
    _pLinearOctree = NEW LinearOctreeForActor(PROPERTY::OCTREE_LEVEL);
    _pLinearOctree->setRootSpace(_X_gone_left  ,_Y_gone_bottom, _Z_gone_near ,
                                 _X_gone_right ,_Y_gone_top   , _Z_gone_far   );
    _TRACE_("�W���؍쐬�I��");
}

void DefaultUniverse::processFinal() {
    _pLinearOctree->clearElem();
    //���[�g��ԍX�V
//    _pLinearOctree->setRootSpace(_X_gone_left  ,_Y_gone_bottom, _Z_gone_near ,
//                                     _X_gone_right ,_Y_gone_top   , _Z_gone_far   );
}

DefaultUniverse::~DefaultUniverse() {
#ifdef MY_DEBUG
    _pLinearOctree->putTree();
    ColliAABActor::release();
    ColliAAPrismActor::release();
    ColliSphereActor::release();
#endif
    GGAF_DELETE(_pLinearOctree);
}
