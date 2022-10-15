#include "tests.h"

int main()
{
    test_run_all();
}

void test_run_all()
{
    test_split_good_string1();
    test_split_good_string2();

    test_split_string_with_spaces1();
    test_split_string_with_spaces2();

    test_split_string_with_other_symbols1();
    test_split_string_with_other_symbols2();
    test_split_string_with_other_symbols3();

    test_split_empty_string1();
    test_split_empty_string2();

    printf("%s\n", "=======================================");

    test_search_success1();
    test_search_success2();
    test_search_success3();
    test_search_success4();

    test_search_bad1();

    test_search_error1();
    test_search_error2();
    test_search_error3();

    printf("%s\n", "=======================================");

    test_remove_spaces1();
    test_remove_spaces2();

    test_remove_spaces_empty_str1();
    test_remove_spaces_empty_str2();
}

void test_split_good_string1()
{
    char line[] = "Hello, World !";
    char *argv[4];
    shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, 4);

    assert(strcmp(argv[0], "Hello,") == 0);
    assert(strcmp(argv[1], "World") == 0);
    assert(strcmp(argv[2], "!") == 0);
    assert(argv[3] == NULL);

    printf("Test %s is done\n", "test_split_good_string1");
}

void test_split_good_string2()
{
    char line[] = "ls -la .";
    char *argv[4];
    shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, 4);

    assert(strcmp(argv[0], "ls") == 0);
    assert(strcmp(argv[1], "-la") == 0);
    assert(strcmp(argv[2], ".") == 0);
    assert(argv[3] == NULL);

    printf("Test %s is done\n", "test_split_good_string2");
}

void test_split_string_with_spaces1()
{
    char line[] = "   ls -la .   ";
    char *argv[4];
    shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, 4);

    assert(strcmp(argv[0], "ls") == 0);
    assert(strcmp(argv[1], "-la") == 0);
    assert(strcmp(argv[2], ".") == 0);
    assert(argv[3] == NULL);

    printf("Test %s is done\n", "test_split_string_with_spaces1");
}

void test_split_string_with_spaces2()
{
    char line[] = "   ls -l      -a .   ";
    char *argv[5];
    shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, 5);

    assert(strcmp(argv[0], "ls") == 0);
    assert(strcmp(argv[1], "-l") == 0);
    assert(strcmp(argv[2], "-a") == 0);
    assert(strcmp(argv[3], ".") == 0);
    assert(argv[4] == NULL);

    printf("Test %s is done\n", "test_split_string_with_spaces2");
}

void test_split_string_with_other_symbols1()
{
    char line[] = "ls \r -l  \n    -a .   ";
    char *argv[5];
    shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, 5);

    assert(strcmp(argv[0], "ls") == 0);
    assert(strcmp(argv[1], "-l") == 0);
    assert(strcmp(argv[2], "-a") == 0);
    assert(strcmp(argv[3], ".") == 0);
    assert(argv[4] == NULL);

    printf("Test %s is done\n", "test_split_string_with_other_symbols1");
}

void test_split_string_with_other_symbols2()
{
    char line[] = "ls \r -l  \n\n \n    -a . \a\a  ";
    char *argv[5];
    shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, 5);

    assert(strcmp(argv[0], "ls") == 0);
    assert(strcmp(argv[1], "-l") == 0);
    assert(strcmp(argv[2], "-a") == 0);
    assert(strcmp(argv[3], ".") == 0);
    assert(argv[4] == NULL);

    printf("Test %s is done\n", "test_split_string_with_other_symbols2");
}

void test_split_string_with_other_symbols3()
{
    char line[] = "\n\n\n";
    char *argv[4] = {NULL};
    shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, 4);

    assert(argv[0] == NULL);
    assert(argv[1] == NULL);
    assert(argv[2] == NULL);
    assert(argv[3] == NULL);

    printf("Test %s is done\n", "test_split_string_with_other_symbols3");
}

void test_split_empty_string1()
{
    char line[] = "";
    char *argv[4] = {NULL};
    shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, 4);

    assert(argv[0] == NULL);
    assert(argv[1] == NULL);
    assert(argv[2] == NULL);
    assert(argv[3] == NULL);

    printf("Test %s is done\n", "test_split_empty_string1");
}

void test_split_empty_string2()
{
    char line[] = "    ";
    char *argv[4] = {NULL};
    shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, 4);

    assert(argv[0] == NULL);
    assert(argv[1] == NULL);
    assert(argv[2] == NULL);
    assert(argv[3] == NULL);

    printf("Test %s is done\n", "test_split_empty_string2");
}

void test_search_success1()
{
    char str1[] = "ls";
    char str2[] = "-la";
    char str3[] = "-la";
    char str4[] = ">";
    char str5[] = "my_file.txt";

    char symbol[] = ">";

    char *char_pointer_array[] = {str1, str2, str3, str4, str5, NULL};

    assert(shell_find_symbol(char_pointer_array, symbol) == 3);

    printf("Test %s is done\n", "test_search_success1");
}

void test_search_success2()
{
    char str1[] = "ls";
    char str2[] = "-la";
    char str4[] = ">>";
    char str5[] = "my_file.txt";

    char symbol[] = ">>";

    char *char_pointer_array[] = {str1, str2, str4, str5, NULL};

    assert(shell_find_symbol(char_pointer_array, symbol) == 2);

    printf("Test %s is done\n", "test_search_success2");
}

void test_search_success3()
{
    char str1[] = "ls";
    char str2[] = "-la";
    char str4[] = ">>";
    char str5[] = "my_file.txt";

    char symbol[] = "ls";

    char *char_pointer_array[] = {str1, str2, str4, str5, NULL};

    assert(shell_find_symbol(char_pointer_array, symbol) == 0);

    printf("Test %s is done\n", "test_search_success3");
}

void test_search_success4()
{
    char str1[] = "ls";
    char str2[] = "-la";
    char str4[] = ">>";
    char str5[] = "my_file.txt";

    char symbol[] = "my_file.txt";

    char *char_pointer_array[] = {str1, str2, str4, str5, NULL};

    assert(shell_find_symbol(char_pointer_array, symbol) == 3);

    printf("Test %s is done\n", "test_search_success4");
}

void test_search_bad1()
{
    char str1[] = "ls";
    char str2[] = "-la";
    char str4[] = ">>";
    char str5[] = "my_file.txt";

    char symbol[] = "|";

    char *char_pointer_array[] = {str1, str2, str4, str5, NULL};

    assert(shell_find_symbol(char_pointer_array, symbol) == -1);

    printf("Test %s is done\n", "test_search_bad1");
}

void test_search_error1()
{
    char symbol[] = "|";
    assert(shell_find_symbol(NULL, symbol) == -1);

    printf("Test %s is done\n", "test_search_error1");
}

void test_search_error2()
{
    char str1[] = "ls";
    char str2[] = "-la";
    char str4[] = ">>";
    char str5[] = "my_file.txt";
    char *char_pointer_array[] = {str1, str2, str4, str5, NULL};

    assert(shell_find_symbol(char_pointer_array, NULL) == -1);

    printf("Test %s is done\n", "test_search_error2");
}

void test_search_error3()
{
    assert(shell_find_symbol(NULL, NULL) == -1);

    printf("Test %s is done\n", "test_search_error3");
}

void test_remove_spaces1()
{
    char str[] = "ls  -l     -a .   ";

    shell_remove_spaces(str);

    assert(strcmp(str, "ls-l-a.") == 0);

    printf("Test %s is done\n", "test_remove_spaces1");
}

void test_remove_spaces2()
{
    char str[] = "     ls  -l     -a .   ";

    shell_remove_spaces(str);

    assert(strcmp(str, "ls-l-a.") == 0);

    printf("Test_remove_spaces2\n");
}

void test_remove_spaces_empty_str1()
{
    char str[] = "";
    shell_remove_spaces(str);

    assert(strcmp(str, "") == 0);

    printf("Test %s is done\n", "test_remove_spaces_empty_str1");
}

void test_remove_spaces_empty_str2()
{
    char *str = NULL;
    shell_remove_spaces(str);

    assert(str == NULL);

    printf("Test %s is done\n", "Test_remove_spaces_empty_str2\n");
}
