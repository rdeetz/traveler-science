#include <stdio.h>
#include <libpq-fe.h>

int main(int argc, char* argv[])
{
    printf("Are you ready to travel?\n");

    const char* conninfo;
    PGconn* conn;

    conninfo = "dbname = traveler";
    conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK)
    {
        printf("You are not ready to travel.\n");
    }
    else
    {
        printf("You ARE ready to travel!\n");
    }

    PQfinish(conn);

    return 0;
}
