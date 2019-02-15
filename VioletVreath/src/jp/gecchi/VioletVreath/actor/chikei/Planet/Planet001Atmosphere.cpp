#include "Planet001Atmosphere.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
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
    setSpecialRenderDepthIndex(RENDER_DEPTH_INDEX_HOSHIBOSHI-1);
    defineRotMvWorldMatrix_Billboard(); //XYZ���r���{�[�h
    drawAnyFar(true); //�����Ă��\��
}
void Planet001Atmosphere::onCreateModel() {
}

void Planet001Atmosphere::initialize() {
    setCullingDraw(false);
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);
}

void Planet001Atmosphere::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->behave();
}

Planet001Atmosphere::~Planet001Atmosphere() {
}

