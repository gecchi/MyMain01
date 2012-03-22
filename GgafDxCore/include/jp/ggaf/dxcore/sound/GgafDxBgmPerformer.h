#ifndef GGAFDXBGMPERFORMER_H_
#define GGAFDXBGMPERFORMER_H_
namespace GgafDxCore {

/**
 * BGM���t�x���N���X .
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxBgmPerformer : public GgafCore::GgafObject {

public:
    static int _active_bgm_bpm;
    int _bgm_num;

    double* _pa_volume;
    /** Bgm�����ڑ� */
    GgafDxBgmConnection** _papBgmCon;

    GgafDxBgmPerformer();
    virtual void useBgm(int prm_bgm_num);
    /**
     *
     * @param prm_id �ԍ�ID
     * @param prm_bgm_name �v���p�e�B�t�@�C����_OGG, _BPM, _TITLE �̃v���t�B�b�N�X�ƂȂ��Ă���key������
     *
     */
    virtual void set(int prm_id, const char* prm_bgm_name);
    virtual void setVolume(int prm_id, int prm_volume);

    virtual void play(int prm_id, int prm_volume, bool prm_is_loop);
    virtual void play(int prm_id, int prm_volume) {
        play(prm_id, prm_volume, true);
    }
    virtual void play(int prm_id) {
        play(prm_id, GGAF_MAX_VOLUME);
    }
    virtual void stop(int prm_id);

    virtual void pause(int prm_id);
    virtual void unpause(int prm_id);

    virtual void pause();
    virtual void unpause();

    virtual ~GgafDxBgmPerformer();
};

}
#endif /*GGAFDXBGMPERFORMER_H_*/
