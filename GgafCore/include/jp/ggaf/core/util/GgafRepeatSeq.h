#ifndef GGAFREPEATSEQ_H_
#define GGAFREPEATSEQ_H_
namespace GgafCore {

/**
 * ユーティリティクラス .
 * 汎用的な静的関数はできるだけここに記述。
 * @version 1.00
 * @since 2007/12/11
 * @author Masatoshi Tsuge
 */
class GgafRepeatSeq {
public:
    static int nowval[10];

    static int getNext(int id);
};

}
#endif /*GGAFREPEATSEQ_H_*/
