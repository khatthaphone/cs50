// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

// Check if a number is one of the power of two
bool is_power_of_two(int n)
{
    if (n < 2)
    {
        return false;
    }
    if (n % 2 != 0)
    {
        return false;
    }

    while (n != 1)
    {
        if (n % 2 != 0)
        {
            return false;
        }
        n = n / 2;
    }

    return true;

}

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO

    // 1/4 => 2/8 => 2
    // 2/4 => 4/8 => 4
    // 3/4 => 6/8 => 6
    // 4/4 => 8/8 => 8

    if (strlen(fraction) == 3)
    {
        int num = fraction[0] - '0';
        int dem = fraction[2] - '0';

        if (is_power_of_two(dem))
        {
            return num * (8 / dem);
        }

    }

    // printf("%ld\n", strlen(fraction));

    return 0;

}


int get_note_position(char note)
{

    struct NOTE
    {
        char note;
        int position;
    };

    // Notes in an octave
    const struct NOTE NOTES_POS[] =
    {
        {'C', 1},
        {'D', 3},
        {'E', 5},
        {'F', 6},
        {'G', 8},
        {'A', 10},
        {'B', 12}
    };

    int i;
    for (i = 0; i < sizeof(NOTES_POS); i++)
    {
        if (note == NOTES_POS[i].note)
        {
            return NOTES_POS[i].position;
        }

    }

    return 0;
}


// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
    int position = 0;
    int octave = 0;
    char suffix = '\0';

    if (is_rest(note))
    {
        return 0;
    }

    position = get_note_position(note[0]);

    if (position != false)
    {

        if (strlen(note) == 2)
        {

            octave = note[1] - '0';

        }
        else if (strlen(note) == 3)
        {

            octave = note[2] - '0';
            suffix = note[1];

        }

        int n = ((12 * octave) + 3 - (12 - position)) - 49;

        if (suffix == '#')
        {
            n = n + 1;
        }
        if (suffix == 'b')
        {
            n = n - 1;
        }

        if (n >= -48 && n <= 39)
        {

            double f = pow(2.0, ((double) n) / 12.0) * 440.0;

            // printf("\n");
            // printf("note = %c\n", note[0]);
            // printf("position = %i\n", position);
            // printf("octave = %i\n", octave);
            // printf("n = %i\n", n);
            // printf("f = %i\n", f);

            return (int) round(f);

        }

        return 0;

    }

    return 0;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO

    // if line is blank, it is a rest
    if (strcmp(s, "\n") == 0 || s[0] == '\0')
    {
        return true;
    }

    return false;
}
