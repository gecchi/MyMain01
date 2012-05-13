#ifndef GRAPHBAR_H_
#define GRAPHBAR_H_
namespace VioletVreath {

/**
 * バー基底 .
 * @version 1.00
 * @since 2012/05/1
 * @author Masatoshi Tsuge
 */
class GraphBar : public GgafLib::DefaultBoardActor {

public:
    /** 内容量 */
    GgafLib::AmountGraph* pAmount_;

    float org_width_;

    /**
     *
     * @param prm_name
     * @param prm_pAmount config済みの AmountGraphオブジェクトの参照
     */
    GraphBar(const char* prm_name, const char* prm_model, GgafLib::AmountGraph* prm_pAmount);

    virtual ~GraphBar();
};

}
#endif /*GRAPHBAR_H_*/

