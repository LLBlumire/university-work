#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

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

void taska( void ) {
    char name[20];
    uint32_t time;

    // Get Name
    fputs("Enter snail name: ", stdout);
    scanf("%20s", name);

    // Get Time
    fputs("Enter the time taken: ", stdout);
    scanf("%u", &time);

    // Get Time in Minutes and Seconds
    uint32_t mins;
    uint32_t secs;
    secminsec(time, &mins, &secs);

    // Output Result
    printf("%s took ", name);
    puttime(mins, secs);
}


void taskb( void ) {
    char name[20];
    uint32_t times[4];

    // Get Name
    fputs("Enter snail name: ", stdout);
    scanf("%20s", name);

    // Get Times
    fputs("Enter the time for each leg, separated by a space: ", stdout);
    scanf("%u %u %u %u", &times[0], &times[1], &times[2], &times[3]);

    // Fold over times, accumulating sum to time
    uint32_t time = 0;
    for (size_t i = 0; i < 4; i++) {
        time += times[i];
    }
    
    // Get Time in Minutes and Seconds
    uint32_t mins;
    uint32_t secs;
    secminsec(time, &mins, &secs);

    // Output Result
    printf("%s took ", name);
    puttime(mins, secs);

}

void taskc( void ) {
    char name[20];
    uint32_t times[4];

    // Get Name
    fputs("Enter snail name: ", stdout);
    scanf("%20s", name);

    // Get Times
    fputs("Enter the time for each leg, separated by a space: ", stdout);
    scanf("%u %u %u %u", &times[0], &times[1], &times[2], &times[3]);

    // Fold over times, accumulating sum to time
    uint32_t time = 0;
    for (size_t i = 0; i < 4; i++) {
        time += times[i];
    }
    
    // Get Time in Minutes and Seconds
    uint32_t mins;
    uint32_t secs;
    secminsec(time, &mins, &secs);

    // Check qualification for WSRF International and Output
    if (mins <= 3) {
        printf("%s did ", name);
    } else {
        printf("%s did not ", name);
    }
    fputs("qualify for the WSRF International Tournament, with a time of ", stdout);
    puttime(mins, secs);
}

void taskd( void ) {
    char name[20];
    uint32_t times[4];

    // Get Name
    fputs("Enter snail name: ", stdout);
    scanf("%20s", name);

    // Get Time
    fputs("Enter the time for each leg, separated by a space: ", stdout);
    scanf("%u %u %u %u", &times[0], &times[1], &times[2], &times[3]);

    // Fold over times, accumulating sum to time
    uint32_t time = 0;
    for (size_t i = 0; i < 4; i++) {
        time += times[i];
    }

    // Get Time in Minutes and Seconds
    uint32_t mins;
    uint32_t secs;
    secminsec(time, &mins, &secs);

    // Identify Tournaments Qualified For
    if (mins <= 3) {
        printf("%s did qualify for the WSRF International Tournament, ", name);
    } else if (mins <= 11) {
        printf("%s did qualify for the WSRF National Race Meeting, ", name);
    } else if (mins <= 29) {
        printf("%s did qualify for the WSRF Beginner's League, ", name);
    } else {
        printf("%s did not qualify for any tournaments, ", name);
    }
    fputs("with a time of ", stdout);
    puttime(mins, secs);
}


int main(void) {
    puts("Week 5 a.");
    taska();
    puts("\nWeek 5 b.");
    taskb();
    puts("\nWeek 5 c.");
    taskc();
    puts("\nWeek 5 d.");
    taskd();

    return 0;
}
