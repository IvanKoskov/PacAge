#ifndef SEARCHEXEC_H
#define SEARCHEXEC_H

int is_executable(const char *path);
const char *find_executable(const char *repoDir);
void move_executable_to_bin(const char *exec_path);
#endif 