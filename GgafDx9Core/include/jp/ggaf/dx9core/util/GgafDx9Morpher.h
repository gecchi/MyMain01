#ifndef GGAFDX9MORPHER_H_
#define GGAFDX9MORPHER_H_
namespace GgafDx9Core {

enum GgafDx9MorphMethod {
    NOMORPH,
    TARGET_LINER,
    LOOP_LINER,
    LOOP_TRIANGLEWAVE,
    TARGET_SIN,
    LOOP_SIN,
    TARGET_PARABOLA,
    LOOP_PARABOLA,
    TARGET_PARABOLA_REV,
    LOOP_PARABOLA_REV
};

class GgafDx9Morpher : public GgafCore::GgafObject {

public:
    /** �ΏۃA�N�^�[ */
    GgafDx9MorphMeshActor* _pActor;

    float _inc_weight[10];
    float _target_weight[10];
    float _top_weight[10];
    float _bottom_weight[10];
    DWORD _loop_attack_frame[10];
    DWORD _loop_rest_frame[10];
    DWORD _loop_spend_frame[10];
    DWORD _loop_begin_frame[10];
    int _halfloop_cnt[10];
    int _stop_halfloop_num[10];

    GgafDx9MorphMethod _method[10];

    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    GgafDx9Morpher(GgafDx9MorphMeshActor* prm_pActor);

    void stopImmediately(int prm_target_mesh);

    /**
     * �^�[�Q�b�g�ֈ�葬�x�Ń��[�t����i�t���[�����w��j .
     * @param prm_target_mesh �^�[�Q�b�g���b�V��NO
     * @param prm_target_weight �^�[�Q�b�g���b�V���̖ڕW�d��
     * @param prm_spend_frame ��₷�t���[����
     */
    void intoTargetLinerUntil(int prm_target_mesh, float prm_target_weight, DWORD prm_spend_frame);

    /**
     * �^�[�Q�b�g�ֈ�葬�x�Ń��[�t����i�d�ݍ����w��j .
     * @param prm_target_mesh �^�[�Q�b�g���b�V��NO
     * @param prm_target_weight �^�[�Q�b�g���b�V���̖ڕW�d��
     * @param prm_inc_weight ���t���[�����Z����d�ݍ���(>0.0)�B���̏d�݂��w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void intoTargetLinerStep(int prm_target_mesh, float prm_target_weight, float prm_inc_weight);

    /**
     * �^�[�Q�b�g�ֈ�葬�x�Ń��[�t���A��葬�x�Ō��ɖ߂�B��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_target_mesh �^�[�Q�b�g���b�V��NO
     * @param prm_loop_spend_frame �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_loop_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(int prm_target_mesh, DWORD prm_loop_spend_frame, float prm_loop_num = -1);

    /**
     * �O�p�g�̔g�`�Ń��[�t����B.
     * <PRE>
     * �C  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
     *            /�_                     /�_
     *           /   �_                  /   �_
     *          /      �_               /      �_
     *         /         �_            /         �_
     *        /            �_         /            �_
     * �D  �Q/               �_�Q�Q�Q/               �_�Q
     *
     *       ���A��            ���B��
     *       ���������� �@ ����������
     * </PRE>
     * ���K�v�Ȑݒ�l��<BR>
     * �@ �P���[�v�̃t���[����<BR>
     * �A �A�^�b�N�܂ł̃t���[����<BR>
     * �B �x�e�t���[����<BR>
     * �C �d�ݏ��(_top_weight[prm_target_mesh] ���ێ�)<BR>
     * �D �d�݉���(_bottom_weight[prm_target_mesh] ���ێ�)<BR>
     * <BR>
     * @param prm_target_mesh �^�[�Q�b�g���b�V��NO
     * @param prm_loop_spend_frame ��}�Ň@�̃t���[����
     * @param prm_attack_frame ��}�ŇA�̃t���[����
     * @param prm_rest_frame ��}�ŇB�̃t���[����
     * @param prm_loop_num ���[�v��(-1�Ŗ���)
     */
    void loopTriangleWave(int prm_target_mesh,
                          DWORD prm_loop_spend_frame,
                          DWORD prm_attack_frame,
                          DWORD prm_rest_frame,
                          float prm_loop_num = -1);

    /**
     * ���t���[����Actor�̐U�镑���B<BR>
     */
    virtual void behave();

    virtual ~GgafDx9Morpher();
};

}
#endif /*GGAFDX9MORPHER_H_*/

