#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Restaurant {
    char title[101];
    char city[101];
    int cost_for_two;
    char currency[101];
    int price_range;
    float rating;
    char rating_text[101];
    int votes;
};

void display_data(struct Restaurant restaurant_locations[], int number_of_rows) {
    printf(
        "%-25s %-18s %10s %-20s %6s %6s %-12s %6s\n",
        "Restaurant name",
        "City",
        "Cost",
        "Currency",
        "Range",
        "Rating",
        "Rating text",
        "Votes"
    );

    for (int i = 0; i < number_of_rows; i++)
    {
        printf("%-25s %-18s %10d %-20s %6d %6.1f %-12s %6d\n",
            restaurant_locations[i].title,
            restaurant_locations[i].city,
            restaurant_locations[i].cost_for_two,
            restaurant_locations[i].currency,
            restaurant_locations[i].price_range,
            restaurant_locations[i].rating,
            restaurant_locations[i].rating_text,
            restaurant_locations[i].votes
        );
    }
}

const int TOTAL_ROWS = 7369;

int main(int)
{
    FILE* fp = fopen("./restaurant.csv", "r");
    struct Restaurant restaurant_locations[TOTAL_ROWS];

    int count_row = 0;

    fscanf(fp, "%*[^\n]\n");

    while (
        count_row < TOTAL_ROWS &&
        fscanf(fp, "%[^,],%[^,],%d,%[^,],%d,%f,%[^,],%d\n",
            restaurant_locations[count_row].title,
            restaurant_locations[count_row].city,
            &restaurant_locations[count_row].cost_for_two,
            restaurant_locations[count_row].currency,
            &restaurant_locations[count_row].price_range,
            &restaurant_locations[count_row].rating,
            restaurant_locations[count_row].rating_text,
            &restaurant_locations[count_row].votes) == 8
    ) { 
        count_row++;
    }

    printf("What do you want to do?\n");
    printf("1. Display data\n");
    printf("2. Search data\n");
    printf("3. Sort data\n");
    printf("4. Export data\n");
    printf("5. Exit\n");
    
    int input = 0;

    printf("Your choice: ");
    scanf("%d", &input); getchar();

    if (input < 0) {
        printf("ERROR: input must be a positive integer\n");
        return 1;
    }

    if (input == 5) {
        printf("Exiting...\n");
        return 0;
    }

    if (input == 1) {
        int number_of_rows = 0;

        printf("Number of rows: ");
        scanf("%d", &number_of_rows); getchar();

        display_data(restaurant_locations, number_of_rows);
    }
    else if (input == 2) {
        char* headers[8] = {
            "Restaurant Name",
            "City",
            "Cost for two",
            "Currency",
            "Price range",
            "Rating",
            "Rating text",
            "Votes"
        };

        char column[101];

        int found = 0;
        int header_index = 0;

        while (found == 0) {
            printf("Choose column: ");

            scanf("%[^\n]", column); getchar();
            
            for (int i = 0; i < 8; i++) {
                if (strcmp(headers[i], column) == 0) {
                    found = 1;
                    header_index = i;
                }
            }
        }

        char query_value[101];

        printf("What data do you want to find? ");

        scanf("%[^\n]", query_value); getchar();

        // printf("column: %s, query_value: %s\n", column, query_value);

        struct Restaurant filtered_restaurant[TOTAL_ROWS];

        int filtered_count = 0;

        for (int i = 0; i < TOTAL_ROWS; i++) {
            // restaurant name
            if (header_index == 0 && strcmp(restaurant_locations[i].title, query_value) == 0) {
                filtered_restaurant[filtered_count] = restaurant_locations[i];
                filtered_count++;
            }
            // city
            else if (header_index == 1 && strcmp(restaurant_locations[i].city, query_value) == 0) {
                filtered_restaurant[filtered_count] = restaurant_locations[i];
                filtered_count++;
            }
            // currency
            else if (header_index == 3 && strcmp(restaurant_locations[i].currency, query_value) == 0) {
                filtered_restaurant[filtered_count] = restaurant_locations[i];
                filtered_count++;
            }
            // rating text
            else if (header_index == 6 && strcmp(restaurant_locations[i].rating_text, query_value) == 0) {
                filtered_restaurant[filtered_count] = restaurant_locations[i];
                filtered_count++;
            }
            // not char type
            else {
                printf("ERROR: char type unsupported");
            }
        }

        display_data(filtered_restaurant, filtered_count);
    }
}