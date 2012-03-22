#ifndef GGAFDXBGM_H_
#define GGAFDXBGM_H_
namespace GgafDxCore {

/**
 * Bgm(Ogg�t�H�[�}�b�g)�N���X .
 */
class GgafDxBgm : public GgafCore::GgafObject {
public:
    /** [r]BGM �� BMP */
    int _bpm;
    /** [r]BGM �� �^�C�g�� */
    std::string _title;
    /** [r]BGM �� ogg�t�@�C���� */
    std::string _ogg_file_name;
    /** [r]PCMPlayer */
    IkdLib::PCMPlayer* _pPcmPlayer;
    IkdLib::OggVorbisFile* _pOggResource;
    IkdLib::OggDecoder* _pOggDecoder;

    /**
     * �R���X�g���N�^ .
     * �v���p�e�B�t�@�C�����玟�̃L�[�̒l���擾���܂��B
     * �@ prm_bgm_key+"_OGG"      �E�E�E �l�FBGM�ƂȂ� ogg�t�@�C����
     * �A prm_bgm_key+"_BPM"      �E�E�E �l�F���ݖ��g�p
     * �B prm_bgm_key+"_TITLE"    �E�E�E �l�F���ݖ��g�p
     * ���ɁA�@�̂̒l����BGM�ƂȂ� ogg�t�@�C���� �v���p�e�B�t�@�C����
     * DIR_OGG �̐ݒ�l�z������T���ăI�[�v�����A�Đ��������s���܂��B
     * @param prm_bgm_key �v���p�e�B�t�@�C����key
     *                    _OGG, _BPM, _TITLE �̃v���t�B�b�N�X���w��
     * @return
     */
    GgafDxBgm(char* prm_bgm_key);

    /**
     * BGM�Đ� .
     * @param prm_volume 0�`100
     * @param prm_pan �� -1.0 �` 0 �` 1.0 �E
     * @param prm_is_looping true:���[�v�Đ�
     */
    void play(int prm_volume, float prm_pan, bool prm_is_looping);
    /**
     * BGM�Đ� .
     * @param prm_is_looping true:���[�v�Đ�
     */
    void play(bool prm_is_looping) {
        play(GGAF_MAX_VOLUME, 0.0f, prm_is_looping);
    }
    void pause();
    void unpause();
    void stop();
    /**
     * BGM�̃{�����[���ݒ� .
     * @param volume 0�`100
     */
    void setVolume(int volume);
    /**
     * BGM�̃p���ݒ� .
     * @param pan �� -1.0 �` 0 �` 1.0 �E
     */
    void setPan(float pan);
    void clear();
    bool isActive();

    virtual ~GgafDxBgm();
};

}
#endif /*GGAFDXBGM_H_*/
