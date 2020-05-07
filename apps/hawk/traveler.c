#include <stdio.h>
#include <string.h>
#include <libpq-fe.h>

int prompt_for_destination(char* destination)
{
    printf("What country do you want to go to? ");    
    char input[128];
    fgets(input, 128, stdin);

    char country[128];
    strncpy(country, input, strlen(input) - 1);
    printf("Looks like you are going to %s\n", country);

    strncpy(destination, country, strlen(country));

    return strlen(country);
}

int query_database(char* country)
{
    char* template = "SELECT id, country, code FROM countries WHERE country LIKE '%%%s%%'";
    char query[128];
    sprintf(query, template, country);

    const char* connection_string = "dbname = traveler";
    PGconn* cxn = PQconnectdb(connection_string);

    if (PQstatus(cxn) != CONNECTION_OK)
    {
        printf("Connection to database failed %s", PQerrorMessage(cxn));
    }
    else
    {
        PGresult* result = PQexec(cxn, query);
        int fields = PQnfields(result);
        // To get the name of a column in the result PQfname(result, i))

        for (int i = 0; i < PQntuples(result); i++)
        {
            for (int j = 0; j < fields; j++)
            {
                printf("%s  ", PQgetvalue(result, i, j));
            }

            printf("\n");
        }

        PQclear(result);
    }

    PQfinish(cxn);

    return 0;
}

int load_csv_file()
{
    FILE* file = fopen("../../data/country-codes.csv", "r");

    int lineCount = 0;
    char line[256];

    while (fgets(line, 256, file) != NULL)
    {
        //result = fscanf(file, "%s\n", line);
        printf("%s", line);
        lineCount++;
    }

    printf("Number of lines: %d\n", lineCount); 

    // fpos_t position;
    // fgetpos(file, &position);

    fclose(file);

    return 0;
}

int main(int argc, char* argv[])
{
    printf("Are you ready to travel?\n");

    load_csv_file();

    return 0;
}
