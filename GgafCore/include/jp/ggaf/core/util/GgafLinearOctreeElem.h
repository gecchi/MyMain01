#ifndef GGAFLINEAROCTREEELEM_H_
#define GGAFLINEAROCTREEELEM_H_
namespace GgafCore {


/**
 * 線形八分木配列用空間の要素クラス .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class GgafLinearOctreeElem {
public:
    /** 所属ツリー */
    GgafLinearOctree* _pLinearOctree;
    /** 所属空間 */
    GgafLinearOctreeSpace* _pSpace_Current;
    /** 次要素 */
    GgafLinearOctreeElem* _pNext;
    /** 前要素 */
    GgafLinearOctreeElem* _pPrev;
    /** 対象オブジェクト */
    GgafObject* _pObject;
    /** 対象オブジェクト種別 */
    DWORD _kindbit;
    /** 登録リスト用リンク */
    GgafLinearOctreeElem* _pRegLinkNext;

    /**
     * コンストラクタ
     * @param prm_pObject 対象オブジェクト(キャラクタなど八分木で管理したい実際の値)
     * @param prm_kindbit その対象オブジェクの種別、種類分け不要な場合は、任意の数値でよい。
     * @return
     */
    GgafLinearOctreeElem(GgafObject* prm_pObject, DWORD prm_kindbit);

    /**
     * 自身が自ら離脱
     */
    void extract();

    /**
     * 自身が自ら空間の末尾に追加
     */
    void addElem(GgafLinearOctreeSpace* prm_pSpace_target);

//    /**
//     * 自身が自ら他空間へ移動
//     * extract()してaddElem()します.
//     * @param prm_pSpace_target
//     */
//void moveToSpace(GgafLinearOctreeSpace* prm_pSpace_target);
    void dump();

    virtual ~GgafLinearOctreeElem();
};

}
#endif /*GGAFLINEAROCTREEELEM_H_*/

