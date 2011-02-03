#ifndef GGAFDX9BGM_H_
#define GGAFDX9BGM_H_
namespace GgafDx9Core {

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
     * @param prm_bgm_key プロパティファイルのkey
     *                    _OGG, _BPM, _TITLE のプレフィックスを指定
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
