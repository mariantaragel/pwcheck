/**
 * @name pwcheck.c
 * @details checking password strength
 * @author Marian Taragel
 * @date 28.10.2021
 */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX 100

typedef struct{
	int nchars;
	int min;
	float total_number_of_characters;
	float number_of_passwords;
	char array_of_characters[256];
} Stats;

/**
 * count length of the string
 * 
 * @param string
 * @return length of the string
 */
int string_length(char *string)
{
	int string_length = 0;
	while (string[string_length] != '\0'){
		string_length++;
	}

	return string_length;
}

/**
 * compare whether two strings are identical
 * 
 * @param string1
 * @param string2
 * @return TRUE when strings are identical, otherwise FALSE
 */
int compare_strings(char string1[], char string2[])
{
	int length1 = string_length(string1);
	int length2 = string_length(string2);

	// when strings have different length, they cannot be indentical
	if (length1 != length2){
		return FALSE;
	}

	// strings are identical when they have exactly the same characters on the same indexes
	for (int i = 0; i < length1; i++){
		if (string1[i] == string2[i]){
			continue;
		}
		else {
			return FALSE;
		}
	}

	return TRUE;
}

/**
 * @param c character to be found
 * @param array the array in which a character schould be sought for
 * @return TRUE when character is found, otherwise FALSE
 */
int find_character_in_array(char c, char array[])
{
	int password_length = string_length(array);
    for (int i = 0; i < password_length; i++){
        if (array[i] == c){
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * checks if a character is lowercase
 * 
 * @param c character to classify
 * @return TRUE when character c is lowercase, otherwise FALSE
 */
int is_lower(char c)
{
	if (c >= 'a' && c <= 'z') {
		return TRUE;
	}

	return FALSE;
}

/**
 * checks if a character is uppercase
 * 
 * @param c character to classify 
 * @return TRUE when character c is uppercase, otherwise FALSE
 */
int is_upper(char c)
{
	if (c >= 'A' && c <= 'Z') {
		return TRUE;
	}

	return FALSE;
}


/**
 * @param stats structure we want inicialized
 * @return inicialized stats to default values
 */
Stats intialized_stats(Stats stats){
	stats.nchars = 0;
	stats.min = MAX;
	stats.number_of_passwords = 0.0;
	stats.total_number_of_characters = 0.0;

	return stats;
}

/**
 * @param stats structure where the stats are to be loaded
 * @param password
 * @return loaded stats about a password
 */
Stats load_stats(Stats stats, char *password)
{
	// find unique characters
	int password_length = string_length(password);
	for (int i = 0; i < password_length; i++){
        char c = password[i];
        if (find_character_in_array(c, stats.array_of_characters)){
            continue;
        }
        else {
            stats.array_of_characters[stats.nchars] = c;
            stats.nchars++;
        }
    }

	// check for the minimum
	if (password_length < stats.min){
        stats.min = password_length;
    }

	// stats needed for avarage length
	stats.number_of_passwords++;
    stats.total_number_of_characters += password_length;

	return stats;
}

/**
 * load password by characters
 * 
 * @param c first character of the password
 * @param password place where to load password
 * @return pointer to the loaded password
 */
char* get_password(int c, char *password)
{
	password[0] = (char)c;
    int i;
    for (i = 1; c != '\n'; i++){
		if (i > MAX){
			return NULL;
		}
        c = getchar();
        password[i] = (char)c;
	}
	// end string with '\0' and exculde '\n'
	password[i - 1] = '\0';

	return password;
}

/**
 * check whether password contains at least one lower-case and one upper-case letter
 * 
 * @param password string
 * @return TRUE when password passes the condition, otherwise FALSE
 */
int check1(char *password)
{
	int lower_case_letters = 0;
	int upper_case_letters = 0;
	int password_length = string_length(password);

	for (int i = 0; i < password_length; i++){
		if (is_lower(password[i])){
			lower_case_letters = 1;
		}
		else if (is_upper(password[i])){
			upper_case_letters = 1;
		}
		
		// when both conditins are true, value TRUE is returned
		if(lower_case_letters == 1 && upper_case_letters == 1){
			return TRUE;
		}
	}
	
	return FALSE;
}

/**
 * check whether a password contains characters from at least X(=param) number of groups
 * 
 * @param password string
 * @param param specifies number of character groups
 * @return TRUE when password passes the condition, otherwise FALSE
 */
int check2(char *password, long param)
{
	int lower_case_letters = 0;
	int upper_case_letters = 0;
	int numbers = 0;
	int special_characters = 0;
	int password_length = string_length(password);

	// decide in which group a character belongs
	for (int i = 0; i < password_length; i++){
		if (is_lower(password[i])){
			lower_case_letters = 1;
		}
		else if (is_upper(password[i])){
			upper_case_letters = 1;
		}
		else if (password[i] >= '0' && password[i] <= '9'){
			numbers = 1;
		}
		// secial_characters is a default group, when none of the above condition is true
		else {
			special_characters = 1;
		}

		// when param is greater than 4, param is initialized to 4
		if(param > 4){
			param = 4;
		}

		if (lower_case_letters + upper_case_letters + numbers + special_characters == param){
			return TRUE;
		}
	}

	return FALSE;
}

/**
 * check whether a password contains a sequence of the same characters of the length at least X(=param)
 * 
 * @param password string
 * @param param specifies the length of the sequence
 * @return TRUE when password passes the condition, otherwise FALSE
 */
int check3(char *password, long param)
{
	//variable length_of_sequence is inicialized to 1, because it is a different character than before
	int length_of_sequence = 1;
	int password_length = string_length(password);

	// loop for checking a match in characters next to each other
	for (int i = 0; i < (password_length - 1); i++){
		// if characters next to each other are identical, the length of the sequence is increased by one
		if (password[i] == password[i + 1]){
			length_of_sequence++;
		}
		else {
			length_of_sequence = 1;
		}
		
		if (length_of_sequence == param){
			return FALSE;
		}
	}

	return TRUE;
}

/**
 * check whether a password contains indetical substrings of the length at least X(=param)
 * 
 * @param password string
 * @param param specifies lthe ength of the substring
 * @return TRUE when password passes the condition, otherwise FALSE
 */
int check4(char *password, long param)
{
	char substring1[param + 1];
	char substring2[param + 1];
	int password_length = string_length(password);
	
	// variable i represents the beginning from where we start initializing substrings
	for (int i = 0; i < (password_length - param); i++){
		// loop 'for' to initialize the first substring
		int j;
		for (j = 0; j < param; j++){
			substring1[j] = password[j + i];
		}
		substring1[j] = '\0';

		// variable l represents the beginning from where all the other substring are initialized
		for (int l = i; l < (password_length - param); l++){
			// loop 'for' to initialize the second substring
			int k;
			for (k = 0; k < param; k++){
				substring2[k] = password[k + l + 1];
			}
			substring2[k] = '\0';

			if (compare_strings(substring1, substring2)){
				return FALSE;
			}
		}
	}

	return TRUE;
}

/**
 * if a password passes the given conditions, it will be printed
 * 
 * @param password password to be tested
 * @param level level of safety
 * @param param parameter
 */
void password_check(char *password, long level, long param){
	for (int i = 1; i <= level + 1; i++){
		if (i == level + 1){
			printf("%s\n", password);
			break;
		}

		if (i == 1){
			if (check1(password)){
				continue;
			}
			else {
				break;
			}
		}

		else if (i == 2){
			if (check2(password, param)){
				continue;
			}
			else {
				break;
			}
		}

		else if (i == 3){
			if (check3(password, param)){
				continue;
			}
			else {
				break;
			}
		}

		else if (i == 4){
			if (check4(password, param)){
				continue;
			}
			else {
				break;
			}
		}
	}
}

/**
 * print statistics about passwords
 */
void print_stats(Stats stats)
{
	printf("Statistika:\n");
    printf("Ruznych znaku: %d\n", stats.nchars);
    printf("Minimalni delka: %d\n", stats.min);
    printf("Prumerna delka: %0.1f\n", (stats.total_number_of_characters / stats.number_of_passwords));
}

int main(int argc, char *argv[])
{
	if (argc < 3 || argc > 4){
		fprintf(stderr, "ERROR: Zadali ste neplatny pocet argumentov (./pwcheck LEVEL PARAM [--stats])!\n");
		return EXIT_FAILURE;
	}

	char *endptr;
	long level = strtol(argv[1], &endptr, 10);
	if (endptr[0] != '\0'){
		fprintf(stderr, "ERROR: Argument musi byt cele cislo!\n");
		return EXIT_FAILURE;
	}
	long param = strtol(argv[2], &endptr, 10);
	if (endptr[0] != '\0'){
		fprintf(stderr, "ERROR: Argument musi byt cele cislo!\n");
		return EXIT_FAILURE;
	}

	if (level < 1 || level > 4 || param < 1){
		fprintf(stderr, "ERROR: Zadali ste argument mimo rozsahu!\n");
		return EXIT_FAILURE;
	}

	if (argc == 4){
		if(!compare_strings(argv[3], "--stats")){
			fprintf(stderr, "ERROR: Zadali ste neplatny format argumentov (./pwcheck LEVEL PARAM [--stats])!\n");
			return EXIT_FAILURE;
		}
	}

	int c;
	Stats stats;
	stats = intialized_stats(stats);

    // load password
	while ((c = getchar()) != EOF){
		char password[MAX + 1];   
		if(get_password(c, password) == NULL){
			fprintf(stderr, "ERROR: Zadali ste velmi dlhe heslo!\n");
			return EXIT_FAILURE;
		}

		stats = load_stats(stats, password);

		password_check(password, level, param);
	}

	// if argument --stats is included, stats will be printed
	if (argc == 4){
		if(compare_strings(argv[3], "--stats")){
			print_stats(stats);
		}
	}

	return EXIT_SUCCESS;
}
