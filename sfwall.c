/* sfall v0.1 -- public domain -- Z8Griz 2026
 * wallpaper manager that is portable for linux and bsd systems
 * This program does not pull images from sites. That's your job.
*/ 

#include <stdio.h>
#include <time.h>
#include <string.h>
#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

// WF = Wallpaper Folder. Prefix for reasons
// change user to your account username 
#define WF_FOLDER "/home/user/Pictures/Wallpaper/" 
#define WF_SEASONS "Seasons/"
#define WF_AUTUMN "Autumn/"
#define WF_WINTER "Winter/"
#define WF_SPRING "Spring/"
#define WF_SUMMER "Summer/"
#define WF_MINIM  "Minimalism/"

#define FEHR "feh", "--bg-scale", "--recursive", "--randomize"

int help(void) {
  printf("-----------------------------\n");
  printf(" Simple (feh) Wallpaper Manager  \n");
  printf("-----------------------------\n");
  printf("There are three call options:\n");
  printf("'-s' calls seasons. It checks current season and sets random wallpaper based on that\n");
  printf("'-m' calls minimalism wallpaper and sets it randomly\n");
  printf("'-r' calls recursive in all wallpaper folder and sets it randomly\n");
  printf("If you do want wallpaper changes every __ minutes/hours/days then use cronjob.\n");
  return 0;
}

/*
The risk is heightened when the system() command is specified without a full path, allowing an attacker to manipulate the PATH environment variable to execute a malicious binary with the same name as the intended command.

Instead, secure alternatives like execve(), execl(), or execvp() are advised, as they do not invoke a shell and thus eliminate the risk of command injection. cmd_run() by nob.h is experimental. It creates a new buffer, cleans up, then shutdown. Similar to pipes().  
*/


Cmd cmd = {0};

// Create folders path   
static int join_path(char *dst, size_t dstlen, const char *a, const char *b) {
  size_t la = strlen(a), lb = strlen(b);
  if (la + lb + 1 >= dstlen) return 0;
  memcpy(dst, a, la);
  memcpy(dst + la, b, lb);
  dst[la + lb] = '\0';
  return 1;
}

int create_folders(void) {
  // TODO: remove hard limit, and rely on pathconf() for extra portability. Requires refactor.
  //if your bsd system flooded, then reduce the number to 1024.
  char path[4096];
  //const char *seasons[] = { WF_WINTER, WF_SPRING, WF_SUMMER, WF_AUTUMN };
  
  if (!mkdir_if_not_exists(WF_FOLDER)) return 1;
  
  //TODO refactor this nasty slop
  if (!join_path(path, sizeof path, WF_FOLDER, WF_SEASONS)) return 1;
  if (!mkdir_if_not_exists(path)) return 1;
  
  if (!join_path(path, sizeof path, WF_FOLDER WF_SEASONS, WF_AUTUMN)) return 1;
  if (!mkdir_if_not_exists(path)) return 1;
  
  if (!join_path(path, sizeof path, WF_FOLDER WF_SEASONS, WF_WINTER)) return 1;
  if (!mkdir_if_not_exists(path)) return 1;
  
  if (!join_path(path, sizeof path, WF_FOLDER WF_SEASONS, WF_SPRING)) return 1;
  if (!mkdir_if_not_exists(path)) return 1;
  
  if (!join_path(path, sizeof path, WF_FOLDER WF_SEASONS, WF_SUMMER)) return 1;
  if (!mkdir_if_not_exists(path)) return 1;
  
  if (!join_path(path, sizeof path, WF_FOLDER, WF_MINIM)) return 1;
  if (!mkdir_if_not_exists(path)) return 1;
  
  puts("folders created (or already exist)");
  return 0;
}

// check directory exist helper
static int dir_exists(const char *path) {
  struct stat st;
  return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

int randomizer(void) {
  cmd_append(&cmd, FEHR, WF_FOLDER);
  if (!cmd_run(&cmd)) return 1;
  return 0;
}

int minimalism(void) {
  cmd_append(&cmd, FEHR, WF_FOLDER WF_MINIM);
  printf("Set Minimalism wallpaper\n");
  if (!cmd_run(&cmd)) return 1;
  return 0; 
}

int seasons(void) {
  time_t now;
  struct tm *current;
  int month, day;
  char *season;

  time(&now);
  current = localtime(&now);
  month = current->tm_mon + 1;  // tm_mon is 0-based (0 = Jan)
  day = current->tm_mday;       // tm_mday is day of the months

  switch (month) {
    case 1:
    case 2:
      season = "Winter";
      cmd_append(&cmd, FEHR, WF_FOLDER WF_SEASONS WF_WINTER);
      if (!cmd_run(&cmd)) return 1;
      break;
    case 3:
      season = (day < 21) ? "Winter" : "Spring";
      if (day < 21) {
        cmd_append(&cmd, FEHR, WF_FOLDER WF_SEASONS WF_WINTER);
        if (!cmd_run(&cmd)) return 1;
      }
      else {
        cmd_append(&cmd, FEHR, WF_FOLDER WF_SEASONS WF_SPRING);
        if (!cmd_run(&cmd)) return 1;
      }
      break;
    case 4:
    case 5:
      season = "Spring";
      break;
    case 6:
      season = (day < 21) ? "Spring" : "Summer";
      if (day < 21) {
        cmd_append(&cmd, FEHR, WF_FOLDER WF_SEASONS WF_SPRING);
        if (!cmd_run(&cmd)) return 1;
      }
      else {
        cmd_append(&cmd, FEHR, WF_FOLDER WF_SEASONS WF_SUMMER);
        if (!cmd_run(&cmd)) return 1;
      }
      break;
    case 7:
    case 8:
      season = "Summer";
      cmd_append(&cmd, FEHR, WF_FOLDER WF_SEASONS WF_SUMMER);
      break;
    case 9:
      season = (day < 21) ? "Summer" : "Autumn";
      if (day < 21) {
        cmd_append(&cmd, FEHR, WF_FOLDER WF_SEASONS WF_SUMMER);
        if (!cmd_run(&cmd)) return 1;
      }
      else {
        cmd_append(&cmd, FEHR, WF_FOLDER WF_SEASONS WF_AUTUMN);
        if (!cmd_run(&cmd)) return 1;
      }
      break;
    case 10:
    case 11:
      season = "Autumn";
      cmd_append(&cmd, FEHR, WF_FOLDER WF_SEASONS WF_AUTUMN);
      if (!cmd_run(&cmd)) return 1;
      break;
    case 12: // I initially had a compare date here but dec is winter. It's forced. 
      season = "Winter";
      cmd_append(&cmd, FEHR, WF_FOLDER WF_SEASONS WF_WINTER);
      if (!cmd_run(&cmd)) return 1;
      break;
    default:
      printf("There is no greater than 12 months of the year. Goofball.\n");
      return 1;
  }

  printf("Today's date: %d/%d\n", month, day);
  printf("The season is %s\n", season);
  printf("Set background picture according to current season\n");
  return 0;

}

int main(int argc, char *argv[]) {
  int opt;
  int opt_tf = 0; // track option flag
  const char *base = WF_FOLDER;

  if (!dir_exists(base)) {
    create_folders();
    if (!dir_exists(base)) {
        perror("failed to create folders");
        return 1;
    }
  }

  while ((opt = getopt(argc, argv, "hsmr")) != -1) { 
   opt_tf = 1;
   switch (opt) {
     case 'h':
       help();
       break;
     case 's':
       seasons();
       break;
     case 'm':
       minimalism();
       break;
     case 'r':
       randomizer();
       break;
     default:
       printf("flag command not found.\n");
       return 1;
    }
  }

  if (!opt_tf && optind >= argc) {
    fprintf(stderr, "Error: Missing required arguments.\n");
    return 1;
  }
  
  return 0;
}
