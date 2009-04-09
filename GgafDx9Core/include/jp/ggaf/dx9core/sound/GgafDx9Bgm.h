#ifndef GGAFDX9BGM_H_
#define GGAFDX9BGM_H_
namespace GgafDx9Core {

// 本プログラムは、<BR>
// 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
// サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
// のサンプルプログラムを流用（一部変更）させていただいて、実装しています。<BR>
// 製作者IKD氏の惜しみない技術共有の心に感謝。<BR>
//
//                                            2009/01/13 Masatoshi Tsuge<BR>

/**
 * Bgm(Ogg ストリーム)クラス .
 */
class GgafDx9Bgm : public GgafCore::GgafObject {
public:
    char* _ogg_name;
    Dix::PCMPlayer* pPcmPlayer;
    Dix::sp< Dix::OggVorbisFile> spOggResource;
    Dix::sp< Dix::OggDecoder> spOggDecoder;

    GgafDx9Bgm(char* _ogg_name);

    //TODO:
    //virtual void behave();でフェードインフェードアウトを実装するぞ！

    //! 活動
    void play(bool isLoop);

    //! 一時停止
    void pause();

    //! 停止
    void stop();

    //! 音量を変える
    void setVolume(int volume);

    //! パンの位置を変える
    void setPan(int pan);
    //! 停止
    void clear();

    bool isActive();

    virtual ~GgafDx9Bgm();
};

}
#endif /*GGAFDX9BGM_H_*/
