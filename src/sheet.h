#pragma once


class SHEET{
public:
    typedef struct SHEET_STRUCT{
        int pointx;
        int pointy;
        int height;
        int width;
        struct SHEET_STRUCT *prev;
        struct SHEET_STRUCT *next;
    }SHEETS;
private:
    SHEETS dummy_sheet;
};