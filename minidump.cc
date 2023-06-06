#include "minidump.h"
#include <iostream>
#include "util.h"
#include "log.h"

int parse_directories(std::vector<MinidumpDir> dirs, Binary *b, FILE *f) {
    char buffer4[4];
    char buffer8[8];
    // for modules
    uint64_t base_address = 0, size_module = 0;
    // for mem segments
    long pos;
    uint64_t numberOfMemoryRanges, baseRva, start_virtual_address, size;
    Section *sec;

    for (MinidumpDir d: dirs) {
        if (d.streamType == MinidumpDir::UnusedStream || d.streamType == MinidumpDir::ReservedStream0 ||
            d.streamType == MinidumpDir::ReservedStream1 ||
            d.streamType == MinidumpDir::FunctionTableStream || d.streamType == MinidumpDir::SystemMemoryInfoStream ||
            d.streamType == MinidumpDir::JavaScriptDataStream || d.streamType == MinidumpDir::ProcessVmCountersStream ||
            d.streamType == MinidumpDir::TokenStream) { continue; }
        else if (d.streamType == MinidumpDir::ThreadListStream) {
            verbose(1, "ThreadListStream");
            /* XXX: todo */
        } else if (d.streamType == MinidumpDir::ModuleListStream) {
            int numberOfModules;

            std::fseek(f, d.rva, SEEK_SET);
            std::fread(buffer4, sizeof(char), 4, f);
            numberOfModules = (int) charBufferToInt(buffer4, 4);

            std::fread(buffer8, sizeof(char), 8, f);
            // base_address
            base_address = charBufferToInt(buffer8, 8);
            std::fread(buffer4, sizeof(char), 4, f);
            //size
            size_module = charBufferToInt(buffer4, 4);
        } else if (d.streamType == MinidumpDir::MemoryListStream)
            verbose(1, "MemoryListStream");
        else if (d.streamType == MinidumpDir::SystemInfoStream)
            verbose(1, "SystemInfoStream");
        else if (d.streamType == MinidumpDir::ThreadExListStream)
            verbose(1, "ThreadExListStream");
        else if (d.streamType == MinidumpDir::Memory64ListStream) {
            std::fseek(f, d.rva, SEEK_SET);
            std::fread(buffer8, sizeof(char), 8, f);
            numberOfMemoryRanges = charBufferToInt(buffer8, 8);
            std::fread(buffer8, sizeof(char), 8, f);
            // start_file_address
            baseRva = charBufferToInt(buffer8, 8);

            for (int j = 0; j < numberOfMemoryRanges; j++) {
                std::fread(buffer8, sizeof(char), 8, f);
                // start_virtual_address
                start_virtual_address = charBufferToInt(buffer8, 8);
                std::fread(buffer8, sizeof(char), 8, f);
                //size
                size = charBufferToInt(buffer8, 8);
                if (start_virtual_address >= base_address &&
                    start_virtual_address + size <= base_address + size_module) {
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
                }
                baseRva += size;
            }
        } else if (d.streamType == MinidumpDir::CommentStreamA)
            verbose(1, "CommentStreamA");
        else if (d.streamType == MinidumpDir::ThreadInfoListStream)
            verbose(1, "ThreadInfoListStream");
    }
    return 0;
}
