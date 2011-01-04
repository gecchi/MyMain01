#ifndef STGUTIL_H_
#define STGUTIL_H_
namespace GgafDx9LibStg {

class StgUtil: public GgafDx9Core::GgafDx9Util {
public:

    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB* pAAB,
                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB);

    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliSphere* pSphere,
                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere);

    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB*    pAAB,
                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere);

    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB);

    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere*  pOppSphere);

    /**
     * Rz�ω��ɂ�� nWay�e������ .
     * @param prm_pFrom ���ˌ�
     * @param prm_pDispatcher_Shot ���˂���V���b�g�̃f�B�X�p�b�`���[
     * @param prm_pTarget �ڕW
     * @param prm_way Way��
     * @param prm_angClearance Way�̊Ԋu
     * @param prm_velo �������x
     * @param prm_acce �����x
     */
    static void shotWay001(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angClearance,
                           velo prm_velo, acce prm_acce);
    /**
     * Rz�ω��ɂ�� nWay�e�𕡐��Z�b�g�����Ɍ��� .
     * @param prm_pFrom        ���ˌ�
     * @param prm_pDispatcher_Shot ���˂���V���b�g�̃f�B�X�p�b�`���[
     * @param prm_pTarget      �ڕW
     * @param prm_way          Way��
     * @param prm_angClearance Way�̊Ԋu
     * @param prm_velo_top     ���eWAY�̏������x
     * @param prm_acce_top     ���eWAY�̉����x
     * @param prm_num          ����WAY�e�̃Z�b�g��
     * @param prm_attenuated   ����WAY�e�̏������x�����x�̌�����
     */
    static void shotWay001v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                             GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                             GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                             int prm_way, angle prm_angClearance,
                             velo prm_velo_top, acce prm_acce_top,
                             int prm_num, float prm_attenuated);


    /**
     * Ry �͖ڕW�ւ̌����{ANGLE90�ŁARz�ω��ɂ�� nWay���˒e��ł� .
     * @param prm_pFrom ���ˌ�
     * @param prm_pDispatcher_Shot ���˂���V���b�g�̃f�B�X�p�b�`���[
     * @param prm_pTarget �ڕW
     * @param prm_way ����Way��
     * @param prm_angBegin ���ˊJ�n�A���O��
     * @param prm_velo �������x
     * @param prm_acce �����x
     */
    static void shotWay002(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angBegin,
                           velo prm_velo, acce prm_acce);

    /**
     * shotWay002�e�𕡐��Z�b�g�����Ɍ��� .
     * @param prm_pFrom ���ˌ�
     * @param prm_pDispatcher_Shot ���˂���V���b�g�̃f�B�X�p�b�`���[
     * @param prm_pTarget �ڕW
     * @param prm_way ����Way��
     * @param prm_angBegin ���ˊJ�n�A���O��
     * @param prm_velo_top ���e����WAY�̏������x
     * @param prm_acce_top ���e����WAY�̉����x
     * @param prm_num      ������WAY�e�̃Z�b�g��
     * @param prm_attenuated ����WAY�e�̏������x�����x�̌�����
     */
    static void shotWay002v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                             GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                             GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                             int prm_way, angle prm_angBegin,
                             velo prm_velo_top, acce prm_acce_top,
                             int prm_num, float prm_attenuated);

};

}
#endif /*STGUTIL_H_*/
