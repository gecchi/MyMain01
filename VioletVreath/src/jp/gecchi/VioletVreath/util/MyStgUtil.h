#ifndef MYSTGUTIL_H_
#define MYSTGUTIL_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/util/StgUtil.h"

#include "jp/ggaf/core/util/Status.h"
#include <map>

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL VioletVreath::MyStgUtil

//#define STATUS(X) (NEW GgafCore::Status(VioletVreath::MyStgUtil::reset##X##Status))
#define StatusReset(X) ((void*)(VioletVreath::MyStgUtil::reset##X##Status))

namespace VioletVreath {

//�C�x���g�p eventval ���l�錾
DECLARE_EVENT_VAL(EVENT_CARETAKER_WILL_DEMISE);
DECLARE_EVENT_VAL(EVENT_PREPARE_TRANSIT_STAGE);
DECLARE_EVENT_VAL(EVENT_PREPARE_NEXT_STAGE);
DECLARE_EVENT_VAL(EVENT_JUST_GAME_OVER);

DECLARE_EVENT_VAL(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
DECLARE_EVENT_VAL(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
DECLARE_EVENT_VAL(EVENT_ALL_MY_SHIP_WAS_DESTROYED);

DECLARE_EVENT_VAL(EVENT_PREGAMETITLESCENE_FINISH);
DECLARE_EVENT_VAL(EVENT_GAMETITLESCENE_FINISH);
DECLARE_EVENT_VAL(EVENT_GAMEDEMOSCENE_FINISH);
DECLARE_EVENT_VAL(EVENT_GAMESTART);
DECLARE_EVENT_VAL(EVENT_GAMEMODE_DECIDE);
DECLARE_EVENT_VAL(EVENT_GAMEOVERSCENE_FINISH);
DECLARE_EVENT_VAL(EVENT_GO_TO_TITLE);
DECLARE_EVENT_VAL(EVENT_NAMEENTRYSCENE_FINISH);

enum EffectKind {
    EF_NOTHING,
    EF_ENTRY_SMALL001_F90,
    EF_ENTRY_SMALL001_F60,
    EF_ENTRY_SMALL001_F30,
    EF_ENTRY_SMALL001_STAY_F90,
    EF_ENTRY_SMALL001_STAY_F60,
    EF_ENTRY_SMALL001_STAY_F30,
    EF_ENTRY_SMALL001_LONG,
    EF_ENTRY_MIDDLE001,
    EF_ENTRY_LARGE001,
    EF_LEAVE_SMALL001_F60,
    EF_LEAVE_SMALL001_F30,
    EF_LEAVE_SMALL001_F90,
    EF_LEAVE_MIDDLE001,
    EF_LEAVE_LARGE001,
    EF_EXPLOSION001,
    EF_EXPLOSION001_STAY,
    EF_EXPLOSION002,
    EF_EXPLOSION003,
    EF_BONUS001,
    EF_BONUS_FORMATION,
    EF_EXPLO_AND_BONUS001,
    EF_TURBO,
    EF_DAMAGED001,
};
enum SeKind {
    SE_NOTHING,
    SE_EXPLOSION_001 = 10000,
    SE_EXPLOSION_002,
    SE_EXPLOSION_MIDDLE_001,
    SE_ENEMY_DAMAGED_001,
};

class MyStgUtil_SeKind {
public:
    static std::map<int, const char*> mapSeId;
    static void initMapSeId() {
        mapSeId[SE_EXPLOSION_001]        = "SE_EXPLOSION_001";
        mapSeId[SE_EXPLOSION_002]        = "SE_EXPLOSION_002";
        mapSeId[SE_EXPLOSION_MIDDLE_001] = "SE_EXPLOSION_MIDDLE_001";
        mapSeId[SE_ENEMY_DAMAGED_001]    = "SE_ENEMY_DAMAGED_001";
    }
};


enum ItemKind {
    ITEM_NOTHING,
    ITEM_MP_SMALL,
    ITEM_MP_MIDDLE,
    ITEM_MP_LARGE,
};

enum ShotKind {
    SHOT_NOTHING,

    SHOT_SMALL001,
    SHOT_SMALL002,

    SHOT_RV_NOMAL001,
    SHOT_RV_NOMAL002,
    SHOT_RV_GOLDEN_ANG_WAY,
};

enum DepoKind {
    DEPO_NOTHING,
    DEPO_LASER001,
    DEPO_LASER002,
};

#define STAT_DEFAULT_ACTOR_KIND (0)

/**
 * �{�A�v���̃��[�e�B���e�B .
 * @version 1.00
 * @since 2010/01/06
 * @author Masatoshi Tsuge
 */
class MyStgUtil : public GgafLib::StgUtil {

public:
    /**
     * �ΏۃA�N�^�[�ɕR�����ێ��A�C�e�����A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(getStatus())�� STAT_ItemKind �̒l�ɂ���ăA�C�e����ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̕ێ��A�C�e���i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDx::FigureActor* activateCommonItemOf(GgafDx::GeometricActor* prm_pActor);
    /**
     * �ΏۃA�N�^�[�ɕR�������ŃG�t�F�N�g���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �^�C�~���O�I�ɂ́A�����G�t�F�N�g�Ɠ����ł��邱�Ƃ������B<BR>
     * �j�󎞂̕ϓ��X�R�A�{�[�i�X�\����A�ʏ�̔����G�t�F�N�g�ȊO�̓���ȃG�t�F�N�g���Ɏg�p�����B<BR>
     * �X�e�[�^�X(getStatus())�� STAT_DestroyedEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^
     * @return �ΏۃA�N�^�[�̏��ŃG�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    //static GgafDx::FigureActor* activateDestroyedEffectOf(GgafCore::Actor* prm_pActor);
    /**
     * �ł��Ԃ��e .
     * @param prm_pActor
     * @return
     */
    static GgafDx::FigureActor* activateRevengeShotOf(GgafDx::GeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR�����_���[�W���G�t�F�N�g���A�擾�ł���Δ������A�����Ԃ� .
     * �X�e�[�^�X(getStatus())�� STAT_DamagedEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̃_���[�W���G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     * @return
     */
//    static GgafDx::FigureActor* activateDamagedEffectOf(GgafDx::GeometricActor* prm_pActor);


    /**
     * �ΏۃA�N�^�[�̕R�����A�t�H�[���[�V�����S�ŃG�t�F�N�g�ƃX�R�A���Z���� .
     * �X�e�[�^�X(getStatus())�� STAT_FormationDestroyedEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̃t�H�[���[�V�����S�ŃG�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
//    static GgafDx::FigureActor* activateFormationDestroyedEffectOf(GgafDx::GeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�̂ɕR�����t�H�[���[�V�����S�ŃA�C�e�����A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(getStatus())�� STAT_FormationDestroyedItemKind �̒l�ɂ���ăA�C�e����ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̃t�H�[���[�V�����S�ŃA�C�e���i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
//    static GgafDx::FigureActor* activateFormationDestroyedItemOf(GgafDx::GeometricActor* prm_pActor);


public:
    static bool _was_MyStgUtil_inited_flg;
    static void init();

    /**
     * �����p .
     * �v�f[x](0�`999) �� x �Ԗڂ̉����p�B
     */
    static angle GOLDEN_ANG[1000];

    /**
     * v = 1 - cos(2��t)�̉��e�[�u�� .
     * �y�����z
     * t:����(�t���[��)
     * v:���x
     * �ʐρ��ړ�����
     * t = 0.0��0.5��1.0 �΂��ĂȂ߂炩�� v = 0.0�`2.0�`0.0 �ƕω����A����1.0���ړ�
     */
    static double SMOOTH_DV[3600+1];

    /**
     * �U���͂̈З͗� .
     * �ߋ����V���b�g�̂ق����U���͂������Ȃ�悤�ɂ��������߂̔z��B
     * �v�f�͏o���t���[�����A�l�͍U���͂ɏ悶����␳���B
     */
    static double SHOT_POWER[300+1];

    /**
     * �����p�g�U���ˏ�e�𕡐��Z�b�g�����Ɍ��� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDx::LocusVehicle �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_x               ���ˌ�X���W
     * @param prm_y               ���ˌ�Y���W
     * @param prm_z               ���ˌ�Z���W
     * @param prm_rz              ���˕���Rz
     * @param prm_ry              ���˕���Ry
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_way_num         �P�Z�b�g���ː�(1�`999)
     * @param prm_first_expanse_angle   ���˒e�̏����Ǝˊp(0 �` D180ANG�B�����d���̌��̍L����p�̂悤�ȃC���[�W�B�������ƒe�̊Ԋu������)
     * @param prm_inc_expanse_angle     1�e���ɉ��Z����Ǝˊp����(0 �` D180ANG)
     * @param prm_velo_first      ���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce            �e�Z�b�g�̃V���b�g���������x
     * @param prm_draw_set_num         �����ˏ�WAY�e�̍��v�Z�b�g��
     * @param prm_interval_frames �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�֏旦�B���x����(< 1.0)�����͑��x����(>1.0)�B1.0�͑S�Z�b�g���x�������B
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDx::FigureActor* shotWayGoldenAng(coord prm_x, coord prm_y, coord prm_z,
                                                  angle prm_rz, angle prm_ry,
                                                  GgafCore::ActorDepository* prm_pDepo_shot,
                                                  coord prm_r,
                                                  int prm_way_num,
                                                  angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                  velo prm_velo_first, acce prm_acce,
                                                  int prm_draw_set_num, frame prm_interval_frames, float prm_attenuated,
                                                  void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);

    /**
     * ���ˌ��������Ă�������i_rz > _ry�j�Ɍ������ĉ����p�g�U���ˏ�e�𕡐��Z�b�g�����Ɍ��� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDx::LocusVehicle �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_pFrom           ���ˌ�
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_way_num         �P�Z�b�g���ː�(1�`999)
     * @param prm_first_expanse_angle   ���˒e�̏����Ǝˊp(0 �` D180ANG�B�����d���̌��̍L����p�̂悤�ȃC���[�W�B�������ƒe�̊Ԋu������)
     * @param prm_inc_expanse_angle     1�e���ɉ��Z����Ǝˊp����(0 �` D180ANG)
     * @param prm_velo_first      ���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce            �e�Z�b�g�̃V���b�g���������x
     * @param prm_draw_set_num         �����ˏ�WAY�e�̍��v�Z�b�g��
     * @param prm_interval_frames �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�֏旦�B���x����(< 1.0)�����͑��x����(>1.0)�B1.0�͑S�Z�b�g���x�������B
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDx::FigureActor* shotWayGoldenAng(GgafDx::GeometricActor* prm_pFrom,
                                                 GgafCore::ActorDepository* prm_pDepo_shot,
                                                 coord prm_r,
                                                 int prm_way_num,
                                                 angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                 velo prm_velo_first, acce prm_acce,
                                                 int prm_draw_set_num, frame prm_interval_frames, float prm_attenuated,
                                                 void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);



    /**
     * ���@���̗D�ʐ��𒲂ׂ�
     * @param kind_my
     * @param kind_enemy
     * @return �ȉ��̕\�Q�ƁB
     * <table>
     * <tr><th>0��菬����              </th><th>0   </th><th>0���傫��         </th></tr>
     * <tr><td>attribute_my�̕�����   </td><td>���i</td><td>kind_my�̕����D��   </td></tr>
     * <tr><td>attribute_enemy�̕����D��</td><td>���i</td><td>kind_enemy�̕�����</td></tr>
     * </table>
     */
    static int judgeAdvantage(uint32_t attribute_this, uint32_t attribute_opp);

    /**
     * �ʏ�V���b�g .
     * @param prm_pActor
     * @return
     */
    static GgafDx::FigureActor* activateCommonAttackShotOf(GgafDx::GeometricActor* prm_pActor);

    /**     */
    static GgafCore::ActorDepository* getCommonDepositoryOf(GgafDx::GeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR���� ���ʓI�ȃG�t�F�N�g�i�A�N�^�[��SE�j ���擾�ł���ΗL���ɂ��A�����Ԃ� .
     * @param prm_pActor �ΏۃA�N�^�[
     * @param prm_status_kind �G�t�F�N�g���
     *   STAT_ExplosionEffectKind
     *   STAT_DamagedEffectKind
     *   STAT_EntryEffectKind
     *   STAT_LeaveEffectKind
     *   STAT_ProperEffect01Kind
     * @return �G�t�F�N�g�i�����ς݁Anullptr�͕Ԃ�Ȃ�)
     */
    static GgafDx::FigureActor* activateCommonEffectOf(GgafDx::GeometricActor* prm_pActor, int prm_status_kind, bool prm_is_adjust_part=false);

    /**
     * �Փ˂����q�b�g�p�[�g���l�����āA�Փ˃I�u�W�F�N�g�̍��W��Ԃ��B
     * @param prm_pTargetAtor
     * @param prm_is_adjust_part
     * @param out_x
     * @param out_y
     * @param out_z
     */
    static void adjustHitCoord(GgafDx::GeometricActor* prm_pTargetAtor, bool prm_is_adjust_part, coord& out_x, coord& out_y, coord& out_z);

    /**
     * �G�L�����q�b�g���̕W���I�ȏ��� .
     * ���j�󂳂ꂽ�ꍇ��<br>
     * �E�j�󎞓��_���Z<br>
     * �E�����N���Z<br>
     * �E�A�C�e���o��             activateCommonItemOf()<br>
     * �E���Ŏ�����G�t�F�N�g�J�n activateDestroyedEffectOf()<br>
     * �E�ł��Ԃ��e�o��           activateRevengeShotOf()<br>
     * �E�����G�t�F�N�g�o��       activateExplosionEffectOf()<br>
     * �E�ґ��S�Ŕ���<br>
     * �E�ґ��S�Ŏ��A�C�e���o��(STAT_ItemKind)<br>
     * ���j�󂳂�Ȃ������ꍇ��<br>
     * �E�_���[�W��^�������_���Z<br>
     * �E�_���[�W�t���b�V���\��       STAT_FlushAble<br>
     * �E�_���[�W������G�t�F�N�g�o�� activateDamagedEffectOf()<br>
     * @param prm_this �q�b�g�������g�i�G�L�����j�̃A�N�^�[��n��
     * @param prm_pOther �q�b�g��������̃A�N�^�[��n��
     * @return true:�j�󂳂ꂽ/false:�j�󂳂�ĂȂ�
     */
//    static bool performEnemyHit(GgafDx::FigureActor* prm_this, const GgafDx::GeometricActor* const prm_pOther);

    /**
     * �ґ��S�j�󎞂̕W���I�ȏ��� .
     * @param prm_pActor_last_destroyed �ґ��̍Ō�ɔj�󂳂ꂽ�A�N�^�[��n��
     * @return �ґ��S�Ŏ��G�t�F�N�g
     */
//    static GgafDx::FigureActor* performFormationDestroyAll(GgafDx::FigureActor* prm_pActor_last_destroyed);


    static void registerCommonSeOf(GgafDx::GeometricActor* prm_pActor);


    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�X�e�[�^�XCreater.xls�v����s�����ƁB
    // gen01 start
    //�f�t�H���g
    static GgafCore::Status* resetDefaultStatus(GgafCore::Status* p);
    //���@
    static GgafCore::Status* resetMyShipStatus(GgafCore::Status* p);
    //���@�V���b�g
    static GgafCore::Status* resetMyShot001Status(GgafCore::Status* p);
    //���@�X�i�C�v�V���b�g
    static GgafCore::Status* resetMySnipeShot001Status(GgafCore::Status* p);
    //�}�W�b�N�G�l���M�[�j
    static GgafCore::Status* resetMyMagicEnergyCoreStatus(GgafCore::Status* p);
    //���@���[�U�[
    static GgafCore::Status* resetMyStraightLaserChip001Status(GgafCore::Status* p);
    //���g
    static GgafCore::Status* resetMyBunshinStatus(GgafCore::Status* p);
    //���g�V�����V���b�g
    static GgafCore::Status* resetMyBunshinShot001Status(GgafCore::Status* p);
    //���g�X�i�C�v�V�����V���b�g
    static GgafCore::Status* resetMyBunshinSnipeShot001Status(GgafCore::Status* p);
    //���g�X�g���[�g���[�U�[
    static GgafCore::Status* resetMyBunshinStraightLaserChip001Status(GgafCore::Status* p);
    //���g�J�[�u���[�U�[
    static GgafCore::Status* resetMyBunshinWateringLaserChip001Status(GgafCore::Status* p);
    //�g�D�s�[�h
    static GgafCore::Status* resetMyTorpedoStatus(GgafCore::Status* p);
    //�g�D�s�[�h����
    static GgafCore::Status* resetMyTorpedoBlastStatus(GgafCore::Status* p);
    //�ėp�V���b�g001
    static GgafCore::Status* resetShot001Status(GgafCore::Status* p);
    //�ėp�V���b�g002
    static GgafCore::Status* resetShot002Status(GgafCore::Status* p);
    //�ėp�V���b�g003�~�j���[�U�[
    static GgafCore::Status* resetShot003Status(GgafCore::Status* p);
    //�ėp�~�j���[�U�[�V���b�g
    static GgafCore::Status* resetShot004Status(GgafCore::Status* p);
    //�ėp�G�X�g���[�g���[�U�[001
    static GgafCore::Status* resetEnemyStraightLaserChip001Status(GgafCore::Status* p);
    //�ėp�G�J�[�u���[�U�[001
    static GgafCore::Status* resetEnemyWateringLaserChip001Status(GgafCore::Status* p);
    //�G���X
    static GgafCore::Status* resetEnemyEresStatus(GgafCore::Status* p);
    //�G���X�V���b�g001
    static GgafCore::Status* resetEnemyEresShot001Status(GgafCore::Status* p);
    //�G���X�ґ�001
    static GgafCore::Status* resetFormationEres001Status(GgafCore::Status* p);
    //�G���X�ґ�002
    static GgafCore::Status* resetFormationEres002Status(GgafCore::Status* p);
    //�X�g���G�A
    static GgafCore::Status* resetEnemyStraeaStatus(GgafCore::Status* p);
    //�X�g���G�A���[�U�[
    static GgafCore::Status* resetEnemyStraeaLaserChip001Status(GgafCore::Status* p);
    //�X�g���G�A���[�U�[
    static GgafCore::Status* resetEnemyStraeaLaserChip002Status(GgafCore::Status* p);
    //�X�g���G�A���[�U�[
    static GgafCore::Status* resetEnemyStraeaLaserChip003Status(GgafCore::Status* p);
    //�X�g���G�A���[�U�[
    static GgafCore::Status* resetEnemyStraeaLaserChip004Status(GgafCore::Status* p);
    //�I�����X�i���e�B�X�����B�A�̃n�b�`�j
    static GgafCore::Status* resetEnemyOmulusStatus(GgafCore::Status* p);
    //�G���X�i���e�B�X�����B�A�̃n�b�`�j
    static GgafCore::Status* resetEnemyEmusStatus(GgafCore::Status* p);
    //�G���X�̃��[�U�[
    static GgafCore::Status* resetEnemyEmusLaserChip001Status(GgafCore::Status* p);
    //�G�e�B�X
    static GgafCore::Status* resetEnemyEtisStatus(GgafCore::Status* p);
    //�G�e�B�X�ґ�001
    static GgafCore::Status* resetFormationEtis001Status(GgafCore::Status* p);
    //���X
    static GgafCore::Status* resetEnemyRisStatus(GgafCore::Status* p);
    //���X�ґ�001
    static GgafCore::Status* resetFormationRis001Status(GgafCore::Status* p);
    //���X�ґ�002
    static GgafCore::Status* resetFormationRis002Status(GgafCore::Status* p);
    //�Q���A
    static GgafCore::Status* resetEnemyGeriaStatus(GgafCore::Status* p);
    //�n���A
    static GgafCore::Status* resetEnemyHaliaStatus(GgafCore::Status* p);
    //�n���A�ґ�
    static GgafCore::Status* resetFormationHaliaStatus(GgafCore::Status* p);
    //���܂��P
    static GgafCore::Status* resetEnemyTamago01Status(GgafCore::Status* p);
    //�C���P
    static GgafCore::Status* resetEnemyIrceStatus(GgafCore::Status* p);
    //���e�B�X�����B�A�i�g�[���X�j
    static GgafCore::Status* resetEnemyRatislaviaStatus(GgafCore::Status* p);
    //�A���X
    static GgafCore::Status* resetEnemyAllasStatus(GgafCore::Status* p);
    //�A���X�ґ�001
    static GgafCore::Status* resetFormationAllas001Status(GgafCore::Status* p);
    //�A���X�ґ�001
    static GgafCore::Status* resetFormationAllas002Status(GgafCore::Status* p);
    //�E�[�m�~�A
    static GgafCore::Status* resetEnemyUnomiaStatus(GgafCore::Status* p);
    //�E�m�~�A�ґ�001
    static GgafCore::Status* resetFormationUnomia001Status(GgafCore::Status* p);
    //�E�m�~�A�ґ�001
    static GgafCore::Status* resetFormationUnomia002Status(GgafCore::Status* p);
    //�G�~���A
    static GgafCore::Status* resetEnemyEmiliaStatus(GgafCore::Status* p);
    //�G�~���A�f��
    static GgafCore::Status* resetEnemyEmiliaFragmentStatus(GgafCore::Status* p);
    //�G�~���A�f�Ђ̒f��
    static GgafCore::Status* resetEnemyEmiliaFragment2Status(GgafCore::Status* p);
    //�G�~���A�f�Ђ̒f�Ђ̒f��
    static GgafCore::Status* resetEnemyEmiliaFragment3Status(GgafCore::Status* p);
    //MP�A�C�e����
    static GgafCore::Status* resetMagicPointItem001Status(GgafCore::Status* p);
    //MP�A�C�e����
    static GgafCore::Status* resetMagicPointItem002Status(GgafCore::Status* p);
    //MP�A�C�e����
    static GgafCore::Status* resetMagicPointItem003Status(GgafCore::Status* p);
    //�X�R�A�A�C�e��
    static GgafCore::Status* resetScoreItem001Status(GgafCore::Status* p);
    //Vreath�A�C�e��
    static GgafCore::Status* resetVreathItem001Status(GgafCore::Status* p);
    //�G�[�x
    static GgafCore::Status* resetEnemyEbeStatus(GgafCore::Status* p);
    //�G�[�x�ґ�001
    static GgafCore::Status* resetFormationEbe001Status(GgafCore::Status* p);
    //�q�Y�r�[
    static GgafCore::Status* resetEnemyHisbeStatus(GgafCore::Status* p);
    //�q�Y�r�[2
    static GgafCore::Status* resetEnemyHisbe002Status(GgafCore::Status* p);
    //�q�Y�r�[���[�U�[
    static GgafCore::Status* resetEnemyHisbeLaserChip001Status(GgafCore::Status* p);
    //�q�Y�r�[���[�U�[
    static GgafCore::Status* resetEnemyHisbeLaserChip002Status(GgafCore::Status* p);
    //�q�Y�r�[���[�U�[
    static GgafCore::Status* resetEnemyHisbeLaserChip003Status(GgafCore::Status* p);
    //�h���X�e�A
    static GgafCore::Status* resetEnemyDrasteaStatus(GgafCore::Status* p);
    //�h���X�e�A�ґ�001
    static GgafCore::Status* resetFormationDrastea001Status(GgafCore::Status* p);
    //�^�����e
    static GgafCore::Status* resetEnemyTalanteStatus(GgafCore::Status* p);
    //�G�X�y���A
    static GgafCore::Status* resetEnemyEsperiaStatus(GgafCore::Status* p);
    //�G�X�y���A�A���[�U�[
    static GgafCore::Status* resetEnemyEsperiaLaserChip001Status(GgafCore::Status* p);
    //�O�[�e�X�g
    static GgafCore::Status* resetTestGuStatus(GgafCore::Status* p);
    //�`���L�[�e�X�g
    static GgafCore::Status* resetTestChokiStatus(GgafCore::Status* p);
    //�p�[�e�X�g
    static GgafCore::Status* resetTestPaStatus(GgafCore::Status* p);
    //�m�[�}���[�e�X�g
    static GgafCore::Status* resetTestNomalStatus(GgafCore::Status* p);
    //�O�[�V���b�g
    static GgafCore::Status* resetTestGuShotStatus(GgafCore::Status* p);
    //�`���L�[�V���b�g
    static GgafCore::Status* resetTestChokiShotStatus(GgafCore::Status* p);
    //�p�[�V���b�g
    static GgafCore::Status* resetTestPaShotStatus(GgafCore::Status* p);
    //�m�[�}���[�V���b�g
    static GgafCore::Status* resetTestNomalShotStatus(GgafCore::Status* p);
    //���e�B�X�����B�A�A�C
    static GgafCore::Status* resetEnemyRatislaviaEyeStatus(GgafCore::Status* p);
    //���e�B�X�����B�A�A�C�p�X�g���[�g���[�U�[001
    static GgafCore::Status* resetEnemyRatislaviaEyeStraightLaserChip001Status(GgafCore::Status* p);
    //�G���~�I�l
    static GgafCore::Status* resetEnemyErmioneStatus(GgafCore::Status* p);
    //�G���~�I�l�r�̓�
    static GgafCore::Status* resetEnemyErmioneArmHeadStatus(GgafCore::Status* p);
    //�G���~�I�l�r�̓���
    static GgafCore::Status* resetEnemyErmioneArmBodyStatus(GgafCore::Status* p);
    //�G���~�I�l�r�̎�_
    static GgafCore::Status* resetEnemyErmioneArmWeakStatus(GgafCore::Status* p);
    //�A�b�t�H�[
    static GgafCore::Status* resetEnemyApphoStatus(GgafCore::Status* p);
    //�A�b�t�H�[�ґ�001
    static GgafCore::Status* resetFormationAppho001Status(GgafCore::Status* p);
    //�A���e�B�I�y
    static GgafCore::Status* resetEnemyAntiopeStatus(GgafCore::Status* p);
    //�f���w�C�h
    static GgafCore::Status* resetEnemyDelheidStatus(GgafCore::Status* p);
    //�f���w�C�h�ґ�001
    static GgafCore::Status* resetFormationDelheid001Status(GgafCore::Status* p);
    //�A���T�i
    static GgafCore::Status* resetEnemyAlisanaStatus(GgafCore::Status* p);
    //�C�[�_
    static GgafCore::Status* resetEnemyIdaStatus(GgafCore::Status* p);
    //�C�[�_�ґ�001
    static GgafCore::Status* resetFormationIda001Status(GgafCore::Status* p);
    //�^�S���X
    static GgafCore::Status* resetEnemyThagorasStatus(GgafCore::Status* p);
    //�^�S���X�ґ�001
    static GgafCore::Status* resetFormationThagoras001Status(GgafCore::Status* p);
    //�^�S���X�ґ�002
    static GgafCore::Status* resetFormationThagoras002Status(GgafCore::Status* p);
    //�I���g�D�i
    static GgafCore::Status* resetEnemyOrtunaStatus(GgafCore::Status* p);
    //�I���g�D�i�ґ�001
    static GgafCore::Status* resetFormationOrtuna001Status(GgafCore::Status* p);
    //�O����
    static GgafCore::Status* resetEnemyGlajaStatus(GgafCore::Status* p);
    //�O�������e
    static GgafCore::Status* resetEnemyGlajaLance001Status(GgafCore::Status* p);
    //�h�D�[�i
    static GgafCore::Status* resetEnemyDunaStatus(GgafCore::Status* p);
    //�I�[�c�@���e�B�A
    static GgafCore::Status* resetEnemyOzartiaStatus(GgafCore::Status* p);
    //�I�[�c�@���e�B�A�V���b�g�O�P(�ǃu���b�N)
    static GgafCore::Status* resetEnemyOzartiaShot01Status(GgafCore::Status* p);
    //�I�[�c�@���e�B�A���[�U�[�`�b�v
    static GgafCore::Status* resetEnemyOzartiaLaserChip01Status(GgafCore::Status* p);
    //�I�[�c�@���e�B�A�X��
    static GgafCore::Status* resetEnemyOzartiaPillar01Status(GgafCore::Status* p);
    //�G�r�E�X
    static GgafCore::Status* resetEnemyOebiusStatus(GgafCore::Status* p);
    //�G�r�E�X�R�A
    static GgafCore::Status* resetEnemyOebiusCoreStatus(GgafCore::Status* p);
    //�G�r�E�X�ґ�001
    static GgafCore::Status* resetFormationOebius001Status(GgafCore::Status* p);
    //�G�r�E�X�ґ�002
    static GgafCore::Status* resetFormationOebius002Status(GgafCore::Status* p);
    //�G�����}��
    static GgafCore::Status* resetEnemyErelmanStatus(GgafCore::Status* p);
    //�G�����}���ґ�001
    static GgafCore::Status* resetFormationErelman001Status(GgafCore::Status* p);
    //�G�����}���ґ�002
    static GgafCore::Status* resetFormationErelman002Status(GgafCore::Status* p);
    //�G�����}���ґ�003
    static GgafCore::Status* resetFormationErelman003Status(GgafCore::Status* p);
    //�G�����}���R�A
    static GgafCore::Status* resetEnemyErelmanCoreStatus(GgafCore::Status* p);
    //�E�����f�B�P
    static GgafCore::Status* resetEnemyUrydikeStatus(GgafCore::Status* p);
    //�E�����f�B�P�ґ�001
    static GgafCore::Status* resetFormationUrydike001Status(GgafCore::Status* p);
    //�E�����f�B�P�ґ�002
    static GgafCore::Status* resetFormationUrydike002Status(GgafCore::Status* p);
    //�e���A���X�p�V���b�g
    static GgafCore::Status* resetAliceShotStatus(GgafCore::Status* p);
    //�n�`�{�b�N�X01
    static GgafCore::Status* resetWall01Status(GgafCore::Status* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
