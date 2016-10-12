#ifndef __RH_CF_NS_DEFS__
#define __RH_CF_NS_DEFS__

#ifdef  NO_NAMESPACE

#define REDHAWK_CPP_NAMESPACE    
#define REDHAWK_CPP_NAMESPACE_BEGIN  
#define REDHAWK_CPP_NAMESPACE_END  
#define REDHAWK_CPP_NAMESPACE_USE  
#define REDHAWK_CPP_NAMESPACE_QUALIFIER 

#else

#define REDHAWK_CPP_NAMESPACE   redhawk
#define REDHAWK_CPP_NAMESPACE_BEGIN  namespace REDHAWK_CPP_NAMESPACE {   
#define REDHAWK_CPP_NAMESPACE_END  };
#define REDHAWK_CPP_NAMESPACE_USE  using namespace REDHAWK_CPP_NAMESPACE;
#define REDHAWK_CPP_NAMESPACE_QUALIFIER REDHAWK_CPP_NAMESPACE::

namespace REDHAWK_CPP_NAMESPACE  {};

#endif

#endif // ifndef __REDHAWK_NS_DEFS__
