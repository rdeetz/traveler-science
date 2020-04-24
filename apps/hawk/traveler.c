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
        printf("Connection to database failed %s", PQerrorMessage(conn));
    }
    else
    {
        printf("You ARE ready to travel!\n");

        PGresult* res = PQexec(conn, "SELECT * FROM countries");

        int fields = PQnfields(res);

        for (int i = 0; i < fields; i++)
        {
            printf("%-2s\n", PQfname(res, i));
        }

        for (int i = 0; i < PQntuples(res); i++)
        {
            for (int j = 0; j < fields; j++)
            {
                printf("%s  ", PQgetvalue(res, i, j));
            }

            printf("\n");
        }

        PQclear(res);
    }

    PQfinish(conn);

    return 0;
}
