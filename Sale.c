#include <stdio.h>
#include <stdlib.h>

#define MONTHS 12

//Function to open The input.txt file, 
void sales_from_file(char *filename, double *sales) {
    FILE *input_file = fopen(filename, "r");
    //Error handling for opening the file
    if (input_file == NULL) {
        perror("Error opening file"); //Got this from google it prints the description of the last error
        exit(EXIT_FAILURE);
    }
//Iterate through the months
    for (int i = 0; i < MONTHS; ++i) {
        //Error handling for the reading the file 
        if (fscanf(input_file, "%lf", &sales[i]) != 1) {
            fprintf(stderr, "Error reading from file\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(input_file);
}

//Function to handle the display of the monthly sales
void sales_report(char **months, double *sales) {
    printf("Monthly sales report for 2022:\n");
    printf("%-10s %s\n", "Month", "Sales");

    for (int i = 0; i < MONTHS; ++i) {
        printf("%-10s $%.2f\n", months[i], sales[i]);
    }
}

//Display a summary of sales including Max and Min
void sales_summary(char **months, double *sales) {
    double min_sale = sales[0];
    double max_sale = sales[0];
    double avg_sale = 0.0;

    for (int i = 0; i < MONTHS; ++i) {
        //Update the min and maz sales
        if (sales[i] < min_sale) {
            min_sale = sales[i];
        }
        if (sales[i] > max_sale) {
            max_sale = sales[i];
        }
        avg_sale += sales[i];
    }

    avg_sale /= MONTHS;

    printf("\nSales summary:\n");
    printf("Minimum sales: $%.2f (%s)\n", min_sale, months[0]);
    printf("Maximum sales: $%.2f (%s)\n", max_sale, months[MONTHS - 1]);
    printf("Average sales: $%.2f\n", avg_sale);
}

void six_month_moving_average(char **months, double *sales) {
    printf("\nSix-Month Moving Average Report:\n");

    for (int i = 0; i <= MONTHS - 6; ++i) {
        double average = 0.0;
        for (int j = 0; j < 6; ++j) {
            average += sales[i + j];
        }
        average /= 6;

        printf("%s - %s $%.2f\n", months[i], months[i + 5], average);
    }
}

void sorted_sales_report(char **months, double *sales) {
    printf("\nSales Report (Highest to Lowest):\n");

    // Create an array of indices and sort them based on sales
    int indices[MONTHS];
    for (int i = 0; i < MONTHS; ++i) {
        indices[i] = i;
    }
    //Sort the index based on the month and sales
    for (int i = 0; i < MONTHS - 1; ++i) {
        for (int j = i + 1; j < MONTHS; ++j) {
            if (sales[indices[i]] < sales[indices[j]]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    printf("%-10s %s\n", "Month", "Sales");//-10 specifies a minimum width of 10 characters
    for (int i = 0; i < MONTHS; ++i) {
        printf("%-10s $%.2f\n", months[indices[i]], sales[indices[i]]);
    }
}

int main() {
    //declaring the name of the file, incase you want to test new values ensure to keep the name the same
    char *filename = "input.txt";
    char *months[MONTHS] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    double sales[MONTHS];

    sales_from_file(filename, sales);

    sales_report(months, sales);
    sales_summary(months, sales);
    six_month_moving_average(months, sales);
    sorted_sales_report(months, sales);

    return 0;
}
