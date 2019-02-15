#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"



using namespace GgafLib;

DefaultGeometricActor::DefaultGeometricActor(const char* prm_name, GgafDx::Checker* prm_pChecker) :
    GgafDx::GeometricActor(prm_name, prm_pChecker)
{
    _class_name = "DefaultGeometricActor";
}

DefaultGeometricActor::~DefaultGeometricActor() {
}

