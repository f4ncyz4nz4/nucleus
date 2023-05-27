#include "minidump.h"
#include <iostream>
#include "util.h"
#include "log.h"

int parse_directory(MinidumpDir d, Binary *b, FILE *f) {
    char buffer4[4];
    char buffer8[8];
    int n, i;
    long pos;
    uint64_t numberOfMemoryRanges, baseRva, start_virtual_address, size;
    Section *sec;

    if (d.streamType == MinidumpDir::UnusedStream || d.streamType == MinidumpDir::ReservedStream0 ||
        d.streamType == MinidumpDir::ReservedStream1 ||
        d.streamType == MinidumpDir::FunctionTableStream || d.streamType == MinidumpDir::SystemMemoryInfoStream ||
        d.streamType == MinidumpDir::JavaScriptDataStream || d.streamType == MinidumpDir::ProcessVmCountersStream ||
        d.streamType == MinidumpDir::TokenStream)
        return 0;
        //3 17 4 19
    else if (d.streamType == MinidumpDir::ThreadListStream)
        std::cout << "ThreadListStream" << std::endl;
    else if (d.streamType == MinidumpDir::ModuleListStream)
        std::cout << "ModuleListStream" << std::endl;
    else if (d.streamType == MinidumpDir::MemoryListStream)
        std::cout << "MemoryListStream" << std::endl;
    else if (d.streamType == MinidumpDir::SystemInfoStream)
        std::cout << "SystemInfoStream" << std::endl;
    else if (d.streamType == MinidumpDir::ThreadExListStream)
        std::cout << "ThreadExListStream" << std::endl;
    else if (d.streamType == MinidumpDir::Memory64ListStream) {
        std::fseek(f, d.rva, SEEK_SET);
        std::fread(buffer8, sizeof(char), 8, f);
        numberOfMemoryRanges = charBufferToInt(buffer8, 8);
        std::fread(buffer8, sizeof(char), 8, f);
        // start_file_address
        baseRva = charBufferToInt(buffer8, 8);

        for (int j = 0; j < numberOfMemoryRanges && j < 15; j++) {
            std::fread(buffer8, sizeof(char), 8, f);
            // start_virtual_address
            start_virtual_address = charBufferToInt(buffer8, 8);
            std::fread(buffer8, sizeof(char), 8, f);
            //size
            size = charBufferToInt(buffer8, 8);
            //if (j == 14) {
            b->sections.push_back(Section());
            sec = &b->sections.back();
            sec->size = size;
            sec->binary = b;
            sec->name = std::string("dmp" + std::to_string(j));
            sec->type = Section::SEC_TYPE_CODE;
            sec->bytes = (uint8_t *) malloc(sec->size);
            pos = ftell(f);
            fseek(f, baseRva, SEEK_SET);
            if (fread(sec->bytes, 1, sec->size, f) != (size_t) sec->size) {
                print_err("failed to read binary '%s'", b->filename.c_str());
                return -1;
            }
            fseek(f, pos, SEEK_SET);
            sec->vma = start_virtual_address;
            //}
            baseRva += size;
        }
    } else if (d.streamType == MinidumpDir::CommentStreamA)
        std::cout << "CommentStreamA" << std::endl;
    else if (d.streamType == MinidumpDir::ThreadInfoListStream)
        std::cout << "ThreadInfoListStream" << std::endl;
    return 0;
}
