#include "main.h"

/* 最初以外のエントリは使わない */
uint64_t Level4PageTable;
/* 0～7以外のエントリは使わない */
uint64_t Level3PageTable[8];
/* 全エントリ使用 */
uint64_t Level2PageTable[8][512];
/* 全エントリ使用 */
uint64_t Level1PageTable[8][512][512];

void init_paging(void)
{
    /* 対応した3段目のページテーブルのアドレス */
    Level4PageTable = reinterpret_cast<uint64_t>(&Level3PageTable[0]) | 0x3;
    for (int pt_3 = 0; pt_3 < 8; ++pt_3)
    {
        /* 対応した2段目のページテーブルのアドレス */
        Level3PageTable[pt_3] = reinterpret_cast<uint64_t>(&Level2PageTable[pt_3]) | 0x3;
        for (int pt_2 = 0; pt_2 < 512; ++pt_2)
        {
            /* 対応した1段目のページテーブルのアドレス */
            Level2PageTable[pt_3][pt_2] = reinterpret_cast<uint64_t>(&Level1PageTable[pt_3][pt_2]) | 0x3;
            for (int pt_1 = 0; pt_1 < 512; ++pt_1)
            {
                /* 仮想アドレス=物理アドレス */
                Level1PageTable[pt_3][pt_2][pt_1] = (pt_3 << 30) | (pt_2 << 21) | (pt_1 << 12) | 0x83;
            }
        }
    }
    // set_paging_reg();
    //set_CR3(reinterpret_cast<uint64_t>(&Level4PageTable));
}