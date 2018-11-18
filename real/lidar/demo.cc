
#include <exception>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include <unistd.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;

#include "lidar.hh"
#include "view.hh"

int
main(int argc, char* argv[])
{
    Lidar neem;
    neem.start();
    return start_view(argc, argv, &neem);
}

