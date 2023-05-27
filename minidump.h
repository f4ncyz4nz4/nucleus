#ifndef NUCLEUS_MINIDUMP_H
#define NUCLEUS_MINIDUMP_H

#include <string>
#include <vector>
#include "loader.h"

class Minidump;

class MinidumpDir;

class Minidump {
public:
    Minidump() : version(0), implementationVersion(0), numberOfStreams(0), streamDirectoryRva(0), dirs() {}

    std::string signature;
    int version;
    int implementationVersion;
    int numberOfStreams;
    int streamDirectoryRva;
    std::vector<MinidumpDir> dirs;
};

class MinidumpDir {
public:
    enum MinidumpStreamType {
        UnusedStream = 0,
        ReservedStream0 = 1,
        ReservedStream1 = 2,
        ThreadListStream = 3,
        ModuleListStream = 4,
        MemoryListStream = 5,
        ExceptionStream = 6,
        SystemInfoStream = 7,
        ThreadExListStream = 8,
        Memory64ListStream = 9,
        CommentStreamA = 10,
        CommentStreamW = 11,
        HandleDataStream = 12,
        FunctionTableStream = 13,
        UnloadedModuleListStream = 14,
        MiscInfoStream = 15,
        MemoryInfoListStream = 16,
        ThreadInfoListStream = 17,
        HandleOperationListStream = 18,
        TokenStream = 19,
        JavaScriptDataStream = 20,
        SystemMemoryInfoStream = 21,
        ProcessVmCountersStream = 22,
        ThreadNamesStream = 24
    };

    MinidumpDir() : streamType(0), dataSize(0), rva(0) {}

    //bool contains        (uint64_t addr) { return (addr >= vma) && (addr-vma < size); }
    //bool is_import_table ()              { return name == ".plt"; }

    int streamType;
    int dataSize;
    int rva;
};

int parse_directory(MinidumpDir d,Binary* b,FILE*f);

#endif //NUCLEUS_MINIDUMP_H