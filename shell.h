#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for num_convert() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_MYGETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

	 extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct displayinfo - A container for pseudo-arguments
* used to pass data into a function,
* providing a consistent prototype for function pointer structs

 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @error_num: the exit()s error code
 * @flag_linecount: if on count this line of input
 * @file_name: the program filename
 * @myenv: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buffer: address of pointer to cmd_buffer, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd in which line input read
 * @histcount: the history line number count
 */
typedef struct displayinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	Int error_num int flag_linecount;
	char *file_name;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;	/* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} display_info;

#define INFO_INIT                                                             \
	{                                                                          \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			 0, 0, 0                                                             \
	}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(display_info *);
} builtin_table;

int interactive_mode(display_info *);
int is_delim(char, char *);
int isalpha(int);
int my_atoi(char *);

int errors_atoi(char *);
void _puts(char *);
int _errputchar(char);
void myprint_error(display_info *, char *);

int _history(display_info *);
int _alias(display_info *);
int myprint_alias(list_t *)

	 void _puts(char *);
int _putchar(char);
int _putfd(char a, int fd);
int _putsfd(char *str, int fd);

int errors_atoi(char *);
void myprint_error(display_info *, char *);
int print_dec(int, int);
char *num_convert(long int, int, int);
void comments_remover(char *);

char *_getenv(display_info *, const char *);
int _myenv(display_info *);
int _setenv(display_info *);
int _unsetenv(display_info *);
int initialize_env_list(display_info *);

char *copy_str(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **get_env_str(display_info *);
int _unsetenv(display_info *, char *);
int _setenv(display_info *, char *, char *);

ssize_t get_value(display_info *);
ssize_t input_buffer(display_info *);
int _mygetline(display_info *, char **, size_t *);
void sigintHandler(int);

void reset_display_info(display_info *);
void set_info(display_info *, char **);
void free_display_info(display_info *, int);

char *get_history(display_info *info);
int write_history(display_info *info);
int read_hist(display_info *info);
int build_hist_list(display_info *info, char *buf, int linecount);
int renum_hist(display_info *info);

list_t *add_node_list(list_t **, const char *, int);
list_t *add_last(list_t **, const char *, int);
size_t print_str_list(const list_t *);
int delete_node_index(list_t **, unsigned int);
void free_node(list_t **);

size_t list_len(const list_t *);
char **list_to_str(list_t *);
size_t myprint_list(const list_t *);
list_t *starts_node(list_t *, char *, char);
ssize_t get_node(list_t *, list_t *);

int ptr_free(void **);

int _lenstr(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_dup_str(const char *);
void _puts(char *);
int _putchar(char);

int hsh(display_info *, char **);
int check_builtin(display_info *);
void find_com(display_info *);
void cmd_fork(display_info *);

char *_mem_set(char *, char, unsigned int);
void free_str(char **);
void *mem_realloc(void *, unsigned int, unsigned int);

int my_cmd(display_info *, char *);
char *dup_chars(char *, int, int);
char *find_pathstr(display_info *, char *, char *)

	 int loophsh(char **);

char **str_word(char *, char *);
char **str_word1(char *, char);

int is_chain(display_info *, char *, size_t *);
void check_chain(display_info *, char *, size_t *, size_t, size_t);
int rep_alias(display_info *);
int rep_vars(display_info *);
int replace_string(char **, char *);

#endif
