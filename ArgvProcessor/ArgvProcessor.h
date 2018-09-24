
#ifndef __ARGV_PROCESSOR_H__
#define __ARGV_PROCESSOR_H__

#include <algorithm>
#include <map>
#include <string.h>
using namespace std;

extern const char *BIN;

#define ARGV_UNPROCESSED -3;
#define ARGV_ERROR_RUNTIME -2;
#define ARGV_UNKNOWN_PARAMETER -1;
#define ARGV_SUCCESS 0;


typedef map<const char *, pair<bool (*)(const char *), int>> argvmap_t;

class ArgvProcessor
{
  private:
    argvmap_t guide_map;
    struct char_cmp_t
    {
      private:
        const char *cmpchar;
      public:
        char_cmp_t(const char *str) { cmpchar = str; }
        bool operator()(const argvmap_t::value_type &pair)
        {
            return (strcmp(pair.first, cmpchar) == 0);
        }
    };

  public:
    ArgvProcessor(argvmap_t &map);
    int process(const char **argv);
};


#endif