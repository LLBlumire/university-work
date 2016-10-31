#include<stdint.h>
#include<stdio.h>
#include<string.h>

/// Convert a value in seconds to a value in minutes and a value in seconds
void secminsec( uint32_t sec, uint32_t* omin, uint32_t* osec ) {
    *omin = sec / 60;
    *osec = sec % 60;
}

/// Nicely output a time
void puttime( uint32_t mins, uint32_t secs ) {
    printf("%u ", mins);
    if (mins == 1) {
        fputs("minute ", stdout);
    } else {
        fputs("minutes ", stdout);
    }
    printf("and %u ", secs);
    if (secs == 1) {
        fputs("second.", stdout);
    } else {
        fputs("seconds.", stdout);
    }
    puts("");
}

int main(void) {
    char snails[8][20];
    uint32_t legs[8][5];

    char confirm[2];

    // Get all inputs
    size_t count = 0;
    for ( ; count < 8 ; count++ ) {
        fputs("Enter Snail Name: ", stdout);
        fscanf(stdin, "%19s", snails[count]);;

        fputs("Enter time for each leg, separated by a space: ", stdout);
        fscanf(stdin, "%u %u %u %u", 
                &legs[count][0], 
                &legs[count][1], 
                &legs[count][2], 
                &legs[count][3]);

        // If it's not going to end anyway, check if they are done entering
        if (count != 8) {
            fputs("Would you like to continue? [y/n]: ", stdout);
            fscanf(stdin, "%1s", confirm);

            if (confirm[0] == 'n' || confirm[0] == 'N') {
                count++; // Fixes Off By 1 Error
                break;
            }
        }
    }

    // Sum all legs and output times
    uint32_t mins;
    uint32_t secs;
    for (size_t sumcount = 0; sumcount < count; sumcount++) {
        legs[sumcount][4] = 0;
        for (size_t legcount = 0; legcount < 4; legcount++) {
            legs[sumcount][4] += legs[sumcount][legcount];
        }
        secminsec(legs[sumcount][4], &mins, &secs);
        fprintf(stdout, "Snail %lu \"%s\" took ", sumcount+1, snails[sumcount]);
        puttime(mins, secs);
    }

    // Calculate fastest times for all legs
    uint32_t fastestspeeds[5] = {legs[0][0], legs[0][1], legs[0][2], legs[0][3], legs[0][4]};
    uint32_t fastestsnail[5] = {0, 0, 0, 0, 0}; // Initialize both to avoid undefined behaviour
    for (size_t sumcount = 0; sumcount < count; sumcount++) {
        for (size_t legcount = 0; legcount < 5; legcount++) {
            if (legs[sumcount][legcount] < fastestspeeds[legcount]) {
                fastestspeeds[legcount] = legs[sumcount][legcount];
                fastestsnail[legcount] = sumcount;
            }
        }
    }

    // Output fastest snail in each leg
    for (size_t legcount = 0; legcount < 5; legcount++) {
        // Update output times
        secminsec(fastestspeeds[legcount], &mins, &secs);
        if (legcount != 4) {
            fprintf(stdout, "The fastest time for leg %lu was set by snail %u \"%s\" as ", 
                    legcount+1, fastestsnail[legcount]+1, snails[fastestsnail[legcount]]);
        } else {
            fprintf(stdout, "The fastest overall time was set by snail %u \"%s\" as", 
                    fastestsnail[legcount]+1, snails[fastestsnail[legcount]]);
        }
        puttime(mins, secs);
    }
    
    return 0;
}
