#ifndef GGAFDX9BGM_H_
#define GGAFDX9BGM_H_
namespace GgafDx9Core {

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
class GgafDx9Bgm : public GgafCore::GgafObject {
public:
    int _bpm;
    std::string _title;
    std::string _ogg_file_name;
    Dix::PCMPlayer* pPcmPlayer;
    Dix::OggVorbisFile* pOggResource;
    Dix::OggDecoder* pOggDecoder;

//    Dix::sp< Dix::OggVorbisFile> pOggResource;
//    Dix::sp< Dix::OggDecoder> pOggDecoder;
    /**
     *
     * @param prm_bgm_key �v���p�e�B�t�@�C����key
     *                    _OGG, _BPM, _TITLE �̃v���t�B�b�N�X���w��
     * @return
     */
    GgafDx9Bgm(char* prm_bgm_key);

    void play(int prm_volume, int prm_pan, bool prm_isLoop);
    void play(bool prm_isLoop) {
        play(DSBVOLUME_MAX, DSBPAN_CENTER, prm_isLoop);
    }
    void pause();
    void stop();
    void setVolume(int volume);
    void setPan(int pan);
    void clear();
    bool isActiveActor();

    virtual ~GgafDx9Bgm();
};

}
#endif /*GGAFDX9BGM_H_*/
