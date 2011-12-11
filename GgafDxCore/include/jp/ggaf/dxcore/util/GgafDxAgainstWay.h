//#ifndef GGAFDXAGAINSTWAY_H_
//#define GGAFDXAGAINSTWAY_H_
//namespace GgafDxCore {
//
//
//class GgafDxAgainstWay {
//    enum MoveWay {
//        WAY_ZRIGHT_DOWN_BEHIND = 0,   //0    TN(-1,-1,-1)
//        WAY_DOWN_BEHIND,              //1    TN(-1,-1, 0)
//        WAY_ZLEFT_DOWN_BEHIND,        //2    TN(-1,-1, 1)
//        WAY_ZRIGHT_BEHIND,            //3    TN(-1, 0,-1)
//        WAY_BEHIND,                   //4    TN(-1, 0, 0)
//        WAY_ZLEFT_BEHIND,             //5    TN(-1, 0, 1)
//        WAY_ZRIGHT_UP_BEHIND,         //6    TN(-1, 1,-1)
//        WAY_UP_BEHIND,                //7    TN(-1, 1, 0)
//        WAY_ZLEFT_UP_BEHIND,          //8    TN(-1, 1, 1)
//        WAY_ZRIGHT_DOWN,              //9    TN( 0,-1,-1)
//        WAY_DOWN,                     //10   TN( 0,-1, 0)
//        WAY_ZLEFT_DOWN,               //11   TN( 0,-1, 1)
//        WAY_ZRIGHT,                   //12   TN( 0, 0,-1)
//        WAY_NONE,                     //13   TN( 0, 0, 0)
//        WAY_ZLEFT,                    //14   TN( 0, 0, 1)
//        WAY_ZRIGHT_UP,                //15   TN( 0, 1,-1)
//        WAY_UP,                       //16   TN( 0, 1, 0)
//        WAY_ZLEFT_UP,                 //17   TN( 0, 1, 1)
//        WAY_ZRIGHT_DOWN_FRONT,        //18   TN( 1,-1,-1)
//        WAY_DOWN_FRONT,               //19   TN( 1,-1, 0)
//        WAY_ZLEFT_DOWN_FRONT,         //20   TN( 1,-1, 1)
//        WAY_ZRIGHT_FRONT,             //21   TN( 1, 0,-1)
//        WAY_FRONT,                    //22   TN( 1, 0, 0)
//        WAY_ZLEFT_FRONT,              //23   TN( 1, 0, 1)
//        WAY_ZRIGHT_UP_FRONT,          //24   TN( 1, 1,-1)
//        WAY_UP_FRONT,                 //25   TN( 1, 1, 0)
//        WAY_ZLEFT_UP_FRONT            //26   TN( 1, 1, 1)
//    };
//public:
//
//
//    int _X, _Y, _Z;
//
//    int getIndex() {
//        //3êiêîÅ®10êiêîïœä∑
//        //_TRACE_("_way.X, _way.Y, _way.Z="<<_way.X<<","<<_way.Y<<","<< _way.Z);
//        return (3 * 3 * (sgn(_X) + 1)) + (3 * (sgn(_way.Y) + 1)) + (sgn(_way.Z) + 1);
//    }
//};
//}
//#endif /*GGAFDXAGAINSTWAY_H_*/
//
