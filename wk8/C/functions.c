#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

/// Converts a percentage into a grade.
char GradeFromPercentage(float percentage) {
    if (percentage >= 90.0) {
        return 'A';
    } else if (percentage >= 70) {
        return 'B';
    } else if (percentage >= 50) {
        return 'C';
    } else if (percentage >= 30) {
        return 'D';
    } else {
        return 'F';
    }
}

/// Converts mars into a grade.
char GradeFromRawMarks(float marksAwarded, float marksAvailable) {
    return GradeFromPercentage( (marksAwarded / marksAvailable) * 100.0 );
}

/// Converts a set of mars into a grade
char GradeFromTotalRawMarks(float marksAwarded[], float marksAvailable[], size_t maxAssignments) {
    float awarded = 0;
    float available = 0;
    for (size_t i = 0; i < maxAssignments; i++) {
        awarded = awarded + marksAwarded[i];
        available = available + marksAvailable[i];
    }
    return GradeFromRawMarks(awarded, available);
}


/// Checks if a char is uppercase 
bool IsUppercase(char a) {
    if (a >= 65 && a <= 90) {
        return true;
    } else {
        return false;
    }
}

/// Checks if a char is lowercase
bool IsLowercase(char a) {
    if (a >= 97 && a <= 122) {
        return true;
    } else {
        return false;
    }
}

/// Checks if two chars are alphabetical and the same (ignoring case)
bool CaseCheck(char a, char b) {
    if (IsUppercase(a)) {
        a = a + 32;
    }
    if (IsUppercase(b)) {
        b = b + 32;
    }

    if (IsLowercase(a) && IsLowercase(b)) { // True for all alphabetical values now
        if (a == b) {
            return true;
        }
    }
    return false;
}

int main(void)  {

    // Demonstrate grade from percent generation
    float input;
    fputs("Enter percentage: ", stdout);
    fscanf(stdin, "%f", &input);
    fprintf(stdout, "Grade: %c\n", GradeFromPercentage(input));

    fputs("\n", stdout);


    // Demonstrate grade from marks generation
    float awarded;
    float max;
    fputs("Enter Marks Awarded: ", stdout);
    fscanf(stdin, "%f", &awarded);
    fputs("Enter Maximum Marks: ", stdout);
    fscanf(stdin, "%f", &max);
    fprintf(stdout, "Grade: %c\n", GradeFromRawMarks(awarded, max));

    fputs("\n", stdout);


    // Demonstrate list of marks into grade
    float awarded_l[100];
    float available_l[100];
    size_t count = 1;
    char confirm[2];
    while (count <= 100) { // 'outer_loop
        fputs("Enter Marks Awarded: ", stdout);
        fscanf(stdin, "%f", &awarded_l[count-1]);
        fputs("Enter Maximum Marks: ", stdout);
        fscanf(stdin, "%f", &available_l[count-1]);

        if (count != 100) { while (true) {
            fputs("Enter another grade [y/n]? ", stdout);
            fscanf(stdin, "%1s", confirm);
            
            if (CaseCheck(confirm[0], 'n')) {
                goto end_outer_loop; // break 'outer_loop; ::::  READ COMMENT ON LABEL
            } else if (CaseCheck(confirm[0], 'y')) {
                break;
            } else {
                fputs("Invalid Input\n", stdout);
                continue;
            }
        } }

        count++;
    }
end_outer_loop: // THIS IS ACTUALLY ONE OF THE LAST SANE USES OF GOTO, IN LIEU OF LABELLED BREAKS
    fprintf(stdout, "Grade: %c\n", GradeFromTotalRawMarks(awarded_l, available_l, count));

    return 0;
}
