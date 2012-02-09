#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultUniverse::DefaultUniverse(const char* prm_name, GgafDxCamera* prm_pCamera) : GgafDxUniverse(prm_name, prm_pCamera) {
    _class_name = "DefaultUniverse";
    //�W���؍쐬
    _TRACE_("�W���؍쐬�J�n");
    _pLinearOctree = NEW LinearOctreeForActor(7);
    _pLinearOctree->setRootSpace(_X_goneLeft  ,_Y_goneBottom, _Z_goneNear ,
                                 _X_goneRight ,_Y_goneTop   , _Z_goneFar   );
    _TRACE_("�W���؍쐬�I��");
}


void DefaultUniverse::processFinal() {
    _pLinearOctree->clearElem();
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
