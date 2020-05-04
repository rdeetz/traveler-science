#include <stdio.h>
#include <string.h>
#include <libpq-fe.h>

int main(int argc, char* argv[])
{
    // Accept an input, query the database, return results.
    // Accept an input, query the search index via API, return results.
    // Accept an input, load a CSV files, query the files, return results.

    printf("Are you ready to travel?\n");

    printf("What country do you want to go to? ");
    
    char input[128];
    fgets(input, 128, stdin);
    char country[128];
    strncpy(country, input, strlen(input) - 1);

    printf("Looks like you are going to %s\n", country);

    char* template = "SELECT id, country, code FROM countries WHERE country LIKE '%%%s%%'";
    char query[128];
    sprintf(query, template, country);

    const char* conninfo = "dbname = traveler";

    PGconn* conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK)
    {
        printf("Connection to database failed %s", PQerrorMessage(conn));
    }
    else
    {
        PGresult* res = PQexec(conn, query);

        int fields = PQnfields(res);
        // To get the name of a column in the result PQfname(res, i))

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
