// Test for pset3
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int frequency(string note);

int main(void) {

    // if (argc == 2) {

    //     // printf("%i\n", duration(argv[1]));

    //     printf("%i\n", frequency(argv[1]));

    // }

    printf("%i\n", frequency("A4"));
    printf("%i\n", frequency("G4"));
    printf("%i\n", frequency("C5"));
    printf("%i\n", frequency("G#4"));
    printf("%i\n", frequency("C4"));
    printf("%i\n", frequency("Gb4"));
    printf("%i\n", frequency("C#5"));
    printf("%i\n", frequency("G4"));
    printf("%i\n", frequency("B4"));

}

int get_note_position(char note) {

    struct NOTE {
        char note;
        int position;
    };

    // Notes in an octave
    const struct NOTE NOTES[] = {
        {'C', 1},
        {'D', 3},
        {'E', 5},
        {'F', 6},
        {'G', 8},
        {'A', 10},
        {'B', 12}
    };

    int i;
    for (i = 0; i < sizeof(NOTES); i++) {
        if (note == NOTES[i].note) return NOTES[i].position;
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


    position = get_note_position(note[0]);

        if (position != false) {

        if (strlen(note) == 2) {

            octave = note[1] - '0';

        } else if (strlen(note) == 3) {

            octave = note[2] - '0';
            suffix = note[1];

        }

        int n = ((12 * octave) + 3 - (12 - position)) - 49;

        if (suffix == '#') n = n + 1;
        if (suffix == 'b') n = n - 1;

        double f = pow(2.0, ((double) n) / 12.0) * 440.0;

        printf("\n");
        printf("note = %c\n", note[0]);
        printf("position = %i\n", position);
        printf("octave = %i\n", octave);
        printf("n = %i\n", n);
        printf("f = %f\n", f);

        return (int) f;

    }

    return 0;

}
