#ifndef GGAFDXBGM_H_
#define GGAFDXBGM_H_
namespace GgafDxCore {

// 本プログラムは、<BR>
// 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
// サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
// のサンプルプログラムのクラスを一部変更し使用しています。<BR>
// 製作者IKD氏の惜しみない知識共有の心に感謝。<BR>
//
//対象箇所
// Dix ネームスペースのクラス
//                                            2009/01/13 Masatoshi Tsuge<BR>

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
    bool isActiveInTheWorld();

    virtual ~GgafDxBgm();
};

}
#endif /*GGAFDXBGM_H_*/
