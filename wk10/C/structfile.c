#include<stdbool.h>
#include<stddef.h>
#include<stdio.h>
#include<string.h>

/// Models an AccessRecord.
typedef struct AccessRecord AccessRecord;
struct AccessRecord {
    size_t customer_id;
    char domain[256];
    char timestamp[20];
};
/// Create a new empty AccessRecord, fully initialized but not populated.
AccessRecord p_AccessRecord_new_raw(void) {
    return (AccessRecord) {
        .customer_id = 0,
        .domain = { 0 },
        .timestamp = "YYYY-MM-DD HH:MM:SS" // Format characters pre-positioned
    };
}
/// Create a new AccessRecord, all time and date strings are handled as exact width and do not need
/// to be zero terminated. Domain must be zero terminated.
AccessRecord AccessRecord_new(size_t customer_id, char domain[256], char year[4], char month[2], 
                              char day[2], char hour[2], char minute[2], char second[2]) {

    AccessRecord new_access_record = p_AccessRecord_new_raw();
    new_access_record.customer_id = customer_id;
    strcpy(new_access_record.domain, domain);
    strncpy(&new_access_record.timestamp[0], year, 4);
    strncpy(&new_access_record.timestamp[5], month, 2);
    strncpy(&new_access_record.timestamp[8], day, 2);
    strncpy(&new_access_record.timestamp[11], hour, 2);
    strncpy(&new_access_record.timestamp[14], minute, 2);
    strncpy(&new_access_record.timestamp[17], second, 2);

    return new_access_record;
}
/// Nicely formats and outputs an AccessRecord
void AccessRecord_display(AccessRecord *self, FILE *stream) {
    fprintf(stream, "%s: User %zd visited %s", self->timestamp, self->customer_id, self->domain);
}
/// Formats an AccessRecord for serialization
void AccessRecord_serial(AccessRecord *self, FILE *stream) {
    fprintf(stream, "%zd|%s|%s", self->customer_id, self->domain, self->timestamp);
}

void menu_add(AccessRecord records[100], size_t *record_count) {
    size_t customer_id;
    char domain[256];
    char year[5];
    char month[3];
    char day[3];
    char hour[3];
    char minute[3];
    char second[3];

    fputs("Enter a Customer ID: ", stdout);
    fscanf(stdin, "%zd", &customer_id);
    fputs("Enter a Domain: ", stdout);
    fscanf(stdin, "%255s", domain);
    fputs("Enter a Timestamp: ", stdout);
    fscanf(stdin, "%4s-%2s-%2s %2s:%2s:%2s", year, month, day, hour, minute, second);

    records[*record_count] = AccessRecord_new(customer_id, domain, year, month, 
                                              day, hour, minute, second);

    (*record_count)++;
}

void menu_list(AccessRecord records[100], size_t *record_count) {
    for (size_t i = 0; i < *record_count; i++) {
        AccessRecord_display(&records[i], stdout);
        fputs("\n", stdout);
    }
}

void menu_file(AccessRecord records[100], size_t *record_count) {
    size_t customer_id;
    char buffer[256];
    char year[5];
    char month[3];
    char day[3];
    char hour[3];
    char minute[3];
    char second[3];

    fputs("Enter a file path: ", stdout);
    fscanf(stdin, "%s", buffer);

    FILE *file = fopen(buffer, "r");

    while (EOF != fscanf(file, "%zd|%255[^|]|%4[^-]-%2[^-]-%2[^-] %2[^:]:%2[^:]:%2[^\n]\n",
                         &customer_id, buffer, year, month, day, hour, minute, second)) {

        records[*record_count] = AccessRecord_new(customer_id, buffer, year, month, 
                                                  day, hour, minute, second);


        AccessRecord_display(&records[*record_count], stdout);
        puts("");

        (*record_count)++;

    }

    fclose(file);
}

void menu_write(AccessRecord records[100], size_t *record_count) {
    char buffer[256];

    fputs("Enter a file path: ", stdout);
    fscanf(stdin, "%s", buffer);

    FILE *file = fopen(buffer, "w");

    for (size_t i = 0; i < *record_count; i++) {
        AccessRecord_serial(&records[i], file);
        fputs("\n", file);
    }

    fclose(file);
}

void menu_user(AccessRecord records[100], size_t *record_count) {
    size_t user;
    fputs("Enter the user to query: ", stdout);
    fscanf(stdin, "%zd", &user);


    for (size_t i = 0; i < *record_count; i++) {
        if (records[i].customer_id == user) {
            AccessRecord_display(&records[i], stdout);
            fputs("\n", stdout);
        }
    }
}

void display_menu(AccessRecord records[100], size_t *record_count) {
    while (true) {
        fputs("\nA) Display all records.", stdout);
        fputs("\nB) Add a record.", stdout);
        fputs("\nC) Load from file.", stdout);
        fputs("\nD) Save to file.", stdout);
        fputs("\nE) Show user records.", stdout);
        fputs("\nQ) Quit Program", stdout);
        fputs("\n\n>>> ", stdout);

        char menu_choice = '?';

        fscanf(stdin, " %c", &menu_choice);

        if (menu_choice == 'A') {
            menu_list(records, record_count);
        }

        if (menu_choice == 'B') {
            menu_add(records, record_count);
        }

        if (menu_choice == 'C') {
            menu_file(records, record_count);
        }

        if (menu_choice == 'D') {
            menu_write(records, record_count);
        }

        if (menu_choice == 'E') {
            menu_user(records, record_count);
        }

        if (menu_choice == 'Q') {
            return;
        }
    }
}

int main(void) {
    AccessRecord records[100];
    size_t record_count = 0;

    display_menu(records, &record_count);

    return 0;
}
