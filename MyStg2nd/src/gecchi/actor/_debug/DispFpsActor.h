#ifndef DISPFPSACTOR_H_
#define DISPFPSACTOR_H_
namespace MyStg2nd {

class DispFpsActor : public GgafDx9Core::GgafDx9StringBoardActor {
    char _aBuf[80];
    std::string _strFps;
public:
    DispFpsActor(const char* prm_name, const char* prm_model);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize() override;

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processBehavior() override;

    virtual ~DispFpsActor();
};

}
#endif /*DISPFPSACTOR_H_*/

