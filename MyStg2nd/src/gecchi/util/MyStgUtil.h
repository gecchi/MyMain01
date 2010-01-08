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

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�V�[��Creater.xls�v����s���Ă������������B
    // gen01 start
	//�P���X
	static void resetEnemyCeresStatus(GgafCore::GgafActor* p);
	//�A�X�g���G�A
	static void resetEnemyAstraeaStatus(GgafCore::GgafActor* p);
	//���F�X�^
	static void resetEnemyVestaStatus(GgafCore::GgafActor* p);
	//�C���X
	static void resetEnemyIrisStatus(GgafCore::GgafActor* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
