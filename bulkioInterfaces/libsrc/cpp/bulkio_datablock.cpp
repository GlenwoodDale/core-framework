/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file
 * distributed with this source distribution.
 *
 * This file is part of REDHAWK bulkioInterfaces.
 *
 * REDHAWK bulkioInterfaces is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * REDHAWK bulkioInterfaces is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#include <stdexcept>
#include <vector>

#include <boost/make_shared.hpp>

#include "bulkio_base.h"
#include "bulkio_datablock.h"
#include "bulkio_sri.h"
#include "bulkio_time_operators.h"

namespace bulkio {
    namespace {
        double get_drift(const SampleTimestamp& begin, const bulkio::SampleTimestamp& end, double xdelta)
        {
            double real = end.time - begin.time;
            double expected = (end.offset - begin.offset)*xdelta;
            return real-expected;
        }

        void validate_timestamps(const std::list<SampleTimestamp>& timestamps)
        {
            // Validity checks
            if (timestamps.empty()) {
                throw std::logic_error("block contains no timestamps");
            } else if (timestamps.front().offset != 0) {
                throw std::logic_error("no timestamp at offset 0");
            }
        }
    }
}

using bulkio::SampleTimestamp;
using bulkio::DataBlock;

template <class T>
struct DataBlock<T>::Impl
{
    Impl(const bulkio::SharedSRI& sri, const T& data) :
        data(data),
        sri(sri),
        sriChangeFlags(bulkio::sri::NONE),
        inputQueueFlushed(false)
    {
    }

    T data;
    bulkio::SharedSRI sri;
    std::list<SampleTimestamp> timestamps;
    int sriChangeFlags;
    bool inputQueueFlushed;
};

template <class T>
DataBlock<T>::DataBlock() :
    _impl()
{
}

template <class T>
DataBlock<T>::DataBlock(const bulkio::SharedSRI& sri, const T& data) :
    _impl(boost::make_shared<Impl>(sri, data))
{
}

template <class T>
DataBlock<T> DataBlock<T>::copy() const
{
    DataBlock result;
    if (_impl) {
        result._impl = boost::make_shared<Impl>(*_impl);
    }
    return result;
}

template <class T>
const bulkio::SRI& DataBlock<T>::sri() const
{
    return *(_impl->sri);
}

template <class T>
double DataBlock<T>::xdelta() const
{
    return sri().xdelta;
}

template <class T>
const T& DataBlock<T>::data() const
{
    return _impl->data;
}

template <class T>
void DataBlock<T>::addTimestamp(const bulkio::SampleTimestamp& timestamp)
{
    std::list<SampleTimestamp>::iterator pos = _impl->timestamps.begin();
    const std::list<SampleTimestamp>::iterator end = _impl->timestamps.end();
    while ((pos != end) && (timestamp.offset >= pos->offset)) {
        // TODO: Replace existing
        ++pos;
    }
    _impl->timestamps.insert(pos, timestamp);
}

template <class T>
std::list<SampleTimestamp> DataBlock<T>::getTimestamps() const
{
    return _impl->timestamps;
}

template <class T>
const BULKIO::PrecisionUTCTime& DataBlock<T>::getStartTime() const
{
    const std::list<SampleTimestamp>& timestamps = _impl->timestamps;
    validate_timestamps(timestamps);

    return _impl->timestamps.front().time;
}

template <class T>
double DataBlock<T>::getNetTimeDrift() const
{
    const std::list<SampleTimestamp>& timestamps = _impl->timestamps;
    validate_timestamps(timestamps);

    return get_drift(timestamps.front(), timestamps.back(), xdelta());
}

template <class T>
double DataBlock<T>::getMaxTimeDrift() const
{
    const std::list<SampleTimestamp>& timestamps = _impl->timestamps;
    validate_timestamps(timestamps);

    double max = 0.0;
    std::list<SampleTimestamp>::const_iterator current = timestamps.begin();
    std::list<SampleTimestamp>::const_iterator next = current;
    ++next;
    for (; next != timestamps.end(); ++current, ++next) {
        double drift = get_drift(*current, *next, xdelta());
        if (std::abs(drift) > std::abs(max)) {
            max = drift;
        }
    }
    return max;
}

template <class T>
bool DataBlock<T>::sriChanged() const
{
    return sriChangeFlags() != bulkio::sri::NONE;
}

template <class T>
int DataBlock<T>::sriChangeFlags() const
{
    return _impl->sriChangeFlags;
}

template <class T>
void DataBlock<T>::sriChangeFlags(int flags)
{
    _impl->sriChangeFlags = flags;
}

template <class T>
bool DataBlock<T>::inputQueueFlushed() const
{
    return _impl->inputQueueFlushed;
}

template <class T>
void DataBlock<T>::inputQueueFlushed(bool flushed)
{
    _impl->inputQueueFlushed = flushed;
}

template <class T>
DataBlock<T>::operator unspecified_bool_type() const
{
    return _impl?&DataBlock::_impl:0;
}

using bulkio::SampleDataBlock;

template <class T>
SampleDataBlock<T>::SampleDataBlock() :
    Base()
{
}

template <class T>
SampleDataBlock<T>::SampleDataBlock(const bulkio::SharedSRI& sri,
                                    const ScalarBuffer& buffer) :
    Base(sri, buffer)
{
}

template <class T>
SampleDataBlock<T>::SampleDataBlock(const BULKIO::StreamSRI& sri, size_t size) :
    Base(bulkio::SharedSRI(sri), redhawk::buffer<T>(size))
{
}

template <class T>
T* SampleDataBlock<T>::data()
{
    return const_cast<T*>(_impl->data.data());
}

template <class T>
const T* SampleDataBlock<T>::data() const
{
    return _impl->data.data();
}

template <class T>
size_t SampleDataBlock<T>::size() const
{
    return _impl->data.size();
}

template <class T>
void SampleDataBlock<T>::resize(size_t count)
{
    // TODO: Copy data
    _impl->data = redhawk::buffer<T>(count);
}

template <class T>
bool SampleDataBlock<T>::complex() const
{
    return this->sri().complex();
}

template <class T>
std::complex<T>* SampleDataBlock<T>::cxdata()
{
    return reinterpret_cast<ComplexType*>(data());
}

template <class T>
const std::complex<T>* SampleDataBlock<T>::cxdata() const
{
    return reinterpret_cast<const ComplexType*>(data());
}

template <class T>
size_t SampleDataBlock<T>::cxsize() const
{
    return size() / 2;
}

template <class T>
void SampleDataBlock<T>::swap(std::vector<ScalarType>& other)
{
    // Copy the vector data into a new shared buffer
    ScalarBuffer data = ScalarBuffer::make_transient(&other[0], other.size()).copy();
    // Swap the block's data with the new shared buffer
    _impl->data.swap(data);
    // Assign the old data to the vector
    other.assign(data.begin(), data.end());
}

template <class T>
typename SampleDataBlock<T>::ScalarBuffer SampleDataBlock<T>::buffer() const
{
    return _impl->data;
}

template <class T>
typename SampleDataBlock<T>::ComplexBuffer SampleDataBlock<T>::cxbuffer() const
{
    return ComplexBuffer::recast(_impl->data);
}

template <class T>
void SampleDataBlock<T>::buffer(const ScalarBuffer& data)
{
    _impl->data = data;
}

// Instantiate templates for supported types
#define INSTANTIATE_TEMPLATE(x)                 \
    template class DataBlock< x >;

#define INSTANTIATE_NUMERIC_TEMPLATE(x)                                 \
    INSTANTIATE_TEMPLATE(redhawk::shared_buffer<x>); template class SampleDataBlock<x>;

INSTANTIATE_TEMPLATE(std::string);
INSTANTIATE_NUMERIC_TEMPLATE(int8_t);
INSTANTIATE_NUMERIC_TEMPLATE(CORBA::Octet);
INSTANTIATE_NUMERIC_TEMPLATE(CORBA::Short);
INSTANTIATE_NUMERIC_TEMPLATE(CORBA::UShort);
INSTANTIATE_NUMERIC_TEMPLATE(CORBA::Long);
INSTANTIATE_NUMERIC_TEMPLATE(CORBA::ULong);
INSTANTIATE_NUMERIC_TEMPLATE(CORBA::LongLong);
INSTANTIATE_NUMERIC_TEMPLATE(CORBA::ULongLong);
INSTANTIATE_NUMERIC_TEMPLATE(CORBA::Float);
INSTANTIATE_NUMERIC_TEMPLATE(CORBA::Double);
