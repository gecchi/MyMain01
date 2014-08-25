#ifndef GGAFCORE_GGAFLINEAROCTREEELEM_H_
#define GGAFCORE_GGAFLINEAROCTREEELEM_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafCore {

/**
 * 線形八分木配列用空間の要素クラス .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class GgafLinearOctreeElem : public GgafObject {

    friend class GgafLinearOctree;

private:
    /**
     * 自身が自ら空間から離脱、所属空間の情報もいきなり削除 .
     */
    void clear();
    /**
     * 自身が自ら空間の末尾にぶら下がり追加される .
     * 一度 belongTo() を実行し所属したならば、
     * GgafLinearOctree::clearElem();
     * にて、八分木全要素クリアされるまで、再度 belongTo() は出来ない。
     * @param prm_pSpace_target 所属する空間
     */
    void belongTo(GgafLinearOctreeSpace* prm_pSpace_target);

public:
    /** [r]所属ツリー */
    GgafLinearOctree* _pLinearOctree;
    /** [r]所属空間 */
    GgafLinearOctreeSpace* _pSpace_current;
    /** [r]次要素 */
    GgafLinearOctreeElem* _pNext;
    /** [r]前要素 */
    GgafLinearOctreeElem* _pPrev;
    /** [r]対象オブジェクト */
    GgafObject* _pObject;
    /** [r]対象オブジェクト種別 */
    uint32_t _kindbit;
    /** [r]登録リスト用リンク */
    GgafLinearOctreeElem* _pRegLinkNext;

    /**
     * コンストラクタ
     * @param prm_pObject 対象オブジェクト(キャラクタなど八分木で管理したい実際の値)
     * @param prm_kindbit その対象オブジェクの種別、種類分け不要な場合は、任意の数値でよい。
     * @return
     */
    GgafLinearOctreeElem(GgafObject* prm_pObject, uint32_t prm_kindbit);

    void dump();

    virtual ~GgafLinearOctreeElem();
};

}
#endif /*GGAFCORE_GGAFLINEAROCTREEELEM_H_*/

