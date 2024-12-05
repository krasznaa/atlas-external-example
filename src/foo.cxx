// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "hls/foo.h"

// System include(s).
#include <iostream>

namespace hls
{

   void Foo::bar()
   {
      std::cout << "Hello, World!" << std::endl;
      return;
   }

}
