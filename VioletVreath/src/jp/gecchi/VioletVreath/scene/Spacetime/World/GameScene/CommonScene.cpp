#include "CommonScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/core/actor/ex/ActorDepositoryStore.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

#define REGISTER_DEPO(TYPE, NUM)   do { \
        pCOMMON_DEPO(TYPE) = NEW GgafCore::ActorDepository("CommonDepo_" #TYPE); \
        pCOMMON_DEPO(TYPE)->putn<TYPE>(NUM); \
        bringSceneMediator()->appendGroupChild(pCOMMON_DEPO(TYPE)); \
}while(0)
#define REGISTER_LASERDEPO_STORE(TYPE, SET_NUM, LASER_NUM) do { \
    pCOMMON_DEPO_STORE(TYPE) = NEW GgafCore::ActorDepositoryStore("CommonDepoStore_" #TYPE); \
    LaserChipDepository* pLaserChipDepo; \
    for (int laser_set = 0; laser_set < SET_NUM; laser_set++) { \
        std::string name_depo = "LaserChipDepo["+XTOS(laser_set)+"]"; \
        pLaserChipDepo = NEW LaserChipDepository(name_depo.c_str()); \
        pLaserChipDepo->putn<TYPE>(LASER_NUM); \
        pCOMMON_DEPO_STORE(TYPE)->put(pLaserChipDepo); \
    } \
    bringSceneMediator()->appendGroupChild(pCOMMON_DEPO_STORE(TYPE)); \
}while(0)


CommonScene::CommonScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "CommonScene";

    //�S�V�[���ɓn���ď펞�g�p�Ȕėp�I�ȃA�N�^�[�ނ�
    //�R�R�ɂ��̃f�|�W�g�������O�쐬����B
    //�ėp�����G�t�F�N�g
    REGISTER_DEPO(EffectExplosion001, 300);
    //�ėp�����G�t�F�N�g
    REGISTER_DEPO(EffectExplosion002, 100);
    //�ėp�����G�t�F�N�g
    REGISTER_DEPO(EffectExplosion003, 50);
    //�ėp�����G�t�F�N�g��
    REGISTER_DEPO(EffectExplosion004, 100);
    //�A�C�e����
    REGISTER_DEPO(MagicPointItem001, 400);
    //�A�C�e����
    REGISTER_DEPO(MagicPointItem002, 30);
    //�A�C�e����
    REGISTER_DEPO(MagicPointItem003, 10);
    //Effect EffectTurbo002 �^�[�{����
    REGISTER_DEPO(EffectTurbo002, 10);
    //�ėp�o���G�t�F�N�g EffectBlink001
    REGISTER_DEPO(EffectBlink001, 200);
    //�ėp�o���G�t�F�N�g EffectBlink002
    REGISTER_DEPO(EffectBlink002, 30);
    //�ėp�o���G�t�F�N�g EffectBlink003
    REGISTER_DEPO(EffectBlink003, 30);
    //�{�[�i�X�|�C���g�\���G�t�F�N�g
    REGISTER_DEPO(SpriteLabelBonus001, 30);
    //�ėp�V���b�g
    REGISTER_DEPO(Shot004, 30);

    REGISTER_LASERDEPO_STORE(EnemyWateringLaserChip001, 30, 40);
    REGISTER_LASERDEPO_STORE(EnemyStraightLaserChip001, 8 ,40);

}

void CommonScene::initialize() {
}
void CommonScene::onReset() {
    //�X�N���[������
    setFeatureFunction(nullptr);
    setFeatureParam1(0);

    fadeinScene(0);
}

void CommonScene::processBehavior() {

}

void CommonScene::scrollX(GgafCore::Object* pThat, void* p1, void* p2, void* p3) {

    if (pThat->instanceOf(Obj_GgafDx_GeometricActor)) {
        GgafDx::GeometricActor* pActor = (GgafDx::GeometricActor*)pThat;
        if (pActor->lookUpKind() & KIND_ITEM) {
            //Item�̓X�N���[���̉e�����󂯂Ȃ�
        } else {
            pActor->_x -= (*((coord*)p1));
            //setDriverLeader() ����Ă�����A�X�N���[���̉e�����󂯂�
            GgafDx::DriverLeader* pDriverLeader = pActor->getDriverLeader();
            if (pDriverLeader) {
                pDriverLeader->_x_start_in_loop -= (*((coord*)p1));
            }
        }
    }
}

CommonScene::~CommonScene() {
}
