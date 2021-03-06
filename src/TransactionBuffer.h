/* Header for TransactionBuffer class
   Copyright (C) 2018-2020 Adam Leszczynski.

This file is part of Open Log Replicator.

Open Log Replicator is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 3, or (at your option)
any later version.

Open Log Replicator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License
along with Open Log Replicator; see the file LICENSE.txt  If not see
<http://www.gnu.org/licenses/>.  */

#include "types.h"

#ifndef TRANSACTIONBUFFER_H_
#define TRANSACTIONBUFFER_H_

#define ROW_HEADER_MEMORY (sizeof(struct RedoLogRecord)+sizeof(struct RedoLogRecord)+sizeof(typeuba)+sizeof(uint32_t)+sizeof(uint32_t)+sizeof(uint32_t)+sizeof(uint32_t)+sizeof(uint32_t)+sizeof(uint32_t)+sizeof(typescn))

namespace OpenLogReplicator {

    class TransactionChunk;
    class RedoLogRecord;

    class TransactionBuffer {
    protected:
        TransactionChunk *unused;
        uint32_t usedBuffers;
        uint32_t redoBuffers;
        uint32_t redoBufferSize;

        void appendTransactionChunk(TransactionChunk* tc, uint32_t objn, uint32_t objd, typeuba uba, uint32_t dba,
                uint8_t slt, uint8_t rci, RedoLogRecord *redoLogRecord1, RedoLogRecord *redoLogRecord2);
    public:
        TransactionChunk* newTransactionChunk();
        TransactionChunk* addTransactionChunk(TransactionChunk* tc, uint32_t objn, uint32_t objd, typeuba uba, uint32_t dba,
                uint8_t slt, uint8_t rci, RedoLogRecord *redoLogRecord1, RedoLogRecord *redoLogRecord2);
        TransactionChunk* rollbackTransactionChunk(TransactionChunk* tc, typeuba &lastUba, uint32_t &lastDba,
                uint8_t &lastSlt, uint8_t &lastRci);
        bool getLastRecord(TransactionChunk* tc, uint32_t &opCode, RedoLogRecord* &redoLogRecord1, RedoLogRecord* &redoLogRecord2);
        bool deleteTransactionPart(TransactionChunk* tc, typeuba &uba, uint32_t &dba, uint8_t &slt, uint8_t &rci);
        void deleteTransactionChunk(TransactionChunk* tc);
        void deleteTransactionChunks(TransactionChunk* tc, TransactionChunk* lastTc);

        TransactionBuffer(uint32_t redoBuffers, uint32_t redoBufferSize);
        virtual ~TransactionBuffer();
    };
}

#endif
