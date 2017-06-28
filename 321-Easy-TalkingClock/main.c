#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char * digits[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

char * teens[] = { "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };

char * tens[] = { "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };

char * num_to_string(int num);
char * get_minute_name(int min);
char * get_hour_name(int hrs);

int main(void)
{
    while(true) {
        int hours = -1, minutes = -1;
        scanf("%d:%d", &hours, &minutes);

        if(hours >= 24 || hours < 0 || minutes >= 60 || minutes < 0) {
            puts("Invalid time, aborting...");
            break;
        }

        char * meridian = hours < 12? "am" : "pm";
        char * hour_name = get_hour_name(hours);

        if(minutes == 0) {
            printf("It's %s %s\n", hour_name, meridian);
        }
        else {
            char * minute_name = get_minute_name(minutes);
            printf("It's %s %s %s\n", hour_name, minute_name, meridian);
            free(minute_name);
        }

        free(hour_name);
    }
    return 0;
}

char * get_hour_name(int hrs) {
    hrs = hrs % 12;
    // 0 o'clock is actually 12 o'clock
    hrs = hrs == 0? 12 : hrs;

    return num_to_string(hrs);
}

char * get_minute_name(int min) {
    char * result;

    char * min_str = num_to_string(min);
    if(min < 10 && min > 0) {
        result = malloc(strlen(min_str) + 4); 

        sprintf(result, "oh %s", min_str);
        free(min_str);
    }
    else {
        result = min_str;
    }

    return result;
}

/**
 * 0 =< num < 60
 */
char * num_to_string(int num) {
    char * result;

    if(num == 0) {
        result = malloc(1);
        result[0] = 0;
    }
    else if(num < 10) {
        result = malloc(strlen(digits[num - 1]) + 1);
        strcpy(result, digits[num - 1]);
    }
    else if(num < 20 && num > 10) {
        result = malloc(strlen(teens[num - 11]) + 1);
        strcpy(result, teens[num - 11]);
    }
    else {
        char * ten = tens[num / 10 - 1];

        if(num % 10 == 0) {
            result = malloc(strlen(ten) + 1);
            sprintf(result, "%s", ten);
        }
        else {
            char * digit = num_to_string(num % 10);
            result = malloc(strlen(ten) + strlen(digit) + 2);
            sprintf(result, "%s %s", ten, digit);
            free(digit);
        }
    }

    return result;
}
