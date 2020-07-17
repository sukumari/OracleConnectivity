/* This file contains view metadata related sql queries */

#include <string>
#include <vector>

using namespace std;

vector<string> totalQueriesToRun();

vector<string> sql_queries;

vector<string> totalQueriesToRun() {
string sql = "SELECT view_name FROM dba_views WHERE OWNER='SYS'";

string sql1 = "SELECT nvl(VIEW_TYPE, 'STANDARD') as type, " \
              "CASE " \
                "WHEN VIEW_TYPE IS NULL THEN '' " \
                "WHEN VIEW_TYPE = 'XMLTYPE' THEN ' OF ' || TYPE_TEXT || ' WITH OBJECT IDENTIFIER ' || " \
                  "CASE " \
                    "WHEN OID_TEXT = null OR OID_TEXT = 'DEFAULT' THEN 'DEFAULT' " \
                    "ELSE '(' || OID_TEXT || ')' " \
                  "END " \
                "ELSE ' OF ' || VIEW_TYPE_OWNER || '.' || VIEW_TYPE || " \
                  "CASE " \
                    "WHEN SUPERVIEW_NAME IS NULL THEN ' WITH OBJECT IDENTIFIER ' || " \
                      "CASE " \
                        "WHEN OID_TEXT = null OR OID_TEXT = 'DEFAULT' THEN 'DEFAULT' " \
                        "ELSE '(' || OID_TEXT || ')' " \
                      "END " \
                    "ELSE ' UNDER ' || SUPERVIEW_NAME " \
                  "END " \
              "END " \
              "FROM dba_views " \
              "WHERE owner='SYS' AND view_name='DBMS_SQLPATCH_STATE' ";

string sql2 = "SELECT column_name " \
              "FROM dba_tab_cols " \
              "WHERE owner='SYS' AND table_name='DBMS_SQLPATCH_STATE' " \
              "ORDER BY column_id ";
              
string sql3 = "SELECT " \
                "DECODE(dc.generated, 'GENERATED NAME', '', 'CONSTRAINT ' || dc.constraint_name || ' ') constname, " \
                "CASE dc.CONSTRAINT_TYPE " \
                  "WHEN 'P' THEN 'PRIMARY KEY ' " \
                  "WHEN 'U' THEN 'UNIQUE ' " \
                  "WHEN 'R' THEN 'FOREIGN KEY ' " \
                "END, " \
                "listagg(dcc.column_name, ', ')  WITHIN GROUP (ORDER BY dcc.position), " \
                "DECODE(dc.deferrable, 'DEFERRABLE', ' DEFERRABLE INITIALLY ' || dc.deferred, ''), " \
                "CASE " \
                  "WHEN dc.r_owner IS NULL THEN '' " \
                  "ELSE ' REFERENCES ' || dc.r_owner || '.' || dccR.table_name " \
                          "|| ' (' || listagg(dccR.column_name, ', ') WITHIN GROUP (ORDER BY dccR.column_name) || ')' " \
                "END, " \
                "CASE " \
                  "WHEN delete_rule IS NULL THEN '' " \
                  "WHEN delete_rule = 'CASCADE' THEN ' ON DELETE CASCADE' " \
                  "ELSE ' ON DELETE SET NULL' " \
                "END, " \
                "CASE dc.status " \
                  "WHEN 'ENABLED' THEN " \
                    "DECODE(dc.validated, 'VALIDATED', '', ' ENABLE NOVALIDATE') " \
                  "ELSE " \
                    "DECODE(dc.validated, 'VALIDATED', ' DISABLE VALIDATE', ' DISABLE') " \
                "END, " \
                "DECODE(dc.rely, 'RELY', ' RELY', '') " \
              "FROM dba_constraints dc " \
              "LEFT OUTER JOIN dba_cons_columns dcc ON dcc.owner=dc.owner AND dcc.CONSTRAINT_NAME = dc.constraint_name " \
              "LEFT OUTER JOIN dba_cons_columns dccR ON dc.r_owner=dccR.OWNER AND dc.R_CONSTRAINT_NAME = dccR.constraint_name " \
              "WHERE (dc.constraint_type = 'P' OR dc.constraint_type = 'U' OR dc.constraint_type = 'R') " \
                "AND dc.owner='SYS' and dc.table_name='DBMS_SQLPATCH_STATE' " \
                "AND dcc.column_name!='SYS_NC_ROWINFO$' AND dcc.column_name!='SYS_NC_OID$' " \
              "GROUP BY " \
                "dc.constraint_type, dc.constraint_name, dc.generated, dc.deferrable, dc.deferred, " \
                "dc.status, dc.validated, dc.rely, dc.r_owner, dccR.table_name, dc.delete_rule " \
              "ORDER BY dc.CONSTRAINT_TYPE, dc.CONSTRAINT_NAME ";

string sql4 = "SELECT " \
                "CASE " \
                  "WHEN " \
                    "VIEW_TYPE IS NULL " \
                      "AND " \
                    "(SELECT COUNT(column_name) FROM dba_tab_cols WHERE owner='SYS' AND table_name='DBMS_SQLPATCH_STATE') != 0 " \
                  "THEN chr(10) || chr(9) || ')' " \
                  "ELSE '' " \
                "END, " \
                "nvl(text, ''), " \
                "CASE " \
                  "WHEN text IS NULL THEN text_vc " \
                  "ELSE '' " \
                "END " \
              "FROM dba_views " \
              "WHERE owner='SYS' AND view_name='DBMS_SQLPATCH_STATE' ";

string sql5 = "SELECT grantee, privilege, grantor, " \
                "CASE " \
                  "WHEN GRANTABLE = 'Y' OR GRANTABLE = 'YES' THEN ' WITH GRANT OPTION' " \
                  "ELSE '' " \
                "END, " \
                "CASE " \
                  "WHEN HIERARCHY = 'Y' OR HIERARCHY = 'YES' THEN ' WITH HIERARCHY OPTION' " \
                  "ELSE '' " \
                "END " \
              "FROM dba_tab_privs " \
              "WHERE owner='SYS' AND table_name='DBMS_SQLPATCH_STATE' " \
              "ORDER BY grantee, privilege, grantor ";
    sql_queries.push_back(sql);
    sql_queries.push_back(sql1);
    sql_queries.push_back(sql2);
    sql_queries.push_back(sql3);
    sql_queries.push_back(sql4);
    sql_queries.push_back(sql5);

    return sql_queries;
}
