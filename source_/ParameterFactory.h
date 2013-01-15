/*
 *  ParameterFactory.h
 *  BeatCounter
 *
 *  Created by Nik Reiman on 2010-04-17.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __ParameterFactory_h__
#define __ParameterFactory_h__

#ifndef __PluginParameterSet_h__
#include "PluginParameterSet.h"
#endif

namespace teragon {
  class ParameterFactory {
  public:
    ParameterFactory() {}
    ~ParameterFactory() {}
    
    pluginParameters::PluginParameterSet* createPluginParameterSet();
  };
}

#endif
