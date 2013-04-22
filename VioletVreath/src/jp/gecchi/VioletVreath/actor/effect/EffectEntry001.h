#ifndef EFFECTENTRANCE001_H_
#define EFFECTENTRANCE001_H_
namespace VioletVreath {

/**
 * �o��G�t�F�N�g�A����1 .
 * @version 1.00
 * @since 2012/06/11
 * @author Masatoshi Tsuge
 */
class EffectEntry001 : public GgafLib::DefaultMeshSetActor {

public:
    frame scale_in_frames_;
    frame duration_frames_;
    frame scale_out_frames_;

    enum {
        PROG_INIT ,
        PROG_IN   ,
        PROG_STAY ,
        PROG_OUT  ,
    };

    EffectEntry001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    /**
     * �G�t�F�N�g�̔����A�����A���ł̎��Ԃ�ݒ�B.
     * </PRE>
     *       �Q�Q�Q�Q               �� �X�P�[���� 1.0
     *      /:      :�_
     *     / :      :  �_
     *    /  :      :    �_
     *   /   :      :      �_
     *  /    :      :        �_
     * /     :      :          �_   �� �X�P�[���� 0
     * ----------------------------------------------->���ԁi�t���[���j
     * ���@��|���A��|���� �B ����|
     *
     * </PRE>
     *
     * @param prm_scale_in_frames ��L�@�̃t���[����
     * @param prm_duration_frames ��L�A�̃t���[����
     * @param prm_scale_out_frames ��L�B�̃t���[����
     */
    void config(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames);

    virtual ~EffectEntry001();
};

}
#endif /*EFFECTENTRANCE001_H_*/

