# GzParser
对zlib的解压C API用C++11封装，使用风格和STL相似

```c++

std::string gz_file = "xxx.gz";

GzParser parser(gz_file);
for(auto &&e : parser)
{
    std::cout<<e<<std::endl;
}

//std::copy(GzParser(gz_file), GzParser(), std::ostream_iterator<std::string>(std::cout, "\n"));
```

