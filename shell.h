#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <dirent.h>
/*my macros*/
#define INTERACTIVE 1
#define NON_INTERACTIVE_FILE 0
#define NON_INTERACTIVE_PIPED 2
#define ERROR -1
/*Error status macros*/
#define NOT_FOUND 127
#define PERMISSION_DENIED 126
#define EXIT_ERROR 2
#define TOK_D " \t\r\n\a\""
extern char **environ;
/**
 * struct list_pa - singly linked list
 * @path: string
 * @lenn: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_pa
{
	char *path;
	unsigned int lenn;
	struct list_pa *next;
} list_pa;
int _strlllp(char *s1, char *s2);
char *_gellnv(char *name);
void frrr_li(list_pa *head);
int _srren(char *s);
ssize_t _getlineHelper(char **lineptr, size_t *n,
		__attribute__((unused)) FILE * stream);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_stvvvp(char *str);
char *_styyat(char *dest, char *src);
char *_steeey(char *dest, char *src);
list_pa *add_ne(list_pa **head, char *path);
list_pa *set_al_pls_to_li();
list_pa *sxt_al_vor_o_lz();
char **geat_av_wooh_fl(char *line, int status);
unsigned int char_cnt(char *str, char c);
/*==========================================================================*/
void free_all(char **lines, int counter, list_pa *env,
				list_pa *current, char *line, char **line_vector);
int _varllp(char *var_name, char *full_var);
void __ittenv(char *name, char *value, list_pa *env_list);
list_pa *get_saaaaaa(char *name, list_pa *head);
size_t print_aalu(const list_pa *p);
void sat_luat_eav(list_pa *p);
size_t evv_lsat_lan(const list_pa *p);
int _cd(char *line_vector[], char **argv);
unsigned int _craak(char c, const char *str);
char *_saak(char *str, const char *delim);
unsigned int cher_cot_pid(char *str, char c);
void prllt_calt_o(char *program_name, int counter, char *file_name);
void is_nat_bqt_i(char **line_vector, char *env[], int *status,
						int counter, list_pa *current, char *argv[]);
char **raxt_to_v(char *text);
char **fie_non_itevw(char *file_name, char *program_name);
char **pipwd_non_inteaave();
char **gat_collands(int mode, char *file_name, char *program_name);
void free_e_v(char *line, char **line_vector);
int is_dar(char *line, char **argv, int counter,
			char **line_vector, int *status, char *old_line);
int _aorr(char *s);
void is_etyy(char *line, char **line_vector, list_pa *current,
		char *program_name, int counter, int *status, list_pa *env, char **lines);
void priwt_ewwr(char *program_name, int counter,
		char *command, int type_of_error);
void handle_comments(char *input);
/*==*/
void handle_semicolons(char *line);
void execute_command_with_waitpid(char *path, char **av, char **env);
/*====*/
char *nu_to_ch(int nom);
char *crrok_arr(char *line_av_1, list_pa *current);
void execute_command(char *path, char **av, char **env, int *status);
void print_eve(int *status);
char *get_pro_io();
char *get_sta(int n);
int is_baalt_ia(char *line, char **line_vector, list_pa *current,
		char *program_name,
		int counter, int *status, list_pa *env, char **lines, char **argv);
void priwt_ewwr(char *program_name, int counter,
		char *command, int type_of_error);
char *get_cod_fewm_fiaa(char *file);
char *get_cod_fr_ur(list_pa *current);
int chddk_mllo(int argc);
void free_vector(char **v);
#endif
