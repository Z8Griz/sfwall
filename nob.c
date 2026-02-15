#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv)
{
  NOB_GO_REBUILD_URSELF(argc, argv);
  Nob_Cmd cmd = {0};
  nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-o", "sfwall", "sfwall.c");
  if (!nob_cmd_run(&cmd)) return 1;

  nob_cc(&cmd);
  nob_cc_flags(&cmd);
  nob_cc_output(&cmd, "sfwall");
  nob_cc_inputs(&cmd, "sfwall.c");
  return 0;
}
