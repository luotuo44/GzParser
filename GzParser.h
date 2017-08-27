//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef GZPARSER_H
#define GZPARSER_H


#include<string>
#include<memory>



class GzParser : public std::iterator<std::input_iterator_tag, std::string>
{
public:
    explicit GzParser(const std::string &filename);
    GzParser();

    GzParser(const GzParser&)=default;
    GzParser& operator = (const GzParser&)=default;
    GzParser(GzParser &&gp)=default;
    GzParser& operator = (GzParser &&gp)=default;

    ~GzParser();


public:
    std::string operator *()const;

    void operator ++ ();
    void operator ++ (int);
    bool operator != (const GzParser &gp)const { return !(*this == gp); }
    bool operator == (const GzParser &gp)const;

    GzParser begin(){ return *this; }
    GzParser end() { return GzParser();}

private:
    class Impl;

private:
    std::shared_ptr<Impl> m_impl;
};


#endif // GZPARSER_H

