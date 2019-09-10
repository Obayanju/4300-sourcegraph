#include "CubeAppData.h"
#include "CubeAppCommand.h"
#include "CubeSearch.h"
#include <iostream>

namespace ai {
  namespace rubiks {
    static int search_aux( AppData& data ) {
      data.os << "You must implement this function.  You may consider borrowing large chunks of code from the RectangleSolver program." << std::endl;
      return EXIT_USAGE;
    }

    int search( AppData& data ) {
      return search_aux( data );
    }
  }
}
