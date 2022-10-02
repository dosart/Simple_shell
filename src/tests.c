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
    char *argv[4];
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
    char *argv[4];
    shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, 4);

    assert(argv[0] == NULL);
    assert(argv[1] == NULL);
    assert(argv[2] == NULL);
    assert(argv[3] == NULL);

    printf("Test %s is done\n", "test_split_empty_string2");
}
