#ifndef GGAFDX9GEOMETRYMORPHER_H_
#define GGAFDX9GEOMETRYMORPHER_H_
namespace GgafDx9Core {

enum GgafDx9MorphMethod {
    NOMORPH,
    TARGET_LINER,
    LOOP_LINER,
    LOOP_TRIANGLEWAVE,
    TARGET_SIN,
    LOOP_SIN,
    TARGET_ACCELERATION,
    LOOP_PARABOLA,
    TARGET_PARABOLA_REV,
    LOOP_PARABOLA_REV
};


/**
 * ���[�t�x���N���X .
 * GgafDx9MorphMeshActor �̃����o��<BR>
 * _weight[] <BR>
 * ���ȒP�ɑ��삷�邽�߂ɐ݌v�B<BR>
 * @version 1.00
 * @since 2009/05/11
 * @author Masatoshi Tsuge
 */
class GgafDx9GeometryMorpher : public GgafCore::GgafObject {

public:
    /** �ΏۃA�N�^�[ */
    GgafDx9MorphMeshActor* _pActor;

    float _target_weight[MAX_MORPH_TARGET+1];
    float _top_weight[MAX_MORPH_TARGET+1];
    float _bottom_weight[MAX_MORPH_TARGET+1];
    float _velo_weight[MAX_MORPH_TARGET+1];
    float _acce_weight[MAX_MORPH_TARGET+1];
    DWORD _loop_attack_frame[MAX_MORPH_TARGET+1];
    DWORD _loop_rest_frame[MAX_MORPH_TARGET+1];
    DWORD _loop_spend_frame[MAX_MORPH_TARGET+1];
    DWORD _loop_begin_frame[MAX_MORPH_TARGET+1];
    int _halfloop_cnt[MAX_MORPH_TARGET+1];
    int _stop_halfloop_num[MAX_MORPH_TARGET+1];

    GgafDx9MorphMethod _method[MAX_MORPH_TARGET+1];

    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    GgafDx9GeometryMorpher(GgafDx9MorphMeshActor* prm_pActor);

    void setWeightRange(int prm_target_mesh, float prm_weight1, float prm_weight2) {
        if (prm_weight1 < prm_weight2) {
            _top_weight[prm_target_mesh] = prm_weight2;
            _bottom_weight[prm_target_mesh] = prm_weight1;
        } else {
            _top_weight[prm_target_mesh] = prm_weight1;
            _bottom_weight[prm_target_mesh] = prm_weight2;
        }
    }

    void resetWeight(int prm_target_mesh) {
        _pActor->_weight[prm_target_mesh] = _bottom_weight[prm_target_mesh];
    }
    void resetTopWeight(int prm_target_mesh) {
        _pActor->_weight[prm_target_mesh] = _top_weight[prm_target_mesh];
    }


    void stopImmediately(int prm_target_mesh);

    /**
     * �^�[�Q�b�g�ֈ�葬�x�Ń��[�t����i�t���[�����w��j .
     * @param prm_target_mesh �^�[�Q�b�g���b�V��NO
     * @param prm_target_weight �^�[�Q�b�g���b�V���̖ڕW�d��(0.0�`1.0)
     * @param prm_spend_frame ��₷�t���[����
     */
    void intoTargetLinerUntil(int prm_target_mesh, float prm_target_weight, DWORD prm_spend_frame);

    /**
     * �^�[�Q�b�g�ֈ�葬�x�Ń��[�t����i�d�ݍ����w��j .
     * @param prm_target_mesh �^�[�Q�b�g���b�V��NO
     * @param prm_target_weight �^�[�Q�b�g���b�V���̖ڕW�d��(0.0�`1.0)
     * @param prm_velo_weight ���t���[�����Z����d�ݍ���(>0.0)�B���̏d�݂��w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void intoTargetLinerStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight);

    /**
     * �^�[�Q�b�g�։����w��Ń��[�t����i�d�ݑ��x�A�d�݉����x���w��j .
     * �d�݉����x��0�Ɏw�肷��� intoTargetLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * intoTargetLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_target_mesh �^�[�Q�b�g���b�V��NO
     * @param prm_target_weight �^�[�Q�b�g���b�V���̖ڕW�d��(0.0�`1.0)
     * @param prm_velo_weight �����d�ݑ��x
     * @param prm_acce_weight �d�݉����x
     */
    void intoTargetAccelerationStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight, float prm_acce_weight);

    /**
     * �^�[�Q�b�g�ֈ�葬�x�Ń��[�t���A��葬�x�Ō��ɖ߂�B��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_target_mesh �^�[�Q�b�g���b�V��NO
     * @param prm_loop_spend_frame �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_loop_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(int prm_target_mesh, DWORD prm_loop_spend_frame, float prm_loop_num = -1);

    /**
     * �O�p�g�̔g�`���d�݂Ƃ��ă��[�t����B.
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

    virtual ~GgafDx9GeometryMorpher();
};

}
#endif /*GGAFDX9GEOMETRYMORPHER_H_*/

