#include <stdio.h>

void Score_Combo(int score) {
    int td_count, fg_count, tdfg_count, tdconvert_count, safety_count;

    for (td_count = 0; score >= (8 * td_count); td_count++) {
        for (tdfg_count = 0; (8 * td_count + 7 * tdfg_count) <= score; tdfg_count++) {
            for (tdconvert_count = 0; (8 * td_count + 7 * tdfg_count + 6 * tdconvert_count) <= score; tdconvert_count++) {
                for (fg_count = 0; (8 * td_count + 7 * tdfg_count + 6 * tdconvert_count + 3 * fg_count) <= score; fg_count++) {
                    for (safety_count = 0; (8 * td_count + 7 * tdfg_count + 6 * tdconvert_count + 2 * safety_count) <= score; safety_count++) {
                        if (score == (8 * td_count + 7 * tdfg_count + 6 * tdconvert_count + 3 * fg_count + 2 * safety_count)) {
                            printf("%d TD + %d 2pt, %d TD + %d %d 3pt FG, %d Safety\n", td_count, safety_count, fg_count, tdfg_count, tdconvert_count, safety_count);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int score;

    while (1) {
        printf("Enter 0 or 1 to Stop.\n");
        printf("Enter the NFL score: ");
        scanf("%d", &score);

        if (score <= 1) {
            printf("Program terminated.\n");
            break;
        }

        printf("Possible combinations of scoring plays:\n");
        Score_Combo(score);
    }

    return 0;
}
