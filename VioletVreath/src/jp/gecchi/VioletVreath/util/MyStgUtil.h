#ifndef MYSTGUTIL_H_
#define MYSTGUTIL_H_
#include "jp/ggaf/lib/util/StgUtil.h"

#include "jp/ggaf/core/util/GgafStatus.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL VioletVreath::MyStgUtil

#define STATUS(X) (NEW GgafCore::GgafStatus(STAT_BANPEI+1, VioletVreath::MyStgUtil::reset##X##Status))

//�C�x���g�p hashval ���l�錾
HASHVAL(EVENT_GOD_WILL_DIE);
HASHVAL(EVENT_PREPARE_TRANSIT_STAGE);
HASHVAL(EVENT_PREPARE_NEXT_STAGE);
HASHVAL(EVENT_JUST_GAME_OVER);

HASHVAL(EVENT_TRANSIT_WAS_END);
HASHVAL(EVENT_RANKUP_WAS_END);
HASHVAL(EVENT_RANKUP_ON_GARBAGED);

HASHVAL(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
HASHVAL(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
HASHVAL(EVENT_ALL_MY_SHIP_WAS_DESTROYED);

HASHVAL(EVENT_PREGAMETITLESCENE_FINISH);
HASHVAL(EVENT_GAMETITLESCENE_FINISH);
HASHVAL(EVENT_GAMEDEMOSCENE_FINISH);
HASHVAL(EVENT_GAMESTART);
HASHVAL(EVENT_GOTO_GAMETITLE);
HASHVAL(EVENT_GAMEMODE_DECIDE);
HASHVAL(EVENT_GAMEOVERSCENE_FINISH);
HASHVAL(EVENT_BACK_TO_TITLE);
HASHVAL(EVENT_NAMEENTRYSCENE_FINISH);
HASHVAL(EVENT_MENU_NAMEENTRY_DONE);


namespace VioletVreath {


/**
 * �{�A�v���̃��[�e�B���e�B .
 * @version 1.00
 * @since 2010/01/06
 * @author Masatoshi Tsuge
 */
class MyStgUtil : public GgafLib::StgUtil {
public:
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
        EF_EXPLO_AND_BONUS001,
        EF_TURBO,
        EF_DAMAGED001,
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
    static int judgeMyAdvantage(actorkind attribute_my, actorkind attribute_enemy);

    static int judgeEnemyAdvantage(actorkind kattribute_enemy, actorkind attribute_my);

    /**
     * �j�󎞂ɉ��Z����郉���N�|�C���g��STAT_AddRankPoint_Reduction�ɂ�茸�������� .
     * @param prm_pEnemy �G
     */
    static void updateEnemyRankPoint(GgafCore::GgafMainActor* prm_pEnemy);

    /**
     * ����(���@)�̗̑͌v�Z .
     * @param prm_pMy  ����(���@)
     * @param prm_pOpp ����(���@�ȊO)
     * @return ����(���@)�̗̑�
     */
    static int calcMyStamina(GgafCore::GgafMainActor* prm_pMy, GgafCore::GgafMainActor* prm_pOpp);

    /**
     * ����(�G�@)�̗̑͌v�Z .
     * ����ɁA�̗͂�0�ɂȂ����ꍇ�́A�������肪���@�֘A�������Ȃ�΁A
     * �Q�[���X�R�A�A�Q�[�������N�A����(�G�@)�̏����t�H�[���[�V�����ւ̔j�󂳂�܂����ʒm�A��
     * �����������ɍs���Ă��܂��֗����\�b�h�ɂȂ����I
     * @param prm_pMy  ����(�G�@)
     * @param prm_pOpp ����(�G�@�ȊO)
     * @return ����(�G�@)�̗̑�
     */
    static int calcEnemyStamina(GgafCore::GgafMainActor* prm_pEnemy, GgafCore::GgafMainActor* prm_pOpp);

    /**
     * �ΏۃA�N�^�[�ɕR���������G�t�F�N�g���A�擾�ł���Δ������A�����Ԃ� .
     * �X�e�[�^�X(getStatus())�� STAT_ExplosionEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̔����G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateExplosionEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR�����_���[�W���G�t�F�N�g���A�擾�ł���Δ������A�����Ԃ� .
     * �X�e�[�^�X(getStatus())�� STAT_DamagedEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̃_���[�W���G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     * @return
     */
    static GgafDxCore::GgafDxDrawableActor* activateDamagedEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ʏ�V���b�g .
     * @param prm_pActor
     * @return
     */
    static GgafDxCore::GgafDxDrawableActor* activateAttackShotOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**     */
    static GgafCore::GgafActorDepository* getDepositoryOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ł��Ԃ��e .
     * @param prm_pActor
     * @return
     */
    static GgafDxCore::GgafDxDrawableActor* activateRevengeShotOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR�����ێ��A�C�e�����A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(getStatus())�� STAT_ItemKind �̒l�ɂ���ăA�C�e����ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̕ێ��A�C�e���i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateItemOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR�������ŃG�t�F�N�g���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �^�C�~���O�I�ɂ́A�����G�t�F�N�g�Ɠ����ł��邱�Ƃ������B<BR>
     * �j�󎞂̕ϓ��X�R�A�{�[�i�X�\����A�ʏ�̔����G�t�F�N�g�ȊO�̓���ȃG�t�F�N�g���Ɏg�p�����B<BR>
     * �X�e�[�^�X(getStatus())�� STAT_DestroyedEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^
     * @return �ΏۃA�N�^�[�̏��ŃG�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateDestroyedEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR��������G�t�F�N�g���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(getStatus())�� STAT_EntryEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̓���G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateEntryEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR�����ޏ�G�t�F�N�g���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(getStatus())�� STAT_LeaveEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̑ޏ�G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateLeaveEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�̕R�����A�t�H�[���[�V�����S�ŃG�t�F�N�g�ƃX�R�A���Z���� .
     * �X�e�[�^�X(getStatus())�� STAT_FormationDestroyedEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̃t�H�[���[�V�����S�ŃG�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateFormationDestroyedEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);
    /**
     * �ΏۃA�N�^�[�̂ɕR�����t�H�[���[�V�����S�ŃA�C�e�����A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(getStatus())�� STAT_FormationDestroyedItemKind �̒l�ɂ���ăA�C�e����ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̃t�H�[���[�V�����S�ŃA�C�e���i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateFormationDestroyedItemOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR�����ŗL�G�t�F�N�g�i���̂P�j���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(getStatus())�� STAT_ProperEffect01Kind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̓���G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateProperEffect01Of(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �G�L�����q�b�g���̕W���I�ȏ��� .
     * ���j�󂳂ꂽ�ꍇ��
     * �E�j�󎞓��_���Z
     * �E�����N���Z
     * �E�A�C�e���o��             activateItemOf()
     * �E���Ŏ�����G�t�F�N�g�J�n activateDestroyedEffectOf()
     * �E�ł��Ԃ��e�o��           activateRevengeShotOf()
     * �E�����G�t�F�N�g�o��       activateExplosionEffectOf()
     * �E�ґ��S�Ŕ���
     * �E�ґ��S�Ŏ��A�C�e���o��(STAT_ItemKind)
     * ���j�󂳂�Ȃ������ꍇ��
     * �E�_���[�W��^�������_���Z
     * �E�_���[�W�t���b�V���\��       STAT_FlushAble
     * �E�_���[�W������G�t�F�N�g�o�� activateDamagedEffectOf()
     * @param prm_this �q�b�g�������g�i�G�L�����j�̃A�N�^�[��n��
     * @param prm_pOther �q�b�g��������̃A�N�^�[��n��
     * @return true:�j�󂳂ꂽ/false:�j�󂳂�ĂȂ�
     */
    static bool proceedEnemyHit(GgafDxCore::GgafDxDrawableActor* prm_this, GgafDxCore::GgafDxGeometricActor* prm_pOther);

    /**
     * �ґ��S�j�󎞂̕W���I�ȏ��� .
     * @param prm_pActor_last_destroyed �ґ��̍Ō�ɔj�󂳂ꂽ�A�N�^�[��n��
     * @return �ґ��S�Ŏ��G�t�F�N�g
     */
    static GgafDxCore::GgafDxDrawableActor* proceedFormationDestroyAll(GgafDxCore::GgafDxDrawableActor* prm_pActor_last_destroyed);

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�X�e�[�^�XCreater.xls�v����s�����ƁB
    // gen01 start
    //���@
    static GgafCore::GgafStatus* resetMyShipStatus(GgafCore::GgafStatus* p);
    //���@�V���b�g
    static GgafCore::GgafStatus* resetMyShot001Status(GgafCore::GgafStatus* p);
    //�}�W�b�N�G�l���M�[�j
    static GgafCore::GgafStatus* resetMyMagicEnergyCoreStatus(GgafCore::GgafStatus* p);
    //���@���[�U�[
    static GgafCore::GgafStatus* resetMyStraightLaserChip001Status(GgafCore::GgafStatus* p);
    //�I�v�V����
    static GgafCore::GgafStatus* resetMyOptionStatus(GgafCore::GgafStatus* p);
    //�I�v�V�����V���b�g
    static GgafCore::GgafStatus* resetMyOptionShot001Status(GgafCore::GgafStatus* p);
    //�I�v�V�����J�[�u���[�U�[
    static GgafCore::GgafStatus* resetMyOptionWateringLaserChip001Status(GgafCore::GgafStatus* p);
    //�I�v�V�����X�g���[�g���[�U�[
    static GgafCore::GgafStatus* resetMyOptionStraightLaserChip001Status(GgafCore::GgafStatus* p);
    //�g�D�s�[�h
    static GgafCore::GgafStatus* resetMyTorpedoStatus(GgafCore::GgafStatus* p);
    //�g�D�s�[�h����
    static GgafCore::GgafStatus* resetMyTorpedoBlastStatus(GgafCore::GgafStatus* p);
    //�ėp�V���b�g001
    static GgafCore::GgafStatus* resetShot001Status(GgafCore::GgafStatus* p);
    //�ėp�V���b�g002
    static GgafCore::GgafStatus* resetShot002Status(GgafCore::GgafStatus* p);
    //�ėp�V���b�g003�~�j���[�U�[
    static GgafCore::GgafStatus* resetShot003Status(GgafCore::GgafStatus* p);
    //�ėp�~�j���[�U�[�V���b�g
    static GgafCore::GgafStatus* resetShot004Status(GgafCore::GgafStatus* p);
    //�ėp�G�X�g���[�g���[�U�[001
    static GgafCore::GgafStatus* resetEnemyStraightLaserChip001Status(GgafCore::GgafStatus* p);
    //�ėp�G�J�[�u���[�U�[001
    static GgafCore::GgafStatus* resetEnemyWateringLaserChip001Status(GgafCore::GgafStatus* p);
    //�G���X
    static GgafCore::GgafStatus* resetEnemyEresStatus(GgafCore::GgafStatus* p);
    //�G���X�V���b�g001
    static GgafCore::GgafStatus* resetEnemyEresShot001Status(GgafCore::GgafStatus* p);
    //�X�g���G�A
    static GgafCore::GgafStatus* resetEnemyStraeaStatus(GgafCore::GgafStatus* p);
    //�X�g���G�A���[�U�[
    static GgafCore::GgafStatus* resetEnemyStraeaLaserChip001Status(GgafCore::GgafStatus* p);
    //�X�g���G�A���[�U�[
    static GgafCore::GgafStatus* resetEnemyStraeaLaserChip002Status(GgafCore::GgafStatus* p);
    //�X�g���G�A���[�U�[
    static GgafCore::GgafStatus* resetEnemyStraeaLaserChip003Status(GgafCore::GgafStatus* p);
    //�X�g���G�A���[�U�[
    static GgafCore::GgafStatus* resetEnemyStraeaLaserChip004Status(GgafCore::GgafStatus* p);
    //�I�����X�i���e�B�X�����B�A�̃n�b�`�j
    static GgafCore::GgafStatus* resetEnemyOmulusStatus(GgafCore::GgafStatus* p);
    //�G���X�i���e�B�X�����B�A�̃n�b�`�j
    static GgafCore::GgafStatus* resetEnemyEmusStatus(GgafCore::GgafStatus* p);
    //�G���X�̃��[�U�[
    static GgafCore::GgafStatus* resetEnemyEmusLaserChip001Status(GgafCore::GgafStatus* p);
    //�G�e�B�X
    static GgafCore::GgafStatus* resetEnemyEtisStatus(GgafCore::GgafStatus* p);
    //���X
    static GgafCore::GgafStatus* resetEnemyRisStatus(GgafCore::GgafStatus* p);
    //�Q���A
    static GgafCore::GgafStatus* resetEnemyGeriaStatus(GgafCore::GgafStatus* p);
    //�n���A
    static GgafCore::GgafStatus* resetEnemyHaliaStatus(GgafCore::GgafStatus* p);
    //���܂��P
    static GgafCore::GgafStatus* resetEnemyTamago01Status(GgafCore::GgafStatus* p);
    //�C���P
    static GgafCore::GgafStatus* resetEnemyIrceStatus(GgafCore::GgafStatus* p);
    //���e�B�X�����B�A�i�g�[���X�j
    static GgafCore::GgafStatus* resetEnemyRatislaviaStatus(GgafCore::GgafStatus* p);
    //�n�`�{�b�N�X001
    static GgafCore::GgafStatus* resetWall001Status(GgafCore::GgafStatus* p);
    //�n�`�v���Y��001
    static GgafCore::GgafStatus* resetWall001PrismStatus(GgafCore::GgafStatus* p);
    //�A���X
    static GgafCore::GgafStatus* resetEnemyAllasStatus(GgafCore::GgafStatus* p);
    //�E�[�m�~�A
    static GgafCore::GgafStatus* resetEnemyUnomiaStatus(GgafCore::GgafStatus* p);
    //�G�~���A
    static GgafCore::GgafStatus* resetEnemyEmiliaStatus(GgafCore::GgafStatus* p);
    //�G�~���A�f��
    static GgafCore::GgafStatus* resetEnemyEmiliaFragmentStatus(GgafCore::GgafStatus* p);
    //�G�~���A�f�Ђ̒f��
    static GgafCore::GgafStatus* resetEnemyEmiliaFragment2Status(GgafCore::GgafStatus* p);
    //�G�~���A�f�Ђ̒f�Ђ̒f��
    static GgafCore::GgafStatus* resetEnemyEmiliaFragment3Status(GgafCore::GgafStatus* p);
    //MP�A�C�e����
    static GgafCore::GgafStatus* resetMagicPointItem001Status(GgafCore::GgafStatus* p);
    //MP�A�C�e����
    static GgafCore::GgafStatus* resetMagicPointItem002Status(GgafCore::GgafStatus* p);
    //MP�A�C�e����
    static GgafCore::GgafStatus* resetMagicPointItem003Status(GgafCore::GgafStatus* p);
    //�X�R�A�A�C�e��
    static GgafCore::GgafStatus* resetScoreItem001Status(GgafCore::GgafStatus* p);
    //Vreath�A�C�e��
    static GgafCore::GgafStatus* resetVreathItem001Status(GgafCore::GgafStatus* p);
    //�G�[�x
    static GgafCore::GgafStatus* resetEnemyEbeStatus(GgafCore::GgafStatus* p);
    //�q�Y�r�[
    static GgafCore::GgafStatus* resetEnemyHisbeStatus(GgafCore::GgafStatus* p);
    //�q�Y�r�[2
    static GgafCore::GgafStatus* resetEnemyHisbe002Status(GgafCore::GgafStatus* p);
    //�q�Y�r�[���[�U�[
    static GgafCore::GgafStatus* resetEnemyHisbeLaserChip001Status(GgafCore::GgafStatus* p);
    //�q�Y�r�[���[�U�[
    static GgafCore::GgafStatus* resetEnemyHisbeLaserChip002Status(GgafCore::GgafStatus* p);
    //�q�Y�r�[���[�U�[
    static GgafCore::GgafStatus* resetEnemyHisbeLaserChip003Status(GgafCore::GgafStatus* p);
    //�h���X�e�A
    static GgafCore::GgafStatus* resetEnemyDrasteaStatus(GgafCore::GgafStatus* p);
    //�^�����e
    static GgafCore::GgafStatus* resetEnemyTalanteStatus(GgafCore::GgafStatus* p);
    //�G�X�g���G�A
    static GgafCore::GgafStatus* resetEnemyEsperiaStatus(GgafCore::GgafStatus* p);
    //�G�X�g���G�A���[�U�[
    static GgafCore::GgafStatus* resetEnemyEsperiaLaserChip001Status(GgafCore::GgafStatus* p);
    //�O�[�e�X�g
    static GgafCore::GgafStatus* resetTestGuStatus(GgafCore::GgafStatus* p);
    //�`���L�[�e�X�g
    static GgafCore::GgafStatus* resetTestChokiStatus(GgafCore::GgafStatus* p);
    //�p�[�e�X�g
    static GgafCore::GgafStatus* resetTestPaStatus(GgafCore::GgafStatus* p);
    //�m�[�}���[�e�X�g
    static GgafCore::GgafStatus* resetTestNomalStatus(GgafCore::GgafStatus* p);
    //�O�[�V���b�g
    static GgafCore::GgafStatus* resetTestGuShotStatus(GgafCore::GgafStatus* p);
    //�`���L�[�V���b�g
    static GgafCore::GgafStatus* resetTestChokiShotStatus(GgafCore::GgafStatus* p);
    //�p�[�V���b�g
    static GgafCore::GgafStatus* resetTestPaShotStatus(GgafCore::GgafStatus* p);
    //�m�[�}���[�V���b�g
    static GgafCore::GgafStatus* resetTestNomalShotStatus(GgafCore::GgafStatus* p);
    //���e�B�X�����B�A�A�C
    static GgafCore::GgafStatus* resetEnemyRatislaviaEyeStatus(GgafCore::GgafStatus* p);
    //���e�B�X�����B�A�A�C�p�X�g���[�g���[�U�[001
    static GgafCore::GgafStatus* resetEnemyRatislaviaEyeStraightLaserChip001Status(GgafCore::GgafStatus* p);
    //�G���~�I�l
    static GgafCore::GgafStatus* resetEnemyErmioneStatus(GgafCore::GgafStatus* p);
    //�G���~�I�l�r�̓�
    static GgafCore::GgafStatus* resetEnemyErmioneArmHeadStatus(GgafCore::GgafStatus* p);
    //�G���~�I�l�r�̓���
    static GgafCore::GgafStatus* resetEnemyErmioneArmBodyStatus(GgafCore::GgafStatus* p);
    //�G���~�I�l�r�̎�_
    static GgafCore::GgafStatus* resetEnemyErmioneArmWeakStatus(GgafCore::GgafStatus* p);
    //�A�b�|�[
    static GgafCore::GgafStatus* resetEnemyApphoStatus(GgafCore::GgafStatus* p);
    //�A���e�B�I�y
    static GgafCore::GgafStatus* resetEnemyAntiopeStatus(GgafCore::GgafStatus* p);
    //�f���w�C�h
    static GgafCore::GgafStatus* resetEnemyDelheidStatus(GgafCore::GgafStatus* p);
    //�A���T�i
    static GgafCore::GgafStatus* resetEnemyAlisanaStatus(GgafCore::GgafStatus* p);
    //�C�[�_
    static GgafCore::GgafStatus* resetEnemyIdaStatus(GgafCore::GgafStatus* p);
    //�^�S���X
    static GgafCore::GgafStatus* resetEnemyThagorasStatus(GgafCore::GgafStatus* p);
    //�I���g�D�i
    static GgafCore::GgafStatus* resetEnemyOrtunaStatus(GgafCore::GgafStatus* p);
    //�O����
    static GgafCore::GgafStatus* resetEnemyGlajaStatus(GgafCore::GgafStatus* p);
    //�O�������e
    static GgafCore::GgafStatus* resetEnemyGlajaLance001Status(GgafCore::GgafStatus* p);
    //�h�D�[�i
    static GgafCore::GgafStatus* resetEnemyDunaStatus(GgafCore::GgafStatus* p);
    //�I�[�c�@���e�B�A
    static GgafCore::GgafStatus* resetEnemyOzartiaStatus(GgafCore::GgafStatus* p);
    //�I�[�c�@���e�B�A�V���b�g�O�P(�ǃu���b�N)
    static GgafCore::GgafStatus* resetEnemyOzartiaShot01Status(GgafCore::GgafStatus* p);
    //�I�[�c�@���e�B�A���[�U�[�`�b�v
    static GgafCore::GgafStatus* resetEnemyOzartiaLaserChip01Status(GgafCore::GgafStatus* p);
    //�I�[�c�@���e�B�A�X��
    static GgafCore::GgafStatus* resetEnemyOzartiaPillar01Status(GgafCore::GgafStatus* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
