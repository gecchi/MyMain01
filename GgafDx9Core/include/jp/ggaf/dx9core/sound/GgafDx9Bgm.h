#ifndef GGAFDX9BGM_H_
#define GGAFDX9BGM_H_
namespace GgafDx9Core {

// �{�v���O�����́A<BR>
// �u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html <BR>
// �T�C�g���R���e���c�� �uOgg Vorbis����ҁv http://marupeke296.com/OGG_main.html <BR>
// �̃T���v���v���O�����𗬗p�i�ꕔ�ύX�j�����Ă��������āA�������Ă��܂��B<BR>
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
    char* _ogg_name;
    Dix::PCMPlayer* pPcmPlayer;
    Dix::OggVorbisFile* spOggResource;
    Dix::OggDecoder* spOggDecoder;

//    Dix::sp< Dix::OggVorbisFile> spOggResource;
//    Dix::sp< Dix::OggDecoder> spOggDecoder;

    GgafDx9Bgm(char* _ogg_name);

    void play(int prm_volume, int prm_pan, bool prm_isLoop);
    void play(bool prm_isLoop) {
        play(DSBVOLUME_MAX, DSBPAN_CENTER, prm_isLoop);
    }
    void pause();
    void stop();
    void setVolume(int volume);
    void setPan(int pan);
    void clear();
    bool isActive();

    virtual ~GgafDx9Bgm();
};

}
#endif /*GGAFDX9BGM_H_*/
