#ifndef SEARCHEXEC_H
#define SEARCHEXEC_H

int is_executable(const char *path);
const char *find_executable(const char *repoDir, const char *repoUrl);

#endif 