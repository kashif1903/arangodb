////////////////////////////////////////////////////////////////////////////////
/// @brief cursor
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2014 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2014, ArangoDB GmbH, Cologne, Germany
/// @author Copyright 2012-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGOD_UTILS_CURSOR_H
#define ARANGOD_UTILS_CURSOR_H 1

#include "Basics/Common.h"
#include "Basics/StringBuffer.h"
#include "VocBase/voc-types.h"

struct TRI_json_t;
struct TRI_vocbase_t;

namespace triagens {
namespace arango {

class CollectionExport;


typedef TRI_voc_tick_t CursorId;

class Cursor {
 public:
  Cursor(Cursor const&) = delete;
  Cursor& operator=(Cursor const&) = delete;

  Cursor(CursorId, size_t, struct TRI_json_t*, double, bool);

  virtual ~Cursor();

  
 public:
  CursorId id() const { return _id; }

  size_t batchSize() const { return _batchSize; }

  struct TRI_json_t* extra() const {
    return _extra;
  }

  bool hasCount() const { return _hasCount; }

  double ttl() const { return _ttl; }

  double expires() const { return _expires; }

  bool isUsed() const { return _isUsed; }

  bool isDeleted() const { return _isDeleted; }

  void deleted() { _isDeleted = true; }

  void use() {
    TRI_ASSERT(!_isDeleted);
    TRI_ASSERT(!_isUsed);

    _isUsed = true;
    _expires = TRI_microtime() + _ttl;
  }

  void release() {
    TRI_ASSERT(_isUsed);
    _isUsed = false;
  }

  virtual bool hasNext() = 0;

  virtual struct TRI_json_t* next() = 0;

  virtual size_t count() const = 0;

  virtual void dump(triagens::basics::StringBuffer&) = 0;

  
 protected:
  CursorId const _id;
  size_t const _batchSize;
  size_t _position;
  struct TRI_json_t* _extra;
  double _ttl;
  double _expires;
  bool const _hasCount;
  bool _isDeleted;
  bool _isUsed;
};


class JsonCursor : public Cursor {
 public:
  JsonCursor(TRI_vocbase_t*, CursorId, struct TRI_json_t*, size_t,
             struct TRI_json_t*, double, bool, bool);

  ~JsonCursor();

  
 public:
  bool hasNext() override final;

  struct TRI_json_t* next() override final;

  size_t count() const override final;

  void dump(triagens::basics::StringBuffer&) override final;

  
 private:
  void freeJson();

  
 private:
  TRI_vocbase_t* _vocbase;
  struct TRI_json_t* _json;
  size_t const _size;
  bool _cached;
};


class ExportCursor : public Cursor {
 public:
  ExportCursor(TRI_vocbase_t*, CursorId, triagens::arango::CollectionExport*,
               size_t, double, bool);

  ~ExportCursor();

  
 public:
  bool hasNext() override final;

  struct TRI_json_t* next() override final;

  size_t count() const override final;

  void dump(triagens::basics::StringBuffer&) override final;

  
 private:
  TRI_vocbase_t* _vocbase;
  triagens::arango::CollectionExport* _ex;
  size_t const _size;
};
}
}

#endif


