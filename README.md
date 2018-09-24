# c-cpp-tool
Some useful c/cpp classes


# ArgvProcessor
## What's this: 
A class which helps handle command line parameters.

## Introduce:
ArgvProcessor class requires a guide_map list created from user. Accroding to this guide_map, the class can handle the command line parameters.

###  guide_map Format:     
    std::map<const char *, std::pair<bool (*)(const char *), int>>
  The first item of std::map is a full-matching word. 
  We suggest adding "-" at the beginning. for example "-ignore". 
  Word "BIN" has been specifically defined for the executable file name(argv[0]).
  The first item of std::pair is a functor pointer that tells the Processor what to do after matcing the word.
  The second item of std::pair shows the number of parameters the Processor should take. 
  If n < 0, then means the number is unknown.

  Also, you can use argvmap_t instead:

    typedef std::map<const char *, std::pair<bool (*)(const char *), int>> argvmap_t;
#### example:
    argvmap_t argv_guide = {{BIN, {bin, 1}},
                           {"-hello", {hello, -1}},
                           {"-world", {world, 2}}};

    bool bin(const char *x)
    {
        printf("BIN %s\n", x);
        return true;
    }
### use:
    int ArgvProcessor::process(const char **const argv);
#### return type:
    ARGV_UNPROCESSED : no parameter found.
    #define ARGV_ERROR_RUNTIME : parameter Error when calling function.
    #define ARGV_UNKNOWN_PARAMETER : unknown parameter.
    #define ARGV_SUCCESS : successful.