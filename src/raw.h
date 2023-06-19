#ifndef NUCLEUS_RAW_H
#define NUCLEUS_RAW_H

#include "loader.h"
#include "log.h"
#include <iostream>
#include <vector>
#include "options.h"

extern int best_offset;
extern int invalid_count[20];

int raw_auto_detection(Binary *bin, FILE *f, uint64_t fsize);
void get_best_offset();

#endif //NUCLEUS_RAW_H
