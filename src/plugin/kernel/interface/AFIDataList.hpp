/*
 * This source file is part of ARK
 * For the latest info, see https://github.com/ArkNX
 *
 * Copyright (c) 2013-2020 ArkNX authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"),
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "base/AFString.hpp"
#include "base/AFMisc.hpp"
#include "base/AFDefine.hpp"
#include "AFIData.hpp"

namespace ark {

class AFIDataList
{
public:
    virtual bool Concat(const AFIDataList& src) = 0;
    virtual bool Split(const std::string& src, const std::string& split) = 0;

    virtual bool Append(const AFIData& data) = 0;
    virtual bool Append(const AFIDataList& src, size_t start, size_t count) = 0;

    virtual void Clear() = 0;

    virtual bool Empty() const = 0;

    virtual size_t GetCount() const = 0;

    virtual ArkDataType GetType(size_t index) const = 0;

    // add data
    virtual bool AddBool(bool value) = 0;
    virtual bool AddInt(int value) = 0;
    virtual bool AddInt64(int64_t value) = 0;
    virtual bool AddUInt(uint32_t value) = 0;
    virtual bool AddUInt64(uint64_t value) = 0;
    virtual bool AddFloat(float value) = 0;
    virtual bool AddDouble(double value) = 0;
    virtual bool AddString(const char* value) = 0;
    virtual bool AddPointer(void* value) = 0;
    virtual bool AddUserData(const void* pData, size_t size) = 0;
    virtual bool AddRawUserData(void* value) = 0;

    // get data
    virtual bool Bool(size_t index) const = 0;
    virtual int Int(size_t index) const = 0;
    virtual int64_t Int64(size_t index) const = 0;
    virtual uint32_t UInt(size_t index) const = 0;
    virtual uint64_t UInt64(size_t index) const = 0;
    virtual float Float(size_t index) const = 0;
    virtual double Double(size_t index) const = 0;
    virtual const char* String(size_t index) const = 0;
    virtual void* Pointer(size_t index) const = 0;
    virtual const void* UserData(size_t index, size_t& size) const = 0;
    virtual void* RawUserData(size_t index) const = 0;
    virtual const std::string ToString(size_t index) = 0;

    // get memory usage
    virtual size_t GetMemUsage() const = 0;

    template<typename... Args>
    bool TypeEx(const ArkDataType arg1, const Args&... args) const
    {
        bool bRet = true;
        ArkDataType values[] = {arg1, args...};

        int index = 0;

        for (auto v : values)
        {
            if (v == ArkDataType::DT_EMPTY)
            {
                bRet = false;
                return bRet;
            }

            ArkDataType varType = GetType(index);

            if (varType != v)
            {
                bRet = false;
                break;
            }

            ++index;
        }

        return bRet;
    }

    bool ToAFIData(size_t index, AFIData& xData) const
    {
        if (GetType(index) != xData.GetType())
        {
            return false;
        }

        switch (xData.GetType())
        {
        case ArkDataType::DT_BOOLEAN:
            xData.SetBool(Bool(index));
            break;
        case ArkDataType::DT_INT32:
            xData.SetInt(Int(index));
            break;
        case ArkDataType::DT_INT64:
            xData.SetInt64(Int64(index));
            break;
        case ArkDataType::DT_FLOAT:
            xData.SetFloat(Float(index));
            break;
        case ArkDataType::DT_DOUBLE:
            xData.SetDouble(Double(index));
            break;
        case ArkDataType::DT_STRING:
            xData.SetString(String(index));
            break;
        default:
            ARK_ASSERT_RET_VAL(0, false);
            break;
        }

        return true;
    }

    bool Equal(size_t index, const AFIData& xData) const
    {
        if (GetType(index) != xData.GetType())
        {
            return false;
        }

        switch (xData.GetType())
        {
        case ArkDataType::DT_BOOLEAN:
            return xData.GetBool() == Bool(index);
            break;
        case ArkDataType::DT_INT32:
            return xData.GetInt() == Int(index);
            break;
        case ArkDataType::DT_INT64:
            return xData.GetInt64() == Int64(index);
            break;
        case ArkDataType::DT_UINT32:
            return xData.GetUInt() == UInt(index);
            break;
        case ArkDataType::DT_UINT64:
            return xData.GetUInt64() == UInt64(index);
            break;
        case ArkDataType::DT_FLOAT:
            return IS_FLOAT_ZERO(float, xData.GetFloat() - Float(index));
            break;
        case ArkDataType::DT_DOUBLE:
            return IS_FLOAT_ZERO(double, xData.GetDouble() - Double(index));
            break;
        case ArkDataType::DT_STRING:
            return std::string(xData.GetString()) == std::string(String(index));
            break;
        default:
            ARK_ASSERT_RET_VAL(0, false);
            break;
        }

        return true;
    }

    // operator <<
    inline AFIDataList& operator<<(bool value)
    {
        bool bRet = AddBool(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(int8_t value)
    {
        bool bRet = AddInt(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(uint8_t value)
    {
        bool bRet = AddInt(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(int16_t value)
    {
        bool bRet = AddInt(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(uint16_t value)
    {
        bool bRet = AddInt(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(int32_t value)
    {
        bool bRet = AddInt(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(uint32_t value)
    {
        bool bRet = AddUInt(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(int64_t value)
    {
        bool bRet = AddInt64(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(uint64_t value)
    {
        bool bRet = AddUInt64(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(float value)
    {
        bool bRet = AddFloat(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(double value)
    {
        bool bRet = AddDouble(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }
    inline AFIDataList& operator<<(const char* value)
    {
        bool bRet = AddString(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }
    inline AFIDataList& operator<<(const std::string& value)
    {
        bool bRet = AddString(value.c_str());
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(const AFString<char, 128>& value)
    {
        bool bRet = AddString(value.c_str());
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }

    inline AFIDataList& operator<<(const AFIDataList& value)
    {
        bool bRet = Concat(value);
        ARK_ASSERT_NO_EFFECT(bRet);
        return *this;
    }
};

} // namespace ark
