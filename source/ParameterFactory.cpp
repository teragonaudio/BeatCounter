/*
 *  ParameterFactor.cpp
 *  BeatCounter
 *
 *  Created by Nik Reiman on 2010-04-17.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __ParameterFactory_h__
#include "ParameterFactory.h"
#endif

#ifndef __MapParameterSet_h__
#include "MapParameterSet.h"
#endif

#ifndef __BooleanParameter_h__
#include "BooleanParameter.h"
#endif

#ifndef __FloatingPointParameter_h__
#include "FloatingPointParameter.h"
#endif

using namespace teragon::pluginParameters;

namespace teragon {
  pluginParameters::PluginParameterSet* ParameterFactory::createPluginParameterSet() {
    MapParameterSet* result = new MapParameterSet();
    
    result->addParameter(new BooleanParameter("Reset"));
    result->addParameter(new FloatingPointParameter("Tolerance", 0.0, 100.0));
    result->addParameter(new FloatingPointParameter("Period", 5.0, 20.0));
    result->addParameter(new BooleanParameter("Autofilter On"));
    result->addParameter(new FloatingPointParameter("Autofilter Freq.", 50.0, 500.0));
    result->addParameter(new BooleanParameter("Link to Host Tempo"));
    
    return result;
  }
}
