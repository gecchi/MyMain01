#ifndef GGAFDX9BGM_H_
#define GGAFDX9BGM_H_
namespace GgafDx9Core {

// 本プログラムは、<BR>
// 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
// サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
// のサンプルプログラムを流用（一部変更）させていただいて、実装しています。<BR>
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
