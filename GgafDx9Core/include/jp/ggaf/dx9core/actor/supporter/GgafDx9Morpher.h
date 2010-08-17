#ifndef GGAFDX9MORPHER_H_
#define GGAFDX9MORPHER_H_
namespace GgafDx9Core {


/**
 * ���[�t�B���O�x���N���X .
 * GgafDx9MorphMeshActor �̃����o��<BR>
 * �d�� _weight[] <BR>
 * ���ȒP�ɑ��삷�邽�߂ɐ݌v�B<BR>
 * �� _weight[] �́A[0]�͖��g�p�A[1]�`[n]�����[�t�^�[�Q�b�g1�`n�̏d�� <BR>
 * @version 1.00
 * @since 2009/05/11
 * @author Masatoshi Tsuge
 */
class GgafDx9Morpher : public GgafCore::GgafObject {

public:
    /** �ΏۃA�N�^�[ */
    GgafDx9MorphMeshActor* _pActor;
    /** �e���[�t�^�[�Q�b�g�̏d��(0.0 �` 1.0) */
    float _weight[MAX_MORPH_TARGET+1];
    /** �e���[�t�^�[�Q�b�g�֐ݒ肳�ꂽ�ڕW�̏d��(0.0 �` 1.0) */
    float _target_weight[MAX_MORPH_TARGET+1];
    /** �e���[�t�^�[�Q�b�g�֏d�ݏ��(0.0 �` 1.0) */
    float _top_weight[MAX_MORPH_TARGET+1];
    /** �e���[�t�^�[�Q�b�g�֏d�݉���(0.0 �` 1.0) */
    float _bottom_weight[MAX_MORPH_TARGET+1];
    /** �e���[�t�^�[�Q�b�g�ւ̖��t���[���d�ݑ��x */
    float _velo_weight[MAX_MORPH_TARGET+1];
    /** �e���[�t�^�[�Q�b�g�ւ̖��t���[���d�݉����x */
    float _acce_weight[MAX_MORPH_TARGET+1];

    /** ���[�v�d�݂̂P���[�v�t���[���� */
    frame _loop_spend_frame[MAX_MORPH_TARGET+1];
    /** ���[�v�d�݂̊J�n���΃t���[�� */
    frame _loop_begin_frame[MAX_MORPH_TARGET+1];
    /** �O�p�g���[�v�d�݂̃A�^�b�N�܂ł̃t���[���� */
    frame _loop_attack_frame[MAX_MORPH_TARGET+1];
    /** �O�p�g���[�v�d�݂̋x���t���[���� */
    frame _loop_rest_frame[MAX_MORPH_TARGET+1];
    /** �P���[�v�������ƍl�����ꍇ�̕Г����[�v���J�E���^(�P���[�v�łQ������) */
    int _halfloop_cnt[MAX_MORPH_TARGET+1];
    /** ��~�\��̕Г����[�v�� */
    int _stop_halfloop_num[MAX_MORPH_TARGET+1];
    /** ���[�v�̐U�镑����� */
    GgafDx9MorphMethod _method[MAX_MORPH_TARGET+1];

    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    GgafDx9Morpher(GgafDx9MorphMeshActor* prm_pActor);

    /**
     * ���[�t�^�[�Q�b�g�̏d�݂̏���Ɖ�����ݒ肵�d�݂̒l�𐧌����� .
     * @param prm_target_mesh ���[�t�^�[�Q�b�g���b�V��NO
     * @param prm_weight1 �d�݂P(��� or ����)
     * @param prm_weight2 �d�݂Q(���� or ���)
     */
    void forceWeightRange(int prm_target_mesh, float prm_weight1, float prm_weight2) {
        if (prm_weight1 < prm_weight2) {
            _top_weight[prm_target_mesh] = prm_weight2;
            _bottom_weight[prm_target_mesh] = prm_weight1;
        } else {
            _top_weight[prm_target_mesh] = prm_weight1;
            _bottom_weight[prm_target_mesh] = prm_weight2;
        }
    }

    /**
     * ���[�t�^�[�Q�b�g�̏d�݂𒼐ڎw�� .
     * @param prm_target_mesh ���[�t�^�[�Q�b�g���b�V��NO
     * @param prm_weight �d��
     */
    void setWeight(int prm_target_mesh, float prm_weight) {
        if (_top_weight[prm_target_mesh] < prm_weight) {
            _weight[prm_target_mesh] = _top_weight[prm_target_mesh];
        } else if (_bottom_weight[prm_target_mesh] > prm_weight) {
            _weight[prm_target_mesh] = _bottom_weight[prm_target_mesh];
        } else {
            _weight[prm_target_mesh] = prm_weight;
        }
    }

    /**
     * ���[�t�^�[�Q�b�g�̏d�݂������l�ɐݒ� .
     * @param prm_target_mesh ���[�t�^�[�Q�b�g���b�V��NO
     */
    void setWeightToBottom(int prm_target_mesh) {
        _weight[prm_target_mesh] = _bottom_weight[prm_target_mesh];
    }

    /**
     * ���[�t�^�[�Q�b�g�̏d�݂�����l�ɐݒ� .
     * @param prm_target_mesh ���[�t�^�[�Q�b�g���b�V��NO
     */
    void setWeightToTop(int prm_target_mesh) {
        _weight[prm_target_mesh] = _top_weight[prm_target_mesh];
    }

    /**
     * ���[�t�B���O���~����
     * @param prm_target_mesh ���[�t�B���O���̃��[�t�^�[�Q�b�g���b�V��NO
     */
    void stopImmediately(int prm_target_mesh);

    /**
     * ���[�t�^�[�Q�b�g�ֈ�葬�x�Ń��[�t�B���O����i�t���[�����w��j .
     * @param prm_target_mesh ���[�t�^�[�Q�b�g���b�V��NO
     * @param prm_target_weight �^�[�Q�b�g���b�V���̖ڕW�d��(0.0�`1.0)
     * @param prm_spend_frame ��₷�t���[����
     */
    void intoTargetLinerUntil(int prm_target_mesh, float prm_target_weight, frame prm_spend_frame);

    /**
     * ���[�t�^�[�Q�b�g�ֈ�葬�x�Ń��[�t�B���O����i�d�ݍ����w��j .
     * @param prm_target_mesh ���[�t�^�[�Q�b�g���b�V��NO
     * @param prm_target_weight �^�[�Q�b�g���b�V���̖ڕW�d��(0.0�`1.0)
     * @param prm_velo_weight ���t���[�����Z����d�ݍ���(>0.0)�B���̏d�݂��w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void intoTargetLinerStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight);

    /**
     * ���[�t�^�[�Q�b�g�։����w��Ń��[�t�B���O����i�d�ݑ��x�A�d�݉����x���w��j .
     * �d�݉����x��0�Ɏw�肷��� intoTargetLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * intoTargetLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_target_mesh ���[�t�^�[�Q�b�g���b�V��NO
     * @param prm_target_weight �^�[�Q�b�g���b�V���̖ڕW�d��(0.0�`1.0)
     * @param prm_velo_weight �����d�ݑ��x
     * @param prm_acce_weight �d�݉����x
     */
    void intoTargetAcceStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight, float prm_acce_weight);

    /**
     * ���[�t�^�[�Q�b�g�ֈ�葬�x�Ń��[�t�B���O���A��葬�x�Ō��ɖ߂�B��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_target_mesh ���[�t�^�[�Q�b�g���b�V��NO
     * @param prm_loop_spend_frame �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_loop_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(int prm_target_mesh, frame prm_loop_spend_frame, float prm_loop_num = -1);

    /**
     * �O�p�g�̔g�`���d�݂Ƃ��ă��[�t�B���O����B .
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
     * @param prm_target_mesh ���[�t�^�[�Q�b�g���b�V��NO
     * @param prm_loop_spend_frame ��}�Ň@�̃t���[����
     * @param prm_attack_frame ��}�ŇA�̃t���[����
     * @param prm_rest_frame ��}�ŇB�̃t���[����
     * @param prm_loop_num ���[�v��(-1�Ŗ���)
     */
    void loopTriangleWave(int prm_target_mesh,
                          frame prm_loop_spend_frame,
                          frame prm_attack_frame,
                          frame prm_rest_frame,
                          float prm_loop_num = -1);

    /**
     * ���t���[���̐U�镑�����\�b�h�B<BR>
     * �{�N���X�̃��[�t�B���O�@�\�𗘗p����ꍇ�́A<BR>
     * ���̃��\�b�h�𖈃t���[�����s���邱�Ƃ��K�v�ł��B <BR>
     */
    virtual void behave();

    virtual ~GgafDx9Morpher();
};

}
#endif /*GGAFDX9MORPHER_H_*/

