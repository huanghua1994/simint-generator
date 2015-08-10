#include <iostream>
#include <memory>
#include <stdexcept>
#include <fstream>

#include "generator/Algorithms.hpp"
#include "generator/Helpers.hpp"
#include "generator/Options.hpp"
#include "generator/WriterInfo.hpp"
#include "generator/ET_Writer.hpp"

using namespace std;

int main(int argc, char ** argv)
{
    try {

    // default options
    OptionsMap options = DefaultOptions();

    // max L value
    int maxL = 0;

    // other stuff
    std::string fpath;
    std::string cpuinfofile;

    // parse command line
    int i = 1;
    while(i < argc)
    {
        std::string argstr(GetNextArg(i, argc, argv));
        if(argstr == "-L")
            maxL = GetIArg(i, argc, argv);
        else if(argstr == "-o")
            fpath = GetNextArg(i, argc, argv);
        else if(argstr == "-c")
            cpuinfofile = GetNextArg(i, argc, argv);
        else if(argstr == "-i")
            options[OPTION_INTRINSICS] = 1;
        else if(argstr == "-S")
            options[OPTION_SCALAR] = 1;
        else
        {
            std::cout << "\n\n";
            std::cout << "--------------------------------\n";
            std::cout << "Unknown argument: " << argstr << "\n";
            std::cout << "--------------------------------\n";
            return 1; 
        } 
    }

    if(fpath == "")
    {
        std::cout << "\noutput path (-o) required\n\n";
        return 2;
    }

    if(maxL == 0)
    {
        std::cout << "\nMaximum L value (-L) required\n\n";
        return 2;
    }

    if(cpuinfofile == "")
    {
        std::cout << "\nCPU info file required\n\n";
        return 2;
    }

    if(fpath.back() != '/')
        fpath += '/';



    // different source and header files
    std::string srcpath = fpath + "et.c";
    std::string headpath = fpath + "et.h";
    
    cout << "Generating source file " << srcpath << "\n";
    cout << "Generating header file " << headpath << "\n";

    std::ofstream of(srcpath);
    if(!of.is_open())
    {
        std::cout << "Cannot open file: " << srcpath << "\n";
        return 2; 
    }

    std::ofstream ofh(headpath);
    if(!ofh.is_open())
    {
        std::cout << "Cannot open file: " << headpath << "\n";
        return 2; 
    }

    // start the header file
    ofh << "#ifndef ET__H\n";
    ofh << "#define ET__H\n";
    ofh << "\n";
    ofh << "#include \"eri/eri.h\"\n";
    ofh << "\n";

    // init once here to get the includes
    WriterInfo::Init(options, {maxL, 0, 0, 0}, cpuinfofile);
    WriterInfo::WriteIncludes(ofh);

    // output to source file
    of << "#include \"eri/eri.h\"\n";

    // we want all gaussians up to the maximum L value
    for(i = 0; i <= maxL; i++)
    for(int j = 1; j <= maxL; j++)
    {
        if(i == 0 && j == 0)
            continue;

        // The algorithm to use 
        std::unique_ptr<ET_Algorithm_Base> etalgo(new Makowski_ET);

        QAM am{i, 0, j, 0};
        WriterInfo::Init(options, am, cpuinfofile);

        // Create the mapping
        etalgo->Create(am);

        ET_Writer et_writer(*etalgo);

        // write to the output file
        et_writer.WriteETFile(of, ofh);
        cout << "Done!\n";

    }

    ofh << "\n";
    ofh << "#endif\n\n";
    

    } // close try block
    catch(std::exception & ex)
    {
        cout << "\n\n";
        cout << "Caught exception\n";
        cout << "What = " << ex.what() << "\n\n";
        return 100;
    }
    return 0;
}
