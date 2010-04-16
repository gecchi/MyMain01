#ifndef GAMEACTOR_H_
#define GAMEACTOR_H_
namespace MyStg2nd {

/**
 * アクターの具象クラス.
 */
template<class P>
class GameActor : public P {


public:

    int _point;
    int _max_hp;

    GameActor(const char* prm_name, const char* prm_model): P(prm_name, prm_model) {}

    virtual ~GameActor(){}
};

}
#endif /*GAMEACTOR_H_*/
