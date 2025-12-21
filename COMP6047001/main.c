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

int compare_restaurants(struct Restaurant a, struct Restaurant b, int column, int ascending) {
    int result = 0;

    // restaurant name
    if (column == 0) {
        result = strcmp(a.title, b.title);
    }
    // city
    else if (column == 1) {
        result = strcmp(a.city, b.city);
    }
    // cost for two
    else if (column == 2) {
        result = (a.cost_for_two > b.cost_for_two) - (a.cost_for_two < b.cost_for_two);
    }
    // currency
    else if (column == 3) {
        result = strcmp(a.currency, b.currency);
    }
    // price range
    else if (column == 4) {
        result = (a.price_range > b.price_range) - (a.price_range < b.price_range);
    }
    // rating
    else if (column == 5) {
        result = (a.rating > b.rating) - (a.rating < b.rating);
    }
    // rating text
    else if (column == 6) {
        result = strcmp(a.rating_text, b.rating_text);
    }
    // votes
    else if (column == 7) {
        result = (a.votes > b.votes) - (a.votes < b.votes);
    }

    return ascending ? result : -result;
}

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

    for (int i = 0; i < number_of_rows; i++) {
        printf("%-25s %-18s %10d %-20s %6d %6f %-12s %6d\n",
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

int choose_column_index() {
    char column[101];

    int found = 0;
    int header_index = 0;

    while (found == 0) {
        printf("Choose column: ");

        scanf("%[^\n]", column); getchar();
        
        for (int i = 0; i < 8; i++) {
            if (strcmp(HEADERS[i], column) == 0) {
                found = 1;
                header_index = i;
            }
        }
    }

    return header_index;
}

const int TOTAL_ROWS = 7369;

const char* HEADERS[8] = {
    "Restaurant Name",
    "City",
    "Cost for two",
    "Currency",
    "Price range",
    "Rating",
    "Rating text",
    "Votes"
};

int main(int) {
    FILE* fp = fopen("./restaurant.csv", "r");

    if (fp == NULL) {
        printf("ERROR: cannot open ./restaurant.csv");
        return 1;
    }

    struct Restaurant restaurant_locations[TOTAL_ROWS];

    fscanf(fp, "%*[^\n]\n");
    
    int count_row = 0;

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

    fclose(fp);

    printf("What do you want to do?\n");
    printf("1. Display data\n");
    printf("2. Search data\n");
    printf("3. Sort data\n");
    printf("4. Export data\n");
    printf("5. Exit\n");
    
    int input = 0;

    printf("Your choice: ");
    scanf("%d", &input); getchar();

    // must be positive integer per case study
    if (input < 0) {
        printf("ERROR: input must be a positive integer\n");
        return 1;
    }

    // exit
    if (input == 5) {
        printf("Exiting...\n");
        return 0;
    }

    // display data
    if (input == 1) {
        int number_of_rows = 0;

        printf("Number of rows: ");
        scanf("%d", &number_of_rows); getchar();

        if (number_of_rows > TOTAL_ROWS) {
            printf("ERROR: out of bounds\n");
            return -1;
        }
        
        if (number_of_rows < 0) {
            printf("ERROR: must be a positive integer\n");
            return -1;
        }

        display_data(restaurant_locations, number_of_rows);
    }
    // search data
    else if (input == 2) {
        int header_index = choose_column_index();

        if (header_index == 2
            || header_index == 4
            || header_index == 5
            || header_index == 7
        ) {
            printf("ERROR: int or float type column are not supported");
            return 1;
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
        }

        display_data(filtered_restaurant, filtered_count);
    }
    else if (input == 3) {
        int header_index = choose_column_index();

        char sort_option[5];

        do {
            printf("Sort ascending (asc) or descending (desc)? ");
    
            scanf("%[^\n]", sort_option); getchar();
        } while (
            strcmp(sort_option, "asc") != 0
            && strcmp(sort_option, "desc") != 0
        );

        struct Restaurant sorted_restaurant[TOTAL_ROWS];

        for (int i = 0; i < TOTAL_ROWS; i++) {
            sorted_restaurant[i] = restaurant_locations[i];
        }

        int sort_ascending = strcmp(sort_option, "asc") == 0;

        // alphabetical / numerical sorting
        for (int i = 0; i < TOTAL_ROWS - 1; i++) {
            for (int j = i + 1; j < TOTAL_ROWS; j++) {
                if (compare_restaurants(
                    sorted_restaurant[i],
                    sorted_restaurant[j],
                    header_index, sort_ascending) > 0
                ) {
                    struct Restaurant temp = sorted_restaurant[i];
                    sorted_restaurant[i] = sorted_restaurant[j];
                    sorted_restaurant[j] = temp;
                }
            }
        }

        display_data(sorted_restaurant, TOTAL_ROWS);
    }
    // export
    else if (input == 4) {
        char filename[101];

        printf("File name: ");
        scanf("%[^\n]", filename); getchar();

        if (strlen(filename) + 4 < 100) {
            strcat(filename, ".csv");
        }

        FILE* fexport = fopen(filename, "w");

        if (fexport == NULL) {
            printf("ERROR: cannot open %s\n", filename);
            return 1;
        }

        for (int i = 0; i < TOTAL_ROWS; i++) {
            fprintf(fexport, "%s,%s,%d,%s,%d,%f,%s,%d\n",
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

        printf("Data successfully written to file %s!\n", filename);

        fclose(fexport);
    }
}
