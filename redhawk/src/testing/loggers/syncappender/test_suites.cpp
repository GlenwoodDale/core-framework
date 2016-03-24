#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<log4cxx/logger.h>
#include<log4cxx/propertyconfigurator.h>
#include <log4cxx/logstring.h>
#include <log4cxx/helpers/loglog.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/rollingfileappender.h>
#include <log4cxx/logmanager.h>
#include <boost/filesystem.hpp>
#include "test_suites.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( test_suite_one );
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( test_suite_one, "test_one" );
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( test_suite_two, "test_two" );


void 
test_suite_one::setUp()
{

  // Set up a simple configuration that logs on the console.
  log4cxx::PropertyConfigurator::configure("log4j.stdout" );

  log4cxx::helpers::LogLog::setInternalDebugging(true);

  logger = log4cxx::Logger::getLogger("LOG-MultiProcRollingFileAppender");

  LOG4CXX_INFO(logger, "Setup cache directory for saved configuration files");
  boost::filesystem::path dir("./logs");
  boost::filesystem::create_directory(dir);
}

void 
test_suite_one::tearDown()
{
  // Set up a simple configuration that logs on the console.
  log4cxx::PropertyConfigurator::configure("log4j.stdout" );

  boost::filesystem::path dir("./logs");
  boost::filesystem::remove_all(dir);

}

void 
test_suite_one::test_one()
{
  LOG4CXX_INFO(logger, "RH_SyncRollingAppender - BEGIN ");

  // Set up a simple configuration that logs on the console.
  log4cxx::PropertyConfigurator::configure("log4j.appender" );
  int cnt=10;
  int pid = getpid();
  
  while ( cnt-- ) {
   LOG4CXX_INFO(logger, "test_log4j_props_appender  MSG 1 - root logger (" << pid << ")" );
   LOG4CXX_INFO(logger, "test_log4j_props_appender  MSG 2 - root logger (" << pid << ")" );
   LOG4CXX_INFO(logger, "test_log4j_props_appender  MSG 3 - root logger (" << pid << ")" );

  std::ostringstream os;
  os << "LOG-MultiProcRollingFileAppender.Sub" << getpid();
  log4cxx::LoggerPtr lp  = log4cxx::Logger::getLogger(os.str());
  LOG4CXX_INFO(lp, "test_log4j_props_appender  MSG 1 - SUB logger (" << pid << ")" );
  LOG4CXX_INFO(lp, "test_log4j_props_appender  MSG 2 - SUB logger (" << pid << ")" );
  LOG4CXX_INFO(lp, "test_log4j_props_appender  MSG 3 - SUB logger (" << pid << ")" );

  LOG4CXX_INFO(logger, "RH_SyncRollingAppender -END ");
  usleep(1000);
  }
  
}


void 
test_suite_one::test_two()
{
  LOG4CXX_INFO(logger, "MultiProcess Test - BEGIN ");
  
  typedef std::vector< int >   Chillens;

  Chillens chillens;
  int cnt=10;
  for( int i=0; i<cnt; i++ ) {
    chillens.push_back(  system("./proc_log ") );
  }
    
  usleep(1000);

  LOG4CXX_INFO(logger, "MultiProcess Test - END ");

}


void 
test_suite_two::setUp()
{

  // Set up a simple configuration that logs on the console.
  log4cxx::PropertyConfigurator::configure("log4j.stdout" );

  log4cxx::helpers::LogLog::setInternalDebugging(true);

  logger = log4cxx::Logger::getLogger("LOG-SyncRollingAppender");

  LOG4CXX_INFO(logger, "Setup cache directory for saved configuration files");
  boost::filesystem::path dir("./logs");
  boost::filesystem::create_directory(dir);
}

void 
test_suite_two::tearDown()
{
  // Set up a simple configuration that logs on the console.
  log4cxx::PropertyConfigurator::configure("log4j.stdout" );

  boost::filesystem::path dir("./logs");
  boost::filesystem::remove_all(dir);

}


void 
test_suite_two::test_loop()
{
  LOG4CXX_INFO(logger, "RH_SyncRollingAppender - BEGIN ");

  // Set up a simple configuration that logs on the console.
  log4cxx::PropertyConfigurator::configure("log4j.appender" );
  int cnt=10;
  int pid = getpid();
  
  while ( 1 ) {
   LOG4CXX_INFO(logger, "test_log4j_props_appender  MSG 1 - root logger (" << pid << ")" );
   LOG4CXX_INFO(logger, "test_log4j_props_appender  MSG 2 - root logger (" << pid << ")" );
   LOG4CXX_INFO(logger, "test_log4j_props_appender  MSG 3 - root logger (" << pid << ")" );

  std::ostringstream os;
  os << "LOG-MultiProcRollingFileAppender.Sub" << getpid();
  log4cxx::LoggerPtr lp  = log4cxx::Logger::getLogger(os.str());
  LOG4CXX_INFO(lp, "test_log4j_props_appender  MSG 1 - SUB logger (" << pid << ")" );
  LOG4CXX_INFO(lp, "test_log4j_props_appender  MSG 2 - SUB logger (" << pid << ")" );
  LOG4CXX_INFO(lp, "test_log4j_props_appender  MSG 3 - SUB logger (" << pid << ")" );

  LOG4CXX_INFO(logger, "RH_SyncRollingAppender -END ");
  usleep(10);
  }
  
}
