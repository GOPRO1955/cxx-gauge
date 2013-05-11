#pragma once

#include <cassert>
#include <cstdint>
#include <boost/any.hpp>

namespace gauge
{

    /// Simple helper format struct, used when printing values.
    /// The format for specific data types may be overwritten to
    /// produce a specific output.
    struct format
    {
    public:

        virtual void print(std::ostream &s, bool val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, int8_t val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, uint8_t val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, int16_t val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, uint16_t val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, int32_t val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, uint32_t val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, int64_t val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, uint64_t val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, float val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, double val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, const std::string &val) const
        {
            s << val;
        }

        virtual void print(std::ostream &s, const boost::any &val) const
        {
            if(val.empty())
                return;

            if(typeid(bool) == val.type())
                return print(s, boost::any_cast<bool>(val));

            if(typeid(int8_t) == val.type())
                return print(s, boost::any_cast<int8_t>(val));

            if(typeid(uint8_t) == val.type())
                return print(s, boost::any_cast<uint8_t>(val));

            if(typeid(int16_t) == val.type())
                return print(s, boost::any_cast<int16_t>(val));

            if(typeid(uint16_t) == val.type())
                return print(s, boost::any_cast<uint16_t>(val));

            if(typeid(int32_t) == val.type())
                return print(s, boost::any_cast<int32_t>(val));

            if(typeid(uint32_t) == val.type())
                return print(s, boost::any_cast<uint32_t>(val));

            if(typeid(int64_t) == val.type())
                return print(s, boost::any_cast<int64_t>(val));

            if(typeid(uint64_t) == val.type())
                return print(s, boost::any_cast<uint64_t>(val));

            if(typeid(float) == val.type())
                return print(s, boost::any_cast<float>(val));

            if(typeid(double) == val.type())
                return print(s, boost::any_cast<double>(val));

            if(typeid(std::string) == val.type())
                return print(s, boost::any_cast<std::string>(val));

            std::cout << val.type().name() << std::endl;
            std::cout << typeid(std::string).name() << std::endl;
            // We don't know how to convert this type
            assert(0);

        }

    };

}