#ifndef GGAFDXBGM_H_
#define GGAFDXBGM_H_
namespace GgafDxCore {

/**
 * Bgm(Ogg ストリーム)クラス .
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
     * @param prm_bgm_key プロパティファイルのkey
     *                    _OGG, _BPM, _TITLE のプレフィックスを指定
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
