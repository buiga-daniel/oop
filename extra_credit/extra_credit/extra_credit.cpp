#include <stdio.h>
#include <string.h>

struct letter_to_freq {
    char letter;
    double freq;
    double expected_nr;
    double expected_eng;
    double chi_sums;
};

void frequency(char* s, int* freq) 
{
    int i = 0;
    while (s[i] != '\0') 
    {
        if (s[i] >= 'a' && s[i] <= 'z')
            freq[s[i] - 'a']++;
        else if (s[i] >= 'A' && s[i] <= 'Z')
            freq[s[i] - 'A']++;
        i++;
    }
}

void normalized(char* s, int* freq, struct letter_to_freq* normalized_freq) 
{
    int i = 0;
    int leng=0;
    while (s[i] != '\0')
    {
        if ((s[i] >= 'a' && s[i] <= 'z' )||(s[i] >= 'A' && s[i] <= 'Z'))
            leng++;
        i++;
    }
    double norm;
    for (int i = 0; i < 26; i++) 
    {
        norm = (double)freq[i] / leng * 1.0;
        normalized_freq[i].letter = (char)i + 'a';
        normalized_freq[i].freq = norm;
    }
}



void chi_square(struct letter_to_freq* normalized_freq, int* freq, char* s,int index)
{
    int i = 0;
    int leng = 0;
    double result_formula;
    double chi_square_sum = 0;
    while (s[i] != '\0')
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            leng++;
        i++;
    }
    for (int i = 0; i < 26; i++)
    {
        normalized_freq[i].expected_nr = leng * normalized_freq[i].expected_eng;
        result_formula = (normalized_freq[i].expected_nr - freq[i]) * (normalized_freq[i].expected_nr - freq[i]) / normalized_freq[i].expected_nr;
        chi_square_sum += result_formula;
    }
    normalized_freq[index].chi_sums = chi_square_sum;
}

void encrypt(char s[], int n)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (n < 0)
            n = 26 + (n % 26);
        if (s[i] <= 'z' && s[i] >= 'a')
        {
            char c = 'a' + (s[i] - 'a' + n) % 26;
            s[i] = c;
        }
        if (s[i] <= 'Z' && s[i] >= 'A')
        {
            char c = 'A' + (s[i] - 'A' + n) % 26;
            s[i] = c;
        }
    }
}

int least_chi_sum(struct letter_to_freq* normalized_freq,int* freq, char* s)
{
    int min_index = 0;
    char s_copy[300];
    for (int i = 0; i < 26; i++)
    {
        int freq[26] = { 0 };
        strcpy_s(s_copy, s);
        encrypt(s_copy, i);
        frequency(s_copy, freq);
        chi_square(normalized_freq, freq, s_copy, i);
    }
    for (int i = 1; i < 26; i++)
    {
        if (normalized_freq[i].chi_sums < normalized_freq[min_index].chi_sums)
            min_index = i;
        ///printf("%f \n", normalized_freq[i].chi_sums);
    }
    ////printf("\n %f", normalized_freq[min_index].chi_sums);

    return min_index;
}

int reading(struct letter_to_freq* normalized_freq)
{
    FILE* fp;
    errno_t err;

    err = fopen_s(&fp, "distribution.txt", "r");
    if (err != 0) {
        printf("Error while opening the file.\n");
        return 1;
    }
    int i = 0;
    float distr;
    //fscanf(fp, "%1d", &normalized_freq[i].expected_eng);
    for(int i=0;i<26;i++)
    {
        fscanf_s(fp, "%f", &distr);
        ///printf("%.3f \n", distr);
        normalized_freq[i].expected_eng = distr;
    }
}

int main() {
    
    printf("         --------------------\n");
    printf("        | FREQUENCY ANALYSIS |\n");
    printf("         --------------------\n");
    printf("     Commands:\n");
    printf("     [ 1 ] to read the string that needs to be deciphered \n");
    printf("     [ 2 ] to see the explanation of frequency analisys \n");
    printf("     [ 3 ] to exit \n");

    char s[300];
    int freq[26] = {0};
    int option;
    int minimal;
    do {
        scanf_s("%d", &option);
        switch (option) {
        case 1:
            struct letter_to_freq normalized_freq[26];
            fgets(s, 300, stdin);
            frequency(s, freq);
            normalized(s, freq, normalized_freq);
            reading(normalized_freq);
            minimal = least_chi_sum(normalized_freq, freq, s);
            char solution[300];
            encrypt(s, minimal);
            strcpy_s(solution, s);
            printf("%s\n", solution);
            break;

        case 2:
            printf("We used frequency analysis to break Caesar’s cipher.");
            printf("This is a brute force method that tests all the possible displacements");
            printf("and returns the most likely decryption of a text.");
            printf("Frequency analysis relies on the fact that some letters(or combination of letters ");
            printf("occur more in a language, regardless of the text size.For example, ");
            printf("in English the letters E, A are the most frequent, while the Z and Q are the least frequent\n");
            break;

        case 3:
            printf("\nExiting program...\n");
            break;
        default:
            printf("\nInvalid option. Please try again.\n");
            break;
        }
    } while (option != 3 && option != 3);

    ///for(int i=0;i<26 ;i++)
    //{
        ///printf("%f \n", normalized_freq[i].expected_eng);
    ///}
     
    ///for (int i = 0; i < 26; i++) {
        //printf("%c = %f appears %d times \n", normalized_freq[i].letter, normalized_freq[i].freq, freq[i]);
    ///}
    ///printf("\n");
    
    ///for (int i = 0; i < 26; i++)
        ///printf("\n%d = %f", i, normalized_freq[i].chi_sums);
    
    

    return 0;
}