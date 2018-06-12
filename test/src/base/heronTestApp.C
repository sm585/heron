//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "heronTestApp.h"
#include "heronApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<heronTestApp>()
{
  InputParameters params = validParams<heronApp>();
  return params;
}

heronTestApp::heronTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  heronApp::registerObjectDepends(_factory);
  heronApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  heronApp::associateSyntaxDepends(_syntax, _action_factory);
  heronApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  heronApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    heronTestApp::registerObjects(_factory);
    heronTestApp::associateSyntax(_syntax, _action_factory);
    heronTestApp::registerExecFlags(_factory);
  }
}

heronTestApp::~heronTestApp() {}

void
heronTestApp::registerApps()
{
  registerApp(heronApp);
  registerApp(heronTestApp);
}

void
heronTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
heronTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
heronTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
heronTestApp__registerApps()
{
  heronTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
heronTestApp__registerObjects(Factory & factory)
{
  heronTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
heronTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  heronTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
heronTestApp__registerExecFlags(Factory & factory)
{
  heronTestApp::registerExecFlags(factory);
}
