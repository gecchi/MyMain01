#include "MyTorpedoBlast.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

MyTorpedoBlast::MyTorpedoBlast(const char* prm_name) :
        VvMyActor<DefaultMeshSetActor>(prm_name, "MyTorpedoBlast", StatusReset(MyTorpedoBlast)) {
    _class_name = "MyTorpedoBlast";
    effectBlendOne(); //���Z��������Technique�w��
    setAlpha(0.3);
    useZBufferDrawing(true);        //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZBufferWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
}

void MyTorpedoBlast::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    getLocusVehicle()->setRollPitchYawFaceAngVelo(D_ANG(0), D_ANG(0), D_ANG(6));
    setHitAble(true);
}

void MyTorpedoBlast::onReset() {
    //MyTorpedo��reset()�����s�����B
    //MyTorpedoBlast�́AdispatchForce�����̂ŁA
    //onInactive() onActive()�ł̎����������
    getStatus()->reset();
    getWorldCollisionChecker()->setColliSphere(0, PX_C(10));
    getLocusVehicle()->setMvVelo(0);
    setScale(R_SC(1));
    GgafDx::Scaler* const pScaler = getScaler();
    pScaler->setRange(R_SC(1), R_SC(400));
    pScaler->beat(120, 120/2, 0, 120/2, 1); //1��c���ł��ڂ�
}

void MyTorpedoBlast::processBehavior() {
    GgafDx::Scaler* const pScaler = getScaler();
    if (!pScaler->isTransitioning()) {
        sayonara();//�c���ł��ڂނ��I����
    } else {
        getWorldCollisionChecker()->setColliSphere(0, _sx); //�����蔻����ω�
        getLocusVehicle()->behave();
        pScaler->behave();
    }
}

void MyTorpedoBlast::processJudgement() {
}

void MyTorpedoBlast::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    //�q�b�g���Ă����ł��܂���
    int sta = calcStamina(pOther);
}

MyTorpedoBlast::~MyTorpedoBlast() {
}
