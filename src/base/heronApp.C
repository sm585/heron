#include "heronApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<heronApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

heronApp::heronApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  heronApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  heronApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  heronApp::registerExecFlags(_factory);
}

heronApp::~heronApp() {}

void
heronApp::registerApps()
{
  registerApp(heronApp);
}

void
heronApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"heronApp"});
}

void
heronApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"heronApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
heronApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
heronApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
heronApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
heronApp__registerApps()
{
  heronApp::registerApps();
}

extern "C" void
heronApp__registerObjects(Factory & factory)
{
  heronApp::registerObjects(factory);
}

extern "C" void
heronApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  heronApp::associateSyntax(syntax, action_factory);
}

extern "C" void
heronApp__registerExecFlags(Factory & factory)
{
  heronApp::registerExecFlags(factory);
}
