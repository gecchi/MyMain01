#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultUniverse::DefaultUniverse(const char* prm_name, DefaultCamera* prm_pCamera) : GgafDxUniverse(prm_name, prm_pCamera) {
    _class_name = "DefaultUniverse";
    //８分木作成
    _TRACE_("８分木作成開始");
    _pLinearOctree = NEW LinearOctreeForActor(PROPERTY::OCTREE_LEVEL);
    _pLinearOctree->setRootSpace(_X_goneLeft  ,_Y_goneBottom, _Z_goneNear ,
                                 _X_goneRight ,_Y_goneTop   , _Z_goneFar   );
    _TRACE_("８分木作成終了");
}

void DefaultUniverse::processFinal() {
    _pLinearOctree->clearElem();
    //ルート空間更新
//    _pLinearOctree->setRootSpace(_X_goneLeft  ,_Y_goneBottom, _Z_goneNear ,
//                                     _X_goneRight ,_Y_goneTop   , _Z_goneFar   );
}

DefaultUniverse::~DefaultUniverse() {
#ifdef MY_DEBUG
    _pLinearOctree->putTree();
    ColliAABActor::release();
    ColliAAPrismActor::release();
    ColliSphereActor::release();
#endif
    DELETE_IMPOSSIBLE_NULL(_pLinearOctree);
}
