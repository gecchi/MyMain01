#ifndef MYSTGUTIL_H_
#define MYSTGUTIL_H_
namespace MyStg2nd {

class MyStgUtil: public GgafDx9LibStg::StgUtil {
public:

    static char RANK_1stDeg[10][6];
    static char RANK_10thDeg[10][5];
    static char RANK_100thDeg[10][7];
    static char RANK_1000thDeg[10][9];
    static char RANK_10000thDeg[10][46];
    static char RANK_INF[7];

    /**
     * �����N���l���當����ϊ�
     * @param prm_rank �����N���l(1�`100000)
     * @param out ���ʏo��[80]�K�v
     * @return
     */
    static void getRankStr(int prm_rank, char* out);

    /**
     * �D�ʐ��𒲂ׂ�
     * @param kind_my
     * @param kind_enemy
     * @return �ȉ��̕\�Q�ƁB
     * <table>
     * <tr><th>0��菬����                        </th><th>0  </th><th>0���傫��                  </th></tr>
     * <tr><td>kind_my�̕�����       </td><td>���i</td><td>kind_my�̕����D��</td></tr>
     * <tr><td>kind_enemy�̕����D��</td><td>���i</td><td>kind_enemy�̕�����</td></tr>
     * <table>
     */
    static int judgeMyDominant(actorkint kind_my, actorkint kind_enemy) {
        ret = 0;
        if (kind_my & KIND_MY_SHOT_GU) {
            if (kind_enemy & KIND_ENEMY_SHOT_CHOKI) {
                ret++;
            }
            if (kind_enemy & KIND_ENEMY_SHOT_PA) {
                ret--;
            }
        }

        if (kind_my & KIND_MY_SHOT_CHOKI) {
            if (kind_enemy & KIND_ENEMY_SHOT_PA) {
                ret++;
            }
            if (kind_enemy & KIND_ENEMY_SHOT_GU) {
                ret--;
            }
        }

        if (kind_my & KIND_MY_SHOT_PA) {
            if (kind_enemy & KIND_ENEMY_SHOT_GU) {
                ret++;
            }
            if (kind_enemy & KIND_ENEMY_SHOT_CHOKI) {
                ret--;
            }
        }
        return ret;
    }


    static int judgeEnemyDominant(actorkint kind_enemy, actorkint kind_my) {
        ret = 0;
        if (kind_enemy & KIND_ENEMY_SHOT_GU) {
            if (kind_my & KIND_MY_SHOT_CHOKI) {
                ret++;
            }
            if (kind_my & KIND_MY_SHOT_PA) {
                ret--;
            }
        }

        if (kind_enemy & KIND_ENEMY_SHOT_CHOKI) {
            if (kind_my & KIND_MY_SHOT_PA) {
                ret++;
            }
            if (kind_my & KIND_MY_SHOT_GU) {
                ret--;
            }
        }

        if (kind_enemy & KIND_ENEMY_SHOT_PA) {
            if (kind_my & KIND_MY_SHOT_GU) {
                ret++;
            }
            if (kind_my & KIND_MY_SHOT_CHOKI) {
                ret--;
            }
        }
        return ret;
    }

    /**
     * �����̗̑͌v�Z
     * @param pMy
     * @param pEnemy
     * @return
     */
    static int calMyStamina(GgafCore::GgafActor* pMy, GgafCore::GgafActor* pEnemy) {
        int domi = MyStgUtil::judgeMyDominant(pMy->getGroupActor()->_kind, pEnemy->getGroupActor()->_kind);
        if (domi > 0) {
            //�������D����
            return pMy->pStatus->minus(STAT_Stamina, pEnemy->_pStatus->get(STAT_AttackRecessive)); //����̗򐫎��̍U���͂��󂯂�
        } else if (domi == 0) {
            //����Ɠ��i��
            return pMy->pStatus->minus(STAT_Stamina, pEnemy->_pStatus->get(STAT_Attack));
        } else if (domi < 0) {
            //�������򐫎�
            return pMy->pStatus->minus(STAT_Stamina, pEnemy->_pStatus->get(STAT_AttackRecessive)); //����̗D�����̍U���͂��󂯂�
        }
    }



    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�V�[��Creater.xls�v����s���Ă������������B
    // gen01 start
    //���@���[�U�[
    static void resetMyStraightLaserChip001Status(GgafCore::GgafActor* p);
    //���@
    static void resetMyShipStatus(GgafCore::GgafActor* p);
    //�P���X
    static void resetEnemyCeresStatus(GgafCore::GgafActor* p);
    //�P���X�V���b�g001
    static void resetEnemyCeresShot001Status(GgafCore::GgafActor* p);
    //�A�X�g���G�A
    static void resetEnemyAstraeaStatus(GgafCore::GgafActor* p);
    //�A�X�g���G�A���[�U�[
    static void resetEnemyAstraeaLaserChip001Status(GgafCore::GgafActor* p);
    //���F�X�^
    static void resetEnemyVestaStatus(GgafCore::GgafActor* p);
    //�C���X
    static void resetEnemyIrisStatus(GgafCore::GgafActor* p);
    //�ėp�V���b�g001
    static void resetShot001Status(GgafCore::GgafActor* p);
    //�ėp�V���b�g002
    static void resetShot002Status(GgafCore::GgafActor* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
