#ifndef MAIN_H_
#define MAIN_H_

/*
 * Function Declarations for builtin shell commands:
 */
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

/*
 * List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
"cd",
"help",
exit"
};

int (*builtin_func[]) (char **) = {
&lsh_cd,
&lsh_help,
&lsh_exit
};

int lsh_num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}
