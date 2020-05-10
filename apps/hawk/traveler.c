#include <stdio.h>
#include <string.h>
#include <libpq-fe.h>

int prompt_for_destination(char* destination)
{
    printf("What country do you want to go to? ");    
    char input[128];
    fgets(input, 128, stdin);

    char country[128];
    strncpy(country, input, strlen(input) - 1); // Trying to remove the newline included by fgets.
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
        printf("Connection to database failed: %s", PQerrorMessage(cxn));
    }
    else
    {
        PGresult* result = PQexec(cxn, query);
        int fields = PQnfields(result);
        // To get the name of a column in the result PQfname(result, index))

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

int print_out_string(char* line)
{
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == '\n')
        {
            printf("[%d] line-feed", i);
        }
        else if (line[i] == '\r')
        {
            printf("[%d] carriage-return", i);
        }
        else
        {
            printf("[%d] %c", i, line[i]);
        }
        
        printf("\n");
    }

    printf("Total length of this line: %lu\n", strlen(line));

    return 0;
}

int load_csv_file()
{
    FILE* file = fopen("../../data/country-codes.csv", "r");

    int line_count = 0;
    char line[256];

    while (fgets(line, 256, file) != NULL)
    {
        line_count++;
    }

    printf("Number of lines in the file: %d\n", line_count);
    rewind(file);

    int country_count = line_count;

    char tmp[256];
    char lines[country_count][256];

    for (int i = 0; i < country_count; i++)
    {
        fgets(lines[i], 256, file);
    }

    size_t array_length = (sizeof lines) / (sizeof lines[0]);
    printf("Number elements in the array: %zu\n", array_length);

    fclose(file);

    char countries[country_count][256];

    for (int j = 0; j < country_count; j++)
    {
        if (j != 247)
        {
            strncpy(countries[j], lines[j], strlen(lines[j]) - 2);
        }
    }

    for (int k = 0; k < country_count; k++)
    {
        int diff = strlen(lines[k]) - strlen(countries[k]);

        if (diff != 2)
        {
            printf("This one is screwed up: %d\n", k);
            printf("%s", lines[k]);
            printf("Length of line: %lu / Length of country: %lu\n\n", strlen(lines[k]), strlen(countries[k]));
        }
    }

    /*
    // Now we can inspect elements in the array.
    int index = 242;
    // printf("Which country would you like to visit? ");
    // fscanf(stdin, "%d", &index);
    printf("Original line %s", lines[index]);
    print_out_string(lines[index]);

    // char tmp[256];
    // strncpy(tmp, lines[index], strlen(lines[index]) - 2);
    // printf("Here you go after trimming! %s\n", tmp); // Need to add newline here, as expected.
    // print_out_string(tmp);
    
    printf("Modified country %s\n", countries[index]); // Need to add newline here, as expected.
    print_out_string(countries[index]);
    */

    return 0;
}

int main(int argc, char* argv[])
{
    printf("Are you ready to travel?\n");

    load_csv_file();

    return 0;
}
