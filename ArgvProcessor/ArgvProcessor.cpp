
#include "ArgvProcessor.h"

const char *BIN = "__BIN_EFFECT__";

ArgvProcessor::ArgvProcessor(argvmap_t &map)
{
    guide_map = map;
}

int ArgvProcessor::process(const char **argv)
{
    if (*(argv + 1) == nullptr)
    {
        return ARGV_UNPROCESSED;
    }

    for (const char **i = argv; *i != nullptr; ++i)
    {
        argvmap_t::iterator iter;
        iter = find_if(guide_map.begin(), guide_map.end(), char_cmp_t(*i));
        if ((iter == guide_map.end()) && (i != argv))
        {
            return ARGV_UNKNOWN_PARAMETER
        }
        if (i == argv)
        {
            iter = find_if(guide_map.begin(), guide_map.end(), char_cmp_t(BIN));
            if (iter == guide_map.end())
                return ARGV_UNKNOWN_PARAMETER;
        }
        //iter is now point to the function
        if (iter->second.second < 0)
        {
            while (true)
            {
                ++i;
                if (find_if(guide_map.begin(), guide_map.end(), char_cmp_t(*i)) == guide_map.end())
                //current i is not a instruction
                {
                    if (iter->second.first(*i) == false)
                        return ARGV_ERROR_RUNTIME;
                }
                else //it's a instruction
                {
                    --i;
                    break;
                }
            }
        }
        else
        { //int >= 0
            for (int j = 1; j <= iter->second.second; j++)
            {
                ++i;
                if (iter->second.first(*i) == false)
                {
                    return ARGV_ERROR_RUNTIME;
                }
            }
        }
    } //for
    return ARGV_SUCCESS;
}
