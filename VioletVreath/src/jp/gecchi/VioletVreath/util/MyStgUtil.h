#ifndef MYSTGUTIL_H_
#define MYSTGUTIL_H_

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL VioletVreath::MyStgUtil

#define STATUS(X) (NEW GgafCore::GgafStatus(STAT_Sentry+1, VioletVreath::MyStgUtil::reset##X##Status))



namespace VioletVreath {



class MyStgUtil : public GgafLib::StgUtil {
public:
    enum EffectKind {
        EF_NOTHING,
        EF_ENTRY_SMALL001,
        EF_ENTRY_MIDDLE001,
        EF_ENTRY003,
        EF_EXPLOSION001 ,
        EF_EXPLOSION002,
        EF_EXPLOSION003,
        EF_BONUS001,
        EF_EXPLO_AND_BONUS001,
        EF_TURBO,
    };

    enum ItemKind {
        ITEM_MP_SMALL = 1,
        ITEM_MP_MIDDLE,
    };
    enum ShotKind {
        SHOT_SMALL001 = 1,
        SHOT_SMALL002,
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
     * ����(���@)�̗̑͌v�Z .
     * @param prm_pMy  ����(���@)
     * @param prm_pOpp ����(���@�ȊO)
     * @return ����(���@)�̗̑�
     */
    static int calcMyStamina(GgafCore::GgafMainActor* prm_pMy, GgafCore::GgafMainActor* prm_pOpp);

    /**
     * ����(�G�@)�̗̑͌v�Z .
     * �̗͂�0�ɂȂ����ꍇ�A���肪���@�֘A�������ꍇ
     * �Q�[���X�R�A�A�Q�[�������N�A����(�G�@)�̏����t�H�[���[�V�����ւ̔j�󂳂�܂����ʒm�A��
     * �������s���Ă��܂��B
     * @param prm_pMy  ����(�G�@)
     * @param prm_pOpp ����(�G�@�ȊO)
     * @return ����(�G�@)�̗̑�
     */
    static int calcEnemyStamina(GgafCore::GgafMainActor* prm_pEnemy, GgafCore::GgafMainActor* prm_pOpp);

    /**
     * �ΏۃA�N�^�[�ɕR���������G�t�F�N�g���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(_pStatus)�� STAT_ExplosionEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̔����G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateExplosionEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    static GgafDxCore::GgafDxDrawableActor* activateShotOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR�����ێ��A�C�e�����A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(_pStatus)�� STAT_ItemKind �̒l�ɂ���ăA�C�e����ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̕ێ��A�C�e���i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateItemOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR�������ŃG�t�F�N�g���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * ���^�@�̏ꍇ�̃X�R�A�\�����Ɏg�p�����B<BR>
     * �X�e�[�^�X(_pStatus)�� STAT_DestroyedEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^
     * @return �ΏۃA�N�^�[�̏��ŃG�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateDestroyedEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR��������G�t�F�N�g���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(_pStatus)�� STAT_EntryEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̓���G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateEntryEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR�����ޏ�G�t�F�N�g���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(_pStatus)�� STAT_LeaveEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̑ޏ�G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateLeaveEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�̕R�����A�t�H�[���[�V�����S�ŃG�t�F�N�g�ƃX�R�A���Z���� .
     * �X�e�[�^�X(_pStatus)�� STAT_FormationDestroyedEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̃t�H�[���[�V�����S�ŃG�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateFormationDestroyedEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);
    /**
     * �ΏۃA�N�^�[�̂ɕR�����t�H�[���[�V�����S�ŃA�C�e�����A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(_pStatus)�� STAT_FormationDestroyedItemKind �̒l�ɂ���ăA�C�e����ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̃t�H�[���[�V�����S�ŃA�C�e���i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateFormationDestroyedItemOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * �ΏۃA�N�^�[�ɕR�����ŗL�G�t�F�N�g�i���̂P�j���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(_pStatus)�� STAT_ProperEffect01Kind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̓���G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ nullptr�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateProperEffect01Of(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�X�e�[�^�XCreater.xls�v����s�����ƁB
    // gen01 start
	//���@���[�U�[
	static GgafCore::GgafStatus* resetMyStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//�I�v�V�����J�[�u���[�U�[
	static GgafCore::GgafStatus* resetMyOptionWateringLaserChip001Status(GgafCore::GgafStatus* p);
	//�I�v�V�����X�g���[�g���[�U�[
	static GgafCore::GgafStatus* resetMyOptionStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//�g�D�s�[�h
	static GgafCore::GgafStatus* resetMyTorpedoStatus(GgafCore::GgafStatus* p);
	//�g�D�s�[�h����
	static GgafCore::GgafStatus* resetMyTorpedoBlastStatus(GgafCore::GgafStatus* p);
	//���@
	static GgafCore::GgafStatus* resetMyShipStatus(GgafCore::GgafStatus* p);
	//�G�X�g���[�g���[�U�[001
	static GgafCore::GgafStatus* resetEnemyStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//�G�J�[�u���[�U�[001
	static GgafCore::GgafStatus* resetEnemyCurveLaserChip001Status(GgafCore::GgafStatus* p);
	//�P���X
	static GgafCore::GgafStatus* resetEnemyCeresStatus(GgafCore::GgafStatus* p);
	//�P���X�V���b�g001
	static GgafCore::GgafStatus* resetEnemyCeresShot001Status(GgafCore::GgafStatus* p);
	//�A�X�g���G�A
	static GgafCore::GgafStatus* resetEnemyAstraeaStatus(GgafCore::GgafStatus* p);
	//�A�X�g���G�A���[�U�[
	static GgafCore::GgafStatus* resetEnemyAstraeaLaserChip001Status(GgafCore::GgafStatus* p);
	//�A�X�g���G�A���[�U�[
	static GgafCore::GgafStatus* resetEnemyAstraeaLaserChip002Status(GgafCore::GgafStatus* p);
	//�A�X�g���G�A���[�U�[
	static GgafCore::GgafStatus* resetEnemyAstraeaLaserChip003Status(GgafCore::GgafStatus* p);
	//�A�X�g���G�A���[�U�[
	static GgafCore::GgafStatus* resetEnemyAstraeaLaserChip004Status(GgafCore::GgafStatus* p);
	//�������X�i�V�����B�A�̃n�b�`�j
	static GgafCore::GgafStatus* resetEnemyRomulusStatus(GgafCore::GgafStatus* p);
	//�����X�i�V�����B�A�̃n�b�`�j
	static GgafCore::GgafStatus* resetEnemyRemusStatus(GgafCore::GgafStatus* p);
	//�����X�̃��[�U�[
	static GgafCore::GgafStatus* resetEnemyRemusLaserChip001Status(GgafCore::GgafStatus* p);
	//���e�B�X
	static GgafCore::GgafStatus* resetEnemyMetisStatus(GgafCore::GgafStatus* p);
	//�C���X
	static GgafCore::GgafStatus* resetEnemyIrisStatus(GgafCore::GgafStatus* p);
	//�W���m�[
	static GgafCore::GgafStatus* resetEnemyJunoStatus(GgafCore::GgafStatus* p);
	//�^����
	static GgafCore::GgafStatus* resetEnemyThaliaStatus(GgafCore::GgafStatus* p);
	//�ėp�V���b�g001
	static GgafCore::GgafStatus* resetShot001Status(GgafCore::GgafStatus* p);
	//�ėp�V���b�g002
	static GgafCore::GgafStatus* resetShot002Status(GgafCore::GgafStatus* p);
	//���܂��P
	static GgafCore::GgafStatus* resetEnemyTamago01Status(GgafCore::GgafStatus* p);
	//�L���P
	static GgafCore::GgafStatus* resetEnemyCirceStatus(GgafCore::GgafStatus* p);
	//�ėp�V���b�g003�~�j���[�U�[
	static GgafCore::GgafStatus* resetShot003Status(GgafCore::GgafStatus* p);
	//�~�j���[�U�[�V���b�g
	static GgafCore::GgafStatus* resetShot004Status(GgafCore::GgafStatus* p);
	//�V�����B�A�i�g�[���X�j
	static GgafCore::GgafStatus* resetEnemySylviaStatus(GgafCore::GgafStatus* p);
	//�n�`�{�b�N�X001
	static GgafCore::GgafStatus* resetWall001Status(GgafCore::GgafStatus* p);
	//�n�`�v���Y��001
	static GgafCore::GgafStatus* resetWall001PrismStatus(GgafCore::GgafStatus* p);
	//�p���X
	static GgafCore::GgafStatus* resetEnemyPallasStatus(GgafCore::GgafStatus* p);
	//�G�E�m�~�A
	static GgafCore::GgafStatus* resetEnemyEunomiaStatus(GgafCore::GgafStatus* p);
	//���@�V���b�g
	static GgafCore::GgafStatus* resetMyShot001Status(GgafCore::GgafStatus* p);
	//�}�b�T���A
	static GgafCore::GgafStatus* resetEnemyMassaliaStatus(GgafCore::GgafStatus* p);
	//�}�b�T���A�f��
	static GgafCore::GgafStatus* resetEnemyMassaliaFragmentStatus(GgafCore::GgafStatus* p);
	//�}�b�T���A�f�Ђ̒f��
	static GgafCore::GgafStatus* resetEnemyMassaliaFragment2Status(GgafCore::GgafStatus* p);
	//�}�b�T���A�f�Ђ̒f�Ђ̒f��
	static GgafCore::GgafStatus* resetEnemyMassaliaFragment3Status(GgafCore::GgafStatus* p);
	//�I�v�V����
	static GgafCore::GgafStatus* resetMyOptionStatus(GgafCore::GgafStatus* p);
	//MP�A�C�e��
	static GgafCore::GgafStatus* resetMagicPointItem001Status(GgafCore::GgafStatus* p);
	//�ґ��S��MP�A�C�e��
	static GgafCore::GgafStatus* resetMagicPointItem002Status(GgafCore::GgafStatus* p);
	//�X�R�A�A�C�e��
	static GgafCore::GgafStatus* resetScoreItem001Status(GgafCore::GgafStatus* p);
	//Vreath�A�C�e��
	static GgafCore::GgafStatus* resetVreathItem001Status(GgafCore::GgafStatus* p);
	//�w�[�x
	static GgafCore::GgafStatus* resetEnemyHebeStatus(GgafCore::GgafStatus* p);
	//�V�Y�r�[
	static GgafCore::GgafStatus* resetEnemyThisbeStatus(GgafCore::GgafStatus* p);
	//�V�Y�r�[2
	static GgafCore::GgafStatus* resetEnemyThisbe002Status(GgafCore::GgafStatus* p);
	//�V�Y�r�[���[�U�[
	static GgafCore::GgafStatus* resetEnemyThisbeLaserChip001Status(GgafCore::GgafStatus* p);
	//�V�Y�r�[���[�U�[
	static GgafCore::GgafStatus* resetEnemyThisbeLaserChip002Status(GgafCore::GgafStatus* p);
	//�V�Y�r�[���[�U�[
	static GgafCore::GgafStatus* resetEnemyThisbeLaserChip003Status(GgafCore::GgafStatus* p);
	//�A�h���X�e�A
	static GgafCore::GgafStatus* resetEnemyAdrasteaStatus(GgafCore::GgafStatus* p);
	//�A�^�����e
	static GgafCore::GgafStatus* resetEnemyAtalanteStatus(GgafCore::GgafStatus* p);
	//�A�X�g���G�A
	static GgafCore::GgafStatus* resetEnemyHesperiaStatus(GgafCore::GgafStatus* p);
	//�A�X�g���G�A���[�U�[
	static GgafCore::GgafStatus* resetEnemyHesperiaLaserChip001Status(GgafCore::GgafStatus* p);
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
	//�V�����B�A�A�C
	static GgafCore::GgafStatus* resetEnemySylviaEyeStatus(GgafCore::GgafStatus* p);
	//�V�����B�A�A�C�p�X�g���[�g���[�U�[001
	static GgafCore::GgafStatus* resetEnemySylviaEyeStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//�w���~�I�l
	static GgafCore::GgafStatus* resetEnemyHermioneStatus(GgafCore::GgafStatus* p);
	//�w���~�I�l�r�̓�
	static GgafCore::GgafStatus* resetEnemyHermioneArmHeadStatus(GgafCore::GgafStatus* p);
	//�w���~�I�l�r�̓���
	static GgafCore::GgafStatus* resetEnemyHermioneArmBodyStatus(GgafCore::GgafStatus* p);
	//�w���~�I�l�r�̎�_
	static GgafCore::GgafStatus* resetEnemyHermioneArmWeakStatus(GgafCore::GgafStatus* p);
	//�T�b�t�H�[
	static GgafCore::GgafStatus* resetEnemySapphoStatus(GgafCore::GgafStatus* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
