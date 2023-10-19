#ifndef SHELL_H
#define SHELL_H

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
#include <stdbool.h>
#include <string.h>


/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\0'

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

/**
 * struct display_info - Structure for storing display-related information.
 * list_length - Calculate the length of a linked list.
 * @t: Pointer to the first node in the list.
 * list_to_str - Convert a linked list of strings to an array of strings.
 * @hd: Pointer to the first node of the linked list.
 * myprint_list - Print all elements in a linked list of list_t.
 * starts_node - Returns a node whose string starts with a given prefix.
 * @node: A pointer to the head of the list.
 * @prefix: The string to match as a prefix.
 * @r: The next character after the prefix to match.
 * get_node - Find the index of a specific node in a list.
 * add_node_list - Add a node to the beginning of the list.
 * @hd: A pointer to the head node pointer.
 * @str: The string field for the new node.
 * @num: The node index used in history.
 * add_last - Appends a new node to the end of the linked list.
 * print_str_list - Print only the "str" elements from a list of type list_t.
 * @a: A pointer to the first node of the linked list.
 * delete_node_index - Remove a node at a specified index.
 * @index: The index of the node to be deleted.
 * free_node - Release memory occupied by all nodes in a linked list.
 * @hd_ptr: Pointer to the address of the head node.
 * main - Entry point of the program.
 * @ac: Argument count.
 * @av: Argument vector.
 * @environ: Environment variables.
 * @history: History of commands.
 * @readfd: File descriptor for reading input.
 * @env_changed: Flag indicating if the environment has changed.
 * ptr_free - frees memory associated with a pointer and sets it to NULL.
 * @p: The address of the pointer to free.
 */

typedef struct display_info
{
	char **argv;
	char *path;
	size_t argc;
	char *file_name;
        int (*builtin_func)(struct display_info *);
	int status;
	int error_num;
	int flag_linecount;
        int histcount;
        char **environ;
        list_t *env;
        list_t *history;
        list_t *alias;
        char **cmd_buf;
        char *arg_buf;
        size_t arg_len;
        char *cmd_path;
        char *cmd_arg;
        int cmd_buf_type;
        char *cmd_ret;
        size_t cmd_ret_len;
        int exit_code;
        char *hist_file;
        char *arg_file;
        int fd;
	char *buf;
	char *prompt;
	char *arg;
	char *delim;
	int line_count;
        int pipe_count;
        int cmd_pipe;
        int is_background;
	int chain_command;
        int flag_exit;
        int exit_buffer;
        int cmd_last_exit;
        pid_t pid;
        int readfd;
	int env_changed;
        int cmd_arg_count;
        int cmd_arg_type;
        struct cmd_arg *arg_list;
        size_t pipe_id;
	list_t *env_list;
        char *cmd_line;
	struct display_info *next;

} display_info;

/**
 * struct list_t - A linked list structure.
 * @str: A string element.
 * @num: An integer element.
 * @next: A pointer to the next node in the list.
 */

typedef struct list_t {
	char *str;
	int num;
	struct list_t *next;
} list_t;

#define INFO_INIT {0, NULL, NULL, NULL, 0, 0}

/* my_atoi */
int interactive_mode(display_info *myinfo);
int is_delim(char a, char *delimiter);
int isalpha(int a);
int my_atoi(char *p);

int my_exit(display_info *myinfo);
int my_cd(display_info *myinfo);
int my_help(display_info *myinfo);

int _history(display_info *myinfo);
int unset_alias(display_info *myinfo, char *str);
int set_alias(display_info *myinfo, char *str);
int myprint_alias(list_t *node);
int _alias(display_info *myinfo);

void _puts(char *str);
int _errputchar(char a);
int _putfd(char a, int fd);
int _putsfd(char *str, int fd);

int errors_atoi(char *a);
void myprint_error(display_info *myinfo, char *errstr);
int print_dec(int value, int fd);
char *num_convert(long int num, int base, int flags);

/*the comments_remover */
void comments_remover(char *buf);

/* environ.c */
int _myenviron(display_info *myinfo);
char *_getenv(display_info *myinfo, const char *var);
int _setenv(display_info *myinfo);
int _unsetenv(display_info *myinfo);
int initialize_env_list(display_info *myinfo);
int _unsetenv(display_info *myinfo, char *var);
int _setenv(display_info *myinfo, char *var, char *data);

/* exits.c */
int _myenviron(display_info *myinfo);
char *_getenv(display_info *myinfo, const char *var);
int _setenv(display_info *myinfo);
int _unsetenv(display_info *myinfo);
int initialize_env_list(display_info *myinfo);

char *copy_str(char *des, char *src, int m);
char *_strncat(char *des, char *src, int m);
char *_strchr(char *s, char b);

/* getenv.c */
int _myenviron(display_info *myinfo);
char *_getenv(display_info *myinfo, const char *var);
int _unsetenv(display_info *myinfo, char *var);
int _setenv(display_info *myinfo, char *var, char *data);

/* getinfo.c */
void initialize_display_info(display_info *myinfo);
void set_display_info(display_info *myinfo, char **av);
void free_display_info(display_info *myinfo, int all);

/* getLine.c */
int input_buffer(display_info *myinfo, char **buf, size_t *len);
ssize_t get_value(display_info *myinfo);
ssize_t read_buf(display_info *myinfo, char *buffer, size_t *i);
int _mygetline(display_info *myinfo, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused)) int signal_num);

/* history.c */
char *get_history(display_info *myinfo);
int write_history(display_info *myinfo);
int read_hist(display_info *myinfo);
int build_hist_list(display_info *myinfo, char *buf, int linecount);
int renum_hist(display_info *myinfo);

/* lists1.c */
size_t list_length(const list_t *t);
char **list_to_str(list_t *hd);
size_t myprint_list(const list_t *t);
list_t *starts_node(list_t *node, char *prefix, char r);
ssize_t get_node(list_t *hd, list_t *node);

/* lists.c */
void free_node(list_t **hd_ptr);
int delete_node_index(list_t **hd, unsigned int index);
size_t print_str_list(const list_t *a);
list_t *add_last(list_t **hd, const char *str, int num);
list_t *add_node_list(list_t **hd, const char *str, int num);

/* main.c */
int main(int ac, char **av);
int my_cmd(display_info *myinfo, const char *command);

/* memory.c */
int ptr_free(void **p);

/* parser.c */
int my_cmd(display_info *myinfo, char *path);
char *dup_chars(char *pathstr, int begin, int halt);
char *find_pathstr(display_info *myinfo, char *pathstr, char *cmd);

/* realloc.c */
char *_mem_set(char *s, char a, unsigned int n);
void free_str(char **yy);
void *mem_realloc(void *ptr, unsigned int size_old, unsigned int size_new);

/* string.c */
int _lenstr(char *p);
int _strcmp(char *p1, char *p2);
char *starts_with(const char *source_string, const char *substring);
char *_strcat(char *dest, char *src);

/* string1.c */
char *_strcpy(char *dest, char *src);
char *_dup_str(const char *s);
void _puts(char *s);
int _putchar(char a);

/* tokenizer.c */
char **str_word(char *str, char *f);
char **str_word2(char *str, char f);

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(display_info *myinfo);
} builtin_table;

/* shell_loop.c */
int hsh(display_info *myinfo, char **av);
oid reset_display_info(display_info *myinfo);
int interactive_mode(display_info *myinfo);
ssize_t get_value(display_info *myinfo);
void set_info(display_info *myinfo, char **av);
int check_builtin(display_info *myinfo);
void write_history(display_info *myinfo);
void free_display_info(display_info *myinfo, int mode);
void find_com(display_info *myinfo);
int is_delim(char c, const char *delimiters);
char *find_path(display_info *myinfo, int dog, const char *command);
int my_cmd(display_info *myinfo, const char *command);
void cmd_fork(display_info *myinfo);
void myprint_error(display_info *myinfo, const char *message);

/* vars.c */
int is_chain(display_info *myinfo, char *buf, size_t *c);
void chain_check(display_info *myinfo, char *buf, size_t *c, size_t j, size_t length);
int rep_alias(display_info *myinfo);
int rep_vars(display_info *myinfo);
int replace_string(char **oldstr, char *newstr);

#endif
