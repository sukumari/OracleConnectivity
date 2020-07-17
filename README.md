# This repo contains POC for c++ application to connect Oracle Database using SQLAPI++.

#TestOracleConnectionWithOCI.cpp  - This file contains POC for C++ application using OCI driver to connect Oracle database.

#TestOracleConnectionWithODBC.cpp - This file contains POC for C++ application using ODBC driver to connect Oracle database.
  Theconnection string used in case of ODBC driver is 
    string url ="Driver={Oracle in OraDB18Home1};dbq=<host_ip>:<port_number>/<service_name>"; 
    con.Connect(url.c_str(), "user", "pwd", SA_ODBC_Client);
  Please note that "Oracle in OraDB18Home1" is name of ODBC driver. For more details, please refer https://www.connectionstrings.com/oracle/
  To check service_name in oracle database , we can use below query
    select value from v$parameter where name='service_nam
