#pragma once

#include <iostream>
#include "idgenerator.h"
#include "storage.h"
#include "../drawing/bitmap.h"
#include "../drawing/IDrawing.h"
#include "../objects/dot.h"
#include "../objects/segment.h"


enum ObjType {
    OBJ_DOT,
    OBJ_SEG
};

enum RelativePosType {
    COINSIDENT_DOTS,
    EQUAL_LENGTH_SEGMENTS, // Отрезки должны быть одинаковы по длине
    ORTHO_SEGMENTS, // Отрезки должны быть ортогональны
};

enum SRPResult {
    ALL_OK = 0,
    INVALID_OBJECTS,
    INVALID_RELPOS
};


class Base {
public:

    struct dotinfo {
        ID id;
        dot* data;
    };

    struct seginfo {
        ID id;
        segment* data;
    };

    ID addObject(ObjType otype);
    void removeObject(size_t id);

    SRPResult setRelativePos(Storage<ID>& objects, RelativePosType rpt);
    double getError(Storage<ID>& objects, RelativePosType rpt);
    int getObjChildren(ID id, Storage<ID>& childIds);
    int getObjParams(ID id, Storage<double>& params);

    Storage<dotinfo>* getDotStorage();
    Storage<seginfo>* getSegmentStorage();
  
    void Print() const;

private:

    class relativePositionInfo {
    public:

        Storage<ID>* ids_storage;
        RelativePosType type;

        relativePositionInfo(Storage<ID>* ids_storage, const RelativePosType t) : ids_storage(ids_storage), type(t) {}
        relativePositionInfo() : ids_storage(nullptr), type(ORTHO_SEGMENTS) {}
    };

    Storage<dotinfo> m_dotStorage;
    Storage<seginfo> m_segmentStorage;

    Storage<relativePositionInfo> m_relativePositionInfoStorage;

    mutable IDrawing* m_idr;

    void setDrawing(IDrawing* idr) { 
        m_idr = idr;
    }

};
