#ifndef DEFAULTWORLD_H_
#define DEFAULTWORLD_H_
namespace GgafDx9LibStg {

/**
 * 「世界」クラスインターフェイス.
 * GgafDx9Core::GgafDx9World を継承しただけのインターフェースです。<BR>
 * Ggafライブラリを利用する場合、本クラスを継承し実装した世界クラスが必要です。<BR>
 */
class DefaultWorld : public GgafDx9Core::GgafDx9World {

public:
    DefaultWorld(const char* prm_name);

    virtual ~DefaultWorld();
};

}
#endif /*DEFAULTWORLD_H_*/
