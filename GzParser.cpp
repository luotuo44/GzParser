//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include"GzParser.h"

#include<stdexcept>


#include<zlib.h>

class GzParser::Impl
{
public:
    Impl();
    explicit Impl(const std::string &filename);
    Impl(const Impl&)=delete;
    Impl& operator = (const Impl&)=delete;


public:
    std::string operator *()const;

    void operator ++ ();
    void operator ++ (int);
    bool operator == (const Impl &impl)const;

private:
    void readData();

private:
    gzFile m_gzfp = nullptr;
    std::string m_str;
    std::string::size_type m_data_end = 0;
    std::string::size_type m_delim_pos = std::string::npos;
    std::string::size_type m_last_delim_pos = std::string::npos;

    std::string m_cur_str;

    bool m_finish;
};



GzParser::Impl::Impl()
    : m_finish(true)
{
}

GzParser::Impl::Impl(const std::string &filename)
    : m_finish(false)
{
    m_gzfp = gzopen(filename.c_str(), "rb");
    if(!m_gzfp)
    {
        throw std::logic_error("cannot open " + filename);
    }

    m_str.reserve(40960);

    readData();
}


void GzParser::Impl::readData()
{
    m_data_end = m_str.size();
    m_str.resize(m_data_end + std::max(static_cast<size_t>(4), 2*m_data_end));

    //m_delim_pos = std::string::npos;
    int num = 0;
    while( (num = gzread(m_gzfp, &m_str[m_data_end], m_str.size()-m_data_end)) > 0)
    {
        m_data_end += num;
        m_str.resize(m_data_end);//这一步很重要，防止越界find

        if( (m_delim_pos = m_str.find('\n')) != std::string::npos)
            break;
        else
        {
            m_data_end = m_str.size();
            m_str.resize(m_data_end + 2*num);
        }
    }

    if(num <= 0)
    {
        m_finish = true;
        if( gzclose(m_gzfp) != Z_OK )
            throw std::runtime_error("the gz file is incomplete or invalid stream");

        return ;
    }


    m_cur_str = m_str.substr(0, m_delim_pos);
}


std::string GzParser::Impl::operator *()const
{
    if( m_finish )
    {
        throw std::runtime_error("unexpect error");
    }

    return m_cur_str;
}


void GzParser::Impl::operator ++ ()
{
    auto last_pos = m_delim_pos+1;
    if( (m_delim_pos = m_str.find('\n', last_pos)) != std::string::npos)
        m_cur_str = m_str.substr(last_pos, m_delim_pos-last_pos);
    else
    {
        m_str.erase(0, last_pos);
        readData();
    }
}

void GzParser::Impl::operator ++ (int)
{
    ++(*this);
}



bool GzParser::Impl::operator == (const Impl &impl)const
{
    //任何两个正在读取的GzParser都不会相等
    return m_finish == impl.m_finish && m_finish == true;
}


//==========================================================


GzParser::GzParser(const std::string &filename)
    : m_impl(std::make_shared<Impl>(filename))
{
}


GzParser::GzParser()
    : m_impl(std::make_shared<Impl>())
{
}


GzParser::~GzParser()
{
}



std::string GzParser::operator *()const
{
    return m_impl->operator *();
}


void GzParser::operator ++ ()
{
    ++*m_impl;
}


void GzParser::operator ++ (int)
{
    (*m_impl)++;
}


bool GzParser::operator == (const GzParser &gp)const
{
    return *m_impl == *gp.m_impl;
}




