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


    /**
     * �D�ʐ��𒲂ׂ�
     * @param kind_my
     * @param kind_enemy
     * @return �ȉ��̕\�Q�ƁB
     * <table>
     * <tr><th>0��菬����         </th><th>0   </th><th>0���傫��         </th></tr>
     * <tr><td>attribute_my�̕�����   </td><td>���i</td><td>kind_my�̕����D��   </td></tr>
     * <tr><td>attribute_enemy�̕����D��</td><td>���i</td><td>kind_enemy�̕�����</td></tr>
     * </table>
     */
    static int judgeMyDomination(actorkind attribute_my, actorkind attribute_enemy) {
        int ret = 0;
        if (attribute_my & ATTRIBUTE_GU) {
            if (attribute_enemy & ATTRIBUTE_CHOKI) {
                ret++;
            }
            if (attribute_enemy & ATTRIBUTE_PA) {
                ret--;
            }
        }

        if (attribute_my & ATTRIBUTE_CHOKI) {
            if (attribute_enemy & ATTRIBUTE_PA) {
                ret++;
            }
            if (attribute_enemy & ATTRIBUTE_GU) {
                ret--;
            }
        }

        if (attribute_my & ATTRIBUTE_PA) {
            if (attribute_enemy & ATTRIBUTE_GU) {
                ret++;
            }
            if (attribute_enemy & ATTRIBUTE_CHOKI) {
                ret--;
            }
        }
        return ret;
    }


    static int judgeEnemyDomination(actorkind kattribute_enemy, actorkind attribute_my) {
        int ret = 0;
        if (kattribute_enemy & ATTRIBUTE_GU) {
            if (attribute_my & ATTRIBUTE_CHOKI) {
                ret++;
            }
            if (attribute_my & ATTRIBUTE_PA) {
                ret--;
            }
        }

        if (kattribute_enemy & ATTRIBUTE_CHOKI) {
            if (attribute_my & ATTRIBUTE_PA) {
                ret++;
            }
            if (attribute_my & ATTRIBUTE_GU) {
                ret--;
            }
        }

        if (kattribute_enemy & ATTRIBUTE_PA) {
            if (attribute_my & ATTRIBUTE_GU) {
                ret++;
            }
            if (attribute_my & ATTRIBUTE_CHOKI) {
                ret--;
            }
        }
        return ret;
    }

    /**
     * ����(���@)�̗̑͌v�Z .
     * @param prm_pMy  ����(���@)
     * @param prm_pOpp ����(���@�ȊO)
     * @return ����(���@)�̗̑�
     */
    static int calcMyStamina(GgafCore::GgafMainActor* prm_pMy, GgafCore::GgafMainActor* prm_pOpp) {
        GgafCore::GgafStatus* pStatMy = prm_pMy->_pStatus;
        GgafCore::GgafStatus* pStatOpp = prm_pOpp->_pStatus;

        //�D���򐫔���
        int my_domi = MyStgUtil::judgeMyDomination(pStatMy->get(STAT_Attribute), pStatOpp->get(STAT_Attribute));
        //����(�G)�U����
        int opp_attack = pStatOpp->get(STAT_Attack);
        //�D���򐫂ɉ����Ėh�䗦���悸��
        if (my_domi > 0) {
            //�������D����
            return pStatMy->minus(STAT_Stamina,
                                  (int)(opp_attack * pStatMy->getDouble(STAT_DominantDefenceRate)));
        } else if (my_domi < 0) {
            //�������򐫎�
            return pStatMy->minus(STAT_Stamina,
                                  (int)(opp_attack * pStatMy->getDouble(STAT_RecessiveDefenceRate)));
        } else {
            //����(�G)�Ɠ��i��
            return pStatMy->minus(STAT_Stamina,
                                  (int)(opp_attack * pStatMy->getDouble(STAT_DefaultDefenceRate)));
        }
    }

    /**
     * ����(�G�@)�̗̑͌v�Z .
     * �̗͂�0�ɂȂ����ꍇ�A���肪���@�֘A�������ꍇ
     * �Q�[���X�R�A�A�Q�[�������N�A����(�G�@)�̏����t�H�[���[�V�����ւ̔j�󂳂�܂����ʒm�A��
     * �������s���Ă��܂��B
     * @param prm_pMy  ����(�G�@)
     * @param prm_pOpp ����(�G�@�ȊO)
     * @return ����(�G�@)�̗̑�
     */
    static int calcEnemyStamina(GgafCore::GgafMainActor* prm_pEnemy, GgafCore::GgafMainActor* prm_pOpp) {
        GgafCore::GgafStatus* pStatEnemy = prm_pEnemy->_pStatus;
        GgafCore::GgafStatus* pStatOpp = prm_pOpp->_pStatus;
        //�D���򐫔���
        int enemy_domi = MyStgUtil::judgeEnemyDomination(pStatEnemy->get(STAT_Attribute), pStatOpp->get(STAT_Attribute));
        //����(���@)�U����
        int opp_attack = pStatOpp->get(STAT_Attack);
        //�D���򐫂ɉ����Ėh�䗦���悸��
        int enemy_stamina;
        if (enemy_domi > 0) {
            //�����i�G�j���D����
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_DominantDefenceRate)));
        } else if (enemy_domi < 0) {
            //�����i�G�j���򐫎�
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_RecessiveDefenceRate)));
        } else {
            //����(���@)�Ɠ��i��
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_DefaultDefenceRate)));
        }
        if (enemy_stamina <= 0 && (prm_pOpp->getKind() & KIND_MY)) {
            //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
            _SCORE_ += pStatEnemy->get(STAT_AddScorePoint);      //���_
            _RANK_  += pStatEnemy->getDouble(STAT_AddRankPoint); //�����N���Z
            prm_pEnemy->notifyDestroyedToFormation(); //�ґ��S�Ŕ���ɗL���Ȕj��̂�����ł�����ʒm

            if (prm_pEnemy->getPlatformScene()->instanceOf(Obj_RankUpStage)) {
                //�����N�A�b�v�X�e�[�W�̓G�Ȃ�΁A
                RankUpStage* pRankUpStage = (RankUpStage*)(prm_pEnemy->getPlatformScene());
                pRankUpStage->hit_enemy_num_ ++; //�����N�A�b�v�X�e�[�W�̓G�|������I�J�E���g�A�b�v
            }
        }
        return enemy_stamina;
    }


    /**
     * �ΏۃA�N�^�[�ɕR���������G�t�F�N�g���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(_pStatus)�� STAT_ExplosionEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̔����G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ NULL�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateExplosionEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
        GgafDxCore::GgafDxDrawableActor* pE = NULL;
        switch (prm_pActor->_pStatus->get(STAT_ExplosionEffectKind)) {
            case 0: {
                pE = NULL; //�����G�t�F�N�g����
                break;
            }
            case 1: {
                pE = employFromCommon(EffectExplosion001);
                break;
            }
            case 2: {
                pE = employFromCommon(EffectExplosion002);
                break;
            }
            case 3: {
                pE = employFromCommon(EffectExplosion003);
                break;
            }
            default: {
                _TRACE_("���x���� �Ή� ExplosionEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName());
                pE = NULL;
                break;
            }
        }

        if (pE) {
            //�o�����W��ݒ�
            pE->locateWith(prm_pActor);
            pE->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
        }
        return pE;
    }

    /**
     * �ΏۃA�N�^�[�ɕR�����ێ��A�C�e�����A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(_pStatus)�� STAT_ItemKind �̒l�ɂ���ăA�C�e����ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̕ێ��A�C�e���i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ NULL�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateItemOf(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
        GgafDxCore::GgafDxDrawableActor* pI = NULL;
        switch (prm_pActor->_pStatus->get(STAT_ItemKind)) {
            case 0: {
                pI = NULL; //�A�C�e������
                break;
            }
            case 1: {
                pI = employFromCommon(MagicPointItem001);
                break;
            }
            case 2: {
                pI = employFromCommon(MagicPointItem002);
                break;
            }
            default: {
                _TRACE_("���x���� �Ή� ExplosionEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName());
                pI = NULL;
                break;
            }
        }
        if (pI) {
            //�o�����W��ݒ�
            pI->locateWith(prm_pActor);
        }
        return pI;
    }

    /**
     * �ΏۃA�N�^�[�ɕR��������G�t�F�N�g���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(_pStatus)�� STAT_EntryEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̓���G�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ NULL�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateEntryEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
        GgafDxCore::GgafDxDrawableActor* pE = NULL;
        switch (prm_pActor->_pStatus->get(STAT_EntryEffectKind)) {
            case 0: {
                pE = NULL; //����G�t�F�N�g����
                break;
            }
            case 1: {
                pE = employFromCommon(EffectEntry001);
                break;
            }
            case 2: {
                pE = employFromCommon(EffectEntry002);
                break;
            }
            case 3: {
                pE = employFromCommon(EffectEntry003);
                break;
            }
            default: {
                pE = NULL;
                break;
            }
        }
        if (pE) {
            //�o�����W��ݒ�
            pE->locateWith(prm_pActor);
        }
        return pE;
    }

    /**
     * �ΏۃA�N�^�[�̕R�����A�t�H�[���[�V�����S�ŃG�t�F�N�g�ƃX�R�A���Z���� .
     * �X�e�[�^�X(_pStatus)�� STAT_FormationDestroyedEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̃t�H�[���[�V�����S�ŃG�t�F�N�g�i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ NULL�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateFormationDestroyedEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
        int addscore = prm_pActor->_pStatus->get(STAT_FormationDestroyedAddScorePoint); //�t�H�[���[�V�����S�œ��_���Z
        _SCORE_ += addscore;
        GgafDxCore::GgafDxDrawableActor* pE = NULL;
        switch (prm_pActor->_pStatus->get(STAT_FormationDestroyedEffectKind)) {
            case 0: {
                pE = NULL; //�G�t�F�N�g����
                break;
            }
            case 1: {
                //1�͒ʏ�̃t�H�[���[�V�����{�[�i�X�X�R�A�\���G�t�F�N�g
                SpriteLabelBonus001* pLabel = employForceFromCommon(SpriteLabelBonus001);
                pLabel->locateWith(prm_pActor);
                pLabel->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
                std::string s = ITOS(addscore);
                pLabel->update(s.c_str());
                pE = pLabel;
                break;
            }
//            case 2: {
//                pE = employFromCommon(EffectExplosion002);
//                break;
//            }
//            case 3: {
//                pE = employFromCommon(EffectExplosion003);
//                break;
//            }
            default: {
                _TRACE_("���x���� �Ή� STAT_FormationDestroyedEffectKind ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName());
                pE = NULL;
                break;
            }
        }

//        if (pE) {
//            //�o�����W��ݒ�
//            pE->locateWith(prm_pActor);
//            pE->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
//        }
        return pE;
    }

    /**
     * �ΏۃA�N�^�[�̂ɕR�����t�H�[���[�V�����S�ŃA�C�e�����A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(_pStatus)�� STAT_FormationDestroyedItemKind �̒l�ɂ���ăA�C�e����ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̃t�H�[���[�V�����S�ŃA�C�e���i�����ς݁j�B���́A�擾�ł��Ȃ��ꍇ NULL�B
     */
    static GgafDxCore::GgafDxDrawableActor* activateFormationDestroyedItemOf(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
        GgafDxCore::GgafDxDrawableActor* pI = NULL;
        switch (prm_pActor->_pStatus->get(STAT_FormationDestroyedItemKind)) {
            case 0: {
                pI = NULL; //�A�C�e������
                break;
            }
            case 1: {
                pI = employFromCommon(MagicPointItem001);
                break;
            }
            case 2: {
                pI = employFromCommon(MagicPointItem002);
                break;
            }
            default: {
                _TRACE_("���x���� �Ή� STAT_FormationDestroyedItemKind ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName());
                pI = NULL;
                break;
            }
        }
        if (pI) {
            //�o�����W��ݒ�
            pI->locateWith(prm_pActor);
        }
        return pI;
    }


    static int nextRepeatVal(int prm_id) {
        return 0;
    }

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
	//�A�C�e��
	static GgafCore::GgafStatus* resetMagicPointItem001Status(GgafCore::GgafStatus* p);
	//�ґ��S�ŃA�C�e��
	static GgafCore::GgafStatus* resetMagicPointItem002Status(GgafCore::GgafStatus* p);
	//�w�[�x
	static GgafCore::GgafStatus* resetEnemyHebeStatus(GgafCore::GgafStatus* p);
	//�V�Y�r�[
	static GgafCore::GgafStatus* resetEnemyThisbeStatus(GgafCore::GgafStatus* p);
	//�V�Y�r�[���[�U�[
	static GgafCore::GgafStatus* resetEnemyThisbeLaserChip001Status(GgafCore::GgafStatus* p);
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
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
