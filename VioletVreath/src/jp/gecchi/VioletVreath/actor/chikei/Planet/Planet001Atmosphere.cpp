#include "Planet001Atmosphere.h"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi.h"

using namespace GgafLib;
using namespace VioletVreath;

Planet001Atmosphere::Planet001Atmosphere(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planet001Atmosphere") {
    _class_name = "Planet001Atmosphere";
    setHitAble(false);
    setZEnableDraw(true);        //Z�o�b�t�@�͍l��
    setZWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
    defineRotMvWorldMatrix_Billboard(); //XYZ���r���{�[�h
}
void Planet001Atmosphere::onCreateModel() {
    getModel()->drawAnyFar();//�����Ă��\��
}

void Planet001Atmosphere::initialize() {
    setCullingDraw(false);
    getLocusVehicle()->setFaceAngVelo(AXIS_Z, 1000);
}

void Planet001Atmosphere::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->behave();
}

Planet001Atmosphere::~Planet001Atmosphere() {
}

