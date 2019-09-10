#ifndef _CUBEACTION_H_
#define _CUBEACTION_H_

#include "CubeModel.h"

namespace ai {
    namespace rectangle {
       
        class Action : public ai::Search::Action {
        public:

            Action( const Move& move );
            virtual ~Action( );
            virtual void Display( ) const;
            
            const Move& getMove( ) const;
      
        protected:
          Move mMove;
          
        private:
      
        };

    }
}

std::ostream& operator<<( std::ostream& os, const ai::rubiks::Action& action );

#endif
