#include "MyMagicEnergy.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

MyMagicEnergy::MyMagicEnergy(const char* prm_name, MyMagicEnergyCore* prm_pCore) :
        DefaultMeshActor(prm_name, "MagicEnergy") {
    _class_name = "MyMagicEnergy";
    effectBlendOne(); //���Z��������Technique�w��
    pCore_ = prm_pCore;
    setZEnableDraw(true);        //Z�o�b�t�@�͍l�����ĕ`��
    setZWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
    setHitAble(false);
    setCullingDraw(false);
}

void MyMagicEnergy::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void MyMagicEnergy::initialize() {
    callRikisha()->setRollPitchYawFaceAngVelo(2111, 2333, 2777);
}

void MyMagicEnergy::onActive() {
}

void MyMagicEnergy::processBehavior() {
    GgafDx::Rikisha* const pRikisha = callRikisha();
    pRikisha->behave();
    setPositionAt(pCore_);
    setScaleAt(pCore_);
}

void MyMagicEnergy::processJudgement() {
}

void MyMagicEnergy::processPreDraw() {
    setSpecialRenderDepthIndex(pCore_->_now_drawdepth-1);//�R�A��ɕ`�悷�邽��
    DefaultMeshActor::processPreDraw();
}

int MyMagicEnergy::isOutOfView() {
    //��ʊO���薳��
    return 0;
}

bool MyMagicEnergy::isOutOfSpacetime() const {
    //�Q�[�����W�͈͊O���薳��
    return false;
}

void MyMagicEnergy::drawHitArea() {
    //CollisionChecker::drawHitArea(_pColliChecker);
}

MyMagicEnergy::~MyMagicEnergy() {
}
