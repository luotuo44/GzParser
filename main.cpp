//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include<string.h>

#include<iostream>
#include<string>
#include<iterator>
#include<algorithm>


#include"GzParser.h"

using namespace std;




int main(int argc, char **argv)
{
    if( argc < 2 )
    {
        std::cout<<"usage: "<<argv[0]<<" xxx.gz "<<std::endl;
        return 1;
    }

    std::string gz_file = argv[1];


    GzParser parser(gz_file);
    for(auto &&e : parser)
    {
        std::cout<<e<<std::endl;
    }

    //std::copy(GzParser(gz_file), GzParser(), std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}

