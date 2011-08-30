#ifndef MYSTGUTIL_H_
#define MYSTGUTIL_H_

#define STATUS(X) MyStgUtil::reset##X##Status(NEW GgafCore::GgafStatus(12))

namespace MyStg2nd {

class MyStgUtil: public GgafDx9LibStg::StgUtil {
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
     * @param pStatMy  ����(���@)�̃X�e�[�^�X
     * @param kind_my  ����(���@)�̎��
     * @param pStatOpp ����(�G�@)�̃X�e�[�^�X
     * @param kind_opp ����(�G�@)�̎��
     * @return
     */
    static int calcMyStatus(GgafCore::GgafStatus* pStatMy,
                             actorkind kind_my,
                             GgafCore::GgafStatus* pStatOpp,
                             actorkind kind_opp) {
        //�D���򐫔���
        int my_domi = MyStgUtil::judgeMyDominant(kind_my, kind_opp);
        //����U����
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
            //����Ɠ��i��
            return pStatMy->minus(STAT_Stamina,
                                  (int)(opp_attack * pStatMy->getDouble(STAT_DefaultDefenceRate)));
        }
    }

    static int calcEnemyStatus(GgafCore::GgafStatus* pStatEnemy,
                                actorkind kind_enemy,
                                GgafCore::GgafStatus* pStatOpp,
                                actorkind kind_opp) {
        //�D���򐫔���
        int enemy_domi = MyStgUtil::judgeEnemyDominant(kind_enemy, kind_opp);
        //_TRACE_("enemy_domi="<<enemy_domi);
        //����(���@�֘A)�U����
        int opp_attack = pStatOpp->get(STAT_Attack);
        //_TRACE_("my_attack="<<my_attack);
        //�D���򐫂ɉ����Ėh�䗦���悸��
        int enemy_stamina;
        if (enemy_domi > 0) {
            //�����i�G�֘A�j���D����
//_TRACE_("pStatEnemy->get(STAT_DominantDefenceRate)="<<pStatEnemy->get(STAT_DominantDefenceRate));

            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_DominantDefenceRate)));
        //_TRACE_("enemy_stamina="<<enemy_stamina);
        } else if (enemy_domi < 0) {
            //�����i�G�֘A�j���򐫎�
//_TRACE_("pStatEnemy->get(STAT_DominantDefenceRate)="<<pStatEnemy->getDouble(STAT_RecessiveDefenceRate));
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->get(STAT_RecessiveDefenceRate)));

        _TRACE_("enemy_stamina="<<enemy_stamina);
        } else {
//_TRACE_("pStatEnemy->get(STAT_DominantDefenceRate)="<<pStatEnemy->getDouble(STAT_DefaultDefenceRate));

            //����(���@�֘A)�Ɠ��i��
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_DefaultDefenceRate)));
        //_TRACE_("enemy_stamina="<<enemy_stamina);
        }
//_TRACE_("enemy_stamina="<<enemy_stamina);
        if (enemy_stamina <= 0 && (kind_opp & KIND_MY)) {
            //����̎�ʂ� My �Ȃ�Γ��_���Z
            _SCORE_ += pStatEnemy->get(STAT_AddScorePoint);
            _RANK_  += pStatEnemy->getDouble(STAT_AddRankPoint);
        }

        return enemy_stamina;

    }

    static int nextRepeatVal(int prm_id) {
        return 0;
    }




    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�X�e�[�^�XCreater.xls�v����s���Ă������������B
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
	//�A�C�e��
	static GgafCore::GgafStatus* resetMagicPointItem001Status(GgafCore::GgafStatus* p);
	//
	static GgafCore::GgafStatus* resetEnemyMassaliaStatus(GgafCore::GgafStatus* p);
	//
	static GgafCore::GgafStatus* resetMyOptionStatus(GgafCore::GgafStatus* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
