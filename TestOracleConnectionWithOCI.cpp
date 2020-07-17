// TestOracleConnectionWithOCI.cpp : Defines the entry point for the console application.
//
/*

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
*/
#include <iostream>  // for printf
#include <stdlib.h>
#include <ctime>
#include <SQLAPI.h>
#include "SqlQueries.h"

using namespace std;

clock_t START_TIMER;

clock_t startTimer()
{
    return START_TIMER = clock();
}

void stopTimer(clock_t start = START_TIMER)
{
    cout
        << "Elapsed time: "
        << (clock() - start) / (double)CLOCKS_PER_SEC << "s"
        << endl;
}

void createOracleConnection(SAConnection& con)
{
    string url ="(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=10.248.139.221)(PORT=1521))(CONNECT_DATA=(SERVICE_NAME=orcl.tripwirelab.com)))";
    con.setOption("UseApi") = "OCI8";
    con.Connect(url.c_str(), "scott", "tiger", SA_Oracle_Client);
    if(con.isConnected()) {
        cout << "Database connected sucessfully" << "\n";
    }   
}

int main()
{
    SAConnection con; // connection object

    vector<string> view_sql_queries = totalQueriesToRun();
    // Declaring iterator to a vector 
    vector<string>::iterator itr; 
    try {
        // connect to database (Oracle in our example)
        createOracleConnection(con);
        for (int i =1; i <=5; ++i) {
            SACommand cmd(&con);
            startTimer();
            for (int i =1; i <=50; ++i) {
                for (itr = view_sql_queries.begin(); itr < view_sql_queries.end(); itr++) {
                    cmd.setCommandText((*itr).c_str());
                    cmd.Execute();
                }
            }
            stopTimer();
        }

        // commit changes on success
        con.Commit();

        if(con.isConnected()) {
            con.Disconnect();
        }
        cout << "Press any key to exit" << "\n";
        std::cin.get();
    }
    catch(SAException &x)
    {
       cout << "Exception caught ......."<<"\n";
        cout <<  (const char*)x.ErrText();
        cout << "Press any key to exit" << "\n";
        std::cin.get();
    }
    
    return 0;
}

