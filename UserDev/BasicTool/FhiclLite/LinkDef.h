//
// cint script to generate libraries
// Declaire namespace & classes you defined
// #pragma statement: order matters! Google it ;)
//

#if defined(__ROOTCINT__) || defined(__ROOTCLING__)
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class fcl::PSet+;
#pragma link C++ class fcl::PSetManager+;
#pragma link C++ class fcl::FhiclLiteException+;

#pragma link C++ class CfgFileReader+;
//ADD_NEW_CLASS ... do not change this line
#endif


