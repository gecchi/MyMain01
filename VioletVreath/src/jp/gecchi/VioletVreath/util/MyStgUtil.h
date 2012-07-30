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
     * <tr><td>kind_my�̕�����   </td><td>���i</td><td>kind_my�̕����D��   </td></tr>
     * <tr><td>kind_enemy�̕����D��</td><td>���i</td><td>kind_enemy�̕�����</td></tr>
     * </table>
     */
    static int judgeMyDominant(actorkind kind_my, actorkind kind_enemy) {
        int ret = 0;
        if (kind_my & KIND_GU) {
            if (kind_enemy & KIND_CHOKI) {
                ret++;
            }
            if (kind_enemy & KIND_PA) {
                ret--;
            }
        }

        if (kind_my & KIND_CHOKI) {
            if (kind_enemy & KIND_PA) {
                ret++;
            }
            if (kind_enemy & KIND_GU) {
                ret--;
            }
        }

        if (kind_my & KIND_PA) {
            if (kind_enemy & KIND_GU) {
                ret++;
            }
            if (kind_enemy & KIND_CHOKI) {
                ret--;
            }
        }
        return ret;
    }


    static int judgeEnemyDominant(actorkind kind_enemy, actorkind kind_my) {
        int ret = 0;
        if (kind_enemy & KIND_GU) {
            if (kind_my & KIND_CHOKI) {
                ret++;
            }
            if (kind_my & KIND_PA) {
                ret--;
            }
        }

        if (kind_enemy & KIND_CHOKI) {
            if (kind_my & KIND_PA) {
                ret++;
            }
            if (kind_my & KIND_GU) {
                ret--;
            }
        }

        if (kind_enemy & KIND_PA) {
            if (kind_my & KIND_GU) {
                ret++;
            }
            if (kind_my & KIND_CHOKI) {
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
        actorkind kind_my = prm_pMy->getKind();
        GgafCore::GgafStatus* pStatOpp = prm_pOpp->_pStatus;
        actorkind kind_opp = prm_pOpp->getKind();

        //�D���򐫔���
        int my_domi = MyStgUtil::judgeMyDominant(kind_my, kind_opp);
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
        actorkind kind_enemy = prm_pEnemy->getKind();
        GgafCore::GgafStatus* pStatOpp = prm_pOpp->_pStatus;
        actorkind kind_opp = prm_pOpp->getKind();
        //�D���򐫔���
        int enemy_domi = MyStgUtil::judgeEnemyDominant(kind_enemy, kind_opp);
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
                                              (int)(opp_attack * pStatEnemy->get(STAT_RecessiveDefenceRate)));

        } else {
            //����(���@)�Ɠ��i��
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_DefaultDefenceRate)));
        }
        if (enemy_stamina <= 0 && (kind_opp & KIND_MY)) {
            //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
            _SCORE_ += pStatEnemy->get(STAT_AddScorePoint);      //���_
            _RANK_  += pStatEnemy->getDouble(STAT_AddRankPoint); //�����N���Z
            prm_pEnemy->notifyDestroyedToFormation(); //�ґ��S�Ŕ���ɗL���Ȕj��̂�����ł�����ʒm
        }

        return enemy_stamina;

    }



    /**
     * �ΏۃA�N�^�[�ɕR���������G�t�F�N�g���A�擾�ł���ΗL���ɂ��A�����Ԃ� .
     * �X�e�[�^�X(_pStatus)�� STAT_ExplosionEffectKind �̒l�ɂ���Ď�ނ��U�蕪������B
     * @param prm_pActor �ΏۃA�N�^�[
     * @return �ΏۃA�N�^�[�̔����G�t�F�N�g�B���́A�擾�ł��Ȃ��ꍇ NULL�B
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
     * @return �ΏۃA�N�^�[�̕ێ��A�C�e���B���́A�擾�ł��Ȃ��ꍇ NULL�B
     */
    static Item* activateItemOf(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
        Item* pI = NULL;
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
     * @return �ΏۃA�N�^�[�̓���G�t�F�N�g�B���́A�擾�ł��Ȃ��ꍇ NULL�B
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
	//���F�X�^
	static GgafCore::GgafStatus* resetEnemyVestaStatus(GgafCore::GgafStatus* p);
	//���e�B�X
	static GgafCore::GgafStatus* resetEnemyMetisStatus(GgafCore::GgafStatus* p);
	//�C���X
	static GgafCore::GgafStatus* resetEnemyIrisStatus(GgafCore::GgafStatus* p);
	//�W���m�[
	static GgafCore::GgafStatus* resetEnemyJunoStatus(GgafCore::GgafStatus* p);
	//�^�G��
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
	//�n�`�g�[���X
	static GgafCore::GgafStatus* resetTorusStatus(GgafCore::GgafStatus* p);
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
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
