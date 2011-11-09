#ifndef GGAFDXBGM_H_
#define GGAFDXBGM_H_
namespace GgafDxCore {

// �{�v���O�����́A<BR>
// �u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html <BR>
// �T�C�g���R���e���c�� �uOgg Vorbis����ҁv http://marupeke296.com/OGG_main.html <BR>
// �̃T���v���v���O�����̃N���X���ꕔ�ύX���g�p���Ă��܂��B<BR>
// �����IKD���̐ɂ��݂Ȃ��m�����L�̐S�Ɋ��ӁB<BR>
//
//�Ώۉӏ�
// Dix �l�[���X�y�[�X�̃N���X
//                                            2009/01/13 Masatoshi Tsuge<BR>

/**
 * Bgm(Ogg �X�g���[��)�N���X .
 */
class GgafDxBgm : public GgafCore::GgafObject {
public:
    int _bpm;
    std::string _title;
    std::string _ogg_file_name;
    Dix::PCMPlayer* _pPcmPlayer;
    Dix::OggVorbisFile* _pOggResource;
    Dix::OggDecoder* _pOggDecoder;

    /**
     *
     * @param prm_bgm_key �v���p�e�B�t�@�C����key
     *                    _OGG, _BPM, _TITLE �̃v���t�B�b�N�X���w��
     * @return
     */
    GgafDxBgm(char* prm_bgm_key);

    /**
     *
     * @param prm_volume 0~100
     * @param prm_pan    -1.0 ~ 0 ~ 1.0
     * @param prm_is_looping
     */
    void play(int prm_volume, float prm_pan, bool prm_is_looping);
    void play(bool prm_is_looping) {
        play(GGAF_MAX_VOLUME, 0.0f, prm_is_looping);
    }
    void pause();
    void stop();
    void setVolume(int volume);
    void setPan(float pan);
    void clear();
    bool isActive();

    virtual ~GgafDxBgm();
};

}
#endif /*GGAFDXBGM_H_*/