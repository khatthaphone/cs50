#include <stdio.h>
#include <cs50.h>
#include "student.h"

int main(void)
{

    int enrollment = get_int("How many students?");

    student students[enrollment];

    // prompt users to type students' names and dorm
    for (int i = 0; i < enrollment; i++)
    {
        students[i].name = get_string("type student's name:\n");
        students[i].dorm = get_string("type student's dorm:\n");
    }

    // print students' names and dorms to file

    FILE *file = fopen("file.csv", "w");
    if(file)
    {

        fprintf(file, "%s,%s\n", "Name", "Dorm");

        for (int i = 0; i < enrollment; i++)
        {
            fprintf(file, "%s,%s\n", students[i].name, students[i].name);
        }

    }

    fclose(file);
}