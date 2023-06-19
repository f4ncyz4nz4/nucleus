#include "raw.h"

int N_offset = 20;
int invalid_count[20];
int best_offset = 0;

int raw_auto_detection(Binary *bin, FILE *f, uint64_t fsize) {
    Section *sec;
    int i;

    for (i = 0; i < N_offset; i++) {
        invalid_count[i] = 0;
    }

    for (i = 0; i < N_offset; i++) {
        bin->sections.push_back(Section());
        sec = &bin->sections.back();

        sec->vma = options.binary.base_vma;
        sec->vma += i;
        sec->binary = bin;
        sec->name = (i < 10 ? "0" : "") + std::to_string(i);
        sec->name = "raw" + sec->name;
        sec->type = Section::SEC_TYPE_CODE;

        sec->size = (uint64_t) fsize - sec->vma;
        sec->bytes = (uint8_t *) malloc(sec->size);
        if (!sec->bytes) {
            print_err("out of memory");
            return -1;
        }

        fseek(f, sec->vma, SEEK_SET);
        if (fread(sec->bytes, 1, sec->size, f) != (size_t) sec->size) {
            return -1;
        }
    }
    return 0;
}

void get_best_offset() {
    for (int i = 0; i < N_offset; i++) {
        if (invalid_count[i] < invalid_count[best_offset]) {
            best_offset = i;
        }
    }
    verbose(1, "Best offset= 0x%x", best_offset);
}